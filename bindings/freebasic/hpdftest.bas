'****************************************************************************** 
'*  Program name: hpdftest
'*  Version:      0.1
'*
'*  Author:       Copyright (c) 2008 Klaus Siebke
'*                Siebke Unternehmensberatung
'*                URL http://www.siebke.com
'*
'*  Description:
'*  -----------
'*
'*  Program to test the creation of a PDF file using the Haru Free PDF Library
'*  for more details see: http://www.freebasic.net/forum/viewtopic.php?t=9014
'*
'*  License:
'*  -------
'*
'*  Permission to use, copy, modify, distribute and sell this software
'*  and its documentation for any purpose is hereby granted without fee,
'*  provided that the above copyright notice appear in all copies and
'*  that both that copyright notice and this permission notice appear
'*  in supporting documentation.
'*  It is provided "as is" without express or implied warranty.
'*
'*
'*  External libraries used by the program:
'*  --------------------------------------
'*
'*  << Haru Free PDF Library 2.0.8 >>
'*  URL http://libharu.org/
'*  Copyright (c) 1999-2006 Takeshi Kanno
'*
'****************************************************************************** 

#include "crt/errno.bi"
#include "zlib.bi"       

'****************************************************************************** 
'* Includes for Haru Free PDF Library 
'****************************************************************************** 
#ifndef __mod_hpdf_bi__
#define __mod_hpdf_bi__
#include once "hpdf_consts.bi"
#include once "hpdf_types.bi"
#include once "hpdf.bi"
#endif

'****************************************************************************** 
'* Declarations of subroutines and functions
'****************************************************************************** 
declare sub error_handler cdecl (byval error_no as HPDF_STATUS, byval detail_no as HPDF_STATUS, byval user_data as any ptr )

'****************************************************************************** 
'* Constants
'****************************************************************************** 
#define NULL 0 
const page_title = "PDF test document"

'****************************************************************************** 
'* Variables
'****************************************************************************** 
dim shared pdf          as HPDF_Doc 'ptr 
dim shared fname        as string * 256   
dim shared page         as HPDF_Page
dim shared def_font     as HPDF_Font
dim shared txt_font     as HPDF_Font
dim shared tw           as HPDF_REAL
dim shared doc_height   as HPDF_REAL
dim shared doc_width    as HPDF_REAL 
dim shared i            as HPDF_UINT
'dim shared errno        as HPDF_STATUS ptr
dim shared detno        as HPDF_STATUS ptr
dim shared userdat      as any ptr


'****************************************************************************** 
'* Begin of main program
'****************************************************************************** 

'let's go ... (initialize hpdf)
pdf = HPDF_New(@error_handler, NULL)


'add a new page object
page = HPDF_AddPage (pdf)

'specify the document size
doc_height = HPDF_Page_GetHeight (page)
doc_width = HPDF_Page_GetWidth (page)

'print a frame
HPDF_Page_SetLineWidth (page, .5)
HPDF_Page_Rectangle (page, 50, 50, doc_width - 100, doc_height - 110)
HPDF_Page_Stroke (page)

'print the title of the page (with positioning center) with font Helvetica
def_font = HPDF_GetFont (pdf, "Helvetica", NULL)
HPDF_Page_SetFontAndSize (page, def_font, 24)
tw = HPDF_Page_TextWidth (page, page_title)
HPDF_Page_BeginText (page)
HPDF_Page_TextOut (page, (doc_width - tw) / 2, doc_height - 50, page_title)
HPDF_Page_EndText (page)

'print some text inside the frame 
HPDF_Page_BeginText (page)

'first line with font Times Roman 14
txt_font = HPDF_GetFont (pdf, "Times-Roman", NULL)
HPDF_Page_MoveTextPos (page, 60, doc_height - 105)
HPDF_Page_SetFontAndSize (page, txt_font, 14)
HPDF_Page_ShowText (page, "This is a first line")

'second line with font Courier 12
txt_font = HPDF_GetFont (pdf, "Courier", NULL)
HPDF_Page_MoveTextPos (page, 0, -20)
HPDF_Page_SetFontAndSize (page, txt_font, 12)
HPDF_Page_ShowText (page, "This is a second line")

'third line with font Symbol 16
txt_font = HPDF_GetFont (pdf, "Symbol", NULL)
HPDF_Page_MoveTextPos (page, 0, -20)
HPDF_Page_SetFontAndSize (page, txt_font, 16)
HPDF_Page_ShowText (page, "Here are some symbols")

'fourth line with font Helvetica 14
txt_font = HPDF_GetFont (pdf, "Helvetica", NULL)
HPDF_Page_MoveTextPos (page, 0, -20)
HPDF_Page_SetFontAndSize (page, txt_font, 14)
HPDF_Page_ShowText (page, "This is arial")


HPDF_Page_EndText (page)

'save the document
HPDF_SaveToFile (pdf, "mydoc.pdf")

'clean up
HPDF_Free (pdf)

'****************************************************************************** 
'* End of main program
'****************************************************************************** 


sub error_handler cdecl (byval error_no as HPDF_STATUS, byval detail_no as HPDF_STATUS, byval user_data as any ptr) 
'****************************************************************************** 
'* Error handler
'****************************************************************************** 
' do something here ... 
  print "error_no: ", error_no
  print "detail_no:", detail_no
  print "data:     ", user_data

end sub
