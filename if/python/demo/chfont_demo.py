###
## * << Haru Free PDF Library 2.0.0 >> -- chfont_demo.c
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
    global  pdf

    if (len(sys.argv) < 4):
        printf ("chfont_demo <cp936-ttc-font-file-name> "
                "<cp936-index> <cp932-ttc-font-file-name> <cp932-index>\n")
        return 1


    fname="mbtext/%s"% "cp932.txt"
    cp932 = open (fname, "rb")
    if (not cp932):
        printf ("error: cannot open cp932.txt\n")
        return 1

    fname= "mbtext/%s" % "cp936.txt"
    cp936 = open (fname, "rb")
    if (not cp936):
        printf ("error: cannot open cp936.txt\n")
        return 1

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1


    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL)
    HPDF_UseJPEncodings (pdf)
    HPDF_UseCNSEncodings (pdf)

    fcp936_name = HPDF_LoadTTFontFromFile2 (pdf, sys.argv[1], int(sys.argv[2]),
            HPDF_TRUE)
    fcp932_name = HPDF_LoadTTFontFromFile2 (pdf, sys.argv[3], int(sys.argv[4]),
            HPDF_TRUE)

    # add a new page object.
    page = HPDF_AddPage (pdf)

    HPDF_Page_SetHeight (page, 300)
    HPDF_Page_SetWidth (page, 550)

    fcp936 = HPDF_GetFont (pdf, fcp936_name, "GBK-EUC-H")
    fcp932 = HPDF_GetFont (pdf, fcp932_name, "90ms-RKSJ-H")

    print_grid  (pdf, page)

    HPDF_Page_SetTextLeading (page, 20)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, 50, 250)
    HPDF_Page_SetTextLeading (page, 25)

    buf=cp936.read(1024)
    while buf:
        HPDF_Page_SetFontAndSize (page, fcp936, 18)
        buf ='%s\0' % buf
        HPDF_Page_ShowText (page, buf)

        buf=cp936.read(1024)
        if buf:
            HPDF_Page_SetFontAndSize (page, fcp932, 18)
            buf ='%s\0' % buf
            HPDF_Page_ShowText (page, buf)

        HPDF_Page_MoveToNextLine (page)

    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    cp936.close ()
    cp932.close ()

    return 0

main()