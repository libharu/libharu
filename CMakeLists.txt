cmake_minimum_required(VERSION 3.10)

project(libharu
    VERSION 2.4.0
    DESCRIPTION "libHaru is a free, cross platform, open source library for generating PDF files."
    LANGUAGES C)

# determine compiler name
set(COMPILER_LABEL "unknown")
if(CMAKE_COMPILER_IS_GNUCC)
  set(COMPILER_LABEL "gcc")
endif(CMAKE_COMPILER_IS_GNUCC)
if(MSVC)
  set(COMPILER_LABEL "vc")
endif(MSVC)

# Location where the haru cmake build system first looks for cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# =======================================================================
# command line options
# =======================================================================
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" ON)
option(LIBHPDF_EXAMPLES "Build libharu examples" NO)
option(LIBHPDF_DEBUG "Enable HPDF Debug")
option(LIBHPDF_DEBUG_TRACE "Enable HPDF Debug trace")

# Enable exceptions on linux if required
# (eg if you are using libharu in a C++ environment,
# and you want your error-callback to throw an exception,
# you will need to enable this for the exception to be
# able to throw through the libharu callstack).
if (CMAKE_COMPILER_IS_GNUCC OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"))
   option (LIBHPDF_ENABLE_EXCEPTIONS "Enable exceptions" NO)
   if (LIBHPDF_ENABLE_EXCEPTIONS)
      set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions")
   endif (LIBHPDF_ENABLE_EXCEPTIONS)
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# =======================================================================
# look for headers and libraries
# =======================================================================
include(haru)
include(summary)

# check zlib availability
find_package(ZLIB)
  
# check png availability
find_package(PNG)

# Find math library, sometimes needs to be explicitly linked against
find_library(M_LIB m)

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

# Just set to 1, we'll assume they are always available.
# If not, then someone will have to add some tests in here to correctly determine
# the headers existence.
set (LIBHPDF_STDC_HEADERS 1)

# support all of the different variations of LIBPNG defines in HARU
set (LIBHPDF_HAVE_LIBPNG ${PNG_FOUND})

# support different zlib defines
set (LIBHPDF_HAVE_LIBZ ${ZLIB_FOUND})

# create hpdf_config.h
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/hpdf_config.h.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/include/hpdf_config.h
)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

# =======================================================================
# create library and demos
# =======================================================================
add_subdirectory(src)
if(LIBHPDF_EXAMPLES)
    add_subdirectory(demo)
endif(LIBHPDF_EXAMPLES)

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
    ${CMAKE_CURRENT_BINARY_DIR}/include/hpdf_config.h
)

# install header files
install(FILES ${haru_HDRS} DESTINATION include)

# install various files
install(FILES README.md CHANGES INSTALL DESTINATION .)
install(DIRECTORY if DESTINATION .)

# =======================================================================
# print out some information
# =======================================================================
summary()
