/*
 * << Haru Free PDF Library 2.4.4 >> -- pattern2.c
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
  \par Multiple dictionaries, arrays and matrix demo

  This demo shows usage of PDF dictionaries and arrays and matrix transformation.
  PDF tiling pattern is created by feeding corresponding dictionaries.
  Dictionary can have stream within, in this case it is created using
  HPDF_DictStream_New() function, otherwise HPDF_Dict_New() should be called.

  Library automatically calculates cross-references when array inserted to dictionary
  or dictionary inserted to dictionary etc.

  Also, some items are inserted to page's "Resources" dictionary.
  It is done using HPDF_Page_GetInheritableItem() function.

  Pattern transformation matrix is calculated using set of utility functions:
  HPDF_Matrix_Scale() and HPDF_Matrix_RotateDeg().
*/

#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "hpdf_utils.h"
#include "handler.h"

static const HPDF_REAL cellWidth = HPDF_MM*2;
static const HPDF_REAL lineWidth = HPDF_MM*0.1;

/* pattern creation routine */
HPDF_Dict
createPattern (HPDF_Doc pdf, HPDF_REAL degrees, HPDF_REAL scale)
{
    /* create dictionary with writable stream */
    HPDF_Dict patDict = HPDF_DictStream_New (pdf->mmgr, pdf->xref);
    HPDF_Dict_AddName (patDict, "Type", "Pattern");
    HPDF_Dict_AddNumber (patDict, "PatternType", 1);
    HPDF_Dict_AddNumber (patDict, "PaintType", 2);
    HPDF_Dict_AddNumber (patDict, "TilingType", 1);
    HPDF_Dict_AddReal (patDict, "XStep", cellWidth);
    HPDF_Dict_AddReal (patDict, "YStep", cellWidth);

    char patternData[200];

    HPDF_REAL cellWidth_4 = cellWidth / 4;
    HPDF_REAL cellWidth_34 = cellWidth / 4 * 3;

    sprintf(patternData, "q %f w %f 0 m %f %f l %f 0 m %f %f l S Q", lineWidth, cellWidth_4, cellWidth_4, cellWidth, cellWidth_34, cellWidth_34, cellWidth);
    /* write simple pattern directly with PDF language */
    HPDF_Stream_WriteStr (patDict->stream, (const char*)&patternData);

    /* setup pattern bounding box */
    HPDF_Array b = HPDF_Array_New (patDict->mmgr);
    HPDF_Array_AddReal (b, 0);
    HPDF_Array_AddReal (b, 0);
    HPDF_Array_AddReal (b, cellWidth);
    HPDF_Array_AddReal (b, cellWidth);

    HPDF_Dict_Add (patDict, "BBox", b);

    /* prepare pattern transformation */
    HPDF_TransMatrix r = IDENTITY_MATRIX;
    r = HPDF_Matrix_RotateDeg (r, degrees);
    r = HPDF_Matrix_Scale (r, scale, scale);

    /* setup pattern transformation matrix */
    HPDF_Array matrixArray = HPDF_Array_New (patDict->mmgr);
    HPDF_Array_AddReal (matrixArray, r.a);
    HPDF_Array_AddReal (matrixArray, r.b);
    HPDF_Array_AddReal (matrixArray, r.c);
    HPDF_Array_AddReal (matrixArray, r.d);
    HPDF_Array_AddReal (matrixArray, r.x);
    HPDF_Array_AddReal (matrixArray, r.y);

    HPDF_Dict_Add (patDict, "Matrix", matrixArray);

    /* return pattern handle */
    return patDict;
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
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);

    /* set up pattern color space dictionary */
    HPDF_Dict csDict = HPDF_Dict_New (pdf->mmgr);
    HPDF_Array array = HPDF_Array_New (csDict->mmgr);
    HPDF_Array_AddName (array, "Pattern");
    HPDF_Array_AddName (array, "DeviceRGB");
    HPDF_Dict_Add (csDict, "pgcs", array);
    HPDF_Xref_Add (pdf->xref, csDict);

    /* create dictionary holding pattern definitions */
    HPDF_Dict patNames = HPDF_Dict_New (pdf->mmgr);

    HPDF_Dict originalPat = createPattern (pdf, 0, 1.0);
    HPDF_Dict scaledPat = createPattern (pdf, 0, 0.2);
    HPDF_Dict rotatedPat = createPattern (pdf, 70, 1.7);

    /* add patterns to definition dictionary */
    HPDF_Dict_Add (patNames, "hatch1", originalPat);
    HPDF_Dict_Add (patNames, "hatch2", scaledPat);
    HPDF_Dict_Add (patNames, "hatch3", rotatedPat);

    /* add color space and pattern dictionaries to page's description */
    HPDF_Dict resources = HPDF_Page_GetInheritableItem (page, "Resources", HPDF_OCLASS_DICT);
    HPDF_Dict_Add (resources, "ColorSpace", csDict);
    HPDF_Dict_Add (resources, "Pattern", patNames);

    HPDF_REAL width = HPDF_Page_GetWidth (page);
    HPDF_REAL height = HPDF_Page_GetHeight (page);
    HPDF_REAL margin = 15*HPDF_MM;
    HPDF_REAL rectWidth = (width - margin*2)/3;

    /* first rectangle */
    HPDF_Page_GSave (page);
    HPDF_Page_RawWrite (page, "/pgcs cs 0 0 1 /hatch1 scn ");
    HPDF_Page_Rectangle (page, margin, margin, rectWidth, height - margin*2);
    HPDF_Page_Fill (page);
    HPDF_Page_GRestore (page);

    /* second rectangle */
    HPDF_Page_GSave (page);
    HPDF_Page_RawWrite (page, "/pgcs cs 0 0 1 /hatch2 scn ");
    HPDF_Page_Rectangle (page, margin+rectWidth, margin, rectWidth, height - margin*2);
    HPDF_Page_Fill (page);
    HPDF_Page_GRestore (page);

    /* third rectangle */
    HPDF_Page_GSave (page);
    HPDF_Page_RawWrite (page, "/pgcs cs 0 0 1 /hatch3 scn ");
    HPDF_Page_Rectangle (page, margin+rectWidth+rectWidth, margin, rectWidth, height - margin*2);
    HPDF_Page_Fill (page);
    HPDF_Page_GRestore (page);

    /* save document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
