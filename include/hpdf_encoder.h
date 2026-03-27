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

struct _HPDF_Encoder_Rec;
struct _HPDF_BasicEncoderAttr_Rec;
struct _HPDF_CMapEncoderAttr_Rec;
struct _HPDF_CidRange_Rec;
struct _HPDF_ParseText_Rec;
struct _HPDF_UnicodeMap_Rec;
struct _HPDF_Encoder_Rec;

typedef struct _HPDF_BasicEncoderAttr_Rec *HPDF_BasicEncoderAttr;
typedef struct _HPDF_CMapEncoderAttr_Rec  *HPDF_CMapEncoderAttr;

typedef struct _HPDF_Encoder_Rec    HPDF_Encoder_Rec;
typedef struct _HPDF_Encoder_Rec    *HPDF_Encoder;
typedef struct _HPDF_ParseText_Rec  HPDF_ParseText_Rec;
typedef struct _HPDF_CidRange_Rec   HPDF_CidRange_Rec;
typedef struct _HPDF_UnicodeMap_Rec HPDF_UnicodeMap_Rec;

typedef HPDF_STATUS
(*HPDF_Encoder_Init_Func)  (HPDF_Encoder  encoder);

typedef enum _HPDF_EncodingType {
    HPDF_STANDARD_ENCODING = 0,
    HPDF_MAC_ROMAN_ENCODING,
    HPDF_WIN_ANSI_ENCODING,
    HPDF_FONT_SPECIFIC,
    HPDF_ENCODING_EOF
} HPDF_EncodingType;

typedef enum _HPDF_BaseEncodings {
    HPDF_BASE_ENCODING_STANDARD,
    HPDF_BASE_ENCODING_WIN_ANSI,
    HPDF_BASE_ENCODING_MAC_ROMAN,
    HPDF_BASE_ENCODING_FONT_SPECIFIC,
    HPDF_BASE_ENCODING_EOF
} HPDF_BaseEncodings;

HPDF_STATUS
HPDF_Encoder_Validate(
    HPDF_Encoder encoder
);

void
HPDF_Encoder_SetParseText(
    HPDF_Encoder        encoder,
    HPDF_ParseText_Rec *state,
    const HPDF_BYTE    *text,
    HPDF_UINT           len
);

HPDF_ByteType
HPDF_Encoder_ByteType(
    HPDF_Encoder        encoder,
    HPDF_ParseText_Rec *state
);

HPDF_UNICODE
HPDF_Encoder_ToUnicode(
    HPDF_Encoder encoder,
    HPDF_UINT16  code
);

void
HPDF_Encoder_Free(
    HPDF_Encoder encoder
);

/*-- HPDF_BasicEncoder ----------------------------------*/

HPDF_Encoder
HPDF_BasicEncoder_New(
    HPDF_MMgr   mmgr,
    const char *encoding_name
);

void
HPDF_BasicEncoder_Free(
    HPDF_Encoder encoder
);

HPDF_STATUS
HPDF_BasicEncoder_Write(
    HPDF_Encoder encoder,
    HPDF_Stream  out
);

HPDF_UNICODE
HPDF_BasicEncoder_ToUnicode(
    HPDF_Encoder encoder,
    HPDF_UINT16  code
);

/*-- HPDF_CMapEncoder ----------------------------------*/

HPDF_Encoder
HPDF_CMapEncoder_New(
    HPDF_MMgr               mmgr,
    char                   *name,
    HPDF_Encoder_Init_Func  init_fn
);

HPDF_STATUS
HPDF_CMapEncoder_InitAttr(
    HPDF_Encoder encoder
);

void
HPDF_CMapEncoder_Free(
    HPDF_Encoder encoder
);

HPDF_STATUS
HPDF_CMapEncoder_Write(
    HPDF_Encoder encoder,
    HPDF_Stream  out
);

HPDF_UNICODE
HPDF_CMapEncoder_ToUnicode(
    HPDF_Encoder encoder,
    HPDF_UINT16  code
);

HPDF_UINT16
HPDF_CMapEncoder_ToCID(
    HPDF_Encoder encoder,
    HPDF_UINT16  code
);

HPDF_STATUS
HPDF_CMapEncoder_SetParseText(
    HPDF_Encoder        encoder,
    HPDF_ParseText_Rec *state,
    const HPDF_BYTE    *text,
    HPDF_UINT           len
);

HPDF_ByteType
HPDF_CMapEncoder_ByteType(
    HPDF_Encoder        encoder,
    HPDF_ParseText_Rec *state
);

HPDF_STATUS
HPDF_CMapEncoder_AddCMap(
    HPDF_Encoder             encoder,
    const HPDF_CidRange_Rec *range
);

HPDF_STATUS
HPDF_CMapEncoder_AddNotDefRange(
    HPDF_Encoder      encoder,
    HPDF_CidRange_Rec range
);

HPDF_STATUS
HPDF_CMapEncoder_AddCodeSpaceRange(
    HPDF_Encoder      encoder,
    HPDF_CidRange_Rec range
);

void
HPDF_CMapEncoder_SetUnicodeArray(
    HPDF_Encoder               encoder,
    const HPDF_UnicodeMap_Rec *array1
);

HPDF_STATUS
HPDF_CMapEncoder_AddJWWLineHead(
    HPDF_Encoder       encoder,
    const HPDF_UINT16 *code
);

HPDF_BOOL
HPDF_Encoder_CheckJWWLineHead(
    HPDF_Encoder      encoder,
    const HPDF_UINT16 code
);

/*-- utility functions ----------------------------------*/

const char*
HPDF_UnicodeToGryphName(
    HPDF_UNICODE unicode
);

HPDF_UNICODE
HPDF_GryphNameToUnicode(
    const char *gryph_name
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_ENCODER_H */
