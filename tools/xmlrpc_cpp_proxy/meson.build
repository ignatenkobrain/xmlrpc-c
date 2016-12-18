executable(
  'xmlrpc_cpp_proxy',
  sources : [
    'xmlrpc_cpp_proxy.cpp',
    'xmlrpcMethod.cpp',
    'xmlrpcType.cpp',
    'proxyClass.cpp',
    'systemProxy.cpp',
  ],
  include_directories : [
    hdr_incdir,
  ],
  link_with : [
    libxmlrpcpp,
    libxmlrpc_clientpp,
  ],
  install : true,
)
