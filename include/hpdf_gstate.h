/*
 * << Haru Free PDF Library >> -- hpdf_gstate.h
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

#ifndef _HPDF_GSTATE_H
#define _HPDF_GSTATE_H

#include "hpdf_font.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*------ graphic state stack -------------------------------------------------*/

struct _HPDF_GState_Rec;
typedef struct _HPDF_GState_Rec  *HPDF_GState;

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

HPDF_GState
HPDF_GState_New(
    HPDF_MMgr   mmgr,
    HPDF_GState current
);

HPDF_GState
HPDF_GState_Free(
    HPDF_MMgr   mmgr,
    HPDF_GState gstate
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_GSTATE_H */

