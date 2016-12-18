libxmlrpc_cpp = library(
  'xmlrpc_cpp',
  sources : [
    'XmlRpcCpp.cpp',
  ],
  include_directories : [
    hdr_incdir,
  ],
  link_with : [
    libxmlrpc,
    libxmlrpc_util,
    libxmlrpc_server,
  ],
  soversion : 8,
  version : '8.@0@'.format(version_minor),
  install : true,
)

libxmlrpcpp = library(
  'xmlrpc++',
  sources : [
    'fault.cpp',
    'global.cpp',
    'outcome.cpp',
    'param_list.cpp',
    'value.cpp',
    'xml.cpp',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : [
    libxmlrpc,
    libxmlrpc_utilpp,
  ],
  soversion : 8,
  version : '8.@0@'.format(version_minor),
  install : true,
)
pkgg.generate(
  name : 'xmlrpc++',
  description : 'Xmlrpc-c basic XML-RPC C++ library',
  version : meson.project_version(),
  requires_private : ['xmlrpc', 'xmlrpc_util++'],
  libraries : libxmlrpcpp,
  install : true,
)

libxmlrpc_serverpp = library(
  'xmlrpc_server++',
  sources : [
    'registry.cpp',
  ],
  include_directories : [
    hdr_incdir,
  ],
  link_with : [
    libxmlrpcpp,
    libxmlrpc_server,
  ],
  soversion : 8,
  version : '8.@0@'.format(version_minor),
  install : true,
)
pkgg.generate(
  name : 'xmlrpc_server++',
  description : 'Xmlrpc-c XML-RPC server C++ library',
  version : meson.project_version(),
  requires_private : ['xmlrpc++', 'xmlrpc_server'],
  libraries : libxmlrpc_serverpp,
  install : true,
)

if get_option('abyss-server')
  libxmlrpc_server_abysspp = library(
    'xmlrpc_server_abyss++',
    sources : [
      'server_abyss.cpp',
      'abyss_reqhandler_xmlrpc.cpp',
    ],
    include_directories : [
      top_incdir,
      hdr_incdir,
      util_incdir,
    ],
    link_with : [
      libxmlrpc_abysspp,
      libxmlrpc_serverpp,
      libxmlrpc_server_abyss,
    ],
    soversion : 8,
    version : '8.@0@'.format(version_minor),
    install : true,
  )
  pkgg.generate(
    name : 'xmlrpc_server_abyss++',
    description : 'Xmlrpc-c Abyss XML-RPC server C++ library',
    version : meson.project_version(),
    requires_private : ['xmlrpc_abyss++', 'xmlrpc_server++', 'xmlrpc_server_abyss'],
    libraries : libxmlrpc_server_abysspp,
    install : true,
  )
endif

if get_option('cgi-server')
  libxmlrpc_server_cgipp = library(
    'xmlrpc_server_cgi++',
    sources : [
      'server_cgi.cpp',
    ],
    include_directories : [
      top_incdir,
      hdr_incdir,
    ],
    link_with : [
      libxmlrpc_serverpp,
    ],
    soversion : 8,
    version : '8.@0@'.format(version_minor),
    install : true,
  )
endif

libxmlrpc_packetsocket = library(
  'xmlrpc_packetsocket',
  sources : [
    'packetsocket.cpp',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : [
    libxmlrpcpp,
  ],
  soversion : 8,
  version : '8.@0@'.format(version_minor),
  install : true,
)

if build_xmlrpc_pstream
  libxmlrpc_server_pstreampp = library(
    'xmlrpc_server_pstream++',
    sources : [
      'server_pstream_conn.cpp',
      'server_pstream.cpp',
    ],
    include_directories : [
      top_incdir,
      hdr_incdir,
    ],
    link_with : [
      libxmlrpcpp,
      libxmlrpc_serverpp,
      libxmlrpc_packetsocket,
    ],
    soversion : 8,
    version : '8.@0@'.format(version_minor),
    install : true,
  )
  pkgg.generate(
    name : 'xmlrpc_server_pstream',
    description : 'Xmlrpc-c packet-stream XML-RPC server library',
    version : meson.project_version(),
    requires_private : ['xmlrpc++', 'xmlrpc_server++'],
    libraries : [libxmlrpc_server_pstreampp, libxmlrpc_packetsocket],
    install : true,
  )
endif

if build_client
  libxmlrpc_clientpp = library(
    'xmlrpc_client++',
    sources : [
      'client.cpp',
      'client_simple.cpp',
      'curl.cpp',
      'libwww.cpp',
      'wininet.cpp',
      'pstream.cpp',
    ],
    include_directories : [
      top_incdir,
      hdr_incdir,
      util_incdir,
    ],
    link_with : [
      libxmlrpcpp,
      libxmlrpc_client,
      libxmlrpc_packetsocket,
    ],
    soversion : 8,
    version : '8.@0@'.format(version_minor),
    install : true,
  )
endif
