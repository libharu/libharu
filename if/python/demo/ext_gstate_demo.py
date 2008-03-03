###
## * << Haru Free PDF Library 2.0.0 >> -- ext_gstate_demo.c
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


def draw_circles (page, description, x, y):
    HPDF_Page_SetLineWidth (page, 1.0)
    HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0)
    HPDF_Page_SetRGBFill (page, 1.0, 0.0, 0.0)
    HPDF_Page_Circle (page, x + 40, y + 40, 40)
    HPDF_Page_ClosePathFillStroke (page)
    HPDF_Page_SetRGBFill (page, 0.0, 1.0, 0.0)
    HPDF_Page_Circle (page, x + 100, y + 40, 40)
    HPDF_Page_ClosePathFillStroke (page)
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 1.0)
    HPDF_Page_Circle (page, x + 70, y + 74.64, 40)
    HPDF_Page_ClosePathFillStroke (page)

    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0)
    HPDF_Page_BeginText (page)
    HPDF_Page_TextOut (page, x + 0.0, y + 130.0, description)
    HPDF_Page_EndText (page)


def main ():
    global pdf

    PAGE_WIDTH = 600
    PAGE_HEIGHT = 900

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    hfont = HPDF_GetFont (pdf, "Helvetica-Bold", NULL)

    # add a new page object.
    page = HPDF_AddPage (pdf)

    HPDF_Page_SetFontAndSize (page, hfont, 10)

    HPDF_Page_SetHeight (page, PAGE_HEIGHT)
    HPDF_Page_SetWidth (page, PAGE_WIDTH)

    # normal
    HPDF_Page_GSave (page)
    draw_circles (page, "normal", 40.0, PAGE_HEIGHT - 170)
    HPDF_Page_GRestore (page)

    # transparency (0.8)
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetAlphaFill (gstate, 0.8)
    HPDF_ExtGState_SetAlphaStroke (gstate, 0.8)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "alpha fill = 0.8", 230.0, PAGE_HEIGHT - 170)
    HPDF_Page_GRestore (page)

    # transparency (0.4)
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetAlphaFill (gstate, 0.4)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "alpha fill = 0.4", 420.0, PAGE_HEIGHT - 170)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_MULTIPLY
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_MULTIPLY)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_MULTIPLY", 40.0, PAGE_HEIGHT - 340)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_SCREEN
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_SCREEN)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_SCREEN", 230.0, PAGE_HEIGHT - 340)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_OVERLAY
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_OVERLAY)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_OVERLAY", 420.0, PAGE_HEIGHT - 340)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_DARKEN
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_DARKEN)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_DARKEN", 40.0, PAGE_HEIGHT - 510)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_LIGHTEN
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_LIGHTEN)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_LIGHTEN", 230.0, PAGE_HEIGHT - 510)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_COLOR_DODGE
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_COLOR_DODGE)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_COLOR_DODGE", 420.0, PAGE_HEIGHT - 510)
    HPDF_Page_GRestore (page)


    # blend-mode=HPDF_BM_COLOR_BUM
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_COLOR_BUM)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_COLOR_BUM", 40.0, PAGE_HEIGHT - 680)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_HARD_LIGHT
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_HARD_LIGHT)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_HARD_LIGHT", 230.0, PAGE_HEIGHT - 680)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_SOFT_LIGHT
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_SOFT_LIGHT)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_SOFT_LIGHT", 420.0, PAGE_HEIGHT - 680)
    HPDF_Page_GRestore (page)

    # blend-mode=HPDF_BM_DIFFERENCE
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_DIFFERENCE)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_DIFFERENCE", 40.0, PAGE_HEIGHT - 850)
    HPDF_Page_GRestore (page)


    # blend-mode=HPDF_BM_EXCLUSHON
    HPDF_Page_GSave (page)
    gstate = HPDF_CreateExtGState (pdf)
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_EXCLUSHON)
    HPDF_Page_SetExtGState (page, gstate)
    draw_circles (page, "HPDF_BM_EXCLUSHON", 230.0, PAGE_HEIGHT - 850)
    HPDF_Page_GRestore (page)


    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()