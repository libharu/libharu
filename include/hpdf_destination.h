/*
 * << Haru Free PDF Library >> -- hpdf_destination.c
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

#ifndef _HPDF_DESTINATION_H
#define _HPDF_DESTINATION_H

#include "hpdf_objects.h"
#include "hpdf.h"
#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*----- HPDF_Destination -----------------------------------------------------*/

HPDF_Destination
HPDF_Destination_New(
    HPDF_MMgr mgr,
    HPDF_Page target,
    HPDF_Xref xref
);

HPDF_BOOL
HPDF_Destination_Validate(
    HPDF_Destination dst
);

/**

  \ingroup link
  \brief Define page appearance with three parameters which are \c left, \c top and \c zoom.

  \copydoc dox_param_dst
  \param left The left coordinate of the page.
  \param top  The top coordinate of the page.
  \param zoom The page magnified factor. Value must be between 0.08 (8%) to 32 (3200%).

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetXYZ(
    HPDF_Destination dst,
    HPDF_REAL        left,
    HPDF_REAL        top,
    HPDF_REAL        zoom
);

/**

  \ingroup link
  \brief Set page appearance to display entire page within the window.

  \copydoc dox_param_dst

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFit(
    HPDF_Destination dst
);

/**

  \ingroup link
  \brief Define page appearance to fit page width within the window and set top position of the page \c top parameter.

  \copydoc dox_param_dst
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitH(
    HPDF_Destination dst,
    HPDF_REAL        top
);

/**

  \ingroup link
  \brief Define page appearance to fit page height within the window and set left position of the page \c left parameter.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitV(
    HPDF_Destination dst,
    HPDF_REAL        left
);

/**

  \ingroup link
  \brief Define page appearance to fit page within the rectangle specified by \c left, \c bottom, \c right and \c top.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.
  \param bottom Bottom coordinate of the page.
  \param right Right coordinate of the page.
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitR(
    HPDF_Destination dst,
    HPDF_REAL        left,
    HPDF_REAL        bottom,
    HPDF_REAL        right,
    HPDF_REAL        top
);

/**

  \ingroup link
  \brief Define page appearance to fit page bounding box  within the window.

  \copydoc dox_param_dst

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitB(
    HPDF_Destination dst
);

/**

  \ingroup link
  \brief Define page appearance to fit page bounding box width within the window and set top position of page to value of \c top parameter.

  \copydoc dox_param_dst
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitBH(
    HPDF_Destination dst,
    HPDF_REAL        top
);

/**

  \ingroup link
  \brief Define page appearance to fit page bounding box height within the window and set left position of page to value of \c left parameter.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitBV(
    HPDF_Destination dst,
    HPDF_REAL        left
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_DESTINATION_H */
