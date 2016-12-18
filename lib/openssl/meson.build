libxmlrpc_openssl = library(
  'xmlrpc_openssl',
  sources : [
    'xmlrpc_openssl_thread.c',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : [
    libxmlrpc_util,
  ],
  dependencies : openssl,
  soversion : '1',
  version : '1.@0@'.format(version_minor),
  install : true,
)

pkgg.generate(
  name : 'xmlrpc_openssl',
  description : 'Openssl convenience function from Xmlrpc-c package',
  version : meson.project_version(),
  requires : 'xmlrpc_util',
  libraries : libxmlrpc_openssl,
  install : true,
)
