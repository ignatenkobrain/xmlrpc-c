subdir('gennmtab')
subdir('xmltok')
subdir('xmlparse')

pkgg.generate(
  name : 'xmlrpc_expat',
  description : 'Xmlrpc-c XML parsing library',
  version : meson.project_version(),
  requires_private: 'xmlrpc_util',
  libraries : [
    libxmlrpc_xmlparse,
    libxmlrpc_xmltok,
  ],
  install : true,
)
