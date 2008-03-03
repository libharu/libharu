###
## * << Haru Free PDF Library 2.0.0 >> -- jpfont_demo.c
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

def main():
    global pdf

    chinesefonts='''
SimSun
SimSun,Bold
SimSun,Italic
SimSun,BoldItalic
SimHei
SimHei,Bold
SimHei,Italic
SimHei,BoldItalic
'''
    chinesefonts=chinesefonts.split('\n')
    chinesefonts=[i for i in chinesefonts if i]

    detail_font=[]
    PAGE_HEIGHT = 210

    try:
        f = open ("mbtext/cp936.txt", "rb")
    except:
        printf ("error: cannot open 'mbtext/sjis.txt'\n")
        return 1

    samp_text=f.read(2048)
    f.close ()

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1


    # configure pdf-document to be compressed.
    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL)

    # declaration for using Japanese font, encoding.
    HPDF_UseCNSEncodings (pdf)
    HPDF_UseCNSFonts (pdf)


    for i in chinesefonts:
        detail_font.append( HPDF_GetFont (pdf, i, "GB-EUC-H"))

    # Set page mode to use outlines.
    HPDF_SetPageMode(pdf, HPDF_PAGE_MODE_USE_OUTLINE)

    # create outline root.
    root = HPDF_CreateOutline (pdf, NULL, "JP font demo", NULL)
    HPDF_Outline_SetOpened (root, HPDF_TRUE)

    for i in detail_font:

        # add a new page object.
        page = HPDF_AddPage (pdf)

        # create outline entry
        outline = HPDF_CreateOutline (pdf, root,
                HPDF_Font_GetFontName (i), NULL)
        dst = HPDF_Page_CreateDestination (page)
        HPDF_Outline_SetDestination(outline, dst)

        title_font = HPDF_GetFont (pdf, "Helvetica", NULL)
        HPDF_Page_SetFontAndSize (page, title_font, 10)

        HPDF_Page_BeginText (page)

        # move the position of the text to top of the page.
        HPDF_Page_MoveTextPos(page, 10, 190)
        HPDF_Page_ShowText (page, HPDF_Font_GetFontName (i))

        HPDF_Page_SetFontAndSize (page, i, 15)
        HPDF_Page_MoveTextPos (page, 10, -20)
        HPDF_Page_ShowText (page, "abcdefghijklmnopqrstuvwxyz")
        HPDF_Page_MoveTextPos (page, 0, -20)
        HPDF_Page_ShowText (page, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
        HPDF_Page_MoveTextPos (page, 0, -20)
        HPDF_Page_ShowText (page, "1234567890")
        HPDF_Page_MoveTextPos (page, 0, -20)

        HPDF_Page_SetFontAndSize (page, i, 10)
        HPDF_Page_ShowText (page, samp_text)
        HPDF_Page_MoveTextPos (page, 0, -18)

        HPDF_Page_SetFontAndSize (page, i, 16)
        HPDF_Page_ShowText (page, samp_text)
        HPDF_Page_MoveTextPos (page, 0, -27)

        HPDF_Page_SetFontAndSize (page, i, 23)
        HPDF_Page_ShowText (page, samp_text)
        HPDF_Page_MoveTextPos (page, 0, -36)

        HPDF_Page_SetFontAndSize (page, i, 30)
        HPDF_Page_ShowText (page, samp_text)

        p = HPDF_Page_GetCurrentTextPos (page)

        # finish to print text.
        HPDF_Page_EndText (page)

        HPDF_Page_SetLineWidth (page, 0.5)

        x_pos = 20
        for j in range(len (samp_text) // 2):
            HPDF_Page_MoveTo (page, x_pos, p.y - 10)
            HPDF_Page_LineTo (page, x_pos, p.y - 12)
            HPDF_Page_Stroke (page)
            x_pos = x_pos + 30

        HPDF_Page_SetWidth (page, p.x + 20)
        HPDF_Page_SetHeight (page, PAGE_HEIGHT)

        HPDF_Page_MoveTo (page, 10, PAGE_HEIGHT - 25)
        HPDF_Page_LineTo (page, p.x + 10, PAGE_HEIGHT - 25)
        HPDF_Page_Stroke (page)

        HPDF_Page_MoveTo (page, 10, PAGE_HEIGHT - 85)
        HPDF_Page_LineTo (page, p.x + 10, PAGE_HEIGHT - 85)
        HPDF_Page_Stroke (page)

        HPDF_Page_MoveTo (page, 10, p.y - 12)
        HPDF_Page_LineTo (page, p.x + 10, p.y - 12)
        HPDF_Page_Stroke (page)

    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()