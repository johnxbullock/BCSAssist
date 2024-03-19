# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\clipboardlistener_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\clipboardlistener_autogen.dir\\ParseCache.txt"
  "clipboardlistener_autogen"
  )
endif()
