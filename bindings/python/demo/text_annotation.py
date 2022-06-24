#coding=utf-8
###
## * << Haru Free PDF Library 2.0.0 >> -- text_annotation.c
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
    rect1 =HPDF_Rect(50, 350, 150, 400)
    rect2 =HPDF_Rect(210, 350, 350, 400)
    rect3 =HPDF_Rect(50, 250, 150, 300)
    rect4 =HPDF_Rect(210, 250, 350, 300)
    rect5 =HPDF_Rect(50, 150, 150, 200)
    rect6 =HPDF_Rect(210, 150, 350, 200)
    rect7 =HPDF_Rect(50, 50, 150, 100)
    rect8 =HPDF_Rect(210, 50, 350, 100)

    global  pdf

    fname=os.path.realpath(sys.argv[0])
    fname=fname[:fname.rfind('.')]+'.pdf'

    pdf = HPDF_New (error_handler, NULL)
    if (not pdf):
        printf ("error: cannot create PdfDoc object\n")
        return 1

    # use Times-Roman font.
    font = HPDF_GetFont (pdf, "Times-Roman", "WinAnsiEncoding")

    page = HPDF_AddPage (pdf)

    HPDF_Page_SetWidth (page, 400)
    HPDF_Page_SetHeight (page, 500)

    HPDF_Page_BeginText (page)
    HPDF_Page_SetFontAndSize (page, font, 16)
    HPDF_Page_MoveTextPos (page, 130, 450)
    HPDF_Page_ShowText (page, "Annotation Demo")
    HPDF_Page_EndText (page)


    annot = HPDF_Page_CreateTextAnnot (page, rect1, "Annotation with Comment "
                "Icon. \n This annotation set to be opened initially.",
                NULL)

    HPDF_TextAnnot_SetIcon (annot, HPDF_ANNOT_ICON_COMMENT)
    HPDF_TextAnnot_SetOpened (annot, HPDF_TRUE)

    annot = HPDF_Page_CreateTextAnnot (page, rect2,
                "Annotation with Key Icon", NULL)
    HPDF_TextAnnot_SetIcon (annot, HPDF_ANNOT_ICON_PARAGRAPH)

    annot = HPDF_Page_CreateTextAnnot (page, rect3,
                "Annotation with Note Icon", NULL)
    HPDF_TextAnnot_SetIcon (annot, HPDF_ANNOT_ICON_NOTE)

    annot = HPDF_Page_CreateTextAnnot (page, rect4,
                "Annotation with Help Icon", NULL)
    HPDF_TextAnnot_SetIcon (annot, HPDF_ANNOT_ICON_HELP)

    annot = HPDF_Page_CreateTextAnnot (page, rect5,
                "Annotation with NewParagraph Icon", NULL)
    HPDF_TextAnnot_SetIcon (annot, HPDF_ANNOT_ICON_NEW_PARAGRAPH)

    annot = HPDF_Page_CreateTextAnnot (page, rect6,
                "Annotation with Paragraph Icon", NULL)
    HPDF_TextAnnot_SetIcon (annot, HPDF_ANNOT_ICON_PARAGRAPH)

    annot = HPDF_Page_CreateTextAnnot (page, rect7,
                "Annotation with Insert Icon", NULL)
    HPDF_TextAnnot_SetIcon (annot, HPDF_ANNOT_ICON_INSERT)

    encoding = HPDF_GetEncoder (pdf, "ISO8859-2")

    #HPDF_Page_CreateTextAnnot (page, rect8,
    #            "Annotation with ISO8859 text 釉罩棕?, encoding)

    HPDF_Page_SetFontAndSize (page, font, 11)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect1.left + 35, rect1.top - 20)
    HPDF_Page_ShowText (page, "Comment Icon.")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect2.left + 35, rect2.top - 20)
    HPDF_Page_ShowText (page, "Key Icon")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect3.left + 35, rect3.top - 20)
    HPDF_Page_ShowText (page, "Note Icon.")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect4.left + 35, rect4.top - 20)
    HPDF_Page_ShowText (page, "Help Icon")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect5.left + 35, rect5.top - 20)
    HPDF_Page_ShowText (page, "NewParagraph Icon")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect6.left + 35, rect6.top - 20)
    HPDF_Page_ShowText (page, "Paragraph Icon")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect7.left + 35, rect7.top - 20)
    HPDF_Page_ShowText (page, "Insert Icon")
    HPDF_Page_EndText (page)

    HPDF_Page_BeginText (page)
    HPDF_Page_MoveTextPos (page, rect8.left + 35, rect8.top - 20)
    HPDF_Page_ShowText (page, "Text Icon(ISO8859-2 text)")
    HPDF_Page_EndText (page)


    # save the document to a file
    HPDF_SaveToFile (pdf, fname)

    # clean up
    HPDF_Free (pdf)

    return 0

main()