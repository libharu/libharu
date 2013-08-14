/*
 * << Haru Free PDF Library >> -- hpdf_font.h
 *
 * URL: http://libharu.org
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2007-2009 Antony Dovgal <tony@daylessday.org>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#ifndef _HPDF_FONT_H
#define _HPDF_FONT_H

#include "hpdf_fontdef.h"

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------------*/
/*----- Writing Mode ---------------------------------------------------------*/

typedef enum _HPDF_FontType {
    HPDF_FONT_TYPE1 = 0,
    HPDF_FONT_TRUETYPE,
    HPDF_FONT_TYPE3,
    HPDF_FONT_TYPE0_CID,
    HPDF_FONT_TYPE0_TT,
    HPDF_FONT_CID_TYPE0,
    HPDF_FONT_CID_TYPE2,
    HPDF_FONT_MMTYPE1
} HPDF_FontType;


typedef HPDF_Dict HPDF_Font;


typedef HPDF_INT
(*HPDF_Font_CharWidth_Func)  (HPDF_Font        font,
                              HPDF_BOOL        converted,
                              HPDF_BYTE        irf,
                              const HPDF_BYTE *text,
                              HPDF_UINT       *bytes,
                              HPDF_UCS4       *ucs4);


typedef struct _HPDF_FontAttr_Rec  *HPDF_FontAttr;

typedef struct _HPDF_FontAttr_Rec {
    HPDF_FontType               type;
    HPDF_WritingMode            writing_mode;
    HPDF_Font_CharWidth_Func    char_width_fn;
    HPDF_FontDef                fontdef;
    HPDF_Encoder                encoder;

    /* if the encoding-type is HPDF_ENCODER_TYPE_SINGLE_BYTE, the width of
     * each charactors are cashed in 'widths'.
     * when HPDF_ENCODER_TYPE_DOUBLE_BYTE the width is calculate each time.
     */
    HPDF_INT16*                 widths;
    HPDF_BYTE*                  used;

    HPDF_Xref                   xref;
    HPDF_Font                   descendant_font;
    HPDF_Dict                   map_stream;
    HPDF_Dict                   cmap_stream;
    HPDF_Dict                   to_unicode_stream;

    HPDF_Font                   relief_font;
    HPDF_List                   converters_list[HPDF_MAX_CONVERTERS + 1];
    HPDF_UINT                   converters_index;
    HPDF_UINT                   text_cache_allocated;
    HPDF_BYTE                  *text_cache;
    HPDF_UINT                   text_cache_len;
    HPDF_TextWidth              tw_cache;
    HPDF_REAL                   width_per_byte;
} HPDF_FontAttr_Rec;


HPDF_Font
HPDF_Type1Font_New  (HPDF_MMgr        mmgr,
                     HPDF_FontDef     fontdef,
                     HPDF_Encoder     encoder,
                     HPDF_Xref        xref);

HPDF_Font
HPDF_TTFont_New  (HPDF_MMgr        mmgr,
                  HPDF_FontDef     fontdef,
                  HPDF_Encoder     encoder,
                  HPDF_Xref        xref);

HPDF_Font
HPDF_Type0Font_New  (HPDF_MMgr        mmgr,
                     HPDF_FontDef     fontdef,
                     HPDF_Encoder     encoder,
                     HPDF_Xref        xref);


HPDF_BOOL
HPDF_Font_Validate  (HPDF_Font font);


HPDF_UINT
HPDF_Font_StrLen  (HPDF_Font        font,
                   const char      *s,
                   HPDF_INT         maxlen);


void
HPDF_Font_FreeConvertersListAll (HPDF_Font font);


HPDF_STATUS
HPDF_Font_ConvertText  (HPDF_Font        font,
                        HPDF_UINT32      flags,
                        const char      *text,
                        HPDF_UINT        len);


HPDF_BOOL
HPDF_Font_IsRtL  (HPDF_Font font);


void
HPDF_Font_CheckBiDi  (HPDF_Font font,
                      HPDF_BOOL even_users);


void
HPDF_Font_SetParseText  (HPDF_Font            font,
                         HPDF_ParseText_Rec  *state,
                         const char          *text,
                         HPDF_UINT            len);


HPDF_Font
HPDF_Font_GetReliefFont  (HPDF_Font  font,
                          HPDF_UCS4  ucs4,
                          HPDF_BYTE *index);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_FONT_H */

