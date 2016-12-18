executable(
  'xmlrpc_transport',
  sources : [
    'xmlrpc_transport.c',
  ],
  dependencies : [
    util_dep,
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
  ],
  link_with : [
    libxmlrpc_client,
  ],
  install : true,
)
