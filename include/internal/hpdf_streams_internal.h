#ifndef HPDF_STREAMS_INTERNAL_H
#define HPDF_STREAMS_INTERNAL_H

#include "hpdf_streams.h"


typedef struct _HPDF_MemStreamAttr_Rec {
    HPDF_List  buf;
    HPDF_UINT  buf_siz;
    HPDF_UINT  w_pos;
    HPDF_BYTE  *w_ptr;
    HPDF_UINT  r_ptr_idx;
    HPDF_UINT  r_pos;
    HPDF_BYTE  *r_ptr;
} HPDF_MemStreamAttr_Rec;

typedef struct _HPDF_Stream_Rec {
    HPDF_UINT32               sig_bytes;
    HPDF_StreamType           type;
    HPDF_MMgr                 mmgr;
    HPDF_Error                error;
    HPDF_UINT                 size;
    HPDF_Stream_Write_Func    write_fn;
    HPDF_Stream_Read_Func     read_fn;
    HPDF_Stream_Seek_Func     seek_fn;
    HPDF_Stream_Free_Func     free_fn;
    HPDF_Stream_Tell_Func     tell_fn;
    HPDF_Stream_Size_Func     size_fn;
    void*                     attr;
} HPDF_Stream_Rec;

#endif /* HPDF_STREAMS_INTERNAL_H */
