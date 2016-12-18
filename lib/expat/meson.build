subdir('gennmtab')
subdir('xmltok')
subdir('xmlparse')

pkgg.generate(
  name : 'xmlrpc_expat',
  description : 'Xmlrpc-c XML parsing library',
  version : meson.project_version(),
  requires: 'xmlrpc_util',
  libraries : [
    libxmlrpc_xmlparse,
    libxmlrpc_xmltok,
  ],
  install : true,
)
