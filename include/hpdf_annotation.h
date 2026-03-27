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

#ifndef _HPDF_ANNOTATION_H
#define _HPDF_ANNOTATION_H

#include "hpdf_objects.h"
#include "hpdf.h"

#ifdef LIBHPDF_U3D_SUPPORT

#include "hpdf_u3d.h"

#endif /* LIBHPDF_U3D_SUPPORT */

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*------ HPDF_Annotation -----------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*----- annotation ---------------------------------------------------------*/

/**

  \ingroup link
  \brief Create new text annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle where annotation is displayed.
  \param text Text to be displayed.
  \param encoder Encoder handle which is used to encode text. If it is \c NULL, PDFDocEncoding is used.

  \return New annotation object handle. If it failed, it returns \c NULL.

  \todo Clarify what PDFDocEncoding is.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILED_TO_ALLOC_MEM
  - \ref HPDF_INVALID_ENCODER

*/
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateTextAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateFreeTextAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateLineAnnot(
    HPDF_Page    page,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint(
    HPDF_Doc  pdf,
    HPDF_Page page,
    HPDF_Rect rect
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateWidgetAnnot(
    HPDF_Page page,
    HPDF_Rect rect
);

/**

  \ingroup link
  \brief Create new link annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle clickable area.
  \param dst Handle of destination object to jump to.

  \return New annotation object handle. If it fails, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_FAILED_TO_ALLOC_MEM
  - \ref HPDF_INVALID_DESTINATION

*/
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateLinkAnnot(
    HPDF_Page        page,
    HPDF_Rect        rect,
    HPDF_Destination dst
);

/**

  \ingroup link
  \brief Create new web link annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle of clickable area.
  \param uri Destination URI to jump to.

  \return New annotation object handle. If it fails, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_FAILED_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateURILinkAnnot(
    HPDF_Page   page,
    HPDF_Rect   rect,
    const char* uri
);

HPDF_Annotation
HPDF_Page_CreateTextMarkupAnnot(
    HPDF_Page      page,
    HPDF_Rect      rect,
    const char*    text,
    HPDF_Encoder   encoder,
    HPDF_AnnotType subType
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateHighlightAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateUnderlineAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateSquigglyAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateStrikeOutAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreatePopupAnnot(
    HPDF_Page       page,
    HPDF_Rect       rect,
    HPDF_Annotation parent
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateStampAnnot(
    HPDF_Page           page,
    HPDF_Rect           rect,
    HPDF_StampAnnotName name,
    const char*         text,
    HPDF_Encoder        encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateProjectionAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateSquareAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateCircleAnnot(
    HPDF_Page    page,
    HPDF_Rect    rect,
    const char*  text,
    HPDF_Encoder encoder
);

HPDF_Annotation
HPDF_Annotation_New(
    HPDF_MMgr      mmgr,
    HPDF_Xref      xref,
    HPDF_AnnotType type,
    HPDF_Rect      rect
);

HPDF_Annotation
HPDF_WidgetAnnot_New(
    HPDF_MMgr mmgr,
    HPDF_Xref xref,
    HPDF_Rect rect
);

HPDF_Annotation
HPDF_LinkAnnot_New(
    HPDF_MMgr        mmgr,
    HPDF_Xref        xref,
    HPDF_Rect        rect,
    HPDF_Destination dst
);


HPDF_Annotation
HPDF_URILinkAnnot_New(
    HPDF_MMgr   mmgr,
    HPDF_Xref   xref,
    HPDF_Rect   rect,
    const char* uri
);

HPDF_Annotation
HPDF_MarkupAnnot_New(
    HPDF_MMgr      mmgr,
	HPDF_Xref      xref,
	HPDF_Rect      rect,
	const char*    text,
	HPDF_Encoder   encoder,
	HPDF_AnnotType subtype
);

HPDF_Annotation
HPDF_PopupAnnot_New(
    HPDF_MMgr       mmgr,
    HPDF_Xref       xref,
    HPDF_Rect       rect,
	HPDF_Annotation parent
);

HPDF_Annotation
HPDF_StampAnnot_New(
    HPDF_MMgr           mmgr,
    HPDF_Xref           xref,
    HPDF_Rect           rect,
	HPDF_StampAnnotName name,
	const char*	        text,
	HPDF_Encoder	    encoder
);

HPDF_Annotation
HPDF_ProjectionAnnot_New(
    HPDF_MMgr    mmgr,
	HPDF_Xref    xref,
	HPDF_Rect    rect,
	const char*  text,
	HPDF_Encoder encoder
);

HPDF_BOOL
HPDF_Annotation_Validate(
    HPDF_Annotation annot
);

/**

  \ingroup link
  \brief Define link annotation mouse click appearance.

  \copydoc dox_param_annot
  \param mode Link annotation highlight mode.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_FAILED_TO_ALLOC_MEM

  \see _HPDF_AnnotHighlightMode
*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_LinkAnnot_SetHighlightMode(
    HPDF_Annotation         annot,
    HPDF_AnnotHighlightMode mode
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LinkAnnot_SetJavaScript(
    HPDF_Annotation annot,
    HPDF_JavaScript javascript
);

/**

  \ingroup link
  \brief Define link annotation border style.

  \copydoc dox_param_annot
  \param width Annotation border width
  \param dash_on, dash_off Dash style parameters

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_INVALID_PARAMETER
  - \ref HPDF_FAILED_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_LinkAnnot_SetBorderStyle(
    HPDF_Annotation annot,
    HPDF_REAL       width,
    HPDF_UINT16     dash_on,
    HPDF_UINT16     dash_off
);

/**

  \ingroup link
  \brief Define link annotation icon.

  \copydoc dox_param_annot
  \param icon Link annotation icon type.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_ANNOT_INVALID_ICON
  - \ref HPDF_FAILED_TO_ALLOC_MEM

  \see _HPDF_AnnotIcon

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_TextAnnot_SetIcon(
    HPDF_Annotation annot,
    HPDF_AnnotIcon  icon
);

/**

  \ingroup link
  \brief Define whether link annotation is initially opened.

  \copydoc dox_param_annot
  \param opened \ref HPDF_TRUE if annotation initially displayed open.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_FAILED_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_TextAnnot_SetOpened(
    HPDF_Annotation annot,
    HPDF_BOOL       opened
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetRGBColor(
    HPDF_Annotation annot,
    HPDF_RGBColor   color
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetCMYKColor(
    HPDF_Annotation annot,
    HPDF_CMYKColor  color
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetGrayColor(
    HPDF_Annotation annot,
    HPDF_REAL       color
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetNoColor(
    HPDF_Annotation annot
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetTitle(
    HPDF_Annotation annot,
    const char*     name
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetSubject(
    HPDF_Annotation annot,
    const char*     name
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetCreationDate(
    HPDF_Annotation annot,
    HPDF_Date       value
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetTransparency(
    HPDF_Annotation annot,
    HPDF_REAL       value
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetIntent(
    HPDF_Annotation  annot,
    HPDF_AnnotIntent intent
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetPopup(
    HPDF_Annotation annot,
    HPDF_Annotation popup
);

/* RD entry */
HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetRectDiff(
    HPDF_Annotation annot,
    HPDF_Rect       rect
); 

/* BE entry */
HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetCloudEffect(
    HPDF_Annotation annot,
    HPDF_INT        cloudIntensity
);

/* IC with RGB entry */
HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorRGBColor(
    HPDF_Annotation annot,
    HPDF_RGBColor   color
);

/* IC with CMYK entry */
HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorCMYKColor(
    HPDF_Annotation annot,
    HPDF_CMYKColor  color
);

/* IC with Gray entry */
HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorGrayColor(
    HPDF_Annotation annot,
    HPDF_REAL       color
);

/* IC with No Color entry */
HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorTransparent(
    HPDF_Annotation annot
); 

/* l-left, r-right, b-bottom, t-top positions */
HPDF_EXPORT(HPDF_STATUS)
HPDF_TextMarkupAnnot_SetQuadPoints(
    HPDF_Annotation annot,
    HPDF_Point      lb,
    HPDF_Point      rb,
    HPDF_Point      rt,
    HPDF_Point      lt
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_Set3DView(
    HPDF_MMgr       mmgr,
    HPDF_Annotation annot,
    HPDF_Annotation annot3d,
    HPDF_Dict       view
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_PopupAnnot_SetOpened(
    HPDF_Annotation annot,
    HPDF_BOOL       opened
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_SetLineEndingStyle(
    HPDF_Annotation           annot, 
    HPDF_LineAnnotEndingStyle startStyle, 
    HPDF_LineAnnotEndingStyle endStyle
);

/* Callout line will be in default user space */
HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_Set3PointCalloutLine(
    HPDF_Annotation annot,
    HPDF_Point      startPoint,
    HPDF_Point      kneePoint,
    HPDF_Point      endPoint
); 

/* Callout line will be in default user space */
HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_Set2PointCalloutLine(
    HPDF_Annotation annot,
    HPDF_Point      startPoint,
    HPDF_Point      endPoint
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_SetDefaultStyle(
    HPDF_Annotation annot,
    const char*     style
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LineAnnot_SetPosition(
    HPDF_Annotation           annot,
    HPDF_Point                startPoint,
    HPDF_LineAnnotEndingStyle startStyle,
    HPDF_Point                endPoint,
    HPDF_LineAnnotEndingStyle endStyle
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LineAnnot_SetLeader(
    HPDF_Annotation annot,
    HPDF_INT        leaderLen,
    HPDF_INT        leaderExtLen,
    HPDF_INT        leaderOffsetLen
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LineAnnot_SetCaption(
    HPDF_Annotation           annot,
    HPDF_BOOL                 showCaption,
    HPDF_LineAnnotCapPosition position,
    HPDF_INT                  horzOffset,
    HPDF_INT                  vertOffset
);

/**

  \ingroup link
  \brief Define text annotation border appearance.

  \copydoc dox_param_annot
  \param subtype Border style subtype. See \ref _HPDF_BSSubtype.
  \param width Annotation border width
  \param dash_on, dash_off, dash_phase Dash style

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_FAILED_TO_ALLOC_MEM

  \see _HPDF_BSSubtype

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Annotation_SetBorderStyle(
    HPDF_Annotation annot,
    HPDF_BSSubtype  subtype,
    HPDF_REAL       width,
    HPDF_UINT16     dash_on,
    HPDF_UINT16     dash_off,
    HPDF_UINT16     dash_phase
);

HPDF_EXPORT(HPDF_STATUS)
HPDF_ProjectionAnnot_SetExData(
    HPDF_Annotation annot, 
    HPDF_ExData exdata
);

#ifdef LIBHPDF_U3D_SUPPORT

HPDF_Annotation
HPDF_3DAnnot_New(
    HPDF_MMgr  mmgr,
    HPDF_Xref  xref,
    HPDF_Rect  rect,
    HPDF_BOOL  tb,
    HPDF_BOOL  np,
    HPDF_U3D   u3d,
    HPDF_Image ap
);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_Create3DAnnot(
    HPDF_Page  page,
    HPDF_Rect  rect,
    HPDF_BOOL  tb,
    HPDF_BOOL  np,
    HPDF_U3D   u3d,
    HPDF_Image ap
);

#endif /* LIBHPDF_U3D_SUPPORT */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_ANNOTATION_H */
