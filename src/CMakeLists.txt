# src/CMakeLists.txt
#
# Copyright (C) 2008  Werner Smekal
#
# create library
# =======================================================================
# libhpdf source files
# =======================================================================
set(
    LIBHPDF_SRCS
    hpdf_annotation.c
    hpdf_array.c
    hpdf_binary.c
    hpdf_boolean.c
    hpdf_catalog.c
    hpdf_destination.c
    hpdf_dict.c
    hpdf_direct.c
    hpdf_doc_png.c
    hpdf_doc.c
    hpdf_encoder_cns.c
    hpdf_encoder_cnt.c
    hpdf_encoder_jp.c
    hpdf_encoder_kr.c
    hpdf_encoder_utf.c
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
    hpdf_shading.c
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

# FIXME: Redeclaration
set(
  haru_HDRS
    ${PROJECT_SOURCE_DIR}/include/hpdf.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_types.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_consts.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_annotation.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_catalog.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_conf.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_destination.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_doc.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_encoder.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_encrypt.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_encryptdict.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_error.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_ext_gstate.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_font.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_fontdef.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_gstate.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_image.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_info.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_list.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_mmgr.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_namedict.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_objects.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_outline.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_pages.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_page_label.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_streams.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_u3d.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_utils.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_pdfa.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_3dmeasure.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_exdata.h
    ${PROJECT_SOURCE_DIR}/include/hpdf_version.h
    ${PROJECT_BINARY_DIR}/include/hpdf_config.h
)

# =======================================================================
# create hpdf library
# =======================================================================
add_library(hpdf 
    ${LIBHPDF_SRCS} 
    ${haru_HDRS})
# target_include_directories(hpdf PUBLIC
#                         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
#                         "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hpdf>")
target_include_directories(hpdf PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_include_directories(hpdf PUBLIC ${haru_HDRS})
set_target_properties(hpdf PROPERTIES
    SOVERSION ${hpdf_short_version}
    VERSION ${hpdf_full_version}
)

if (BUILD_FRAMEWORK)
    set_target_properties(hpdf PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION "${hpdf_full_version}"
        PUBLIC_HEADER "${haru_HDRS}"
        PRODUCT_BUNDLE_IDENTIFIER "github.com/libharu/libharu"
        XCODE_ATTRIBUTE_INSTALL_PATH "@rpath"
        OUTPUT_NAME "hpdf"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
        MACOSX_FRAMEWORK_IDENTIFIER "github.com/libharu/libharu"
        MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${hpdf_short_version}"
        MACOSX_FRAMEWORK_BUNDLE_VERSION "${hpdf_full_version}"
    )
endif ()

if (PNG_FOUND)
    include_directories (${PNG_INCLUDE_DIRS})
    target_link_libraries (hpdf ${PNG_LIBRARIES})
endif()
if (ZLIB_FOUND)
    include_directories (${ZLIB_INCLUDE_DIRS})
    target_link_libraries (hpdf ${ZLIB_LIBRARIES})
endif()

# Math library
if(UNIX AND NOT APPLE)
    target_link_libraries (hpdf ${M_LIB})
endif()

# install(FILES ${haru_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS hpdf
    EXPORT hpdf
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FRAMEWORK DESTINATION Library/Frameworks COMPONENT runtime OPTIONAL
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
