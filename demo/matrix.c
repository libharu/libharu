/*
 * << Haru Free PDF Library 2.4.4 >> -- matrix.c
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
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

/**
  \par Matrix transformations combined demo program.

  This program shows usage of matrix multiplication.
  It allows to produce some delayed and combined calculations on matrices.

  Please pay attention, matrix combination operations and page operations
  are in reverse order to each other.
*/ 
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "hpdf_utils.h"
#include "handler.h"

int
main (int argc, char **argv)
{
    HPDF_Doc  pdf;
    HPDF_Page page;
    char fname[256];

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    /* create document object*/
    pdf = HPDF_New (demo_error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    /* add a new page object. */
    page = HPDF_AddPage (pdf);

    /* set up added page */
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);

    /* draw line using page transformation */

    HPDF_Page_GSave (page);

    HPDF_Page_Translate (page, 25*HPDF_MM, 50*HPDF_MM);
    HPDF_Page_Scale (page, 0.5, 0.5);
    HPDF_Page_Rotate (page, -35*HPDF_PI/180);
    HPDF_Page_Translate (page, 0*HPDF_MM, -25*HPDF_MM);

    HPDF_Page_MoveTo (page, 0, 0);
    HPDF_Page_LineTo (page, 0*HPDF_MM, 50*HPDF_MM);
    HPDF_Page_Stroke (page);

    HPDF_Page_GRestore (page);

    /* draw line using matrix calculation */

    HPDF_Page_GSave (page);
    HPDF_TransMatrix r = IDENTITY_MATRIX;

    r = HPDF_Matrix_Translate(r, 0*HPDF_MM, -25*HPDF_MM);
    r = HPDF_Matrix_RotateDeg (r, -45);
    r = HPDF_Matrix_Scale (r, 0.5, 0.5);
    r = HPDF_Matrix_Translate(r, 25*HPDF_MM, 25*HPDF_MM);

    HPDF_Page_Concat (page, r.a, r.b, r.c, r.d, r.x, r.y);

    HPDF_Page_MoveTo (page, 0, 0);
    HPDF_Page_LineTo (page, 0, 50*HPDF_MM);
    HPDF_Page_Stroke (page);

    HPDF_Page_GRestore (page);

    /* draw center rectangles */
    HPDF_Page_GSave (page);
    HPDF_Page_Rectangle (page, 25*HPDF_MM-2.5, 25*HPDF_MM-2.5, 5, 5);
    HPDF_Page_Stroke (page);

    HPDF_Page_Rectangle (page, 25*HPDF_MM-2.5, 50*HPDF_MM-2.5, 5, 5);
    HPDF_Page_Stroke (page);
    HPDF_Page_GRestore (page);

    /* save document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
