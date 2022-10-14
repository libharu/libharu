###
## * << Haru Free PDF Library 2.0.0 >> -- arc_demo.c
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
from grid_sheet import *


@HPDF_Error_Handler(None, HPDF_UINT, HPDF_UINT, c_void_p)
def error_handler (error_no, detail_no, user_data):
    global pdf
    printf ("ERROR: %s, detail_no=%u\n", error_detail[error_no],
                detail_no)
    HPDF_Free (pdf)
    sys.exit(1)


def main ():
    global pdf

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    # add a new page object.
    page = HPDF_AddPage (pdf)

    HPDF_Page_SetHeight (page, 220)
    HPDF_Page_SetWidth (page, 200)

    # draw grid to the page
    print_grid  (pdf, page)

    # draw pie chart
    # *
    # *   A: 45% Red
    # *   B: 25% Blue
    # *   C: 15% green
    # *   D: other yellow


    # A
    HPDF_Page_SetRGBFill (page, 1.0, 0, 0)
    HPDF_Page_MoveTo (page, 100, 100)
    HPDF_Page_LineTo (page, 100, 180)
    HPDF_Page_Arc (page, 100, 100, 80, 0, 360 * 0.45)
    pos = HPDF_Page_GetCurrentPos (page)
    HPDF_Page_LineTo (page, 100, 100)
    HPDF_Page_Fill (page)

    # B
    HPDF_Page_SetRGBFill (page, 0, 0, 1.0)
    HPDF_Page_MoveTo (page, 100, 100)
    HPDF_Page_LineTo (page, pos.x, pos.y)
    HPDF_Page_Arc (page, 100, 100, 80, 360 * 0.45, 360 * 0.7)
    pos = HPDF_Page_GetCurrentPos (page)
    HPDF_Page_LineTo (page, 100, 100)
    HPDF_Page_Fill (page)

    # C
    HPDF_Page_SetRGBFill (page, 0, 1.0, 0)
    HPDF_Page_MoveTo (page, 100, 100)
    HPDF_Page_LineTo (page, pos.x, pos.y)
    HPDF_Page_Arc (page, 100, 100, 80, 360 * 0.7, 360 * 0.85)
    pos = HPDF_Page_GetCurrentPos (page)
    HPDF_Page_LineTo (page, 100, 100)
    HPDF_Page_Fill (page)

    # D
    HPDF_Page_SetRGBFill (page, 1.0, 1.0, 0)
    HPDF_Page_MoveTo (page, 100, 100)
    HPDF_Page_LineTo (page, pos.x, pos.y)
    HPDF_Page_Arc (page, 100, 100, 80, 360 * 0.85, 360)
    pos = HPDF_Page_GetCurrentPos (page)
    HPDF_Page_LineTo (page, 100, 100)
    HPDF_Page_Fill (page)

    # draw center circle
    HPDF_Page_SetGrayStroke (page, 0)
    HPDF_Page_SetGrayFill (page, 1)
    HPDF_Page_Circle (page, 100, 100, 30)
    HPDF_Page_Fill (page)

    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()