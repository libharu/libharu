/*
 * << Haru Free PDF Library >> -- hpdf_color_spaces.h
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

#ifndef _HPDF_COLOR_SPACES_H
#define _HPDF_COLOR_SPACES_H

#include "hpdf_objects.h"

#ifdef __cplusplus
extern "C" {
#endif

HPDF_ColorSpaceObj
HPDF_New_IccBasedSpace (HPDF_MMgr        mmgr,
				                HPDF_UINT        profile_size,
	                      unsigned char   *profile_buf,
                        HPDF_UINT *      num_sample,
                        HPDF_ColorSpace* color_space,
                        HPDF_Xref        xref);

HPDF_LabSpace
HPDF_New_LabSpace  (HPDF_MMgr        mmgr,
                    HPDF_REAL        white_x,
                    HPDF_REAL        white_y,
                    HPDF_REAL        white_z,
                    HPDF_Xref        xref);


HPDF_ColorSpaceObj
HPDF_New_SepLabSpace (HPDF_MMgr        mmgr,
                      const char      *sep_name,
                      HPDF_LabSpace    lab_space,
				              HPDF_REAL        sep_L,
                      HPDF_REAL        sep_a,
                      HPDF_REAL        sep_b,
                      HPDF_Xref        xref);

HPDF_ColorSpaceObj
HPDF_New_SepCmykSpace (HPDF_MMgr        mmgr,
                       const char      *sep_name,
                       HPDF_REAL        sep_C,
                       HPDF_REAL        sep_M,
                       HPDF_REAL        sep_Y,
                       HPDF_REAL        sep_K,
                       HPDF_Xref        xref);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_COLOR_SPACES_H */

