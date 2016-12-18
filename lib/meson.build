subdir('util')
subdir('libutil')
if get_option('cplusplus')
  subdir('libutil++')
endif
if get_option('abyss-server')
  subdir('abyss')
  if get_option('cplusplus')
    subdir('abyss++')
  endif
endif
if get_option('wininet-client')
  subdir('wininet_transport')
endif
if get_option('curl-client')
  subdir('curl_transport')
endif
if get_option('libwww-client')
  subdir('libwww_transport')
endif
if not get_option('libxml2-backend')
  subdir('expat')
endif

if openssl.found()
  subdir('openssl')
endif
