/*
 * << Haru Free PDF Library >> -- hpdf_encoder.h
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

#ifndef _HPDF_ENCODER_H
#define _HPDF_ENCODER_H

#include "hpdf_consts.h"
#include "hpdf_streams.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-- HPDF_Encoder ---------------------------------------*/

#define HPDF_ENCODER_SIG_BYTES 0x454E4344L

/*----------------------------------------------------------------------------*/
/*------ predefined font encodings -------------------------------------------*/

#define  HPDF_ENCODING_FONT_SPECIFIC  "FontSpecific"
#define  HPDF_ENCODING_STANDARD       "StandardEncoding"
#define  HPDF_ENCODING_MAC_ROMAN      "MacRomanEncoding"
#define  HPDF_ENCODING_WIN_ANSI       "WinAnsiEncoding"
#define  HPDF_ENCODING_ISO8859_2      "ISO8859-2"
#define  HPDF_ENCODING_ISO8859_3      "ISO8859-3"
#define  HPDF_ENCODING_ISO8859_4      "ISO8859-4"
#define  HPDF_ENCODING_ISO8859_5      "ISO8859-5"
#define  HPDF_ENCODING_ISO8859_6      "ISO8859-6"
#define  HPDF_ENCODING_ISO8859_7      "ISO8859-7"
#define  HPDF_ENCODING_ISO8859_8      "ISO8859-8"
#define  HPDF_ENCODING_ISO8859_9      "ISO8859-9"
#define  HPDF_ENCODING_ISO8859_10     "ISO8859-10"
#define  HPDF_ENCODING_ISO8859_11     "ISO8859-11"
#define  HPDF_ENCODING_ISO8859_13     "ISO8859-13"
#define  HPDF_ENCODING_ISO8859_14     "ISO8859-14"
#define  HPDF_ENCODING_ISO8859_15     "ISO8859-15"
#define  HPDF_ENCODING_ISO8859_16     "ISO8859-16"
#define  HPDF_ENCODING_CP1250         "CP1250"
#define  HPDF_ENCODING_CP1251         "CP1251"
#define  HPDF_ENCODING_CP1252         "CP1252"
#define  HPDF_ENCODING_CP1253         "CP1253"
#define  HPDF_ENCODING_CP1254         "CP1254"
#define  HPDF_ENCODING_CP1255         "CP1255"
#define  HPDF_ENCODING_CP1256         "CP1256"
#define  HPDF_ENCODING_CP1257         "CP1257"
#define  HPDF_ENCODING_CP1258         "CP1258"
#define  HPDF_ENCODING_KOI8_R         "KOI8-R"

/*----------------------------------------------------------------------------*/
/*----- definition for font encoding -----------------------------------------*/

#define char_NOTDEF        ".notdef"

typedef enum _HPDF_EncodingType {
    HPDF_STANDARD_ENCODING = 0,
    HPDF_MAC_ROMAN_ENCODING,
    HPDF_WIN_ANSI_ENCODING,
    HPDF_FONT_SPECIFIC,
    HPDF_ENCODING_EOF
} HPDF_EncodingType;


typedef struct _HPDF_ParseText_Rec {
    const HPDF_BYTE  *text;
    HPDF_UINT        index;
    HPDF_UINT        len;
    HPDF_UINT        char_bytes;
    HPDF_CharEnc     charenc;
} HPDF_ParseText_Rec;


typedef struct _HPDF_Encoder_Rec *HPDF_Encoder;

typedef struct _HPDF_Doc_Rec  *HPDF_Doc;


typedef HPDF_ByteType
(*HPDF_Encoder_ByteType_Func)  (HPDF_Encoder        encoder,
                                HPDF_ParseText_Rec *state,
                                HPDF_UINT          *bytes);


typedef HPDF_UCS4
(*HPDF_Encoder_ToUcs4_Func)  (HPDF_Encoder   encoder,
                              const HPDF_BYTE *text,
                              HPDF_UINT      bytes);


typedef HPDF_STATUS
(*HPDF_Encoder_Write_Func)  (HPDF_Encoder  encoder,
                             HPDF_Stream   out);


typedef HPDF_STATUS
(*HPDF_Encoder_Init_Func)  (HPDF_Encoder  encoder,
                            HPDF_Doc      pdf);


typedef void
(*HPDF_Encoder_Free_Func)  (HPDF_Encoder  encoder);


typedef struct  _HPDF_Encoder_Rec {
    HPDF_UINT32                     sig_bytes;
    char                            name[HPDF_LIMIT_MAX_NAME_LEN + 1];
    HPDF_MMgr                       mmgr;
    HPDF_Error                      error;
    HPDF_EncoderType                type;
    HPDF_CharEnc                    charenc;

    HPDF_Encoder_ByteType_Func      byte_type_fn;
    HPDF_Encoder_ToUcs4_Func        to_ucs4_fn;
    HPDF_Encoder_Write_Func         write_fn;
    HPDF_Encoder_Free_Func          free_fn;
    HPDF_Encoder_Init_Func          init_fn;
    /*
    char                         lang_code[3];
    char                         country_code[3];
    */
    void                            *attr;
}  HPDF_Encoder_Rec;


typedef enum _HPDF_BaseEncodings {
    HPDF_BASE_ENCODING_STANDARD,
    HPDF_BASE_ENCODING_WIN_ANSI,
    HPDF_BASE_ENCODING_MAC_ROMAN,
    HPDF_BASE_ENCODING_FONT_SPECIFIC,
    HPDF_BASE_ENCODING_EOF
} HPDF_BaseEncodings;

HPDF_STATUS
HPDF_Encoder_Validate  (HPDF_Encoder  encoder);

void
HPDF_Encoder_SetParseText  (HPDF_Encoder        encoder,
                            HPDF_ParseText_Rec  *state,
                            const HPDF_BYTE     *text,
                            HPDF_UINT           len);

HPDF_ByteType
HPDF_Encoder_ByteType  (HPDF_Encoder        encoder,
                        HPDF_ParseText_Rec *state,
                        HPDF_UINT          *bytes);


HPDF_UCS4
HPDF_Encoder_ToUnicode  (HPDF_Encoder     encoder,
                         HPDF_UINT16      code);


HPDF_UCS4
HPDF_Encoder_CodeToUcs4  (HPDF_Encoder     encoder,
                          HPDF_CODE        code,
                          HPDF_UINT        bytes);


HPDF_UCS4
HPDF_Encoder_ToUcs4  (HPDF_Encoder     encoder,
                      const HPDF_BYTE *text,
                      HPDF_UINT        bytes);


HPDF_UINT
HPDF_Encoder_StrLen  (HPDF_Encoder     encoder,
                      const HPDF_BYTE *s,
                      HPDF_INT         maxlen);


void
HPDF_Encoder_Free  (HPDF_Encoder  encoder);


/*-- HPDF_BasicEncoder ----------------------------------*/


typedef struct _HPDF_BasicEncoderAttr_Rec  *HPDF_BasicEncoderAttr;

typedef struct  _HPDF_BasicEncoderAttr_Rec {
      char           base_encoding[HPDF_LIMIT_MAX_NAME_LEN + 1];
      HPDF_BYTE           first_char;
      HPDF_BYTE           last_char;
      HPDF_UNICODE        unicode_map[256];
      HPDF_BOOL           has_differences;
      HPDF_BYTE           differences[256];
} HPDF_BasicEncoderAttr_Rec;


HPDF_Encoder
HPDF_BasicEncoder_New  (HPDF_MMgr        mmgr,
                        const char  *encoding_name);


void
HPDF_BasicEncoder_Free  (HPDF_Encoder  encoder);


HPDF_STATUS
HPDF_BasicEncoder_Write  (HPDF_Encoder  encoder,
                          HPDF_Stream   out);


HPDF_UCS4
HPDF_BasicEncoder_ToUcs4 (HPDF_Encoder     encoder,
                          const HPDF_BYTE *text,
                          HPDF_UINT        bytes);

/*-- HPDF_CMapEncoder ----------------------------------*/

typedef HPDF_CID
(*HPDF_CMapEncoder_ToCID_Func)  (HPDF_Encoder  encoder,
                                 HPDF_UCS4     ucs4);


typedef struct _HPDF_CidRange_Rec {
    HPDF_CODE  from;
    HPDF_CODE  to;
    HPDF_INT16 bytes;
    HPDF_CID   cid;
} HPDF_CidRange_Rec;


typedef struct _HPDF_UnicodeMap_Rec {
    HPDF_UINT16   code;
    HPDF_UNICODE  unicode;
} HPDF_UnicodeMap_Rec;

typedef struct _HPDF_CMapInfo_Rec *HPDF_CMapInfo;

typedef struct _HPDF_CMapInfo_Rec {
    char                             registry[HPDF_LIMIT_MAX_NAME_LEN + 1];
    char                             ordering[HPDF_LIMIT_MAX_NAME_LEN + 1];
    HPDF_WritingMode                 writing_mode;
    HPDF_UINT                        count;
    HPDF_PDFVer                      pdf_version;
} HPDF_CMapInfo_Rec;

typedef struct _HPDF_CMap_Rec *HPDF_CMap;

typedef struct _HPDF_CMap_Rec {
    HPDF_CMapInfo_Rec                info;
    HPDF_CID                         cid_map[HPDF_MAX_UCS4 + 1];
} HPDF_CMap_Rec;

typedef struct _HPDF_CMapEncoderAttr_Rec  *HPDF_CMapEncoderAttr;

typedef struct _HPDF_CMapEncoderAttr_Rec {
    HPDF_UNICODE                    *unicode_map;
    HPDF_CMapInfo                    cmap;
    HPDF_List                        notdef_range;
    HPDF_List                        code_space_range;
    HPDF_CMapEncoder_ToCID_Func      to_cid_fn;
    HPDF_INT                         supplement;
    HPDF_CID                         max_cid;
    HPDF_INT                         uid_offset;
    HPDF_UINT                        xuid[3];
} HPDF_CMapEncoderAttr_Rec;


HPDF_Encoder
HPDF_CMapEncoder_New  (HPDF_MMgr                mmgr,
                       const char              *name,
                       HPDF_Encoder_Init_Func   init_fn);


HPDF_STATUS
HPDF_CMapEncoder_InitAttr  (HPDF_Encoder  encoder);


void
HPDF_CMapEncoder_Free  (HPDF_Encoder   encoder);


HPDF_STATUS
HPDF_CMapEncoder_Write  (HPDF_Encoder   encoder,
                         HPDF_Stream    out);


HPDF_CID
HPDF_CMapEncoder_ToCID  (HPDF_Encoder   encoder,
                         HPDF_UCS4      ucs4);


HPDF_UINT
HPDF_CMapEncoder_NextCode  (HPDF_Encoder  encoder,
                            HPDF_UINT     *pcodespaceindex,
                            HPDF_CODE     *pcode);


/* with converter, use HPDF_Font_SetParseText */
HPDF_STATUS
HPDF_CMapEncoder_SetParseText  (HPDF_Encoder         encoder,
                                HPDF_ParseText_Rec  *state,
                                const HPDF_BYTE     *text,
                                HPDF_UINT            len);

HPDF_ByteType
HPDF_CMapEncoder_ByteType  (HPDF_Encoder         encoder,
                            HPDF_ParseText_Rec  *state,
                            HPDF_UINT           *bytes);


HPDF_STATUS
HPDF_CMapEncoder_AddCMap  (HPDF_Encoder              encoder,
                           const HPDF_CidRange_Rec  *range);


HPDF_STATUS
HPDF_CMapEncoder_AddNotDefRange  (HPDF_Encoder        encoder,
                                  HPDF_CidRange_Rec   range);


HPDF_STATUS
HPDF_CMapEncoder_AddCodeSpaceRange  (HPDF_Encoder        encoder,
                                     HPDF_CidRange_Rec   range);


HPDF_STATUS
HPDF_CMapEncoder_SetUnicodeArray  (HPDF_Encoder               encoder,
                                   const HPDF_UnicodeMap_Rec *array1);


HPDF_STATUS
HPDF_UTF8Encoder_Init  (HPDF_Encoder  encoder,
                        HPDF_Doc      pdf);


HPDF_STATUS
HPDF_UTF16Encoder_Init  (HPDF_Encoder  encoder,
                         HPDF_Doc      pdf);


/*-- utility functions ----------------------------------*/

const char*
HPDF_UnicodeToGryphName  (HPDF_UNICODE  unicode);


HPDF_UNICODE
HPDF_GryphNameToUnicode  (const char  *gryph_name);


typedef HPDF_UINT
(*HPDF_UTFBytes_Func)  (const HPDF_BYTE *text);


typedef HPDF_UCS4
(*HPDF_UTFToUcs4_Func)  (const HPDF_BYTE *text,
                         HPDF_UINT        bytes);


typedef HPDF_UINT
(*HPDF_Ucs4ToUTF_Func)  (HPDF_BYTE    *buf,
                         HPDF_UCS4     ucs4);


HPDF_UINT
HPDF_UTF8Bytes  (const HPDF_BYTE *text);


HPDF_UCS4
HPDF_UTF8ToUcs4  (const HPDF_BYTE *text,
                  HPDF_UINT        bytes);


HPDF_UINT
HPDF_Ucs4ToUTF8  (HPDF_BYTE    *buf,
                  HPDF_UCS4     ucs4);


HPDF_UINT
HPDF_UTF16BEBytes  (const HPDF_BYTE *text);


HPDF_UCS4
HPDF_UTF16BEToUcs4  (const HPDF_BYTE *text,
                     HPDF_UINT        bytes);


HPDF_UINT
HPDF_Ucs4ToUTF16BE  (HPDF_BYTE    *buf,
                     HPDF_UCS4     ucs4);


HPDF_UINT
HPDF_UTF16LEBytes  (const HPDF_BYTE *text);


HPDF_UCS4
HPDF_UTF16LEToUcs4  (const HPDF_BYTE *text,
                     HPDF_UINT        bytes);


HPDF_UINT
HPDF_Ucs4ToUTF16LE  (HPDF_BYTE    *buf,
                     HPDF_UCS4     ucs4);


HPDF_UINT
HPDF_UTF32BEBytes  (const HPDF_BYTE *text);


HPDF_UCS4
HPDF_UTF32BEToUcs4  (const HPDF_BYTE *text,
                     HPDF_UINT        bytes);


HPDF_UINT
HPDF_Ucs4ToUTF32BE  (HPDF_BYTE    *buf,
                     HPDF_UCS4     ucs4);


HPDF_UINT
HPDF_UTF32LEBytes  (const HPDF_BYTE *text);


HPDF_UCS4
HPDF_UTF32LEToUcs4  (const HPDF_BYTE *text,
                     HPDF_UINT        bytes);


HPDF_UINT
HPDF_Ucs4ToUTF32LE  (HPDF_BYTE    *buf,
                     HPDF_UCS4     ucs4);


void
HPDF_NormalizeCharEnc  (HPDF_CharEnc *pcharenc);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_ENCODER_H */
