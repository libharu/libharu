/*
 * << Haru Free PDF Library 2.0.0 >> -- handler.h
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2007-2009 Antony Dovgal et al.
 * Copyright (c) 2023 Dmitry Solomennikov
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#ifndef __HANDLER_H
#define __HANDLER_H

#include "hpdf.h"
#include <setjmp.h>

HPDF_HANDLER(void)
demo_error_handler  (HPDF_STATUS   error_no,
                     HPDF_STATUS   detail_no,
                     void         *user_data);

static jmp_buf env;

#endif /* __HANDLER_H */
