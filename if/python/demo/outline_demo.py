#coding=ISO8859-2

###
## * << Haru Free PDF Library 2.0.0 >> -- outline_demo.c
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


def print_page  (page,  page_num):

    HPDF_Page_SetWidth (page, 800)
    HPDF_Page_SetHeight (page, 800)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, 30, 740)

    buf="Page:%d" % page_num


    HPDF_Page_ShowText (page, buf)
    HPDF_Page_EndText (page)


def main():
    global pdf
    page=[None for i in range(4)]
    outline=[None for i in range(4)]

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    # create default-font
    font = HPDF_GetFont (pdf, "Helvetica", NULL)

    # Set page mode to use outlines.
    HPDF_SetPageMode(pdf, HPDF_PAGE_MODE_USE_OUTLINE)

    # Add 3 pages to the document.
    page[0] = HPDF_AddPage (pdf)
    HPDF_Page_SetFontAndSize (page[0], font, 30)
    print_page(page[0], 1)

    page[1] = HPDF_AddPage (pdf)
    HPDF_Page_SetFontAndSize (page[1], font, 30)
    print_page(page[1], 2)

    page[2] = HPDF_AddPage (pdf)
    HPDF_Page_SetFontAndSize (page[2], font, 30)
    print_page(page[2], 3)

    # create outline root.
    root = HPDF_CreateOutline (pdf, NULL, "OutlineRoot", NULL)
    HPDF_Outline_SetOpened (root, HPDF_TRUE)

    outline[0] = HPDF_CreateOutline (pdf, root, "page1", NULL)
    outline[1] = HPDF_CreateOutline (pdf, root, "page2", NULL)

    # create outline with test which is ISO8859-2 encoding
    #outline[2] = HPDF_CreateOutline (pdf, root, "ISO8859-2 text 釉罩棕?,
    #                HPDF_GetEncoder (pdf, "ISO8859-2"))

    # create destination objects on each pages
    # and link it to outline items.

    dst = HPDF_Page_CreateDestination (page[0])
    HPDF_Destination_SetXYZ(dst, 0, HPDF_Page_GetHeight(page[0]), 1)
    HPDF_Outline_SetDestination(outline[0], dst)
    #HPDF_Catalog_SetOpenAction(dst)

    dst = HPDF_Page_CreateDestination (page[1])
    HPDF_Destination_SetXYZ(dst, 0, HPDF_Page_GetHeight(page[1]), 1)
    HPDF_Outline_SetDestination(outline[1], dst)

    dst = HPDF_Page_CreateDestination (page[2])
    HPDF_Destination_SetXYZ(dst, 0, HPDF_Page_GetHeight(page[2]), 1)
    HPDF_Outline_SetDestination(outline[2], dst)

    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()