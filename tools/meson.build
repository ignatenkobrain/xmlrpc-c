subdir('lib')
subdir('xml')
if build_client
  subdir('xmlrpc')
  subdir('xmlrpc_transport')
  if get_option('cplusplus')
    subdir('xml-rpc-api2cpp')
    subdir('xml-rpc-api2txt')
    subdir('xmlrpc_cpp_proxy')
    if build_xmlrpc_pstream
      subdir('xmlrpc_pstream')
    endif
  endif
endif
