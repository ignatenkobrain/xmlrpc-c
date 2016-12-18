config_h = configure_file(input : 'config.h.in',
                          output : 'config.h',
                          configuration : conf)

compat_links = [
  [ 'oldxmlrpc.h',         'xmlrpc.h'                   ],
  [ 'server.h',            'xmlrpc_server.h'            ],
  [ 'server_abyss.h',      'xmlrpc_abyss.h'             ],
  [ 'server_w32httpsys.h', 'xmlrpc_server_w32httpsys.h' ],
]

hdrs = [
  join_paths(meson.current_build_dir(), 'config.h'), # config_h,
  'inttypes.h',
  'c_util.h',
  'util.h',
  'base.h',
  'json.h',
  'abyss.h',
  'abyss_unixsock.h',
  'abyss_winsock.h',
  'server.h',
  'server_abyss.h',
  'server_w32httpsys.h',
  'oldxmlrpc.h',
]
if get_option('cplusplus')
  hdrs += [
    'oldcppwrapper.hpp',
    'girerr.hpp',
    'girmem.hpp',
    'base.hpp',
    'base64.hpp',
    'timeout.hpp',
    'xml.hpp',
    'registry.hpp',
    'server_abyss.hpp',
    'packetsocket.hpp',
    'server_pstream.hpp',
    'AbyssEnvironment.hpp',
    'AbyssServer.hpp',
    'abyss_reqhandler_xmlrpc.hpp',
    'AbyssChanSwitch.hpp',
    'AbyssChanSwitchUnix.hpp',
  ]
  compat_links += [
    ['oldcppwrapper.hpp', 'XmlRpcCpp.h'],
  ]
endif
if build_client
  hdrs += [
    'client.h',
    'transport.h',
    'client_global.h',
  ]
  compat_links += [
    ['client.h', 'xmlrpc_client.h'],
  ]
  if get_option('cplusplus')
    hdrs += [
      'client.hpp',
      'client_transport.hpp',
      'client_simple.hpp',
    ]
  endif
endif
if get_option('cgi-server')
  hdrs += [
    'server_cgi.h',
  ]
  compat_links += [
    ['server_cgi.h', 'xmlrpc_cgi.h'],
  ]
endif
if openssl.found()
  hdrs += [
    'openssl_thread.h',
  ]
endif

install_headers(hdrs, subdir : meson.project_name())
# Install old names of header files for backward compatibility
foreach compat_link : compat_links
  tgt = join_paths(get_option('prefix'), get_option('includedir'), meson.project_name(), compat_link[0])
  src = join_paths(get_option('prefix'), get_option('includedir'), compat_link[1])
  meson.add_install_script('lnsfr.sh', tgt, src)
endforeach
