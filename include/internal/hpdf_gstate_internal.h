#ifndef HPDF_GSTATE_INTERNAL_H
#define HPDF_GSTATE_INTERNAL_H

typedef struct _HPDF_GState_Rec {
    HPDF_TransMatrix        trans_matrix;
    HPDF_REAL               line_width;
    HPDF_LineCap            line_cap;
    HPDF_LineJoin           line_join;
    HPDF_REAL               miter_limit;
    HPDF_DashMode           dash_mode;
    HPDF_REAL               flatness;

    HPDF_REAL               char_space;
    HPDF_REAL               word_space;
    HPDF_REAL               h_scalling;
    HPDF_REAL               text_leading;
    HPDF_TextRenderingMode  rendering_mode;
    HPDF_REAL               text_rise;

    HPDF_ColorSpace         cs_fill;
    HPDF_ColorSpace         cs_stroke;
    HPDF_RGBColor           rgb_fill;
    HPDF_RGBColor           rgb_stroke;
    HPDF_CMYKColor          cmyk_fill;
    HPDF_CMYKColor          cmyk_stroke;
    HPDF_REAL               gray_fill;
    HPDF_REAL               gray_stroke;

    HPDF_Font               font;
    HPDF_REAL               font_size;
    HPDF_WritingMode        writing_mode;

    HPDF_GState             prev;
    HPDF_UINT               depth;
} HPDF_GState_Rec;

#endif /* HPDF_GSTATE_INTERNAL_H */