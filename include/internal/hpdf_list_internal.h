#ifndef HPDF_LIST_INTERNAL_H
#define HPDF_LIST_INTERNAL_H

typedef struct _HPDF_List_Rec {
      HPDF_MMgr       mmgr;
      HPDF_Error      error;
      HPDF_UINT       block_siz;
      HPDF_UINT       items_per_block;
      HPDF_UINT       count;
      void            **obj;
} HPDF_List_Rec;

#endif /* HPDF_LIST_INTERNAL_H */