xmlrpc_deps = []
xmlrpc_incs = []
xmlrpc_libs = []
# TODO: handle clients

if get_option('libxml2-backend')
  xmlrpc_xml_parser = 'xmlrpc_libxml2.c'
  xmlrpc_deps += [libxml2]
  xmlrpc_pkgconfig_req = 'libxml-2.0'
else
  xmlrpc_xml_parser = 'xmlrpc_expat.c'
  xmlrpc_incs += [xmlparse_incdir]
  xmlrpc_libs += [libxmlrpc_xmlparse]
  xmlrpc_pkgconfig_req = 'xmlrpc_expat'
endif

libxmlrpc = library(
  'xmlrpc',
  sources : [
    'base_global.c',
    'double.c',
    'json.c',
    'parse_datetime.c',
    'parse_value.c',
    'resource.c',
    'trace.c',
    'version.c',
    'xmlrpc_data.c',
    'xmlrpc_datetime.c',
    'xmlrpc_string.c',
    'xmlrpc_array.c',
    'xmlrpc_struct.c',
    'xmlrpc_build.c',
    'xmlrpc_decompose.c',
    xmlrpc_xml_parser,
    'xmlrpc_parse.c',
    'xmlrpc_serialize.c',
    'xmlrpc_authcookie.c',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ] + xmlrpc_incs,
  link_with : xmlrpc_libs,
  dependencies : xmlrpc_deps,
  soversion : 3,
  version : '3.@0@'.format(version_minor),
  install : true,
)
pkgg.generate(
  name : 'xmlrpc',
  description : 'Xmlrpc-c basic XML-RPC library',
  version : meson.project_version(),
  requires_private : xmlrpc_pkgconfig_req,
  libraries : libxmlrpc,
  install : true,
)

libxmlrpc_server = library(
  'xmlrpc_server',
  sources : [
    'registry.c',
    'method.c',
    'system_method.c',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : [
    libxmlrpc,
    libxmlrpc_util,
  ],
  soversion : 3,
  version : '3.@0@'.format(version_minor),
  install : true,
)
pkgg.generate(
  name : 'xmlrpc_server',
  description : 'Xmlrpc-c XML-RPC server library',
  version : meson.project_version(),
  requires_private : ['xmlrpc', 'xmlrpc_util'],
  libraries : libxmlrpc_server,
  install : true,
)

if get_option('abyss-server')
  libxmlrpc_server_abyss = library(
    'xmlrpc_server_abyss',
    sources : [
      'xmlrpc_server_abyss.c',
      'abyss_handler.c',
    ],
    include_directories : [
      top_incdir,
      hdr_incdir,
      util_incdir,
    ],
    link_with : [
      libxmlrpc,
      libxmlrpc_server,
      libxmlrpc_abyss,
      libxmlrpc_util,
    ],
    soversion : 3,
    version : '3.@0@'.format(version_minor),
    install : true,
  )
  pkgg.generate(
    name : 'xmlrpc_server_abyss',
    description : 'Xmlrpc-c Abyss XML-RPC server library',
    version : meson.project_version(),
    requires_private : ['xmlrpc', 'xmlrpc_server', 'xmlrpc_abyss', 'xmlrpc_util'],
    libraries : libxmlrpc_server_abyss,
    install : true,
  )
endif

if get_option('cgi-server')
  libxmlrpc_server_cgi = library(
    'xmlrpc_server_cgi',
    sources : [
      'xmlrpc_server_cgi.c',
    ],
    include_directories : [
      top_incdir,
      hdr_incdir,
      util_incdir,
    ],
    link_with : [
      libxmlrpc,
      libxmlrpc_server,
      libxmlrpc_util,
    ],
    soversion : 3,
    version : '3.@0@'.format(version_minor),
    install : true,
  )
  pkgg.generate(
    name : 'xmlrpc_server_cgi',
    description : 'Xmlrpc-c CGI XML-RPC server library',
    version : meson.project_version(),
    requires_private : ['xmlrpc', 'xmlrpc_server', 'xmlrpc_util'],
    libraries : libxmlrpc_server_cgi,
    install : true,
  )
endif

if build_client
  xmlrpc_client_transports = []
  if get_option('curl-client')
    xmlrpc_client_transports += [xmlrpc_curl_transport]
  endif
  libxmlrpc_client = library(
    'xmlrpc_client',
    sources : [
      'xmlrpc_client.c',
      'xmlrpc_client_global.c',
      'xmlrpc_server_info.c',
    ],
    include_directories : [
      top_incdir,
      hdr_incdir,
      util_incdir,
    ],
    link_with : [
      libxmlrpc,
      libxmlrpc_util,
    ],
    dependencies : xmlrpc_client_transports,
    soversion : 3,
    version : '3.@0@'.format(version_minor),
    install : true,
  )
  pkgg.generate(
    name : 'xmlrpc_client',
    description : 'Xmlrpc-c XML-RPC client library',
    version : meson.project_version(),
    requires_private : ['xmlrpc', 'xmlrpc_util'],
    libraries : libxmlrpc_client,
    install : true,
  )
endif

if get_option('cplusplus')
  subdir('cpp')
endif
