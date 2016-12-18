executable(
  'xmlrpc_pstream',
  sources : [
    'xmlrpc_pstream.cpp',
  ],
  dependencies : [
    dumpvalue,
    util_cpp_dep,
    readline,
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
  ],
  link_with : [
    libxmlrpc_clientpp,
  ],
  install : true,
)
