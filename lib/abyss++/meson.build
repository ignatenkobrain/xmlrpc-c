if host_machine.system() == 'windows'
  abysspp_chan_switch = 'AbyssChanSwitchWin.cpp'
else
  abysspp_chan_switch = ['AbyssChanSwitchUnix.cpp']
  if openssl.found()
    abysspp_chan_switch += ['AbyssChanSwitchOpenSsl.cpp']
  endif
endif

libxmlrpc_abysspp = library(
  'xmlrpc_abyss++',
  sources : [
    'AbyssServer.cpp',
    'AbyssChanSwitch.cpp',
    'AbyssEnvironment.cpp',
    abysspp_chan_switch,
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  link_with : [
    libxmlrpc_abyss,
    libxmlrpc_utilpp,
  ],
  dependencies : [
    socket,
  ],
  soversion : 8,
  version : '8.@0@'.format(version_minor),
  install : true,
)

pkgg.generate(
  name : 'xmlrpc_abyss++',
  description : 'Xmlrpc-c Abyss HTTP C++ library',
  version : meson.project_version(),
  requires : ['xmlrpc_abyss', 'xmlrpc_util++'],
  libraries : libxmlrpc_abysspp,
  install : true,
)
