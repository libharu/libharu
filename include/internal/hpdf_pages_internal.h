#ifndef HPDF_PAGES_INTERNAL_H
#define HPDF_PAGES_INTERNAL_H

typedef struct _HPDF_PageAttr_Rec {
    HPDF_Pages         parent;
    HPDF_Dict          fonts;
    HPDF_Dict          xobjects;
    HPDF_Dict          ext_gstates;
    HPDF_Dict          shadings;
    HPDF_GState        gstate;
    HPDF_Point         str_pos;
    HPDF_Point         cur_pos;
    HPDF_Point         text_pos;
    HPDF_TransMatrix   text_matrix;
    HPDF_UINT16        gmode;
    HPDF_Dict          contents;
    HPDF_Stream        stream;
    HPDF_Xref          xref;
    HPDF_UINT          compression_mode;
    HPDF_PDFVer       *ver;
} HPDF_PageAttr_Rec;

#endif /* HPDF_PAGES_INTERNAL_H */