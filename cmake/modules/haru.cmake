# cmake/modules/haru.cmake
#
# Copyright (C) 2008  Werner Smekal
#
# check if headers exist
# Need these modules to do subsequent checks.
include(CheckIncludeFiles)

# =======================================================================
# additional library support
# =======================================================================
# On windows systems the math library is not separated so do not specify
# it unless you are on a non-windows system.
if(NOT WIN32)
  find_library(MATH_LIB NAMES m PATHS /usr/local/lib /usr/lib)
  if(NOT MATH_LIB)
    message(FATAL_ERROR "Cannot find required math library")
  endif(NOT MATH_LIB)
else(NOT WIN32)
  set(MATH_LIB)
endif(NOT WIN32)
