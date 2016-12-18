# FIXME: it's default already to 1 in xmlrpc_config.h
util_lock_pthread = ['lock_pthread.c']
# TODO: handle mscvrt.dll properly
util_lock_windows = [] # lock_windows.c

libxmlrpc_util = library(
  'xmlrpc_util',
  sources : [
    'asprintf.c',
    'base64.c',
    'error.c',
    'lock_platform.c',
    util_lock_pthread,
    util_lock_windows,
    'lock_none.c',
    'make_printable.c',
    'memblock.c',
    'mempool.c',
    'select.c',
    'sleep.c',
    'string_number.c',
    'time.c',
    'utf8.c',
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  soversion : 4,
  version : '4.@0@'.format(version_minor),
  install : true,
)

pkgg.generate(
  name : 'xmlrpc_util',
  description : 'Xmlrpc-c utility functions library',
  version : meson.project_version(),
  libraries : libxmlrpc_util,
  install : true,
)
