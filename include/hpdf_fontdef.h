/*
 * << Haru Free PDF Library >> -- hpdf_fontdef.h
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

#ifndef _HPDF_FONTDEF_H
#define _HPDF_FONTDEF_H

#include "hpdf_objects.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HPDF_FONTDEF_SIG_BYTES 0x464F4E54L

/*------ collection of flags for defining characteristics. ---*/

#define HPDF_FONT_FIXED_WIDTH    1
#define HPDF_FONT_SERIF          2
#define HPDF_FONT_SYMBOLIC       4
#define HPDF_FONT_SCRIPT         8
/* Reserved                      16 */
#define HPDF_FONT_STD_CHARSET    32
#define HPDF_FONT_ITALIC         64
  /* Reserved                    128
     Reserved                    256
     Reserved                    512
     Reserved                    1024
     Reserved                    2048
     Reserved                    4096
     Reserved                    8192
     Reserved                    16384
     Reserved                    32768 */
#define HPDF_FONT_ALL_CAP        65536
#define HPDF_FONT_SMALL_CAP      131072
#define HPDF_FONT_FOURCE_BOLD    262144

#define HPDF_CID_W_TYPE_FROM_TO     0
#define HPDF_CID_W_TYPE_FROM_ARRAY  1

/*-- HPDF_FontDef ---------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----- HPDF_FontDef ---------------------------------------------------------*/

struct _HPDF_FontDef_Rec;
typedef struct _HPDF_FontDef_Rec *HPDF_FontDef;

struct _HPDF_CharData;
typedef struct _HPDF_CharData HPDF_CharData;

void
HPDF_FontDef_Free(
    HPDF_FontDef fontdef
);

void
HPDF_FontDef_Cleanup(
    HPDF_FontDef fontdef
);

HPDF_BOOL
HPDF_FontDef_Validate(
    HPDF_FontDef fontdef
);

/*----------------------------------------------------------------------------*/
/*----- HPDF_Type1FontDef  ---------------------------------------------------*/

struct _HPDF_Type1FontDefAttrRec;
typedef struct _HPDF_Type1FontDefAttrRec *HPDF_Type1FontDefAttr;

HPDF_FontDef
HPDF_Type1FontDef_New(
    HPDF_MMgr mmgr
);

HPDF_FontDef
HPDF_Type1FontDef_Load(
    HPDF_MMgr   mmgr,
    HPDF_Stream afm,
    HPDF_Stream font_data
);

HPDF_FontDef
HPDF_Type1FontDef_Duplicate(
    HPDF_MMgr    mmgr,
    HPDF_FontDef src
);

HPDF_STATUS
HPDF_Type1FontDef_SetWidths(
    HPDF_FontDef         fontdef,
    const HPDF_CharData *widths
);

HPDF_INT16
HPDF_Type1FontDef_GetWidthByName(
    HPDF_FontDef fontdef,
    const char*  gryph_name
);

HPDF_INT16
HPDF_Type1FontDef_GetWidth(
    HPDF_FontDef fontdef,
    HPDF_UNICODE unicode
);

HPDF_FontDef
HPDF_Base14FontDef_New(
    HPDF_MMgr   mmgr,
    const char* font_name
);

struct _HPDF_TTFontDefAttr_Rec;
typedef struct _HPDF_TTFontDefAttr_Rec   *HPDF_TTFontDefAttr;

HPDF_FontDef
HPDF_TTFontDef_New(
    HPDF_MMgr mmgr
);

HPDF_FontDef
HPDF_TTFontDef_Load(
    HPDF_MMgr   mmgr,
    HPDF_Stream stream,
    HPDF_BOOL   embedding
);

HPDF_FontDef
HPDF_TTFontDef_Load2(
    HPDF_MMgr   mmgr,
    HPDF_Stream stream,
    HPDF_UINT   index,
    HPDF_BOOL   embedding
);

HPDF_UINT16
HPDF_TTFontDef_GetGlyphid(
    HPDF_FontDef fontdef,
    HPDF_UINT16  unicode
);

HPDF_INT16
HPDF_TTFontDef_GetCharWidth(
    HPDF_FontDef fontdef,
    HPDF_UINT16  unicode
);

HPDF_INT16
HPDF_TTFontDef_GetGidWidth(
    HPDF_FontDef fontdef,
    HPDF_UINT16  gid
);

HPDF_STATUS
HPDF_TTFontDef_SaveFontData(
    HPDF_FontDef fontdef,
    HPDF_Stream  stream
);

HPDF_Box
HPDF_TTFontDef_GetCharBBox(
    HPDF_FontDef fontdef,
    HPDF_UINT16  unicode
);

void
HPDF_TTFontDef_SetTagName(
    HPDF_FontDef fontdef,
    char*        tag
);

/*----------------------------------------------------------------------------*/
/*----- HPDF_CIDFontDef  -----------------------------------------------------*/

struct _HPDF_CIDFontDefAttrRec;
typedef struct _HPDF_CIDFontDefAttrRec   *HPDF_CIDFontDefAttr;

typedef HPDF_STATUS (*HPDF_FontDef_InitFunc) (HPDF_FontDef fontdef);

struct _HPDF_CID_Width;
typedef struct _HPDF_CID_Width HPDF_CID_Width;

HPDF_FontDef
HPDF_CIDFontDef_New(
    HPDF_MMgr             mmgr,
    char*                 name,
    HPDF_FontDef_InitFunc init_fn
);

HPDF_STATUS
HPDF_CIDFontDef_AddWidth(
    HPDF_FontDef          fontdef,
    const HPDF_CID_Width* widths
);

HPDF_INT16
HPDF_CIDFontDef_GetCIDWidth(
    HPDF_FontDef fontdef,
    HPDF_UINT16  cid
);

HPDF_STATUS
HPDF_CIDFontDef_ChangeStyle(
    HPDF_FontDef fontdef,
    HPDF_BOOL    bold,
    HPDF_BOOL    italic
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_FONTDEF_H */
