libxmlrpc_utilpp = library(
  'xmlrpc_util++',
  sources : [
    'Lock.cpp',
    'base64.cpp',
    'env_wrap.cpp',
    'girerr.cpp',
    'girmem.cpp',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : libxmlrpc_util,
  soversion : '8',
  version : '8.@0@'.format(version_minor),
  install : true,
)

pkgg.generate(
  name : 'xmlrpc_util++',
  description : 'Xmlrpc-c C++ utility functions library',
  version : meson.project_version(),
  requires : 'xmlrpc_util',
  libraries : libxmlrpc_utilpp,
  install : true,
)
