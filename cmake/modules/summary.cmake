# cmake/modules/summary.cmake
#
# Copyright (C) 2008  Werner Smekal
#

# Macro for outputting all the most important CMake variables for haru

MACRO( summary )
SET(_output_results "
Summary of CMake build system results for the haru library

Install location variables which can be set by the user:
CMAKE_INSTALL_PREFIX:      ${CMAKE_INSTALL_PREFIX}
CMAKE_INSTALL_EXEC_PREFIX  ${CMAKE_INSTALL_EXEC_PREFIX}
CMAKE_INSTALL_BINDIR 	   ${CMAKE_INSTALL_BINDIR}
CMAKE_INSTALL_DATADIR 	   ${CMAKE_INSTALL_DATADIR}
CMAKE_INSTALL_LIBDIR 	   ${CMAKE_INSTALL_LIBDIR}
CMAKE_INSTALL_INCLUDEDIR   ${CMAKE_INSTALL_INCLUDEDIR}
CMAKE_INSTALL_INFODIR 	   ${CMAKE_INSTALL_INFODIR}
CMAKE_INSTALL_MANDIR 	   ${CMAKE_INSTALL_MANDIR}

Other important CMake variables:

CMAKE_SYSTEM_NAME:	${CMAKE_SYSTEM_NAME}
UNIX:			${UNIX}
WIN32:			${WIN32}
APPLE:			${APPLE}
MSVC:			${MSVC}	(MSVC_VERSION:	${MSVC_VERSION})
MINGW:			${MINGW}
MSYS:			${MSYS}
CYGWIN:			${CYGWIN}
BORLAND:		${BORLAND}
WATCOM:		  ${WATCOM}

CMAKE_BUILD_TYPE:	${CMAKE_BUILD_TYPE}
CMAKE_C_COMPILER CMAKE_C_FLAGS:			${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS}

Library options:
BUILD_SHARED_LIBS:	${BUILD_SHARED_LIBS}

Optional libraries:
HAVE_LIBZ:		${HAVE_LIBZ}
HAVE_LIBPNG:		${HAVE_LIBPNG}
")
MESSAGE( "${_output_results}" )
ENDMACRO( summary )
