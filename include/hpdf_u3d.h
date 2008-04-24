/*
 * << Haru Free PDF Library 2.0.3 >> -- hpdf_u3d.h
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#ifndef _HPDF_U3D_H
#define _HPDF_U3D_H

#include "hpdf_objects.h"

#ifdef __cplusplus
extern "C" {
#endif

HPDF_EXPORT(HPDF_U3D)
HPDF_LoadU3DFromFile  ( HPDF_Doc     pdf,
		                const char  *filename);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_U3D_H */

