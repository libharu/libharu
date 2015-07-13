{*
 * << Haru Free PDF Library 2.3.0 >> -- hpdf.pas
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2015 David Pethes
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 *}
unit hpdf;
{$define USE_STATIC} //remove to only load libHaru on demand by calling LoadHaru()
{$IFDEF FPC}
  {$MACRO ON}
  {$ifdef USE_STATIC}
    {$mode objfpc}
    {$IFDEF Windows}
      {$DEFINE extdecl := stdcall external}
    {$ELSE}
      {$DEFINE extdecl := cdecl external}
    {$ENDIF}
  {$else}
    {$MODE Delphi} //needs Delphi mode for untyped pointer to func variable assignment when using dynamic linking
    {$IFDEF Windows}
      {$DEFINE extdecl := stdcall}
    {$ELSE}
      {$DEFINE extdecl := cdecl}
    {$ENDIF}
  {$endif}
  {$H+}
{$ENDIF}
{$IFDEF Delphi}
  {$DEFINE extdecl := stdcall}
{$ENDIF}

interface

uses
  {$IFDEF FPC} dynlibs, {$ENDIF}
  SysUtils, hpdf_types;

const
  {$IFDEF FPC} LIBHPDF_LIB = 'libhpdf.' + SharedSuffix; {$ENDIF}
  {$IFDEF Delphi} LIBHPDF_LIB = 'libhpdf.dll'; {$ENDIF}

type
  HPDF_HANDLE = Pointer;
  HPDF_Doc = HPDF_HANDLE;
  HPDF_Page = HPDF_HANDLE;
  HPDF_Pages = HPDF_HANDLE;
  HPDF_Stream = HPDF_HANDLE;
  HPDF_Image = HPDF_HANDLE;
  HPDF_Font = HPDF_HANDLE;
  HPDF_Outline = HPDF_HANDLE;
  HPDF_Encoder = HPDF_HANDLE;
  HPDF_Destination = HPDF_HANDLE;
  HPDF_XObject = HPDF_HANDLE;
  HPDF_Annotation = HPDF_HANDLE;
  HPDF_ExtGState = HPDF_HANDLE;
  HPDF_CHAR = PChar;
  HPDF_STATUS = Cardinal;

{$ifdef USE_STATIC}
{%Region}
function HPDF_GetVersion: pchar; extdecl LIBHPDF_LIB;

function HPDF_NewEx (user_error_fn: THPDF_ErrorFunc;
        user_alloc_fn: THPDF_AllocFunc; user_free_fn: THPDF_FreeFunc;
        mem_pool_buf_size: HPDF_UINT; user_data: Pointer): HPDF_Doc;
         extdecl LIBHPDF_LIB;

function HPDF_New (user_error_fn: THPDF_ErrorFunc; user_data: Pointer): HPDF_Doc;
         extdecl LIBHPDF_LIB;

function HPDF_SetErrorHandler (pdf: HPDF_Doc; user_error_fn: THPDF_ErrorFunc):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

procedure HPDF_Free (pdf: HPDF_Doc); extdecl LIBHPDF_LIB;

function HPDF_NewDoc (pdf: HPDF_Doc): HPDF_STATUS; extdecl LIBHPDF_LIB;

procedure HPDF_FreeDoc (pdf: HPDF_Doc); extdecl LIBHPDF_LIB;

function HPDF_HasDoc (pdf: HPDF_Doc): HPDF_BOOL; extdecl LIBHPDF_LIB;

procedure HPDF_FreeDocAll (pdf: HPDF_Doc); extdecl LIBHPDF_LIB;

function HPDF_SaveToStream (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_GetStreamSize (pdf: HPDF_Doc): HPDF_UINT32;
         extdecl LIBHPDF_LIB;

function HPDF_ReadFromStream (pdf: HPDF_Doc; buf: HPDF_PBYTE; 
         size: HPDF_PUINT): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_ResetStream (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_SaveToFile (pdf: HPDF_Doc; const file_name: HPDF_PCHAR): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_GetError (pdf: HPDF_Doc): HPDF_STATUS; extdecl LIBHPDF_LIB;

procedure HPDF_ResetError (pdf: HPDF_Doc); extdecl LIBHPDF_LIB;

function HPDF_SetPagesConfiguration (pdf: HPDF_Doc; page_per_pages: HPDF_UINT):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_GetPageByIndex (pdf: HPDF_Doc; index: HPDF_UINT): HPDF_Page;
         extdecl LIBHPDF_LIB;

function HPDF_GetPageLayout (pdf: HPDF_Doc): THPDF_PageLayout;
         extdecl LIBHPDF_LIB;

function HPDF_SetPageLayout (pdf: HPDF_Doc; layout: THPDF_PageLayout): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_GetPageMode (pdf: HPDF_Doc): THPDF_PageMode;
         extdecl LIBHPDF_LIB;

function HPDF_SetPageMode (pdf: HPDF_Doc; mode: THPDF_PageMode): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_SetOpenAction (pdf: HPDF_Doc; open_action: HPDF_Destination):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_GetViewerPreference (pdf: HPDF_Doc): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_SetViewerPreference (pdf: HPDF_Doc; value: HPDF_UINT): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_GetCurrentPage (pdf: HPDF_Doc): HPDF_Page;
         extdecl LIBHPDF_LIB;

function HPDF_AddPage (pdf: HPDF_Doc): HPDF_Page; extdecl LIBHPDF_LIB;

function HPDF_InsertPage (pdf: HPDF_Doc; page: HPDF_Page): HPDF_Page;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetWidth (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetHeight (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetSize (page: HPDF_Page; size: THPDF_PageSizes;
        direction: THPDF_PageDirection): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetRotate (page: HPDF_Page; angle: HPDF_UINT16): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetZoom (page: HPDF_Page; zoom: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_GetFont (pdf: HPDF_Doc; const font_name: HPDF_PCHAR;
        const encoding_name: HPDF_PCHAR): HPDF_Font; extdecl LIBHPDF_LIB;

function HPDF_LoadType1FontFromFile (pdf: HPDF_Doc; afmfilename: HPDF_PCHAR;
        pfmfilename: HPDF_PCHAR): HPDF_PCHAR; extdecl LIBHPDF_LIB;

function HPDF_LoadTTFontFromFile (pdf: HPDF_Doc; const file_name: HPDF_PCHAR;
        embedding: HPDF_BOOL): HPDF_PCHAR; extdecl LIBHPDF_LIB;

function HPDF_LoadTTFontFromFile2 (pdf: HPDF_Doc; const file_name: HPDF_PCHAR;
        index: HPDF_UINT; embedding: HPDF_BOOL): HPDF_CHAR;
         extdecl LIBHPDF_LIB;

function HPDF_AddPageLabel (pdf: HPDF_Doc; page_num: HPDF_UINT;
        style: THPDF_PageNumStyle; first_page: HPDF_UINT; const prefix: HPDF_PCHAR):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_UseJPFonts (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_UseKRFonts (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_UseCNSFonts (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_UseCNTFonts (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_CreateOutline (pdf: HPDF_Doc; parent: HPDF_Outline;
        const title: HPDF_PCHAR; encoder: HPDF_Encoder): HPDF_Outline;
         extdecl LIBHPDF_LIB;

function HPDF_Outline_SetOpened (outline: HPDF_Outline; opened: HPDF_BOOL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Outline_SetDestination (outline: HPDF_Outline;
        dst: HPDF_Destination): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_CreateDestination (page: HPDF_Page): HPDF_Destination;
         extdecl LIBHPDF_LIB;

function HPDF_Destination_SetXYZ (dst: HPDF_Destination; left: HPDF_REAL;
        top: HPDF_REAL; zoom: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Destination_SetFit (dst: HPDF_Destination): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Destination_SetFitH (dst: HPDF_Destination; top: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Destination_SetFitV (dst: HPDF_Destination; left: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Destination_SetFitR (dst: HPDF_Destination; left: HPDF_REAL;
        bottom: HPDF_REAL; right: HPDF_REAL; top: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Destination_SetFitB (dst: HPDF_Destination): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Destination_SetFitBH (dst: HPDF_Destination; top: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Destination_SetFitBV (dst: HPDF_Destination; left: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_GetEncoder (pdf: HPDF_Doc; const encoding_name: HPDF_PCHAR):
        HPDF_Encoder; extdecl LIBHPDF_LIB;

function HPDF_GetCurrentEncoder (pdf: HPDF_Doc): HPDF_Encoder;
         extdecl LIBHPDF_LIB;

function HPDF_SetCurrentEncoder (pdf: HPDF_Doc; const encoding_name: HPDF_PCHAR):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Encoder_GetType (encoder: HPDF_Encoder): THPDF_EncoderType;
         extdecl LIBHPDF_LIB;

function HPDF_Encoder_GetByteType (encoder: HPDF_Encoder; const text: HPDF_PCHAR;
        index: HPDF_UINT): THPDF_ByteType; extdecl LIBHPDF_LIB;

function HPDF_Encoder_GetUnicode (encoder: HPDF_Encoder; code: HPDF_UINT16):
        HPDF_UNICODE; extdecl LIBHPDF_LIB;

function HPDF_Encoder_GetWritingMode (encoder: HPDF_Encoder): THPDF_EncoderType;
         extdecl LIBHPDF_LIB;

function HPDF_UseJPEncodings (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_UseKREncodings (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_UseCNSEncodings (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_UseCNTEncodings (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_UseUTFEncodings (pdf: HPDF_Doc): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_CreateTextAnnot (page: HPDF_Page; rect: THPDF_Rect;
        const text: HPDF_PCHAR; encoder: HPDF_Encoder): HPDF_Annotation;
         extdecl LIBHPDF_LIB;

function HPDF_Page_CreateLinkAnnot (page: HPDF_Page; rect: THPDF_Rect;
        dst: HPDF_Destination): HPDF_Annotation; extdecl LIBHPDF_LIB;

function HPDF_Page_CreateURILinkAnnot (page: HPDF_Page; rect: THPDF_Rect;
        const uri: HPDF_PCHAR): HPDF_Annotation; extdecl LIBHPDF_LIB;

function HPDF_LinkAnnot_SetHighlightMode (annot: HPDF_Annotation;
        mode: THPDF_AnnotHighlightMode): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_LinkAnnot_SetBorderStyle (annot: HPDF_Annotation; width: HPDF_REAL;
        dash_on: HPDF_UINT16; dash_off: HPDF_UINT16): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_TextAnnot_SetIcon (annot: HPDF_Annotation; icon: THPDF_AnnotIcon):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_TextAnnot_SetOpened (annot: HPDF_Annotation; opened: HPDF_BOOL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_LoadPngImageFromMem (pdf: HPDF_Doc; const buffer: HPDF_PBYTE; size: HPDF_UINT):
        HPDF_Image; extdecl LIBHPDF_LIB;

function HPDF_LoadPngImageFromFile (pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; extdecl LIBHPDF_LIB;

function HPDF_LoadPngImageFromFile2 (pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; extdecl LIBHPDF_LIB;

function HPDF_LoadJpegImageFromFile (pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; extdecl LIBHPDF_LIB;

function HPDF_LoadRawImageFromFile (pdf: HPDF_Doc; filename: HPDF_PCHAR;
        width: HPDF_UINT; height: HPDF_UINT; color_space: THPDF_ColorSpace):
        HPDF_Image; extdecl LIBHPDF_LIB;

function HPDF_LoadRawImageFromMem (pdf: HPDF_Doc; const buf: HPDF_PBYTE;
        width: HPDF_UINT; height: HPDF_UINT; color_space: THPDF_ColorSpace;
        bits_per_component: HPDF_UINT): HPDF_Image; extdecl LIBHPDF_LIB;

function HPDF_Image_GetSize2 (image: HPDF_Image; size: PHPDF_Point): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Image_GetWidth (image: HPDF_Image): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_Image_GetHeight (image: HPDF_Image): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_Image_GetBitsPerComponent (image: HPDF_Image): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_Image_GetColorSpace (image: HPDF_Image): HPDF_PCHAR;
         extdecl LIBHPDF_LIB;

function HPDF_Image_SetColorMask (image: HPDF_Image; rmin: HPDF_UINT;
        rmax: HPDF_UINT; gmin: HPDF_UINT; gmax: HPDF_UINT; bmin: HPDF_UINT;
        bmax: HPDF_UINT): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Image_SetMaskImage (image: HPDF_Image; mask_image: HPDF_Image):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_SetInfoAttr (pdf: HPDF_Doc; info_type: THPDF_InfoType;
        const value: HPDF_PCHAR): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_GetInfoAttr (pdf: HPDF_Doc; info_type: THPDF_InfoType): HPDF_PCHAR;
         extdecl LIBHPDF_LIB;

function HPDF_SetInfoDateAttr (pdf: HPDF_Doc; info_type: THPDF_InfoType; value: THPDF_Date):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_SetPassword (pdf: HPDF_Doc; const owner_passwd: HPDF_PCHAR;
        const user_passwd: HPDF_PCHAR): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_SetPermission (pdf: HPDF_Doc; permission: HPDF_UINT): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_SetEncryptionMode (pdf: HPDF_Doc; mode: THPDF_EncryptMode;
        key_len: HPDF_UINT): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_SetCompressionMode (pdf: HPDF_Doc; mode: HPDF_UINT): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_TextWidth (page: HPDF_Page; const text: HPDF_PCHAR): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_MeasureText (page: HPDF_Page; const text: HPDF_PCHAR;
        width: HPDF_REAL; wordwrap: HPDF_BOOL; real_width: HPDF_PREAL): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetWidth (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetHeight (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetGMode (page: HPDF_Page): HPDF_UINT16;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetCurrentPos2 (page: HPDF_Page; pos: PHPDF_Point): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetCurrentTextPos2 (page: HPDF_Page; pos: PHPDF_Point): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetCurrentFont (page: HPDF_Page): HPDF_Font;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetFontName (font: HPDF_Font): HPDF_PCHAR;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetEncodingName (font: HPDF_Font): HPDF_PCHAR;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetUnicodeWidth (font: HPDF_Font; code: HPDF_UNICODE): HPDF_INT;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetBBox (font: HPDF_Font): THPDF_Rect;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetAscent (font: HPDF_Font): HPDF_INT;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetDescent (font: HPDF_Font): HPDF_INT;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetXHeight (font: HPDF_Font): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_Font_GetCapHeight (font: HPDF_Font): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_Font_TextWidth  (font: HPDF_Font; const text: PChar; len: HPDF_UINT): THPDF_TextWidth;
         extdecl LIBHPDF_LIB;

function HPDF_Font_MeasureText (font: HPDF_Font; const text: PChar; len: HPDF_UINT;
         width: HPDF_REAL; font_size: HPDF_REAL; char_space: HPDF_REAL; 
         word_space: HPDF_REAL; wordwrap: HPDF_BOOL; real_width: HPDF_PREAL) : HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_CreateExtGState  (pdf: HPDF_Doc) : HPDF_ExtGState;
         extdecl LIBHPDF_LIB;

function HPDF_ExtGState_SetAlphaStroke  (ext_gstate: HPDF_ExtGState; 
         value: HPDF_REAL) : HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_ExtGState_SetAlphaFill  (ext_gstate: HPDF_ExtGState; 
         value: HPDF_REAL) : HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_ExtGState_SetBlendMode  (ext_gstate: HPDF_ExtGState; 
         mode: THPDF_BlendMode) : HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_GetCurrentFontSize (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetTransMatrix (page: HPDF_Page): THPDF_TransMatrix;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetLineWidth (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetLineCap (page: HPDF_Page): THPDF_LineCap;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetLineJoin (page: HPDF_Page): THPDF_LineJoin;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetMiterLimit (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetDash (page: HPDF_Page): THPDF_DashMode;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetFlat (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetCharSpace (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetWordSpace (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetHorizontalScalling (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetTextLeading (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetTextRenderingMode (page: HPDF_Page): THPDF_TextRenderingMode;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetTextRaise (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetRGBFill (page: HPDF_Page): THPDF_RGBColor;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetRGBStroke (page: HPDF_Page): THPDF_RGBColor;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetCMYKFill (page: HPDF_Page): THPDF_CMYKColor;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetCMYKStroke (page: HPDF_Page): THPDF_CMYKColor;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetGrayFill (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetGrayStroke (page: HPDF_Page): HPDF_REAL;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetStrokingColorSpace (page: HPDF_Page): THPDF_ColorSpace;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetFillingColorSpace (page: HPDF_Page): THPDF_ColorSpace;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetTextMatrix (page: HPDF_Page): THPDF_TransMatrix;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GetGStateDepth (page: HPDF_Page): HPDF_UINT;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetLineWidth (page: HPDF_Page; line_width: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetLineCap (page: HPDF_Page; line_cap: THPDF_LineCap):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetLineJoin (page: HPDF_Page; line_join: THPDF_LineJoin):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetMiterLimit (page: HPDF_Page; miter_limit: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetDash (page: HPDF_Page; ptn: HPDF_PUINT16; num_param: HPDF_UINT;
        phase: HPDF_UINT): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetFlat (page: HPDF_Page; flatness: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetExtGState (page: HPDF_Page; ext_gstate: HPDF_ExtGState): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GSave (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_GRestore (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Concat (page: HPDF_Page; a: HPDF_REAL; b: HPDF_REAL; c: HPDF_REAL;
        d: HPDF_REAL; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_MoveTo (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_LineTo (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_CurveTo (page: HPDF_Page; x1: HPDF_REAL; y1: HPDF_REAL;
        x2: HPDF_REAL; y2: HPDF_REAL; x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_CurveTo2 (page: HPDF_Page; x2: HPDF_REAL; y2: HPDF_REAL;
        x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_CurveTo3 (page: HPDF_Page; x1: HPDF_REAL; y1: HPDF_REAL;
        x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_ClosePath (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Rectangle (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        width: HPDF_REAL; height: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Stroke (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_ClosePathStroke (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Fill (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Eofill (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_FillStroke (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_EofillStroke (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_ClosePathFillStroke (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_ClosePathEofillStroke (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_EndPath (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Clip (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Eoclip (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_BeginText (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_EndText (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetCharSpace (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetWordSpace (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetHorizontalScalling (page: HPDF_Page; value: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetTextLeading (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetFontAndSize (page: HPDF_Page; font: HPDF_Font;
        size: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetTextRenderingMode (page: HPDF_Page;
        mode: THPDF_TextRenderingMode): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetTextRaise (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_MoveTextPos (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_MoveTextPos2 (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetTextMatrix (page: HPDF_Page; a: HPDF_REAL; b: HPDF_REAL; 
        c: HPDF_REAL; d: HPDF_REAL; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_MoveToNextLine (page: HPDF_Page): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_ShowText (page: HPDF_Page; const text: HPDF_PCHAR): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_ShowTextNextLine (page: HPDF_Page; const text: HPDF_PCHAR):
        HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_ShowTextNextLineEx (page: HPDF_Page; word_space: HPDF_REAL;
        char_space: HPDF_REAL; const text: HPDF_PCHAR): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetGrayFill (page: HPDF_Page; gray: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetGrayStroke (page: HPDF_Page; gray: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetRGBFill (page: HPDF_Page; r: HPDF_REAL; g: HPDF_REAL;
        b: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetRGBStroke (page: HPDF_Page; r: HPDF_REAL; g: HPDF_REAL;
        b: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetCMYKFill (page: HPDF_Page; c: HPDF_REAL; m: HPDF_REAL;
        y: HPDF_REAL; k: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_SetCMYKStroke (page: HPDF_Page; c: HPDF_REAL; m: HPDF_REAL;
        y: HPDF_REAL; k: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_ExecuteXObject (page: HPDF_Page; obj: HPDF_XObject): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_DrawImage (page: HPDF_Page; image: HPDF_Image; x: HPDF_REAL;
        y: HPDF_REAL; width: HPDF_REAL; height: HPDF_REAL): HPDF_STATUS;
         extdecl LIBHPDF_LIB;

function HPDF_Page_Circle (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        ray: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_Arc (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL; ray: HPDF_REAL;
        ang1: HPDF_REAL; ang2: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_Ellipse (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        xray: HPDF_REAL; yray: HPDF_REAL): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_TextOut (page: HPDF_Page; xpos: HPDF_REAL; ypos: HPDF_REAL;
         const text: HPDF_PCHAR): HPDF_STATUS; extdecl LIBHPDF_LIB;

function HPDF_Page_TextRect  (page: HPDF_Page; left: HPDF_REAL; top: HPDF_REAL;
        right: HPDF_REAL; bottom: HPDF_REAL; const text: HPDF_PCHAR; 
        align: THPDF_TextAlignment; len: HPDF_PUINT): HPDF_STATUS; 
         extdecl LIBHPDF_LIB;

function HPDF_Page_SetSlideShow  (page: HPDF_Page; sstype: THPDF_TransitionStyle; 
        disp_time: HPDF_REAL; trans_time: HPDF_REAL): HPDF_STATUS; 
         extdecl LIBHPDF_LIB;
{%EndRegion}
{$else}
{%Region}
var
HPDF_GetVersion: function(): pchar; extdecl;
HPDF_NewEx: function(user_error_fn: THPDF_ErrorFunc;
        user_alloc_fn: THPDF_AllocFunc; user_free_fn: THPDF_FreeFunc;
        mem_pool_buf_size: HPDF_UINT; user_data: Pointer): HPDF_Doc;
         extdecl;
HPDF_New: function(user_error_fn: THPDF_ErrorFunc; user_data: Pointer): HPDF_Doc;
         extdecl;
HPDF_SetErrorHandler: function(pdf: HPDF_Doc; user_error_fn: THPDF_ErrorFunc):
        HPDF_STATUS; extdecl;
HPDF_Free : procedure (pdf: HPDF_Doc); extdecl;
HPDF_NewDoc : function(pdf: HPDF_Doc): HPDF_STATUS; extdecl;
HPDF_FreeDoc : procedure (pdf: HPDF_Doc); extdecl;
HPDF_HasDoc : function(pdf: HPDF_Doc): HPDF_BOOL; extdecl;
HPDF_FreeDocAll : procedure (pdf: HPDF_Doc); extdecl;
HPDF_SaveToStream: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_GetStreamSize: function(pdf: HPDF_Doc): HPDF_UINT32;
         extdecl;
HPDF_ReadFromStream: function(pdf: HPDF_Doc; buf: HPDF_PBYTE;
         size: HPDF_PUINT): HPDF_STATUS; extdecl;
HPDF_ResetStream: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_SaveToFile: function(pdf: HPDF_Doc; const file_name: HPDF_PCHAR): HPDF_STATUS;
         extdecl;
HPDF_GetError: function(pdf: HPDF_Doc): HPDF_STATUS; extdecl;
HPDF_ResetError  : procedure (pdf: HPDF_Doc); extdecl;
HPDF_SetPagesConfiguration: function(pdf: HPDF_Doc; page_per_pages: HPDF_UINT):
        HPDF_STATUS; extdecl;
HPDF_GetPageByIndex: function(pdf: HPDF_Doc; index: HPDF_UINT): HPDF_Page;
         extdecl;
HPDF_GetPageLayout: function(pdf: HPDF_Doc): THPDF_PageLayout;
         extdecl;
HPDF_SetPageLayout: function(pdf: HPDF_Doc; layout: THPDF_PageLayout): HPDF_STATUS;
         extdecl;
HPDF_GetPageMode: function(pdf: HPDF_Doc): THPDF_PageMode;
         extdecl;
HPDF_SetPageMode: function(pdf: HPDF_Doc; mode: THPDF_PageMode): HPDF_STATUS;
         extdecl;
HPDF_SetOpenAction: function(pdf: HPDF_Doc; open_action: HPDF_Destination):
        HPDF_STATUS; extdecl;
HPDF_GetViewerPreference: function(pdf: HPDF_Doc): HPDF_UINT;
         extdecl;
HPDF_SetViewerPreference: function(pdf: HPDF_Doc; value: HPDF_UINT): HPDF_STATUS;
         extdecl;
HPDF_GetCurrentPage: function(pdf: HPDF_Doc): HPDF_Page;
         extdecl;
HPDF_AddPage: function(pdf: HPDF_Doc): HPDF_Page; extdecl;
HPDF_InsertPage: function(pdf: HPDF_Doc; page: HPDF_Page): HPDF_Page;
         extdecl;
HPDF_Page_SetWidth: function(page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetHeight: function(page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetSize: function(page: HPDF_Page; size: THPDF_PageSizes;
        direction: THPDF_PageDirection): HPDF_STATUS; extdecl;
HPDF_Page_SetRotate: function(page: HPDF_Page; angle: HPDF_UINT16): HPDF_STATUS;
         extdecl;
HPDF_Page_SetZoom: function(page: HPDF_Page; zoom: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_GetFont: function(pdf: HPDF_Doc; const font_name: HPDF_PCHAR;
        const encoding_name: HPDF_PCHAR): HPDF_Font; extdecl;
HPDF_LoadType1FontFromFile: function(pdf: HPDF_Doc; afmfilename: HPDF_PCHAR;
        pfmfilename: HPDF_PCHAR): HPDF_PCHAR; extdecl;
HPDF_LoadTTFontFromFile: function(pdf: HPDF_Doc; const file_name: HPDF_PCHAR;
        embedding: HPDF_BOOL): HPDF_PCHAR; extdecl;
HPDF_LoadTTFontFromFile2: function(pdf: HPDF_Doc; const file_name: HPDF_PCHAR;
        index: HPDF_UINT; embedding: HPDF_BOOL): HPDF_CHAR;
         extdecl;
HPDF_AddPageLabel: function(pdf: HPDF_Doc; page_num: HPDF_UINT;
        style: THPDF_PageNumStyle; first_page: HPDF_UINT; const prefix: HPDF_PCHAR):
        HPDF_STATUS; extdecl;
HPDF_UseJPFonts: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_UseKRFonts: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_UseCNSFonts: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_UseCNTFonts: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_CreateOutline: function(pdf: HPDF_Doc; parent: HPDF_Outline;
        const title: HPDF_PCHAR; encoder: HPDF_Encoder): HPDF_Outline;
         extdecl;
HPDF_Outline_SetOpened: function(outline: HPDF_Outline; opened: HPDF_BOOL):
        HPDF_STATUS; extdecl;
HPDF_Outline_SetDestination: function(outline: HPDF_Outline;
        dst: HPDF_Destination): HPDF_STATUS; extdecl;
HPDF_Page_CreateDestination: function(page: HPDF_Page): HPDF_Destination;
         extdecl;
HPDF_Destination_SetXYZ: function(dst: HPDF_Destination; left: HPDF_REAL;
        top: HPDF_REAL; zoom: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Destination_SetFit: function(dst: HPDF_Destination): HPDF_STATUS;
         extdecl;
HPDF_Destination_SetFitH: function(dst: HPDF_Destination; top: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Destination_SetFitV: function(dst: HPDF_Destination; left: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Destination_SetFitR: function(dst: HPDF_Destination; left: HPDF_REAL;
        bottom: HPDF_REAL; right: HPDF_REAL; top: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Destination_SetFitB: function(dst: HPDF_Destination): HPDF_STATUS;
         extdecl;
HPDF_Destination_SetFitBH: function(dst: HPDF_Destination; top: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Destination_SetFitBV: function(dst: HPDF_Destination; left: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_GetEncoder: function(pdf: HPDF_Doc; const encoding_name: HPDF_PCHAR):
        HPDF_Encoder; extdecl;
HPDF_GetCurrentEncoder: function(pdf: HPDF_Doc): HPDF_Encoder;
         extdecl;
HPDF_SetCurrentEncoder: function(pdf: HPDF_Doc; const encoding_name: HPDF_PCHAR):
        HPDF_STATUS; extdecl;
HPDF_Encoder_GetType: function(encoder: HPDF_Encoder): THPDF_EncoderType;
         extdecl;
HPDF_Encoder_GetByteType: function(encoder: HPDF_Encoder; const text: HPDF_PCHAR;
        index: HPDF_UINT): THPDF_ByteType; extdecl;
HPDF_Encoder_GetUnicode: function(encoder: HPDF_Encoder; code: HPDF_UINT16):
        HPDF_UNICODE; extdecl;
HPDF_Encoder_GetWritingMode: function(encoder: HPDF_Encoder): THPDF_EncoderType;
         extdecl;
HPDF_UseJPEncodings: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_UseKREncodings: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_UseCNSEncodings: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_UseCNTEncodings: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_UseUTFEncodings: function(pdf: HPDF_Doc): HPDF_STATUS;
         extdecl;
HPDF_Page_CreateTextAnnot: function(page: HPDF_Page; rect: THPDF_Rect;
        const text: HPDF_PCHAR; encoder: HPDF_Encoder): HPDF_Annotation;
         extdecl;
HPDF_Page_CreateLinkAnnot: function(page: HPDF_Page; rect: THPDF_Rect;
        dst: HPDF_Destination): HPDF_Annotation; extdecl;
HPDF_Page_CreateURILinkAnnot: function(page: HPDF_Page; rect: THPDF_Rect;
        const uri: HPDF_PCHAR): HPDF_Annotation; extdecl;
HPDF_LinkAnnot_SetHighlightMode: function(annot: HPDF_Annotation;
        mode: THPDF_AnnotHighlightMode): HPDF_STATUS; extdecl;
HPDF_LinkAnnot_SetBorderStyle: function(annot: HPDF_Annotation; width: HPDF_REAL;
        dash_on: HPDF_UINT16; dash_off: HPDF_UINT16): HPDF_STATUS;
         extdecl;
HPDF_TextAnnot_SetIcon: function(annot: HPDF_Annotation; icon: THPDF_AnnotIcon):
        HPDF_STATUS; extdecl;
HPDF_TextAnnot_SetOpened: function(annot: HPDF_Annotation; opened: HPDF_BOOL):
        HPDF_STATUS; extdecl;
HPDF_LoadPngImageFromMem: function(pdf: HPDF_Doc; const buffer: HPDF_PBYTE; size: HPDF_UINT):
        HPDF_Image; extdecl;
HPDF_LoadPngImageFromFile: function(pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; extdecl;
HPDF_LoadPngImageFromFile2: function(pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; extdecl;
HPDF_LoadJpegImageFromFile: function(pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; extdecl;
HPDF_LoadRawImageFromFile: function(pdf: HPDF_Doc; filename: HPDF_PCHAR;
        width: HPDF_UINT; height: HPDF_UINT; color_space: THPDF_ColorSpace):
        HPDF_Image; extdecl;
HPDF_LoadRawImageFromMem: function(pdf: HPDF_Doc; const buf: HPDF_PBYTE;
        width: HPDF_UINT; height: HPDF_UINT; color_space: THPDF_ColorSpace;
        bits_per_component: HPDF_UINT): HPDF_Image; extdecl;
HPDF_Image_GetSize2: function(image: HPDF_Image; size: PHPDF_Point): HPDF_STATUS;
         extdecl;
HPDF_Image_GetWidth: function(image: HPDF_Image): HPDF_UINT;
         extdecl;
HPDF_Image_GetHeight: function(image: HPDF_Image): HPDF_UINT;
         extdecl;
HPDF_Image_GetBitsPerComponent: function(image: HPDF_Image): HPDF_UINT;
         extdecl;
HPDF_Image_GetColorSpace: function(image: HPDF_Image): HPDF_PCHAR;
         extdecl;
HPDF_Image_SetColorMask: function(image: HPDF_Image; rmin: HPDF_UINT;
        rmax: HPDF_UINT; gmin: HPDF_UINT; gmax: HPDF_UINT; bmin: HPDF_UINT;
        bmax: HPDF_UINT): HPDF_STATUS; extdecl;
HPDF_Image_SetMaskImage: function(image: HPDF_Image; mask_image: HPDF_Image):
        HPDF_STATUS; extdecl;
HPDF_SetInfoAttr: function(pdf: HPDF_Doc; info_type: THPDF_InfoType;
        const value: HPDF_PCHAR): HPDF_STATUS; extdecl;
HPDF_GetInfoAttr: function(pdf: HPDF_Doc; info_type: THPDF_InfoType): HPDF_PCHAR;
         extdecl;
HPDF_SetInfoDateAttr: function(pdf: HPDF_Doc; info_type: THPDF_InfoType; value: THPDF_Date):
        HPDF_STATUS; extdecl;
HPDF_SetPassword: function(pdf: HPDF_Doc; const owner_passwd: HPDF_PCHAR;
        const user_passwd: HPDF_PCHAR): HPDF_STATUS; extdecl;
HPDF_SetPermission: function(pdf: HPDF_Doc; permission: HPDF_UINT): HPDF_STATUS;
         extdecl;
HPDF_SetEncryptionMode: function(pdf: HPDF_Doc; mode: THPDF_EncryptMode;
        key_len: HPDF_UINT): HPDF_STATUS; extdecl;
HPDF_SetCompressionMode: function(pdf: HPDF_Doc; mode: HPDF_UINT): HPDF_STATUS;
         extdecl;
HPDF_Page_TextWidth: function(page: HPDF_Page; const text: HPDF_PCHAR): HPDF_REAL;
         extdecl;
HPDF_Page_MeasureText: function(page: HPDF_Page; const text: HPDF_PCHAR;
        width: HPDF_REAL; wordwrap: HPDF_BOOL; real_width: HPDF_PREAL): HPDF_UINT;
         extdecl;
HPDF_Page_GetWidth: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetHeight: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetGMode: function(page: HPDF_Page): HPDF_UINT16;
         extdecl;
HPDF_Page_GetCurrentPos2: function(page: HPDF_Page; pos: PHPDF_Point): HPDF_STATUS;
         extdecl;
HPDF_Page_GetCurrentTextPos2: function(page: HPDF_Page; pos: PHPDF_Point): HPDF_STATUS;
         extdecl;
HPDF_Page_GetCurrentFont: function(page: HPDF_Page): HPDF_Font;
         extdecl;
HPDF_Font_GetFontName: function(font: HPDF_Font): HPDF_PCHAR;
         extdecl;
HPDF_Font_GetEncodingName: function(font: HPDF_Font): HPDF_PCHAR;
         extdecl;
HPDF_Font_GetUnicodeWidth: function(font: HPDF_Font; code: HPDF_UNICODE): HPDF_INT;
         extdecl;
HPDF_Font_GetBBox: function(font: HPDF_Font): THPDF_Rect;
         extdecl;
HPDF_Font_GetAscent: function(font: HPDF_Font): HPDF_INT;
         extdecl;
HPDF_Font_GetDescent: function(font: HPDF_Font): HPDF_INT;
         extdecl;
HPDF_Font_GetXHeight: function(font: HPDF_Font): HPDF_UINT;
         extdecl;
HPDF_Font_GetCapHeight: function(font: HPDF_Font): HPDF_UINT;
         extdecl;
HPDF_Font_TextWidth : function(font: HPDF_Font; const text: PChar; len: HPDF_UINT): THPDF_TextWidth;
         extdecl;
HPDF_Font_MeasureText: function(font: HPDF_Font; const text: PChar; len: HPDF_UINT;
         width: HPDF_REAL; font_size: HPDF_REAL; char_space: HPDF_REAL;
         word_space: HPDF_REAL; wordwrap: HPDF_BOOL; real_width: HPDF_PREAL) : HPDF_UINT;
         extdecl;
HPDF_CreateExtGState : function(pdf: HPDF_Doc) : HPDF_ExtGState;
         extdecl;
HPDF_ExtGState_SetAlphaStroke : function(ext_gstate: HPDF_ExtGState;
         value: HPDF_REAL) : HPDF_STATUS; extdecl;
HPDF_ExtGState_SetAlphaFill : function(ext_gstate: HPDF_ExtGState;
         value: HPDF_REAL) : HPDF_STATUS; extdecl;
HPDF_ExtGState_SetBlendMode : function(ext_gstate: HPDF_ExtGState;
         mode: THPDF_BlendMode) : HPDF_STATUS; extdecl;
HPDF_Page_GetCurrentFontSize: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetTransMatrix: function(page: HPDF_Page): THPDF_TransMatrix;
         extdecl;
HPDF_Page_GetLineWidth: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetLineCap: function(page: HPDF_Page): THPDF_LineCap;
         extdecl;
HPDF_Page_GetLineJoin: function(page: HPDF_Page): THPDF_LineJoin;
         extdecl;
HPDF_Page_GetMiterLimit: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetDash: function(page: HPDF_Page): THPDF_DashMode;
         extdecl;
HPDF_Page_GetFlat: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetCharSpace: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetWordSpace: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetHorizontalScalling: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetTextLeading: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetTextRenderingMode: function(page: HPDF_Page): THPDF_TextRenderingMode;
         extdecl;
HPDF_Page_GetTextRaise: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetRGBFill: function(page: HPDF_Page): THPDF_RGBColor;
         extdecl;
HPDF_Page_GetRGBStroke: function(page: HPDF_Page): THPDF_RGBColor;
         extdecl;
HPDF_Page_GetCMYKFill: function(page: HPDF_Page): THPDF_CMYKColor;
         extdecl;
HPDF_Page_GetCMYKStroke: function(page: HPDF_Page): THPDF_CMYKColor;
         extdecl;
HPDF_Page_GetGrayFill: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetGrayStroke: function(page: HPDF_Page): HPDF_REAL;
         extdecl;
HPDF_Page_GetStrokingColorSpace: function(page: HPDF_Page): THPDF_ColorSpace;
         extdecl;
HPDF_Page_GetFillingColorSpace: function(page: HPDF_Page): THPDF_ColorSpace;
         extdecl;
HPDF_Page_GetTextMatrix: function(page: HPDF_Page): THPDF_TransMatrix;
         extdecl;
HPDF_Page_GetGStateDepth: function(page: HPDF_Page): HPDF_UINT;
         extdecl;
HPDF_Page_SetLineWidth: function(page: HPDF_Page; line_width: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Page_SetLineCap: function(page: HPDF_Page; line_cap: THPDF_LineCap):
        HPDF_STATUS; extdecl;
HPDF_Page_SetLineJoin: function(page: HPDF_Page; line_join: THPDF_LineJoin):
        HPDF_STATUS; extdecl;
HPDF_Page_SetMiterLimit: function(page: HPDF_Page; miter_limit: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Page_SetDash: function(page: HPDF_Page; ptn: HPDF_PUINT16; num_param: HPDF_UINT;
        phase: HPDF_UINT): HPDF_STATUS;
         extdecl;
HPDF_Page_SetFlat: function(page: HPDF_Page; flatness: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetExtGState: function(page: HPDF_Page; ext_gstate: HPDF_ExtGState): HPDF_STATUS;
         extdecl;
HPDF_Page_GSave: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_GRestore: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_Concat: function(page: HPDF_Page; a: HPDF_REAL; b: HPDF_REAL; c: HPDF_REAL;
        d: HPDF_REAL; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_MoveTo: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_LineTo: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_CurveTo: function(page: HPDF_Page; x1: HPDF_REAL; y1: HPDF_REAL;
        x2: HPDF_REAL; y2: HPDF_REAL; x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_CurveTo2: function(page: HPDF_Page; x2: HPDF_REAL; y2: HPDF_REAL;
        x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_CurveTo3: function(page: HPDF_Page; x1: HPDF_REAL; y1: HPDF_REAL;
        x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_ClosePath: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_Rectangle: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        width: HPDF_REAL; height: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_Stroke: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_ClosePathStroke: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_Fill: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_Eofill: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_FillStroke: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_EofillStroke: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_ClosePathFillStroke: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_ClosePathEofillStroke: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_EndPath: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_Clip: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_Eoclip: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_BeginText: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_EndText: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_SetCharSpace: function(page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetWordSpace: function(page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetHorizontalScalling: function(page: HPDF_Page; value: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Page_SetTextLeading: function(page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetFontAndSize: function(page: HPDF_Page; font: HPDF_Font;
        size: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_SetTextRenderingMode: function(page: HPDF_Page;
        mode: THPDF_TextRenderingMode): HPDF_STATUS; extdecl;
HPDF_Page_SetTextRaise: function(page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_MoveTextPos: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Page_MoveTextPos2: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Page_SetTextMatrix: function(page: HPDF_Page; a: HPDF_REAL; b: HPDF_REAL;
        c: HPDF_REAL; d: HPDF_REAL; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; extdecl;
HPDF_Page_MoveToNextLine: function(page: HPDF_Page): HPDF_STATUS;
         extdecl;
HPDF_Page_ShowText: function(page: HPDF_Page; const text: HPDF_PCHAR): HPDF_STATUS;
         extdecl;
HPDF_Page_ShowTextNextLine: function(page: HPDF_Page; const text: HPDF_PCHAR):
        HPDF_STATUS; extdecl;
HPDF_Page_ShowTextNextLineEx: function(page: HPDF_Page; word_space: HPDF_REAL;
        char_space: HPDF_REAL; const text: HPDF_PCHAR): HPDF_STATUS;
         extdecl;
HPDF_Page_SetGrayFill: function(page: HPDF_Page; gray: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetGrayStroke: function(page: HPDF_Page; gray: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_SetRGBFill: function(page: HPDF_Page; r: HPDF_REAL; g: HPDF_REAL;
        b: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_SetRGBStroke: function(page: HPDF_Page; r: HPDF_REAL; g: HPDF_REAL;
        b: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_SetCMYKFill: function(page: HPDF_Page; c: HPDF_REAL; m: HPDF_REAL;
        y: HPDF_REAL; k: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_SetCMYKStroke: function(page: HPDF_Page; c: HPDF_REAL; m: HPDF_REAL;
        y: HPDF_REAL; k: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_ExecuteXObject: function(page: HPDF_Page; obj: HPDF_XObject): HPDF_STATUS;
         extdecl;
HPDF_Page_DrawImage: function(page: HPDF_Page; image: HPDF_Image; x: HPDF_REAL;
        y: HPDF_REAL; width: HPDF_REAL; height: HPDF_REAL): HPDF_STATUS;
         extdecl;
HPDF_Page_Circle: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        ray: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_Arc: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL; ray: HPDF_REAL;
        ang1: HPDF_REAL; ang2: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_Ellipse: function(page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        xray: HPDF_REAL; yray: HPDF_REAL): HPDF_STATUS; extdecl;
HPDF_Page_TextOut: function(page: HPDF_Page; xpos: HPDF_REAL; ypos: HPDF_REAL;
         const text: HPDF_PCHAR): HPDF_STATUS; extdecl;
HPDF_Page_TextRect : function(page: HPDF_Page; left: HPDF_REAL; top: HPDF_REAL;
        right: HPDF_REAL; bottom: HPDF_REAL; const text: HPDF_PCHAR;
        align: THPDF_TextAlignment; len: HPDF_PUINT): HPDF_STATUS;
         extdecl;
HPDF_Page_SetSlideShow : function(page: HPDF_Page; sstype: THPDF_TransitionStyle;
        disp_time: HPDF_REAL; trans_time: HPDF_REAL): HPDF_STATUS;
         extdecl;
{%EndRegion}
{$endif}

function HPDF_Page_GetCurrentPos (page: HPDF_Page): THPDF_Point;
function HPDF_Page_GetCurrentTextPos (page: HPDF_Page): THPDF_Point;
function HPDF_Image_GetSize (image: HPDF_Image): THPDF_Point;

function LoadHaru: boolean;

implementation

function HPDF_Page_GetCurrentPos (page: HPDF_Page): THPDF_Point;
var
  pos: THPDF_Point;
begin
  HPDF_Page_GetCurrentPos2 (page, @pos);
  result := pos;
end;

function HPDF_Page_GetCurrentTextPos (page: HPDF_Page): THPDF_Point;
var
  pos: THPDF_Point;
begin
  HPDF_Page_GetCurrentTextPos2 (page, @pos);
  result := pos;
end;

function HPDF_Image_GetSize (image: HPDF_Image): THPDF_Point;
var
  size: THPDF_Point;
begin
  HPDF_Image_GetSize2 (image, @size);
  result := size;
end;

{$ifdef USE_STATIC}
function LoadHaru: boolean;
begin
  result := true;
end;
{$endif}
{$ifndef USE_STATIC}
//loads Haru library, returns false if loading failed
var
  lib: TLibHandle;

function LoadHaru: boolean;
  function LoadHaruProc(fnName: string): pointer;
  begin
    result := GetProcedureAddress(lib, fnName)
  end;
begin
  result := true;
  lib := LoadLibrary(LIBHPDF_LIB);
  if lib = 0 then begin
      result := false;
      Exit;
  end;

  @HPDF_AddPage                      := LoadHaruProc('HPDF_AddPage');
  @HPDF_AddPageLabel                 := LoadHaruProc('HPDF_AddPageLabel');
  @HPDF_CreateExtGState              := LoadHaruProc('HPDF_CreateExtGState');
  @HPDF_CreateOutline                := LoadHaruProc('HPDF_CreateOutline');
  @HPDF_Destination_SetFit           := LoadHaruProc('HPDF_Destination_SetFit');
  @HPDF_Destination_SetFitB          := LoadHaruProc('HPDF_Destination_SetFitB');
  @HPDF_Destination_SetFitBH         := LoadHaruProc('HPDF_Destination_SetFitBH');
  @HPDF_Destination_SetFitBV         := LoadHaruProc('HPDF_Destination_SetFitBV');
  @HPDF_Destination_SetFitH          := LoadHaruProc('HPDF_Destination_SetFitH');
  @HPDF_Destination_SetFitR          := LoadHaruProc('HPDF_Destination_SetFitR');
  @HPDF_Destination_SetFitV          := LoadHaruProc('HPDF_Destination_SetFitV');
  @HPDF_Destination_SetXYZ           := LoadHaruProc('HPDF_Destination_SetXYZ');
  @HPDF_Encoder_GetByteType          := LoadHaruProc('HPDF_Encoder_GetByteType');
  @HPDF_Encoder_GetType              := LoadHaruProc('HPDF_Encoder_GetType');
  @HPDF_Encoder_GetUnicode           := LoadHaruProc('HPDF_Encoder_GetUnicode');
  @HPDF_Encoder_GetWritingMode       := LoadHaruProc('HPDF_Encoder_GetWritingMode');
  @HPDF_ExtGState_SetAlphaFill       := LoadHaruProc('HPDF_ExtGState_SetAlphaFill');
  @HPDF_ExtGState_SetAlphaStroke     := LoadHaruProc('HPDF_ExtGState_SetAlphaStroke');
  @HPDF_ExtGState_SetBlendMode       := LoadHaruProc('HPDF_ExtGState_SetBlendMode');
  @HPDF_Font_GetAscent               := LoadHaruProc('HPDF_Font_GetAscent');
  @HPDF_Font_GetBBox                 := LoadHaruProc('HPDF_Font_GetBBox');
  @HPDF_Font_GetCapHeight            := LoadHaruProc('HPDF_Font_GetCapHeight');
  @HPDF_Font_GetDescent              := LoadHaruProc('HPDF_Font_GetDescent');
  @HPDF_Font_GetEncodingName         := LoadHaruProc('HPDF_Font_GetEncodingName');
  @HPDF_Font_GetFontName             := LoadHaruProc('HPDF_Font_GetFontName');
  @HPDF_Font_GetUnicodeWidth         := LoadHaruProc('HPDF_Font_GetUnicodeWidth');
  @HPDF_Font_GetXHeight              := LoadHaruProc('HPDF_Font_GetXHeight');
  @HPDF_Font_MeasureText             := LoadHaruProc('HPDF_Font_MeasureText');
  @HPDF_Font_TextWidth               := LoadHaruProc('HPDF_Font_TextWidth');
  @HPDF_Free                         := LoadHaruProc('HPDF_Free');
  @HPDF_FreeDoc                      := LoadHaruProc('HPDF_FreeDoc');
  @HPDF_FreeDocAll                   := LoadHaruProc('HPDF_FreeDocAll');
  @HPDF_GetCurrentEncoder            := LoadHaruProc('HPDF_GetCurrentEncoder');
  @HPDF_GetCurrentPage               := LoadHaruProc('HPDF_GetCurrentPage');
  @HPDF_GetEncoder                   := LoadHaruProc('HPDF_GetEncoder');
  @HPDF_GetError                     := LoadHaruProc('HPDF_GetError');
//  @HPDF_GetErrorDetail               := LoadHaruProc('HPDF_GetErrorDetail');
  @HPDF_GetFont                      := LoadHaruProc('HPDF_GetFont');
  @HPDF_GetInfoAttr                  := LoadHaruProc('HPDF_GetInfoAttr');
  @HPDF_GetPageByIndex               := LoadHaruProc('HPDF_GetPageByIndex');
  @HPDF_GetPageLayout                := LoadHaruProc('HPDF_GetPageLayout');
  @HPDF_GetPageMode                  := LoadHaruProc('HPDF_GetPageMode');
  @HPDF_GetStreamSize                := LoadHaruProc('HPDF_GetStreamSize');
  @HPDF_GetVersion                   := LoadHaruProc('HPDF_GetVersion');
  @HPDF_GetViewerPreference          := LoadHaruProc('HPDF_GetViewerPreference');
  @HPDF_HasDoc                       := LoadHaruProc('HPDF_HasDoc');
  @HPDF_Image_GetBitsPerComponent    := LoadHaruProc('HPDF_Image_GetBitsPerComponent');
  @HPDF_Image_GetColorSpace          := LoadHaruProc('HPDF_Image_GetColorSpace');
  @HPDF_Image_GetHeight              := LoadHaruProc('HPDF_Image_GetHeight');
//  @HPDF_Image_GetSize                := LoadHaruProc('HPDF_Image_GetSize');
  @HPDF_Image_GetSize2               := LoadHaruProc('HPDF_Image_GetSize2');
  @HPDF_Image_GetWidth               := LoadHaruProc('HPDF_Image_GetWidth');
  @HPDF_Image_SetColorMask           := LoadHaruProc('HPDF_Image_SetColorMask');
  @HPDF_Image_SetMaskImage           := LoadHaruProc('HPDF_Image_SetMaskImage');
  @HPDF_InsertPage                   := LoadHaruProc('HPDF_InsertPage');
  @HPDF_LinkAnnot_SetBorderStyle     := LoadHaruProc('HPDF_LinkAnnot_SetBorderStyle');
  @HPDF_LinkAnnot_SetHighlightMode   := LoadHaruProc('HPDF_LinkAnnot_SetHighlightMode');
  @HPDF_LoadJpegImageFromFile        := LoadHaruProc('HPDF_LoadJpegImageFromFile');
  @HPDF_LoadPngImageFromFile         := LoadHaruProc('HPDF_LoadPngImageFromFile');
  @HPDF_LoadPngImageFromMem          := LoadHaruProc('HPDF_LoadPngImageFromMem');
  @HPDF_LoadPngImageFromFile2        := LoadHaruProc('HPDF_LoadPngImageFromFile2');
  @HPDF_LoadRawImageFromFile         := LoadHaruProc('HPDF_LoadRawImageFromFile');
  @HPDF_LoadRawImageFromMem          := LoadHaruProc('HPDF_LoadRawImageFromMem');
  @HPDF_LoadTTFontFromFile           := LoadHaruProc('HPDF_LoadTTFontFromFile');
  @HPDF_LoadTTFontFromFile2          := LoadHaruProc('HPDF_LoadTTFontFromFile2');
  @HPDF_LoadType1FontFromFile        := LoadHaruProc('HPDF_LoadType1FontFromFile');
  @HPDF_New                          := LoadHaruProc('HPDF_New');
  @HPDF_NewDoc                       := LoadHaruProc('HPDF_NewDoc');
  @HPDF_NewEx                        := LoadHaruProc('HPDF_NewEx');
  @HPDF_Outline_SetDestination       := LoadHaruProc('HPDF_Outline_SetDestination');
  @HPDF_Outline_SetOpened            := LoadHaruProc('HPDF_Outline_SetOpened');
  @HPDF_Page_Arc                     := LoadHaruProc('HPDF_Page_Arc');
  @HPDF_Page_BeginText               := LoadHaruProc('HPDF_Page_BeginText');
  @HPDF_Page_Circle                  := LoadHaruProc('HPDF_Page_Circle');
  @HPDF_Page_Clip                    := LoadHaruProc('HPDF_Page_Clip');
  @HPDF_Page_ClosePath               := LoadHaruProc('HPDF_Page_ClosePath');
  @HPDF_Page_ClosePathEofillStroke   := LoadHaruProc('HPDF_Page_ClosePathEofillStroke');
  @HPDF_Page_ClosePathFillStroke     := LoadHaruProc('HPDF_Page_ClosePathFillStroke');
  @HPDF_Page_ClosePathStroke         := LoadHaruProc('HPDF_Page_ClosePathStroke');
  @HPDF_Page_Concat                  := LoadHaruProc('HPDF_Page_Concat');
  @HPDF_Page_CreateDestination       := LoadHaruProc('HPDF_Page_CreateDestination');
  @HPDF_Page_CreateLinkAnnot         := LoadHaruProc('HPDF_Page_CreateLinkAnnot');
  @HPDF_Page_CreateTextAnnot         := LoadHaruProc('HPDF_Page_CreateTextAnnot');
  @HPDF_Page_CreateURILinkAnnot      := LoadHaruProc('HPDF_Page_CreateURILinkAnnot');
  @HPDF_Page_CurveTo                 := LoadHaruProc('HPDF_Page_CurveTo');
  @HPDF_Page_CurveTo2                := LoadHaruProc('HPDF_Page_CurveTo2');
  @HPDF_Page_CurveTo3                := LoadHaruProc('HPDF_Page_CurveTo3');
  @HPDF_Page_DrawImage               := LoadHaruProc('HPDF_Page_DrawImage');
  @HPDF_Page_Ellipse                 := LoadHaruProc('HPDF_Page_Ellipse');
  @HPDF_Page_EndPath                 := LoadHaruProc('HPDF_Page_EndPath');
  @HPDF_Page_EndText                 := LoadHaruProc('HPDF_Page_EndText');
  @HPDF_Page_Eoclip                  := LoadHaruProc('HPDF_Page_Eoclip');
  @HPDF_Page_Eofill                  := LoadHaruProc('HPDF_Page_Eofill');
  @HPDF_Page_EofillStroke            := LoadHaruProc('HPDF_Page_EofillStroke');
  @HPDF_Page_ExecuteXObject          := LoadHaruProc('HPDF_Page_ExecuteXObject');
  @HPDF_Page_Fill                    := LoadHaruProc('HPDF_Page_Fill');
  @HPDF_Page_FillStroke              := LoadHaruProc('HPDF_Page_FillStroke');
  @HPDF_Page_GetCharSpace            := LoadHaruProc('HPDF_Page_GetCharSpace');
  @HPDF_Page_GetCMYKFill             := LoadHaruProc('HPDF_Page_GetCMYKFill');
  @HPDF_Page_GetCMYKStroke           := LoadHaruProc('HPDF_Page_GetCMYKStroke');
  @HPDF_Page_GetCurrentFont          := LoadHaruProc('HPDF_Page_GetCurrentFont');
  @HPDF_Page_GetCurrentFontSize      := LoadHaruProc('HPDF_Page_GetCurrentFontSize');
//  @HPDF_Page_GetCurrentPos           := LoadHaruProc('HPDF_Page_GetCurrentPos');
  @HPDF_Page_GetCurrentPos2          := LoadHaruProc('HPDF_Page_GetCurrentPos2');
//  @HPDF_Page_GetCurrentTextPos       := LoadHaruProc('HPDF_Page_GetCurrentTextPos');
  @HPDF_Page_GetCurrentTextPos2      := LoadHaruProc('HPDF_Page_GetCurrentTextPos2');
  @HPDF_Page_GetDash                 := LoadHaruProc('HPDF_Page_GetDash');
  @HPDF_Page_GetFillingColorSpace    := LoadHaruProc('HPDF_Page_GetFillingColorSpace');
  @HPDF_Page_GetFlat                 := LoadHaruProc('HPDF_Page_GetFlat');
  @HPDF_Page_GetGMode                := LoadHaruProc('HPDF_Page_GetGMode');
  @HPDF_Page_GetGrayFill             := LoadHaruProc('HPDF_Page_GetGrayFill');
  @HPDF_Page_GetGrayStroke           := LoadHaruProc('HPDF_Page_GetGrayStroke');
  @HPDF_Page_GetGStateDepth          := LoadHaruProc('HPDF_Page_GetGStateDepth');
  @HPDF_Page_GetHeight               := LoadHaruProc('HPDF_Page_GetHeight');
  @HPDF_Page_GetHorizontalScalling   := LoadHaruProc('HPDF_Page_GetHorizontalScalling');
  @HPDF_Page_GetLineCap              := LoadHaruProc('HPDF_Page_GetLineCap');
  @HPDF_Page_GetLineJoin             := LoadHaruProc('HPDF_Page_GetLineJoin');
  @HPDF_Page_GetLineWidth            := LoadHaruProc('HPDF_Page_GetLineWidth');
  @HPDF_Page_GetMiterLimit           := LoadHaruProc('HPDF_Page_GetMiterLimit');
  @HPDF_Page_GetRGBFill              := LoadHaruProc('HPDF_Page_GetRGBFill');
  @HPDF_Page_GetRGBStroke            := LoadHaruProc('HPDF_Page_GetRGBStroke');
  @HPDF_Page_GetStrokingColorSpace   := LoadHaruProc('HPDF_Page_GetStrokingColorSpace');
  @HPDF_Page_GetTextLeading          := LoadHaruProc('HPDF_Page_GetTextLeading');
  @HPDF_Page_GetTextMatrix           := LoadHaruProc('HPDF_Page_GetTextMatrix');
//  @HPDF_Page_GetTextRise             := LoadHaruProc('HPDF_Page_GetTextRise');
  @HPDF_Page_GetTextRaise            := LoadHaruProc('HPDF_Page_GetTextRaise');
  @HPDF_Page_GetTextRenderingMode    := LoadHaruProc('HPDF_Page_GetTextRenderingMode');
  @HPDF_Page_GetTransMatrix          := LoadHaruProc('HPDF_Page_GetTransMatrix');
  @HPDF_Page_GetWidth                := LoadHaruProc('HPDF_Page_GetWidth');
  @HPDF_Page_GetWordSpace            := LoadHaruProc('HPDF_Page_GetWordSpace');
  @HPDF_Page_GRestore                := LoadHaruProc('HPDF_Page_GRestore');
  @HPDF_Page_GSave                   := LoadHaruProc('HPDF_Page_GSave');
  @HPDF_Page_LineTo                  := LoadHaruProc('HPDF_Page_LineTo');
  @HPDF_Page_MeasureText             := LoadHaruProc('HPDF_Page_MeasureText');
  @HPDF_Page_MoveTextPos             := LoadHaruProc('HPDF_Page_MoveTextPos');
  @HPDF_Page_MoveTextPos2            := LoadHaruProc('HPDF_Page_MoveTextPos2');
  @HPDF_Page_MoveTo                  := LoadHaruProc('HPDF_Page_MoveTo');
  @HPDF_Page_MoveToNextLine          := LoadHaruProc('HPDF_Page_MoveToNextLine');
  @HPDF_Page_Rectangle               := LoadHaruProc('HPDF_Page_Rectangle');
  @HPDF_Page_SetCharSpace            := LoadHaruProc('HPDF_Page_SetCharSpace');
  @HPDF_Page_SetCMYKFill             := LoadHaruProc('HPDF_Page_SetCMYKFill');
  @HPDF_Page_SetCMYKStroke           := LoadHaruProc('HPDF_Page_SetCMYKStroke');
  @HPDF_Page_SetDash                 := LoadHaruProc('HPDF_Page_SetDash');
  @HPDF_Page_SetExtGState            := LoadHaruProc('HPDF_Page_SetExtGState');
  @HPDF_Page_SetFlat                 := LoadHaruProc('HPDF_Page_SetFlat');
  @HPDF_Page_SetFontAndSize          := LoadHaruProc('HPDF_Page_SetFontAndSize');
  @HPDF_Page_SetGrayFill             := LoadHaruProc('HPDF_Page_SetGrayFill');
  @HPDF_Page_SetGrayStroke           := LoadHaruProc('HPDF_Page_SetGrayStroke');
  @HPDF_Page_SetHeight               := LoadHaruProc('HPDF_Page_SetHeight');
  @HPDF_Page_SetHorizontalScalling   := LoadHaruProc('HPDF_Page_SetHorizontalScalling');
  @HPDF_Page_SetLineCap              := LoadHaruProc('HPDF_Page_SetLineCap');
  @HPDF_Page_SetLineJoin             := LoadHaruProc('HPDF_Page_SetLineJoin');
  @HPDF_Page_SetLineWidth            := LoadHaruProc('HPDF_Page_SetLineWidth');
  @HPDF_Page_SetMiterLimit           := LoadHaruProc('HPDF_Page_SetMiterLimit');
  @HPDF_Page_SetRGBFill              := LoadHaruProc('HPDF_Page_SetRGBFill');
  @HPDF_Page_SetRGBStroke            := LoadHaruProc('HPDF_Page_SetRGBStroke');
  @HPDF_Page_SetRotate               := LoadHaruProc('HPDF_Page_SetRotate');
  @HPDF_Page_SetSize                 := LoadHaruProc('HPDF_Page_SetSize');
  @HPDF_Page_SetSlideShow            := LoadHaruProc('HPDF_Page_SetSlideShow');
  @HPDF_Page_SetTextLeading          := LoadHaruProc('HPDF_Page_SetTextLeading');
  @HPDF_Page_SetTextMatrix           := LoadHaruProc('HPDF_Page_SetTextMatrix');
//  @HPDF_Page_SetTextRise             := LoadHaruProc('HPDF_Page_SetTextRise');
  @HPDF_Page_SetTextRaise            := LoadHaruProc('HPDF_Page_SetTextRaise');
  @HPDF_Page_SetTextRenderingMode    := LoadHaruProc('HPDF_Page_SetTextRenderingMode');
  @HPDF_Page_SetWidth                := LoadHaruProc('HPDF_Page_SetWidth');
  @HPDF_Page_SetWordSpace            := LoadHaruProc('HPDF_Page_SetWordSpace');
  @HPDF_Page_ShowText                := LoadHaruProc('HPDF_Page_ShowText');
  @HPDF_Page_ShowTextNextLine        := LoadHaruProc('HPDF_Page_ShowTextNextLine');
  @HPDF_Page_ShowTextNextLineEx      := LoadHaruProc('HPDF_Page_ShowTextNextLineEx');
  @HPDF_Page_Stroke                  := LoadHaruProc('HPDF_Page_Stroke');
  @HPDF_Page_TextOut                 := LoadHaruProc('HPDF_Page_TextOut');
  @HPDF_Page_TextRect                := LoadHaruProc('HPDF_Page_TextRect');
  @HPDF_Page_TextWidth               := LoadHaruProc('HPDF_Page_TextWidth');
  @HPDF_ReadFromStream               := LoadHaruProc('HPDF_ReadFromStream');
  @HPDF_ResetError                   := LoadHaruProc('HPDF_ResetError');
  @HPDF_ResetStream                  := LoadHaruProc('HPDF_ResetStream');
  @HPDF_SaveToFile                   := LoadHaruProc('HPDF_SaveToFile');
  @HPDF_SaveToStream                 := LoadHaruProc('HPDF_SaveToStream');
  @HPDF_SetCompressionMode           := LoadHaruProc('HPDF_SetCompressionMode');
  @HPDF_SetCurrentEncoder            := LoadHaruProc('HPDF_SetCurrentEncoder');
  @HPDF_SetEncryptionMode            := LoadHaruProc('HPDF_SetEncryptionMode');
  @HPDF_SetErrorHandler              := LoadHaruProc('HPDF_SetErrorHandler');
  @HPDF_SetInfoAttr                  := LoadHaruProc('HPDF_SetInfoAttr');
//  @HPDF_SetInfoDateAttr             := LoadHaruProc('HPDF_SetInfoDateAttr');
  @HPDF_SetOpenAction                := LoadHaruProc('HPDF_SetOpenAction');
  @HPDF_SetPageLayout                := LoadHaruProc('HPDF_SetPageLayout');
  @HPDF_SetPageMode                  := LoadHaruProc('HPDF_SetPageMode');
  @HPDF_SetPagesConfiguration        := LoadHaruProc('HPDF_SetPagesConfiguration');
  @HPDF_SetPassword                  := LoadHaruProc('HPDF_SetPassword');
  @HPDF_SetPermission                := LoadHaruProc('HPDF_SetPermission');
  @HPDF_SetViewerPreference          := LoadHaruProc('HPDF_SetViewerPreference');
  @HPDF_TextAnnot_SetIcon            := LoadHaruProc('HPDF_TextAnnot_SetIcon');
  @HPDF_TextAnnot_SetOpened          := LoadHaruProc('HPDF_TextAnnot_SetOpened');
  @HPDF_UseCNSEncodings              := LoadHaruProc('HPDF_UseCNSEncodings');
  @HPDF_UseCNSFonts                  := LoadHaruProc('HPDF_UseCNSFonts');
  @HPDF_UseCNTEncodings              := LoadHaruProc('HPDF_UseCNTEncodings');
  @HPDF_UseCNTFonts                  := LoadHaruProc('HPDF_UseCNTFonts');
  @HPDF_UseJPEncodings               := LoadHaruProc('HPDF_UseJPEncodings');
  @HPDF_UseJPFonts                   := LoadHaruProc('HPDF_UseJPFonts');
  @HPDF_UseKREncodings               := LoadHaruProc('HPDF_UseKREncodings');
  @HPDF_UseKRFonts                   := LoadHaruProc('HPDF_UseKRFonts');
  @HPDF_UseUTFEncodings              := LoadHaruProc('HPDF_UseUTFEncodings');
end;

initialization
  lib := 0;

finalization
  if lib <> 0 then FreeLibrary(lib);
{$endif}

end.
