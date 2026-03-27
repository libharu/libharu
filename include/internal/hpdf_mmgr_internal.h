#ifndef HPDF_MMGR_INTERNAL_H
#define HPDF_MMGR_INTERNAL_H

#include "hpdf_mmgr.h"

typedef struct  _HPDF_MPool_Node_Rec {
    HPDF_BYTE*       buf;
    HPDF_UINT        size;
    HPDF_UINT        used_size;
    HPDF_MPool_Node  next_node;
} HPDF_MPool_Node_Rec;

typedef struct  _HPDF_MMgr_Rec {
    HPDF_Error        error;
    HPDF_Alloc_Func   alloc_fn;
    HPDF_Free_Func    free_fn;
    HPDF_MPool_Node   mpool;
    HPDF_UINT         buf_size;

#ifdef HPDF_MEM_DEBUG
    HPDF_UINT         alloc_cnt;
    HPDF_UINT         free_cnt;
#endif
} HPDF_MMgr_Rec;

#endif /* HPDF_MMGR_INTERNAL_H */