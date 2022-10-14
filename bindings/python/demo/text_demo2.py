###
## * << Alternative PDF Library 1.0.0 >> -- text_demo2.c
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

from grid_sheet import *

from math import *


global pdf

@HPDF_Error_Handler(None, HPDF_UINT, HPDF_UINT, c_void_p)
def error_handler  (error_no, detail_no, user_data):
    printf ("ERROR: error_no=%04X, detail_no=%u\n", error_no,
                detail_no)
    HPDF_Free (pdf)


global no
no = 0

def PrintText(page):
    #char buf[512]
    pos = HPDF_Page_GetCurrentTextPos (page)

    no+=1
    buf=".[%d]%0.2f %0.2f" %( no, pos.x, pos.y)
    HPDF_Page_ShowText(page, buf)


def main ():
    global pdf

    rect=HPDF_Rect()

    SAMP_TXT = "The quick brown fox jumps over the lazy dog. "

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    # add a new page object.
    page = HPDF_AddPage (pdf)
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT)

    print_grid  (pdf, page)

    page_height = HPDF_Page_GetHeight (page)

    font = HPDF_GetFont (pdf, "Helvetica", NULL)
    HPDF_Page_SetTextLeading (page, 20)

    # text_rect method

    # HPDF_TALIGN_LEFT
    rect.left = 25
    rect.top = 545
    rect.right = 200
    rect.bottom = rect.top - 40

    HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
                rect.top - rect.bottom)
    HPDF_Page_Stroke (page)

    HPDF_Page_BeginText (page)

    HPDF_Page_SetFontAndSize (page, font, 10)
    HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_LEFT")

    HPDF_Page_SetFontAndSize (page, font, 13)
    HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
                SAMP_TXT, HPDF_TALIGN_LEFT, NULL)

    HPDF_Page_EndText (page)

    # HPDF_TALIGN_RIGTH
    rect.left = 220
    rect.right = 395

    HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
                rect.top - rect.bottom)
    HPDF_Page_Stroke (page)

    HPDF_Page_BeginText (page)

    HPDF_Page_SetFontAndSize (page, font, 10)
    HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_RIGTH")

    HPDF_Page_SetFontAndSize (page, font, 13)
    HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
                SAMP_TXT, HPDF_TALIGN_RIGHT, NULL)

    HPDF_Page_EndText (page)

    # HPDF_TALIGN_CENTER
    rect.left = 25
    rect.top = 475
    rect.right = 200
    rect.bottom = rect.top - 40

    HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
                rect.top - rect.bottom)
    HPDF_Page_Stroke (page)

    HPDF_Page_BeginText (page)

    HPDF_Page_SetFontAndSize (page, font, 10)
    HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_CENTER")

    HPDF_Page_SetFontAndSize (page, font, 13)
    HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
                SAMP_TXT, HPDF_TALIGN_CENTER, NULL)

    HPDF_Page_EndText (page)

    # HPDF_TALIGN_JUSTIFY
    rect.left = 220
    rect.right = 395

    HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
                rect.top - rect.bottom)
    HPDF_Page_Stroke (page)

    HPDF_Page_BeginText (page)

    HPDF_Page_SetFontAndSize (page, font, 10)
    HPDF_Page_TextOut (page, rect.left, rect.top + 3, "HPDF_TALIGN_JUSTIFY")

    HPDF_Page_SetFontAndSize (page, font, 13)
    HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
                SAMP_TXT, HPDF_TALIGN_JUSTIFY, NULL)

    HPDF_Page_EndText (page)



    # Skewed coordinate system
    HPDF_Page_GSave (page)

    angle1 = 5
    angle2 = 10
    rad1 = angle1 / 180 * 3.141592
    rad2 = angle2 / 180 * 3.141592

    HPDF_Page_Concat (page, 1, tan(rad1), tan(rad2), 1, 25, 350)
    rect.left = 0
    rect.top = 40
    rect.right = 175
    rect.bottom = 0

    HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
                rect.top - rect.bottom)
    HPDF_Page_Stroke (page)

    HPDF_Page_BeginText (page)

    HPDF_Page_SetFontAndSize (page, font, 10)
    HPDF_Page_TextOut (page, rect.left, rect.top + 3, "Skewed coordinate system")

    HPDF_Page_SetFontAndSize (page, font, 13)
    HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
                SAMP_TXT, HPDF_TALIGN_LEFT, NULL)

    HPDF_Page_EndText (page)

    HPDF_Page_GRestore (page)


    # Rotated coordinate system
    HPDF_Page_GSave (page)

    angle1 = 5
    rad1 = angle1 / 180 * 3.141592

    HPDF_Page_Concat (page, cos(rad1), sin(rad1), -sin(rad1), cos(rad1), 220, 350)
    rect.left = 0
    rect.top = 40
    rect.right = 175
    rect.bottom = 0

    HPDF_Page_Rectangle (page, rect.left, rect.bottom, rect.right - rect.left,
                rect.top - rect.bottom)
    HPDF_Page_Stroke (page)

    HPDF_Page_BeginText (page)

    HPDF_Page_SetFontAndSize (page, font, 10)
    HPDF_Page_TextOut (page, rect.left, rect.top + 3, "Rotated coordinate system")

    HPDF_Page_SetFontAndSize (page, font, 13)
    HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
                SAMP_TXT, HPDF_TALIGN_LEFT, NULL)

    HPDF_Page_EndText (page)

    HPDF_Page_GRestore (page)


    # text along a circle
    HPDF_Page_SetGrayStroke (page, 0)
    HPDF_Page_Circle (page, 210, 190, 145)
    HPDF_Page_Circle (page, 210, 190, 113)
    HPDF_Page_Stroke (page)

    angle1 = 360.0 / (len (SAMP_TXT))
    angle2 = 180

    HPDF_Page_BeginText (page)
    font = HPDF_GetFont (pdf, "Courier-Bold", NULL)
    HPDF_Page_SetFontAndSize (page, font, 30)

    for i in range(len (SAMP_TXT)):
        buf=[None, None]

        rad1 = (angle2 - 90) / 180 * 3.141592
        rad2 = angle2 / 180 * 3.141592

        x = 210 + cos(rad2) * 122
        y = 190 + sin(rad2) * 122

        HPDF_Page_SetTextMatrix(page, cos(rad1), sin(rad1), -sin(rad1), cos(rad1), x, y)

        buf[0] = SAMP_TXT[i]
        buf[1] = chr(0)
        HPDF_Page_ShowText (page, buf)
        angle2 -= angle1

    HPDF_Page_EndText (page)

    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0


main()