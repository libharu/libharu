/*
 * << Haru Free PDF Library >> -- hpdf_consts.h
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


#ifndef _HPDF_CONSTS_H
#define _HPDF_CONSTS_H

#include "hpdf_types.h"

/*----------------------------------------------------------------------------*/

#define  HPDF_TRUE                  1
#define  HPDF_FALSE                 0

#define  HPDF_OK                    0
#define  HPDF_NOERROR               0

#define  HPDF_PI                    3.14159265358979323846

/*----- default values -------------------------------------------------------*/

/* buffer size which is required when we convert to character string. */
#define HPDF_TMP_BUF_SIZ            512
#define HPDF_SHORT_BUF_SIZ          32
#define HPDF_REAL_LEN               64
#define HPDF_INT_LEN                11
#define HPDF_TEXT_DEFAULT_LEN       256
#define HPDF_UNICODE_HEADER_LEN     2
#define HPDF_DATE_TIME_STR_LEN      23

/* length of each item defined in PDF */
#define HPDF_BYTE_OFFSET_LEN        10
#define HPDF_OBJ_ID_LEN             7
#define HPDF_GEN_NO_LEN             5

/* default value of Graphic State */
#define HPDF_DEF_FONT               "Helvetica"
#define HPDF_DEF_PAGE_LAYOUT        HPDF_PAGE_LAYOUT_SINGLE
#define HPDF_DEF_PAGE_MODE          HPDF_PAGE_MODE_USE_NONE
#define HPDF_DEF_WORDSPACE          0
#define HPDF_DEF_CHARSPACE          0
#define HPDF_DEF_FONTSIZE           10
#define HPDF_DEF_HSCALING           100
#define HPDF_DEF_LEADING            0
#define HPDF_DEF_RENDERING_MODE     HPDF_FILL
#define HPDF_DEF_RISE               0
#define HPDF_DEF_RAISE              HPDF_DEF_RISE
#define HPDF_DEF_LINEWIDTH          1
#define HPDF_DEF_LINECAP            HPDF_BUTT_END
#define HPDF_DEF_LINEJOIN           HPDF_MITER_JOIN
#define HPDF_DEF_MITERLIMIT         10
#define HPDF_DEF_FLATNESS           1
#define HPDF_DEF_PAGE_NUM           1

#define HPDF_BS_DEF_WIDTH           1

/* default page-size */
#define HPDF_DEF_PAGE_WIDTH         595.276F
#define HPDF_DEF_PAGE_HEIGHT        841.89F

/*---------------------------------------------------------------------------*/
/*----- compression mode ----------------------------------------------------*/

#define  HPDF_COMP_NONE            0x00
#define  HPDF_COMP_TEXT            0x01
#define  HPDF_COMP_IMAGE           0x02
#define  HPDF_COMP_METADATA        0x04
#define  HPDF_COMP_ALL             0x0F
/* #define  HPDF_COMP_BEST_COMPRESS   0x10
 * #define  HPDF_COMP_BEST_SPEED      0x20
 */
#define  HPDF_COMP_MASK            0xFF


/*----------------------------------------------------------------------------*/
/*----- permission flags (only Revision 2 is supported)-----------------------*/

#define HPDF_ENABLE_READ         0
#define HPDF_ENABLE_PRINT        4
#define HPDF_ENABLE_EDIT_ALL     8
#define HPDF_ENABLE_COPY         16
#define HPDF_ENABLE_EDIT         32


/*----------------------------------------------------------------------------*/
/*------ viewer preferences definitions --------------------------------------*/

#define HPDF_HIDE_TOOLBAR    1
#define HPDF_HIDE_MENUBAR    2
#define HPDF_HIDE_WINDOW_UI  4
#define HPDF_FIT_WINDOW      8
#define HPDF_CENTER_WINDOW   16
#define HPDF_PRINT_SCALING_NONE   32


/*---------------------------------------------------------------------------*/
/*------ limitation of object implementation (PDF1.4) -----------------------*/

#define HPDF_LIMIT_MAX_INT             2147483647
#define HPDF_LIMIT_MIN_INT             -2147483647

#define HPDF_LIMIT_MAX_REAL             3.4E38f // per PDF 1.7 spec, Annex C, old value  32767
#define HPDF_LIMIT_MIN_REAL            -3.4E38f // per PDF 1.7 spec, Annex C, old value -32767

#define HPDF_LIMIT_MAX_STRING_LEN      2147483646 // per PDF 1.7 spec, limit 32767 is for strings in content stream and no limit in other cases => open the limit to max Integer, old value 65535
#define HPDF_LIMIT_MAX_NAME_LEN        127

#define HPDF_LIMIT_MAX_ARRAY           8388607  // per PDF 1.7 spec, "Maximum number of indirect objects in a PDF file" is 8388607, old value 8191
#define HPDF_LIMIT_MAX_DICT_ELEMENT    8388607  // per PDF 1.7 spec, "Maximum number of indirect objects in a PDF file" is 8388607, old value 4095
#define HPDF_LIMIT_MAX_XREF_ELEMENT    8388607
#define HPDF_LIMIT_MAX_GSTATE          28
#define HPDF_LIMIT_MAX_DEVICE_N        8
#define HPDF_LIMIT_MAX_DEVICE_N_V15    32
#define HPDF_LIMIT_MAX_CID             65535
#define HPDF_MAX_GENERATION_NUM        65535

#define HPDF_MIN_MAGNIFICATION_FACTOR   0.08 // 8 percent
#define HPDF_MAX_MAGNIFICATION_FACTOR  64.00 // 6400 percent

/*---------------------------------------------------------------------------*/
/*------ limitation of various properties -----------------------------------*/

/// Minimal page size in user units according to PDF standard
#define HPDF_MIN_PAGE_MEASURE       3

/// Maximal page size in user units according to PDF standard
#define HPDF_MAX_PAGE_MEASURE       14400

#define HPDF_MIN_HORIZONTALSCALING  10
#define HPDF_MAX_HORIZONTALSCALING  300
#define HPDF_MIN_WORDSPACE          -30
#define HPDF_MAX_WORDSPACE          300
#define HPDF_MIN_CHARSPACE          -30
#define HPDF_MAX_CHARSPACE          300
#define HPDF_MAX_FONTSIZE           600
#define HPDF_MAX_ZOOMSIZE           10
#define HPDF_MAX_LEADING            300
#define HPDF_MAX_LINEWIDTH          100
#define HPDF_MAX_DASH_PATTERN       100

#define HPDF_MAX_JWW_NUM            128

static const HPDF_TransMatrix IDENTITY_MATRIX = {1, 0, 0, 1, 0, 0};
static const HPDF_RGBColor DEF_RGB_COLOR = {0, 0, 0};
static const HPDF_CMYKColor DEF_CMYK_COLOR = {0, 0, 0, 0};
static const HPDF_DashMode DEF_DASH_MODE = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0, 0.0f};

/*----------------------------------------------------------------------------*/
/*----- Graphics mode --------------------------------------------------------*/

#define   HPDF_GMODE_PAGE_DESCRIPTION       0x0001
#define   HPDF_GMODE_PATH_OBJECT            0x0002
#define   HPDF_GMODE_TEXT_OBJECT            0x0004
#define   HPDF_GMODE_CLIPPING_PATH          0x0008
#define   HPDF_GMODE_SHADING                0x0010
#define   HPDF_GMODE_INLINE_IMAGE           0x0020
#define   HPDF_GMODE_EXTERNAL_OBJECT        0x0040


/*----------------------------------------------------------------------------*/
/**
  \brief Predefined value for calculations with millimeters. Equals to 72.0/25.4 (72 points pre inch per mm).
*/
#define HPDF_MM                             2.834646

/**
  \brief Predefined value for calculations with inches
*/
#define HPDF_IN                             72.00000

#endif /* _HPDF_CONSTS_H */
