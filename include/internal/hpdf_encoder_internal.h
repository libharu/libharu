#ifndef _HPDF_ENCODER_INTERNAL_H
#define _HPDF_ENCODER_INTERNAL_H

#include "hpdf_encoder.h"

typedef struct _HPDF_ParseText_Rec {
    const HPDF_BYTE  *text;
    HPDF_UINT        index;
    HPDF_UINT        len;
    HPDF_ByteType    byte_type;
} HPDF_ParseText_Rec;

typedef struct _HPDF_Encoder_Rec *HPDF_Encoder;

typedef HPDF_ByteType
(*HPDF_Encoder_ByteType_Func)  (HPDF_Encoder        encoder,
                                HPDF_ParseText_Rec  *state);

typedef HPDF_UNICODE
(*HPDF_Encoder_ToUnicode_Func)  (HPDF_Encoder   encoder,
                                 HPDF_UINT16    code);

typedef char *
(*HPDF_Encoder_EncodeText_Func)  (HPDF_Encoder  encoder,
				  const char   *text,
				  HPDF_UINT     len,
				  HPDF_UINT    *encoded_length);

typedef HPDF_STATUS
(*HPDF_Encoder_Write_Func)  (HPDF_Encoder  encoder,
                             HPDF_Stream   out);

typedef void
(*HPDF_Encoder_Free_Func)  (HPDF_Encoder  encoder);

typedef struct  _HPDF_Encoder_Rec {
    HPDF_UINT32                     sig_bytes;
    char                            name[HPDF_LIMIT_MAX_NAME_LEN + 1];
    HPDF_MMgr                       mmgr;
    HPDF_Error                      error;
    HPDF_EncoderType                type;

    HPDF_Encoder_ByteType_Func      byte_type_fn;
    HPDF_Encoder_ToUnicode_Func     to_unicode_fn;
    HPDF_Encoder_EncodeText_Func    encode_text_fn;
    HPDF_Encoder_Write_Func         write_fn;
    HPDF_Encoder_Free_Func          free_fn;
    HPDF_Encoder_Init_Func          init_fn;
    /*
    char                         lang_code[3];
    char                         country_code[3];
    */
    void                            *attr;
} HPDF_Encoder_Rec;

typedef HPDF_BOOL
(*HPDF_CMapEncoder_ByteType_Func)  (HPDF_Encoder  encoder,
                                    HPDF_BYTE     b);

typedef struct  _HPDF_CMapEncoderAttr_Rec {
      HPDF_UNICODE                     unicode_map[256][256];
      HPDF_UINT16                      cid_map[256][256];
      HPDF_UINT16                      jww_line_head[HPDF_MAX_JWW_NUM];
      HPDF_List                        cmap_range;
      HPDF_List                        notdef_range;
      HPDF_List                        code_space_range;
      HPDF_WritingMode                 writing_mode;
      char                             registry[HPDF_LIMIT_MAX_NAME_LEN + 1];
      char                             ordering[HPDF_LIMIT_MAX_NAME_LEN + 1];
      HPDF_INT                         suppliment;
      HPDF_CMapEncoder_ByteType_Func   is_lead_byte_fn;
      HPDF_CMapEncoder_ByteType_Func   is_trial_byte_fn;
      HPDF_INT                         uid_offset;
      HPDF_UINT                        xuid[3];
} HPDF_CMapEncoderAttr_Rec;

typedef struct _HPDF_CidRange_Rec {
    HPDF_UINT16  from;
    HPDF_UINT16  to;
    HPDF_UINT16  cid;
} HPDF_CidRange_Rec;


typedef struct _HPDF_UnicodeMap_Rec {
    HPDF_UINT16  code;
    HPDF_UINT16  unicode;
} HPDF_UnicodeMap_Rec;

typedef struct  _HPDF_BasicEncoderAttr_Rec {
      char           base_encoding[HPDF_LIMIT_MAX_NAME_LEN + 1];
      HPDF_BYTE           first_char;
      HPDF_BYTE           last_char;
      HPDF_UNICODE        unicode_map[256];
      HPDF_BOOL           has_differences;
      HPDF_BYTE           differences[256];
} HPDF_BasicEncoderAttr_Rec;


#endif /* _HPDF_ENCODER_INTERNAL_H */
