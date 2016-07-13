#---------------------------------------------------------------------------
# Get and build zlib. This is required by the Python build and it is re-used
# by ITK and VTK.

ExternalProject_Add(zlib
  GIT_REPOSITORY "${git_protocol}://github.com/tony/zlib.git"
  GIT_TAG "freebsd-support"
  SOURCE_DIR zlib
  BINARY_DIR zlib-build
  INSTALL_DIR zlib-install
  CMAKE_CACHE_ARGS
    ## CXX should not be needed, but it a cmake default test
    -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
    -DZLIB_MANGLE_PREFIX:STRING=vis_zlib_
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  UPDATE_COMMAND ""
  )
set(zlib_DIR "${CMAKE_CURRENT_BINARY_DIR}/zlib-install" CACHE PATH "zlib dir" FORCE)
set(ZLIB_ROOT ${zlib_DIR} CACHE PATH "zlib root" FORCE)
set(ZLIB_INCLUDE_DIR ${zlib_DIR}/include CACHE PATH "zlib include dir" FORCE)
if(WIN32)
  set(ZLIB_LIBRARY ${zlib_DIR}/lib/zlib.lib CACHE FILEPATH "zlib library" FORCE)
else()
  set(ZLIB_LIBRARY ${zlib_DIR}/lib/libzlib.a CACHE FILEPATH "zlib library" FORCE)
endif()
