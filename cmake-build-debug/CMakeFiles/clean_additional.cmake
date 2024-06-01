# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "5chess_autogen"
  "CMakeFiles\\5chess_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\5chess_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\libcurl.dll_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\libcurl.dll_autogen.dir\\ParseCache.txt"
  "libcurl.dll_autogen"
  )
endif()
