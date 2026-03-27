/*
 * << Haru Free PDF Library 2.0.0 >> -- page_sizes_demo.c
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "handler.h"
#include "utils.h"
#include "hpdf_utils.h"

/**

  \par All available page sizes demo.

  This demo creates PDF file, feed it with pages of all sizes from \ref HPDF_PageSizes enumeration.
  For every page outline is created with the name of a page size from \ref HPDF_PageSizeName.
*/

int main (int argc, char **argv)
{
    HPDF_Doc  pdf;
    char fname[256];
    HPDF_PageSizes i = HPDF_PAGE_SIZE_US_LETTER;
    HPDF_Outline root;

    pdf = HPDF_NewEx (demo_error_handler, NULL, NULL, 0, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    /* Set page mode to use outlines. */
    HPDF_SetPageMode(pdf, HPDF_PAGE_MODE_USE_THUMBS);

    /* create outline root. */
    root = HPDF_CreateOutline (pdf, NULL, "Page sizes list", NULL);
    HPDF_Outline_SetOpened (root, HPDF_TRUE);

    while (i < HPDF_PAGE_SIZE_EOF) {
        printf("Processing %s...\n", HPDF_PageSizeName (i));
        HPDF_Page page = HPDF_AddPage (pdf);
        HPDF_Outline outline;
        HPDF_Destination dst;

        HPDF_Page_SetSize (page, i, HPDF_PAGE_PORTRAIT);

        outline = HPDF_CreateOutline (pdf, root, HPDF_PageSizeName (i), NULL);
        dst = HPDF_Page_CreateDestination (page);
        HPDF_Destination_SetXYZ(dst, 0, HPDF_Page_GetHeight(page), 1);
        HPDF_Outline_SetDestination(outline, dst);

        i++;
    }

    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
