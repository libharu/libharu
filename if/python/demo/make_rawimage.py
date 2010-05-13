###
## * << Haru Free PDF Library 2.0.0 >> -- make_rawimage.c
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
    global  pdf

    if (len(sys.argv) < 2):
        printf ("usage: make_rawimage <in-file-name> <out-file-name>\n")
        return 1

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    # load image file.
    image = HPDF_LoadPngImageFromFile (pdf, sys.argv[1])

    iw = HPDF_Image_GetWidth (image)
    ih = HPDF_Image_GetHeight (image)
    bits_per_comp = HPDF_Image_GetBitsPerComponent (image)
    cs = HPDF_Image_GetColorSpace (image)

    printf ("width=%u\n", iw)
    printf ("height=%u\n", ih)
    printf ("bits_per_comp=%u\n", bits_per_comp)
    printf ("color_space=%s\n", cs)

    # save raw-data to file
    stream = HPDF_FileWriter_New (pdf.mmgr, sys.argv[2])
    if (not stream):
        printf ("cannot open %s\n", sys.argv[2])
    else:
        HPDF_Stream_WriteToStream(image.stream, stream, 0, NULL)

    HPDF_Stream_Free (stream)

    # clean up
    HPDF_Free (pdf)

    return 0

main()