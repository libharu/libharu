#ifndef HPDF_OBJECTS_INTERNAL_H
#define HPDF_OBJECTS_INTERNAL_H

/*
 *  structure of Object-ID
 *
 *  1       direct-object
 *  2       indirect-object
 *  3       reserved
 *  4       shadow-object
 *  5-8     reserved
 *  9-32    object-id
 *
 *  the real Object-ID is described "obj_id & 0x00FFFFFF"
 */

typedef struct _HPDF_Obj_Header {
    HPDF_UINT32  obj_id;
    HPDF_UINT16  gen_no;
    HPDF_UINT16  obj_class;
} HPDF_Obj_Header;

typedef struct _HPDF_Null_Rec {
    HPDF_Obj_Header header;
} HPDF_Null_Rec;

typedef struct _HPDF_Boolean_Rec {
    HPDF_Obj_Header  header;
    HPDF_BOOL        value;
} HPDF_Boolean_Rec;

typedef struct _HPDF_Number_Rec {
    HPDF_Obj_Header  header;
    HPDF_INT32       value;
} HPDF_Number_Rec;

typedef struct _HPDF_Real_Rec {
    HPDF_Obj_Header  header;
    HPDF_Error       error;
    HPDF_REAL        value;
} HPDF_Real_Rec;

typedef struct _HPDF_Name_Rec {
    HPDF_Obj_Header  header;
    HPDF_Error       error;
    char        value[HPDF_LIMIT_MAX_NAME_LEN + 1];
} HPDF_Name_Rec;

typedef struct _HPDF_String_Rec {
    HPDF_Obj_Header  header;
    HPDF_MMgr        mmgr;
    HPDF_Error       error;
    HPDF_Encoder     encoder;
    HPDF_BYTE        *value;
    HPDF_UINT        len;
} HPDF_String_Rec;

typedef struct _HPDF_Binary_Rec {
    HPDF_Obj_Header  header;
    HPDF_MMgr        mmgr;
    HPDF_Error       error;
    HPDF_BYTE        *value;
    HPDF_UINT        len;
} HPDF_Binary_Rec;

typedef struct _HPDF_Array_Rec {
    HPDF_Obj_Header  header;
    HPDF_MMgr        mmgr;
    HPDF_Error       error;
    HPDF_List        list;
} HPDF_Array_Rec;

typedef struct _HPDF_Dict_Rec {
    HPDF_Obj_Header            header;
    HPDF_MMgr                  mmgr;
    HPDF_Error                 error;
    HPDF_List                  list;
    HPDF_Dict_BeforeWriteFunc  before_write_fn;
    HPDF_Dict_OnWriteFunc      write_fn;
    HPDF_Dict_AfterWriteFunc   after_write_fn;
    HPDF_Dict_FreeFunc         free_fn;
    HPDF_Stream                stream;
    HPDF_UINT                  filter;
    HPDF_Dict                  filterParams;
    void                       *attr;
} HPDF_Dict_Rec;

typedef struct _HPDF_DictElement_Rec {
    char   key[HPDF_LIMIT_MAX_NAME_LEN + 1];
    void        *value;
} HPDF_DictElement_Rec;

typedef struct _HPDF_Proxy_Rec {
    HPDF_Obj_Header  header;
    void             *obj;
} HPDF_Proxy_Rec;

typedef struct _HPDF_XrefEntry_Rec {
      char    entry_typ;
      HPDF_UINT    byte_offset;
      HPDF_UINT16  gen_no;
      void*        obj;
} HPDF_XrefEntry_Rec;

typedef struct _HPDF_Xref_Rec {
      HPDF_MMgr    mmgr;
      HPDF_Error   error;
      HPDF_UINT32  start_offset;
      HPDF_List    entries;
      HPDF_UINT    addr;
      HPDF_Xref    prev;
      HPDF_Dict    trailer;
} HPDF_Xref_Rec;

typedef struct _HPDF_Direct_Rec {
    HPDF_Obj_Header  header;
    HPDF_MMgr        mmgr;
    HPDF_Error       error;
    HPDF_BYTE        *value;
    HPDF_UINT        len;
} HPDF_Direct_Rec;

#endif /* HPDF_OBJECTS_INTERNAL_H */