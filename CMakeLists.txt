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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wno-unused-variable -Wno-unused-parameter")
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

set(DEPS_INSTALL_DIR "${CMAKE_BINARY_DIR}/usr" CACHE PATH "Dependencies install directory.")
set(DEPS_BIN_DIR "${DEPS_INSTALL_DIR}/bin" CACHE PATH "Dependencies binary install directory.")
set(DEPS_LIB_DIR "${DEPS_INSTALL_DIR}/lib" CACHE PATH "Dependencies library install directory.")
set(DEPS_BUILD_DIR "${CMAKE_BINARY_DIR}/build" CACHE PATH "Dependencies build directory.")
set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downloads" CACHE PATH "Dependencies download directory.")

option(USE_EXISTING_SRC_DIR "Skip download of deps sources in case of existing source directory." OFF)

if(UNIX)
  find_program(MAKE_PRG NAMES gmake make)
  if(MAKE_PRG)
    execute_process(
      COMMAND "${MAKE_PRG}" --version
      OUTPUT_VARIABLE MAKE_VERSION_INFO)
    if(NOT "${OUTPUT_VARIABLE}" MATCHES ".*GNU.*")
      unset(MAKE_PRG)
    endif()
  endif()
  if(NOT MAKE_PRG)
    message(FATAL_ERROR "GNU Make is required to build the dependencies.")
  else()
    message(STATUS "Found GNU Make at ${MAKE_PRG}")
  endif()
endif()

# When using make, use the $(MAKE) variable to avoid warning about the job
# server.
if(CMAKE_GENERATOR MATCHES "Makefiles")
  set(MAKE_PRG "$(MAKE)")
endif()

if(CMAKE_C_COMPILER_ARG1)
  set(DEPS_C_COMPILER "${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ARG1}")
else()
  set(DEPS_C_COMPILER "${CMAKE_C_COMPILER}")
endif()
set(UNIBILIUM_URL https://github.com/mauke/unibilium/archive/v1.2.0.tar.gz)
set(UNIBILIUM_SHA256 623af1099515e673abfd3cae5f2fa808a09ca55dda1c65a7b5c9424eb304ead8)
set(LIBTERMKEY_URL http://www.leonerd.org.uk/code/libtermkey/libtermkey-0.18.tar.gz)
set(LIBTERMKEY_SHA256 239746de41c845af52bb3c14055558f743292dd6c24ac26c2d6567a5a6093926)
add_subdirectory(cmake/superbuild)
find_package(LibTermkey REQUIRED)
add_custom_target(superbuild
  cmake --build . --target libtermkey
  BYPRODUCTS ${LIBTERMKEY_LIBRARY} ${UNIBILIUM_LIBRARY}
  DEPENDS libtermkey
)

include_directories("./")

file(GLOB vis_SOURCES array.cc buffer.cc libutf.cc main.cc map.cc register.cc ring-buffer.cc
	sam.cc text.cc text-motions.cc text-objects.cc text-regex.cc text-util.cc
	ui-curses.cc view.cc vis.cc vis-lua.cc vis-modes.cc vis-motions.cc
	vis-operators.cc vis-prompt.cc vis-text-objects.cc)

configure_file (
"${PROJECT_SOURCE_DIR}/config.def.hh"
"${PROJECT_SOURCE_DIR}/config.hh"
)

include_directories(${CURSES_INCLUDE_DIR} ${LIBTERMKEY_INCLUDE_DIR} ${UNIBILIUM_INCLUDE_DIR})

MESSAGE(STATUS "CURSES_INCLUDE_DIR: " ${CURSES_INCLUDE_DIR})

add_executable(vis ${vis_SOURCES} )
set_property(TARGET vis PROPERTY CXX_STANDARD 11)
add_dependencies(vis libtermkey)

target_link_libraries(vis ${CURSES_LIBRARY} ${LIBTERMKEY_LIBRARY} ${UNIBILIUM_LIBRARY})

MESSAGE(STATUS "BIN_DIR: " ${BIN_DIR})
install(TARGETS vis RUNTIME DESTINATION ${BIN_DIR})
