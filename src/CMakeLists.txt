
# libharu source files
SET(
  libharu_SRCS
  	hpdf_utils.c
  	hpdf_error.c
  	hpdf_mmgr.c
  	hpdf_list.c
  	hpdf_streams.c
  	hpdf_objects.c
  	hpdf_null.c
  	hpdf_boolean.c
  	hpdf_number.c
  	hpdf_real.c
  	hpdf_name.c
  	hpdf_array.c
  	hpdf_dict.c
  	hpdf_xref.c
  	hpdf_encoder.c
  	hpdf_string.c
  	hpdf_binary.c
  	hpdf_encrypt.c
  	hpdf_encryptdict.c
  	hpdf_fontdef.c
  	hpdf_fontdef_tt.c
  	hpdf_fontdef_type1.c
  	hpdf_fontdef_base14.c
  	hpdf_fontdef_cid.c
  	hpdf_font.c
  	hpdf_font_type1.c
  	hpdf_font_tt.c
  	hpdf_font_cid.c
  	hpdf_doc.c
  	hpdf_info.c
  	hpdf_catalog.c
  	hpdf_page_label.c
  	hpdf_gstate.c
  	hpdf_pages.c
  	hpdf_page_operator.c
  	hpdf_destination.c
  	hpdf_annotation.c
  	hpdf_outline.c
  	hpdf_image.c
  	hpdf_encoder_jp.c
  	hpdf_encoder_kr.c
  	hpdf_encoder_cns.c
  	hpdf_encoder_cnt.c
  	hpdf_fontdef_jp.c
  	hpdf_fontdef_kr.c
  	hpdf_fontdef_cns.c
  	hpdf_fontdef_cnt.c
  	hpdf_image_png.c
  	hpdf_doc_png.c
  	hpdf_ext_gstate.c
)

IF( BUILD_SHARED_LIBS AND WIN32 AND NOT CYGWIN )
  SET_SOURCE_FILES_PROPERTIES( ${libharu_SRCS} PROPERTIES COMPILE_FLAGS "-DHPDF_DLL_MAKE")
  ADD_DEFINITIONS(-DHPDF_DLL_MAKE)
ENDIF( BUILD_SHARED_LIBS AND WIN32 AND NOT CYGWIN )

# create haru library
ADD_LIBRARY(
  haru
  ${libharu_SRCS}
)
TARGET_LINK_LIBRARIES( haru ${ADDITIONAL_LIBRARIES} )

# install libary and demos
INSTALL(
  TARGETS
    haru
  ARCHIVE DESTINATION 
    lib
  LIBRARY DESTINATION 
    lib
  RUNTIME DESTINATION
    bin
)
