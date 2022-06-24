###
## * << Haru Free PDF Library 2.0.0 >> -- ttfont_demo.c
## *
## * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
## *
## * Permission to use, copy, modify, distribute and sell this software
## * and its documentation for any purpose is hereby granted without fee,
## * provided that the above copyright notice appear in all copies and
## * that both that copyright notice and this permission notice appear
## * in supporting documentation.
## * It is provided "as is" without express or implied warranty.
## *
##

## port to python by Li Jun
## http://groups.google.com/group/pythoncia

import os, sys

from ctypes import *
up=2
def setlibpath(up):
    import sys
    path=os.path.normpath(os.path.split(os.path.realpath(__file__))[0]+'\..'*up)
    if path not in sys.path:
        sys.path.append(path)

setlibpath(up)

from haru import *
from haru.c_func import *
from haru.hpdf_errorcode import *


@HPDF_Error_Handler(None, HPDF_UINT, HPDF_UINT, c_void_p)
def error_handler (error_no, detail_no, user_data):
    global pdf
    printf ("ERROR: %s, detail_no=%u\n", error_detail[error_no],
                detail_no)
    HPDF_Free (pdf)
    sys.exit(1)


def main ():
    global pdf

    SAMP_TXT = "The quick brown fox jumps over the lazy dog."

    if (len(sys.argv) < 2):
        printf("usage: ttfont_demo [path to font file] "
                "-E(embedding font).\n")
        return 1

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    # Add a new page object.
    page = HPDF_AddPage (pdf)

    title_font = HPDF_GetFont (pdf, "Helvetica", NULL)

    if (len(sys.argv) > 2 and sys.argv[2]=="-E"):
        embed = HPDF_TRUE
    else:
        embed = HPDF_FALSE

    detail_font_name = HPDF_LoadTTFontFromFile (pdf, sys.argv[1], embed)

    detail_font = HPDF_GetFont (pdf, detail_font_name, NULL)

    HPDF_Page_SetFontAndSize (page, title_font, 10)

    HPDF_Page_BeginText (page)

    # Move the position of the text to top of the page.
    HPDF_Page_MoveTextPos(page, 10, 190)
    HPDF_Page_ShowText (page, detail_font_name)

    if (embed):
        HPDF_Page_ShowText (page, "(Embedded Subset)")

    HPDF_Page_SetFontAndSize (page, detail_font, 15)
    HPDF_Page_MoveTextPos (page, 10, -20)
    HPDF_Page_ShowText (page, "abcdefghijklmnopqrstuvwxyz")
    HPDF_Page_MoveTextPos (page, 0, -20)
    HPDF_Page_ShowText (page, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    HPDF_Page_MoveTextPos (page, 0, -20)
    HPDF_Page_ShowText (page, "1234567890")
    HPDF_Page_MoveTextPos (page, 0, -20)

    HPDF_Page_SetFontAndSize (page, detail_font, 10)
    HPDF_Page_ShowText (page, SAMP_TXT)
    HPDF_Page_MoveTextPos (page, 0, -18)

    HPDF_Page_SetFontAndSize (page, detail_font, 16)
    HPDF_Page_ShowText (page, SAMP_TXT)
    HPDF_Page_MoveTextPos (page, 0, -27)

    HPDF_Page_SetFontAndSize (page, detail_font, 23)
    HPDF_Page_ShowText (page, SAMP_TXT)
    HPDF_Page_MoveTextPos (page, 0, -36)

    HPDF_Page_SetFontAndSize (page, detail_font, 30)
    HPDF_Page_ShowText (page, SAMP_TXT)
    HPDF_Page_MoveTextPos (page, 0, -36)

    pw = HPDF_Page_TextWidth (page, SAMP_TXT)
    page_height = 210
    page_width = pw + 40

    HPDF_Page_SetWidth (page, page_width)
    HPDF_Page_SetHeight (page, page_height)

    # Finish to print text.
    HPDF_Page_EndText (page)

    HPDF_Page_SetLineWidth (page, 0.5)

    HPDF_Page_MoveTo (page, 10, page_height - 25)
    HPDF_Page_LineTo (page, page_width - 10, page_height - 25)
    HPDF_Page_Stroke (page)

    HPDF_Page_MoveTo (page, 10, page_height - 85)
    HPDF_Page_LineTo (page, page_width - 10, page_height - 85)
    HPDF_Page_Stroke (page)

    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()