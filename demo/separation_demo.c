/*
 * << Haru Free PDF Library 2.0.0 >> -- separation_demo.c
 *
 * Copyright (c) 2024 Max Derhak
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
#include <math.h>
#include <setjmp.h>
#include "hpdf.h"

#if VSBUILD
#define DEMOFOLDER "..\\..\\..\\..\\demo\\"
#else
#define DEMOFOLDER
#endif

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

void
draw_tint_ramp (HPDF_Page    page,
                HPDF_ColorSpaceArray sep,
                float        x,
                float        y,
                const char  *text)
{
    int n;

    HPDF_Page_SetFontAndSize (page, HPDF_Page_GetCurrentFont (page), 8);
    HPDF_Page_SetRGBFill (page, 0, 0, 0);

    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x + 20, y - 12);
    HPDF_Page_ShowText (page, text);
    HPDF_Page_EndText (page);

    for (n=0; n<10; n++) {
      HPDF_Page_SetSepFill(page, sep, ((HPDF_REAL)n + 1.0) / 10.0);
      HPDF_Page_Rectangle(page, x+ n * 50, y, 45, 45);
      HPDF_Page_FillStroke(page);
    }
}


int main (int argc, char **argv)
{
    HPDF_Doc  pdf;
    HPDF_Font font;
    HPDF_Page page;
    HPDF_LabSpace lab_cs;
    HPDF_ColorSpaceArray sep;
    char fname[256];
    HPDF_Destination dst;

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    /* error-handler */
    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);

    /* create default-font */
    font = HPDF_GetFont (pdf, "Helvetica", NULL);

    /* add a new page object. */
    page = HPDF_AddPage (pdf);

    HPDF_Page_SetWidth (page, 550);
    HPDF_Page_SetHeight (page, 500);

    dst = HPDF_Page_CreateDestination (page);
    HPDF_Destination_SetXYZ (dst, 0, HPDF_Page_GetHeight (page), 1);
    HPDF_SetOpenAction(pdf, dst);

    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 20);
    HPDF_Page_MoveTextPos (page, 200, HPDF_Page_GetHeight (page) - 70);
    HPDF_Page_ShowText (page, "SeparationDemo");
    HPDF_Page_EndText (page);

    lab_cs = HPDF_NewLabSpace(pdf, 0.964203, 1.0, 0.824905);
    sep = HPDF_NewSepLabSpace(pdf, "Lab:50:-55:30", lab_cs, 50.0, -55.0, 30.0);
		draw_tint_ramp(page, sep, 25, HPDF_Page_GetHeight(page) - 150, "10% tints of CIELAB L*=50, a*=-55, b*=30");

    sep = HPDF_NewSepCmykSpace(pdf, "CMYK:100:75:0:0", 1.0, 0.75, 0.0, 0.0);
		draw_tint_ramp(page, sep, 25, HPDF_Page_GetHeight(page) - 250, "10% tints of Device CMYK C=100, M=75, Y=0, K=0");

    sep = HPDF_NewSepRgbSpace(pdf, "RGB:255:128:0", 1.0, 0.5, 0.0);
		draw_tint_ramp(page, sep, 25, HPDF_Page_GetHeight(page) - 350, "10% tints of Device RGB R=255, G=128, B=0");

    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
