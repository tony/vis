#---------------------------------------------------------------------------
# https://github.com/InsightSoftwareConsortium/ITKExamples/blob/master/LICENSE
# https://github.com/InsightSoftwareConsortium/ITKExamples/blob/a91dee/Superbuild/External-Python.cmake
# Changes as of 2016-06-09
# - Switch to python 3.5.1
# Get and build C Python

set(_python_version "3.5.1")
set(_python_SOURCE_DIR "${CMAKE_BINARY_DIR}/Python-${_python_version}")

if(MSVC)
  list(APPEND EXTERNAL_PROJECT_OPTIONAL_ARGS
    PATCH_COMMAND ${CMAKE_COMMAND}
      -DPYTHON_SRC_DIR:PATH=${_python_SOURCE_DIR}
      -P ${CMAKE_CURRENT_LIST_DIR}/PythonPatch.cmake
    )
endif()

ExternalProject_Add(Python-source
  URL "https://www.python.org/ftp/python/${_python_version}/Python-${_python_version}.tgz"
  URL_MD5 "be78e48cdfc1a7ad90efff146dce6cfe"
  DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}
  SOURCE_DIR ${_python_SOURCE_DIR}
  ${EXTERNAL_PROJECT_OPTIONAL_ARGS}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  )

if(APPLE)
  list(APPEND EXTERNAL_PROJECT_OPTIONAL_CMAKE_ARGS
    -DCMAKE_BUILD_WITH_INSTALL_RPATH:BOOL=ON
    )
endif()

set(EXTERNAL_PROJECT_OPTIONAL_CMAKE_CACHE_ARGS)

# Force Python build to "Release".
if(CMAKE_CONFIGURATION_TYPES)
  set(SAVED_CMAKE_CFG_INTDIR ${CMAKE_CFG_INTDIR})
  set(CMAKE_CFG_INTDIR "Release")
else()
  list(APPEND EXTERNAL_PROJECT_OPTIONAL_CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=Release)
endif()

ExternalProject_Add(Python
  GIT_REPOSITORY "${git_protocol}://github.com/python-cmake-buildsystem/python-cmake-buildsystem.git"
  GIT_TAG "846ae61"
  SOURCE_DIR ${CMAKE_BINARY_DIR}/Python
  BINARY_DIR Python-build
  CMAKE_CACHE_ARGS
    -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
    #-DCMAKE_CXX_FLAGS:STRING=${ep_common_cxx_flags} # Not used
    -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/Python-install
    #-DBUILD_TESTING:BOOL=OFF
    -DBUILD_LIBPYTHON_SHARED:BOOL=ON
    -DUSE_SYSTEM_LIBRARIES:BOOL=OFF
    -DZLIB_ROOT:FILEPATH=${ZLIB_ROOT}
    -DZLIB_INCLUDE_DIR:PATH=${ZLIB_INCLUDE_DIR}
    -DZLIB_LIBRARY:FILEPATH=${ZLIB_LIBRARY}
    -DSRC_DIR:PATH=${_python_SOURCE_DIR}
    -DDOWNLOAD_SOURCES:BOOL=OFF
    -DINSTALL_WINDOWS_TRADITIONAL:BOOL=OFF
    ${EXTERNAL_PROJECT_OPTIONAL_CMAKE_CACHE_ARGS}
  ${EXTERNAL_PROJECT_OPTIONAL_CMAKE_ARGS}
  DEPENDS Python-source zlib
  UPDATE_COMMAND ""
  )
set(_python_DIR ${CMAKE_CURRENT_BINARY_DIR}/Python-install)

if(UNIX)
  set(_python_IMPORT_SUFFIX so)
  if(APPLE)
    set(_python_IMPORT_SUFFIX dylib)
  endif()
  set(PYTHON_INCLUDE_DIR "${_python_DIR}/include/python3.5" CACHE PATH "Python include dir" FORCE)

  set(PYTHON_LIBRARY "${_python_DIR}/lib/libpython3.5m.${_python_IMPORT_SUFFIX}" CACHE FILEPATH "Python library" FORCE)
  set(PYTHON_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/Python-build/bin/python CACHE FILEPATH "Python executable" FORCE)
  set(PY_SITE_PACKAGES_PATH "${_python_DIR}/lib/python3.5/site-packages" CACHE PATH "Python site-packages path" FORCE)
elseif(WIN32)
  set(PYTHON_INCLUDE_DIR "${_python_DIR}/include" CACHE PATH "Python include dir" FORCE)
  set(PYTHON_LIBRARY "${_python_DIR}/libs/python35.lib" CACHE FILEPATH "Python library" FORCE)
  set(PYTHON_EXECUTABLE "${CMAKE_CURRENT_BINARY_DIR}/Python-install/bin/python.exe" CACHE FILEPATH "Python executable" FORCE)
  set(PY_SITE_PACKAGES_PATH "${_python_DIR}/Lib/site-packages" CACHE PATH "Python site-packages path" FORCE)
else()
  message(FATAL_ERROR "Unknown system !")
endif()
