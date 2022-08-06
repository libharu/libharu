###
## * << Haru Free PDF Library 2.0.0 >> -- jpeg_demo.c
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

def draw_image (pdf, filename, x, y, text):

    page = HPDF_GetCurrentPage (pdf)

    filename1="images/%s" % filename

    image = HPDF_LoadJpegImageFromFile (pdf, filename1)

    # Draw image to the canvas.
    HPDF_Page_DrawImage (page, image, x, y, HPDF_Image_GetWidth (image),
                HPDF_Image_GetHeight (image))

    # Print the text.
    HPDF_Page_BeginText (page)
    HPDF_Page_SetTextLeading (page, 16)
    HPDF_Page_MoveTextPos (page, x, y)
    HPDF_Page_ShowTextNextLine (page, filename)
    HPDF_Page_ShowTextNextLine (page, text)
    HPDF_Page_EndText (page)


def main():
    global pdf

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL)

    # create default-font
    font = HPDF_GetFont (pdf, "Helvetica", NULL)

    # add a new page object.
    page = HPDF_AddPage (pdf)

    HPDF_Page_SetWidth (page, 650)
    HPDF_Page_SetHeight (page, 500)

    dst = HPDF_Page_CreateDestination (page)
    HPDF_Destination_SetXYZ (dst, 0, HPDF_Page_GetHeight (page), 1)
    HPDF_SetOpenAction(pdf, dst)

    HPDF_Page_BeginText (page)
    HPDF_Page_SetFontAndSize (page, font, 20)
    HPDF_Page_MoveTextPos (page, 220, HPDF_Page_GetHeight (page) - 70)
    HPDF_Page_ShowText (page, "JpegDemo")
    HPDF_Page_EndText (page)

    HPDF_Page_SetFontAndSize (page, font, 12)

    draw_image (pdf, "rgb.jpg", 70, HPDF_Page_GetHeight (page) - 410,
                "24bit color image")
    draw_image (pdf, "gray.jpg", 340, HPDF_Page_GetHeight (page) - 410,
                "8bit grayscale image")

    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()