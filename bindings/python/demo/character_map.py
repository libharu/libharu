###
## * << Haru Free PDF Library 2.0.0 >> -- character_map.c
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
## * usage character_map <encoding-name> <low-range-from> <low-range-to>
## *              <high-range-from> <high-range-to>
## * ex. character_map 90ms-RKSJ-V 0x80 0x
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

def draw_page(pdf, page, title_font, font, h_byte, l_byte):
    PAGE_WIDTH = 420
    CELL_HEIGHT = 20
    CELL_WIDTH = 20


    l_byte = int(l_byte / 16) * 16
    h_count = 16 - (l_byte / 16)
    page_height = 40 + 40 + (h_count + 1) * CELL_HEIGHT

    HPDF_Page_SetHeight (page, page_height)
    HPDF_Page_SetWidth (page, PAGE_WIDTH)

    HPDF_Page_SetFontAndSize (page, title_font, 10)

    ypos = h_count + 1
    while True:
        y = (ypos) * CELL_HEIGHT + 40

        HPDF_Page_MoveTo (page, 40, y)
        HPDF_Page_LineTo (page, 380, y)
        HPDF_Page_Stroke (page)
        if (ypos < h_count):
            buf=[None,None]

            buf[0] = 16 - ypos - 1
            if (buf[0] < 10):
                buf[0] += ord('0')
            else:
                buf[0] += (ord('A') - 10)
            buf[1] = 0
            buf=[i % 256 for i in buf]      #because buf is unsigned char *

            w = HPDF_Page_TextWidth (page, buf)
            HPDF_Page_BeginText (page)
            HPDF_Page_MoveTextPos (page, 40 + (20 - w) / 2, y + 5)
            HPDF_Page_ShowText (page, buf)
            HPDF_Page_EndText (page)


        if (ypos == 0):
            break

        ypos-=1


    for xpos in range(18):
        y = (h_count + 1) * CELL_HEIGHT + 40
        x = xpos * CELL_WIDTH + 40

        HPDF_Page_MoveTo (page, x, 40)
        HPDF_Page_LineTo (page, x, y)
        HPDF_Page_Stroke (page)

        if (xpos > 0 and xpos <= 16):
            buf=[None,None]

            buf[0] = xpos - 1
            if (buf[0] < 10):
                buf[0] += ord('0')
            else:
                buf[0] += (ord('A') - 10)
            buf[1] = 0
            buf=[i % 256 for i in buf]      #because buf is unsigned char *

            w = HPDF_Page_TextWidth(page, buf)
            HPDF_Page_BeginText(page)
            HPDF_Page_MoveTextPos(page, x + (20 - w) / 2,
                        h_count * CELL_HEIGHT + 45)
            HPDF_Page_ShowText(page, buf)
            HPDF_Page_EndText(page)


    HPDF_Page_SetFontAndSize (page, font, 15)

    ypos = h_count
    while True:
        y = (ypos - 1) * CELL_HEIGHT + 45

        for xpos in range(16):
            buf=[None for i in range(3)]

            x = xpos * CELL_WIDTH + 40 + CELL_WIDTH

            buf[0] = h_byte
            buf[1] = (16 - ypos) * 16 + xpos
            buf[2] = 0x00
            buf=[i % 256 for i in buf]      #because buf is unsigned char *

            w = HPDF_Page_TextWidth(page, buf)
            if (w > 0):
                HPDF_Page_BeginText(page)
                HPDF_Page_MoveTextPos(page, x + (20 - w) / 2, y)
                HPDF_Page_ShowText(page, buf)
                HPDF_Page_EndText(page)


        if (ypos == 0):
            break

        ypos-=1


def main ():
    global  pdf

    flg=[HPDF_UINT16(0) for i in range(256)]

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    if (len(sys.argv) < 3):
        printf ("usage: character_map <encoding-name> <font-name>\n")
        printf ('for example, character_map.py GBK-EUC-H SimHei,Bold')
        return 1

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1


    # configure pdf-document (showing outline, compression enabled)
    HPDF_SetPageMode(pdf, HPDF_PAGE_MODE_USE_OUTLINE)
    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL)
    HPDF_SetPagesConfiguration (pdf, 10)

    HPDF_UseJPEncodings (pdf)
    HPDF_UseJPFonts (pdf)
    HPDF_UseKREncodings (pdf)
    HPDF_UseKRFonts (pdf)
    HPDF_UseCNSEncodings (pdf)
    HPDF_UseCNSFonts (pdf)
    HPDF_UseCNTEncodings (pdf)
    HPDF_UseCNTFonts (pdf)

    encoder = HPDF_GetEncoder (pdf, sys.argv[1])
    if (HPDF_Encoder_GetType (encoder) != HPDF_ENCODER_TYPE_DOUBLE_BYTE):
        printf ("error: %s is not cmap-encoder\n", sys.argv[1])
        HPDF_Free (pdf)
        return 1

    font = HPDF_GetFont (pdf, sys.argv[2], sys.argv[1])

    min_l = 255
    min_h = 256
    max_l = 0
    max_h = 0


    for i in range(256):
        for j in range(20, 256):
            buf=[None, None ,None]
            code = i * 256 + j

            buf[0] = i
            buf[1] = j
            buf[2] = 0

            btype = HPDF_Encoder_GetByteType (encoder, buf, 0)
            unicode = HPDF_Encoder_GetUnicode (encoder, code)

            if (btype == HPDF_BYTE_TYPE_LEAD and
                    unicode != 0x25A1):
                if (min_l > j):
                    min_l = j

                if (max_l < j):
                    max_l = j

                if (min_h > i):
                    min_h = i

                if (max_h < i):
                    max_h = i

                flg[i] = 1

    printf ("min_h=%04X max_h=%04X min_l=%04X max_l=%04X\n",
            min_h, max_h, min_l, max_l)

    # create outline root.
    root = HPDF_CreateOutline (pdf, NULL, sys.argv[1], NULL)
    HPDF_Outline_SetOpened (root, HPDF_TRUE)

    for i in range(256):
        if (flg[i]):
            page = HPDF_AddPage (pdf)
            title_font = HPDF_GetFont (pdf, "Helvetica", NULL)

            buf="0x%04X-0x%04X" %(
                                  (i * 256 + min_l),
                                  (i * 256 + max_l)
                                 )

            outline = HPDF_CreateOutline (pdf, root, buf, NULL)
            dst = HPDF_Page_CreateDestination (page)
            HPDF_Outline_SetDestination(outline, dst)

            draw_page (pdf, page, title_font, font, i, min_l)

            buf="%s (%s) 0x%04X-0x%04X" %(
                        sys.argv[1],
                        sys.argv[2],
                        (i * 256 + min_l),
                        (i * 256 + max_l)
                        )
            HPDF_Page_SetFontAndSize (page, title_font, 10)
            HPDF_Page_BeginText (page)
            HPDF_Page_MoveTextPos (page, 40, HPDF_Page_GetHeight (page) - 35)
            HPDF_Page_ShowText (page, buf)
            HPDF_Page_EndText (page)

    HPDF_SaveToFile (pdf, fname)
    HPDF_Free (pdf)

    return 0

main()