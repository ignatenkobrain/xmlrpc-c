executable(
  'xml-rpc-api2cpp',
  sources : [
    'xml-rpc-api2cpp.cpp',
    'DataType.cpp',
    'XmlRpcFunction.cpp',
    'XmlRpcClass.cpp',
    'SystemProxy.cpp',
  ],
  include_directories : [
    hdr_incdir,
  ],
  link_with : [
    libxmlrpc_client,
    libxmlrpc_cpp,
  ],
  install : true,
)
install_man('xml-rpc-api2cpp.1')
