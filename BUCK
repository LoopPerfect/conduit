cxx_library(
  name = 'conduit',
  header_namespace =  'conduit',
  exported_headers = subdir_glob([
    ('include/conduit', '**/*.h'), 
    ('include/conduit', '**/*.hpp'), 
  ]), 
  exported_linker_flags = [
    '-lc++', 
  ], 
  licenses = [
    'LICENSE', 
  ], 
  visibility = [
    'PUBLIC', 
  ],
)
