#include "xmlrpc_config.h"  /* prereq for mallocvar.h -- defines __inline__ */

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <getopt.h>

#include "mallocvar.h"
#include "bool.h"
#include "casprintf.h"

#include "cmdline_parser.h"

#define MAXOPTS 100

struct optionDesc {
    const char *    name;
    enum optiontype type;
    bool            present;
    union {
        unsigned int u;
        int          i;
        const char * s;
    } value;
};



struct cmdlineParserCtl {
    struct optionDesc * optionDescArray;
    unsigned int        numOptions;
    const char **       argumentArray;
    unsigned int        numArguments;
};



static struct option *
createLongOptsArray(struct optionDesc * const optionDescArray,
                    unsigned int        const numOptions) {

    struct option * longopts; 

    MALLOCARRAY(longopts, numOptions+1);
    if (longopts != NULL) {
        unsigned int i;

        for (i = 0; i < numOptions; ++i) {
            longopts[i].name = optionDescArray[i].name;
            /* If the option takes a value, we say it is optional even
               though it never is.  That's because if we say it is
               mandatory, getopt_long_only() pretends it doesn't even
               recognize the option if the user doesn't give a value.
               We prefer to generate a meaningful error message when
               the user omits a required option value.
            */
            longopts[i].has_arg = 
                optionDescArray[i].type == OPTTYPE_FLAG ? 
                no_argument : optional_argument;
            longopts[i].flag = NULL;
            longopts[i].val = i;
        }
        longopts[numOptions] = (struct option) {0, 0, 0, 0};
    }
    return longopts;
}



static void
parseOptionValue(const char *        const optarg, 
                 struct optionDesc * const optionP,
                 const char **       const errorP) {
    
    switch (optionP->type) {
    case OPTTYPE_UINT: 
    case OPTTYPE_INT: {
        if (optarg == NULL)
            casprintf(errorP, "Option requires a value");
        else if (strlen(optarg) == 0)
            casprintf(errorP, "Numeric option value is null string");
        else {
            char * tailptr;
            long const longvalue = strtol(optarg, &tailptr, 10);
            if (*tailptr != '\0')
                casprintf(errorP, "Non-numeric value "
                         "for numeric option value: '%s'", optarg);
            else if (errno == ERANGE || longvalue > INT_MAX)
                casprintf(errorP, "Numeric value out of range: %s", optarg);
            else { 
                if (optionP->type == OPTTYPE_UINT) {
                    if (longvalue < 0)
                        casprintf(errorP, "Unsigned numeric value is "
                                  "negative: %ld", longvalue);
                    else {
                        *errorP = NULL;
                        optionP->value.u = (unsigned int) longvalue;
                    }
                } else {
                    *errorP = NULL;
                    optionP->value.u = (int) longvalue;
                }
            }
        }
    }
    break;
    case OPTTYPE_STRING:
        if (optarg == NULL)
            casprintf(errorP, "Option requires a value");
        else {
            *errorP = NULL;
            optionP->value.s = strdup(optarg);
        }
        break;
    case OPTTYPE_FLAG:
        *errorP = NULL;
        break;
    }
}



static void
processOption(struct optionDesc * const optionP,
              const char *        const optarg,
              const char **       const errorP) {

    const char * error;
    
    parseOptionValue(optarg, optionP, &error);
    if (error)
        casprintf(errorP, "Error in '%s' option: %s", optionP->name, error);
    else
        optionP->present = TRUE;
}



static void
extractArguments(struct cmdlineParserCtl * const cpP,
                 int                       const argc,
                 const char **             const argv,
                 int                       const optind) {
    
    cpP->numArguments = argc - optind;
    MALLOCARRAY(cpP->argumentArray, cpP->numArguments);

    if (cpP->argumentArray == NULL) {
        fprintf(stderr, "Unable to allocate memory for argument array\n");
        abort();
    } else {
        unsigned int i;

        for (i = 0; i < cpP->numArguments; ++i) {
            cpP->argumentArray[i] = strdup(argv[optind + i]);
            if (cpP->argumentArray[i] == NULL) {
                fprintf(stderr, "Unable to allocate memory for Argument %u\n",
                        i);
                abort();
            }
        }
    }
}



void
cmd_processOptions(cmdlineParser   const cpP,
                   int             const argc,
                   const char **   const argv, 
                   const char **   const errorP) {

    struct option * longopts;

    longopts = createLongOptsArray(cpP->optionDescArray, cpP->numOptions);

    if (longopts == NULL) 
        casprintf(errorP, "Unable to get memory for longopts array");
    else {
        bool endOfOptions;
        unsigned int i;

        *errorP = NULL;

        /* Set up initial assumption:  No options present */

        for (i = 0; i < cpP->numOptions; ++i)
            cpP->optionDescArray[i].present = FALSE;

        endOfOptions = FALSE;  /* initial value */
            
        while (!endOfOptions && !*errorP) {
            int rc;
            int longoptsIndex;
            
            opterr = 0; 
                /* Don't let getopt_long_only() print an error message */
            
            rc = getopt_long_only(argc, (char**) argv, "", longopts, 
                                  &longoptsIndex);
            if (rc < 0)
                endOfOptions = TRUE;
             else if (rc == '?') {
                 casprintf(errorP, "Unrecognized option: '%s'", 
                           argv[optind-1]);
            } else
                processOption(&cpP->optionDescArray[longoptsIndex], optarg,
                              errorP);
        }

        extractArguments(cpP, argc, argv, optind);

        free(longopts);
    }
}



cmdlineParser
cmd_createOptionParser(void) {

    struct cmdlineParserCtl * cpP;

    MALLOCVAR(cpP);

    if (cpP != NULL) {
        struct optionDesc * optionDescArray;

        cpP->numOptions = 0;
        MALLOCARRAY(optionDescArray, MAXOPTS);
        if (optionDescArray == NULL) {
            free(cpP);
            cpP = NULL;
        } else 
            cpP->optionDescArray = optionDescArray;
    }
    return cpP;
}



void
cmd_destroyOptionParser(cmdlineParser const cpP) {
    
    unsigned int i;

    for (i = 0; i < cpP->numOptions; ++i) {
        struct optionDesc const option = cpP->optionDescArray[i];
        if (option.type == OPTTYPE_STRING && option.present)
            strfree(option.value.s);
        strfree(option.name);
    }

    for (i = 0; i < cpP->numArguments; ++i)
        strfree(cpP->argumentArray[i]);

    free(cpP->optionDescArray);
    free(cpP);
}



void
cmd_defineOption(cmdlineParser   const cpP,
                 const char *    const name, 
                 enum optiontype const type) {
    
    if (cpP->numOptions < MAXOPTS) {
        cpP->optionDescArray[cpP->numOptions].name = strdup(name);
        cpP->optionDescArray[cpP->numOptions].type = type;
        
        ++cpP->numOptions;
    }
}



static struct optionDesc *
findOptionDesc(struct cmdlineParserCtl * const cpP,
               const char *              const name) {

    struct optionDesc * retval;
    unsigned int i;

    retval = NULL;

    for (i = 0; i < cpP->numOptions && !retval; ++i)
        if (strcmp(cpP->optionDescArray[i].name, name) == 0)
            retval = &cpP->optionDescArray[i];

    return retval;
}



int
cmd_optionIsPresent(cmdlineParser const cpP,
                    const char *  const name) {

    struct optionDesc * const optionDescP = findOptionDesc(cpP, name);

    bool present;

    if (!optionDescP) {
        fprintf(stderr, "cmdlineParser called incorrectly.  "
                "optionIsPresent() called for undefined option '%s'\n",
                name);
        abort();
    } else 
        present = optionDescP->present;

    return present;
}



unsigned int
cmd_getOptionValueUint(cmdlineParser const cpP,
                       const char *  const name) {

    struct optionDesc * const optionDescP = findOptionDesc(cpP, name);

    unsigned int retval;

    if (!optionDescP) {
        fprintf(stderr, "cmdlineParser called incorrectly.  "
                "cmd_getOptionValueUint() called for undefined option '%s'\n",
                name);
        abort();
    } else {
        if (optionDescP->type != OPTTYPE_UINT) {
            fprintf(stderr, "cmdlineParser called incorrectly.  "
                    "cmd_getOptionValueUint() called for non-unsigned integer "
                    "option '%s'\n", optionDescP->name);
            abort();
        } else {
            if (optionDescP->present) 
                retval = optionDescP->value.u;
            else
                retval = 0;
        }
    }
    return retval;
}



int
cmd_getOptionValueInt(cmdlineParser const cpP,
                      const char *  const name) {

    struct optionDesc * const optionDescP = findOptionDesc(cpP, name);

    int retval;

    if (!optionDescP) {
        fprintf(stderr, "cmdlineParser called incorrectly.  "
                "cmd_getOptionValueInt() called for undefined option '%s'\n",
                name);
        abort();
    } else {
        if (optionDescP->type != OPTTYPE_INT) {
            fprintf(stderr, "cmdlineParser called incorrectly.  "
                    "cmd_getOptionValueInt() called for non-integer "
                    "option '%s'\n", optionDescP->name);
            abort();
        } else {
            if (optionDescP->present) 
                retval = optionDescP->value.i;
            else
                retval = 0;
        }
    }

    return retval;
}



const char *
cmd_getOptionValueString(cmdlineParser const cpP,
                         const char *  const name) {

    struct optionDesc * const optionDescP = findOptionDesc(cpP, name);

    const char * retval;

    if (!optionDescP) {
        fprintf(stderr, "cmdlineParser called incorrectly.  "
                "cmd_getOptionValueString() called for " 
                "undefined option '%s'\n",
                name);
        abort();
    } else {
        if (optionDescP->type != OPTTYPE_STRING) {
            fprintf(stderr, "cmdlineParser called incorrectly.  "
                    "getOptionValueString() called for non-string "
                    "option '%s'\n", optionDescP->name);
            abort();
        } else {
            if (optionDescP->present) {
                retval = strdup(optionDescP->value.s);
                if (retval == NULL) {
                    fprintf(stderr, 
                            "out of memory in cmd_getOptionValueString()\n");
                    abort();
                }
            } else
                retval = NULL;
        }
    }
    return retval;
}



unsigned int 
cmd_argumentCount(cmdlineParser const cpP) {

    return cpP->numArguments;

}
                  


const char * 
cmd_getArgument(cmdlineParser const cpP, 
                unsigned int  const argNumber) { 

    const char * retval;
 
    if (argNumber >= cpP->numArguments)
        retval = NULL;
    else {
        retval = strdup(cpP->argumentArray[argNumber]);

        if (retval == NULL) {
            fprintf(stderr, 
                    "out of memory in cmd_getArgument()\n");
            abort();
        }
    }
    return retval;
}
