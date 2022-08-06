''
''
'' hpdf -- header translated with help of SWIG FB wrapper
''
'' NOTICE: This file is part of the FreeBASIC Compiler package and can't
''         be included in other distributions without authorization.
''
''
#ifndef __hpdf_bi__
#define __hpdf_bi__

#inclib "hpdf"  


'extern "c" 
declare function HPDF_GetVersion cdecl alias "HPDF_GetVersion" () as zstring ptr
declare function HPDF_NewEx cdecl alias "HPDF_NewEx" (byval user_error_fn as HPDF_Error_Handler, byval user_alloc_fn as HPDF_Alloc_Func, byval user_free_fn as HPDF_Free_Func, byval mem_pool_buf_size as HPDF_UINT, byval user_data as any ptr) as HPDF_Doc
declare function HPDF_New cdecl alias "HPDF_New" (byval user_error_fn as HPDF_Error_Handler, byval user_data as any ptr) as HPDF_Doc
declare function HPDF_SetErrorHandler cdecl alias "HPDF_SetErrorHandler" (byval pdf as HPDF_Doc, byval user_error_fn as HPDF_Error_Handler) as HPDF_STATUS
declare sub HPDF_Free cdecl alias "HPDF_Free" (byval pdf as HPDF_Doc)
declare function HPDF_NewDoc cdecl alias "HPDF_NewDoc" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare sub HPDF_FreeDoc cdecl alias "HPDF_FreeDoc" (byval pdf as HPDF_Doc)
declare function HPDF_HasDoc cdecl alias "HPDF_HasDoc" (byval pdf as HPDF_Doc) as HPDF_BOOL
declare sub HPDF_FreeDocAll cdecl alias "HPDF_FreeDocAll" (byval pdf as HPDF_Doc)
declare function HPDF_SaveToStream cdecl alias "HPDF_SaveToStream" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_GetStreamSize cdecl alias "HPDF_GetStreamSize" (byval pdf as HPDF_Doc) as HPDF_UINT32
declare function HPDF_ReadFromStream cdecl alias "HPDF_ReadFromStream" (byval pdf as HPDF_Doc, byval buf as HPDF_BYTE ptr, byval size as HPDF_UINT32 ptr) as HPDF_STATUS
declare function HPDF_ResetStream cdecl alias "HPDF_ResetStream" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_SaveToFile cdecl alias "HPDF_SaveToFile" (byval pdf as HPDF_Doc, byval file_name as zstring ptr) as HPDF_STATUS
declare function HPDF_GetError cdecl alias "HPDF_GetError" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_GetErrorDetail cdecl alias "HPDF_GetErrorDetail" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare sub HPDF_ResetError cdecl alias "HPDF_ResetError" (byval pdf as HPDF_Doc)
declare function HPDF_SetPagesConfiguration cdecl alias "HPDF_SetPagesConfiguration" (byval pdf as HPDF_Doc, byval page_per_pages as HPDF_UINT) as HPDF_STATUS
declare function HPDF_GetPageByIndex cdecl alias "HPDF_GetPageByIndex" (byval pdf as HPDF_Doc, byval index as HPDF_UINT) as HPDF_Page
declare function HPDF_GetPageLayout cdecl alias "HPDF_GetPageLayout" (byval pdf as HPDF_Doc) as HPDF_PageLayout
declare function HPDF_SetPageLayout cdecl alias "HPDF_SetPageLayout" (byval pdf as HPDF_Doc, byval layout as HPDF_PageLayout) as HPDF_STATUS
declare function HPDF_GetPageMode cdecl alias "HPDF_GetPageMode" (byval pdf as HPDF_Doc) as HPDF_PageMode
declare function HPDF_SetPageMode cdecl alias "HPDF_SetPageMode" (byval pdf as HPDF_Doc, byval mode as HPDF_PageMode) as HPDF_STATUS
declare function HPDF_GetViewerPreference cdecl alias "HPDF_GetViewerPreference" (byval pdf as HPDF_Doc) as HPDF_UINT
declare function HPDF_SetViewerPreference cdecl alias "HPDF_SetViewerPreference" (byval pdf as HPDF_Doc, byval value as HPDF_UINT) as HPDF_STATUS
declare function HPDF_SetOpenAction cdecl alias "HPDF_SetOpenAction" (byval pdf as HPDF_Doc, byval open_action as HPDF_Destination) as HPDF_STATUS
declare function HPDF_GetCurrentPage cdecl alias "HPDF_GetCurrentPage" (byval pdf as HPDF_Doc) as HPDF_Page
declare function HPDF_AddPage cdecl alias "HPDF_AddPage" (byval pdf as HPDF_Doc) as HPDF_Page
declare function HPDF_InsertPage cdecl alias "HPDF_InsertPage" (byval pdf as HPDF_Doc, byval page as HPDF_Page) as HPDF_Page
declare function HPDF_Page_SetWidth cdecl alias "HPDF_Page_SetWidth" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetHeight cdecl alias "HPDF_Page_SetHeight" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetSize cdecl alias "HPDF_Page_SetSize" (byval page as HPDF_Page, byval size as HPDF_PageSizes, byval direction as HPDF_PageDirection) as HPDF_STATUS
declare function HPDF_Page_SetRotate cdecl alias "HPDF_Page_SetRotate" (byval page as HPDF_Page, byval angle as HPDF_UINT16) as HPDF_STATUS
declare function HPDF_GetFont cdecl alias "HPDF_GetFont" (byval pdf as HPDF_Doc, byval font_name as zstring ptr, byval encoding_name as zstring ptr) as HPDF_Font
declare function HPDF_LoadType1FontFromFile cdecl alias "HPDF_LoadType1FontFromFile" (byval pdf as HPDF_Doc, byval afm_file_name as zstring ptr, byval data_file_name as zstring ptr) as zstring ptr
declare function HPDF_LoadTTFontFromFile cdecl alias "HPDF_LoadTTFontFromFile" (byval pdf as HPDF_Doc, byval file_name as zstring ptr, byval embedding as HPDF_BOOL) as zstring ptr
declare function HPDF_LoadTTFontFromFile2 cdecl alias "HPDF_LoadTTFontFromFile2" (byval pdf as HPDF_Doc, byval file_name as zstring ptr, byval index as HPDF_UINT, byval embedding as HPDF_BOOL) as zstring ptr
declare function HPDF_AddPageLabel cdecl alias "HPDF_AddPageLabel" (byval pdf as HPDF_Doc, byval page_num as HPDF_UINT, byval style as HPDF_PageNumStyle, byval first_page as HPDF_UINT, byval prefix as zstring ptr) as HPDF_STATUS
declare function HPDF_UseJPFonts cdecl alias "HPDF_UseJPFonts" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_UseKRFonts cdecl alias "HPDF_UseKRFonts" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_UseCNSFonts cdecl alias "HPDF_UseCNSFonts" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_UseCNTFonts cdecl alias "HPDF_UseCNTFonts" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_CreateOutline cdecl alias "HPDF_CreateOutline" (byval pdf as HPDF_Doc, byval parent as HPDF_Outline, byval title as zstring ptr, byval encoder as HPDF_Encoder) as HPDF_Outline
declare function HPDF_Outline_SetOpened cdecl alias "HPDF_Outline_SetOpened" (byval outline as HPDF_Outline, byval opened as HPDF_BOOL) as HPDF_STATUS
declare function HPDF_Outline_SetDestination cdecl alias "HPDF_Outline_SetDestination" (byval outline as HPDF_Outline, byval dst as HPDF_Destination) as HPDF_STATUS
declare function HPDF_Page_CreateDestination cdecl alias "HPDF_Page_CreateDestination" (byval page as HPDF_Page) as HPDF_Destination
declare function HPDF_Destination_SetXYZ cdecl alias "HPDF_Destination_SetXYZ" (byval dst as HPDF_Destination, byval left as HPDF_REAL, byval top as HPDF_REAL, byval zoom as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Destination_SetFit cdecl alias "HPDF_Destination_SetFit" (byval dst as HPDF_Destination) as HPDF_STATUS
declare function HPDF_Destination_SetFitH cdecl alias "HPDF_Destination_SetFitH" (byval dst as HPDF_Destination, byval top as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Destination_SetFitV cdecl alias "HPDF_Destination_SetFitV" (byval dst as HPDF_Destination, byval left as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Destination_SetFitR cdecl alias "HPDF_Destination_SetFitR" (byval dst as HPDF_Destination, byval left as HPDF_REAL, byval bottom as HPDF_REAL, byval right as HPDF_REAL, byval top as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Destination_SetFitB cdecl alias "HPDF_Destination_SetFitB" (byval dst as HPDF_Destination) as HPDF_STATUS
declare function HPDF_Destination_SetFitBH cdecl alias "HPDF_Destination_SetFitBH" (byval dst as HPDF_Destination, byval top as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Destination_SetFitBV cdecl alias "HPDF_Destination_SetFitBV" (byval dst as HPDF_Destination, byval left as HPDF_REAL) as HPDF_STATUS
declare function HPDF_GetEncoder cdecl alias "HPDF_GetEncoder" (byval pdf as HPDF_Doc, byval encoding_name as zstring ptr) as HPDF_Encoder
declare function HPDF_GetCurrentEncoder cdecl alias "HPDF_GetCurrentEncoder" (byval pdf as HPDF_Doc) as HPDF_Encoder
declare function HPDF_SetCurrentEncoder cdecl alias "HPDF_SetCurrentEncoder" (byval pdf as HPDF_Doc, byval encoding_name as zstring ptr) as HPDF_STATUS
declare function HPDF_Encoder_GetType cdecl alias "HPDF_Encoder_GetType" (byval encoder as HPDF_Encoder) as HPDF_EncoderType
declare function HPDF_Encoder_GetByteType cdecl alias "HPDF_Encoder_GetByteType" (byval encoder as HPDF_Encoder, byval text as zstring ptr, byval index as HPDF_UINT) as HPDF_ByteType
declare function HPDF_Encoder_GetUnicode cdecl alias "HPDF_Encoder_GetUnicode" (byval encoder as HPDF_Encoder, byval code as HPDF_UINT16) as HPDF_UNICODE
declare function HPDF_Encoder_GetWritingMode cdecl alias "HPDF_Encoder_GetWritingMode" (byval encoder as HPDF_Encoder) as HPDF_WritingMode
declare function HPDF_UseJPEncodings cdecl alias "HPDF_UseJPEncodings" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_UseKREncodings cdecl alias "HPDF_UseKREncodings" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_UseCNSEncodings cdecl alias "HPDF_UseCNSEncodings" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_UseCNTEncodings cdecl alias "HPDF_UseCNTEncodings" (byval pdf as HPDF_Doc) as HPDF_STATUS
declare function HPDF_Page_CreateTextAnnot cdecl alias "HPDF_Page_CreateTextAnnot" (byval page as HPDF_Page, byval rect as HPDF_Rect, byval text as zstring ptr, byval encoder as HPDF_Encoder) as HPDF_Annotation
declare function HPDF_Page_CreateLinkAnnot cdecl alias "HPDF_Page_CreateLinkAnnot" (byval page as HPDF_Page, byval rect as HPDF_Rect, byval dst as HPDF_Destination) as HPDF_Annotation
declare function HPDF_Page_CreateURILinkAnnot cdecl alias "HPDF_Page_CreateURILinkAnnot" (byval page as HPDF_Page, byval rect as HPDF_Rect, byval uri as zstring ptr) as HPDF_Annotation
declare function HPDF_LinkAnnot_SetHighlightMode cdecl alias "HPDF_LinkAnnot_SetHighlightMode" (byval annot as HPDF_Annotation, byval mode as HPDF_AnnotHighlightMode) as HPDF_STATUS
declare function HPDF_LinkAnnot_SetBorderStyle cdecl alias "HPDF_LinkAnnot_SetBorderStyle" (byval annot as HPDF_Annotation, byval width as HPDF_REAL, byval dash_on as HPDF_UINT16, byval dash_off as HPDF_UINT16) as HPDF_STATUS
declare function HPDF_TextAnnot_SetIcon cdecl alias "HPDF_TextAnnot_SetIcon" (byval annot as HPDF_Annotation, byval icon as HPDF_AnnotIcon) as HPDF_STATUS
declare function HPDF_TextAnnot_SetOpened cdecl alias "HPDF_TextAnnot_SetOpened" (byval annot as HPDF_Annotation, byval opened as HPDF_BOOL) as HPDF_STATUS
declare function HPDF_LoadPngImageFromFile cdecl alias "HPDF_LoadPngImageFromFile" (byval pdf as HPDF_Doc, byval filename as zstring ptr) as HPDF_Image
declare function HPDF_LoadPngImageFromFile2 cdecl alias "HPDF_LoadPngImageFromFile2" (byval pdf as HPDF_Doc, byval filename as zstring ptr) as HPDF_Image
declare function HPDF_LoadJpegImageFromFile cdecl alias "HPDF_LoadJpegImageFromFile" (byval pdf as HPDF_Doc, byval filename as zstring ptr) as HPDF_Image
declare function HPDF_LoadRawImageFromFile cdecl alias "HPDF_LoadRawImageFromFile" (byval pdf as HPDF_Doc, byval filename as zstring ptr, byval width as HPDF_UINT, byval height as HPDF_UINT, byval color_space as HPDF_ColorSpace) as HPDF_Image
declare function HPDF_LoadRawImageFromMem cdecl alias "HPDF_LoadRawImageFromMem" (byval pdf as HPDF_Doc, byval buf as HPDF_BYTE ptr, byval width as HPDF_UINT, byval height as HPDF_UINT, byval color_space as HPDF_ColorSpace, byval bits_per_component as HPDF_UINT) as HPDF_Image
declare function HPDF_Image_GetSize cdecl alias "HPDF_Image_GetSize" (byval image as HPDF_Image) as HPDF_Point
declare function HPDF_Image_GetSize2 cdecl alias "HPDF_Image_GetSize2" (byval image as HPDF_Image, byval size as HPDF_Point ptr) as HPDF_STATUS
declare function HPDF_Image_GetWidth cdecl alias "HPDF_Image_GetWidth" (byval image as HPDF_Image) as HPDF_UINT
declare function HPDF_Image_GetHeight cdecl alias "HPDF_Image_GetHeight" (byval image as HPDF_Image) as HPDF_UINT
declare function HPDF_Image_GetBitsPerComponent cdecl alias "HPDF_Image_GetBitsPerComponent" (byval image as HPDF_Image) as HPDF_UINT
declare function HPDF_Image_GetColorSpace cdecl alias "HPDF_Image_GetColorSpace" (byval image as HPDF_Image) as zstring ptr
declare function HPDF_Image_SetColorMask cdecl alias "HPDF_Image_SetColorMask" (byval image as HPDF_Image, byval rmin as HPDF_UINT, byval rmax as HPDF_UINT, byval gmin as HPDF_UINT, byval gmax as HPDF_UINT, byval bmin as HPDF_UINT, byval bmax as HPDF_UINT) as HPDF_STATUS
declare function HPDF_Image_SetMaskImage cdecl alias "HPDF_Image_SetMaskImage" (byval image as HPDF_Image, byval mask_image as HPDF_Image) as HPDF_STATUS
declare function HPDF_SetInfoAttr cdecl alias "HPDF_SetInfoAttr" (byval pdf as HPDF_Doc, byval type as HPDF_InfoType, byval value as zstring ptr) as HPDF_STATUS
declare function HPDF_GetInfoAttr cdecl alias "HPDF_GetInfoAttr" (byval pdf as HPDF_Doc, byval type as HPDF_InfoType) as zstring ptr
declare function HPDF_SetInfoDateAttr cdecl alias "HPDF_SetInfoDateAttr" (byval pdf as HPDF_Doc, byval type as HPDF_InfoType, byval value as HPDF_Date) as HPDF_STATUS
declare function HPDF_SetPassword cdecl alias "HPDF_SetPassword" (byval pdf as HPDF_Doc, byval owner_passwd as zstring ptr, byval user_passwd as zstring ptr) as HPDF_STATUS
declare function HPDF_SetPermission cdecl alias "HPDF_SetPermission" (byval pdf as HPDF_Doc, byval permission as HPDF_UINT) as HPDF_STATUS
declare function HPDF_SetEncryptionMode cdecl alias "HPDF_SetEncryptionMode" (byval pdf as HPDF_Doc, byval mode as HPDF_EncryptMode, byval key_len as HPDF_UINT) as HPDF_STATUS
declare function HPDF_SetCompressionMode cdecl alias "HPDF_SetCompressionMode" (byval pdf as HPDF_Doc, byval mode as HPDF_UINT) as HPDF_STATUS
declare function HPDF_Font_GetFontName cdecl alias "HPDF_Font_GetFontName" (byval font as HPDF_Font) as zstring ptr
declare function HPDF_Font_GetEncodingName cdecl alias "HPDF_Font_GetEncodingName" (byval font as HPDF_Font) as zstring ptr
declare function HPDF_Font_GetUnicodeWidth cdecl alias "HPDF_Font_GetUnicodeWidth" (byval font as HPDF_Font, byval code as HPDF_UNICODE) as HPDF_INT
declare function HPDF_Font_GetBBox cdecl alias "HPDF_Font_GetBBox" (byval font as HPDF_Font) as HPDF_Box
declare function HPDF_Font_GetAscent cdecl alias "HPDF_Font_GetAscent" (byval font as HPDF_Font) as HPDF_INT
declare function HPDF_Font_GetDescent cdecl alias "HPDF_Font_GetDescent" (byval font as HPDF_Font) as HPDF_INT
declare function HPDF_Font_GetXHeight cdecl alias "HPDF_Font_GetXHeight" (byval font as HPDF_Font) as HPDF_UINT
declare function HPDF_Font_GetCapHeight cdecl alias "HPDF_Font_GetCapHeight" (byval font as HPDF_Font) as HPDF_UINT
declare function HPDF_Font_TextWidth cdecl alias "HPDF_Font_TextWidth" (byval font as HPDF_Font, byval text as HPDF_BYTE ptr, byval len as HPDF_UINT) as HPDF_TextWidth
declare function HPDF_Font_MeasureText cdecl alias "HPDF_Font_MeasureText" (byval font as HPDF_Font, byval text as HPDF_BYTE ptr, byval len as HPDF_UINT, byval width as HPDF_REAL, byval font_size as HPDF_REAL, byval char_space as HPDF_REAL, byval word_space as HPDF_REAL, byval wordwrap as HPDF_BOOL, byval real_width as HPDF_REAL ptr) as HPDF_UINT
declare function HPDF_CreateExtGState cdecl alias "HPDF_CreateExtGState" (byval pdf as HPDF_Doc) as HPDF_ExtGState
declare function HPDF_ExtGState_SetAlphaStroke cdecl alias "HPDF_ExtGState_SetAlphaStroke" (byval ext_gstate as HPDF_ExtGState, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_ExtGState_SetAlphaFill cdecl alias "HPDF_ExtGState_SetAlphaFill" (byval ext_gstate as HPDF_ExtGState, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_ExtGState_SetBlendMode cdecl alias "HPDF_ExtGState_SetBlendMode" (byval ext_gstate as HPDF_ExtGState, byval mode as HPDF_BlendMode) as HPDF_STATUS
declare function HPDF_Page_TextWidth cdecl alias "HPDF_Page_TextWidth" (byval page as HPDF_Page, byval text as zstring ptr) as HPDF_REAL
declare function HPDF_Page_MeasureText cdecl alias "HPDF_Page_MeasureText" (byval page as HPDF_Page, byval text as zstring ptr, byval width as HPDF_REAL, byval wordwrap as HPDF_BOOL, byval real_width as HPDF_REAL ptr) as HPDF_UINT
declare function HPDF_Page_GetWidth cdecl alias "HPDF_Page_GetWidth" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetHeight cdecl alias "HPDF_Page_GetHeight" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetGMode cdecl alias "HPDF_Page_GetGMode" (byval page as HPDF_Page) as HPDF_UINT16
declare function HPDF_Page_GetCurrentPos cdecl alias "HPDF_Page_GetCurrentPos" (byval page as HPDF_Page) as HPDF_Point
declare function HPDF_Page_GetCurrentPos2 cdecl alias "HPDF_Page_GetCurrentPos2" (byval page as HPDF_Page, byval pos as HPDF_Point ptr) as HPDF_STATUS
declare function HPDF_Page_GetCurrentTextPos cdecl alias "HPDF_Page_GetCurrentTextPos" (byval page as HPDF_Page) as HPDF_Point
declare function HPDF_Page_GetCurrentTextPos2 cdecl alias "HPDF_Page_GetCurrentTextPos2" (byval page as HPDF_Page, byval pos as HPDF_Point ptr) as HPDF_STATUS
declare function HPDF_Page_GetCurrentFont cdecl alias "HPDF_Page_GetCurrentFont" (byval page as HPDF_Page) as HPDF_Font
declare function HPDF_Page_GetCurrentFontSize cdecl alias "HPDF_Page_GetCurrentFontSize" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetTransMatrix cdecl alias "HPDF_Page_GetTransMatrix" (byval page as HPDF_Page) as HPDF_TransMatrix
declare function HPDF_Page_GetLineWidth cdecl alias "HPDF_Page_GetLineWidth" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetLineCap cdecl alias "HPDF_Page_GetLineCap" (byval page as HPDF_Page) as HPDF_LineCap
declare function HPDF_Page_GetLineJoin cdecl alias "HPDF_Page_GetLineJoin" (byval page as HPDF_Page) as HPDF_LineJoin
declare function HPDF_Page_GetMiterLimit cdecl alias "HPDF_Page_GetMiterLimit" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetDash cdecl alias "HPDF_Page_GetDash" (byval page as HPDF_Page) as HPDF_DashMode
declare function HPDF_Page_GetFlat cdecl alias "HPDF_Page_GetFlat" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetCharSpace cdecl alias "HPDF_Page_GetCharSpace" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetWordSpace cdecl alias "HPDF_Page_GetWordSpace" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetHorizontalScalling cdecl alias "HPDF_Page_GetHorizontalScalling" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetTextLeading cdecl alias "HPDF_Page_GetTextLeading" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetTextRenderingMode cdecl alias "HPDF_Page_GetTextRenderingMode" (byval page as HPDF_Page) as HPDF_TextRenderingMode
declare function HPDF_Page_GetTextRaise cdecl alias "HPDF_Page_GetTextRaise" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetTextRise cdecl alias "HPDF_Page_GetTextRise" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetRGBFill cdecl alias "HPDF_Page_GetRGBFill" (byval page as HPDF_Page) as HPDF_RGBColor
declare function HPDF_Page_GetRGBStroke cdecl alias "HPDF_Page_GetRGBStroke" (byval page as HPDF_Page) as HPDF_RGBColor
declare function HPDF_Page_GetCMYKFill cdecl alias "HPDF_Page_GetCMYKFill" (byval page as HPDF_Page) as HPDF_CMYKColor
declare function HPDF_Page_GetCMYKStroke cdecl alias "HPDF_Page_GetCMYKStroke" (byval page as HPDF_Page) as HPDF_CMYKColor
declare function HPDF_Page_GetGrayFill cdecl alias "HPDF_Page_GetGrayFill" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetGrayStroke cdecl alias "HPDF_Page_GetGrayStroke" (byval page as HPDF_Page) as HPDF_REAL
declare function HPDF_Page_GetStrokingColorSpace cdecl alias "HPDF_Page_GetStrokingColorSpace" (byval page as HPDF_Page) as HPDF_ColorSpace
declare function HPDF_Page_GetFillingColorSpace cdecl alias "HPDF_Page_GetFillingColorSpace" (byval page as HPDF_Page) as HPDF_ColorSpace
declare function HPDF_Page_GetTextMatrix cdecl alias "HPDF_Page_GetTextMatrix" (byval page as HPDF_Page) as HPDF_TransMatrix
declare function HPDF_Page_GetGStateDepth cdecl alias "HPDF_Page_GetGStateDepth" (byval page as HPDF_Page) as HPDF_UINT
declare function HPDF_Page_SetLineWidth cdecl alias "HPDF_Page_SetLineWidth" (byval page as HPDF_Page, byval line_width as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetLineCap cdecl alias "HPDF_Page_SetLineCap" (byval page as HPDF_Page, byval line_cap as HPDF_LineCap) as HPDF_STATUS
declare function HPDF_Page_SetLineJoin cdecl alias "HPDF_Page_SetLineJoin" (byval page as HPDF_Page, byval line_join as HPDF_LineJoin) as HPDF_STATUS
declare function HPDF_Page_SetMiterLimit cdecl alias "HPDF_Page_SetMiterLimit" (byval page as HPDF_Page, byval miter_limit as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetDash cdecl alias "HPDF_Page_SetDash" (byval page as HPDF_Page, byval dash_ptn as HPDF_UINT16 ptr, byval num_param as HPDF_UINT, byval phase as HPDF_UINT) as HPDF_STATUS
declare function HPDF_Page_SetFlat cdecl alias "HPDF_Page_SetFlat" (byval page as HPDF_Page, byval flatness as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetExtGState cdecl alias "HPDF_Page_SetExtGState" (byval page as HPDF_Page, byval ext_gstate as HPDF_ExtGState) as HPDF_STATUS
declare function HPDF_Page_GSave cdecl alias "HPDF_Page_GSave" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_GRestore cdecl alias "HPDF_Page_GRestore" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_Concat cdecl alias "HPDF_Page_Concat" (byval page as HPDF_Page, byval a as HPDF_REAL, byval b as HPDF_REAL, byval c as HPDF_REAL, byval d as HPDF_REAL, byval x as HPDF_REAL, byval y as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_MoveTo cdecl alias "HPDF_Page_MoveTo" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_LineTo cdecl alias "HPDF_Page_LineTo" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_CurveTo cdecl alias "HPDF_Page_CurveTo" (byval page as HPDF_Page, byval x1 as HPDF_REAL, byval y1 as HPDF_REAL, byval x2 as HPDF_REAL, byval y2 as HPDF_REAL, byval x3 as HPDF_REAL, byval y3 as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_CurveTo2 cdecl alias "HPDF_Page_CurveTo2" (byval page as HPDF_Page, byval x2 as HPDF_REAL, byval y2 as HPDF_REAL, byval x3 as HPDF_REAL, byval y3 as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_CurveTo3 cdecl alias "HPDF_Page_CurveTo3" (byval page as HPDF_Page, byval x1 as HPDF_REAL, byval y1 as HPDF_REAL, byval x3 as HPDF_REAL, byval y3 as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_ClosePath cdecl alias "HPDF_Page_ClosePath" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_Rectangle cdecl alias "HPDF_Page_Rectangle" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL, byval width as HPDF_REAL, byval height as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_Stroke cdecl alias "HPDF_Page_Stroke" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_ClosePathStroke cdecl alias "HPDF_Page_ClosePathStroke" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_Fill cdecl alias "HPDF_Page_Fill" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_Eofill cdecl alias "HPDF_Page_Eofill" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_FillStroke cdecl alias "HPDF_Page_FillStroke" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_EofillStroke cdecl alias "HPDF_Page_EofillStroke" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_ClosePathFillStroke cdecl alias "HPDF_Page_ClosePathFillStroke" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_ClosePathEofillStroke cdecl alias "HPDF_Page_ClosePathEofillStroke" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_EndPath cdecl alias "HPDF_Page_EndPath" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_Clip cdecl alias "HPDF_Page_Clip" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_Eoclip cdecl alias "HPDF_Page_Eoclip" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_BeginText cdecl alias "HPDF_Page_BeginText" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_EndText cdecl alias "HPDF_Page_EndText" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_SetCharSpace cdecl alias "HPDF_Page_SetCharSpace" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetWordSpace cdecl alias "HPDF_Page_SetWordSpace" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetHorizontalScalling cdecl alias "HPDF_Page_SetHorizontalScalling" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetTextLeading cdecl alias "HPDF_Page_SetTextLeading" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetFontAndSize cdecl alias "HPDF_Page_SetFontAndSize" (byval page as HPDF_Page, byval font as HPDF_Font, byval size as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetTextRenderingMode cdecl alias "HPDF_Page_SetTextRenderingMode" (byval page as HPDF_Page, byval mode as HPDF_TextRenderingMode) as HPDF_STATUS
declare function HPDF_Page_SetTextRise cdecl alias "HPDF_Page_SetTextRise" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetTextRaise cdecl alias "HPDF_Page_SetTextRaise" (byval page as HPDF_Page, byval value as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_MoveTextPos cdecl alias "HPDF_Page_MoveTextPos" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_MoveTextPos2 cdecl alias "HPDF_Page_MoveTextPos2" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetTextMatrix cdecl alias "HPDF_Page_SetTextMatrix" (byval page as HPDF_Page, byval a as HPDF_REAL, byval b as HPDF_REAL, byval c as HPDF_REAL, byval d as HPDF_REAL, byval x as HPDF_REAL, byval y as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_MoveToNextLine cdecl alias "HPDF_Page_MoveToNextLine" (byval page as HPDF_Page) as HPDF_STATUS
declare function HPDF_Page_ShowText cdecl alias "HPDF_Page_ShowText" (byval page as HPDF_Page, byval text as zstring ptr) as HPDF_STATUS
declare function HPDF_Page_ShowTextNextLine cdecl alias "HPDF_Page_ShowTextNextLine" (byval page as HPDF_Page, byval text as zstring ptr) as HPDF_STATUS
declare function HPDF_Page_ShowTextNextLineEx cdecl alias "HPDF_Page_ShowTextNextLineEx" (byval page as HPDF_Page, byval word_space as HPDF_REAL, byval char_space as HPDF_REAL, byval text as zstring ptr) as HPDF_STATUS
declare function HPDF_Page_SetGrayFill cdecl alias "HPDF_Page_SetGrayFill" (byval page as HPDF_Page, byval gray as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetGrayStroke cdecl alias "HPDF_Page_SetGrayStroke" (byval page as HPDF_Page, byval gray as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetRGBFill cdecl alias "HPDF_Page_SetRGBFill" (byval page as HPDF_Page, byval r as HPDF_REAL, byval g as HPDF_REAL, byval b as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetRGBStroke cdecl alias "HPDF_Page_SetRGBStroke" (byval page as HPDF_Page, byval r as HPDF_REAL, byval g as HPDF_REAL, byval b as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetCMYKFill cdecl alias "HPDF_Page_SetCMYKFill" (byval page as HPDF_Page, byval c as HPDF_REAL, byval m as HPDF_REAL, byval y as HPDF_REAL, byval k as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_SetCMYKStroke cdecl alias "HPDF_Page_SetCMYKStroke" (byval page as HPDF_Page, byval c as HPDF_REAL, byval m as HPDF_REAL, byval y as HPDF_REAL, byval k as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_ExecuteXObject cdecl alias "HPDF_Page_ExecuteXObject" (byval page as HPDF_Page, byval obj as HPDF_XObject) as HPDF_STATUS
declare function HPDF_Page_DrawImage cdecl alias "HPDF_Page_DrawImage" (byval page as HPDF_Page, byval image as HPDF_Image, byval x as HPDF_REAL, byval y as HPDF_REAL, byval width as HPDF_REAL, byval height as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_Circle cdecl alias "HPDF_Page_Circle" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL, byval ray as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_Ellipse cdecl alias "HPDF_Page_Ellipse" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL, byval xray as HPDF_REAL, byval yray as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_Arc cdecl alias "HPDF_Page_Arc" (byval page as HPDF_Page, byval x as HPDF_REAL, byval y as HPDF_REAL, byval ray as HPDF_REAL, byval ang1 as HPDF_REAL, byval ang2 as HPDF_REAL) as HPDF_STATUS
declare function HPDF_Page_TextOut cdecl alias "HPDF_Page_TextOut" (byval page as HPDF_Page, byval xpos as HPDF_REAL, byval ypos as HPDF_REAL, byval text as zstring ptr) as HPDF_STATUS
declare function HPDF_Page_TextRect cdecl alias "HPDF_Page_TextRect" (byval page as HPDF_Page, byval left as HPDF_REAL, byval top as HPDF_REAL, byval right as HPDF_REAL, byval bottom as HPDF_REAL, byval text as zstring ptr, byval align as HPDF_TextAlignment, byval len as HPDF_UINT ptr) as HPDF_STATUS
declare function HPDF_Page_SetSlideShow cdecl alias "HPDF_Page_SetSlideShow" (byval page as HPDF_Page, byval type as HPDF_TransitionStyle, byval disp_time as HPDF_REAL, byval trans_time as HPDF_REAL) as HPDF_STATUS
'end extern
#endif
