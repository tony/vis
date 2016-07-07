cmake_minimum_required(VERSION 2.8.12)
foreach(p
  CMP0025
  CMP0042
  CMP0046
  CMP0054
  )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

project(vis)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -pedantic -std=c++14")
if (APPLE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DARWIN_C_SOURCE")
elseif(${CMAKE_SYSTEM_NAME} MATCHES FreeBSD)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_BSD_SOURCE -D__BSD_VISIBLE=1")
endif()


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${vis_SOURCE_DIR}/cmake")

add_definitions(-DVERSION="0.0.0.1") 

set(BIN_DIR ${vis_SOURCE_DIR}/bin)

set(CURSES_NEED_NCURSESW TRUE)
find_package(NCursesw REQUIRED)
find_package(LibTermkey REQUIRED)

include_directories("./")

file(GLOB vis_SOURCES array.c buffer.c libutf.c main.cc map.c register.c ring-buffer.c
	sam.c text.c text-motions.c text-objects.c text-regex.c text-util.c
	ui-curses.c view.c vis.c vis-lua.c vis-modes.c vis-motions.c
	vis-operators.c vis-prompt.c vis-text-objects.c)

#if (NOT EXISTS "${PROJECT_SOURCE_DIR}/config.hh")
  configure_file (
    "${PROJECT_SOURCE_DIR}/config.def.hh"
    "${PROJECT_SOURCE_DIR}/config.hh"
  )
#endif()

include_directories(${CURSES_INCLUDE_DIR} ${LIBTERMKEY_INCLUDE_DIR})

add_executable(vis ${vis_SOURCES} )

target_link_libraries(vis ${CURSES_LIBRARY} ${LIBTERMKEY_LIBRARY})

MESSAGE(STATUS "BIN_DIR: " ${BIN_DIR})
install(TARGETS vis RUNTIME DESTINATION ${BIN_DIR})
