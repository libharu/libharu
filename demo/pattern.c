/*
 * << Haru Free PDF Library 2.4.4 >> -- pattern.c
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
  \par PDF dictionaries, arrays and tiling patterns demo

  This demo shows usage of PDF dictionaries and arrays.
  PDF tiling pattern is created by feeding corresponding dictionaries.
  Dictionary can have stream within, in this case it is created using
  HPDF_DictStream_New() function, otherwise HPDF_Dict_New() should be called.

  Library automatically calculates cross-references when array inserted to dictionary
  or dictionary inserted to dictionary etc.

  Also, some items are inserted to page's "Resources" dictionary.
  It is done using HPDF_Page_GetInheritableItem() function.
*/

#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
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

    HPDF_Dict csDict = HPDF_Dict_New (pdf->mmgr);
    HPDF_Array array = HPDF_Array_New (csDict->mmgr);
    HPDF_Array_AddName (array, "Pattern");
    HPDF_Array_AddName (array, "DeviceRGB");
    HPDF_Dict_Add (csDict, "pgcs", array);

    HPDF_Xref_Add (pdf->xref, csDict);

    HPDF_Dict patDict = HPDF_DictStream_New (pdf->mmgr, pdf->xref);
    HPDF_Dict_AddName (patDict, "Type", "Pattern");
    HPDF_Dict_AddNumber (patDict, "PatternType", 1);
    HPDF_Dict_AddNumber (patDict, "PaintType", 2);
    HPDF_Dict_AddNumber (patDict, "TilingType", 1);
    HPDF_Dict_AddReal (patDict, "XStep", 9.96277);
    HPDF_Dict_AddReal (patDict, "YStep", 9.96277);

    HPDF_Stream_WriteStr (
        patDict->stream, 
        "q 0.49814 w -0.09962 -0.09962 m 10.0624 10.0624 l -0.09962 10.0624 m 10.0624 -0.09962 l S Q");

    HPDF_Array b = HPDF_Array_New (patDict->mmgr);
    HPDF_Array_AddReal (b, -0.09962);
    HPDF_Array_AddReal (b, -0.09962);
    HPDF_Array_AddReal (b, 10.0624);
    HPDF_Array_AddReal (b, 10.0624);

    HPDF_Dict_Add (patDict, "BBox", b);

    HPDF_Array m = HPDF_Array_New (patDict->mmgr);

    HPDF_Array_AddReal (m, 0.93358);
    HPDF_Array_AddReal (m, 0.35837);
    HPDF_Array_AddReal (m, -0.35837);
    HPDF_Array_AddReal (m, 0.93358);
    HPDF_Array_AddReal (m, 0.0);
    HPDF_Array_AddReal (m, 0.0);

    HPDF_Dict_Add (patDict, "Matrix", m);

    // When HPDF_DictStream_New() function is used,
    // it is not necessary to add patDict to page's xref directly.
    //
    // HPDF_Xref_Add (pdf->xref, patDict);

    HPDF_Dict patNames = HPDF_Dict_New (pdf->mmgr);
    HPDF_Dict_Add (patNames, "hatch1", patDict);

    HPDF_Dict resources = HPDF_Page_GetInheritableItem (page, "Resources", HPDF_OCLASS_DICT);

    HPDF_Dict_Add (resources, "ColorSpace", csDict);
    HPDF_Dict_Add (resources, "Pattern", patNames);

    HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;
    HPDF_Stream_WriteStr (attr->stream, "/pgcs cs 0 0 1 /hatch1 scn ");

    HPDF_REAL width = HPDF_Page_GetWidth (page);
    HPDF_REAL height = HPDF_Page_GetHeight (page);

    HPDF_REAL margin = 15*HPDF_MM;

    HPDF_Page_Rectangle (page, margin, margin, width - margin*2, height - margin*2);
    HPDF_Page_Fill (page);

    /* save document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
