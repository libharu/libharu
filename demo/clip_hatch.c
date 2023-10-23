/*
 * << Haru Free PDF Library 2.4.4 >> -- minimal.c
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
  \par Clipping path demo program

  This program create hatch pattern using lines, page transform (rotation) and clipping path.

  Clipping path is created using HPDF_Page_Rectangle() function. In order to make clipping work
  properly, HPDF_Page_EndPath() function \a must be called right after clip.

*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <setjmp.h>
#include "hpdf.h"
#include "handler.h"

void
hatch (HPDF_Doc    pdf,
       HPDF_Page   page)
{
    HPDF_REAL height = HPDF_Page_GetHeight (page);
    HPDF_REAL width = HPDF_Page_GetWidth (page);
    HPDF_REAL x = 0.0;

    HPDF_Page_GSave (page);

    HPDF_Page_Rectangle (page, 0, 0, width, 15 * HPDF_MM);
    HPDF_Page_Clip (page);
    HPDF_Page_EndPath (page);

    HPDF_Page_GSave (page);

    HPDF_Page_SetRGBStrokeHex (page, 0x55, 0x77, 0x22);
    HPDF_Page_SetLineWidth (page, 0.25 * HPDF_MM);
    HPDF_REAL angle1 = -45;
    HPDF_REAL rad1 = angle1 / 180 * 3.141592;

    HPDF_Page_Concat (page, cos(rad1), sin(rad1), -sin(rad1), cos(rad1), -15*HPDF_MM, 0);

    while (x < width) {
        HPDF_Page_MoveTo (page, x, 0);
        HPDF_Page_LineTo (page, x, height);
        HPDF_Page_Stroke (page);
        x += HPDF_MM;
    }

    HPDF_Page_GRestore (page);
    HPDF_Page_GRestore (page);
}

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
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    hatch (pdf, page);

    /* save document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
