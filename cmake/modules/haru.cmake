# cmake/modules/haru.cmake
#
# Copyright (C) 2008  Werner Smekal
#
# check if headers exist
# Need these modules to do subsequent checks.
include(CheckIncludeFiles)

# =======================================================================
# check header availability
# =======================================================================
# check if header file exists
check_include_files(dlfcn.h HAVE_DLFCN_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)


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
