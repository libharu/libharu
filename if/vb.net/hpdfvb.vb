'
' << Haru Free PDF Library >> -- hpdfvb.vb
'
' VB.Net wrapper for libhpdf.dll
'
' Copyright (c) 2008 Matthew Underwood <matt@bargolf.net>
'
' Permission to use, copy, modify, distribute and sell this software
' and its documentation for any purpose is hereby granted without fee,
' provided that the above copyright notice appear in all copies and
' that both that copyright notice and this permission notice appear
' in supporting documentation.
' It is provided "as is" without express or implied warranty.
'
'

Imports System
Imports System.Runtime.InteropServices

Namespace HPdf

    Public Enum HPdfPageLayout As Integer
        HPDF_PAGE_LAYOUT_SINGLE = 0
        HPDF_PAGE_LAYOUT_ONE_COLUMN
        HPDF_PAGE_LAYOUT_TWO_CLUMN_LEFT
        HPDF_PAGE_LAYOUT_TWO_CLUMN_RIGHT
        HPDF_PAGE_LAYOUT_EOF
    End Enum
    Public Enum HPdfPageMode As Integer
        HPDF_PAGE_MODE_USE_NONE = 0
        HPDF_PAGE_MODE_USE_OUTLINE
        HPDF_PAGE_MODE_USE_THUMBS
        HPDF_PAGE_MODE_FULL_SCREEN
        HPDF_PAGE_MODE_EOF
    End Enum
    Public Enum HPdfPageSizes As Integer
        HPDF_PAGE_SIZE_LETTER = 0
        HPDF_PAGE_SIZE_LEGAL
        HPDF_PAGE_SIZE_A3
        HPDF_PAGE_SIZE_A4
        HPDF_PAGE_SIZE_A5
        HPDF_PAGE_SIZE_B4
        HPDF_PAGE_SIZE_B5
        HPDF_PAGE_SIZE_EXECUTIVE
        HPDF_PAGE_SIZE_US4x6
        HPDF_PAGE_SIZE_US4x8
        HPDF_PAGE_SIZE_US5x7
        HPDF_PAGE_SIZE_COMM10
        HPDF_PAGE_SIZE_EOF
    End Enum
    Public Enum HPdfPageDirection As Integer
        HPDF_PAGE_PORTRAIT = 0
        HPDF_PAGE_LANDSCAPE
    End Enum
    Public Enum HPdfPageNumStyle As UInt32
        HPDF_PAGE_NUM_STYLE_DECIMAL = 0
        HPDF_PAGE_NUM_STYLE_UPPER_ROMAN
        HPDF_PAGE_NUM_STYLE_LOWER_ROMAN
        HPDF_PAGE_NUM_STYLE_UPPER_LETTERS
        HPDF_PAGE_NUM_STYLE_LOWER_LETTERS
        HPDF_PAGE_NUM_STYLE_EOF
    End Enum
    Public Enum HPdfWritingMode As UInt32
        HPDF_WMODE_HORIZONTAL = 0
        HPDF_WMODE_VERTICAL
        HPDF_WMODE_EOF
    End Enum
    Public Enum HPdfEncoderType As UInt32
        HPDF_ENCODER_TYPE_SINGLE_BYTE = 0
        HPDF_ENCODER_TYPE_DOUBLE_BYTE
        HPDF_ENCODER_TYPE_UNINITIALIZED
        HPDF_ENCODER_UNKNOWN
    End Enum
    Public Enum HPdfByteType As UInt32
        HPDF_BYTE_TYPE_SINGLE = 0
        HPDF_BYTE_TYPE_LEAD
        HPDF_BYTE_TYPE_TRIAL
        HPDF_BYTE_TYPE_UNKNOWN
    End Enum
    Public Enum HPdfAnnotHighlightMode As UInt32
        HPDF_ANNOT_NO_HIGHTLIGHT = 0
        HPDF_ANNOT_INVERT_BOX
        HPDF_ANNOT_INVERT_BORDER
        HPDF_ANNOT_DOWN_APPEARANCE
        HPDF_ANNOT_HIGHTLIGHT_MODE_EOF
    End Enum
    Public Enum HPdfAnnotIcon As UInt32
        HPDF_ANNOT_ICON_COMMENT = 0
        HPDF_ANNOT_ICON_KEY
        HPDF_ANNOT_ICON_NOTE
        HPDF_ANNOT_ICON_HELP
        HPDF_ANNOT_ICON_NEW_PARAGRAPH
        HPDF_ANNOT_ICON_PARAGRAPH
        HPDF_ANNOT_ICON_INSERT
        HPDF_ANNOT_ICON_EOF
    End Enum
    Public Enum HPdfColorSpace As UInt32
        HPDF_CS_DEVICE_GRAY = 0
        HPDF_CS_DEVICE_RGB
        HPDF_CS_DEVICE_CMYK
        HPDF_CS_CAL_GRAY
        HPDF_CS_CAL_RGB
        HPDF_CS_LAB
        HPDF_CS_ICC_BASED
        HPDF_CS_SEPARATION
        HPDF_CS_DEVICE_N
        HPDF_CS_INDEXED
        HPDF_CS_PATTERN
        HPDF_CS_EOF
    End Enum
    Public Enum HPdfInfoType As UInt32
        ' date-time type parameters
        HPDF_INFO_CREATION_DATE = 0
        HPDF_INFO_MOD_DATE = 1

        ' string type parameters
        HPDF_INFO_AUTHOR = 2
        HPDF_INFO_CREATOR = 3
        HPDF_INFO_PRODUCER = 4
        HPDF_INFO_TITLE = 5
        HPDF_INFO_SUBJECT = 6
        HPDF_INFO_KEYWORDS = 7
        HPDF_INFO_EOF = 8
    End Enum
    Public Enum HPdfEncryptMode As UInt32
        HPDF_ENCRYPT_R2 = 2
        HPDF_ENCRYPT_R3 = 3
    End Enum
    Public Enum HPdfTextRenderingMode As UInt32
        HPDF_FILL = 0
        HPDF_STROKE = 1
        HPDF_FILL_THEN_STROKE = 2
        HPDF_INVISIBLE = 3
        HPDF_FILL_CLIPPING = 4
        HPDF_STROKE_CLIPPING = 5
        HPDF_FILL_STROKE_CLIPPING = 6
        HPDF_CLIPPING = 7
        HPDF_RENDERING_MODE_EOF = 8
    End Enum
    Public Enum HPdfLineCap As Integer
        HPDF_BUTT_END = 0
        HPDF_ROUND_END = 1
        HPDF_PROJECTING_SCUARE_END = 2
        HPDF_LINECAP_EOF = 3
    End Enum
    Public Enum HPdfLineJoin As Integer
        HPDF_MITER_JOIN = 0
        HPDF_ROUND_JOIN = 1
        HPDF_BEVEL_JOIN = 2
        HPDF_LINEJOIN_EOF = 3
    End Enum
    Public Enum HPdfTextAlignment As Integer
        HPDF_TALIGN_LEFT = 0
        HPDF_TALIGN_RIGHT = 1
        HPDF_TALIGN_CENTER = 2
        HPDF_TALIGN_JUSTIFY = 3
    End Enum
    Public Enum HPdfTransitionStyle As Integer
        HPDF_TS_WIPE_RIGHT = 0
        HPDF_TS_WIPE_UP
        HPDF_TS_WIPE_LEFT
        HPDF_TS_WIPE_DOWN
        HPDF_TS_BARN_DOORS_HORIZONTAL_OUT
        HPDF_TS_BARN_DOORS_HORIZONTAL_IN
        HPDF_TS_BARN_DOORS_VERTICAL_OUT
        HPDF_TS_BARN_DOORS_VERTICAL_IN
        HPDF_TS_BOX_OUT
        HPDF_TS_BOX_IN
        HPDF_TS_BLINDS_HORIZONTAL
        HPDF_TS_BLINDS_VERTICAL
        HPDF_TS_DISSOLVE
        HPDF_TS_GLITTER_RIGHT
        HPDF_TS_GLITTER_DOWN
        HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT
        HPDF_TS_REPLACE
        HPDF_TS_EOF
    End Enum
    Public Enum HPdfBlendMode As Integer
        HPDF_BM_NORMAL = 0
        HPDF_BM_MULTIPLY
        HPDF_BM_SCREEN
        HPDF_BM_OVERLAY
        HPDF_BM_DARKEN
        HPDF_BM_LIGHTEN
        HPDF_BM_COLOR_DODGE
        HPDF_BM_COLOR_BUM
        HPDF_BM_HARD_LIGHT
        HPDF_BM_SOFT_LIGHT
        HPDF_BM_DIFFERENCE
        HPDF_BM_EXCLUSHON
        HPDF_BM_EOF
    End Enum
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfRect
        Public left As Single
        Public bottom As Single
        Public right As Single
        Public top As Single
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfBox
        Public left As Single
        Public bottom As Single
        Public right As Single
        Public top As Single
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfPoint
        Public x As Single
        Public y As Single
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfDate
        Public year As Int32
        Public month As Int32
        Public day As Int32
        Public hour As Int32
        Public minutes As Int32
        Public seconds As Int32
        Public ind As Char
        Public off_hour As Int32
        Public off_minutes As Int32
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfTextWidth
        Public numchars As UInt32
        ' don't use this value (it may be change in the feature). use numspace as alternated. */
        Public numwords As UInt32

        Public width As UInt32
        Public numspace As UInt32
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfTransMatrix
        Public a As Single
        Public b As Single
        Public c As Single
        Public d As Single
        Public x As Single
        Public y As Single
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfDashMode_Internal
        Public ptn0 As UInt16
        Public ptn1 As UInt16
        Public ptn2 As UInt16
        Public ptn3 As UInt16
        Public ptn4 As UInt16
        Public ptn5 As UInt16
        Public ptn6 As UInt16
        Public ptn7 As UInt16
        Public num_ptn As UInt32
        Public phase As UInt32
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfDashMode
        Public ptn As UInt16()
        Public phase As UInt32
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfRGBColor
        Public r As Single
        Public g As Single
        Public b As Single
    End Structure
    <StructLayout(LayoutKind.Sequential)> Public Structure HPdfCMYKColor
        Public c As Single
        Public y As Single
        Public m As Single
        Public k As Single
    End Structure

    ' error handler (call back function)
    Public Delegate Sub HPDF_ErrorHandler(ByVal error_no As uint32, ByVal detail_no As uint32, ByVal user_data As IntPtr)

    Public Class HPdfDoc
        Implements IDisposable

        Public Const HPDF_TRUE As Integer = 1
        Public Const HPDF_FALSE As Integer = 0
        Public Const HPDF_COMP_NONE As UInt32 = 0
        Public Const HPDF_COMP_TEXT As UInt32 = 1
        Public Const HPDF_COMP_IMAGE As UInt32 = 2
        Public Const HPDF_COMP_METADATA As UInt32 = 4
        Public Const HPDF_COMP_ALL As UInt32 = 15

        Public Const HPDF_HIDE_TOOLBAR As UInt32 = 1
        Public Const HPDF_HIDE_MENUBAR As UInt32 = 2
        Public Const HPDF_HIDE_WINDOW_UI As UInt32 = 4
        Public Const HPDF_FIT_WINDOW As UInt32 = 8
        Public Const HPDF_CENTER_WINDOW As UInt32 = 16

        Public Const HPDF_ENABLE_READ As UInt32 = 0
        Public Const HPDF_ENABLE_PRINT As UInt32 = 4
        Public Const HPDF_ENABLE_EDIT_ALL As UInt32 = 8
        Public Const HPDF_ENABLE_COPY As UInt32 = 16
        Public Const HPDF_ENABLE_EDIT As UInt32 = 32

        Private Declare Function HPDF_GetVersion Lib "libhpdf.dll" Alias "HPDF_GetVersion" () As String
        Private Declare Function HPDF_New Lib "libhpdf.dll" Alias "HPDF_New" (ByVal user_error_fn As HPDF_ErrorHandler, ByVal user_data As IntPtr) As IntPtr
        Private Declare Sub HPDF_Free Lib "libhpdf.dll" Alias "HPDF_Free" (ByVal pdf As IntPtr)
        Private Declare Function HPDF_NewDoc Lib "libhpdf.dll" Alias "HPDF_NewDoc" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_FreeDoc Lib "libhpdf.dll" Alias "HPDF_FreeDoc" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_FreeDocAll Lib "libhpdf.dll" Alias "HPDF_FreeDocAll" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_HasDoc Lib "libhpdf.dll" Alias "HPDF_HasDoc" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_SaveToFile Lib "libhpdf.dll" Alias "HPDF_SaveToFile" (ByVal pdf As IntPtr, ByVal file_name As String) As UInt32
        Private Declare Function HPDF_GetError Lib "libhpdf.dll" Alias "HPDF_GetError" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_GetErrorDetail Lib "libhpdf.dll" Alias "HPDF_GetErrorDetail" (ByVal pdf As IntPtr) As UInt32
        Private Declare Sub HPDF_ResetError Lib "libhpdf.dll" Alias "HPDF_ResetError" (ByVal pdf As IntPtr)
        Private Declare Function HPDF_SetPagesConfiguration Lib "libhpdf.dll" Alias "HPDF_SetPagesConfiguration" (ByVal pdf As IntPtr, ByVal page_per_pages As UInt32) As UInt32
        Private Declare Function HPDF_GetPageByIndex Lib "libhpdf.dll" Alias "HPDF_GetPageByIndex" (ByVal pdf As IntPtr, ByVal index As UInt32) As IntPtr
        Private Declare Function HPDF_GetPageLayout Lib "libhpdf.dll" Alias "HPDF_GetPageLayout" (ByVal pdf As IntPtr) As HPdfPageLayout
        Private Declare Function HPDF_SetPageLayout Lib "libhpdf.dll" Alias "HPDF_SetPageLayout" (ByVal pdf As IntPtr, ByVal layout As HPdfPageLayout) As UInt32
        Private Declare Function HPDF_GetPageMode Lib "libhpdf.dll" Alias "HPDF_GetPageMode" (ByVal pdf As IntPtr) As HPdfPageMode
        Private Declare Function HPDF_SetPageMode Lib "libhpdf.dll" Alias "HPDF_SetPageMode" (ByVal pdf As IntPtr, ByVal layout As HPdfPageMode) As UInt32
        Private Declare Function HPDF_SetOpenAction Lib "libhpdf.dll" Alias "HPDF_SetOpenAction" (ByVal pdf As IntPtr, ByVal open_action As IntPtr) As UInt32
        Private Declare Function HPDF_GetViewerPreference Lib "libhpdf.dll" Alias "HPDF_GetViewerPreference" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_SetViewerPreference Lib "libhpdf.dll" Alias "HPDF_SetViewerPreference" (ByVal pdf As IntPtr, ByVal value As UInt32) As UInt32
        Private Declare Function HPDF_GetCurrentPage Lib "libhpdf.dll" Alias "HPDF_GetCurrentPage" (ByVal pdf As IntPtr) As IntPtr
        Private Declare Function HPDF_AddPage Lib "libhpdf.dll" Alias "HPDF_AddPage" (ByVal pdf As IntPtr) As IntPtr
        Private Declare Function HPDF_InsertPage Lib "libhpdf.dll" Alias "HPDF_InsertPage" (ByVal pdf As IntPtr, ByVal page As IntPtr) As IntPtr
        Private Declare Function HPDF_GetFont Lib "libhpdf.dll" Alias "HPDF_GetFont" (ByVal pdf As IntPtr, ByVal font_name As String, ByVal encoding_name As String) As IntPtr
        Private Declare Function HPDF_LoadType1FontFromFile Lib "libhpdf.dll" Alias "HPDF_LoadType1FontFromFile" (ByVal pdf As IntPtr, ByVal afmfilename As String, ByVal pfmfilename As String) As String
        Private Declare Function HPDF_LoadTTFontFromFile Lib "libhpdf.dll" Alias "HPDF_LoadTTFontFromFile" (ByVal pdf As IntPtr, ByVal file_name As String, ByVal embedding As Int32) As String
        Private Declare Function HPDF_LoadTTFontFromFile2 Lib "libhpdf.dll" Alias "HPDF_LoadTTFontFromFile2" (ByVal pdf As IntPtr, ByVal file_name As String, ByVal index As UInt32, ByVal embedding As Int32) As String
        Private Declare Function HPDF_AddPageLabel Lib "libhpdf.dll" Alias "HPDF_AddPageLabel" (ByVal pdf As IntPtr, ByVal page_num As UInt32, ByVal style As HPdfPageNumStyle, ByVal first_page As UInt32, ByVal prefix As UInt32) As IntPtr
        Private Declare Function HPDF_UseJPFonts Lib "libhpdf.dll" Alias "HPDF_UseJPFonts" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_UseKRFonts Lib "libhpdf.dll" Alias "HPDF_UseKRFonts" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_UseCNSFonts Lib "libhpdf.dll" Alias "HPDF_UseCNSFonts" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_UseCNTFonts Lib "libhpdf.dll" Alias "HPDF_UseCNTFonts" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_CreateOutline Lib "libhpdf.dll" Alias "HPDF_CreateOutline" (ByVal pdf As IntPtr, ByVal parent As IntPtr, ByVal title As String, ByVal encoded As IntPtr) As UInt32
        Private Declare Function HPDF_GetEncoder Lib "libhpdf.dll" Alias "HPDF_GetEncoder" (ByVal pdf As IntPtr, ByVal encoding_name As String) As IntPtr
        Private Declare Function HPDF_GetCurrentEncoder Lib "libhpdf.dll" Alias "HPDF_GetCurrentEncoder" (ByVal pdf As IntPtr) As IntPtr
        Private Declare Function HPDF_SetCurrentEncoder Lib "libhpdf.dll" Alias "HPDF_SetCurrentEncoder" (ByVal pdf As IntPtr, ByVal encoding_name As String) As UInt32
        Private Declare Function HPDF_UseJPEncodings Lib "libhpdf.dll" Alias "HPDF_UseJPEncodings" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_UseKREncodings Lib "libhpdf.dll" Alias "HPDF_UseKREncodings" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_UseCNSEncodings Lib "libhpdf.dll" Alias "HPDF_UseCNSEncodings" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_UseCNTEncodings Lib "libhpdf.dll" Alias "HPDF_UseCNTEncodings" (ByVal pdf As IntPtr) As UInt32
        Private Declare Function HPDF_LoadPngImageFromFile Lib "libhpdf.dll" Alias "HPDF_LoadPngImageFromFile" (ByVal pdf As IntPtr, ByVal filename As String) As IntPtr
        Private Declare Function HPDF_LoadPngImageFromFile2 Lib "libhpdf.dll" Alias "HPDF_LoadPngImageFromFile2" (ByVal pdf As IntPtr, ByVal filename As String) As IntPtr
        Private Declare Function HPDF_LoadJpegImageFromFile Lib "libhpdf.dll" Alias "HPDF_LoadJpegImageFromFile" (ByVal pdf As IntPtr, ByVal filename As String) As IntPtr
        Private Declare Function HPDF_LoadRawImageFromFile Lib "libhpdf.dll" Alias "HPDF_LoadRawImageFromFile" (ByVal pdf As IntPtr, ByVal filename As String, ByVal width As UInt32, ByVal height As UInt32, ByVal color_space As HPdfColorSpace) As IntPtr
        Private Declare Function HPDF_LoadRawImageFromMem Lib "libhpdf.dll" Alias "HPDF_LoadRawImageFromMem" (ByVal pdf As IntPtr, ByVal data As Byte(), ByVal width As UInt32, ByVal height As UInt32, ByVal color_space As HPdfColorSpace, ByVal bits_per_component As UInt32) As IntPtr
        Private Declare Function HPDF_SetInfoAttr Lib "libhpdf.dll" Alias "HPDF_SetInfoAttr" (ByVal pdf As IntPtr, ByVal type As HPdfInfoType, ByVal value As String) As UInt32
        Private Declare Function HPDF_SetInfoDateAttr Lib "libhpdf.dll" Alias "HPDF_SetInfoDateAttr" (ByVal pdf As IntPtr, ByVal type As HPdfInfoType, ByVal value As HPdfDate) As UInt32
        Private Declare Function HPDF_GetInfoAttr Lib "libhpdf.dll" Alias "HPDF_GetInfoAttr" (ByVal pdf As IntPtr, ByVal type As HPdfInfoType) As String
        Private Declare Function HPDF_SetPassword Lib "libhpdf.dll" Alias "HPDF_SetPassword" (ByVal pdf As IntPtr, ByVal owner_passwd As String, ByVal user_passwd As String) As UInt32
        Private Declare Function HPDF_SetPermission Lib "libhpdf.dll" Alias "HPDF_SetPermission" (ByVal pdf As IntPtr, ByVal permission As UInt32) As UInt32
        Private Declare Function HPDF_SetEncryptionMode Lib "libhpdf.dll" Alias "HPDF_SetEncryptionMode" (ByVal pdf As IntPtr, ByVal mode As HPdfEncryptMode, ByVal key_len As UInt32) As UInt32
        Private Declare Function HPDF_SetCompressionMode Lib "libhpdf.dll" Alias "HPDF_SetCompressionMode" (ByVal pdf As IntPtr, ByVal mode As UInt32) As UInt32
        Private Declare Function HPDF_CreateExtGState Lib "libhpdf.dll" Alias "HPDF_CreateExtGState" (ByVal pdf As IntPtr) As IntPtr

        Private hpdf As IntPtr

        Public Sub New()
            Dim error_handler As HPDF_ErrorHandler = New HPDF_ErrorHandler(AddressOf ErrorProc)
            hpdf = HPDF_New(error_handler, IntPtr.Zero)
            If (hpdf = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfDoc object.")
            End If
        End Sub

        Public Sub Dispose() Implements IDisposable.Dispose
            If (hpdf <> IntPtr.Zero) Then
                HPDF_Free(hpdf)
            End If

            hpdf = IntPtr.Zero
        End Sub

        Public Shared Function HPdfGetVersion() As String
            Return HPDF_GetVersion()
        End Function

        Public Shared Sub ErrorProc(ByVal error_no As UInt32, ByVal detail_no As UInt32, ByVal user_data As IntPtr)
            Dim s As String = "error-code=0x" & error_no.ToString("X") & " detail-code=" & detail_no
            Throw New Exception(s)
        End Sub

        Public Sub NewDoc()
            HPDF_NewDoc(hpdf)
        End Sub

        Public Sub FreeDoc()
            HPDF_FreeDoc(hpdf)
        End Sub

        Public Sub FreeDocAll()
            HPDF_FreeDocAll(hpdf)
        End Sub

        Public Function HasDoc() As Boolean
            Return (HPDF_HasDoc(hpdf) <> 0)
        End Function

        Public Sub SaveToFile(ByVal file_name As String)
            HPDF_SaveToFile(hpdf, file_name)
        End Sub

        Public Function GetError() As UInt32
            Return HPDF_GetError(hpdf)
        End Function

        Public Function GetErrorDetail() As UInt32
            Return HPDF_GetErrorDetail(hpdf)
        End Function

        Public Sub ResetError()
            HPDF_ResetError(hpdf)
        End Sub

        Public Sub SetPagesConfiguration(ByVal page_per_pages As UInt32)
            HPDF_SetPagesConfiguration(hpdf, page_per_pages)
        End Sub

        Public Function GetPageByIndex(ByVal index As UInt32) As HPdfPage
            Dim hpage As IntPtr = HPDF_GetPageByIndex(hpdf, index)
            Return New HPdfPage(hpage)
        End Function

        Public Function GetPageLayout() As HPdfPageLayout
            Return HPDF_GetPageLayout(hpdf)
        End Function

        Public Sub SetPageLayout(ByRef layout As HPdfPageLayout)
            HPDF_SetPageLayout(hpdf, layout)
        End Sub

        Public Function GetPageMode() As HPdfPageMode
            Return HPDF_GetPageMode(hpdf)
        End Function

        Public Sub SetPageMode(ByRef mode As HPdfPageMode)
            HPDF_SetPageMode(hpdf, mode)
        End Sub

        Public Sub SetOpenAction(ByRef open_action As HPdfDestination)
            HPDF_SetOpenAction(hpdf, open_action.GetHandle())
        End Sub

        Public Function GetViewerPreference() As UInt32
            Return HPDF_GetViewerPreference(hpdf)
        End Function

        Public Sub SetViewerPreference(ByVal value As UInt32)
            HPDF_SetViewerPreference(hpdf, value)
        End Sub

        Public Function GetCurrentPage() As HPdfPage
            Dim hpage As IntPtr = HPDF_GetCurrentPage(hpdf)
            Return New HPdfPage(hpage)
        End Function

        Public Function AddPage() As HPdfPage
            Dim hpage As IntPtr = HPDF_AddPage(hpdf)
            Return New HPdfPage(hpage)
        End Function

        Public Function InsertPage(ByRef page As HPdfPage) As HPdfPage
            Dim hpage As IntPtr = HPDF_InsertPage(hpdf, page.GetHandle())
            Return New HPdfPage(hpage)
        End Function

        Public Function GetFont(ByVal font_name As String, ByVal encoding_name As String) As HPdfFont
            Dim hfont As IntPtr = HPDF_GetFont(hpdf, font_name, encoding_name)
            Return New HPdfFont(hfont)
        End Function

        Public Function LoadType1FontFromFile(ByVal afmfilename As String, ByVal pfmfilename As String) As String
            Dim font_name As String = HPDF_LoadType1FontFromFile(hpdf, afmfilename, pfmfilename)
            Return font_name
        End Function

        Public Function LoadTTFontFromFile(ByVal file_name As String, ByVal embedding As Boolean) As String
            Dim font_name As String
            Dim emb As Integer

            If (embedding) Then
                emb = HPDF_TRUE
            Else
                emb = HPDF_FALSE
            End If

            font_name = HPDF_LoadTTFontFromFile(hpdf, file_name, emb)
            Return font_name
        End Function

        Public Function LoadTTFontFromFile2(ByVal file_name As String, ByVal index As UInt32, ByVal embedding As Boolean) As String
            Dim font_name As String
            Dim emb As Integer

            If (embedding) Then
                emb = HPDF_TRUE
            Else
                emb = HPDF_FALSE
            End If

            font_name = HPDF_LoadTTFontFromFile2(hpdf, file_name, index, emb)
            Return font_name
        End Function

        Public Sub AddPageLabel(ByVal page_num As UInt32, ByVal style As HPdfPageNumStyle, ByVal first_page As UInt32, ByVal prefix As String)
            HPDF_AddPageLabel(hpdf, page_num, style, first_page, prefix)
        End Sub

        Public Function UseJPFonts() As UInt32
            Return HPDF_UseJPFonts(hpdf)
        End Function

        Public Function UseKRFonts() As UInt32
            Return HPDF_UseKRFonts(hpdf)
        End Function

        Public Function UseCNSFonts() As UInt32
            Return HPDF_UseCNSFonts(hpdf)
        End Function

        Public Function UseCNTFonts() As UInt32
            Return HPDF_UseCNTFonts(hpdf)
        End Function

        Public Function CreateOutline(ByRef parent As HPdfOutline, ByVal title As String, ByRef encoder As HPdfEncoder) As HPdfOutline
            Dim hparent As IntPtr
            Dim hencoder As IntPtr
            Dim houtline As IntPtr

            If (encoder Is Nothing) Then
                hencoder = Nothing
            Else
                hencoder = encoder.GetHandle()
            End If

            If (parent Is Nothing) Then
                hparent = Nothing
            Else
                hparent = parent.GetHandle()
            End If

            houtline = HPDF_CreateOutline(hpdf, hparent, title, hencoder)
            Return New HPdfOutline(houtline)
        End Function
        Public Function GetEncoder(ByVal encoding_name As String) As HPdfEncoder
            Dim hencoder As IntPtr = HPDF_GetEncoder(hpdf, encoding_name)

            Return New HPdfEncoder(hencoder)
        End Function

        Public Function GetCurrentEncoder() As HPdfEncoder
            Dim hencoder As IntPtr = HPDF_GetCurrentEncoder(hpdf)

            Return New HPdfEncoder(hencoder)
        End Function

        Public Sub SetCurrentEncoder(ByVal encoding_name As String)
            HPDF_SetCurrentEncoder(hpdf, encoding_name)
        End Sub

        Public Function UseJPEncodings() As UInt32
            Return HPDF_UseJPEncodings(hpdf)
        End Function

        Public Function UseKREncodings() As UInt32
            Return HPDF_UseKREncodings(hpdf)
        End Function

        Public Function UseCNSEncodings() As UInt32
            Return HPDF_UseCNSEncodings(hpdf)
        End Function

        Public Function UseCNTEncodings() As UInt32
            Return HPDF_UseCNTEncodings(hpdf)
        End Function

        Public Function LoadPngImageFromFile(ByVal filename As String) As HPdfImage
            Dim hobj As IntPtr = HPDF_LoadPngImageFromFile(hpdf, filename)

            Return New HPdfImage(hobj)
        End Function

        Public Function LoadPngImageFromFile2(ByVal filename As String) As HPdfImage
            Dim hobj As IntPtr = HPDF_LoadPngImageFromFile2(hpdf, filename)

            Return New HPdfImage(hobj)
        End Function

        Public Function LoadJpegImageFromFile(ByVal filename As String) As HPdfImage
            Dim hobj As IntPtr = HPDF_LoadJpegImageFromFile(hpdf, filename)

            Return New HPdfImage(hobj)
        End Function

        Public Function LoadRawImageFromFile(ByVal filename As String, ByVal width As UInt32, ByVal height As UInt32, ByRef color_space As HPdfColorSpace) As HPdfImage
            Dim hobj As IntPtr = HPDF_LoadRawImageFromFile(hpdf, filename, width, height, color_space)

            Return New HPdfImage(hobj)
        End Function

        Public Function LoadRawImageFromMem(ByVal data As Byte(), ByVal width As Int32, ByVal height As Int32, ByRef color_space As HPdfColorSpace, ByVal bits_per_component As UInt32) As HPdfImage
            If (width * height < data.Length) Then
                Dim s As String = "error-code=0x1030 detail-code=0"
                Throw New Exception(s)
            End If

            Dim hobj As IntPtr = HPDF_LoadRawImageFromMem(hpdf, data, width, height, color_space, bits_per_component)

            Return New HPdfImage(hobj)
        End Function

        Public Sub SetInfoAttr(ByVal type As HPdfInfoType, ByVal value As String)
            HPDF_SetInfoAttr(hpdf, type, value)
        End Sub

        Public Sub SetInfoDateAttr(ByVal type As HPdfInfoType, ByRef value As HPdfDate)
            HPDF_SetInfoDateAttr(hpdf, type, value)
        End Sub

        Public Function GetInfoAttr(ByVal type As HPdfInfoType) As String
            Return HPDF_GetInfoAttr(hpdf, type)
        End Function

        Public Sub SetPassword(ByVal owner_passwd As String, ByVal user_passwd As String)
            HPDF_SetPassword(hpdf, owner_passwd, user_passwd)
        End Sub

        Public Sub SetPermission(ByVal permission As UInt32)
            HPDF_SetPermission(hpdf, permission)
        End Sub

        Public Sub SetEncryptionMode(ByVal mode As HPdfEncryptMode, ByVal key_len As UInt32)
            HPDF_SetEncryptionMode(hpdf, mode, key_len)
        End Sub

        Public Sub SetCompressionMode(ByVal mode As UInt32)
            HPDF_SetCompressionMode(hpdf, mode)
        End Sub

        Public Function CreateExtGState() As HPdfExtGState
            Dim hgstate As IntPtr = HPDF_CreateExtGState(hpdf)

            Return New HPdfExtGState(hgstate)
        End Function
    End Class
    Public Class HPdfPage
        Public Const HPDF_TRUE As Integer = 1
        Public Const HPDF_FALSE As Integer = 0

        Private Declare Function HPDF_Page_SetWidth Lib "libhpdf.dll" Alias "HPDF_Page_SetWidth" (ByVal page As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_Page_SetHeight Lib "libhpdf.dll" Alias "HPDF_Page_SetHeight" (ByVal page As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_Page_SetSize Lib "libhpdf.dll" Alias "HPDF_Page_SetSize" (ByVal page As IntPtr, ByVal size As HPdfPageSizes, ByVal direction As HPdfPageDirection) As UInt32
        Private Declare Function HPDF_Page_SetRotate Lib "libhpdf.dll" Alias "HPDF_Page_SetRotate" (ByVal page As IntPtr, ByVal angle As UInt16) As UInt16
        Private Declare Function HPDF_Page_CreateDestination Lib "libhpdf.dll" Alias "HPDF_Page_CreateDestination" (ByVal page As IntPtr) As IntPtr
        Private Declare Function HPDF_Page_CreateTextAnnot Lib "libhpdf.dll" Alias "HPDF_Page_CreateTextAnnot" (ByVal page As IntPtr, ByVal rect As HPdfRect, ByVal text As String, ByVal encoder As IntPtr) As IntPtr
        Private Declare Function HPDF_Page_CreateLinkAnnot Lib "libhpdf.dll" Alias "HPDF_Page_CreateLinkAnnot" (ByVal page As IntPtr, ByVal rect As HPdfRect, ByVal dst As IntPtr) As IntPtr
        Private Declare Function HPDF_Page_CreateURILinkAnnot Lib "libhpdf.dll" Alias "HPDF_Page_CreateURILinkAnnot" (ByVal page As IntPtr, ByVal rect As HPdfRect, ByVal url As String) As IntPtr
        Private Declare Function HPDF_Page_TextWidth Lib "libhpdf.dll" Alias "HPDF_Page_TextWidth" (ByVal page As IntPtr, ByVal text As String) As Single
        Private Declare Function HPDF_Page_MeasureText Lib "libhpdf.dll" Alias "HPDF_Page_MeasureText" (ByVal page As IntPtr, ByVal text As String, ByVal width As Single, ByVal wordwrap As Int32, ByRef real_width As Single) As UInt32
        Private Declare Function HPDF_Page_GetWidth Lib "libhpdf.dll" Alias "HPDF_Page_GetWidth" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetHeight Lib "libhpdf.dll" Alias "HPDF_Page_GetHeight" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetGMode Lib "libhpdf.dll" Alias "HPDF_Page_GetGMode" (ByVal page As IntPtr) As UInt16
        Private Declare Function HPDF_Page_GetCurrentPos Lib "libhpdf.dll" Alias "HPDF_Page_GetCurrentPos" (ByVal page As IntPtr) As HPdfPoint
        Private Declare Function HPDF_Page_GetCurrentTextPos Lib "libhpdf.dll" Alias "HPDF_Page_GetCurrentTextPos" (ByVal page As IntPtr) As HPdfPoint
        Private Declare Function HPDF_Page_GetCurrentFont Lib "libhpdf.dll" Alias "HPDF_Page_GetCurrentFont" (ByVal page As IntPtr) As IntPtr
        Private Declare Function HPDF_Page_GetCurrentFontSize Lib "libhpdf.dll" Alias "HPDF_Page_GetCurrentFontSize" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetTransMatrix Lib "libhpdf.dll" Alias "HPDF_Page_GetTransMatrix" (ByVal page As IntPtr) As HPdfTransMatrix
        Private Declare Function HPDF_Page_GetLineWidth Lib "libhpdf.dll" Alias "HPDF_Page_GetLineWidth" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetLineCap Lib "libhpdf.dll" Alias "HPDF_Page_GetLineCap" (ByVal page As IntPtr) As HPdfLineCap
        Private Declare Function HPDF_Page_GetLineJoin Lib "libhpdf.dll" Alias "HPDF_Page_GetLineJoin" (ByVal page As IntPtr) As HPdfLineJoin
        Private Declare Function HPDF_Page_GetMiterLimit Lib "libhpdf.dll" Alias "HPDF_Page_GetMiterLimit" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetDash Lib "libhpdf.dll" Alias "HPDF_Page_GetDash" (ByVal page As IntPtr) As HPdfDashMode_Internal
        Private Declare Function HPDF_Page_GetFlat Lib "libhpdf.dll" Alias "HPDF_Page_GetFlat" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetCharSpace Lib "libhpdf.dll" Alias "HPDF_Page_GetCharSpace" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetWordSpace Lib "libhpdf.dll" Alias "HPDF_Page_GetWordSpace" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetHorizontalScalling Lib "libhpdf.dll" Alias "HPDF_Page_GetHorizontalScalling" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetTextLeading Lib "libhpdf.dll" Alias "HPDF_Page_GetTextLeading" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetTextRenderingMode Lib "libhpdf.dll" Alias "HPDF_Page_GetTextRenderingMode" (ByVal page As IntPtr) As HPdfTextRenderingMode
        Private Declare Function HPDF_Page_GetTextRaise Lib "libhpdf.dll" Alias "HPDF_Page_GetTextRaise" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetRGBFill Lib "libhpdf.dll" Alias "HPDF_Page_GetRGBFill" (ByVal page As IntPtr) As HPdfRGBColor
        Private Declare Function HPDF_Page_GetRGBStroke Lib "libhpdf.dll" Alias "HPDF_Page_GetRGBStroke" (ByVal page As IntPtr) As HPdfRGBColor
        Private Declare Function HPDF_Page_GetCMYKFill Lib "libhpdf.dll" Alias "HPDF_Page_GetCMYKFill" (ByVal page As IntPtr) As HPdfCMYKColor
        Private Declare Function HPDF_Page_GetCMYKStroke Lib "libhpdf.dll" Alias "HPDF_Page_GetCMYKStroke" (ByVal page As IntPtr) As HPdfCMYKColor
        Private Declare Function HPDF_Page_GetGrayFill Lib "libhpdf.dll" Alias "HPDF_Page_GetGrayFill" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetGrayStroke Lib "libhpdf.dll" Alias "HPDF_Page_GetGrayStroke" (ByVal page As IntPtr) As Single
        Private Declare Function HPDF_Page_GetStrokingColorSpace Lib "libhpdf.dll" Alias "HPDF_Page_GetStrokingColorSpace" (ByVal page As IntPtr) As HPdfColorSpace
        Private Declare Function HPDF_Page_GetFillingColorSpace Lib "libhpdf.dll" Alias "HPDF_Page_GetFillingColorSpace" (ByVal page As IntPtr) As HPdfColorSpace
        Private Declare Function HPDF_Page_GetTextMatrix Lib "libhpdf.dll" Alias "HPDF_Page_GetTextMatrix" (ByVal page As IntPtr) As HPdfTransMatrix
        Private Declare Function HPDF_Page_GetGStateDepth Lib "libhpdf.dll" Alias "HPDF_Page_GetGStateDepth" (ByVal page As IntPtr) As UInt32

        ' --- General graphics state -----------------------------------------------
        Private Declare Function HPDF_Page_SetLineWidth Lib "libhpdf.dll" Alias "HPDF_Page_SetLineWidth" (ByVal page As IntPtr, ByVal line_width As Single) As UInt32
        Private Declare Function HPDF_Page_SetLineCap Lib "libhpdf.dll" Alias "HPDF_Page_SetLineCap" (ByVal page As IntPtr, ByVal line_cap As HPdfLineCap) As UInt32
        Private Declare Function HPDF_Page_SetLineJoin Lib "libhpdf.dll" Alias "HPDF_Page_SetLineJoin" (ByVal page As IntPtr, ByVal line_join As HPdfLineJoin) As UInt32
        Private Declare Function HPDF_Page_SetMiterLimit Lib "libhpdf.dll" Alias "HPDF_Page_SetMiterLimit" (ByVal page As IntPtr, ByVal miter_limit As Single) As UInt32
        Private Declare Function HPDF_Page_SetDash Lib "libhpdf.dll" Alias "HPDF_Page_SetDash" (ByVal page As IntPtr, ByVal array As UInt16(), ByVal num_param As UInt32, ByVal phase As UInt32) As UInt32
        Private Declare Function HPDF_Page_SetFlat Lib "libhpdf.dll" Alias "HPDF_Page_SetFlat" (ByVal page As IntPtr, ByVal flatness As Single) As UInt32
        Private Declare Function HPDF_Page_SetExtGState Lib "libhpdf.dll" Alias "HPDF_Page_SetExtGState" (ByVal page As IntPtr, ByVal ext_gstate As IntPtr) As UInt32
        Private Declare Function HPDF_Page_GSave Lib "libhpdf.dll" Alias "HPDF_Page_GSave" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_GRestore Lib "libhpdf.dll" Alias "HPDF_Page_GRestore" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_Concat Lib "libhpdf.dll" Alias "HPDF_Page_Concat" (ByVal page As IntPtr, ByVal a As Single, ByVal b As Single, ByVal c As Single, ByVal d As Single, ByVal x As Single, ByVal y As Single) As UInt32
        Private Declare Function HPDF_Page_MoveTo Lib "libhpdf.dll" Alias "HPDF_Page_MoveTo" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single) As UInt32
        Private Declare Function HPDF_Page_LineTo Lib "libhpdf.dll" Alias "HPDF_Page_LineTo" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single) As UInt32
        Private Declare Function HPDF_Page_CurveTo Lib "libhpdf.dll" Alias "HPDF_Page_CurveTo" (ByVal page As IntPtr, ByVal x1 As Single, ByVal y1 As Single, ByVal x2 As Single, ByVal y2 As Single, ByVal x3 As Single, ByVal y3 As Single) As UInt32
        Private Declare Function HPDF_Page_CurveTo2 Lib "libhpdf.dll" Alias "HPDF_Page_CurveTo2" (ByVal page As IntPtr, ByVal x2 As Single, ByVal y2 As Single, ByVal x3 As Single, ByVal y3 As Single) As UInt32
        Private Declare Function HPDF_Page_CurveTo3 Lib "libhpdf.dll" Alias "HPDF_Page_CurveTo3" (ByVal page As IntPtr, ByVal x1 As Single, ByVal y1 As Single, ByVal x3 As Single, ByVal y3 As Single) As UInt32
        Private Declare Function HPDF_Page_ClosePath Lib "libhpdf.dll" Alias "HPDF_Page_ClosePath" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_Rectangle Lib "libhpdf.dll" Alias "HPDF_Page_Rectangle" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single, ByVal width As Single, ByVal height As Single) As UInt32
        Private Declare Function HPDF_Page_Stroke Lib "libhpdf.dll" Alias "HPDF_Page_Stroke" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_ClosePathStroke Lib "libhpdf.dll" Alias "HPDF_Page_ClosePathStroke" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_Fill Lib "libhpdf.dll" Alias "HPDF_Page_Fill" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_Eofill Lib "libhpdf.dll" Alias "HPDF_Page_Eofill" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_FillStroke Lib "libhpdf.dll" Alias "HPDF_Page_FillStroke" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_EofillStroke Lib "libhpdf.dll" Alias "HPDF_Page_EofillStroke" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_ClosePathFillStroke Lib "libhpdf.dll" Alias "HPDF_Page_ClosePathFillStroke" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_ClosePathEofillStroke Lib "libhpdf.dll" Alias "HPDF_Page_ClosePathEofillStroke" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_EndPath Lib "libhpdf.dll" Alias "HPDF_Page_EndPath" (ByVal page As IntPtr) As UInt32

        ' --- Clipping paths operator --------------------------------------------
        Private Declare Function HPDF_Page_Clip Lib "libhpdf.dll" Alias "HPDF_Page_Clip" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_Eoclip Lib "libhpdf.dll" Alias "HPDF_Page_Eoclip" (ByVal page As IntPtr) As UInt32

        ' --- Text object operator -----------------------------------------------
        Private Declare Function HPDF_Page_BeginText Lib "libhpdf.dll" Alias "HPDF_Page_BeginText" (ByVal page As IntPtr) As UInt32
        Private Declare Function HPDF_Page_EndText Lib "libhpdf.dll" Alias "HPDF_Page_EndText" (ByVal page As IntPtr) As UInt32

        ' --- Text state ---------------------------------------------------------
        Private Declare Function HPDF_Page_SetCharSpace Lib "libhpdf.dll" Alias "HPDF_Page_SetCharSpace" (ByVal page As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_Page_SetWordSpace Lib "libhpdf.dll" Alias "HPDF_Page_SetWordSpace" (ByVal page As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_Page_SetHorizontalScalling Lib "libhpdf.dll" Alias "HPDF_Page_SetHorizontalScalling" (ByVal page As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_Page_SetTextLeading Lib "libhpdf.dll" Alias "HPDF_Page_SetTextLeading" (ByVal page As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_Page_SetFontAndSize Lib "libhpdf.dll" Alias "HPDF_Page_SetFontAndSize" (ByVal page As IntPtr, ByVal hfont As IntPtr, ByVal size As Single) As UInt32
        Private Declare Function HPDF_Page_SetTextRenderingMode Lib "libhpdf.dll" Alias "HPDF_Page_SetTextRenderingMode" (ByVal page As IntPtr, ByVal mode As HPdfTextRenderingMode) As UInt32
        Private Declare Function HPDF_Page_SetTextRaise Lib "libhpdf.dll" Alias "HPDF_Page_SetTextRaise" (ByVal page As IntPtr, ByVal value As Single) As UInt32

        ' --- Text positioning ---------------------------------------------------
        Private Declare Function HPDF_Page_MoveTextPos Lib "libhpdf.dll" Alias "HPDF_Page_MoveTextPos" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single) As UInt32
        Private Declare Function HPDF_Page_MoveTextPos2 Lib "libhpdf.dll" Alias "HPDF_Page_MoveTextPos2" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single) As UInt32
        Private Declare Function HPDF_Page_SetTextMatrix Lib "libhpdf.dll" Alias "HPDF_Page_SetTextMatrix" (ByVal page As IntPtr, ByVal a As Single, ByVal b As Single, ByVal c As Single, ByVal d As Single, ByVal x As Single, ByVal y As Single) As UInt32
        Private Declare Function HPDF_Page_MoveToNextLine Lib "libhpdf.dll" Alias "HPDF_Page_MoveToNextLine" (ByVal page As IntPtr) As UInt32

        ' --- Text showing -------------------------------------------------------
        Private Declare Function HPDF_Page_ShowText Lib "libhpdf.dll" Alias "HPDF_Page_ShowText" (ByVal page As IntPtr, ByVal text As String) As UInt32
        Private Declare Function HPDF_Page_ShowTextNextLine Lib "libhpdf.dll" Alias "HPDF_Page_ShowTextNextLine" (ByVal page As IntPtr, ByVal text As String) As UInt32
        Private Declare Function HPDF_Page_ShowTextNextLineEx Lib "libhpdf.dll" Alias "HPDF_Page_ShowTextNextLineEx" (ByVal page As IntPtr, ByVal word_space As Single, ByVal char_space As Single, ByVal text As String) As UInt32

        ' --- Color showing ------------------------------------------------------
        Private Declare Function HPDF_Page_SetGrayFill Lib "libhpdf.dll" Alias "HPDF_Page_SetGrayFill" (ByVal page As IntPtr, ByVal gray As Single) As UInt32
        Private Declare Function HPDF_Page_SetGrayStroke Lib "libhpdf.dll" Alias "HPDF_Page_SetGrayStroke" (ByVal page As IntPtr, ByVal gray As Single) As UInt32
        Private Declare Function HPDF_Page_SetRGBFill Lib "libhpdf.dll" Alias "HPDF_Page_SetRGBFill" (ByVal page As IntPtr, ByVal r As Single, ByVal g As Single, ByVal b As Single) As UInt32
        Private Declare Function HPDF_Page_SetRGBStroke Lib "libhpdf.dll" Alias "HPDF_Page_SetRGBStroke" (ByVal page As IntPtr, ByVal r As Single, ByVal g As Single, ByVal b As Single) As UInt32
        Private Declare Function HPDF_Page_SetCMYKFill Lib "libhpdf.dll" Alias "HPDF_Page_SetCMYKFill" (ByVal page As IntPtr, ByVal c As Single, ByVal m As Single, ByVal y As Single, ByVal k As Single) As UInt32
        Private Declare Function HPDF_Page_SetCMYKStroke Lib "libhpdf.dll" Alias "HPDF_Page_SetCMYKStroke" (ByVal page As IntPtr, ByVal c As Single, ByVal m As Single, ByVal y As Single, ByVal k As Single) As UInt32
        Private Declare Function HPDF_Page_ExecuteXObject Lib "libhpdf.dll" Alias "HPDF_Page_ExecuteXObject" (ByVal page As IntPtr, ByVal obj As IntPtr) As UInt32

        ' ---------------------------------------------------------------------
        Private Declare Function HPDF_Page_DrawImage Lib "libhpdf.dll" Alias "HPDF_Page_DrawImage" (ByVal page As IntPtr, ByVal image As IntPtr, ByVal x As Single, ByVal y As Single, ByVal width As Single, ByVal height As Single) As UInt32
        Private Declare Function HPDF_Page_Circle Lib "libhpdf.dll" Alias "HPDF_Page_Circle" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single, ByVal ray As Single) As UInt32
        Private Declare Function HPDF_Page_Arc Lib "libhpdf.dll" Alias "HPDF_Page_Arc" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single, ByVal ray As Single, ByVal ang1 As Single, ByVal ang2 As Single) As UInt32
        Private Declare Function HPDF_Page_Ellipse Lib "libhpdf.dll" Alias "HPDF_Page_Ellipse" (ByVal page As IntPtr, ByVal x As Single, ByVal y As Single, ByVal xray As Single, ByVal yray As Single) As UInt32
        Private Declare Function HPDF_Page_TextOut Lib "libhpdf.dll" Alias "HPDF_Page_TextOut" (ByVal page As IntPtr, ByVal xpos As Single, ByVal ypos As Single, ByVal text As String) As UInt32
        Private Declare Function HPDF_Page_TextRect Lib "libhpdf.dll" Alias "HPDF_Page_TextRect" (ByVal page As IntPtr, ByVal left As Single, ByVal top As Single, ByVal right As Single, ByVal bottom As Single, ByVal text As String, ByVal align As HPdfTextAlignment, ByRef len As UInt32) As UInt32
        Private Declare Function HPDF_Page_SetSlideShow Lib "libhpdf.dll" Alias "HPDF_Page_SetSlideShow" (ByVal page As IntPtr, ByVal type As HPdfTransitionStyle, ByVal disp_time As Single, ByVal trans_time As Single) As UInt32

        ' handle to an instance of a HPDF_Doc object.
        Private hpage As IntPtr

        Public Sub New(ByVal hpage As IntPtr)
            If (hpage = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfPage object.")
            End If

            Me.hpage = hpage
        End Sub

        Public Sub SetWidth(ByVal value As Single)
            HPDF_Page_SetWidth(hpage, value)
        End Sub

        Public Sub SetHeight(ByVal value As Single)
            HPDF_Page_SetHeight(hpage, value)
        End Sub

        Public Sub SetSize(ByVal size As HPdfPageSizes, ByVal direction As HPdfPageDirection)
            HPDF_Page_SetSize(hpage, size, direction)
        End Sub

        Public Sub SetRotate(ByVal angle As UInt16)
            HPDF_Page_SetRotate(hpage, angle)
        End Sub

        Public Function CreateDestination() As HPdfDestination
            Dim hdest As IntPtr = HPDF_Page_CreateDestination(hpage)
            Return New HPdfDestination(hdest)
        End Function

        Public Function CreateTextAnnot(ByVal rect As HPdfRect, ByVal text As String, ByRef encoder As HPdfEncoder) As HPdfAnnotation
            Dim hannot As IntPtr = HPDF_Page_CreateTextAnnot(hpage, rect, text, encoder.GetHandle())
            Return New HPdfAnnotation(hannot)
        End Function

        Public Function CreateLinkAnnot(ByVal rect As HPdfRect, ByRef dst As HPdfDestination) As HPdfAnnotation
            Dim hannot As IntPtr = HPDF_Page_CreateLinkAnnot(hpage, rect, dst.GetHandle())
            Return New HPdfAnnotation(hannot)
        End Function

        Public Function CreateURILinkAnnot(ByVal rect As HPdfRect, ByVal uri As String) As HPdfAnnotation
            Dim hannot As IntPtr = HPDF_Page_CreateURILinkAnnot(hpage, rect, uri)
            Return New HPdfAnnotation(hannot)
        End Function

        Public Function TextWidth(ByVal text As String) As Single
            Return HPDF_Page_TextWidth(hpage, text)
        End Function

        Public Function MeasureText(ByVal text As String, ByVal width As Single, ByVal wordwrap As Boolean, ByRef real_width As Single) As UInt32
            Dim ww As Int32

            If (wordwrap) Then
                ww = HPDF_TRUE
            Else
                ww = HPDF_FALSE
            End If

            Return HPDF_Page_MeasureText(hpage, text, width, ww, real_width)
        End Function

        Public Function MeasureText(ByVal text As String, ByVal width As Single, ByVal wordwrap As Boolean) As UInt32
            Dim dummy As Single
            Dim ww As Int32

            If (wordwrap) Then
                ww = HPDF_TRUE
            Else
                ww = HPDF_FALSE
            End If

            Return HPDF_Page_MeasureText(hpage, text, width, ww, dummy)
        End Function

        Public Function GetWidth() As Single
            Return HPDF_Page_GetWidth(hpage)
        End Function

        Public Function GetHeight() As Single
            Return HPDF_Page_GetHeight(hpage)
        End Function

        Public Function GetGMode() As UInt16
            Return HPDF_Page_GetGMode(hpage)
        End Function

        Public Function GetCurrentPos() As HPdfPoint
            Return HPDF_Page_GetCurrentPos(hpage)
        End Function

        Public Function GetCurrentTextPos() As HPdfPoint
            Return HPDF_Page_GetCurrentTextPos(hpage)
        End Function

        Public Function GetCurrentFont() As HPdfFont
            Return New HPdfFont(HPDF_Page_GetCurrentFont(hpage))
        End Function

        Public Function GetCurrentFontSize() As Single
            Return HPDF_Page_GetCurrentFontSize(hpage)
        End Function

        Public Function GetTransMatrix() As HPdfTransMatrix
            Return HPDF_Page_GetTransMatrix(hpage)
        End Function

        Public Function GetLineWidth() As Single
            Return HPDF_Page_GetLineWidth(hpage)
        End Function

        Public Function GetLineCap() As HPdfLineCap
            Return HPDF_Page_GetLineCap(hpage)
        End Function

        Public Function GetLineJoin() As HPdfLineJoin
            Return HPDF_Page_GetLineJoin(hpage)
        End Function

        Public Function GetMiterLimit() As Single
            Return HPDF_Page_GetMiterLimit(hpage)
        End Function

        Public Function GetDash() As HPdfDashMode
            Dim mode1 As HPdfDashMode_Internal = HPDF_Page_GetDash(hpage)
            Dim mode2 As HPdfDashMode

            mode2.phase = mode1.phase
            ReDim mode2.ptn(mode1.num_ptn)

            If (mode1.num_ptn >= 1) Then
                mode2.ptn(0) = mode1.ptn0
            End If

            If (mode1.num_ptn >= 2) Then
                mode2.ptn(1) = mode1.ptn1
            End If

            If (mode1.num_ptn >= 3) Then
                mode2.ptn(2) = mode1.ptn2
            End If

            If (mode1.num_ptn >= 4) Then
                mode2.ptn(3) = mode1.ptn3
            End If

            If (mode1.num_ptn >= 5) Then
                mode2.ptn(4) = mode1.ptn4
            End If

            If (mode1.num_ptn >= 6) Then
                mode2.ptn(5) = mode1.ptn5
            End If

            If (mode1.num_ptn >= 7) Then
                mode2.ptn(6) = mode1.ptn6
            End If

            If (mode1.num_ptn >= 8) Then
                mode2.ptn(7) = mode1.ptn7
            End If

            Return mode2
        End Function

        Public Function GetFlat() As Single
            Return HPDF_Page_GetFlat(hpage)
        End Function

        Public Function GetCharSpace() As Single
            Return HPDF_Page_GetCharSpace(hpage)
        End Function

        Public Function GetWordSpace() As Single
            Return HPDF_Page_GetWordSpace(hpage)
        End Function

        Public Function GetHorizontalScalling() As Single
            Return HPDF_Page_GetHorizontalScalling(hpage)
        End Function

        Public Function GetTextLeading() As Single
            Return HPDF_Page_GetTextLeading(hpage)
        End Function

        Public Function GetTextRenderingMode() As HPdfTextRenderingMode
            Return HPDF_Page_GetTextRenderingMode(hpage)
        End Function

        Public Function GetTextRaise() As Single
            Return HPDF_Page_GetTextRaise(hpage)
        End Function

        Public Function GetRGBFill() As HPdfRGBColor
            Return HPDF_Page_GetRGBFill(hpage)
        End Function

        Public Function GetRGBStroke() As HPdfRGBColor
            Return HPDF_Page_GetRGBStroke(hpage)
        End Function

        Public Function GetCMYKFill() As HPdfCMYKColor
            Return HPDF_Page_GetCMYKFill(hpage)
        End Function

        Public Function GetCMYKStroke() As HPdfCMYKColor
            Return HPDF_Page_GetCMYKStroke(hpage)
        End Function

        Public Function GetGrayFill() As Single
            Return HPDF_Page_GetGrayFill(hpage)
        End Function

        Public Function GetGrayStroke() As Single
            Return HPDF_Page_GetGrayStroke(hpage)
        End Function

        Public Function GetStrokingColorSpace() As HPdfColorSpace
            Return HPDF_Page_GetStrokingColorSpace(hpage)
        End Function

        Public Function GetFillingColorSpace() As HPdfColorSpace
            Return HPDF_Page_GetFillingColorSpace(hpage)
        End Function

        Public Function GetTextMatrix() As HPdfTransMatrix
            Return HPDF_Page_GetTextMatrix(hpage)
        End Function

        Public Function GetGStateDepth() As UInt32
            Return HPDF_Page_GetGStateDepth(hpage)
        End Function

        Public Sub SetLineWidth(ByVal line_width As Single)
            HPDF_Page_SetLineWidth(hpage, line_width)
        End Sub

        Public Sub SetLineCap(ByVal line_cap As HPdfLineCap)
            HPDF_Page_SetLineCap(hpage, line_cap)
        End Sub

        Public Sub SetLineJoin(ByVal line_join As HPdfLineJoin)
            HPDF_Page_SetLineJoin(hpage, line_join)
        End Sub

        Public Sub SetMiterLimit(ByVal miter_limit As Single)
            HPDF_Page_SetMiterLimit(hpage, miter_limit)
        End Sub

        Public Sub SetDash(ByRef dash_ptn As UInt16(), ByVal phase As UInt32)
            If (dash_ptn Is Nothing) Then
                HPDF_Page_SetDash(hpage, dash_ptn, 0, 0)
                Return
            End If

            Dim len As UInt32 = dash_ptn.Length

            HPDF_Page_SetDash(hpage, dash_ptn, len, phase)

        End Sub

        Public Sub SetFlat(ByVal flatness As Single)
            HPDF_Page_SetFlat(hpage, flatness)
        End Sub

        Public Sub SetExtGState(ByVal gstate As HPdfExtGState)
            HPDF_Page_SetExtGState(hpage, gstate.GetHandle())
        End Sub

        Public Sub GSave()
            HPDF_Page_GSave(hpage)
        End Sub

        Public Sub GRestore()
            HPDF_Page_GRestore(hpage)
        End Sub

        Public Sub Concat(ByVal a As Single, ByVal b As Single, ByVal c As Single, ByVal d As Single, ByVal x As Single, ByVal y As Single)
            HPDF_Page_Concat(hpage, a, b, c, d, x, y)
        End Sub

        Public Sub MoveTo(ByVal x As Single, ByVal y As Single)
            HPDF_Page_MoveTo(hpage, x, y)
        End Sub

        Public Sub LineTo(ByVal x As Single, ByVal y As Single)
            HPDF_Page_LineTo(hpage, x, y)
        End Sub

        Public Sub CurveTo(ByVal x1 As Single, ByVal y1 As Single, ByVal x2 As Single, ByVal y2 As Single, ByVal x3 As Single, ByVal y3 As Single)
            HPDF_Page_CurveTo(hpage, x1, y1, x2, y2, x3, y3)
        End Sub

        Public Sub CurveTo2(ByVal x2 As Single, ByVal y2 As Single, ByVal x3 As Single, ByVal y3 As Single)
            HPDF_Page_CurveTo2(hpage, x2, y2, x3, y3)
        End Sub
        Public Sub CurveTo3(ByVal x1 As Single, ByVal y1 As Single, ByVal x3 As Single, ByVal y3 As Single)
            HPDF_Page_CurveTo2(hpage, x1, y1, x3, y3)
        End Sub

        Public Sub ClosePath()
            HPDF_Page_ClosePath(hpage)
        End Sub

        Public Sub Rectangle(ByVal x As Single, ByVal y As Single, ByVal width As Single, ByVal height As Single)
            HPDF_Page_Rectangle(hpage, x, y, width, height)
        End Sub

        Public Sub Stroke()
            HPDF_Page_Stroke(hpage)
        End Sub

        Public Sub ClosePathStroke()
            HPDF_Page_ClosePathStroke(hpage)
        End Sub

        Public Sub Fill()
            HPDF_Page_Fill(hpage)
        End Sub

        Public Sub Eofill()
            HPDF_Page_Eofill(hpage)
        End Sub

        Public Sub FillStroke()
            HPDF_Page_FillStroke(hpage)
        End Sub

        Public Sub EofillStroke()
            HPDF_Page_EofillStroke(hpage)
        End Sub

        Public Sub ClosePathFillStroke()
            HPDF_Page_ClosePathFillStroke(hpage)
        End Sub

        Public Sub ClosePathEofillStroke()
            HPDF_Page_ClosePathEofillStroke(hpage)
        End Sub

        Public Sub EndPath()
            HPDF_Page_EndPath(hpage)
        End Sub

        Public Sub Clip()
            HPDF_Page_Clip(hpage)
        End Sub

        Public Sub Eoclip()
            HPDF_Page_Eoclip(hpage)
        End Sub

        Public Sub BeginText()
            HPDF_Page_BeginText(hpage)
        End Sub

        Public Sub EndText()
            HPDF_Page_EndText(hpage)
        End Sub

        Public Sub SetCharSpace(ByVal value As Single)
            HPDF_Page_SetCharSpace(hpage, value)
        End Sub

        Public Sub SetWordSpace(ByVal value As Single)
            HPDF_Page_SetWordSpace(hpage, value)
        End Sub

        Public Sub SetHorizontalScalling(ByVal value As Single)
            HPDF_Page_SetHorizontalScalling(hpage, value)
        End Sub

        Public Sub SetTextLeading(ByVal value As Single)
            HPDF_Page_SetTextLeading(hpage, value)
        End Sub

        Public Sub SetFontAndSize(ByRef font As HPdfFont, ByVal size As Single)
            HPDF_Page_SetFontAndSize(hpage, font.GetHandle(), size)
        End Sub

        Public Sub SetTextRenderingMode(ByVal mode As HPdfTextRenderingMode)
            HPDF_Page_SetTextRenderingMode(hpage, mode)
        End Sub

        Public Sub SetTextRaise(ByVal value As Single)
            HPDF_Page_SetTextRaise(hpage, value)
        End Sub

        Public Sub MoveTextPos(ByVal x As Single, ByVal y As Single)
            HPDF_Page_MoveTextPos(hpage, x, y)
        End Sub

        Public Sub MoveTextPos2(ByVal x As Single, ByVal y As Single)
            HPDF_Page_MoveTextPos2(hpage, x, y)
        End Sub

        Public Sub SetTextMatrix(ByVal a As Single, ByVal b As Single, ByVal c As Single, ByVal d As Single, ByVal x As Single, ByVal y As Single)
            HPDF_Page_SetTextMatrix(hpage, a, b, c, d, x, y)
        End Sub

        Public Sub MoveToNextLine()
            HPDF_Page_MoveToNextLine(hpage)
        End Sub

        Public Sub ShowText(ByVal text As String)
            HPDF_Page_ShowText(hpage, text)
        End Sub

        Public Sub ShowTextNextLine(ByVal text As String)
            HPDF_Page_ShowTextNextLine(hpage, text)
        End Sub

        Public Sub ShowTextNextLineEx(ByVal word_space As Single, ByVal char_space As Single, ByVal text As String)
            HPDF_Page_ShowTextNextLineEx(hpage, word_space, char_space, text)
        End Sub

        Public Sub SetGrayFill(ByVal gray As Single)
            HPDF_Page_SetGrayFill(hpage, gray)
        End Sub

        Public Sub SetGrayStroke(ByVal gray As Single)
            HPDF_Page_SetGrayStroke(hpage, gray)
        End Sub

        Public Sub SetRGBFill(ByVal r As Single, ByVal g As Single, ByVal b As Single)
            HPDF_Page_SetRGBFill(hpage, r, g, b)
        End Sub

        Public Sub SetRGBStroke(ByVal r As Single, ByVal g As Single, ByVal b As Single)
            HPDF_Page_SetRGBStroke(hpage, r, g, b)
        End Sub

        Public Sub SetCMYKFill(ByVal c As Single, ByVal m As Single, ByVal y As Single, ByVal k As Single)
            HPDF_Page_SetCMYKFill(hpage, c, m, y, k)
        End Sub

        Public Sub SetCMYKStroke(ByVal c As Single, ByVal m As Single, ByVal y As Single, ByVal k As Single)
            HPDF_Page_SetCMYKStroke(hpage, c, m, y, k)
        End Sub

        Public Sub ExecuteXObject(ByRef xobj As HPdfImage)
            HPDF_Page_ExecuteXObject(hpage, xobj.GetHandle())
        End Sub

        Public Sub DrawImage(ByRef image As HPdfImage, ByVal x As Single, ByVal y As Single, ByVal width As Single, ByVal height As Single)
            HPDF_Page_DrawImage(hpage, image.GetHandle(), x, y, width, height)
        End Sub

        Public Sub Circle(ByVal x As Single, ByVal y As Single, ByVal ray As Single)
            HPDF_Page_Circle(hpage, x, y, ray)
        End Sub

        Public Sub Arc(ByVal x As Single, ByVal y As Single, ByVal ray As Single, ByVal ang1 As Single, ByVal ang2 As Single)
            HPDF_Page_Arc(hpage, x, y, ray, ang1, ang2)
        End Sub

        Public Sub TextOut(ByVal xpos As Single, ByVal ypos As Single, ByVal text As String)
            HPDF_Page_TextOut(hpage, xpos, ypos, text)
        End Sub

        Public Sub TextRect(ByVal left As Single, ByVal top As Single, ByVal right As Single, ByVal bottom As Single, ByVal text As String, ByVal align As HPdfTextAlignment, ByRef len As UInt32)
            HPDF_Page_TextRect(hpage, left, top, right, bottom, text, align, len)
        End Sub

        Public Sub SetSlideShow(ByVal type As HPdfTransitionStyle, ByVal disp_time As Single, ByVal trans_time As Single)
            HPDF_Page_SetSlideShow(hpage, type, disp_time, trans_time)
        End Sub

        Public Function GetHandle() As IntPtr
            Return hpage
        End Function

    End Class
    Public Class HPdfFont
        Private Declare Function HPDF_Outline_SetOpened Lib "libhpdf.dll" Alias "HPDF_Outline_SetOpened" (ByVal houtline As IntPtr, ByVal opened As Int32) As UInt32

        Private Declare Function HPDF_Font_GetFontName Lib "libhpdf.dll" Alias "HPDF_Font_GetFontName" (ByVal hfont As IntPtr) As String
        Private Declare Function HPDF_Font_GetEncodingName Lib "libhpdf.dll" Alias "HPDF_Font_GetEncodingName" (ByVal hfont As IntPtr) As String
        Private Declare Function HPDF_Font_GetUnicodeWidth Lib "libhpdf.dll" Alias "HPDF_Font_GetUnicodeWidth" (ByVal hfont As IntPtr, ByVal code As UInt16) As Int32
        Private Declare Function HPDF_Font_GetBBox Lib "libhpdf.dll" Alias "HPDF_Font_GetBBox" (ByVal hfont As IntPtr) As HPdfBox
        Private Declare Function HPDF_Font_GetAscent Lib "libhpdf.dll" Alias "HPDF_Font_GetAscent" (ByVal hfont As IntPtr) As Int32
        Private Declare Function HPDF_Font_GetDescent Lib "libhpdf.dll" Alias "HPDF_Font_GetDescent" (ByVal hfont As IntPtr) As Int32
        Private Declare Function HPDF_Font_GetXHeight Lib "libhpdf.dll" Alias "HPDF_Font_GetXHeight" (ByVal hfont As IntPtr) As UInt32
        Private Declare Function HPDF_Font_GetCapHeight Lib "libhpdf.dll" Alias "HPDF_Font_GetCapHeight" (ByVal hfont As IntPtr) As UInt32
        Private Declare Function HPDF_Font_TextWidth Lib "libhpdf.dll" Alias "HPDF_Font_TextWidth" (ByVal hfont As IntPtr, ByVal text As String, ByVal len As UInt16) As HPdfTextWidth
        Private Declare Function HPDF_Font_MeasureText Lib "libhpdf.dll" Alias "HPDF_Font_MeasureText" (ByVal hfont As IntPtr, ByVal text As String, ByVal len As UInt16, _
                                                                                                        ByVal width As Single, ByVal font_size As Single, ByVal char_space As Single, ByVal word_space As Single, ByVal wordwrap As Int32, ByRef real_width As Single) As UInt32

        Private hfont As IntPtr

        Public Sub New(ByVal hfont As IntPtr)
            If (hfont = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfFont object.")
            End If

            Me.hfont = hfont
        End Sub

        Public Function GetHandle() As IntPtr
            Return hfont
        End Function

        Public Function GetFontName() As String
            Return HPDF_Font_GetFontName(hfont)
        End Function

        Public Function GetEncodingName() As String
            Return HPDF_Font_GetEncodingName(hfont)
        End Function

        Public Function GetUnicodeWidth(ByVal code As UInt16) As Int32
            Return HPDF_Font_GetUnicodeWidth(hfont, code)
        End Function

        Public Function GetBBox() As HPdfBox
            Return HPDF_Font_GetBBox(hfont)
        End Function

        Public Function GetAscent() As Int32
            Return HPDF_Font_GetAscent(hfont)
        End Function

        Public Function GetDescent() As Int32
            Return HPDF_Font_GetDescent(hfont)
        End Function

        Public Function GetXHeight() As UInt32
            Return HPDF_Font_GetXHeight(hfont)
        End Function

        Public Function GetCapHeight() As UInt32
            Return HPDF_Font_GetCapHeight(hfont)
        End Function

        Public Function TextWidth(ByVal text As String, ByVal len As UInt32) As HPdfTextWidth
            Return HPDF_Font_TextWidth(hfont, text, len)
        End Function

        Public Function MeasureText(ByVal text As String, ByVal len As UInt32, ByVal width As Single, _
                                    ByVal font_size As Single, ByVal char_space As Single, ByVal word_space As Single, _
                                    ByVal wordwrap As Int32, ByRef real_width As Single) As UInt32

            Return HPDF_Font_MeasureText(hfont, text, len, width, font_size, char_space, word_space, wordwrap, real_width)
        End Function
    End Class
    Public Class HPdfOutline

        Private Declare Function HPDF_Outline_SetOpened Lib "libhpdf.dll" Alias "HPDF_Outline_SetOpened" (ByVal houtline As IntPtr, ByVal opened As Int32) As UInt32
        Private Declare Function HPDF_Outline_SetDestination Lib "libhpdf.dll" Alias "HPDF_Outline_SetDestination" (ByVal houtline As IntPtr, ByVal hdest As IntPtr) As UInt32

        Private houtline As IntPtr

        Public Sub New(ByVal houtline As IntPtr)
            If (houtline = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfOutline object.")
            End If

            Me.houtline = houtline
        End Sub

        Public Function GetHandle() As IntPtr
            Return houtline
        End Function

        Public Sub SetOpened(ByVal opened As Boolean)
            Dim iopened As Int32

            If (opened) Then
                iopened = HPdfDoc.HPDF_TRUE
            Else
                iopened = HPdfDoc.HPDF_FALSE
            End If

            HPDF_Outline_SetOpened(houtline, iopened)
        End Sub

        Public Sub SetDestination(ByRef dest As HPdfDestination)
            HPDF_Outline_SetDestination(houtline, dest.GetHandle())
        End Sub

    End Class
    Public Class HPdfEncoder
        Private Declare Function HPDF_Encoder_GetType Lib "libhpdf.dll" Alias "HPDF_Encoder_GetType" (ByVal hencoder As IntPtr) As HPdfEncoderType
        Private Declare Function HPDF_Encoder_GetByteType Lib "libhpdf.dll" Alias "HPDF_Encoder_GetByteType" (ByVal hencoder As IntPtr, ByVal text As String, ByVal index As UInt32) As HPdfByteType
        Private Declare Function HPDF_Encoder_GetUnicode Lib "libhpdf.dll" Alias "HPDF_Encoder_GetUnicode" (ByVal hencoder As IntPtr, ByVal code As UInt16) As UInt16
        Private Declare Function HPDF_Encoder_GetWritingMode Lib "libhpdf.dll" Alias "HPDF_Encoder_GetWritingMode" (ByVal hencoder As IntPtr) As HPdfWritingMode

        Private hencoder As IntPtr

        Public Sub New(ByVal hencoder As IntPtr)
            If (hencoder = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfEncoder object.")
            End If

            Me.hencoder = hencoder
        End Sub

        Public Function GetHandle() As IntPtr
            Return hencoder
        End Function

        Public Function GetEncoderType() As HPdfEncoderType
            Return HPDF_Encoder_GetType(hencoder)
        End Function

        Public Function GetByteType(ByVal text As String, ByVal index As UInt32) As HPdfByteType
            Return HPDF_Encoder_GetByteType(hencoder, text, index)
        End Function

        Public Function GetUnicode(ByVal code As UInt16) As UInt16
            Return HPDF_Encoder_GetUnicode(hencoder, code)
        End Function

        Public Function GetWritingMode() As HPdfWritingMode
            Return HPDF_Encoder_GetWritingMode(hencoder)
        End Function
    End Class
    Public Class HPdfDestination
        Private Declare Function HPDF_Destination_SetXYZ Lib "libhpdf.dll" Alias "HPDF_Destination_SetXYZ" (ByVal hdest As IntPtr, ByVal left As Single, ByVal top As Single, ByVal zoom As Single) As UInt32
        Private Declare Function HPDF_Destination_SetFit Lib "libhpdf.dll" Alias "HPDF_Destination_SetFit" (ByVal hdest As IntPtr) As UInt32
        Private Declare Function HPDF_Destination_SetFitH Lib "libhpdf.dll" Alias "HPDF_Destination_SetFitH" (ByVal hdest As IntPtr, ByVal top As Single) As UInt32
        Private Declare Function HPDF_Destination_SetFitV Lib "libhpdf.dll" Alias "HPDF_Destination_SetFitV" (ByVal hdest As IntPtr, ByVal left As Single) As UInt32
        Private Declare Function HPDF_Destination_SetFitR Lib "libhpdf.dll" Alias "HPDF_Destination_SetFitR" (ByVal hdest As IntPtr, ByVal left As Single, ByVal bottom As Single, ByVal right As Single, ByVal top As Single) As UInt32
        Private Declare Function HPDF_Destination_SetFitB Lib "libhpdf.dll" Alias "HPDF_Destination_SetFitB" (ByVal hdest As IntPtr) As UInt32
        Private Declare Function HPDF_Destination_SetFitBH Lib "libhpdf.dll" Alias "HPDF_Destination_SetFitBH" (ByVal hdest As IntPtr, ByVal top As Single) As UInt32
        Private Declare Function HPDF_Destination_SetFitBV Lib "libhpdf.dll" Alias "HPDF_Destination_SetFitBV" (ByVal hdest As IntPtr, ByVal left As Single) As UInt32

        Private hdest As IntPtr

        Public Sub New(ByVal hdest As IntPtr)
            If (hdest = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfDestination object.")
            End If

            Me.hdest = hdest
        End Sub

        Public Sub SetXYZ(ByVal left As Single, ByVal top As Single, ByVal zoom As Single)
            HPDF_Destination_SetXYZ(hdest, left, top, zoom)
        End Sub

        Public Sub SetFit()
            HPDF_Destination_SetFit(hdest)
        End Sub

        Public Sub SetFitH(ByVal top As Single)
            HPDF_Destination_SetFitH(hdest, top)
        End Sub

        Public Sub SetFitV(ByVal left As Single)
            HPDF_Destination_SetFitV(hdest, left)
        End Sub
    
        Public Sub SetFitR(ByVal left As Single, ByVal bottom As Single, ByVal right As Single, ByVal top As Single)
            HPDF_Destination_SetFitR(hdest, left, bottom, right, top)
        End Sub

        Public Sub SetFitB()
            HPDF_Destination_SetFitB(hdest)
        End Sub

        Public Sub SetFitBH(ByVal top As Single)
            HPDF_Destination_SetFitBH(hdest, top)
        End Sub

        Public Sub SetFitBV(ByVal left As Single)
            HPDF_Destination_SetFitBV(hdest, left)
        End Sub
    
        Public Function GetHandle() As IntPtr
            Return hdest
        End Function
    End Class
    Public Class HPdfAnnotation

        Private Declare Function HPDF_LinkAnnot_SetHighlightMode Lib "libhpdf.dll" Alias "HPDF_LinkAnnot_SetHighlightMode" (ByVal hannot As IntPtr, ByVal mode As HPdfAnnotHighlightMode) As UInt32
        Private Declare Function HPDF_LinkAnnot_SetBorderStyle Lib "libhpdf.dll" Alias "HPDF_LinkAnnot_SetBorderStyle" (ByVal hannot As IntPtr, ByVal width As Single, ByVal dash_on As UInt16, ByVal dash_off As UInt16) As UInt32
        Private Declare Function HPDF_TextAnnot_SetIcon Lib "libhpdf.dll" Alias "HPDF_TextAnnot_SetIcon" (ByVal hannot As IntPtr, ByVal icon As HPdfAnnotIcon) As UInt32
        Private Declare Function HPDF_TextAnnot_SetOpened Lib "libhpdf.dll" Alias "HPDF_TextAnnot_SetOpened" (ByVal hannot As IntPtr, ByVal opened As Int32) As UInt32

        Private hannot As IntPtr

        Public Sub New(ByVal hannot As IntPtr)
            If (hannot = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfAnnotation object.")
            End If

            Me.hannot = hannot
        End Sub

        Public Function GetHandle() As IntPtr
            Return hannot
        End Function

        Public Sub SetHighlightMode(ByVal mode As HPdfAnnotHighlightMode)
            HPDF_LinkAnnot_SetHighlightMode(hannot, mode)
        End Sub

        Public Sub SetBorderStyle(ByVal width As Single, ByVal dash_on As UInt16, ByVal dash_off As UInt16)
            HPDF_LinkAnnot_SetBorderStyle(hannot, width, dash_on, dash_off)
        End Sub

        Public Sub SetIcon(ByVal icon As HPdfAnnotIcon)
            HPDF_TextAnnot_SetIcon(hannot, icon)
        End Sub

        Public Sub SetOpened(ByVal opened As Boolean)
            Dim flg As Int32

            If (opened) Then
                flg = HPdfDoc.HPDF_TRUE
            Else
                flg = HPdfDoc.HPDF_FALSE
            End If

            HPDF_TextAnnot_SetOpened(hannot, flg)
        End Sub

    End Class
    Public Class HPdfXObject
        Protected hobj As IntPtr

        Public Sub New(ByVal hobj As IntPtr)
            If (hobj = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfImage object.")
            End If

            Me.hobj = hobj
        End Sub

        Public Function GetHandle() As IntPtr
            Return hobj
        End Function
    End Class
    Public Class HPdfImage
        Inherits HPdfXObject

        Private Declare Function HPDF_Image_GetSize Lib "libhpdf.dll" Alias "HPDF_Image_GetSize" (ByVal image As IntPtr) As HPdfPoint
        Private Declare Function HPDF_Image_GetWidth Lib "libhpdf.dll" Alias "HPDF_Image_GetWidth" (ByVal image As IntPtr) As UInt32
        Private Declare Function HPDF_Image_GetHeight Lib "libhpdf.dll" Alias "HPDF_Image_GetHeight" (ByVal image As IntPtr) As UInt32
        Private Declare Function HPDF_Image_GetBitsPerComponent Lib "libhpdf.dll" Alias "HPDF_Image_GetBitsPerComponent" (ByVal image As IntPtr) As UInt32
        Private Declare Function HPDF_Image_GetColorSpace Lib "libhpdf.dll" Alias "HPDF_Image_GetColorSpace" (ByVal image As IntPtr) As String
        Private Declare Function HPDF_Image_SetColorMask Lib "libhpdf.dll" Alias "HPDF_Image_SetColorMask" (ByVal image As IntPtr, ByVal rmin As UInt32, ByVal rmax As UInt32, ByVal gmin As UInt32, ByVal gmax As UInt32, ByVal bmin As UInt32, ByVal bmax As UInt32) As UInt32
        Private Declare Function HPDF_Image_SetMaskImage Lib "libhpdf.dll" Alias "HPDF_Image_SetMaskImage" (ByVal image As IntPtr, ByVal image_mask As IntPtr) As String

        Public Sub New(ByVal hobj As IntPtr)
            MyBase.New(hobj)
        End Sub

        Public Function GetWidth() As UInt32
            Return HPDF_Image_GetWidth(hobj)
        End Function

        Public Function GetHeight() As UInt32
            Return HPDF_Image_GetHeight(hobj)
        End Function

        Public Function GetBitsPerComponent() As UInt32
            Return HPDF_Image_GetBitsPerComponent(hobj)
        End Function

        Public Function GetColorSpace() As String
            Return HPDF_Image_GetColorSpace(hobj)
        End Function

        Public Sub SetColorMask(ByVal rmin As UInt32, ByVal rmax As UInt32, ByVal gmin As UInt32, ByVal gmax As UInt32, ByVal bmin As UInt32, ByVal bmax As UInt32)
            HPDF_Image_SetColorMask(hobj, rmin, rmax, gmin, gmax, bmin, bmax)
        End Sub

        Public Sub SetMaskImage(ByRef mask_image As HPdfImage)
            HPDF_Image_SetMaskImage(hobj, mask_image.GetHandle())
        End Sub

    End Class
    Public Class HPdfExtGState
        Private Declare Function HPDF_ExtGState_SetAlphaStroke Lib "libhpdf.dll" Alias "HPDF_ExtGState_SetAlphaStroke" (ByVal gstate As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_ExtGState_SetAlphaFill Lib "libhpdf.dll" Alias "HPDF_ExtGState_SetAlphaFill" (ByVal gstate As IntPtr, ByVal value As Single) As UInt32
        Private Declare Function HPDF_ExtGState_SetBlendMode Lib "libhpdf.dll" Alias "HPDF_ExtGState_SetBlendMode" (ByVal gstate As IntPtr, ByVal mode As HPdfBlendMode) As UInt32

        Protected hgstate As IntPtr

        Public Sub New(ByVal hgstate As IntPtr)
            If (hgstate = IntPtr.Zero) Then
                Throw New Exception("cannot create HPdfImage object.")
            End If

            Me.hgstate = hgstate
        End Sub

        Public Function GetHandle() As IntPtr
            Return hgstate
        End Function

        Public Sub SetAlphaStroke(ByVal value As Single)
            HPDF_ExtGState_SetAlphaStroke(hgstate, value)
        End Sub

        Public Sub SetAlphaFill(ByVal value As Single)
            HPDF_ExtGState_SetAlphaFill(hgstate, value)
        End Sub

        Public Sub SetBlendMode(ByVal mode As HPdfBlendMode)
            HPDF_ExtGState_SetBlendMode(hgstate, mode)
        End Sub

    End Class

End Namespace
