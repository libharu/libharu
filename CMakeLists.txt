# CMakeLists.txt
#
# Copyright (C) 2008  Werner Smekal
#
# Process this file with cmake to produce Makefiles or project files
# for your specific compiler tool set
#
# TODO:
# - shared and static library
# - packaging
# - devpackage
# =======================================================================
# libharu project
# =======================================================================
project(libharu C)

# determine compiler name
set(COMPILER_LABEL "unknown")
if(CMAKE_COMPILER_IS_GNUCC)
  set(COMPILER_LABEL "gcc")
endif(CMAKE_COMPILER_IS_GNUCC)
if(MSVC)
  set(COMPILER_LABEL "vc")
endif(MSVC)

# information about libharu
set(LIBHARU_MAJOR 2)
set(LIBHARU_MINOR 2)
set(LIBHARU_PATCH 0)
set(LIBHARU_VERSION ${LIBHARU_MAJOR}.${LIBHARU_MINOR}.${LIBHARU_PATCH})
set(LIBHARU_DESCRIPTION "libHaru is a free, cross platform, open source library for generating PDF files.")
set(LIBHARU_PACKAGE_NAME "libHaru-${LIBHARU_VERSION}-${COMPILER_LABEL}")

# we want cmake version 2.4.8 at least
cmake_minimum_required(VERSION 2.4.8 FATAL_ERROR)

# Location where the haru cmake build system first looks for cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# set library name, msvc does not append 'lib' automatically
if(MSVC)
 set(LIBHARU_NAME lib)
 set(CMAKE_DEBUG_POSTFIX "d")
endif(MSVC)
set(LIBHARU_NAME ${LIBHARU_NAME}hpdf)
set(LIBHARU_NAME_STATIC ${LIBHARU_NAME}s)

# =======================================================================
# command line options
# =======================================================================
option(LIBHARU_SHARED "Build shared lib" YES)
option(LIBHARU_STATIC "Build static lib" YES)
option(LIBHARU_EXAMPLES "Build libharu examples" NO)
option(DEVPAK "Create DevPackage" NO)

if(DEVPAK AND NOT WIN32)
  message( STATUS "DevPackage only available for Win32. Set DEVPAK to OFF." )
  set(DEVPAK OFF)
endif(DEVPAK AND NOT WIN32)
if(DEVPAK AND LIBHARU_EXAMPLES)
  message( STATUS "Examples are not build for DevPackage. Set LIBHARU_EXAMPLES to OFF." )
  set(LIBHARU_EXAMPLES OFF)
endif(DEVPAK AND LIBHARU_EXAMPLES)

if(BUILD_SHARED_LIBS)
  set(LIBHARU_SHARED ON)
endif(BUILD_SHARED_LIBS)

# =======================================================================
# look for headers and libraries
# =======================================================================
include(haru)
include(summary)

# check zlib availibility
find_package(ZLIB)
if(ZLIB_FOUND)
  set(HAVE_LIBZ ON)
  include_directories(${ZLIB_INCLUDE_DIR})
  set(ADDITIONAL_LIBRARIES ${ZLIB_LIBRARIES})
else(ZLIB_FOUND)
  set(HPDF_NOZLIB ON)  
endif(ZLIB_FOUND)
  
# check png availibility
find_package(PNG)
if(PNG_FOUND)
  set(HAVE_LIBPNG ON)
  include_directories(${PNG_INCLUDE_DIR})
  add_definitions(${PNG_DEFINITIONS})
  set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} ${PNG_LIBRARIES})
else(PNG_FOUND)
  set(HPDF_NOPNGLIB ON)  
endif(PNG_FOUND)

# =======================================================================
# configure header files, add compiler flags
# =======================================================================
# add definitions and directories to include
#if(CMAKE_COMPILER_IS_GNUCC)
#  add_definitions("-Wall")
#endif(CMAKE_COMPILER_IS_GNUCC)
if(MSVC_VERSION GREATER 1399)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
endif(MSVC_VERSION GREATER 1399)
include_directories(${CMAKE_SOURCE_DIR}/include)

# create hpdf_config.h
configure_file(
  ${CMAKE_SOURCE_DIR}/include/hpdf_config.h.cmake
  ${CMAKE_BINARY_DIR}/include/hpdf_config.h
)
include_directories(${CMAKE_BINARY_DIR}/include)

# create DevPackage file
if(DEVPAK)
  configure_file(
    ${CMAKE_SOURCE_DIR}/libharu.DevPackage.cmake
    ${CMAKE_BINARY_DIR}/libharu.DevPackage
  )
endif(DEVPAK)
# =======================================================================
# create library and demos
# =======================================================================
add_subdirectory(src)
add_subdirectory(demo)

# =======================================================================
# installation configuration
# =======================================================================
set(
  haru_HDRS
    include/hpdf.h
    include/hpdf_types.h
    include/hpdf_consts.h 
    include/hpdf_version.h
    include/hpdf_annotation.h
    include/hpdf_catalog.h
    include/hpdf_conf.h
    include/hpdf_destination.h
    include/hpdf_doc.h
    include/hpdf_encoder.h
    include/hpdf_encrypt.h
    include/hpdf_encryptdict.h
    include/hpdf_error.h
    include/hpdf_ext_gstate.h
    include/hpdf_font.h
    include/hpdf_fontdef.h
    include/hpdf_gstate.h
    include/hpdf_image.h
    include/hpdf_info.h
    include/hpdf_list.h
    include/hpdf_mmgr.h
    include/hpdf_objects.h
    include/hpdf_outline.h
    include/hpdf_pages.h
    include/hpdf_page_label.h
    include/hpdf_streams.h
    include/hpdf_u3d.h
    include/hpdf_utils.h
    include/hpdf_pdfa.h
    include/hpdf_3dmeasure.h
    include/hpdf_exdata.h
    ${CMAKE_BINARY_DIR}/include/hpdf_config.h
)

# install header files
install(FILES ${haru_HDRS} DESTINATION include)

# install various files
install(FILES README CHANGES INSTALL DESTINATION .)
install(DIRECTORY doc DESTINATION .)
if(NOT DEVPAK)
  install(DIRECTORY if DESTINATION .)
endif(NOT DEVPAK)
if(DEVPAK)
  install(FILES ${CMAKE_BINARY_DIR}/libharu.DevPackage DESTINATION .)
endif(DEVPAK)
# =======================================================================
# print out some information
# =======================================================================
summary()

# =======================================================================
# packing stuff
# =======================================================================
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${LIBHARU_DESCRIPTION})
set(CPACK_PACKAGE_VENDOR "Werner Smekal")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set(CPACK_PACKAGE_VERSION_MAJOR "${LIBHARU_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${LIBHARU_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${LIBHARU_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "libHaru-${LIBHARU_VERSION}-${COMPILER_LABEL}")

set(CPACK_STRIP_FILES ON)

if(WIN32)
  set(CPACK_GENERATOR ZIP)
else(WIN32)
  set(CPACK_GENERATOR TGZ)
endif(WIN32)

INCLUDE( CPack )
