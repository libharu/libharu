/*
 * << Haru Free PDF Library >> -- hpdf_annotation.h
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

#ifndef _HPDF_3DMEASURE_H
#define _HPDF_3DMEASURE_H

#include "hpdf_objects.h"
#include "hpdf.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*------ HPDF_3DMeasure -----------------------------------------------------*/


HPDF_3DMeasure
HPDF_3DC3DMeasure_New(
    HPDF_MMgr    mmgr,
	HPDF_Xref    xref,
	HPDF_Point3D firstanchorpoint,
	HPDF_Point3D textanchorpoint
);
             
HPDF_3DMeasure
HPDF_PD33DMeasure_New(
    HPDF_MMgr    mmgr,
	HPDF_Xref    xref,
	HPDF_Point3D annotationPlaneNormal,
	HPDF_Point3D firstAnchorPoint,
	HPDF_Point3D secondAnchorPoint,
	HPDF_Point3D leaderLinesDirection,
	HPDF_Point3D measurementValuePoint,
	HPDF_Point3D textYDirection,
	HPDF_REAL    value,
	const char*  unitsString
);

/*--------------------------------------------------------------------------*/
/*----- 3D Measure ---------------------------------------------------------*/

HPDF_EXPORT(HPDF_3DMeasure)
HPDF_Page_Create3DC3DMeasure(
    HPDF_Page    page,
    HPDF_Point3D firstanchorpoint,
    HPDF_Point3D textanchorpoint
);

HPDF_EXPORT(HPDF_3DMeasure)
HPDF_Page_CreatePD33DMeasure(
    HPDF_Page    page,
    HPDF_Point3D annotationPlaneNormal,
    HPDF_Point3D firstAnchorPoint,
    HPDF_Point3D secondAnchorPoint,
    HPDF_Point3D leaderLinesDirection,
    HPDF_Point3D measurementValuePoint,
    HPDF_Point3D textYDirection,
    HPDF_REAL    value,
    const char*  unitsString
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DMeasure_SetName(
    HPDF_3DMeasure measure,
    const char*    name
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DMeasure_SetColor(
    HPDF_3DMeasure measure,
    HPDF_RGBColor  color
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DMeasure_SetTextSize(
    HPDF_3DMeasure measure,
    HPDF_REAL      textsize
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DC3DMeasure_SetTextBoxSize(
    HPDF_3DMeasure measure,
    HPDF_INT32     x,
    HPDF_INT32     y
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DC3DMeasure_SetText(
    HPDF_3DMeasure measure,
    const char*    text,
    HPDF_Encoder   encoder
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DC3DMeasure_SetProjectionAnotation(
    HPDF_3DMeasure  measure,
    HPDF_Annotation projectionanotation
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_3DMEASURE_H */
