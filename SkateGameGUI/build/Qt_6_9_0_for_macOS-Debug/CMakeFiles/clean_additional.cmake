# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/SkateGameGUI_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/SkateGameGUI_autogen.dir/ParseCache.txt"
  "SkateGameGUI_autogen"
  )
endif()
