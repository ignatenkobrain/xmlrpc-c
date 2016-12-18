xmlparse_incdir = include_directories('.')

libxmlrpc_xmlparse = library(
  'xmlrpc_xmlparse',
  sources : [
    'xmlparse.c',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
    xmltok_incdir,
  ],
  link_with : [
    libxmlrpc_util,
    libxmlrpc_xmltok,
  ],
  soversion : '3',
  version : '3.@0@'.format(version_minor),
  install : true,
)
