# src/CMakeLists.txt
#
# Copyright (C) 2008  Werner Smekal
#
# create library
# =======================================================================
# libharu source files
# =======================================================================
set(
  libharu_SRCS
  	hpdf_annotation.c
  	hpdf_array.c
  	hpdf_binary.c
  	hpdf_boolean.c
  	hpdf_catalog.c
  	hpdf_destination.c
  	hpdf_dict.c
  	hpdf_doc_png.c
  	hpdf_doc.c
  	hpdf_encoder_cns.c
  	hpdf_encoder_cnt.c
  	hpdf_encoder_jp.c
  	hpdf_encoder_kr.c
  	hpdf_encoder.c
  	hpdf_encrypt.c
  	hpdf_encryptdict.c
  	hpdf_error.c
  	hpdf_ext_gstate.c
  	hpdf_font_cid.c
  	hpdf_font_tt.c
  	hpdf_font_type1.c
  	hpdf_font.c
  	hpdf_fontdef_base14.c
  	hpdf_fontdef_cid.c
  	hpdf_fontdef_cns.c
  	hpdf_fontdef_cnt.c
  	hpdf_fontdef_jp.c
  	hpdf_fontdef_kr.c
  	hpdf_fontdef_tt.c
  	hpdf_fontdef_type1.c
  	hpdf_fontdef.c
  	hpdf_gstate.c
	hpdf_image_ccitt.c
  	hpdf_image_png.c
  	hpdf_image.c
  	hpdf_info.c
  	hpdf_list.c
  	hpdf_mmgr.c
  	hpdf_name.c
  	hpdf_namedict.c
  	hpdf_null.c
  	hpdf_number.c
  	hpdf_objects.c
  	hpdf_outline.c
  	hpdf_page_label.c
  	hpdf_page_operator.c
  	hpdf_pages.c
  	hpdf_real.c
  	hpdf_streams.c
  	hpdf_string.c
  	hpdf_u3d.c
  	hpdf_utils.c
  	hpdf_xref.c
  	hpdf_pdfa.c
	hpdf_3dmeasure.c
	hpdf_exdata.c
	hpdf_encoder_utf.c
)

IF(NOT DEFINED ${HAVE_LIBPNG})
ADD_DEFINITIONS(-DLIBHPDF_HAVE_NOPNGLIB)
ENDIF(NOT DEFINED ${HAVE_LIBPNG})

# =======================================================================
# create static and shared haru library
# =======================================================================
if(LIBHARU_STATIC)
  add_library(${LIBHARU_NAME_STATIC} STATIC ${libharu_SRCS})
  target_link_libraries(${LIBHARU_NAME_STATIC} ${ADDITIONAL_LIBRARIES})
  install(
    TARGETS ${LIBHARU_NAME_STATIC}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
  if(WIN32 AND NOT CYGWIN)
		foreach(addlib ${ADDITIONAL_LIBRARIES})
			install(FILES ${addlib} DESTINATION lib)
		endforeach(addlib)
  endif(WIN32 AND NOT CYGWIN)
endif(LIBHARU_STATIC)
if(LIBHARU_SHARED)
  add_library(${LIBHARU_NAME} SHARED ${libharu_SRCS})
  target_link_libraries(${LIBHARU_NAME} ${ADDITIONAL_LIBRARIES})
  if(WIN32 AND NOT CYGWIN)
  	set_target_properties(${LIBHARU_NAME} PROPERTIES DEFINE_SYMBOL HPDF_DLL_MAKE)
  endif(WIN32 AND NOT CYGWIN)
  install(
    TARGETS ${LIBHARU_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
endif(LIBHARU_SHARED)
