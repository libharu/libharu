#ifndef HPDF_FONT_INTERNAL_H
#define HPDF_FONT_INTERNAL_H

#include "hpdf_font.h"
#include "hpdf_consts.h"

typedef HPDF_Dict HPDF_Font;

typedef struct _HPDF_FontDef_Rec  *HPDF_FontDef;

typedef void (*HPDF_FontDef_FreeFunc) (HPDF_FontDef fontdef);
typedef void (*HPDF_FontDef_CleanFunc) (HPDF_FontDef fontdef);
typedef HPDF_STATUS (*HPDF_FontDef_InitFunc) (HPDF_FontDef fontdef);


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

typedef HPDF_TextWidth
(*HPDF_Font_TextWidths_Func)  (HPDF_Font        font,
                             const HPDF_BYTE  *text,
                             HPDF_UINT        len);

typedef HPDF_UINT
(*HPDF_Font_MeasureText_Func)  (HPDF_Font        font,
                              const HPDF_BYTE  *text,
                              HPDF_UINT        len,
                              HPDF_REAL        width,
                              HPDF_REAL        fontsize,
                              HPDF_REAL        charspace,
                              HPDF_REAL        wordspace,
                              HPDF_BOOL        wordwrap,
                              HPDF_REAL        *real_width);

typedef struct _HPDF_FontAttr_Rec {
    HPDF_FontType               type;
    HPDF_WritingMode            writing_mode;
    HPDF_Font_TextWidths_Func   text_width_fn;
    HPDF_Font_MeasureText_Func  measure_text_fn;
    HPDF_FontDef                fontdef;
    HPDF_Encoder                encoder;

    /* if the encoding-type is HPDF_ENCODER_TYPE_SINGLE_BYTE, the width of
     * each characters are cashed in 'widths'.
     * when HPDF_ENCODER_TYPE_DOUBLE_BYTE the width is calculate each time.
     */
    HPDF_INT16*                 widths;
    HPDF_BYTE*                  used;

    HPDF_Xref                   xref;
    HPDF_Font                   descendant_font;
    HPDF_Dict                   map_stream;
    HPDF_Dict                   cmap_stream;
} HPDF_FontAttr_Rec;

#endif /* HPDF_FONT_INTERNAL_H */
