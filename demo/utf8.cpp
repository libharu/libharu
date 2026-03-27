/*
 * << Haru Free PDF Library 2.4.4 >> -- utf8.c
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
  \par Multi-byte UTF-8 example (C++)

  This is an UTF-8 example for multi-byte encoded text.
  It is important to have font with appropriate characters (Chinese in this example).
  <a href="https://fonts.google.com/noto/specimen/Noto+Sans">Noto Sans</a> font is used here.

  Comparing to \example utf8.c, this file is written in C++ with direct usage of C library.
*/
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "handler.h"

#include <string>

int
main (int argc, char **argv)
{
    HPDF_Doc  pdf;
    HPDF_Page page;
    HPDF_ExtGState gstate;
    char fname[256];

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    /* create document object*/
    pdf = HPDF_New (demo_error_handler, NULL);

    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    try {
        page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
        HPDF_Font font;
        const char *font_name;

        HPDF_UseUTFEncodings (pdf);
        HPDF_SetCurrentEncoder (pdf, "UTF-8");
        font_name = HPDF_LoadTTFontFromFile (pdf, "ttfont/NotoSansSC-Regular.ttf", HPDF_TRUE);
        font = HPDF_GetFont (pdf, font_name, "UTF-8");
        HPDF_Page_SetFontAndSize (page, font, 36);

        HPDF_Page_GSave (page);
        gstate = HPDF_CreateExtGState (pdf);
        HPDF_ExtGState_SetAlphaFill (gstate, 0.4);
        HPDF_Page_SetExtGState (page, gstate);
        HPDF_Page_SetRGBFill(page, 0,0,0.7);

        HPDF_Page_BeginText(page);

        std::string textCyrillic("Привет, мир!");
        std::string textEspanol("Peña, ¿cómo va, mundo?");
        std::string textChinese("你好，世界！");

        HPDF_Page_MoveTextPos(page, 100, 100);
        HPDF_Page_ShowText(page, textCyrillic.c_str());
        HPDF_Page_MoveTextPos(page, 0, 100);
        HPDF_Page_ShowText(page, textEspanol.c_str());
        HPDF_Page_MoveTextPos(page, 0, 100);
        HPDF_Page_ShowText(page, textChinese.c_str());

        HPDF_Page_EndText(page);
        HPDF_Page_GRestore (page);

        HPDF_SaveToFile(pdf, fname);
    }
    catch (...) {
        HPDF_Free (pdf);
        return 1;
    }

    HPDF_Free (pdf);
    return 0;
}
