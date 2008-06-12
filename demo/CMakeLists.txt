
# libharu demo files
SET(
  demos_NAMES
  	encoding_list
  	font_demo
  	image_demo
  	jpeg_demo
  	jpfont_demo
  	line_demo
  	link_annotation
  	outline_demo
  	png_demo
  	text_annotation
  	ttfont_demo
  	character_map
  	encryption
  	permission
  	slide_show_demo
  	ext_gstate_demo
)

SET(
  demos_with_grid_NAMES
  	text_demo
  	text_demo2
  	arc_demo
  	raw_image_demo
)

# we need to add some definitions for win 32
SET( DEMO_C_FLAGS )
IF( WIN32 AND NOT CYGWIN )
  SET( DEMO_C_FLAGS "-D__WIN32__" )
  IF( BUILD_SHARED_LIBS)
    SET( DEMO_C_FLAGS "${DEMO_C_FLAGS} -DHPDF_DLL" )
  ENDIF( BUILD_SHARED_LIBS)
endif( WIN32 AND NOT CYGWIN )

# create demos
FOREACH( demo ${demos_NAMES} )
  ADD_EXECUTABLE( ${demo} ${demo}.c )
  TARGET_LINK_LIBRARIES( ${demo} haru )
  IF( DEMO_C_FLAGS )
    SET_TARGET_PROPERTIES( ${demo} PROPERTIES COMPILE_FLAGS ${DEMO_C_FLAGS} )
    MESSAGE( "DEMO_C_FLAGS=${DEMO_C_FLAGS}" )
  ENDIF( DEMO_C_FLAGS )
ENDFOREACH( demo ${demo_NAMES} )
  
# some demos need grid_sheet.c compiled in
FOREACH( demo ${demos_with_grid_NAMES} )
  ADD_EXECUTABLE( ${demo} ${demo}.c grid_sheet.c )
  TARGET_LINK_LIBRARIES( ${demo} haru )
  IF( DEMO_C_FLAGS )
    SET_TARGET_PROPERTIES( ${demo} PROPERTIES COMPILE_FLAGS ${DEMO_C_FLAGS} )
  ENDIF( DEMO_C_FLAGS )
ENDFOREACH( demo ${demos_with_grid_NAMES} )
  
# the grid_sheet demo needs extra defines
ADD_EXECUTABLE( grid_sheet grid_sheet.c )
TARGET_LINK_LIBRARIES( grid_sheet haru )
SET_TARGET_PROPERTIES( grid_sheet PROPERTIES COMPILE_FLAGS "${DEMO_C_FLAGS} -DSTAND_ALONE" )

# install libary and demos
INSTALL(
  TARGETS
    ${demos_NAMES} ${demos_with_grid_NAMES} grid_sheet
  ARCHIVE DESTINATION 
    lib
  LIBRARY DESTINATION 
    lib
  RUNTIME DESTINATION
    bin
)