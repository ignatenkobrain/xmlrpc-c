libcurl = dependency('libcurl')
if libcurl.version().version_compare('<7.16.0')
  xmlrpc_curl_cargs = ['-DNEED_CURL_TYPES_H']
else
  xmlrpc_curl_cargs = []
endif
xmlrpc_curl_transport = declare_dependency(
  include_directories : include_directories('.'),
  sources : [
    'xmlrpc_curl_transport.c',
    'curltransaction.c',
    'curlmulti.c',
  ],
  compile_args : xmlrpc_curl_cargs,
  dependencies : libcurl,
)
