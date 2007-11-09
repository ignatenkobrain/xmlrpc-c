#include <iostream>
#include <stdexcept>

#include "xmlrpc-c/oldcppwrapper.hpp"

#include "DataType.hpp"
#include "XmlRpcFunction.hpp"
#include "XmlRpcClass.hpp"
#include "SystemProxy.hpp"

using namespace std;

#define NAME           "xml-rpc-api2cpp"
#define VERSION        "0.1"


/*----------------------------------------------------------------------------
   Command line
-----------------------------------------------------------------------------*/

class cmdlineInfo {
public:
    string serverUrl;
    string methodPrefix;
    string localClass;

    cmdlineInfo(int           const argc,
                const char ** const argv);

private:
    cmdlineInfo();
};



cmdlineInfo::cmdlineInfo(int           const argc,
                         const char ** const argv) {

    if (argc-1 != 3) {
        cerr << argv[0] << ": Usage:" << endl
             << "  xml-rpc-api2cpp <server_url> <method_prefix> <local_class>"
             << endl << endl
             << "Sample arguments:" << endl
             << "  server_url = http://localhost/RPC2" << endl
             << "  method_prefix = system" << endl
             << "  local_class = SystemProxy" << endl;
        exit(1);
    }
    this->serverUrl    = string(argv[1]);
    this->methodPrefix = string(argv[2]);
    this->localClass   = string(argv[3]);
}



static XmlRpcClass
getClassInfo(string const& serverUrl,
             string const& classPrefix,
             string const& className) {
/*----------------------------------------------------------------------------
  Connect to a remote server and extract the information we'll need to
  build a proxy class.
-----------------------------------------------------------------------------*/
    XmlRpcClass info(className);

    SystemProxy system(serverUrl);

    XmlRpcValue const methods(system.listMethods());

    size_t const end = methods.arraySize();
    
    for (size_t i = 0; i < end; ++i) {

        // Break the method name into two pieces.
        string const methodName(methods.arrayGetItem(i).getString());
        size_t const lastDot(methodName.rfind('.'));

        string methodPrefix;
        string functionName;

        if (lastDot == string::npos) {
            methodPrefix = "";
            functionName = methodName;
        } else {
            methodPrefix = string(methodName, 0, lastDot);
            functionName = string(methodName, lastDot + 1);
        }

        if (methodPrefix == classPrefix) {
            // It's a method User cares about

            string const help(system.methodHelp(methodName));
            XmlRpcValue const signatureList(
                system.methodSignature(methodName));

            if (signatureList.getType() != XMLRPC_TYPE_ARRAY) {
                // It must be the string "undef", meaning the server
                // won't tell us any signatures.
                cerr << "Skipping method " << methodName << " "
                     << "because server does not report any signatures "
                     << "for it (via system.methodSignature method)"
                     << endl;
            } else {
                // Add this function to our class information.
                XmlRpcFunction const method(functionName,
                                            methodName,
                                            help,
                                            signatureList);
                info.addFunction(method);
            }
        }
    }
    return info;
}



static void
printHeader(ostream          & out,
            XmlRpcClass const& classInfo) {
/*----------------------------------------------------------------------------
  Print a complete header for the specified class.
-----------------------------------------------------------------------------*/
    string const className(classInfo.className());

    try {
        out << "// " << className << ".h - xmlrpc-c C++ proxy class" << endl;
        out << "// Auto-generated by xml-rpc-api2cpp." << endl;
        out << endl;

        string const headerSymbol("_" + className + "_H_");

        out << "#ifndef " << headerSymbol << endl;
        out << "#define " << headerSymbol << " 1" << endl;
        out << endl;
        out << "#include <XmlRpcCpp.h>" << endl;
        out << endl;

        classInfo.printDeclaration(cout);

        out << endl;
        out << "#endif /* " << headerSymbol << " */" << endl;
    } catch (exception const& e) {
        throw(logic_error("Failed to generate header for class " +
                          className + ".  " + e.what()));
    }
}



static void
printCppFile(ostream          & out,
             XmlRpcClass const& classInfo) {
/*----------------------------------------------------------------------------
  Print a complete definition for the specified class.
-----------------------------------------------------------------------------*/
    string const className(classInfo.className());

    try {
        out << "// " << className << ".cc - xmlrpc-c C++ proxy class" << endl;
        out << "// Auto-generated by xml-rpc-api2cpp." << endl;
        out << endl;
        
        out << "#include <XmlRpcCpp.h>" << endl;
        out << "#include \"" << className << ".h\"" << endl;
        
        classInfo.printDefinition(cout);
    } catch (XmlRpcFault const& fault) {
        throw(logic_error("Failed to generate definition for class " +
                          className + ".  " + fault.getFaultString()));
    }
}



int
main(int           const argc,
     const char ** const argv) {

    string const progName(argv[0]);

    cmdlineInfo const cmdline(argc, argv);

    int retval;

    XmlRpcClient::Initialize(NAME, VERSION);

    try {
        XmlRpcClass system = getClassInfo(cmdline.serverUrl,
                                          cmdline.methodPrefix,
                                          cmdline.localClass);
        printHeader(cout, system);
        cout << endl;
        printCppFile(cout, system);
        retval = 0;
    } catch (XmlRpcFault& fault) {
        cerr << progName << ": XML-RPC fault #" << fault.getFaultCode()
             << ": " << fault.getFaultString() << endl;
        retval = 1;
    } catch (logic_error& err) {
        cerr << progName << ": " << err.what() << endl;
        retval = 1;
    } catch (...) {
        cerr << progName << ": Unknown exception" << endl;
        retval = 1;
    }

    XmlRpcClient::Terminate();

    return retval;
}

