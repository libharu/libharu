# demo/CMakeLists.txt
#
# Copyright (C) 2008  Werner Smekal
#
# create demo executables

  # =======================================================================
  # source file names and c flags
  # =======================================================================
set(
  demos_NAMES
    attach
    character_map
    clip_hatch
    clip_hatch2
    encoding_list
    encryption
    ext_gstate_demo
    font_demo
    image_demo
    jpeg_demo
    jpfont_demo
    line_demo
    link_annotation
    make_rawimage
    minimal
    outline_demo
    #outline_demo_jp
    permission
    png_demo
    slide_show_demo
    text_annotation
    ttfont_demo
    ttfont_demo_jp
    utf8
)

set(
  demos_with_grid_NAMES
    arc_demo
    chfont_demo
    grid_demo
    raw_image_demo
    text_demo
    text_demo2
)

# we need to add some definitions for win 32
set(DEMO_C_FLAGS)
if(WIN32 AND NOT CYGWIN)
  set(DEMO_C_FLAGS "-D__WIN32__")
endif(WIN32 AND NOT CYGWIN)

# =======================================================================
# create demos
# =======================================================================
foreach(demo ${demos_NAMES})
  add_executable(${demo} ${demo}.c handler.c)
  target_link_libraries(${demo} PUBLIC hpdf)
  if(UNIX AND NOT APPLE)
    target_link_libraries(${demo} PUBLIC m)
  endif()
  if(DEMO_C_FLAGS)
    set_target_properties(${demo} PROPERTIES COMPILE_FLAGS ${DEMO_C_FLAGS})
  endif(DEMO_C_FLAGS)
endforeach()

# some demos need grid_sheet.c compiled in
foreach(demo ${demos_with_grid_NAMES})
  add_executable(${demo} ${demo}.c grid_sheet.c handler.c)
  target_link_libraries(${demo} PUBLIC hpdf)
  if(UNIX AND NOT APPLE)
    target_link_libraries(${demo} PUBLIC m)
  endif() 
  if(DEMO_C_FLAGS)
    set_target_properties(${demo} PROPERTIES COMPILE_FLAGS ${DEMO_C_FLAGS})
  endif(DEMO_C_FLAGS)
endforeach()

# =======================================================================
# install demo source, demo executables and other files
# =======================================================================
install(
  TARGETS ${demos_NAMES} ${demos_with_grid_NAMES}
  DESTINATION demo
)
foreach(demo ${demos_NAMES} ${demos_with_grid_NAMES})
  install(FILES ${demo}.c DESTINATION demo)
endforeach()

# install demo files
install(
  DIRECTORY images mbtext pngsuite rawimage ttfont type1
  DESTINATION demo
)
