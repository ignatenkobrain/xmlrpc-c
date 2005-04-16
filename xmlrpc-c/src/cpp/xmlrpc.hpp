#ifndef XMLRPC_HPP_INCLUDED
#define XMLRPC_HPP_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <time.h>

#include "xmlrpc.h"

namespace xmlrpc_c {


class value {
    // This is a handle.  You don't wnat to create a pointer to this;
    // it is in fact a pointer itself.
public:
    value();
        // This creates a placeholder.  It can't be used for anything, but
        // holds memory.  instantiate() can turn it into a real object.

    value(xmlrpc_c::value const &value);

    ~value();

    enum type_t {
        TYPE_INT        = 0,
        TYPE_BOOLEAN    = 1,
        TYPE_DOUBLE     = 2,
        TYPE_DATETIME   = 3,
        TYPE_STRING     = 4,
        TYPE_BYTESTRING = 5,
        TYPE_ARRAY      = 6,
        TYPE_STRUCT     = 7,
        TYPE_C_PTR      = 8,
        TYPE_NIL        = 9,
        TYPE_DEAD       = 0xDEAD,
    };

    type_t type() const;

    xmlrpc_c::value&
    operator=(xmlrpc_c::value const&);

    // The following are not meant to be public to users, but just to
    // other Xmlrpc-c library modules.  If we ever go to a pure C++
    // implementation, not based on C xmlrpc_value objects, this shouldn't
    // be necessary.

    void
    append_to_c_array(xmlrpc_value * const arrayP) const;

    void
    add_to_c_struct(xmlrpc_value * const structP,
                    string         const key) const;

    xmlrpc_value *
    c_value() const;

    value(xmlrpc_value * valueP);

    void
    instantiate(xmlrpc_value * const valueP);
        // Work only on a placeholder object created by the no-argument
        // constructor.

    xmlrpc_value * c_valueP;
        // NULL means this is merely a placeholder object.
};



class value_int : public value {
public:
    value_int(int const cvalue);

    value_int(xmlrpc_c::value const baseValue);

    operator int() const;
};



class value_double : public value {
public:
    value_double(double const cvalue);

    value_double(xmlrpc_c::value const baseValue);

    operator double() const;
};



class value_boolean : public value {
public:
    value_boolean(bool const cvalue);

    value_boolean(xmlrpc_c::value const baseValue);

    operator bool() const;
};



class value_datetime : public value {
public:
    value_datetime(std::string const cvalue);
    value_datetime(time_t const cvalue);
    value_datetime(struct timeval const& cvalue);
    value_datetime(struct timespec const& cvalue);

    value_datetime(xmlrpc_c::value const baseValue);

    operator time_t() const;
};



class value_string : public value {
public:
    value_string(std::string const& cvalue);

    value_string(xmlrpc_c::value const baseValue);

    operator string() const;
};



class value_bytestring : public value {
public:
    value_bytestring(std::vector<unsigned char> const& cvalue);

    value_bytestring(xmlrpc_c::value const baseValue);

    // You can't cast to a vector because the compiler can't tell which
    // constructor to use (complains about ambiguity).  So we have this:
    vector<unsigned char>
    vector_uchar_value() const;

    size_t
    length() const;
};



class value_array : public value {
public:
    value_array(std::vector<xmlrpc_c::value> const& cvalue);

    value_array(xmlrpc_c::value const baseValue);

    vector<xmlrpc_c::value>
    vector_value_value() const;

    unsigned int
    size() const;
};



class value_struct : public value {
public:
    value_struct(std::map<std::string, xmlrpc_c::value> const& cvalue);

    value_struct(xmlrpc_c::value const baseValue);

    operator std::map<std::string, xmlrpc_c::value>() const;
};



class value_nil : public value {
public:
    value_nil();

    value_nil(xmlrpc_c::value const baseValue);
};



class fault {
/*----------------------------------------------------------------------------
   This is an XML-RPC fault.

   This object is not intended to be used to represent a fault in the
   execution of XML-RPC client/server software -- just a fault in an
   XML-RPC RPC as described by the XML-RPC spec.

   There is no way to represent "no fault" with this object.  The object is
   meaningful only in the context of some fault.
-----------------------------------------------------------------------------*/
public:
    int faultCode;
    std::string faultDescription;
};

} // namespace

#endif
