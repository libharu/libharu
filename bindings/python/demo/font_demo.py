###
## * << Haru Free PDF Library 2.0.0 >> -- font_demo.c
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

from math import *


global pdf

@HPDF_Error_Handler(None, HPDF_UINT, HPDF_UINT, c_void_p)
def error_handler (error_no, detail_no, user_data):
    global pdf
    printf ("ERROR: error_no=%04X, detail_no=%u\n", error_no,
                detail_no)
    HPDF_Free (pdf)
    sys.exit(1)


font_list=[
    "Courier",
    "Courier-Bold",
    "Courier-Oblique",
    "Courier-BoldOblique",
    "Helvetica",
    "Helvetica-Bold",
    "Helvetica-Oblique",
    "Helvetica-BoldOblique",
    "Times-Roman",
    "Times-Bold",
    "Times-Italic",
    "Times-BoldItalic",
    "Symbol",
    "ZapfDingbats",
]

def main ():
    global pdf

    page_title = "Font Demo"

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1


    # Add a new page object.
    page = HPDF_AddPage (pdf)

    height = HPDF_Page_GetHeight (page)
    width = HPDF_Page_GetWidth (page)

    # Print the lines of the page.
    HPDF_Page_SetLineWidth (page, 1)
    HPDF_Page_Rectangle (page, 50, 50, width - 100, height - 110)
    HPDF_Page_Stroke (page)

    # Print the title of the page (with positioning center).
    def_font = HPDF_GetFont (pdf, "Helvetica", NULL)
    HPDF_Page_SetFontAndSize (page, def_font, 24)

    tw = HPDF_Page_TextWidth (page, page_title)
    HPDF_Page_BeginText (page)
    HPDF_Page_TextOut (page, (width - tw) / 2, height - 50, page_title)
    HPDF_Page_EndText (page)

    # output subtitle.
    HPDF_Page_BeginText (page)
    HPDF_Page_SetFontAndSize (page, def_font, 16)
    HPDF_Page_TextOut (page, 60, height - 80, "<Standerd Type1 fonts samples>")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, 60, height - 105)

    for i in font_list:
        samp_text = "abcdefgABCDEFG12345!#$%&+-@?"

        #font_name = HPDF_LoadTTFontFromFile (pdf, "c:/winnt/fonts/arial.ttf", HPDF_TRUE);

        #font_name='arial.ttf'
        #font = HPDF_GetFont (pdf, font_name, "CP1250");

        #font = HPDF_GetFont (pdf, "Helvetica", NULL)

        font = HPDF_GetFont (pdf, i, NULL)

        # print a label of text
        HPDF_Page_SetFontAndSize (page, def_font, 9)
        HPDF_Page_ShowText (page, i)
        HPDF_Page_MoveTextPos (page, 0, -18)

        # print a sample text.
        HPDF_Page_SetFontAndSize (page, font, 20)
        HPDF_Page_ShowText (page, samp_text)
        HPDF_Page_MoveTextPos (page, 0, -20)


    HPDF_Page_EndText (page)

    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()