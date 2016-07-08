cmake_minimum_required( VERSION 2.8.6 )

if( COMMAND CMAKE_POLICY )
  cmake_policy( SET CMP0003 NEW )
endif( COMMAND CMAKE_POLICY )

project( superbuild )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../superbuild")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

include(${CMAKE_SOURCE_DIR}/cmake/superbuild/superbuild.cmake )
