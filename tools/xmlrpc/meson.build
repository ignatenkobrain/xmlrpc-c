executable(
  'xmlrpc',
  sources : [
    'xmlrpc.c',
  ],
  dependencies : [
    dumpvalue,
    util_dep,
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : [
    libxmlrpc,
    libxmlrpc_client,
  ],
  install : true,
)
