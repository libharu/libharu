###
## * << Haru Free PDF Library 2.0.0 >> -- raw_image_demo.c
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


RAW_IMAGE_DATA=[
    0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xfc,
    0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xf0,
    0xf3, 0xf3, 0xff, 0xe0, 0xf3, 0xf3, 0xff, 0xc0,
    0xf3, 0xf3, 0xff, 0x80, 0xf3, 0x33, 0xff, 0x00,
    0xf3, 0x33, 0xfe, 0x00, 0xf3, 0x33, 0xfc, 0x00,
    0xf8, 0x07, 0xf8, 0x00, 0xf8, 0x07, 0xf0, 0x00,
    0xfc, 0xcf, 0xe0, 0x00, 0xfc, 0xcf, 0xc0, 0x00,
    0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00,
    0xff, 0xfe, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00,
    0xff, 0xf8, 0x0f, 0xe0, 0xff, 0xf0, 0x0f, 0xe0,
    0xff, 0xe0, 0x0c, 0x30, 0xff, 0xc0, 0x0c, 0x30,
    0xff, 0x80, 0x0f, 0xe0, 0xff, 0x00, 0x0f, 0xe0,
    0xfe, 0x00, 0x0c, 0x30, 0xfc, 0x00, 0x0c, 0x30,
    0xf8, 0x00, 0x0f, 0xe0, 0xf0, 0x00, 0x0f, 0xe0,
    0xe0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
]

def main ():
    global  pdf

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

    HPDF_Page_SetWidth (page, 172)
    HPDF_Page_SetHeight (page, 80)

    HPDF_Page_BeginText (page)
    HPDF_Page_SetFontAndSize (page, font, 20)
    HPDF_Page_MoveTextPos (page, 220, HPDF_Page_GetHeight (page) - 70)
    HPDF_Page_ShowText (page, "RawImageDemo")
    HPDF_Page_EndText (page)

    # load RGB raw-image file.
    image = HPDF_LoadRawImageFromFile (pdf, "rawimage/32_32_rgb.dat",
            32, 32, HPDF_CS_DEVICE_RGB)

    x = 20
    y = 20

    # Draw image to the canvas. (normal-mode with actual size.)
    HPDF_Page_DrawImage (page, image, x, y, 32, 32)

    # load GrayScale raw-image file.
    image = HPDF_LoadRawImageFromFile (pdf, "rawimage/32_32_gray.dat",
            32, 32, HPDF_CS_DEVICE_GRAY)

    x = 70
    y = 20

    # Draw image to the canvas. (normal-mode with actual size.)
    HPDF_Page_DrawImage (page, image, x, y, 32, 32)

    # load GrayScale raw-image (1bit) file from memory.
    image = HPDF_LoadRawImageFromMem (pdf, RAW_IMAGE_DATA, 32, 32,
                HPDF_CS_DEVICE_GRAY, 1)

    x = 120
    y = 20

    # Draw image to the canvas. (normal-mode with actual size.)
    HPDF_Page_DrawImage (page, image, x, y, 32, 32)

    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()