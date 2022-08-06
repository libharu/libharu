##
## * << Haru Free PDF Library 2.0.8 >> -- hpdf.h
## *
## * URL http://libharu.org/
## *
## * Copyright (c) 1999-2006 Takeshi Kanno
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

import os
import sys

import types

def setpath():
    dllpath='%s/dll' %(os.path.dirname(os.path.realpath(__file__)))
    if 'PATH' in os.environ:
        if dllpath not in os.environ['PATH']:
            os.environ['PATH']='%s;%s' % (dllpath, os.environ['PATH'])
    else:
        os.environ['PATH']=dllpath
setpath()


from hpdf_consts import *
from hpdf_types import *

if os.sys.platform=='win32':
    harudll='libhpdf.dll'
    #haru=WinDLL(harudll)
    haru=CDLL(harudll)
else:
    harudll='libhpdf.so'
    haru=CDLL(harudll)

HPDF_HANDLE=c_void_p
HPDF_Doc=HPDF_HANDLE
HPDF_Page=HPDF_HANDLE
HPDF_Pages=HPDF_HANDLE
HPDF_Stream=HPDF_HANDLE
HPDF_Image=HPDF_HANDLE
HPDF_Font=HPDF_HANDLE
HPDF_Outline=HPDF_HANDLE
HPDF_Encoder=HPDF_HANDLE
HPDF_Destination=HPDF_HANDLE
HPDF_XObject=HPDF_HANDLE
HPDF_Annotation=HPDF_HANDLE
HPDF_ExtGState=HPDF_HANDLE


#const char * HPDF_GetVersion (void)
HPDF_GetVersion=haru.HPDF_GetVersion
HPDF_GetVersion.restype=c_char_p


#HPDF_Doc HPDF_NewEx (HPDF_Error_Handler user_error_fn, HPDF_Alloc_Func user_alloc_fn, HPDF_Free_Func user_free_fn, HPDF_UINT mem_pool_buf_size, void *user_data)
HPDF_NewEx=haru.HPDF_NewEx
HPDF_NewEx.restype=HPDF_Doc


#HPDF_Doc HPDF_New (HPDF_Error_Handler user_error_fn, void *user_data)
HPDF_New=haru.HPDF_New
HPDF_New.restype=HPDF_Doc


#HPDF_STATUS HPDF_SetErrorHandler (HPDF_Doc pdf, HPDF_Error_Handler user_error_fn)
HPDF_SetErrorHandler=haru.HPDF_SetErrorHandler
HPDF_SetErrorHandler.restype=HPDF_STATUS


#void HPDF_Free (HPDF_Doc pdf)
HPDF_Free=haru.HPDF_Free
HPDF_Free.restype=None


#HPDF_STATUS HPDF_NewDoc (HPDF_Doc pdf)
HPDF_NewDoc=haru.HPDF_NewDoc
HPDF_NewDoc.restype=HPDF_STATUS


#void HPDF_FreeDoc (HPDF_Doc pdf)
HPDF_FreeDoc=haru.HPDF_FreeDoc
HPDF_FreeDoc.restype=None


#HPDF_BOOL HPDF_HasDoc (HPDF_Doc pdf)
HPDF_HasDoc=haru.HPDF_HasDoc
HPDF_HasDoc.restype=HPDF_BOOL


#void HPDF_FreeDocAll (HPDF_Doc pdf)
HPDF_FreeDocAll=haru.HPDF_FreeDocAll
HPDF_FreeDocAll.restype=None


#HPDF_STATUS HPDF_SaveToStream (HPDF_Doc pdf)
HPDF_SaveToStream=haru.HPDF_SaveToStream
HPDF_SaveToStream.restype=HPDF_STATUS


#HPDF_UINT32 HPDF_GetStreamSize (HPDF_Doc pdf)
HPDF_GetStreamSize=haru.HPDF_GetStreamSize
HPDF_GetStreamSize.restype=HPDF_UINT32


#HPDF_STATUS HPDF_ReadFromStream (HPDF_Doc pdf, HPDF_BYTE *buf, HPDF_UINT32 *size)
_HPDF_ReadFromStream=haru.HPDF_ReadFromStream
_HPDF_ReadFromStream.restype=HPDF_STATUS
def HPDF_ReadFromStream(
                        pdf,    #HPDF_Doc
                        buf,    #POINTER(HPDF_BYTE)
                        size,    #POINTER(HPDF_UINT32)
                       ):
    if type(buf) in (types.ListType, types.TupleType):
        size=len(buf)
        buf=pointer((HPDF_BYTE*size)(*buf))
    size=HPDF_UINT32(int(size))
    return _HPDF_ReadFromStream(
                                pdf,    #HPDF_Doc
                                buf,    #POINTER(HPDF_BYTE)
                                size,    #POINTER(HPDF_UINT32)
                               )


#HPDF_STATUS HPDF_ResetStream (HPDF_Doc pdf)
HPDF_ResetStream=haru.HPDF_ResetStream
HPDF_ResetStream.restype=HPDF_STATUS


#HPDF_STATUS HPDF_SaveToFile (HPDF_Doc pdf, const char *file_name)
HPDF_SaveToFile=haru.HPDF_SaveToFile
HPDF_SaveToFile.restype=HPDF_STATUS


#HPDF_STATUS HPDF_GetError (HPDF_Doc pdf)
HPDF_GetError=haru.HPDF_GetError
HPDF_GetError.restype=HPDF_STATUS


#HPDF_STATUS HPDF_GetErrorDetail (HPDF_Doc pdf)
HPDF_GetErrorDetail=haru.HPDF_GetErrorDetail
HPDF_GetErrorDetail.restype=HPDF_STATUS


#void HPDF_ResetError (HPDF_Doc pdf)
HPDF_ResetError=haru.HPDF_ResetError
HPDF_ResetError.restype=None


#HPDF_STATUS HPDF_SetPagesConfiguration (HPDF_Doc pdf, HPDF_UINT page_per_pages)
_HPDF_SetPagesConfiguration=haru.HPDF_SetPagesConfiguration
_HPDF_SetPagesConfiguration.restype=HPDF_STATUS
def HPDF_SetPagesConfiguration(
                               pdf,    #HPDF_Doc
                               page_per_pages,    #HPDF_UINT
                              ):
    page_per_pages=HPDF_UINT(int(page_per_pages))
    return _HPDF_SetPagesConfiguration(
                                       pdf,    #HPDF_Doc
                                       page_per_pages,    #HPDF_UINT
                                      )


#HPDF_Page HPDF_GetPageByIndex (HPDF_Doc pdf, HPDF_UINT index)
HPDF_GetPageByIndex=haru.HPDF_GetPageByIndex
HPDF_GetPageByIndex.restype=HPDF_Page


#---------------------------------------------------------------------------
#---------------------------------------------------------------------------
#HPDF_PageLayout HPDF_GetPageLayout (HPDF_Doc pdf)
HPDF_GetPageLayout=haru.HPDF_GetPageLayout
HPDF_GetPageLayout.restype=HPDF_PageLayout


#HPDF_STATUS HPDF_SetPageLayout (HPDF_Doc pdf, HPDF_PageLayout layout)
HPDF_SetPageLayout=haru.HPDF_SetPageLayout
HPDF_SetPageLayout.restype=HPDF_STATUS


#HPDF_PageMode HPDF_GetPageMode (HPDF_Doc pdf)
HPDF_GetPageMode=haru.HPDF_GetPageMode
HPDF_GetPageMode.restype=HPDF_PageMode


#HPDF_STATUS HPDF_SetPageMode (HPDF_Doc pdf, HPDF_PageMode mode)
HPDF_SetPageMode=haru.HPDF_SetPageMode
HPDF_SetPageMode.restype=HPDF_STATUS


#HPDF_UINT HPDF_GetViewerPreference (HPDF_Doc pdf)
HPDF_GetViewerPreference=haru.HPDF_GetViewerPreference
HPDF_GetViewerPreference.restype=HPDF_UINT


#HPDF_STATUS HPDF_SetViewerPreference (HPDF_Doc pdf, HPDF_UINT value)
HPDF_SetViewerPreference=haru.HPDF_SetViewerPreference
HPDF_SetViewerPreference.restype=HPDF_STATUS


#HPDF_STATUS HPDF_SetOpenAction (HPDF_Doc pdf, HPDF_Destination open_action)
HPDF_SetOpenAction=haru.HPDF_SetOpenAction
HPDF_SetOpenAction.restype=HPDF_STATUS


#---------------------------------------------------------------------------
#----- page handling -------------------------------------------------------


#HPDF_Page HPDF_GetCurrentPage (HPDF_Doc pdf)
HPDF_GetCurrentPage=haru.HPDF_GetCurrentPage
HPDF_GetCurrentPage.restype=HPDF_Page


#HPDF_Page HPDF_AddPage (HPDF_Doc pdf)
HPDF_AddPage=haru.HPDF_AddPage
HPDF_AddPage.restype=HPDF_Page


#HPDF_Page HPDF_InsertPage (HPDF_Doc pdf, HPDF_Page page)
HPDF_InsertPage=haru.HPDF_InsertPage
HPDF_InsertPage.restype=HPDF_Page


#HPDF_STATUS HPDF_Page_SetWidth (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetWidth=haru.HPDF_Page_SetWidth
_HPDF_Page_SetWidth.restype=HPDF_STATUS
def HPDF_Page_SetWidth(
                       page,    #HPDF_Page
                       value,    #HPDF_REAL
                      ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetWidth(
                               page,    #HPDF_Page
                               value,    #HPDF_REAL
                              )


#HPDF_STATUS HPDF_Page_SetHeight (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetHeight=haru.HPDF_Page_SetHeight
_HPDF_Page_SetHeight.restype=HPDF_STATUS
def HPDF_Page_SetHeight(
                        page,    #HPDF_Page
                        value,    #HPDF_REAL
                       ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetHeight(
                                page,    #HPDF_Page
                                value,    #HPDF_REAL
                               )


#HPDF_STATUS
#HPDF_Page_SetSize  (HPDF_Page            page,
#                    HPDF_PageSizes       size,
#                    HPDF_PageDirection   direction);
HPDF_Page_SetSize=haru.HPDF_Page_SetSize
HPDF_Page_SetSize.restype=HPDF_STATUS


#HPDF_STATUS HPDF_Page_SetRotate (HPDF_Page page, HPDF_UINT16 angle)
_HPDF_Page_SetRotate=haru.HPDF_Page_SetRotate
_HPDF_Page_SetRotate.restype=HPDF_STATUS
def HPDF_Page_SetRotate(
                        page,    #HPDF_Page
                        angle,    #HPDF_UINT16
                       ):
    angle=HPDF_UINT16(int(angle))
    return _HPDF_Page_SetRotate(
                                page,    #HPDF_Page
                                angle,    #HPDF_UINT16
                               )

#---------------------------------------------------------------------------
#----- font handling -------------------------------------------------------


#HPDF_Font HPDF_GetFont (HPDF_Doc pdf, const char *font_name, const char *encoding_name)
HPDF_GetFont=haru.HPDF_GetFont
HPDF_GetFont.restype=HPDF_Font


#const char* HPDF_LoadType1FontFromFile (HPDF_Doc pdf, const char *afm_file_name, const char *data_file_name)
HPDF_LoadType1FontFromFile=haru.HPDF_LoadType1FontFromFile
HPDF_LoadType1FontFromFile.restype=c_char_p


#const char* HPDF_LoadTTFontFromFile (HPDF_Doc pdf, const char *file_name, HPDF_BOOL embedding)
HPDF_LoadTTFontFromFile=haru.HPDF_LoadTTFontFromFile
HPDF_LoadTTFontFromFile.restype=c_char_p


#const char* HPDF_LoadTTFontFromFile2 (HPDF_Doc pdf, const char *file_name, HPDF_UINT index, HPDF_BOOL embedding)
HPDF_LoadTTFontFromFile2=haru.HPDF_LoadTTFontFromFile2
HPDF_LoadTTFontFromFile2.restype=c_char_p


#HPDF_STATUS HPDF_AddPageLabel (HPDF_Doc pdf, HPDF_UINT page_num, HPDF_PageNumStyle style, HPDF_UINT first_page, const char *prefix)
_HPDF_AddPageLabel=haru.HPDF_AddPageLabel
_HPDF_AddPageLabel.restype=HPDF_STATUS
def HPDF_AddPageLabel(
                      pdf,    #HPDF_Doc
                      page_num,    #HPDF_UINT
                      style,    #HPDF_PageNumStyle
                      first_page,    #HPDF_UINT
                      prefix,    #c_char_p
                     ):
    page_num, first_page=[HPDF_UINT(int(i))for i in (page_num, first_page)]
    return _HPDF_AddPageLabel(
                              pdf,    #HPDF_Doc
                              page_num,    #HPDF_UINT
                              style,    #HPDF_PageNumStyle
                              first_page,    #HPDF_UINT
                              prefix,    #c_char_p
                             )

#HPDF_STATUS HPDF_UseJPFonts (HPDF_Doc pdf)
HPDF_UseJPFonts=haru.HPDF_UseJPFonts
HPDF_UseJPFonts.restype=HPDF_STATUS


#HPDF_STATUS HPDF_UseKRFonts (HPDF_Doc pdf)
HPDF_UseKRFonts=haru.HPDF_UseKRFonts
HPDF_UseKRFonts.restype=HPDF_STATUS


#HPDF_STATUS HPDF_UseCNSFonts (HPDF_Doc pdf)
HPDF_UseCNSFonts=haru.HPDF_UseCNSFonts
HPDF_UseCNSFonts.restype=HPDF_STATUS


#HPDF_STATUS HPDF_UseCNTFonts (HPDF_Doc pdf)
HPDF_UseCNTFonts=haru.HPDF_UseCNTFonts
HPDF_UseCNTFonts.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#----- outline ------------------------------------------------------------


#HPDF_Outline HPDF_CreateOutline (HPDF_Doc pdf, HPDF_Outline parent, const char *title, HPDF_Encoder encoder)
HPDF_CreateOutline=haru.HPDF_CreateOutline
HPDF_CreateOutline.restype=HPDF_Outline


#HPDF_STATUS HPDF_Outline_SetOpened (HPDF_Outline outline, HPDF_BOOL opened)
HPDF_Outline_SetOpened=haru.HPDF_Outline_SetOpened
HPDF_Outline_SetOpened.restype=HPDF_STATUS


#HPDF_STATUS HPDF_Outline_SetDestination (HPDF_Outline outline, HPDF_Destination dst)
HPDF_Outline_SetDestination=haru.HPDF_Outline_SetDestination
HPDF_Outline_SetDestination.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#----- destination --------------------------------------------------------
#HPDF_Destination HPDF_Page_CreateDestination (HPDF_Page page)
HPDF_Page_CreateDestination=haru.HPDF_Page_CreateDestination
HPDF_Page_CreateDestination.restype=HPDF_Destination


#HPDF_STATUS HPDF_Destination_SetXYZ (HPDF_Destination dst, HPDF_REAL left, HPDF_REAL top, HPDF_REAL zoom)
_HPDF_Destination_SetXYZ=haru.HPDF_Destination_SetXYZ
_HPDF_Destination_SetXYZ.restype=HPDF_STATUS
def HPDF_Destination_SetXYZ(
                            dst,    #HPDF_Destination
                            left,    #HPDF_REAL
                            top,    #HPDF_REAL
                            zoom,    #HPDF_REAL
                           ):
    left=HPDF_REAL(left)
    top=HPDF_REAL(top)
    zoom=HPDF_REAL(zoom)
    return _HPDF_Destination_SetXYZ(
                                    dst,    #HPDF_Destination
                                    left,    #HPDF_REAL
                                    top,    #HPDF_REAL
                                    zoom,    #HPDF_REAL
                                   )


#HPDF_STATUS HPDF_Destination_SetFit (HPDF_Destination dst)
HPDF_Destination_SetFit=haru.HPDF_Destination_SetFit
HPDF_Destination_SetFit.restype=HPDF_STATUS


#HPDF_STATUS HPDF_Destination_SetFitH (HPDF_Destination dst, HPDF_REAL top)
_HPDF_Destination_SetFitH=haru.HPDF_Destination_SetFitH
_HPDF_Destination_SetFitH.restype=HPDF_STATUS
def HPDF_Destination_SetFitH(
                             dst,    #HPDF_Destination
                             top,    #HPDF_REAL
                            ):
    top=HPDF_REAL(top)
    return _HPDF_Destination_SetFitH(
                                     dst,    #HPDF_Destination
                                     top,    #HPDF_REAL
                                    )


#HPDF_STATUS HPDF_Destination_SetFitV (HPDF_Destination dst, HPDF_REAL left)
_HPDF_Destination_SetFitV=haru.HPDF_Destination_SetFitV
_HPDF_Destination_SetFitV.restype=HPDF_STATUS
def HPDF_Destination_SetFitV(
                             dst,    #HPDF_Destination
                             left,    #HPDF_REAL
                            ):
    left=HPDF_REAL(left)
    return _HPDF_Destination_SetFitV(
                                     dst,    #HPDF_Destination
                                     left,    #HPDF_REAL
                                    )


#HPDF_STATUS HPDF_Destination_SetFitR (HPDF_Destination dst, HPDF_REAL left, HPDF_REAL bottom, HPDF_REAL right, HPDF_REAL top)
_HPDF_Destination_SetFitR=haru.HPDF_Destination_SetFitR
_HPDF_Destination_SetFitR.restype=HPDF_STATUS
def HPDF_Destination_SetFitR(
                             dst,    #HPDF_Destination
                             left,    #HPDF_REAL
                             bottom,    #HPDF_REAL
                             right,    #HPDF_REAL
                             top,    #HPDF_REAL
                            ):
    left=HPDF_REAL(left)
    bottom=HPDF_REAL(bottom)
    right=HPDF_REAL(right)
    top=HPDF_REAL(top)
    return _HPDF_Destination_SetFitR(
                                     dst,    #HPDF_Destination
                                     left,    #HPDF_REAL
                                     bottom,    #HPDF_REAL
                                     right,    #HPDF_REAL
                                     top,    #HPDF_REAL
                                    )


#HPDF_STATUS HPDF_Destination_SetFitB (HPDF_Destination dst)
HPDF_Destination_SetFitB=haru.HPDF_Destination_SetFitB
HPDF_Destination_SetFitB.restype=HPDF_STATUS


#HPDF_STATUS HPDF_Destination_SetFitBH (HPDF_Destination dst, HPDF_REAL top)
_HPDF_Destination_SetFitBH=haru.HPDF_Destination_SetFitBH
_HPDF_Destination_SetFitBH.restype=HPDF_STATUS
def HPDF_Destination_SetFitBH(
                              dst,    #HPDF_Destination
                              top,    #HPDF_REAL
                             ):
    top=HPDF_REAL(top)
    return _HPDF_Destination_SetFitBH(
                                      dst,    #HPDF_Destination
                                      top,    #HPDF_REAL
                                     )


#HPDF_STATUS HPDF_Destination_SetFitBV (HPDF_Destination dst, HPDF_REAL left)
_HPDF_Destination_SetFitBV=haru.HPDF_Destination_SetFitBV
_HPDF_Destination_SetFitBV.restype=HPDF_STATUS
def HPDF_Destination_SetFitBV(
                              dst,    #HPDF_Destination
                              left,    #HPDF_REAL
                             ):
    left=HPDF_REAL(left)
    return _HPDF_Destination_SetFitBV(
                                      dst,    #HPDF_Destination
                                      left,    #HPDF_REAL
                                     )


#--------------------------------------------------------------------------
#----- encoder ------------------------------------------------------------
#HPDF_Encoder HPDF_GetEncoder (HPDF_Doc pdf, const char *encoding_name)
HPDF_GetEncoder=haru.HPDF_GetEncoder
HPDF_GetEncoder.restype=HPDF_Encoder


#HPDF_Encoder HPDF_GetCurrentEncoder (HPDF_Doc pdf)
HPDF_GetCurrentEncoder=haru.HPDF_GetCurrentEncoder
HPDF_GetCurrentEncoder.restype=HPDF_Encoder


#HPDF_STATUS HPDF_SetCurrentEncoder (HPDF_Doc pdf, const char *encoding_name)
HPDF_SetCurrentEncoder=haru.HPDF_SetCurrentEncoder
HPDF_SetCurrentEncoder.restype=HPDF_STATUS


#HPDF_EncoderType HPDF_Encoder_GetType (HPDF_Encoder encoder)
HPDF_Encoder_GetType=haru.HPDF_Encoder_GetType
HPDF_Encoder_GetType.restype=HPDF_EncoderType

#HPDF_ByteType HPDF_Encoder_GetByteType (HPDF_Encoder encoder, const char *text, HPDF_UINT index)
_HPDF_Encoder_GetByteType=haru.HPDF_Encoder_GetByteType
_HPDF_Encoder_GetByteType.restype=HPDF_ByteType
def HPDF_Encoder_GetByteType(
                             encoder,       #HPDF_Encoder
                             text,          #const char *
                             index          #HPDF_UINT
                            ):
    if type(text) in (types.ListType, types.TupleType):
        if type(text[-1]) != types.StringType:
            text=[chr(i) for i in text]
        text=''.join(text)
    return _HPDF_Encoder_GetByteType(
                                     encoder,       #HPDF_Encoder
                                     text,          #const char *
                                     index          #HPDF_UINT
                                    )

#HPDF_UNICODE HPDF_Encoder_GetUnicode (HPDF_Encoder encoder, HPDF_UINT16 code)
HPDF_Encoder_GetUnicode=haru.HPDF_Encoder_GetUnicode
HPDF_Encoder_GetUnicode.restype=HPDF_UNICODE


#HPDF_WritingMode HPDF_Encoder_GetWritingMode (HPDF_Encoder encoder)
HPDF_Encoder_GetWritingMode=haru.HPDF_Encoder_GetWritingMode
HPDF_Encoder_GetWritingMode.restype=HPDF_WritingMode


#HPDF_STATUS HPDF_UseJPEncodings (HPDF_Doc pdf)
HPDF_UseJPEncodings=haru.HPDF_UseJPEncodings
HPDF_UseJPEncodings.restype=HPDF_STATUS


#HPDF_STATUS HPDF_UseKREncodings (HPDF_Doc pdf)
HPDF_UseKREncodings=haru.HPDF_UseKREncodings
HPDF_UseKREncodings.restype=HPDF_STATUS


#HPDF_STATUS HPDF_UseCNSEncodings (HPDF_Doc pdf)
HPDF_UseCNSEncodings=haru.HPDF_UseCNSEncodings
HPDF_UseCNSEncodings.restype=HPDF_STATUS


#HPDF_STATUS HPDF_UseCNTEncodings (HPDF_Doc pdf)
HPDF_UseCNTEncodings=haru.HPDF_UseCNTEncodings
HPDF_UseCNTEncodings.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#----- annotation ---------------------------------------------------------
#HPDF_Annotation HPDF_Page_CreateTextAnnot (HPDF_Page page, HPDF_Rect rect, const char *text, HPDF_Encoder encoder)
HPDF_Page_CreateTextAnnot=haru.HPDF_Page_CreateTextAnnot
HPDF_Page_CreateTextAnnot.restype=HPDF_Annotation


#HPDF_Annotation HPDF_Page_CreateLinkAnnot (HPDF_Page page, HPDF_Rect rect, HPDF_Destination dst)
HPDF_Page_CreateLinkAnnot=haru.HPDF_Page_CreateLinkAnnot
HPDF_Page_CreateLinkAnnot.restype=HPDF_Annotation


#HPDF_Annotation HPDF_Page_CreateURILinkAnnot (HPDF_Page page, HPDF_Rect rect, const char *uri)
HPDF_Page_CreateURILinkAnnot=haru.HPDF_Page_CreateURILinkAnnot
HPDF_Page_CreateURILinkAnnot.restype=HPDF_Annotation


#HPDF_STATUS HPDF_LinkAnnot_SetHighlightMode (HPDF_Annotation annot, HPDF_AnnotHighlightMode mode)
HPDF_LinkAnnot_SetHighlightMode=haru.HPDF_LinkAnnot_SetHighlightMode
HPDF_LinkAnnot_SetHighlightMode.restype=HPDF_STATUS


#HPDF_STATUS HPDF_LinkAnnot_SetBorderStyle (HPDF_Annotation annot, HPDF_REAL width, HPDF_UINT16 dash_on, HPDF_UINT16 dash_off)
_HPDF_LinkAnnot_SetBorderStyle=haru.HPDF_LinkAnnot_SetBorderStyle
_HPDF_LinkAnnot_SetBorderStyle.restype=HPDF_STATUS
def HPDF_LinkAnnot_SetBorderStyle(
                                  annot,    #HPDF_Annotation
                                  width,    #HPDF_REAL
                                  dash_on,    #HPDF_UINT16
                                  dash_off,    #HPDF_UINT16
                                 ):
    width=HPDF_REAL(width)
    dash_on=HPDF_UINT16(dash_on)
    dash_off=HPDF_UINT16(dash_off)
    return _HPDF_LinkAnnot_SetBorderStyle(
                                          annot,    #HPDF_Annotation
                                          width,    #HPDF_REAL
                                          dash_on,    #HPDF_UINT16
                                          dash_off,    #HPDF_UINT16
                                         )


#HPDF_STATUS HPDF_TextAnnot_SetIcon (HPDF_Annotation annot, HPDF_AnnotIcon icon)
HPDF_TextAnnot_SetIcon=haru.HPDF_TextAnnot_SetIcon
HPDF_TextAnnot_SetIcon.restype=HPDF_STATUS


#HPDF_STATUS HPDF_TextAnnot_SetOpened (HPDF_Annotation annot, HPDF_BOOL opened)
HPDF_TextAnnot_SetOpened=haru.HPDF_TextAnnot_SetOpened
HPDF_TextAnnot_SetOpened.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#----- image data ---------------------------------------------------------
#HPDF_Image HPDF_LoadPngImageFromFile (HPDF_Doc pdf, const char *filename)
HPDF_LoadPngImageFromFile=haru.HPDF_LoadPngImageFromFile
HPDF_LoadPngImageFromFile.restype=HPDF_Image


#HPDF_Image HPDF_LoadPngImageFromFile2 (HPDF_Doc pdf, const char *filename)
HPDF_LoadPngImageFromFile2=haru.HPDF_LoadPngImageFromFile2
HPDF_LoadPngImageFromFile2.restype=HPDF_Image


#HPDF_Image HPDF_LoadJpegImageFromFile (HPDF_Doc pdf, const char *filename)
HPDF_LoadJpegImageFromFile=haru.HPDF_LoadJpegImageFromFile
HPDF_LoadJpegImageFromFile.restype=HPDF_Image


#HPDF_Image HPDF_LoadRawImageFromFile (HPDF_Doc pdf, const char *filename, HPDF_UINT width, HPDF_UINT height, HPDF_ColorSpace color_space)
_HPDF_LoadRawImageFromFile=haru.HPDF_LoadRawImageFromFile
_HPDF_LoadRawImageFromFile.restype=HPDF_Image
def HPDF_LoadRawImageFromFile(
                              pdf,    #HPDF_Doc
                              filename,    #c_char_p
                              width,    #HPDF_UINT
                              height,    #HPDF_UINT
                              color_space,    #HPDF_ColorSpace
                             ):
    width=HPDF_UINT(width)
    height=HPDF_UINT(height)
    return _HPDF_LoadRawImageFromFile(
                                      pdf,    #HPDF_Doc
                                      filename,    #c_char_p
                                      width,    #HPDF_UINT
                                      height,    #HPDF_UINT
                                      color_space,    #HPDF_ColorSpace
                                     )


#HPDF_Image HPDF_LoadRawImageFromMem (HPDF_Doc pdf, const HPDF_BYTE *buf, HPDF_UINT width, HPDF_UINT height, HPDF_ColorSpace color_space, HPDF_UINT bits_per_component)
_HPDF_LoadRawImageFromMem=haru.HPDF_LoadRawImageFromMem
_HPDF_LoadRawImageFromMem.restype=HPDF_Image
def HPDF_LoadRawImageFromMem(
                             pdf,    #HPDF_Doc
                             buf,    #POINTER(HPDF_BYTE)
                             width,    #HPDF_UINT
                             height,    #HPDF_UINT
                             color_space,    #HPDF_ColorSpace
                             bits_per_component,    #HPDF_UINT
                            ):
    if type(buf) in (types.ListType, types.TupleType):
        size=len(buf)
        buf=pointer((HPDF_BYTE*size)(*buf))
        if height in [0, None]:
            height=size/width
    width=HPDF_UINT(width)
    height=HPDF_UINT(height)
    bits_per_component=HPDF_UINT(bits_per_component)
    return _HPDF_LoadRawImageFromMem(
                                     pdf,    #HPDF_Doc
                                     buf,    #POINTER(HPDF_BYTE)
                                     width,    #HPDF_UINT
                                     height,    #HPDF_UINT
                                     color_space,    #HPDF_ColorSpace
                                     bits_per_component,    #HPDF_UINT
                                    )


#HPDF_Point HPDF_Image_GetSize (HPDF_Image image)
HPDF_Image_GetSize=haru.HPDF_Image_GetSize
HPDF_Image_GetSize.restype=HPDF_Point


#HPDF_STATUS HPDF_Image_GetSize2 (HPDF_Image image, HPDF_Point *size)
_HPDF_Image_GetSize2=haru.HPDF_Image_GetSize2
_HPDF_Image_GetSize2.restype=HPDF_STATUS
def HPDF_Image_GetSize2(
                        image,    #HPDF_Image
                        size=None,    #POINTER(HPDF_Point)
                       ):
    size=HPDF_Point
    ret= _HPDF_Image_GetSize2(
                              image,    #HPDF_Image
                              size,    #POINTER(HPDF_Point)
                             )
    return ret, size.x, size.y


#HPDF_UINT HPDF_Image_GetWidth (HPDF_Image image)
HPDF_Image_GetWidth=haru.HPDF_Image_GetWidth
HPDF_Image_GetWidth.restype=HPDF_UINT


#HPDF_UINT HPDF_Image_GetHeight (HPDF_Image image)
HPDF_Image_GetHeight=haru.HPDF_Image_GetHeight
HPDF_Image_GetHeight.restype=HPDF_UINT


#HPDF_UINT HPDF_Image_GetBitsPerComponent (HPDF_Image image)
HPDF_Image_GetBitsPerComponent=haru.HPDF_Image_GetBitsPerComponent
HPDF_Image_GetBitsPerComponent.restype=HPDF_UINT


#const char* HPDF_Image_GetColorSpace (HPDF_Image image)
HPDF_Image_GetColorSpace=haru.HPDF_Image_GetColorSpace
HPDF_Image_GetColorSpace.restype=c_char_p


#HPDF_STATUS HPDF_Image_SetColorMask (HPDF_Image image, HPDF_UINT rmin, HPDF_UINT rmax, HPDF_UINT gmin, HPDF_UINT gmax, HPDF_UINT bmin, HPDF_UINT bmax)
_HPDF_Image_SetColorMask=haru.HPDF_Image_SetColorMask
_HPDF_Image_SetColorMask.restype=HPDF_STATUS
def HPDF_Image_SetColorMask(
                            image,    #HPDF_Image
                            rmin,    #HPDF_UINT
                            rmax,    #HPDF_UINT
                            gmin,    #HPDF_UINT
                            gmax,    #HPDF_UINT
                            bmin,    #HPDF_UINT
                            bmax,    #HPDF_UINT
                           ):
    rmin=HPDF_UINT(rmin)
    rmax=HPDF_UINT(rmax)
    gmin=HPDF_UINT(gmin)
    gmax=HPDF_UINT(gmax)
    bmin=HPDF_UINT(bmin)
    bmax=HPDF_UINT(bmax)
    return _HPDF_Image_SetColorMask(
                                    image,    #HPDF_Image
                                    rmin,    #HPDF_UINT
                                    rmax,    #HPDF_UINT
                                    gmin,    #HPDF_UINT
                                    gmax,    #HPDF_UINT
                                    bmin,    #HPDF_UINT
                                    bmax,    #HPDF_UINT
                                   )


#HPDF_STATUS HPDF_Image_SetMaskImage (HPDF_Image image, HPDF_Image mask_image)
HPDF_Image_SetMaskImage=haru.HPDF_Image_SetMaskImage
HPDF_Image_SetMaskImage.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#----- info dictionary ----------------------------------------------------
#HPDF_STATUS HPDF_SetInfoAttr (HPDF_Doc pdf, HPDF_InfoType type, const char *value)
HPDF_SetInfoAttr=haru.HPDF_SetInfoAttr
HPDF_SetInfoAttr.restype=HPDF_STATUS


#const char* HPDF_GetInfoAttr (HPDF_Doc pdf, HPDF_InfoType type)
HPDF_GetInfoAttr=haru.HPDF_GetInfoAttr
HPDF_GetInfoAttr.restype=c_char_p


#HPDF_STATUS HPDF_SetInfoDateAttr (HPDF_Doc pdf, HPDF_InfoType type, HPDF_Date value)
HPDF_SetInfoDateAttr=haru.HPDF_SetInfoDateAttr
HPDF_SetInfoDateAttr.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#----- encryption ---------------------------------------------------------
#HPDF_STATUS HPDF_SetPassword (HPDF_Doc pdf, const char *owner_passwd, const char *user_passwd)
HPDF_SetPassword=haru.HPDF_SetPassword
HPDF_SetPassword.restype=HPDF_STATUS

#HPDF_STATUS HPDF_SetPermission (HPDF_Doc pdf, HPDF_UINT permission)
_HPDF_SetPermission=haru.HPDF_SetPermission
_HPDF_SetPermission.restype=HPDF_STATUS
def HPDF_SetPermission(
                       pdf,    #HPDF_Doc
                       permission,    #HPDF_UINT
                      ):
    permission=HPDF_UINT(int(permission))
    return _HPDF_SetPermission(
                               pdf,    #HPDF_Doc
                               permission,    #HPDF_UINT
                              )


#HPDF_STATUS HPDF_SetEncryptionMode (HPDF_Doc pdf, HPDF_EncryptMode mode, HPDF_UINT key_len)
_HPDF_SetEncryptionMode=haru.HPDF_SetEncryptionMode
_HPDF_SetEncryptionMode.restype=HPDF_STATUS
def HPDF_SetEncryptionMode(
                           pdf,    #HPDF_Doc
                           mode,    #HPDF_EncryptMode
                           key_len,    #HPDF_UINT
                          ):
    key_len=HPDF_UINT(int(key_len))
    return _HPDF_SetEncryptionMode(
                                   pdf,    #HPDF_Doc
                                   mode,    #HPDF_EncryptMode
                                   key_len,    #HPDF_UINT
                                  )


#--------------------------------------------------------------------------
#----- compression --------------------------------------------------------
#HPDF_STATUS HPDF_SetCompressionMode (HPDF_Doc pdf, HPDF_UINT mode)
HPDF_SetCompressionMode=haru.HPDF_SetCompressionMode
HPDF_SetCompressionMode.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#----- font ---------------------------------------------------------------
#const char* HPDF_Font_GetFontName (HPDF_Font font)
HPDF_Font_GetFontName=haru.HPDF_Font_GetFontName
HPDF_Font_GetFontName.restype=c_char_p


#const char* HPDF_Font_GetEncodingName (HPDF_Font font)
HPDF_Font_GetEncodingName=haru.HPDF_Font_GetEncodingName
HPDF_Font_GetEncodingName.restype=c_char_p


#HPDF_INT HPDF_Font_GetUnicodeWidth (HPDF_Font font, HPDF_UNICODE code)
HPDF_Font_GetUnicodeWidth=haru.HPDF_Font_GetUnicodeWidth
HPDF_Font_GetUnicodeWidth.restype=HPDF_INT


#HPDF_Box HPDF_Font_GetBBox (HPDF_Font font)
HPDF_Font_GetBBox=haru.HPDF_Font_GetBBox
HPDF_Font_GetBBox.restype=HPDF_Box

#HPDF_INT HPDF_Font_GetAscent (HPDF_Font font)
HPDF_Font_GetAscent=haru.HPDF_Font_GetAscent
HPDF_Font_GetAscent.restype=HPDF_INT

#HPDF_INT HPDF_Font_GetDescent (HPDF_Font font)
HPDF_Font_GetDescent=haru.HPDF_Font_GetDescent
HPDF_Font_GetDescent.restype=HPDF_INT

#HPDF_UINT HPDF_Font_GetXHeight (HPDF_Font font)
HPDF_Font_GetXHeight=haru.HPDF_Font_GetXHeight
HPDF_Font_GetXHeight.restype=HPDF_UINT


#HPDF_UINT HPDF_Font_GetCapHeight (HPDF_Font font)
HPDF_Font_GetCapHeight=haru.HPDF_Font_GetCapHeight
HPDF_Font_GetCapHeight.restype=HPDF_UINT


#HPDF_TextWidth HPDF_Font_TextWidth (HPDF_Font font, const HPDF_BYTE *text, HPDF_UINT len)
HPDF_Font_TextWidth=haru.HPDF_Font_TextWidth
HPDF_Font_TextWidth.restype=HPDF_TextWidth


#HPDF_UINT HPDF_Font_MeasureText (HPDF_Font font, const HPDF_BYTE *text, HPDF_UINT len, HPDF_REAL width, HPDF_REAL font_size, HPDF_REAL char_space, HPDF_REAL word_space, HPDF_BOOL wordwrap, HPDF_REAL *real_width)
_HPDF_Font_MeasureText=haru.HPDF_Font_MeasureText
_HPDF_Font_MeasureText.restype=HPDF_UINT
def HPDF_Font_MeasureText(
                          font,    #HPDF_Font
                          text,    #POINTER(HPDF_BYTE)
                          length,    #HPDF_UINT
                          width,    #HPDF_REAL
                          font_size,    #HPDF_REAL
                          char_space,    #HPDF_REAL
                          word_space,    #HPDF_REAL
                          wordwrap,    #HPDF_BOOL
                          real_width,    #POINTER(HPDF_REAL)
                         ):
    if type(text) in (types.TupleType, types.ListType):
        length=len(text)
        text=pointer((HPDF_BYTE*length)(*text))

    length=HPDF_UINT(int(length))

    width=HPDF_REAL(width)
    font_size=HPDF_REAL(font_size)
    char_space=HPDF_REAL(char_space)
    word_space=HPDF_REAL(word_space)
    real_width=HPDF_REAL(real_width)
    return _HPDF_Font_MeasureText(
                                  font,    #HPDF_Font
                                  text,    #POINTER(HPDF_BYTE)
                                  length,    #HPDF_UINT
                                  width,    #HPDF_REAL
                                  font_size,    #HPDF_REAL
                                  char_space,    #HPDF_REAL
                                  word_space,    #HPDF_REAL
                                  wordwrap,    #HPDF_BOOL
                                  real_width,    #POINTER(HPDF_REAL)
                                 )


#--------------------------------------------------------------------------
#----- extended graphics state --------------------------------------------
#HPDF_ExtGState HPDF_CreateExtGState (HPDF_Doc pdf)
HPDF_CreateExtGState=haru.HPDF_CreateExtGState
HPDF_CreateExtGState.restype=HPDF_ExtGState


#HPDF_STATUS HPDF_ExtGState_SetAlphaStroke (HPDF_ExtGState ext_gstate, HPDF_REAL value)
_HPDF_ExtGState_SetAlphaStroke=haru.HPDF_ExtGState_SetAlphaStroke
_HPDF_ExtGState_SetAlphaStroke.restype=HPDF_STATUS
def HPDF_ExtGState_SetAlphaStroke(
                                  ext_gstate,    #HPDF_ExtGState
                                  value,    #HPDF_REAL
                                 ):
    value=HPDF_REAL(value)
    return _HPDF_ExtGState_SetAlphaStroke(
                                          ext_gstate,    #HPDF_ExtGState
                                          value,    #HPDF_REAL
                                         )


#HPDF_STATUS HPDF_ExtGState_SetAlphaFill (HPDF_ExtGState ext_gstate, HPDF_REAL value)
_HPDF_ExtGState_SetAlphaFill=haru.HPDF_ExtGState_SetAlphaFill
_HPDF_ExtGState_SetAlphaFill.restype=HPDF_STATUS
def HPDF_ExtGState_SetAlphaFill(
                                ext_gstate,    #HPDF_ExtGState
                                value,    #HPDF_REAL
                               ):
    value=HPDF_REAL(value)
    return _HPDF_ExtGState_SetAlphaFill(
                                        ext_gstate,    #HPDF_ExtGState
                                        value,    #HPDF_REAL
                                       )


#HPDF_STATUS HPDF_ExtGState_SetBlendMode (HPDF_ExtGState ext_gstate, HPDF_BlendMode mode)
HPDF_ExtGState_SetBlendMode=haru.HPDF_ExtGState_SetBlendMode
HPDF_ExtGState_SetBlendMode.restype=HPDF_STATUS


#--------------------------------------------------------------------------
#--------------------------------------------------------------------------
#HPDF_REAL HPDF_Page_TextWidth (HPDF_Page page, const char *text)
_HPDF_Page_TextWidth=haru.HPDF_Page_TextWidth
_HPDF_Page_TextWidth.restype=HPDF_REAL
def HPDF_Page_TextWidth(
                        page,           #HPDF_Page
                        text,           #c_char_p
                       ):
    if type(text) in (types.ListType, types.TupleType):
        if type(text[-1]) != types.StringType:
            text=[chr(i) for i in text]
        text=''.join(text)

    return _HPDF_Page_TextWidth(
                                page,           #HPDF_Page
                                text,           #c_char_p
                               )


#HPDF_UINT HPDF_Page_MeasureText (HPDF_Page page, const char *text, HPDF_REAL width, HPDF_BOOL wordwrap, HPDF_REAL *real_width)
_HPDF_Page_MeasureText=haru.HPDF_Page_MeasureText
_HPDF_Page_MeasureText.restype=HPDF_UINT
def HPDF_Page_MeasureText(
                          page,    #HPDF_Page
                          text,    #c_char_p
                          width,    #HPDF_REAL
                          wordwrap,    #HPDF_BOOL
                          real_width,    #POINTER(HPDF_REAL)
                         ):
    width=HPDF_REAL(width)
    real_width=HPDF_REAL(real_width)
    return _HPDF_Page_MeasureText(
                                  page,    #HPDF_Page
                                  text,    #c_char_p
                                  width,    #HPDF_REAL
                                  wordwrap,    #HPDF_BOOL
                                  real_width,    #POINTER(HPDF_REAL)
                                 )


#HPDF_REAL
#HPDF_Page_GetWidth  (HPDF_Page   page);
HPDF_Page_GetWidth=haru.HPDF_Page_GetWidth
HPDF_Page_GetWidth.restype=HPDF_REAL


#HPDF_REAL HPDF_Page_GetHeight (HPDF_Page page)
HPDF_Page_GetHeight=haru.HPDF_Page_GetHeight
HPDF_Page_GetHeight.restype=HPDF_REAL


#HPDF_UINT16 HPDF_Page_GetGMode (HPDF_Page page)
HPDF_Page_GetGMode=haru.HPDF_Page_GetGMode
HPDF_Page_GetGMode.restype=HPDF_UINT16


#HPDF_Point HPDF_Page_GetCurrentPos (HPDF_Page page)
HPDF_Page_GetCurrentPos=haru.HPDF_Page_GetCurrentPos
HPDF_Page_GetCurrentPos.restype=HPDF_Point


#HPDF_STATUS HPDF_Page_GetCurrentPos2 (HPDF_Page page, HPDF_Point *pos)
_HPDF_Page_GetCurrentPos2=haru.HPDF_Page_GetCurrentPos2
_HPDF_Page_GetCurrentPos2.restype=HPDF_STATUS
def HPDF_Page_GetCurrentPos2(
                             page,    #HPDF_Page
                             pos=None,    #POINTER(HPDF_Point)
                            ):
    pos=HPDF_Point()
    ret= _HPDF_Page_GetCurrentPos2(
                                   page,    #HPDF_Page
                                   pos,    #POINTER(HPDF_Point)
                                  )
    return ret, pos.x, pos.y


#HPDF_Point HPDF_Page_GetCurrentTextPos (HPDF_Page page)
HPDF_Page_GetCurrentTextPos=haru.HPDF_Page_GetCurrentTextPos
HPDF_Page_GetCurrentTextPos.restype=HPDF_Point


#HPDF_STATUS HPDF_Page_GetCurrentTextPos2 (HPDF_Page page, HPDF_Point *pos)
_HPDF_Page_GetCurrentTextPos2=haru.HPDF_Page_GetCurrentTextPos2
_HPDF_Page_GetCurrentTextPos2.restype=HPDF_STATUS
def HPDF_Page_GetCurrentTextPos2(
                                 page,    #HPDF_Page
                                 pos=None,    #POINTER(HPDF_Point)
                                ):
    pos=HPDF_Point()
    ret= _HPDF_Page_GetCurrentTextPos2(
                                       page,    #HPDF_Page
                                       pos,    #POINTER(HPDF_Point)
                                      )
    return ret, pos.x, pos.y


#HPDF_Font HPDF_Page_GetCurrentFont (HPDF_Page page)
HPDF_Page_GetCurrentFont=haru.HPDF_Page_GetCurrentFont
HPDF_Page_GetCurrentFont.restype=HPDF_Font


#HPDF_REAL HPDF_Page_GetCurrentFontSize (HPDF_Page page)
HPDF_Page_GetCurrentFontSize=haru.HPDF_Page_GetCurrentFontSize
HPDF_Page_GetCurrentFontSize.restype=HPDF_REAL


#HPDF_TransMatrix HPDF_Page_GetTransMatrix (HPDF_Page page)
HPDF_Page_GetTransMatrix=haru.HPDF_Page_GetTransMatrix
HPDF_Page_GetTransMatrix.restype=HPDF_TransMatrix


#HPDF_REAL HPDF_Page_GetLineWidth (HPDF_Page page)
HPDF_Page_GetLineWidth=haru.HPDF_Page_GetLineWidth
HPDF_Page_GetLineWidth.restype=HPDF_REAL

#HPDF_LineCap HPDF_Page_GetLineCap (HPDF_Page page)
HPDF_Page_GetLineCap=haru.HPDF_Page_GetLineCap
HPDF_Page_GetLineCap.restype=HPDF_LineCap


#HPDF_LineJoin HPDF_Page_GetLineJoin (HPDF_Page page)
HPDF_Page_GetLineJoin=haru.HPDF_Page_GetLineJoin
HPDF_Page_GetLineJoin.restype=HPDF_LineJoin


#HPDF_REAL HPDF_Page_GetMiterLimit (HPDF_Page page)
HPDF_Page_GetMiterLimit=haru.HPDF_Page_GetMiterLimit
HPDF_Page_GetMiterLimit.restype=HPDF_REAL


#HPDF_DashMode HPDF_Page_GetDash (HPDF_Page page)
HPDF_Page_GetDash=haru.HPDF_Page_GetDash
HPDF_Page_GetDash.restype=HPDF_DashMode


#HPDF_REAL HPDF_Page_GetFlat (HPDF_Page page)
HPDF_Page_GetFlat=haru.HPDF_Page_GetFlat
HPDF_Page_GetFlat.restype=HPDF_REAL


#HPDF_REAL HPDF_Page_GetCharSpace (HPDF_Page page)
HPDF_Page_GetCharSpace=haru.HPDF_Page_GetCharSpace
HPDF_Page_GetCharSpace.restype=HPDF_REAL


#HPDF_REAL HPDF_Page_GetWordSpace (HPDF_Page page)
HPDF_Page_GetWordSpace=haru.HPDF_Page_GetWordSpace
HPDF_Page_GetWordSpace.restype=HPDF_REAL


#HPDF_REAL HPDF_Page_GetHorizontalScalling (HPDF_Page page)
HPDF_Page_GetHorizontalScalling=haru.HPDF_Page_GetHorizontalScalling
HPDF_Page_GetHorizontalScalling.restype=HPDF_REAL


#HPDF_REAL HPDF_Page_GetTextLeading (HPDF_Page page)
HPDF_Page_GetTextLeading=haru.HPDF_Page_GetTextLeading
HPDF_Page_GetTextLeading.restype=HPDF_REAL


#HPDF_TextRenderingMode HPDF_Page_GetTextRenderingMode (HPDF_Page page)
HPDF_Page_GetTextRenderingMode=haru.HPDF_Page_GetTextRenderingMode
HPDF_Page_GetTextRenderingMode.restype=HPDF_TextRenderingMode


# This function is obsolete. Use HPDF_Page_GetTextRise.

#HPDF_REAL HPDF_Page_GetTextRaise (HPDF_Page page)
HPDF_Page_GetTextRaise=haru.HPDF_Page_GetTextRaise
HPDF_Page_GetTextRaise.restype=HPDF_REAL


#HPDF_REAL HPDF_Page_GetTextRise (HPDF_Page page)
HPDF_Page_GetTextRise=haru.HPDF_Page_GetTextRise
HPDF_Page_GetTextRise.restype=HPDF_REAL


#HPDF_RGBColor HPDF_Page_GetRGBFill (HPDF_Page page)
HPDF_Page_GetRGBFill=haru.HPDF_Page_GetRGBFill
HPDF_Page_GetRGBFill.restype=HPDF_RGBColor


#HPDF_RGBColor HPDF_Page_GetRGBStroke (HPDF_Page page)
HPDF_Page_GetRGBStroke=haru.HPDF_Page_GetRGBStroke
HPDF_Page_GetRGBStroke.restype=HPDF_RGBColor


#HPDF_CMYKColor HPDF_Page_GetCMYKFill (HPDF_Page page)
HPDF_Page_GetCMYKFill=haru.HPDF_Page_GetCMYKFill
HPDF_Page_GetCMYKFill.restype=HPDF_CMYKColor


#HPDF_CMYKColor HPDF_Page_GetCMYKStroke (HPDF_Page page)
HPDF_Page_GetCMYKStroke=haru.HPDF_Page_GetCMYKStroke
HPDF_Page_GetCMYKStroke.restype=HPDF_CMYKColor


#HPDF_REAL HPDF_Page_GetGrayFill (HPDF_Page page)
HPDF_Page_GetGrayFill=haru.HPDF_Page_GetGrayFill
HPDF_Page_GetGrayFill.restype=HPDF_REAL


#HPDF_REAL HPDF_Page_GetGrayStroke (HPDF_Page page)
HPDF_Page_GetGrayStroke=haru.HPDF_Page_GetGrayStroke
HPDF_Page_GetGrayStroke.restype=HPDF_REAL


#HPDF_ColorSpace HPDF_Page_GetStrokingColorSpace (HPDF_Page page)
HPDF_Page_GetStrokingColorSpace=haru.HPDF_Page_GetStrokingColorSpace
HPDF_Page_GetStrokingColorSpace.restype=HPDF_ColorSpace


#HPDF_ColorSpace HPDF_Page_GetFillingColorSpace (HPDF_Page page)
HPDF_Page_GetFillingColorSpace=haru.HPDF_Page_GetFillingColorSpace
HPDF_Page_GetFillingColorSpace.restype=HPDF_ColorSpace


#HPDF_TransMatrix HPDF_Page_GetTextMatrix (HPDF_Page page)
HPDF_Page_GetTextMatrix=haru.HPDF_Page_GetTextMatrix
HPDF_Page_GetTextMatrix.restype=HPDF_TransMatrix


#HPDF_UINT HPDF_Page_GetGStateDepth (HPDF_Page page)
HPDF_Page_GetGStateDepth=haru.HPDF_Page_GetGStateDepth
HPDF_Page_GetGStateDepth.restype=HPDF_UINT


#--------------------------------------------------------------------------
#----- GRAPHICS OPERATORS -------------------------------------------------


#--- General graphics state ---------------------------------------------
# w
#HPDF_STATUS HPDF_Page_SetLineWidth (HPDF_Page page, HPDF_REAL line_width)
_HPDF_Page_SetLineWidth=haru.HPDF_Page_SetLineWidth
_HPDF_Page_SetLineWidth.restype=HPDF_STATUS
def HPDF_Page_SetLineWidth(
                           page,    #HPDF_Page
                           line_width,    #HPDF_REAL
                          ):
    line_width=HPDF_REAL(line_width)
    return _HPDF_Page_SetLineWidth(
                                   page,    #HPDF_Page
                                   line_width,    #HPDF_REAL
                                  )


# J
#HPDF_STATUS HPDF_Page_SetLineCap (HPDF_Page page, HPDF_LineCap line_cap)
HPDF_Page_SetLineCap=haru.HPDF_Page_SetLineCap
HPDF_Page_SetLineCap.restype=HPDF_STATUS


# j
#HPDF_STATUS HPDF_Page_SetLineJoin (HPDF_Page page, HPDF_LineJoin line_join)
HPDF_Page_SetLineJoin=haru.HPDF_Page_SetLineJoin
HPDF_Page_SetLineJoin.restype=HPDF_STATUS


# M

#HPDF_STATUS HPDF_Page_SetMiterLimit (HPDF_Page page, HPDF_REAL miter_limit)
_HPDF_Page_SetMiterLimit=haru.HPDF_Page_SetMiterLimit
_HPDF_Page_SetMiterLimit.restype=HPDF_STATUS
def HPDF_Page_SetMiterLimit(
                            page,    #HPDF_Page
                            miter_limit,    #HPDF_REAL
                           ):
    miter_limit=HPDF_REAL(miter_limit)
    return _HPDF_Page_SetMiterLimit(
                                    page,    #HPDF_Page
                                    miter_limit,    #HPDF_REAL
                                   )


# d
#HPDF_STATUS HPDF_Page_SetDash (HPDF_Page page, const HPDF_UINT16 *dash_ptn, HPDF_UINT num_param, HPDF_UINT phase)
_HPDF_Page_SetDash=haru.HPDF_Page_SetDash
_HPDF_Page_SetDash.restype=HPDF_STATUS
def HPDF_Page_SetDash(
                      page,    #HPDF_Page
                      dash_ptn,    #POINTER(HPDF_UINT16)
                      num_param,    #HPDF_UINT
                      phase,    #HPDF_UINT
                     ):
    if type(dash_ptn) in (types.ListType, types.TupleType):
        num_param=len(dash_ptn)
        dash_ptn=pointer((HPDF_UINT16*num_param)(*dash_ptn))
    return _HPDF_Page_SetDash(
                              page,    #HPDF_Page
                              dash_ptn,    #POINTER(HPDF_UINT16)
                              num_param,    #HPDF_UINT
                              phase,    #HPDF_UINT
                             )


# ri --not implemented yet

# i

#HPDF_STATUS HPDF_Page_SetFlat (HPDF_Page page, HPDF_REAL flatness)
_HPDF_Page_SetFlat=haru.HPDF_Page_SetFlat
_HPDF_Page_SetFlat.restype=HPDF_STATUS
def HPDF_Page_SetFlat(
                      page,    #HPDF_Page
                      flatness,    #HPDF_REAL
                     ):
    flatness=HPDF_REAL(flatness)
    return _HPDF_Page_SetFlat(
                              page,    #HPDF_Page
                              flatness,    #HPDF_REAL
                             )


# gs

#HPDF_STATUS HPDF_Page_SetExtGState (HPDF_Page page, HPDF_ExtGState ext_gstate)
HPDF_Page_SetExtGState=haru.HPDF_Page_SetExtGState
HPDF_Page_SetExtGState.restype=HPDF_STATUS


#--- Special graphic state operator --------------------------------------
# q
#HPDF_STATUS HPDF_Page_GSave (HPDF_Page page)
HPDF_Page_GSave=haru.HPDF_Page_GSave
HPDF_Page_GSave.restype=HPDF_STATUS


# Q
#HPDF_STATUS HPDF_Page_GRestore (HPDF_Page page)
HPDF_Page_GRestore=haru.HPDF_Page_GRestore
HPDF_Page_GRestore.restype=HPDF_STATUS


# cm

#HPDF_STATUS HPDF_Page_Concat (HPDF_Page page, HPDF_REAL a, HPDF_REAL b, HPDF_REAL c, HPDF_REAL d, HPDF_REAL x, HPDF_REAL y)
_HPDF_Page_Concat=haru.HPDF_Page_Concat
_HPDF_Page_Concat.restype=HPDF_STATUS
def HPDF_Page_Concat(
                     page,    #HPDF_Page
                     a,    #HPDF_REAL
                     b,    #HPDF_REAL
                     c,    #HPDF_REAL
                     d,    #HPDF_REAL
                     x,    #HPDF_REAL
                     y,    #HPDF_REAL
                    ):
    a=HPDF_REAL(a)
    b=HPDF_REAL(b)
    c=HPDF_REAL(c)
    d=HPDF_REAL(d)
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    return _HPDF_Page_Concat(
                             page,    #HPDF_Page
                             a,    #HPDF_REAL
                             b,    #HPDF_REAL
                             c,    #HPDF_REAL
                             d,    #HPDF_REAL
                             x,    #HPDF_REAL
                             y,    #HPDF_REAL
                            )


#--- Path construction operator ------------------------------------------
# m
#HPDF_STATUS HPDF_Page_MoveTo (HPDF_Page page, HPDF_REAL x, HPDF_REAL y)
_HPDF_Page_MoveTo=haru.HPDF_Page_MoveTo
_HPDF_Page_MoveTo.restype=HPDF_STATUS
def HPDF_Page_MoveTo(
                     page,    #HPDF_Page
                     x,    #HPDF_REAL
                     y,    #HPDF_REAL
                    ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    return _HPDF_Page_MoveTo(
                             page,    #HPDF_Page
                             x,    #HPDF_REAL
                             y,    #HPDF_REAL
                            )


# l
#HPDF_STATUS HPDF_Page_LineTo (HPDF_Page page, HPDF_REAL x, HPDF_REAL y)
_HPDF_Page_LineTo=haru.HPDF_Page_LineTo
_HPDF_Page_LineTo.restype=HPDF_STATUS
def HPDF_Page_LineTo(
                     page,    #HPDF_Page
                     x,    #HPDF_REAL
                     y,    #HPDF_REAL
                    ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    return _HPDF_Page_LineTo(
                             page,    #HPDF_Page
                             x,    #HPDF_REAL
                             y,    #HPDF_REAL
                            )


# c

#HPDF_STATUS HPDF_Page_CurveTo (HPDF_Page page, HPDF_REAL x1, HPDF_REAL y1, HPDF_REAL x2, HPDF_REAL y2, HPDF_REAL x3, HPDF_REAL y3)
_HPDF_Page_CurveTo=haru.HPDF_Page_CurveTo
_HPDF_Page_CurveTo.restype=HPDF_STATUS
def HPDF_Page_CurveTo(
                      page,    #HPDF_Page
                      x1,    #HPDF_REAL
                      y1,    #HPDF_REAL
                      x2,    #HPDF_REAL
                      y2,    #HPDF_REAL
                      x3,    #HPDF_REAL
                      y3,    #HPDF_REAL
                     ):
    x1=HPDF_REAL(x1)
    y1=HPDF_REAL(y1)
    x2=HPDF_REAL(x2)
    y2=HPDF_REAL(y2)
    x3=HPDF_REAL(x3)
    y3=HPDF_REAL(y3)
    return _HPDF_Page_CurveTo(
                              page,    #HPDF_Page
                              x1,    #HPDF_REAL
                              y1,    #HPDF_REAL
                              x2,    #HPDF_REAL
                              y2,    #HPDF_REAL
                              x3,    #HPDF_REAL
                              y3,    #HPDF_REAL
                             )


# v
#HPDF_STATUS HPDF_Page_CurveTo2 (HPDF_Page page, HPDF_REAL x2, HPDF_REAL y2, HPDF_REAL x3, HPDF_REAL y3)
_HPDF_Page_CurveTo2=haru.HPDF_Page_CurveTo2
_HPDF_Page_CurveTo2.restype=HPDF_STATUS
def HPDF_Page_CurveTo2(
                       page,    #HPDF_Page
                       x2,    #HPDF_REAL
                       y2,    #HPDF_REAL
                       x3,    #HPDF_REAL
                       y3,    #HPDF_REAL
                      ):
    x2=HPDF_REAL(x2)
    y2=HPDF_REAL(y2)
    x3=HPDF_REAL(x3)
    y3=HPDF_REAL(y3)
    return _HPDF_Page_CurveTo2(
                               page,    #HPDF_Page
                               x2,    #HPDF_REAL
                               y2,    #HPDF_REAL
                               x3,    #HPDF_REAL
                               y3,    #HPDF_REAL
                              )


# y
#HPDF_STATUS HPDF_Page_CurveTo3 (HPDF_Page page, HPDF_REAL x1, HPDF_REAL y1, HPDF_REAL x3, HPDF_REAL y3)
_HPDF_Page_CurveTo3=haru.HPDF_Page_CurveTo3
_HPDF_Page_CurveTo3.restype=HPDF_STATUS
def HPDF_Page_CurveTo3(
                       page,    #HPDF_Page
                       x1,    #HPDF_REAL
                       y1,    #HPDF_REAL
                       x3,    #HPDF_REAL
                       y3,    #HPDF_REAL
                      ):
    x1=HPDF_REAL(x1)
    y1=HPDF_REAL(y1)
    x3=HPDF_REAL(x3)
    y3=HPDF_REAL(y3)
    return _HPDF_Page_CurveTo3(
                               page,    #HPDF_Page
                               x1,    #HPDF_REAL
                               y1,    #HPDF_REAL
                               x3,    #HPDF_REAL
                               y3,    #HPDF_REAL
                              )


# h
#HPDF_STATUS HPDF_Page_ClosePath (HPDF_Page page)
HPDF_Page_ClosePath=haru.HPDF_Page_ClosePath
HPDF_Page_ClosePath.restype=HPDF_STATUS

# re
#HPDF_STATUS HPDF_Page_Rectangle (HPDF_Page page, HPDF_REAL x, HPDF_REAL y, HPDF_REAL width, HPDF_REAL height)
_HPDF_Page_Rectangle=haru.HPDF_Page_Rectangle
_HPDF_Page_Rectangle.restype=HPDF_STATUS
def HPDF_Page_Rectangle(
                        page,    #HPDF_Page
                        x,    #HPDF_REAL
                        y,    #HPDF_REAL
                        width,    #HPDF_REAL
                        height,    #HPDF_REAL
                       ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    width=HPDF_REAL(width)
    height=HPDF_REAL(height)
    return _HPDF_Page_Rectangle(
                                page,    #HPDF_Page
                                x,    #HPDF_REAL
                                y,    #HPDF_REAL
                                width,    #HPDF_REAL
                                height,    #HPDF_REAL
                               )


#--- Path painting operator ---------------------------------------------
# S
#HPDF_STATUS HPDF_Page_Stroke (HPDF_Page page)
_HPDF_Page_Stroke=haru.HPDF_Page_Stroke
_HPDF_Page_Stroke.restype=HPDF_STATUS
def HPDF_Page_Stroke(
                     page,    #HPDF_Page
                    ):
    return _HPDF_Page_Stroke(
                             page,    #HPDF_Page
                            )


# s

#HPDF_STATUS HPDF_Page_ClosePathStroke (HPDF_Page page)
HPDF_Page_ClosePathStroke=haru.HPDF_Page_ClosePathStroke
HPDF_Page_ClosePathStroke.restype=HPDF_STATUS


# f
#HPDF_STATUS HPDF_Page_Fill (HPDF_Page page)
HPDF_Page_Fill=haru.HPDF_Page_Fill
HPDF_Page_Fill.restype=HPDF_STATUS


# f*
#HPDF_STATUS HPDF_Page_Eofill (HPDF_Page page)
HPDF_Page_Eofill=haru.HPDF_Page_Eofill
HPDF_Page_Eofill.restype=HPDF_STATUS


# B
#HPDF_STATUS HPDF_Page_FillStroke (HPDF_Page page)
HPDF_Page_FillStroke=haru.HPDF_Page_FillStroke
HPDF_Page_FillStroke.restype=HPDF_STATUS


# B*

#HPDF_STATUS HPDF_Page_EofillStroke (HPDF_Page page)
HPDF_Page_EofillStroke=haru.HPDF_Page_EofillStroke
HPDF_Page_EofillStroke.restype=HPDF_STATUS


# b

#HPDF_STATUS HPDF_Page_ClosePathFillStroke (HPDF_Page page)
HPDF_Page_ClosePathFillStroke=haru.HPDF_Page_ClosePathFillStroke
HPDF_Page_ClosePathFillStroke.restype=HPDF_STATUS


# b*

#HPDF_STATUS HPDF_Page_ClosePathEofillStroke (HPDF_Page page)
HPDF_Page_ClosePathEofillStroke=haru.HPDF_Page_ClosePathEofillStroke
HPDF_Page_ClosePathEofillStroke.restype=HPDF_STATUS


# n

#HPDF_STATUS HPDF_Page_EndPath (HPDF_Page page)
HPDF_Page_EndPath=haru.HPDF_Page_EndPath
HPDF_Page_EndPath.restype=HPDF_STATUS


#--- Clipping paths operator --------------------------------------------
# W
#HPDF_STATUS HPDF_Page_Clip (HPDF_Page page)
HPDF_Page_Clip=haru.HPDF_Page_Clip
HPDF_Page_Clip.restype=HPDF_STATUS


# W*
#HPDF_STATUS HPDF_Page_Eoclip (HPDF_Page page)
HPDF_Page_Eoclip=haru.HPDF_Page_Eoclip
HPDF_Page_Eoclip.restype=HPDF_STATUS


#--- Text object operator -----------------------------------------------
# BT
#HPDF_STATUS HPDF_Page_BeginText (HPDF_Page page)
HPDF_Page_BeginText=haru.HPDF_Page_BeginText
HPDF_Page_BeginText.restype=HPDF_STATUS


# ET
#HPDF_STATUS HPDF_Page_EndText (HPDF_Page page)
HPDF_Page_EndText=haru.HPDF_Page_EndText
HPDF_Page_EndText.restype=HPDF_STATUS


#--- Text state ---------------------------------------------------------
# Tc

#HPDF_STATUS HPDF_Page_SetCharSpace (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetCharSpace=haru.HPDF_Page_SetCharSpace
_HPDF_Page_SetCharSpace.restype=HPDF_STATUS
def HPDF_Page_SetCharSpace(
                           page,    #HPDF_Page
                           value,    #HPDF_REAL
                          ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetCharSpace(
                                   page,    #HPDF_Page
                                   value,    #HPDF_REAL
                                  )


# Tw

#HPDF_STATUS HPDF_Page_SetWordSpace (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetWordSpace=haru.HPDF_Page_SetWordSpace
_HPDF_Page_SetWordSpace.restype=HPDF_STATUS
def HPDF_Page_SetWordSpace(
                           page,    #HPDF_Page
                           value,    #HPDF_REAL
                          ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetWordSpace(
                                   page,    #HPDF_Page
                                   value,    #HPDF_REAL
                                  )


# Tz

#HPDF_STATUS HPDF_Page_SetHorizontalScalling (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetHorizontalScalling=haru.HPDF_Page_SetHorizontalScalling
_HPDF_Page_SetHorizontalScalling.restype=HPDF_STATUS
def HPDF_Page_SetHorizontalScalling(
                                    page,    #HPDF_Page
                                    value,    #HPDF_REAL
                                   ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetHorizontalScalling(
                                            page,    #HPDF_Page
                                            value,    #HPDF_REAL
                                           )


# TL
#HPDF_STATUS HPDF_Page_SetTextLeading (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetTextLeading=haru.HPDF_Page_SetTextLeading
_HPDF_Page_SetTextLeading.restype=HPDF_STATUS
def HPDF_Page_SetTextLeading(
                             page,    #HPDF_Page
                             value,    #HPDF_REAL
                            ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetTextLeading(
                                     page,    #HPDF_Page
                                     value,    #HPDF_REAL
                                    )


# Tf
#HPDF_STATUS HPDF_Page_SetFontAndSize (HPDF_Page page, HPDF_Font font, HPDF_REAL size)
_HPDF_Page_SetFontAndSize=haru.HPDF_Page_SetFontAndSize
_HPDF_Page_SetFontAndSize.restype=HPDF_STATUS
def HPDF_Page_SetFontAndSize(
                             page,    #HPDF_Page
                             font,    #HPDF_Font
                             size,    #HPDF_REAL
                            ):
    size=HPDF_REAL(size)
    return _HPDF_Page_SetFontAndSize(
                                     page,    #HPDF_Page
                                     font,    #HPDF_Font
                                     size,    #HPDF_REAL
                                    )


# Tr

#HPDF_STATUS HPDF_Page_SetTextRenderingMode (HPDF_Page page, HPDF_TextRenderingMode mode)
HPDF_Page_SetTextRenderingMode=haru.HPDF_Page_SetTextRenderingMode
HPDF_Page_SetTextRenderingMode.restype=HPDF_STATUS


# Ts

#HPDF_STATUS HPDF_Page_SetTextRise (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetTextRise=haru.HPDF_Page_SetTextRise
_HPDF_Page_SetTextRise.restype=HPDF_STATUS
def HPDF_Page_SetTextRise(
                          page,    #HPDF_Page
                          value,    #HPDF_REAL
                         ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetTextRise(
                                  page,    #HPDF_Page
                                  value,    #HPDF_REAL
                                 )


# This function is obsolete. Use HPDF_Page_SetTextRise.

#HPDF_STATUS HPDF_Page_SetTextRaise (HPDF_Page page, HPDF_REAL value)
_HPDF_Page_SetTextRaise=haru.HPDF_Page_SetTextRaise
_HPDF_Page_SetTextRaise.restype=HPDF_STATUS
def HPDF_Page_SetTextRaise(
                           page,    #HPDF_Page
                           value,    #HPDF_REAL
                          ):
    value=HPDF_REAL(value)
    return _HPDF_Page_SetTextRaise(
                                   page,    #HPDF_Page
                                   value,    #HPDF_REAL
                                  )


#--- Text positioning ---------------------------------------------------
# Td
#HPDF_STATUS HPDF_Page_MoveTextPos (HPDF_Page page, HPDF_REAL x, HPDF_REAL y)
_HPDF_Page_MoveTextPos=haru.HPDF_Page_MoveTextPos
_HPDF_Page_MoveTextPos.restype=HPDF_STATUS
def HPDF_Page_MoveTextPos(
                          page,    #HPDF_Page
                          x,    #HPDF_REAL
                          y,    #HPDF_REAL
                         ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    return _HPDF_Page_MoveTextPos(
                                  page,    #HPDF_Page
                                  x,    #HPDF_REAL
                                  y,    #HPDF_REAL
                                 )


# TD

#HPDF_STATUS HPDF_Page_MoveTextPos2 (HPDF_Page page, HPDF_REAL x, HPDF_REAL y)
_HPDF_Page_MoveTextPos2=haru.HPDF_Page_MoveTextPos2
_HPDF_Page_MoveTextPos2.restype=HPDF_STATUS
def HPDF_Page_MoveTextPos2(
                           page,    #HPDF_Page
                           x,    #HPDF_REAL
                           y,    #HPDF_REAL
                          ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    return _HPDF_Page_MoveTextPos2(
                                   page,    #HPDF_Page
                                   x,    #HPDF_REAL
                                   y,    #HPDF_REAL
                                  )


# Tm

#HPDF_STATUS HPDF_Page_SetTextMatrix (HPDF_Page page, HPDF_REAL a, HPDF_REAL b, HPDF_REAL c, HPDF_REAL d, HPDF_REAL x, HPDF_REAL y)
_HPDF_Page_SetTextMatrix=haru.HPDF_Page_SetTextMatrix
_HPDF_Page_SetTextMatrix.restype=HPDF_STATUS
def HPDF_Page_SetTextMatrix(
                            page,    #HPDF_Page
                            a,    #HPDF_REAL
                            b,    #HPDF_REAL
                            c,    #HPDF_REAL
                            d,    #HPDF_REAL
                            x,    #HPDF_REAL
                            y,    #HPDF_REAL
                           ):
    a=HPDF_REAL(a)
    b=HPDF_REAL(b)
    c=HPDF_REAL(c)
    d=HPDF_REAL(d)
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    return _HPDF_Page_SetTextMatrix(
                                    page,    #HPDF_Page
                                    a,    #HPDF_REAL
                                    b,    #HPDF_REAL
                                    c,    #HPDF_REAL
                                    d,    #HPDF_REAL
                                    x,    #HPDF_REAL
                                    y,    #HPDF_REAL
                                   )


# T*

#HPDF_STATUS HPDF_Page_MoveToNextLine (HPDF_Page page)
HPDF_Page_MoveToNextLine=haru.HPDF_Page_MoveToNextLine
HPDF_Page_MoveToNextLine.restype=HPDF_STATUS

#--- Text showing -------------------------------------------------------


# Tj
#HPDF_STATUS HPDF_Page_ShowText (HPDF_Page page, const char *text)
_HPDF_Page_ShowText=haru.HPDF_Page_ShowText
_HPDF_Page_ShowText.restype=HPDF_STATUS
def HPDF_Page_ShowText(page,
                       text
                      ):
    if type(text) in (types.ListType, types.TupleType):
        if type(text[-1]) != types.StringType:
            text=[chr(i) for i in text]
        text=''.join(text)
    return _HPDF_Page_ShowText(page,
                       text
                      )


# TJ

# '
#HPDF_STATUS HPDF_Page_ShowTextNextLine (HPDF_Page page, const char *text)
HPDF_Page_ShowTextNextLine=haru.HPDF_Page_ShowTextNextLine
HPDF_Page_ShowTextNextLine.restype=HPDF_STATUS


# "

#HPDF_STATUS HPDF_Page_ShowTextNextLineEx (HPDF_Page page, HPDF_REAL word_space, HPDF_REAL char_space, const char *text)
_HPDF_Page_ShowTextNextLineEx=haru.HPDF_Page_ShowTextNextLineEx
_HPDF_Page_ShowTextNextLineEx.restype=HPDF_STATUS
def HPDF_Page_ShowTextNextLineEx(
                                 page,    #HPDF_Page
                                 word_space,    #HPDF_REAL
                                 char_space,    #HPDF_REAL
                                 text,    #c_char_p
                                ):
    word_space=HPDF_REAL(word_space)
    char_space=HPDF_REAL(char_space)
    return _HPDF_Page_ShowTextNextLineEx(
                                         page,    #HPDF_Page
                                         word_space,    #HPDF_REAL
                                         char_space,    #HPDF_REAL
                                         text,    #c_char_p
                                        )


#--- Color showing ------------------------------------------------------
# cs --not implemented yet
# CS --not implemented yet
# sc --not implemented yet
# scn --not implemented yet
# SC --not implemented yet
# SCN --not implemented yet

# g
#HPDF_STATUS HPDF_Page_SetGrayFill (HPDF_Page page, HPDF_REAL gray)
_HPDF_Page_SetGrayFill=haru.HPDF_Page_SetGrayFill
_HPDF_Page_SetGrayFill.restype=HPDF_STATUS
def HPDF_Page_SetGrayFill(
                          page,    #HPDF_Page
                          gray,    #HPDF_REAL
                         ):
    gray=HPDF_REAL(gray)
    return _HPDF_Page_SetGrayFill(
                                  page,    #HPDF_Page
                                  gray,    #HPDF_REAL
                                 )


# G

#HPDF_STATUS HPDF_Page_SetGrayStroke (HPDF_Page page, HPDF_REAL gray)
_HPDF_Page_SetGrayStroke=haru.HPDF_Page_SetGrayStroke
_HPDF_Page_SetGrayStroke.restype=HPDF_STATUS
def HPDF_Page_SetGrayStroke(
                            page,    #HPDF_Page
                            gray,    #HPDF_REAL
                           ):
    gray=HPDF_REAL(gray)
    return _HPDF_Page_SetGrayStroke(
                                    page,    #HPDF_Page
                                    gray,    #HPDF_REAL
                                   )


# rg
#HPDF_STATUS HPDF_Page_SetRGBFill (HPDF_Page page, HPDF_REAL r, HPDF_REAL g, HPDF_REAL b)
_HPDF_Page_SetRGBFill=haru.HPDF_Page_SetRGBFill
_HPDF_Page_SetRGBFill.restype=HPDF_STATUS
def HPDF_Page_SetRGBFill(
                         page,    #HPDF_Page
                         r,    #HPDF_REAL
                         g,    #HPDF_REAL
                         b,    #HPDF_REAL
                        ):
    r=HPDF_REAL(r)
    g=HPDF_REAL(g)
    b=HPDF_REAL(b)
    return _HPDF_Page_SetRGBFill(
                                 page,    #HPDF_Page
                                 r,    #HPDF_REAL
                                 g,    #HPDF_REAL
                                 b,    #HPDF_REAL
                                )


# RG
#HPDF_STATUS HPDF_Page_SetRGBStroke (HPDF_Page page, HPDF_REAL r, HPDF_REAL g, HPDF_REAL b)
_HPDF_Page_SetRGBStroke=haru.HPDF_Page_SetRGBStroke
_HPDF_Page_SetRGBStroke.restype=HPDF_STATUS
def HPDF_Page_SetRGBStroke(
                           page,    #HPDF_Page
                           r,    #HPDF_REAL
                           g,    #HPDF_REAL
                           b,    #HPDF_REAL
                          ):
    r=HPDF_REAL(r)
    g=HPDF_REAL(g)
    b=HPDF_REAL(b)
    return _HPDF_Page_SetRGBStroke(
                                   page,    #HPDF_Page
                                   r,    #HPDF_REAL
                                   g,    #HPDF_REAL
                                   b,    #HPDF_REAL
                                  )


# k

#HPDF_STATUS HPDF_Page_SetCMYKFill (HPDF_Page page, HPDF_REAL c, HPDF_REAL m, HPDF_REAL y, HPDF_REAL k)
_HPDF_Page_SetCMYKFill=haru.HPDF_Page_SetCMYKFill
_HPDF_Page_SetCMYKFill.restype=HPDF_STATUS
def HPDF_Page_SetCMYKFill(
                          page,    #HPDF_Page
                          c,    #HPDF_REAL
                          m,    #HPDF_REAL
                          y,    #HPDF_REAL
                          k,    #HPDF_REAL
                         ):
    c=HPDF_REAL(c)
    m=HPDF_REAL(m)
    y=HPDF_REAL(y)
    k=HPDF_REAL(k)
    return _HPDF_Page_SetCMYKFill(
                                  page,    #HPDF_Page
                                  c,    #HPDF_REAL
                                  m,    #HPDF_REAL
                                  y,    #HPDF_REAL
                                  k,    #HPDF_REAL
                                 )


# K

#HPDF_STATUS HPDF_Page_SetCMYKStroke (HPDF_Page page, HPDF_REAL c, HPDF_REAL m, HPDF_REAL y, HPDF_REAL k)
_HPDF_Page_SetCMYKStroke=haru.HPDF_Page_SetCMYKStroke
_HPDF_Page_SetCMYKStroke.restype=HPDF_STATUS
def HPDF_Page_SetCMYKStroke(
                            page,    #HPDF_Page
                            c,    #HPDF_REAL
                            m,    #HPDF_REAL
                            y,    #HPDF_REAL
                            k,    #HPDF_REAL
                           ):
    c=HPDF_REAL(c)
    m=HPDF_REAL(m)
    y=HPDF_REAL(y)
    k=HPDF_REAL(k)
    return _HPDF_Page_SetCMYKStroke(
                                    page,    #HPDF_Page
                                    c,    #HPDF_REAL
                                    m,    #HPDF_REAL
                                    y,    #HPDF_REAL
                                    k,    #HPDF_REAL
                                   )


#--- Shading patterns ---------------------------------------------------
# sh --not implemented yet

#--- In-line images -----------------------------------------------------
# BI --not implemented yet
# ID --not implemented yet
# EI --not implemented yet

#--- XObjects -----------------------------------------------------------
# Do

#HPDF_STATUS HPDF_Page_ExecuteXObject (HPDF_Page page, HPDF_XObject obj)
HPDF_Page_ExecuteXObject=haru.HPDF_Page_ExecuteXObject
HPDF_Page_ExecuteXObject.restype=HPDF_STATUS


#--- Marked content -----------------------------------------------------
# BMC --not implemented yet
# BDC --not implemented yet
# EMC --not implemented yet
# MP --not implemented yet
# DP --not implemented yet

#--- Compatibility ------------------------------------------------------
# BX --not implemented yet
# EX --not implemented yet

#HPDF_STATUS HPDF_Page_DrawImage (HPDF_Page page, HPDF_Image image, HPDF_REAL x, HPDF_REAL y, HPDF_REAL width, HPDF_REAL height)
_HPDF_Page_DrawImage=haru.HPDF_Page_DrawImage
_HPDF_Page_DrawImage.restype=HPDF_STATUS
def HPDF_Page_DrawImage(
                        page,    #HPDF_Page
                        image,    #HPDF_Image
                        x,    #HPDF_REAL
                        y,    #HPDF_REAL
                        width,    #HPDF_REAL
                        height,    #HPDF_REAL
                       ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    width=HPDF_REAL(width)
    height=HPDF_REAL(height)
    return _HPDF_Page_DrawImage(
                                page,    #HPDF_Page
                                image,    #HPDF_Image
                                x,    #HPDF_REAL
                                y,    #HPDF_REAL
                                width,    #HPDF_REAL
                                height,    #HPDF_REAL
                               )


#HPDF_STATUS HPDF_Page_Circle (HPDF_Page page, HPDF_REAL x, HPDF_REAL y, HPDF_REAL ray)
_HPDF_Page_Circle=haru.HPDF_Page_Circle
_HPDF_Page_Circle.restype=HPDF_STATUS
def HPDF_Page_Circle(
                     page,    #HPDF_Page
                     x,    #HPDF_REAL
                     y,    #HPDF_REAL
                     ray,    #HPDF_REAL
                    ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    ray=HPDF_REAL(ray)
    return _HPDF_Page_Circle(
                             page,    #HPDF_Page
                             x,    #HPDF_REAL
                             y,    #HPDF_REAL
                             ray,    #HPDF_REAL
                            )


#HPDF_STATUS HPDF_Page_Ellipse (HPDF_Page page, HPDF_REAL x, HPDF_REAL y, HPDF_REAL xray, HPDF_REAL yray)
_HPDF_Page_Ellipse=haru.HPDF_Page_Ellipse
_HPDF_Page_Ellipse.restype=HPDF_STATUS
def HPDF_Page_Ellipse(
                      page,    #HPDF_Page
                      x,    #HPDF_REAL
                      y,    #HPDF_REAL
                      xray,    #HPDF_REAL
                      yray,    #HPDF_REAL
                     ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    xray=HPDF_REAL(xray)
    yray=HPDF_REAL(yray)
    return _HPDF_Page_Ellipse(
                              page,    #HPDF_Page
                              x,    #HPDF_REAL
                              y,    #HPDF_REAL
                              xray,    #HPDF_REAL
                              yray,    #HPDF_REAL
                             )


#HPDF_STATUS HPDF_Page_Arc (HPDF_Page page, HPDF_REAL x, HPDF_REAL y, HPDF_REAL ray, HPDF_REAL ang1, HPDF_REAL ang2)
_HPDF_Page_Arc=haru.HPDF_Page_Arc
_HPDF_Page_Arc.restype=HPDF_STATUS
def HPDF_Page_Arc(
                  page,    #HPDF_Page
                  x,    #HPDF_REAL
                  y,    #HPDF_REAL
                  ray,    #HPDF_REAL
                  ang1,    #HPDF_REAL
                  ang2,    #HPDF_REAL
                 ):
    x=HPDF_REAL(x)
    y=HPDF_REAL(y)
    ray=HPDF_REAL(ray)
    ang1=HPDF_REAL(ang1)
    ang2=HPDF_REAL(ang2)
    return _HPDF_Page_Arc(
                          page,    #HPDF_Page
                          x,    #HPDF_REAL
                          y,    #HPDF_REAL
                          ray,    #HPDF_REAL
                          ang1,    #HPDF_REAL
                          ang2,    #HPDF_REAL
                         )


#HPDF_STATUS HPDF_Page_TextOut (HPDF_Page page, HPDF_REAL xpos, HPDF_REAL ypos, const char *text)
_HPDF_Page_TextOut=haru.HPDF_Page_TextOut
_HPDF_Page_TextOut.restype=HPDF_STATUS
def HPDF_Page_TextOut(
                      page,    #HPDF_Page
                      xpos,    #HPDF_REAL
                      ypos,    #HPDF_REAL
                      text,    #c_char_p
                     ):
    xpos=HPDF_REAL(xpos)
    ypos=HPDF_REAL(ypos)
    if type(text) in (types.ListType, types.TupleType):
        if type(text[-1]) != types.StringType:
            text=[chr(i) for i in text]
        text=''.join(text)

    return _HPDF_Page_TextOut(
                              page,    #HPDF_Page
                              xpos,    #HPDF_REAL
                              ypos,    #HPDF_REAL
                              text,    #c_char_p
                             )


#HPDF_STATUS HPDF_Page_TextRect (HPDF_Page page, HPDF_REAL left, HPDF_REAL top, HPDF_REAL right, HPDF_REAL bottom, const char *text, HPDF_TextAlignment align, HPDF_UINT *len)
#???
_HPDF_Page_TextRect=haru.HPDF_Page_TextRect
_HPDF_Page_TextRect.restype=HPDF_STATUS
def HPDF_Page_TextRect(
                       page,    #HPDF_Page
                       left,    #HPDF_REAL
                       top,    #HPDF_REAL
                       right,    #HPDF_REAL
                       bottom,    #HPDF_REAL
                       text,    #c_char_p
                       align,    #HPDF_TextAlignment
                       length,    #POINTER(HPDF_UINT)
                      ):
    left=HPDF_REAL(left)
    top=HPDF_REAL(top)
    right=HPDF_REAL(right)
    bottom=HPDF_REAL(bottom)

    if type(length) in (types.ListType, types.TupleType):
        size=len(length)
        length=pointer((HPDF_UINT*size)(*length))

    return _HPDF_Page_TextRect(
                               page,    #HPDF_Page
                               left,    #HPDF_REAL
                               top,    #HPDF_REAL
                               right,    #HPDF_REAL
                               bottom,    #HPDF_REAL
                               text,    #c_char_p
                               align,    #HPDF_TextAlignment
                               length,    #POINTER(HPDF_UINT)
                              )


#HPDF_STATUS HPDF_Page_SetSlideShow (HPDF_Page page, HPDF_TransitionStyle type, HPDF_REAL disp_time, HPDF_REAL trans_time)
_HPDF_Page_SetSlideShow=haru.HPDF_Page_SetSlideShow
_HPDF_Page_SetSlideShow.restype=HPDF_STATUS
def HPDF_Page_SetSlideShow(
                           page,    #HPDF_Page
                           tType,    #HPDF_TransitionStyle
                           disp_time,    #HPDF_REAL
                           trans_time,    #HPDF_REAL
                          ):
    disp_time=HPDF_REAL(disp_time)
    trans_time=HPDF_REAL(trans_time)
    return _HPDF_Page_SetSlideShow(
                                   page,    #HPDF_Page
                                   tType,    #HPDF_TransitionStyle
                                   disp_time,    #HPDF_REAL
                                   trans_time,    #HPDF_REAL
                                  )


NULL=0

HPDF_NOPNGLIB=False
