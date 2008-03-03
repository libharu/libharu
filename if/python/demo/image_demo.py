###
## * << Haru Free PDF Library 2.0.0 >> -- image_demo.c
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

from math import *

@HPDF_Error_Handler(None, HPDF_UINT, HPDF_UINT, c_void_p)
def error_handler (error_no, detail_no, user_data):
    global pdf
    printf ("ERROR: %s, detail_no=%u\n", error_detail[error_no],
                detail_no)
    HPDF_Free (pdf)
    sys.exit(1)


def show_description (page, x, y, text):
    HPDF_Page_MoveTo (page, x, y - 10)
    HPDF_Page_LineTo (page, x, y + 10)
    HPDF_Page_MoveTo (page, x - 10, y)
    HPDF_Page_LineTo (page, x + 10, y)
    HPDF_Page_Stroke (page)

    HPDF_Page_SetFontAndSize (page, HPDF_Page_GetCurrentFont (page), 8)
    HPDF_Page_SetRGBFill (page, 0, 0, 0)

    HPDF_Page_BeginText (page)

    buf="(x=%d,y=%d)" % (int(x), int(y))

    HPDF_Page_MoveTextPos (page, x - HPDF_Page_TextWidth (page, buf) - 5,
            y - 10)
    HPDF_Page_ShowText (page, buf)
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, x - 20, y - 25)
    HPDF_Page_ShowText (page, text)
    HPDF_Page_EndText (page)


def main ():

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

    HPDF_Page_SetWidth (page, 550)
    HPDF_Page_SetHeight (page, 500)

    dst = HPDF_Page_CreateDestination (page)
    HPDF_Destination_SetXYZ (dst, 0, HPDF_Page_GetHeight (page), 1)
    HPDF_SetOpenAction(pdf, dst)

    HPDF_Page_BeginText (page)
    HPDF_Page_SetFontAndSize (page, font, 20)
    HPDF_Page_MoveTextPos (page, 220, HPDF_Page_GetHeight (page) - 70)
    HPDF_Page_ShowText (page, "ImageDemo")
    HPDF_Page_EndText (page)

    # load image file.
    image = HPDF_LoadPngImageFromFile (pdf, "pngsuite/basn3p02.png")

    # image1 is masked by image2.
    image1 = HPDF_LoadPngImageFromFile (pdf, "pngsuite/basn3p02.png")

    # image2 is a mask image.
    image2 = HPDF_LoadPngImageFromFile (pdf, "pngsuite/basn0g01.png")

    # image3 is a RGB-color image. we use this image for color-mask
    # * demo.
    image3 = HPDF_LoadPngImageFromFile (pdf, "pngsuite/maskimage.png")

    iw = HPDF_Image_GetWidth (image)
    ih = HPDF_Image_GetHeight (image)

    HPDF_Page_SetLineWidth (page, 0.5)

    x = 100
    y = HPDF_Page_GetHeight (page) - 150

    # Draw image to the canvas. (normal-mode with actual size.)
    HPDF_Page_DrawImage (page, image, x, y, iw, ih)

    show_description (page, x, y, "Actual Size")

    x += 150

    # Scalling image (X direction)
    HPDF_Page_DrawImage (page, image, x, y, iw * 1.5, ih)

    show_description (page, x, y, "Scalling image (X direction)")

    x += 150

    # Scalling image (Y direction).
    HPDF_Page_DrawImage (page, image, x, y, iw, ih * 1.5)
    show_description (page, x, y, "Scalling image (Y direction)")

    x = 100
    y -= 120

    # Skewing image.
    angle1 = 10
    angle2 = 20
    rad1 = angle1 / 180 * 3.141592
    rad2 = angle2 / 180 * 3.141592

    HPDF_Page_GSave (page)

    HPDF_Page_Concat (page, iw, tan(rad1) * iw, tan(rad2) * ih, ih, x, y)

    HPDF_Page_ExecuteXObject (page, image)
    HPDF_Page_GRestore (page)

    show_description (page, x, y, "Skewing image")

    x += 150

    # Rotating image
    angle = 30;     # rotation of 30 degrees.
    rad = angle / 180 * 3.141592; # Calcurate the radian value.

    HPDF_Page_GSave (page)

    HPDF_Page_Concat (page, iw * cos(rad),
                iw * sin(rad),
                ih * -sin(rad),
                ih * cos(rad),
                x, y)

    HPDF_Page_ExecuteXObject (page, image)
    HPDF_Page_GRestore (page)

    show_description (page, x, y, "Rotating image")

    x += 150

    # draw masked image.

    # Set image2 to the mask image of image1
    HPDF_Image_SetMaskImage (image1, image2)

    HPDF_Page_SetRGBFill (page, 0, 0, 0)
    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, x - 6, y + 14)
    HPDF_Page_ShowText (page, "MASKMASK")
    HPDF_Page_EndText (page)

    HPDF_Page_DrawImage (page, image1, x - 3, y - 3, iw + 6, ih + 6)

    show_description (page, x, y, "masked image")

    x = 100
    y -= 120

    # color mask.
    HPDF_Page_SetRGBFill (page, 0, 0, 0)
    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, x - 6, y + 14)
    HPDF_Page_ShowText (page, "MASKMASK")
    HPDF_Page_EndText (page)

    HPDF_Image_SetColorMask (image3, 0, 255, 0, 0, 0, 255)
    HPDF_Page_DrawImage (page, image3, x, y, iw, ih)

    show_description (page, x, y, "Color Mask")

    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0



if HPDF_NOPNGLIB:
    printf("WARNING: if you want to run this demo, \n"
           "make libhpdf with HPDF_USE_PNGLIB option.\n")
    sys.exit(1)
else:
    main()