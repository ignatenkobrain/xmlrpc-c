project('xmlrpc-c', 'c',
        version : '1.47.99',
        default_options : [
          'b_asneeded=true',
          'b_lundef=true',
          'warning_level=1',
        ],
        meson_version : '>=0.36.0')

version_array = meson.project_version().split('.')
version_major = version_array[0].to_int()
version_minor = version_array[1].to_int()
version_point = version_array[2].to_int()

# version.h
version_conf = configuration_data()
version_conf.set_quoted('XMLRPC_C_VERSION', meson.project_version())
version_conf.set('XMLRPC_VERSION_MAJOR', version_major)
version_conf.set('XMLRPC_VERSION_MINOR', version_minor)
version_conf.set('XMLRPC_VERSION_POINT', version_point)
configure_file(output : 'version.h', configuration : version_conf)

if get_option('wininet-client') or get_option('libwww-client')
  error('only curl-client is implemented yet')
endif

if get_option('cplusplus')
  add_languages('cpp')
endif

cc = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')

optflags = [
  '-Wno-uninitialized',
  '-Wundef',
  '-Wno-unknown-pragmas',
]
cflags = [
  '-Wmissing-declarations',
  '-Wstrict-prototypes',
  '-Wmissing-prototypes',
  '-Wimplicit',
] + optflags
cxxflags = [
  '-Wsynth',
] + optflags
foreach cflag : cflags
  if cc.has_argument(cflag)
    add_project_arguments(cflag, language : 'c')
  endif
endforeach
foreach cxxflag : cxxflags
  if cxx.has_argument(cxxflag)
    add_project_arguments(cxxflag, language : 'cpp')
  endif
endforeach

pkgg = import('pkgconfig')

if not cc.has_function('vsnprintf')
  error('your C library does not provide vsnprintf')
endif
if not cc.has_header('stdarg.h')
  error('stdarg.h is required to build this library')
endif

conf = configuration_data()

check_headers = [
  'wchar.h',
  'sys/filio.h',  # Needed by Abyss on Solaris
  'sys/ioctl.h',  # Needed by Abyss on Solaris
  'sys/select.h',
]
check_functions = [
  'wcsncmp',      # Unicode function needed by test suites
  'setgroups',    # CygWin doesn't provide setgroups
  'asprintf',
  'setenv',
  'strtoll',
  'strtoull',
  'strtoq',
  'strtouq',
  '__strtoll',
  '__strtoull',
  '_strtoui64',
  'pselect',      # uclib doesn't have pselect
  'gettimeofday', # Windows doesn't have gettimeofday
  'localtime_r',  # Windows doesn't have localtime_r
  'gmtime_r',     # Windows doesn't have gmtime_r
  'strcasecmp',   # Windows doesn't have strcasecmp
  'stricmp',
  '_stricmp',
]

foreach hdr : check_headers
  if cc.has_header(hdr)
    conf.set('HAVE_@0@_DEFINE'.format(hdr.to_upper().underscorify()), 1)
  else
    conf.set('HAVE_@0@_DEFINE'.format(hdr.to_upper().underscorify()), 0)
  endif
endforeach
foreach func : check_functions
  if cc.has_function(func)
    conf.set('HAVE_@0@_DEFINE'.format(func.to_upper()), 1)
  else
    conf.set('HAVE_@0@_DEFINE'.format(func.to_upper()), 0)
  endif
endforeach

if not cc.compiles('''
#include <stdarg.h>

int
main ()
{
  va_list list1, list2;
  list1 = list2;
  return 0;
}
               ''')
  conf.set('VA_LIST_IS_ARRAY_DEFINE', 1)
else
  conf.set('VA_LIST_IS_ARRAY_DEFINE', 0)
endif

if cc.compiles('int x __attribute__((__unused__));')
  conf.set('ATTR_UNUSED', '__attribute__((__unused__))')
else
  conf.set('ATTR_UNUSED', '')
endif

if host_machine.system() == 'windows'
  conf.set('DIRECTORY_SEPARATOR', '\\')
else
  conf.set('DIRECTORY_SEPARATOR', '/')
endif

openssl = dependency('openssl', required : false)
if openssl.found()
  conf.set('HAVE_OPENSSL_DEFINE', 1)
else
  conf.set('HAVE_OPENSSL_DEFINE', 0)
endif

if get_option('libwww-ssl')
  conf.set('HAVE_LIBWWW_SSL_DEFINE', 1)
else
  conf.set('HAVE_LIBWWW_SSL_DEFINE', 0)
endif

configure_file(input : 'xmlrpc_config.h.in', output : 'xmlrpc_config.h', configuration : conf)

ncurses = cc.find_library('ncurses', required : false)
readline = cc.find_library('readline', required : false)

build_xmlrpc_pstream = false

if not get_option('wininet-client') and not get_option('curl-client') and not get_option('libwww-client')
  build_client = false
  build_tools = false
  message('We are not building any client XML transport, therefore WE WILL NOT BUILD THE CLIENT LIBRARY')
else
  build_client = true
  if ncurses.found() and readline.found()
    build_xmlrpc_pstream = true
  endif
  build_tools = true
  # transport_config.h
  transport_conf = configuration_data()
  if get_option('wininet-client')
    transport_conf.set('MUST_BUILD_WININET_CLIENT', 1)
    transport_conf.set_quoted('XMLRPC_DEFAULT_TRANSPORT', 'wininet')
  else
    transport_conf.set('MUST_BUILD_WININET_CLIENT', 0)
  endif
  if get_option('curl-client')
    transport_conf.set('MUST_BUILD_CURL_CLIENT', 1)
    transport_conf.set_quoted('XMLRPC_DEFAULT_TRANSPORT', 'curl')
  else
    transport_conf.set('MUST_BUILD_CURL_CLIENT', 0)
  endif
  if get_option('libwww-client')
    transport_conf.set('MUST_BUILD_LIBWWW_CLIENT', 1)
    transport_conf.set_quoted('XMLRPC_DEFAULT_TRANSPORT', 'libwww')
  else
    transport_conf.set('MUST_BUILD_LIBWWW_CLIENT', 0)
  endif
  configure_file(input : 'transport_config.h.in', output : 'transport_config.h', configuration : transport_conf)
endif

threads = dependency('threads')
socket = cc.find_library('socket', required : false)

if get_option('libxml2-backend')
  libxml2 = dependency('libxml-2.0')
endif

top_incdir = include_directories('.')

subdir('include')
subdir('lib')
subdir('src')
if build_tools
  subdir('tools')
endif

install_data('xmlrpc-c-config', install_dir : get_option('bindir'))
