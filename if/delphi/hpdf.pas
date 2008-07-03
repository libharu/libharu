{*
 * << Haru Free PDF Library 2.0.6 >> -- hpdf.pas
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
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

interface

uses
  SysUtils, hpdf_types;

const
  LIBHPDF_DLL = 'libhpdf.dll';

{*
  NOTE:

  if you want to use Haru with Kylix/FreePascal on Linux,
  change "libhpdf.dll" to "libhpdf.so" and change "stdcall" to "cdecl"
  (This file and hpdf_types.pas)

*}

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

function HPDF_NewEx (user_error_fn: THPDF_ErrorFunc;
        user_alloc_fn: THPDF_AllocFunc; user_free_fn: THPDF_FreeFunc;
        mem_pool_buf_size: HPDF_UINT; user_data: Pointer): HPDF_Doc;
         stdcall external LIBHPDF_DLL;


function HPDF_New (user_error_fn: THPDF_ErrorFunc; user_data: Pointer): HPDF_Doc;
         stdcall external LIBHPDF_DLL;


function HPDF_SetErrorHandler (pdf: HPDF_Doc; user_error_fn: THPDF_ErrorFunc):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


procedure HPDF_Free (pdf: HPDF_Doc); stdcall external LIBHPDF_DLL;


function HPDF_NewDoc (pdf: HPDF_Doc): HPDF_STATUS; stdcall external LIBHPDF_DLL;


procedure HPDF_FreeDoc (pdf: HPDF_Doc); stdcall external LIBHPDF_DLL;


function HPDF_HasDoc (pdf: HPDF_Doc): HPDF_BOOL; stdcall external LIBHPDF_DLL;


procedure HPDF_FreeDocAll (pdf: HPDF_Doc); stdcall external LIBHPDF_DLL;


function HPDF_SaveToStream (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_GetStreamSize (pdf: HPDF_Doc): HPDF_UINT32;
         stdcall external LIBHPDF_DLL;


function HPDF_ReadFromStream (pdf: HPDF_Doc; buf: HPDF_PBYTE; 
         size: HPDF_PUINT): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_ResetStream (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_SaveToFile (pdf: HPDF_Doc; const file_name: HPDF_PCHAR): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_GetError (pdf: HPDF_Doc): HPDF_STATUS; stdcall external LIBHPDF_DLL;


procedure HPDF_ResetError (pdf: HPDF_Doc); stdcall external LIBHPDF_DLL;


function HPDF_SetPagesConfiguration (pdf: HPDF_Doc; page_per_pages: HPDF_UINT):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_GetPageByIndex (pdf: HPDF_Doc; index: HPDF_UINT): HPDF_Page;
         stdcall external LIBHPDF_DLL;


function HPDF_GetPageLayout (pdf: HPDF_Doc): THPDF_PageLayout;
         stdcall external LIBHPDF_DLL;


function HPDF_SetPageLayout (pdf: HPDF_Doc; layout: THPDF_PageLayout): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_GetPageMode (pdf: HPDF_Doc): THPDF_PageMode;
         stdcall external LIBHPDF_DLL;


function HPDF_SetPageMode (pdf: HPDF_Doc; mode: THPDF_PageMode): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_SetOpenAction (pdf: HPDF_Doc; open_action: HPDF_Destination):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_GetViewerPreference (pdf: HPDF_Doc): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_SetViewerPreference (pdf: HPDF_Doc; value: HPDF_UINT): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_GetCurrentPage (pdf: HPDF_Doc): HPDF_Page;
         stdcall external LIBHPDF_DLL;


function HPDF_AddPage (pdf: HPDF_Doc): HPDF_Page; stdcall external LIBHPDF_DLL;


function HPDF_InsertPage (pdf: HPDF_Doc; page: HPDF_Page): HPDF_Page;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetWidth (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetHeight (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetSize (page: HPDF_Page; size: THPDF_PageSizes;
        direction: THPDF_PageDirection): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetRotate (page: HPDF_Page; angle: HPDF_UINT16): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;

function HPDF_Page_SetZoom (page: HPDF_Page; zoom: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;

function HPDF_GetFont (pdf: HPDF_Doc; const font_name: HPDF_PCHAR;
        const encoding_name: HPDF_PCHAR): HPDF_Font; stdcall external LIBHPDF_DLL;


function HPDF_LoadType1FontFromFile (pdf: HPDF_Doc; afmfilename: HPDF_PCHAR;
        pfmfilename: HPDF_PCHAR): HPDF_PCHAR; stdcall external LIBHPDF_DLL;


function HPDF_LoadTTFontFromFile (pdf: HPDF_Doc; const file_name: HPDF_PCHAR;
        embedding: HPDF_BOOL): HPDF_PCHAR; stdcall external LIBHPDF_DLL;


function HPDF_LoadTTFontFromFile2 (pdf: HPDF_Doc; const file_name: HPDF_PCHAR;
        index: HPDF_UINT; embedding: HPDF_BOOL): HPDF_CHAR;
         stdcall external LIBHPDF_DLL;

function HPDF_AddPageLabel (pdf: HPDF_Doc; page_num: HPDF_UINT;
        style: THPDF_PageNumStyle; first_page: HPDF_UINT; const prefix: HPDF_PCHAR):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_UseJPFonts (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_UseKRFonts (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_UseCNSFonts (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_UseCNTFonts (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_CreateOutline (pdf: HPDF_Doc; parent: HPDF_Outline;
        const title: HPDF_PCHAR; encoder: HPDF_Encoder): HPDF_Outline;
         stdcall external LIBHPDF_DLL;


function HPDF_Outline_SetOpened (outline: HPDF_Outline; opened: HPDF_BOOL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Outline_SetDestination (outline: HPDF_Outline;
        dst: HPDF_Destination): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_CreateDestination (page: HPDF_Page): HPDF_Destination;
         stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetXYZ (dst: HPDF_Destination; left: HPDF_REAL;
        top: HPDF_REAL; zoom: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetFit (dst: HPDF_Destination): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetFitH (dst: HPDF_Destination; top: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetFitV (dst: HPDF_Destination; left: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetFitR (dst: HPDF_Destination; left: HPDF_REAL;
        bottom: HPDF_REAL; right: HPDF_REAL; top: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetFitB (dst: HPDF_Destination): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetFitBH (dst: HPDF_Destination; top: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Destination_SetFitBV (dst: HPDF_Destination; left: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_GetEncoder (pdf: HPDF_Doc; const encoding_name: HPDF_PCHAR):
        HPDF_Encoder; stdcall external LIBHPDF_DLL;


function HPDF_GetCurrentEncoder (pdf: HPDF_Doc): HPDF_Encoder;
         stdcall external LIBHPDF_DLL;


function HPDF_SetCurrentEncoder (pdf: HPDF_Doc; const encoding_name: HPDF_PCHAR):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Encoder_GetType (encoder: HPDF_Encoder): THPDF_EncoderType;
         stdcall external LIBHPDF_DLL;


function HPDF_Encoder_GetByteType (encoder: HPDF_Encoder; const text: HPDF_PCHAR;
        index: HPDF_UINT): THPDF_ByteType; stdcall external LIBHPDF_DLL;


function HPDF_Encoder_GetUnicode (encoder: HPDF_Encoder; code: HPDF_UINT16):
        HPDF_UNICODE; stdcall external LIBHPDF_DLL;


function HPDF_Encoder_GetWritingMode (encoder: HPDF_Encoder): THPDF_EncoderType;
         stdcall external LIBHPDF_DLL;


function HPDF_UseJPEncodings (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_UseKREncodings (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_UseCNSEncodings (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_UseCNTEncodings (pdf: HPDF_Doc): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_CreateTextAnnot (page: HPDF_Page; rect: THPDF_Rect;
        const text: HPDF_PCHAR; encoder: HPDF_Encoder): HPDF_Annotation;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_CreateLinkAnnot (page: HPDF_Page; rect: THPDF_Rect;
        dst: HPDF_Destination): HPDF_Annotation; stdcall external LIBHPDF_DLL;


function HPDF_Page_CreateURILinkAnnot (page: HPDF_Page; rect: THPDF_Rect;
        const uri: HPDF_PCHAR): HPDF_Annotation; stdcall external LIBHPDF_DLL;


function HPDF_LinkAnnot_SetHighlightMode (annot: HPDF_Annotation;
        mode: THPDF_AnnotHighlightMode): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_LinkAnnot_SetBorderStyle (annot: HPDF_Annotation; width: HPDF_REAL;
        dash_on: HPDF_UINT16; dash_off: HPDF_UINT16): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_TextAnnot_SetIcon (annot: HPDF_Annotation; icon: THPDF_AnnotIcon):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_TextAnnot_SetOpened (annot: HPDF_Annotation; opened: HPDF_BOOL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_LoadPngImageFromFile (pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; stdcall external LIBHPDF_DLL;


function HPDF_LoadPngImageFromFile2 (pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; stdcall external LIBHPDF_DLL;


function HPDF_LoadJpegImageFromFile (pdf: HPDF_Doc; filename: HPDF_PCHAR):
        HPDF_Image; stdcall external LIBHPDF_DLL;


function HPDF_LoadRawImageFromFile (pdf: HPDF_Doc; filename: HPDF_PCHAR;
        width: HPDF_UINT; height: HPDF_UINT; color_space: THPDF_ColorSpace):
        HPDF_Image; stdcall external LIBHPDF_DLL;


function HPDF_LoadRawImageFromMem (pdf: HPDF_Doc; const buf: HPDF_PBYTE;
        width: HPDF_UINT; height: HPDF_UINT; color_space: THPDF_ColorSpace;
        bits_per_component: HPDF_UINT): HPDF_Image; stdcall external LIBHPDF_DLL;


function HPDF_Image_GetSize2 (image: HPDF_Image; size: PHPDF_Point): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Image_GetSize (image: HPDF_Image): THPDF_Point;


function HPDF_Image_GetWidth (image: HPDF_Image): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_Image_GetHeight (image: HPDF_Image): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_Image_GetBitsPerComponent (image: HPDF_Image): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_Image_GetColorSpace (image: HPDF_Image): HPDF_PCHAR;
         stdcall external LIBHPDF_DLL;


function HPDF_Image_SetColorMask (image: HPDF_Image; rmin: HPDF_UINT;
        rmax: HPDF_UINT; gmin: HPDF_UINT; gmax: HPDF_UINT; bmin: HPDF_UINT;
        bmax: HPDF_UINT): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Image_SetMaskImage (image: HPDF_Image; mask_image: HPDF_Image):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_SetInfoAttr (pdf: HPDF_Doc; info_type: THPDF_InfoType;
        const value: HPDF_PCHAR): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_GetInfoAttr (pdf: HPDF_Doc; info_type: THPDF_InfoType): HPDF_PCHAR;
         stdcall external LIBHPDF_DLL;


function HPDF_SetInfoDateAttr (pdf: HPDF_Doc; info_type: THPDF_InfoType; value: THPDF_Date):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_SetPassword (pdf: HPDF_Doc; const owner_passwd: HPDF_PCHAR;
        const user_passwd: HPDF_PCHAR): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_SetPermission (pdf: HPDF_Doc; permission: HPDF_UINT): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_SetEncryptionMode (pdf: HPDF_Doc; mode: THPDF_EncryptMode;
        key_len: HPDF_UINT): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_SetCompressionMode (pdf: HPDF_Doc; mode: HPDF_UINT): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_TextWidth (page: HPDF_Page; const text: HPDF_PCHAR): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_MeasureText (page: HPDF_Page; const text: HPDF_PCHAR;
        width: HPDF_REAL; wordwrap: HPDF_BOOL; real_width: HPDF_PREAL): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetWidth (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetHeight (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetGMode (page: HPDF_Page): HPDF_UINT16;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetCurrentPos2 (page: HPDF_Page; pos: PHPDF_Point): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;

function HPDF_Page_GetCurrentPos (page: HPDF_Page): THPDF_Point;


function HPDF_Page_GetCurrentTextPos2 (page: HPDF_Page; pos: PHPDF_Point): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;

function HPDF_Page_GetCurrentTextPos (page: HPDF_Page): THPDF_Point;


function HPDF_Page_GetCurrentFont (page: HPDF_Page): HPDF_Font;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetFontName (font: HPDF_Font): HPDF_PCHAR;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetEncodingName (font: HPDF_Font): HPDF_PCHAR;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetUnicodeWidth (font: HPDF_Font; code: HPDF_UNICODE): HPDF_INT;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetBBox (font: HPDF_Font): THPDF_Rect;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetAscent (font: HPDF_Font): HPDF_INT;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetDescent (font: HPDF_Font): HPDF_INT;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetXHeight (font: HPDF_Font): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_GetCapHeight (font: HPDF_Font): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_TextWidth  (font: HPDF_Font; const text: PChar; len: HPDF_UINT): THPDF_TextWidth;
         stdcall external LIBHPDF_DLL;


function HPDF_Font_MeasureText (font: HPDF_Font; const text: PChar; len: HPDF_UINT;
         width: HPDF_REAL; font_size: HPDF_REAL; char_space: HPDF_REAL; 
         word_space: HPDF_REAL; wordwrap: HPDF_BOOL; real_width: HPDF_PREAL) : HPDF_UINT;
         stdcall external LIBHPDF_DLL;

function HPDF_CreateExtGState  (pdf: HPDF_Doc) : HPDF_ExtGState;
         stdcall external LIBHPDF_DLL;


function HPDF_ExtGState_SetAlphaStroke  (ext_gstate: HPDF_ExtGState; 
         value: HPDF_REAL) : HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_ExtGState_SetAlphaFill  (ext_gstate: HPDF_ExtGState; 
         value: HPDF_REAL) : HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_ExtGState_SetBlendMode  (ext_gstate: HPDF_ExtGState; 
         mode: THPDF_BlendMode) : HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_GetCurrentFontSize (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetTransMatrix (page: HPDF_Page): THPDF_TransMatrix;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetLineWidth (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetLineCap (page: HPDF_Page): THPDF_LineCap;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetLineJoin (page: HPDF_Page): THPDF_LineJoin;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetMiterLimit (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetDash (page: HPDF_Page): THPDF_DashMode;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetFlat (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetCharSpace (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetWordSpace (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetHorizontalScalling (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetTextLeading (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetTextRenderingMode (page: HPDF_Page): THPDF_TextRenderingMode;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetTextRaise (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetRGBFill (page: HPDF_Page): THPDF_RGBColor;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetRGBStroke (page: HPDF_Page): THPDF_RGBColor;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetCMYKFill (page: HPDF_Page): THPDF_CMYKColor;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetCMYKStroke (page: HPDF_Page): THPDF_CMYKColor;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetGrayFill (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetGrayStroke (page: HPDF_Page): HPDF_REAL;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetStrokingColorSpace (page: HPDF_Page): THPDF_ColorSpace;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetFillingColorSpace (page: HPDF_Page): THPDF_ColorSpace;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetTextMatrix (page: HPDF_Page): THPDF_TransMatrix;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GetGStateDepth (page: HPDF_Page): HPDF_UINT;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetLineWidth (page: HPDF_Page; line_width: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetLineCap (page: HPDF_Page; line_cap: THPDF_LineCap):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetLineJoin (page: HPDF_Page; line_join: THPDF_LineJoin):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetMiterLimit (page: HPDF_Page; miter_limit: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetDash (page: HPDF_Page; ptn: HPDF_PUINT16; num_param: HPDF_UINT;
        phase: HPDF_UINT): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetFlat (page: HPDF_Page; flatness: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetExtGState (page: HPDF_Page; ext_gstate: HPDF_ExtGState): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GSave (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_GRestore (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Concat (page: HPDF_Page; a: HPDF_REAL; b: HPDF_REAL; c: HPDF_REAL;
        d: HPDF_REAL; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_MoveTo (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_LineTo (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_CurveTo (page: HPDF_Page; x1: HPDF_REAL; y1: HPDF_REAL;
        x2: HPDF_REAL; y2: HPDF_REAL; x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_CurveTo2 (page: HPDF_Page; x2: HPDF_REAL; y2: HPDF_REAL;
        x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_CurveTo3 (page: HPDF_Page; x1: HPDF_REAL; y1: HPDF_REAL;
        x3: HPDF_REAL; y3: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_ClosePath (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Rectangle (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        width: HPDF_REAL; height: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Stroke (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_ClosePathStroke (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Fill (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Eofill (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_FillStroke (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_EofillStroke (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_ClosePathFillStroke (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_ClosePathEofillStroke (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_EndPath (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Clip (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Eoclip (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_BeginText (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_EndText (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetCharSpace (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetWordSpace (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetHorizontalScalling (page: HPDF_Page; value: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetTextLeading (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetFontAndSize (page: HPDF_Page; font: HPDF_Font;
        size: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetTextRenderingMode (page: HPDF_Page;
        mode: THPDF_TextRenderingMode): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetTextRaise (page: HPDF_Page; value: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_MoveTextPos (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_MoveTextPos2 (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetTextMatrix (page: HPDF_Page; a: HPDF_REAL; b: HPDF_REAL; 
        c: HPDF_REAL; d: HPDF_REAL; x: HPDF_REAL; y: HPDF_REAL):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_MoveToNextLine (page: HPDF_Page): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_ShowText (page: HPDF_Page; const text: HPDF_PCHAR): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_ShowTextNextLine (page: HPDF_Page; const text: HPDF_PCHAR):
        HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_ShowTextNextLineEx (page: HPDF_Page; word_space: HPDF_REAL;
        char_space: HPDF_REAL; const text: HPDF_PCHAR): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetGrayFill (page: HPDF_Page; gray: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetGrayStroke (page: HPDF_Page; gray: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetRGBFill (page: HPDF_Page; r: HPDF_REAL; g: HPDF_REAL;
        b: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetRGBStroke (page: HPDF_Page; r: HPDF_REAL; g: HPDF_REAL;
        b: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetCMYKFill (page: HPDF_Page; c: HPDF_REAL; m: HPDF_REAL;
        y: HPDF_REAL; k: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_SetCMYKStroke (page: HPDF_Page; c: HPDF_REAL; m: HPDF_REAL;
        y: HPDF_REAL; k: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_ExecuteXObject (page: HPDF_Page; obj: HPDF_XObject): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_DrawImage (page: HPDF_Page; image: HPDF_Image; x: HPDF_REAL;
        y: HPDF_REAL; width: HPDF_REAL; height: HPDF_REAL): HPDF_STATUS;
         stdcall external LIBHPDF_DLL;


function HPDF_Page_Circle (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        ray: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_Arc (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL; ray: HPDF_REAL;
        ang1: HPDF_REAL; ang2: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;

function HPDF_Page_Ellipse (page: HPDF_Page; x: HPDF_REAL; y: HPDF_REAL;
        xray: HPDF_REAL; yray: HPDF_REAL): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_TextOut (page: HPDF_Page; xpos: HPDF_REAL; ypos: HPDF_REAL;
         const text: HPDF_PCHAR): HPDF_STATUS; stdcall external LIBHPDF_DLL;


function HPDF_Page_TextRect  (page: HPDF_Page; left: HPDF_REAL; top: HPDF_REAL;
        right: HPDF_REAL; bottom: HPDF_REAL; const text: HPDF_PCHAR; 
        align: THPDF_TextAlignment; len: HPDF_PUINT): HPDF_STATUS; 
         stdcall external LIBHPDF_DLL;


function HPDF_Page_SetSlideShow  (page: HPDF_Page; sstype: THPDF_TransitionStyle; 
        disp_time: HPDF_REAL; trans_time: HPDF_REAL): HPDF_STATUS; 
         stdcall external LIBHPDF_DLL;

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


end.

