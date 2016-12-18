abyss_deps = [socket]
if host_machine.system() == 'windows'
  abyss_socket = 'socket_win.c'
  abyss_thread = 'thread_windows.c'
  abyss_deps += [threads]
else
  abyss_socket = ['socket_unix.c']
  if openssl.found()
    abyss_socket += ['socket_openssl.c']
    abyss_deps += [openssl]
  endif
  abyss_socket += ['sockutil.c']

  if get_option('abyss-threads')
    abyss_thread = 'thread_pthread.c'
    abyss_deps += [threads]
  else
    abyss_thread = 'thread_fork.c'
  endif
endif

libxmlrpc_abyss = library(
  'xmlrpc_abyss',
  sources : [
    'channel.c',
    'chanswitch.c',
    'conf.c',
    'conn.c',
    'data.c',
    'date.c',
    'file.c',
    'handler.c',
    'http.c',
    'init.c',
    'response.c',
    'server.c',
    'session.c',
    'sessionReadRequest.c',
    'socket.c',
    abyss_socket,
    'token.c',
    abyss_thread,
    'trace.c',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : [
    libxmlrpc_util,
  ],
  dependencies : abyss_deps,
  soversion : 3,
  version : '3.@0@'.format(version_minor),
  install : true,
)

pkgg.generate(
  name : 'xmlrpc_abyss',
  description : 'Xmlrpc-c Abyss HTTP C library',
  version : meson.project_version(),
  libraries : libxmlrpc_abyss,
  requires_private : 'xmlrpc_util',
  install : true,
)
