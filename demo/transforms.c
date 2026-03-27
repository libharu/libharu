/*
 * << Haru Free PDF Library 2.4.4 >> -- transforms.c
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
  \par Transformation helper functions

  This program show usage of helper functions for coordinate system transformations.
  It creates transformation matrices for translate, scale, rotate and skew.
  For this purpose it uses HPDF_Page_Translate(), HPDF_Page_Scale(), HPDF_Page_Rotate()
  and HPDF_Page_Skew() respectively.

  Internally all these functions use HPDF_Page_Concat() for transformation matrix manipulation.
*/
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "handler.h"

const HPDF_REAL rect_height =  50*HPDF_MM;
const HPDF_REAL rect_width  =  50*HPDF_MM;
const HPDF_REAL line_width  = 0.2*HPDF_MM;
const HPDF_REAL font_size   = 14;

const char *captions[] = {
    "Translate",
    "Scale",
    "Rotate",
    "Skew",
    "Combined"
};

/* Draw original rectangle */
void draw_rect (HPDF_Page page)
{
    HPDF_Page_SetLineWidth (page, line_width);
    HPDF_Page_SetRGBStroke (page, 0, 0, 0);
    HPDF_Page_SetDash (page, NULL, 0, 0);
    HPDF_Page_Rectangle (page, 0, 0, rect_width, rect_height);
    HPDF_Page_Stroke (page);
}

/* Draw rectangle after transformation */
void draw_transformed (HPDF_Page page)
{
    HPDF_Page_SetLineWidth (page, line_width);
    HPDF_Page_SetRGBStroke (page, 1.0, 0, 1.0);
    const HPDF_REAL dash[] = {7};
    HPDF_Page_SetDash (page, dash, 1, 1);
    HPDF_Page_Rectangle (page, 0, 0, rect_width, rect_height);
    HPDF_Page_Stroke (page);
}

/* Draw transformation caption */
void draw_caption (HPDF_Page page, int index)
{
    HPDF_Page_BeginText (page);
    HPDF_Page_TextOut (page, 0, -1.5*font_size, captions[index]);
    HPDF_Page_EndText (page);
}

int
main (int argc, char **argv)
{
    HPDF_Doc  pdf;
    HPDF_Page page;
    HPDF_Font font;
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

    /* create default-font */
    font = HPDF_GetFont (pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize (page, font, font_size);

    /* calculate rectangles positions */
    HPDF_REAL page_height = HPDF_Page_GetHeight (page);

    HPDF_REAL x[] = {20*HPDF_MM,
                     90*HPDF_MM,
                     20*HPDF_MM,
                     90*HPDF_MM,
                    160*HPDF_MM};

    HPDF_REAL y[] = {page_height - rect_height - 20*HPDF_MM,
                     page_height - rect_height - 20*HPDF_MM,
                     page_height - rect_height - 90*HPDF_MM,
                     page_height - rect_height - 90*HPDF_MM,
                     page_height - rect_height - 90*HPDF_MM};

    /* translate transformation */
    HPDF_Page_GSave (page);

    HPDF_Page_Translate (page, x[0], y[0]);

    HPDF_Page_GSave (page);
    draw_rect (page);

    HPDF_Page_Translate (page, 5*HPDF_MM, 5*HPDF_MM);

    draw_transformed (page);
    HPDF_Page_GRestore (page);

    draw_caption (page, 0);

    HPDF_Page_GRestore (page);


    /* scale transformation */
    HPDF_Page_GSave (page);

    HPDF_Page_Translate (page, x[1], y[1]);

    HPDF_Page_GSave (page);
    draw_rect (page);

    HPDF_Page_Scale (page, 0.8, 1.2);

    draw_transformed (page);
    HPDF_Page_GRestore (page);

    draw_caption (page, 1);

    HPDF_Page_GRestore (page);

    /* rotate transformation */
    HPDF_Page_GSave (page);

    HPDF_Page_Translate (page, x[2], y[2]);

    HPDF_Page_GSave (page);
    draw_rect (page);

    HPDF_Page_Rotate (page, HPDF_PI/20);

    draw_transformed (page);
    HPDF_Page_GRestore (page);

    draw_caption (page, 2);

    HPDF_Page_GRestore (page);

    /* skew transformation */
    HPDF_Page_GSave (page);

    HPDF_Page_Translate (page, x[3], y[3]);

    HPDF_Page_GSave (page);
    draw_rect (page);

    HPDF_Page_Skew (page, HPDF_PI/20, HPDF_PI/20);

    draw_transformed (page);
    HPDF_Page_GRestore (page);

    draw_caption (page, 3);

    HPDF_Page_GRestore (page);

    /* combined transformation */
    HPDF_Page_GSave (page);

    HPDF_Page_Translate (page, x[4], y[4]);

    HPDF_Page_GSave (page);
    draw_rect (page);

    HPDF_Page_Skew (page, HPDF_PI/20, HPDF_PI/20);
    HPDF_Page_Scale (page, 0.8, 1.2);
    HPDF_Page_Rotate (page, HPDF_PI/20);
    HPDF_Page_Translate (page, 5*HPDF_MM, 5*HPDF_MM);

    draw_transformed (page);
    HPDF_Page_GRestore (page);

    draw_caption (page, 4);

    HPDF_Page_GRestore (page);

    /* save document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
