util_incdir = include_directories('include')
util_casprintf_dep = declare_dependency(
  include_directories : util_incdir,
  sources : 'casprintf.c',
)
util_dep = declare_dependency(
  dependencies : util_casprintf_dep,
  sources : [
    'cmdline_parser.c',
    'getoptx.c',
    'string_parser.c',
    'stripcaseeq.c',
  ],
)
if get_option('cplusplus')
  util_cpp_dep = declare_dependency(
    dependencies : util_dep,
    sources : 'cmdline_parser_cpp.cpp',
  )
endif
