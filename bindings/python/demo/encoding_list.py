###
## * << Haru Free PDF Library 2.0.0 >> -- encoding_list.c
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


PAGE_WIDTH = 420
PAGE_HEIGHT = 400
CELL_WIDTH = 20
CELL_HEIGHT = 20
CELL_HEADER = 10

def draw_graph (page):

    # Draw 16 X 15 cells

    # Draw vertical lines.
    HPDF_Page_SetLineWidth (page, 0.5)

    for i in range(18):
        x = i * CELL_WIDTH + 40

        HPDF_Page_MoveTo (page, x, PAGE_HEIGHT - 60)
        HPDF_Page_LineTo (page, x, 40)
        HPDF_Page_Stroke (page)

        if (i > 0 and i <= 16):
            HPDF_Page_BeginText (page)
            HPDF_Page_MoveTextPos (page, x + 5, PAGE_HEIGHT - 75)
            buf="%X" %(i - 1)
            HPDF_Page_ShowText (page, buf)
            HPDF_Page_EndText (page)

    # Draw horizontal lines.
    for i in range(16):
        y = i * CELL_HEIGHT + 40

        HPDF_Page_MoveTo (page, 40, y)
        HPDF_Page_LineTo (page, PAGE_WIDTH - 40, y)
        HPDF_Page_Stroke (page)

        if (i < 14):
            HPDF_Page_BeginText (page)
            HPDF_Page_MoveTextPos (page, 45, y + 5)

            buf="%X" %( 15 - i)
            HPDF_Page_ShowText (page, buf)
            HPDF_Page_EndText (page)


def draw_fonts (page):
    HPDF_Page_BeginText (page)

    # Draw all character from 0x20 to 0xFF to the canvas.
    for i in range(1,17):
        for j in range(1,17):
            buf=[None, None]
            y = PAGE_HEIGHT - 55 - ((i - 1) * CELL_HEIGHT)
            x = j * CELL_WIDTH + 50

            buf[1] = 0x00

            buf[0] = (i - 1) * 16 + (j - 1)
            if (buf[0] >= 32):
                d  = x - HPDF_Page_TextWidth (page, buf) / 2
                HPDF_Page_TextOut (page, d, y, buf)


    HPDF_Page_EndText (page)



def main ():

    encodings=[
            "StandardEncoding",
            "MacRomanEncoding",
            "WinAnsiEncoding",
            "ISO8859-2",
            "ISO8859-3",
            "ISO8859-4",
            "ISO8859-5",
            "ISO8859-9",
            "ISO8859-10",
            "ISO8859-13",
            "ISO8859-14",
            "ISO8859-15",
            "ISO8859-16",
            "CP1250",
            "CP1251",
            "CP1252",
            "CP1254",
            "CP1257",
            "KOI8-R",
            "Symbol-Set",
            "ZapfDingbats-Set",
            NULL
    ]

    pdf = HPDF_NewEx (error_handler, NULL, NULL, 0, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    # set compression mode
    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL)

    # Set page mode to use outlines.
    HPDF_SetPageMode(pdf, HPDF_PAGE_MODE_USE_OUTLINE)

    # get default font
    font = HPDF_GetFont (pdf, "Helvetica", NULL)

    # load font object
    font_name = HPDF_LoadType1FontFromFile (pdf, "type1/a010013l.afm",
            "type1/a010013l.pfb")

    # create outline root.
    root = HPDF_CreateOutline (pdf, NULL, "Encoding list", NULL)
    HPDF_Outline_SetOpened (root, HPDF_TRUE)

    i=0
    while (encodings[i]):
        page = HPDF_AddPage (pdf)

        HPDF_Page_SetWidth (page, PAGE_WIDTH)
        HPDF_Page_SetHeight (page, PAGE_HEIGHT)

        outline = HPDF_CreateOutline (pdf, root, encodings[i], NULL)
        dst = HPDF_Page_CreateDestination (page)
        HPDF_Destination_SetXYZ(dst, 0, HPDF_Page_GetHeight(page), 1)
        # HPDF_Destination_SetFitB(dst);
        HPDF_Outline_SetDestination(outline, dst)

        HPDF_Page_SetFontAndSize (page, font, 15)
        draw_graph (page)

        HPDF_Page_BeginText (page)
        HPDF_Page_SetFontAndSize (page, font, 20)
        HPDF_Page_MoveTextPos (page, 40, PAGE_HEIGHT - 50)
        HPDF_Page_ShowText (page, encodings[i])
        HPDF_Page_ShowText (page, " Encoding")
        HPDF_Page_EndText (page)

        if encodings[i]=="Symbol-Set":
            font2 = HPDF_GetFont (pdf, "Symbol", NULL)
        elif encodings[i]=="ZapfDingbats-Set":
            font2 = HPDF_GetFont (pdf, "ZapfDingbats", NULL)
        else:
            font2 = HPDF_GetFont (pdf, font_name, encodings[i])

        HPDF_Page_SetFontAndSize (page, font2, 14)
        draw_fonts (page)

        i+=1


    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()