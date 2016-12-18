nametab = custom_target(
  'nametab.h',
  output : 'nametab.h',
  command : gennmtab,
  capture : true,
)

if host_machine.endian() == 'big'
  xmltok_endian_flag = '-DXML_BYTE_ORDER=21'
else
  xmltok_endian_flag = '-DXML_BYTE_ORDER=12'
endif

libxmlrpc_xmltok = library(
  'xmlrpc_xmltok',
  sources : [
    'xmltok.c',
    'xmlrole.c',
    nametab,
  ],
  include_directories : [
    top_incdir,
    hdr_incdir,
    util_incdir,
  ],
  c_args : [xmltok_endian_flag],
  soversion : '3',
  version : '3.@0@'.format(version_minor),
  install : true,
)

xmltok_incdir = include_directories('.')
