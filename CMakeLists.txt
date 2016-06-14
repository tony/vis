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

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_C_COMPILER_ID} STREQUAL "AppleClang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c99 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -DNDEBUG -D_FORTIFY_SOURCE=2")
  if (APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_DARWIN_C_SOURCE")
  elseif(${CMAKE_SYSTEM_NAME} MATCHES FreeBSD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_BSD_SOURCE -D__BSD_VISIBLE=1")
  endif()
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_C_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
	endif()
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${vis_SOURCE_DIR}/cmake")

add_definitions(-DVERSION="0.0.0.1") 

set(BIN_DIR ${vis_SOURCE_DIR}/bin)

set(CURSES_NEED_NCURSESW TRUE)
find_package(NCursesw REQUIRED)
find_package(LibTermKey REQUIRED)

include_directories("./")

#file (GLOB vis_SOURCES *.c)
file(GLOB vis_SOURCES array.c buffer.c libutf.c main.c map.c register.c ring-buffer.c
	sam.c text.c text-motions.c text-objects.c text-regex.c text-util.c
	ui-curses.c view.c vis.c vis-lua.c vis-modes.c vis-motions.c
	vis-operators.c vis-prompt.c vis-text-objects.c)
    #list(REMOVE_ITEM vis_SOURCES vis_lua.c)


include_directories(${CURSES_INCLUDE_DIR} ${LIBTERMKEY_INCLUDE_DIR})

add_executable(vis ${vis_SOURCES} )

target_link_libraries(vis ${CURSES_LIBRARY} ${LIBTERMKEY_LIBRARY})

MESSAGE(STATUS "BIN_DIR: " ${BIN_DIR})
install(TARGETS vis RUNTIME DESTINATION ${BIN_DIR})
