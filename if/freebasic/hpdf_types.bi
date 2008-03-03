''
''
'' hpdf_types -- header translated with help of SWIG FB wrapper
''
'' NOTICE: This file is part of the FreeBASIC Compiler package and can't
''         be included in other distributions without authorization.
''
''
#ifndef __hpdf_types_bi__
#define __hpdf_types_bi__


Type HPDF_HANDLE As Any Ptr
Type HPDF_Doc As HPDF_HANDLE
Type HPDF_Page As HPDF_HANDLE
Type HPDF_Pages As HPDF_HANDLE
Type HPDF_Stream As HPDF_HANDLE
Type HPDF_Image As HPDF_HANDLE
Type HPDF_Font As HPDF_HANDLE
Type HPDF_Outline As HPDF_HANDLE
Type HPDF_Encoder As HPDF_HANDLE
Type HPDF_Destination As HPDF_HANDLE
Type HPDF_XObject As HPDF_HANDLE
Type HPDF_Annotation As HPDF_HANDLE
Type HPDF_ExtGState As HPDF_HANDLE


type HPDF_INT as integer
type HPDF_UINT as uinteger
type HPDF_INT32 as integer
type HPDF_UINT32 as uinteger
type HPDF_INT16 as short
type HPDF_UINT16 as ushort
type HPDF_INT8 as byte
type HPDF_UINT8 as ubyte
type HPDF_BYTE as ubyte
type HPDF_REAL as single
type HPDF_DOUBLE as double
type HPDF_BOOL as integer
type HPDF_STATUS as uinteger
type HPDF_CID as HPDF_UINT16
type HPDF_UNICODE as HPDF_UINT16

type _HPDF_Point
	x as HPDF_REAL
	y as HPDF_REAL
end type

type HPDF_Point as _HPDF_Point

type _HPDF_Rect
	left as HPDF_REAL
	bottom as HPDF_REAL
	right as HPDF_REAL
	top as HPDF_REAL
end type

type HPDF_Rect as _HPDF_Rect
type HPDF_Box as _HPDF_Rect

type _HPDF_Date
	year as HPDF_INT
	month as HPDF_INT
	day as HPDF_INT
	hour as HPDF_INT
	minutes as HPDF_INT
	seconds as HPDF_INT
	ind as byte
	off_hour as HPDF_INT
	off_minutes as HPDF_INT
end type

type HPDF_Date as _HPDF_Date

enum _HPDF_InfoType
	HPDF_INFO_CREATION_DATE = 0
	HPDF_INFO_MOD_DATE
	HPDF_INFO_AUTHOR
	HPDF_INFO_CREATOR
	HPDF_INFO_PRODUCER
	HPDF_INFO_TITLE
	HPDF_INFO_SUBJECT
	HPDF_INFO_KEYWORDS
	HPDF_INFO_EOF
end enum

type HPDF_InfoType as _HPDF_InfoType

enum _HPDF_PdfVer
	HPDF_VER_12 = 0
	HPDF_VER_13
	HPDF_VER_14
	HPDF_VER_15
	HPDF_VER_16
	HPDF_VER_EOF
end enum

type HPDF_PDFVer as _HPDF_PdfVer

enum _HPDF_EncryptMode
	HPDF_ENCRYPT_R2 = 2
	HPDF_ENCRYPT_R3 = 3
end enum

type HPDF_EncryptMode as _HPDF_EncryptMode
type HPDF_Error_Handler as sub cdecl(byval as HPDF_STATUS, byval as HPDF_STATUS, byval as any ptr)
type HPDF_Alloc_Func as sub cdecl(byval as HPDF_UINT)
type HPDF_Free_Func as sub cdecl(byval as any ptr)

type _HPDF_TextWidth
	numchars as HPDF_UINT
	numwords as HPDF_UINT
	width as HPDF_UINT
	numspace as HPDF_UINT
end type

type HPDF_TextWidth as _HPDF_TextWidth

type _HPDF_DashMode
	ptn(0 to 8-1) as HPDF_UINT16
	num_ptn as HPDF_UINT
	phase as HPDF_UINT
end type

type HPDF_DashMode as _HPDF_DashMode

type _HPDF_TransMatrix
	a as HPDF_REAL
	b as HPDF_REAL
	c as HPDF_REAL
	d as HPDF_REAL
	x as HPDF_REAL
	y as HPDF_REAL
end type

type HPDF_TransMatrix as _HPDF_TransMatrix

enum _HPDF_ColorSpace
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
end enum

type HPDF_ColorSpace as _HPDF_ColorSpace

type _HPDF_RGBColor
	r as HPDF_REAL
	g as HPDF_REAL
	b as HPDF_REAL
end type

type HPDF_RGBColor as _HPDF_RGBColor

type _HPDF_CMYKColor
	c as HPDF_REAL
	m as HPDF_REAL
	y as HPDF_REAL
	k as HPDF_REAL
end type

type HPDF_CMYKColor as _HPDF_CMYKColor

enum _HPDF_LineCap
	HPDF_BUTT_END = 0
	HPDF_ROUND_END
	HPDF_PROJECTING_SCUARE_END
	HPDF_LINECAP_EOF
end enum

type HPDF_LineCap as _HPDF_LineCap

enum _HPDF_LineJoin
	HPDF_MITER_JOIN = 0
	HPDF_ROUND_JOIN
	HPDF_BEVEL_JOIN
	HPDF_LINEJOIN_EOF
end enum

type HPDF_LineJoin as _HPDF_LineJoin

enum _HPDF_TextRenderingMode
	HPDF_FILL = 0
	HPDF_STROKE
	HPDF_FILL_THEN_STROKE
	HPDF_INVISIBLE
	HPDF_FILL_CLIPPING
	HPDF_STROKE_CLIPPING
	HPDF_FILL_STROKE_CLIPPING
	HPDF_CLIPPING
	HPDF_RENDERING_MODE_EOF
end enum

type HPDF_TextRenderingMode as _HPDF_TextRenderingMode

enum _HPDF_WritingMode
	HPDF_WMODE_HORIZONTAL = 0
	HPDF_WMODE_VERTICAL
	HPDF_WMODE_EOF
end enum

type HPDF_WritingMode as _HPDF_WritingMode

enum _HPDF_PageLayout
	HPDF_PAGE_LAYOUT_SINGLE = 0
	HPDF_PAGE_LAYOUT_ONE_COLUMN
	HPDF_PAGE_LAYOUT_TWO_COLUMN_LEFT
	HPDF_PAGE_LAYOUT_TWO_COLUMN_RIGHT
	HPDF_PAGE_LAYOUT_EOF
end enum

type HPDF_PageLayout as _HPDF_PageLayout

enum _HPDF_PageMode
	HPDF_PAGE_MODE_USE_NONE = 0
	HPDF_PAGE_MODE_USE_OUTLINE
	HPDF_PAGE_MODE_USE_THUMBS
	HPDF_PAGE_MODE_FULL_SCREEN
	HPDF_PAGE_MODE_EOF
end enum

type HPDF_PageMode as _HPDF_PageMode

enum _HPDF_PageNumStyle
	HPDF_PAGE_NUM_STYLE_DECIMAL = 0
	HPDF_PAGE_NUM_STYLE_UPPER_ROMAN
	HPDF_PAGE_NUM_STYLE_LOWER_ROMAN
	HPDF_PAGE_NUM_STYLE_UPPER_LETTERS
	HPDF_PAGE_NUM_STYLE_LOWER_LETTERS
	HPDF_PAGE_NUM_STYLE_EOF
end enum

type HPDF_PageNumStyle as _HPDF_PageNumStyle

enum _HPDF_DestinationType
	HPDF_XYZ = 0
	HPDF_FIT
	HPDF_FIT_H
	HPDF_FIT_V
	HPDF_FIT_R
	HPDF_FIT_B
	HPDF_FIT_BH
	HPDF_FIT_BV
	HPDF_DST_EOF
end enum

type HPDF_DestinationType as _HPDF_DestinationType

enum _HPDF_AnnotType
	HPDF_ANNOT_TEXT_NOTES
	HPDF_ANNOT_LINK
	HPDF_ANNOT_SOUND
	HPDF_ANNOT_FREE_TEXT
	HPDF_ANNOT_STAMP
	HPDF_ANNOT_SQUARE
	HPDF_ANNOT_CIRCLE
	HPDF_ANNOT_STRIKE_OUT
	HPDF_ANNOT_HIGHTLIGHT
	HPDF_ANNOT_UNDERLINE
	HPDF_ANNOT_INK
	HPDF_ANNOT_FILE_ATTACHMENT
	HPDF_ANNOT_POPUP
end enum

type HPDF_AnnotType as _HPDF_AnnotType

enum _HPDF_AnnotFlgs
	HPDF_ANNOT_INVISIBLE
	HPDF_ANNOT_HIDDEN
	HPDF_ANNOT_PRINT
	HPDF_ANNOT_NOZOOM
	HPDF_ANNOT_NOROTATE
	HPDF_ANNOT_NOVIEW
	HPDF_ANNOT_READONLY
end enum

type HPDF_AnnotFlgs as _HPDF_AnnotFlgs

enum _HPDF_AnnotHighlightMode
	HPDF_ANNOT_NO_HIGHTLIGHT = 0
	HPDF_ANNOT_INVERT_BOX
	HPDF_ANNOT_INVERT_BORDER
	HPDF_ANNOT_DOWN_APPEARANCE
	HPDF_ANNOT_HIGHTLIGHT_MODE_EOF
end enum

type HPDF_AnnotHighlightMode as _HPDF_AnnotHighlightMode

enum _HPDF_AnnotIcon
	HPDF_ANNOT_ICON_COMMENT = 0
	HPDF_ANNOT_ICON_KEY
	HPDF_ANNOT_ICON_NOTE
	HPDF_ANNOT_ICON_HELP
	HPDF_ANNOT_ICON_NEW_PARAGRAPH
	HPDF_ANNOT_ICON_PARAGRAPH
	HPDF_ANNOT_ICON_INSERT
	HPDF_ANNOT_ICON_EOF
end enum

type HPDF_AnnotIcon as _HPDF_AnnotIcon

enum _HPDF_BSSubtype
	HPDF_BS_SOLID
	HPDF_BS_DASHED
	HPDF_BS_BEVELED
	HPDF_BS_INSET
	HPDF_BS_UNDERLINED
end enum

type HPDF_BSSubtype as _HPDF_BSSubtype

enum _HPDF_BlendMode
	HPDF_BM_NORMAL
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
end enum

type HPDF_BlendMode as _HPDF_BlendMode

enum _HPDF_TransitionStyle
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
end enum

type HPDF_TransitionStyle as _HPDF_TransitionStyle

enum _HPDF_PageSizes
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
end enum

type HPDF_PageSizes as _HPDF_PageSizes

enum _HPDF_PageDirection
	HPDF_PAGE_PORTRAIT = 0
	HPDF_PAGE_LANDSCAPE
end enum

type HPDF_PageDirection as _HPDF_PageDirection

enum _HPDF_EncoderType
	HPDF_ENCODER_TYPE_SINGLE_BYTE
	HPDF_ENCODER_TYPE_DOUBLE_BYTE
	HPDF_ENCODER_TYPE_UNINITIALIZED
	HPDF_ENCODER_UNKNOWN
end enum

type HPDF_EncoderType as _HPDF_EncoderType

enum _HPDF_ByteType
	HPDF_BYTE_TYPE_SINGLE = 0
	HPDF_BYTE_TYPE_LEAD
	HPDF_BYTE_TYPE_TRIAL
	HPDF_BYTE_TYPE_UNKNOWN
end enum

type HPDF_ByteType as _HPDF_ByteType

enum _HPDF_TextAlignment
	HPDF_TALIGN_LEFT = 0
	HPDF_TALIGN_RIGHT
	HPDF_TALIGN_CENTER
	HPDF_TALIGN_JUSTIFY
end enum

type HPDF_TextAlignment as _HPDF_TextAlignment



#endif
