cxx_library(
  name = 'conduit',
  visibility = ['PUBLIC'],
  header_namespace= '',
  compiler_flags = [
    "stdlib=libc++",
    "-fcoroutine-ts",
    "-std=c++17"
  ],
  exported_linker_flags = [
    '-lc++'
  ], 
  exported_headers = subdir_glob([
    ("include", "**/*.hpp")
  ])
)
