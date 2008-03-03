###
## * << Haru Free PDF Library 2.0.0 >> -- grid_sheet.c
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


def print_grid  (pdf, page):
    height = HPDF_Page_GetHeight (page)
    width = HPDF_Page_GetWidth (page)
    font = HPDF_GetFont (pdf, "Helvetica", NULL)

    HPDF_Page_SetFontAndSize (page, font, 5)
    HPDF_Page_SetGrayFill (page, 0.5)
    HPDF_Page_SetGrayStroke (page, 0.8)

    # Draw horizontal lines
    y = 0
    while (y < height):
        if (y % 10 == 0):
            HPDF_Page_SetLineWidth (page, 0.5)
        else:
            if (HPDF_Page_GetLineWidth (page) != 0.25):
                HPDF_Page_SetLineWidth (page, 0.25)


        HPDF_Page_MoveTo (page, 0, y)
        HPDF_Page_LineTo (page, width, y)
        HPDF_Page_Stroke (page)

        if (y % 10 == 0 and y > 0):
            HPDF_Page_SetGrayStroke (page, 0.5)

            HPDF_Page_MoveTo (page, 0, y)
            HPDF_Page_LineTo (page, 5, y)
            HPDF_Page_Stroke (page)

            HPDF_Page_SetGrayStroke (page, 0.8)


        y += 5



    # Draw virtical lines
    x = 0
    while (x < width):
        if (x % 10 == 0):
            HPDF_Page_SetLineWidth (page, 0.5)
        else:
            if (HPDF_Page_GetLineWidth (page) != 0.25):
                HPDF_Page_SetLineWidth (page, 0.25)


        HPDF_Page_MoveTo (page, x, 0)
        HPDF_Page_LineTo (page, x, height)
        HPDF_Page_Stroke (page)

        if (x % 50 == 0 and x > 0):
            HPDF_Page_SetGrayStroke (page, 0.5)

            HPDF_Page_MoveTo (page, x, 0)
            HPDF_Page_LineTo (page, x, 5)
            HPDF_Page_Stroke (page)

            HPDF_Page_MoveTo (page, x, height)
            HPDF_Page_LineTo (page, x, height - 5)
            HPDF_Page_Stroke (page)

            HPDF_Page_SetGrayStroke (page, 0.8)


        x += 5


    # Draw horizontal text
    y = 0
    while (y < height):
        if (y % 10 == 0 and y > 0):

            HPDF_Page_BeginText (page)
            HPDF_Page_MoveTextPos (page, 5, y - 2)

            buf="%u" % y

            HPDF_Page_ShowText (page, buf)
            HPDF_Page_EndText (page)

        y += 5


    # Draw virtical text
    x = 0
    while (x < width):
        if (x % 50 == 0 and x > 0):

            HPDF_Page_BeginText (page)
            HPDF_Page_MoveTextPos (page, x, 5)

            buf="%u" % x

            HPDF_Page_ShowText (page, buf)
            HPDF_Page_EndText (page)

            HPDF_Page_BeginText (page)
            HPDF_Page_MoveTextPos (page, x, height - 10)
            HPDF_Page_ShowText (page, buf)
            HPDF_Page_EndText (page)

        x += 5

    HPDF_Page_SetGrayFill (page, 0)
    HPDF_Page_SetGrayStroke (page, 0)


def main():
    global pdf

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    # add a new page object.
    page = HPDF_AddPage (pdf)

    HPDF_Page_SetHeight (page, 600)
    HPDF_Page_SetWidth (page, 400)

    print_grid  (pdf, page)


    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

if __name__=='__main__':
    main()


__all__=['print_grid']