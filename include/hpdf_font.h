/*
 * << Haru Free PDF Library >> -- hpdf_font.h
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

#ifndef _HPDF_FONT_H
#define _HPDF_FONT_H

#include "hpdf_fontdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*----- Writing Mode ---------------------------------------------------------*/

typedef HPDF_Dict HPDF_Font;

struct _HPDF_FontAttr_Rec;
typedef struct _HPDF_FontAttr_Rec  *HPDF_FontAttr;

HPDF_Font
HPDF_Type1Font_New(
    HPDF_MMgr    mmgr,
    HPDF_FontDef fontdef,
    HPDF_Encoder encoder,
    HPDF_Xref    xref
);

HPDF_Font
HPDF_TTFont_New(
    HPDF_MMgr    mmgr,
    HPDF_FontDef fontdef,
    HPDF_Encoder encoder,
    HPDF_Xref    xref
);

HPDF_Font
HPDF_Type0Font_New(
    HPDF_MMgr    mmgr,
    HPDF_FontDef fontdef,
    HPDF_Encoder encoder,
    HPDF_Xref    xref
);

HPDF_BOOL
HPDF_Font_Validate(
    HPDF_Font font
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_FONT_H */
