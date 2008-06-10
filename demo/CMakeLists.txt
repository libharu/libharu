
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


# create demos
FOREACH( demo ${demos_NAMES} )
  ADD_EXECUTABLE( ${demo} ${demo}.c )
ENDFOREACH( demo ${demo_NAMES} )
  
FOREACH( demo ${demos_with_grid_NAMES} )
  ADD_EXECUTABLE( ${demo} ${demo}.c grid_sheet.c )
ENDFOREACH( demo ${demos_with_grid_NAMES} )
  
ADD_EXECUTABLE( grid_sheet grid_sheet.c )
get_source_file_property(MY_C_FLAGS grid_sheet.c COMPILE_FLAGS)
set( MY_C_FLAGS "${MY_C_FLAGS} -DSTAND_ALONE" )
set_target_properties( grid_sheet PROPERTIES COMPILE_FLAGS ${MY_C_FLAGS})

FOREACH( demo ${demos_NAMES} ${demos_with_grid_NAMES} grid_sheet )
  TARGET_LINK_LIBRARIES( ${demo} haru )
  if( BUILD_SHARED_LIBS AND WIN32 AND NOT CYGWIN )
    get_source_file_property(MY_C_FLAGS ${demo}.c COMPILE_FLAGS)
    set( MY_C_FLAGS "${MY_C_FLAGS} -DHPDF_DLL" )
    set_source_files_properties( ${demo}.c
                                 PROPERTIES COMPILE_FLAGS ${MY_C_FLAGS} )
  endif( BUILD_SHARED_LIBS AND WIN32 AND NOT CYGWIN )
  if( WIN32 AND NOT CYGWIN )
    get_source_file_property(MY_C_FLAGS ${demo}.c COMPILE_FLAGS)
    set( MY_C_FLAGS "${MY_C_FLAGS} -D__WIN32__" )
    set_source_files_properties( ${demo}.c
                                 PROPERTIES COMPILE_FLAGS ${MY_C_FLAGS} )
  endif( WIN32 AND NOT CYGWIN )
ENDFOREACH( demo ${demos_NAMES} ${demos_with_grid_NAMES} grid_sheet )

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