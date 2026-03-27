#ifndef _HPDF_DOC_INTERNAL_H
#define _HPDF_DOC_INTERNAL_H

#include "hpdf_types.h"
#include "internal/hpdf_error_internal.h"

typedef struct _HPDF_Doc_Rec {
    HPDF_UINT32     sig_bytes;
    HPDF_PDFVer     pdf_version;

    HPDF_MMgr         mmgr;
    HPDF_Catalog      catalog;
    HPDF_Outline      outlines;
    HPDF_Xref         xref;
    HPDF_Pages        root_pages;
    HPDF_Pages        cur_pages;
    HPDF_Page         cur_page;
    HPDF_List         page_list;
    HPDF_Error_Rec    error;
    HPDF_Dict         info;
    HPDF_Dict         trailer;

    HPDF_List         font_mgr;
    HPDF_BYTE         ttfont_tag[6];

    /* list for loaded fontdefs */
    HPDF_List         fontdef_list;

    /* list for loaded encodings */
    HPDF_List         encoder_list;

    HPDF_Encoder      cur_encoder;

    /* default compression mode */
    HPDF_BOOL         compression_mode;

    HPDF_BOOL         encrypt_on;
    HPDF_EncryptDict  encrypt_dict;

    HPDF_Encoder      def_encoder;

    HPDF_UINT         page_per_pages;
    HPDF_UINT         cur_page_num;

    /* buffer for saving into memory stream */
    HPDF_Stream       stream;

    /* PDF/A conformance */
    HPDF_PDFAType     pdfa_type;
    HPDF_List         xmp_extensions;
} HPDF_Doc_Rec;

#endif /* _HPDF_DOC_INTERNAL_H */