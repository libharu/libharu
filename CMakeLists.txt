###
### Process this file with cmake to produce Makefiles or project files
### for your specific compiler tool set
###
# Copyright (C) 2008 Werner Smekal
#

PROJECT( libharu C )

SET( PACKAGE libharu )

CMAKE_MINIMUM_REQUIRED( VERSION 2.4.8 FATAL_ERROR )

# Location where the haru cmake build system first looks for cmake modules
SET( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules )

# Configure haru component variables....
INCLUDE( haru )
INCLUDE( summary )

# check zlib availibility
FIND_PACKAGE( ZLIB )
IF( ZLIB_FOUND )
  SET( HAVE_LIBZ ON )
  INCLUDE_DIRECTORIES( ${ZLIB_INCLUDE_DIR} )
  SET( ADDITIONAL_LIBRARIES ${ZLIB_LIBRARIES} )
  
  # check png availibility
  FIND_PACKAGE( PNG )
  IF( PNG_FOUND )
    SET( HAVE_LIBPNG ON )
    INCLUDE_DIRECTORIES( ${PNG_INCLUDE_DIR} )
    ADD_DEFINITIONS( ${PNG_DEFINITIONS} )
    SET( ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} ${PNG_LIBRARIES} )
  ELSE( PNG_FOUND )
    SET( HPDF_NOPNGLIB ON )  
  ENDIF( PNG_FOUND )
ELSE( ZLIB_FOUND )
  SET( HPDF_NOZLIB ON )  
  SET( HPDF_NOPNGLIB ON )  
ENDIF( ZLIB_FOUND )
MESSAGE( "Additional libraries: ${ADDITIONAL_LIBRARIES}" )

# add definitions and directories to include
ADD_DEFINITIONS( -Wall )
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/include )

# create hpdf_config.h
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/include/hpdf_config.h.cmake
  ${CMAKE_BINARY_DIR}/include/hpdf_config.h
)
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR}/include )

# create library and demos
ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( demo )

# libharu headers
SET(
  haru_HDRS
    include/hpdf.h
    include/hpdf_encoder.h
    include/hpdf_image.h
    include/hpdf_streams.h    
    include/hpdf_annotation.h
    include/hpdf_encrypt.h
    include/hpdf_info.h
    include/hpdf_types.h
    include/hpdf_catalog.h
    include/hpdf_encryptdict.h
    include/hpdf_list.h
    include/hpdf_u3d.h
    include/hpdf_conf.h
    include/hpdf_error.h
    include/hpdf_mmgr.h
    include/hpdf_utils.h
    include/hpdf_ext_gstate.h  
    include/hpdf_objects.h    
    include/hpdf_version.h
    include/hpdf_consts.h 
    include/hpdf_font.h   
    include/hpdf_outline.h 
    include/hpdf_destination.h 
    include/hpdf_fontdef.h   
    include/hpdf_page_label.h
    include/hpdf_doc.h       
    include/hpdf_gstate.h    
    include/hpdf_pages.h
)

# install header files
INSTALL(
  FILES
    ${haru_HDRS}
  DESTINATION
    include
)

summary()
