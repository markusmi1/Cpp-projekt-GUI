# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtProov_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtProov_autogen.dir\\ParseCache.txt"
  "QtProov_autogen"
  )
endif()
