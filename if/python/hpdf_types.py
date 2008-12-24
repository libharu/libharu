###
## * << Haru Free PDF Library 2.0.3 >> -- hpdf_types.h
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

from ctypes import *

#----------------------------------------------------------------------------
#----- type definition ------------------------------------------------------


#  native OS integer types
HPDF_INT=c_int
HPDF_UINT=c_uint


#  32bit integer types
HPDF_INT32=c_int
HPDF_UINT32=c_uint


#  16bit integer types
HPDF_INT16=c_short
HPDF_UINT16=c_ushort


#  8bit integer types
HPDF_INT8=c_char
HPDF_UINT8=c_ubyte


#  8bit binary types
HPDF_BYTE=c_ubyte


#  float type (32bit IEEE754)
HPDF_REAL=c_float


#  double type (64bit IEEE754)
HPDF_DOUBLE=c_double


#  boolean type (0: False, !0: True)
HPDF_BOOL=c_int


#  error-no type (32bit unsigned integer)
HPDF_STATUS=c_ulong


#  charactor-code type (16bit)
HPDF_CID=HPDF_UINT16
HPDF_UNICODE=HPDF_UINT16


#  HPDF_Point struct
class _HPDF_Point(Structure):
    _fields_=[
              ('x',            HPDF_REAL),
              ('y',            HPDF_REAL),
             ]
HPDF_Point = _HPDF_Point

class _HPDF_Rect(Structure):
    _fields_=[
              ('left',         HPDF_REAL),
              ('bottom',       HPDF_REAL),
              ('right',        HPDF_REAL),
              ('top',          HPDF_REAL),
             ]
HPDF_Rect = _HPDF_Rect

HPDF_Box= _HPDF_Rect

# HPDF_Date struct
class _HPDF_Date(Structure):
    _fields_=[
              ('year',         HPDF_INT),
              ('month',        HPDF_INT),
              ('day',          HPDF_INT),
              ('hour',         HPDF_INT),
              ('minutes',      HPDF_INT),
              ('seconds',      HPDF_INT),
              ('ind',          c_char),
              ('off_hour',     HPDF_INT),
              ('off_minutes',  HPDF_INT),
             ]
HPDF_Date = _HPDF_Date


#enum starts
## date-time type parameters
HPDF_INFO_CREATION_DATE     =0
HPDF_INFO_MOD_DATE          =1

## string type parameters
HPDF_INFO_AUTHOR            =2
HPDF_INFO_CREATOR           =3
HPDF_INFO_PRODUCER          =4
HPDF_INFO_TITLE             =5
HPDF_INFO_SUBJECT           =6
HPDF_INFO_KEYWORDS          =7
HPDF_INFO_EOF               =8
HPDF_InfoType               =c_int
#enum ends

#enum starts
HPDF_VER_12                 =0
HPDF_VER_13                 =1
HPDF_VER_14                 =2
HPDF_VER_15                 =3
HPDF_VER_16                 =4
HPDF_VER_EOF                =5
HPDF_PDFVer                 =c_int
#enum ends



#enum starts
HPDF_ENCRYPT_R2             =2
HPDF_ENCRYPT_R3             =3
HPDF_EncryptMode            =c_int
#enum ends




##typedef void
##(HPDF_STDCALL *HPDF_Error_Handler)  (HPDF_STATUS   error_no,
##                                     HPDF_STATUS   detail_no,
##                                     void         *user_data)
def HPDF_Error_Handler(restype,
                       error_no,
                       detail_no,
                       user_data):
    return CFUNCTYPE(restype,
                     error_no,
                     detail_no,
                     user_data,
                    )

#typedef void*
#(HPDF_STDCALL *HPDF_Alloc_Func)  (HPDF_UINT  size)
HPDF_Alloc_Func=CFUNCTYPE(c_void_p,
                          HPDF_UINT,        #size
                         )


#typedef void
#(HPDF_STDCALL *HPDF_Free_Func)  (void  *aptr)
HPDF_Free_Func=CFUNCTYPE(None,
                         c_void_p,          #aptr
                        )


#---------------------------------------------------------------------------
#------ text width struct --------------------------------------------------

class _HPDF_TextWidth(Structure):
    _fields_=[
              ('numchars',            HPDF_UINT),

              # don't use this value (it may be change in the feature).
              # use numspace as alternated.
              ('numwords',            HPDF_UINT),

              ('width',               HPDF_UINT),
              ('numspace',            HPDF_UINT),
             ]
HPDF_TextWidth = _HPDF_TextWidth


#---------------------------------------------------------------------------
#------ dash mode ----------------------------------------------------------

class _HPDF_DashMode(Structure):
    _fields_=[
              ('ptn',                 HPDF_UINT16*8),
              ('num_ptn',             HPDF_UINT),
              ('phase',               HPDF_UINT),
             ]
HPDF_DashMode = _HPDF_DashMode


#---------------------------------------------------------------------------
#----- HPDF_TransMatrix struct ---------------------------------------------

class _HPDF_TransMatrix(Structure):
    _fields_=[
              ('a',                   HPDF_REAL),
              ('b',                   HPDF_REAL),
              ('c',                   HPDF_REAL),
              ('d',                   HPDF_REAL),
              ('x',                   HPDF_REAL),
              ('y',                   HPDF_REAL),
             ]
HPDF_TransMatrix = _HPDF_TransMatrix




#---------------------------------------------------------------------------

#enum starts
HPDF_CS_DEVICE_GRAY            =0
HPDF_CS_DEVICE_RGB             =1
HPDF_CS_DEVICE_CMYK            =2
HPDF_CS_CAL_GRAY               =3
HPDF_CS_CAL_RGB                =4
HPDF_CS_LAB                    =5
HPDF_CS_ICC_BASED              =6
HPDF_CS_SEPARATION             =7
HPDF_CS_DEVICE_N               =8
HPDF_CS_INDEXED                =9
HPDF_CS_PATTERN                =10
HPDF_CS_EOF                    =11
HPDF_ColorSpace                =c_int
#enum ends



#---------------------------------------------------------------------------
#----- HPDF_RGBColor struct ------------------------------------------------

class _HPDF_RGBColor(Structure):
    _fields_=[
              ('r',            HPDF_REAL),
              ('g',            HPDF_REAL),
              ('b',            HPDF_REAL),
             ]
HPDF_RGBColor = _HPDF_RGBColor

#---------------------------------------------------------------------------
#----- HPDF_CMYKColor struct -----------------------------------------------

class _HPDF_CMYKColor(Structure):
    _fields_=[
              ('c',             HPDF_REAL),
              ('m',             HPDF_REAL),
              ('y',             HPDF_REAL),
              ('k',             HPDF_REAL),
             ]
HPDF_CMYKColor=_HPDF_CMYKColor

#---------------------------------------------------------------------------
#------ The line cap style -------------------------------------------------

#enum starts
HPDF_BUTT_END                                =0
HPDF_ROUND_END                               =1
HPDF_PROJECTING_SCUARE_END                   =2
HPDF_LINECAP_EOF                             =3
HPDF_LineCap                                 =c_int
#enum ends



#----------------------------------------------------------------------------
#------ The line join style -------------------------------------------------

#enum starts
HPDF_MITER_JOIN                              =0
HPDF_ROUND_JOIN                              =1
HPDF_BEVEL_JOIN                              =2
HPDF_LINEJOIN_EOF                            =3
HPDF_LineJoin                                =c_int
#enum ends



#----------------------------------------------------------------------------
#------ The text rendering mode ---------------------------------------------

#enum starts
HPDF_FILL                                    =0
HPDF_STROKE                                  =1
HPDF_FILL_THEN_STROKE                        =2
HPDF_INVISIBLE                               =3
HPDF_FILL_CLIPPING                           =4
HPDF_STROKE_CLIPPING                         =5
HPDF_FILL_STROKE_CLIPPING                    =6
HPDF_CLIPPING                                =7
HPDF_RENDERING_MODE_EOF                      =8
HPDF_TextRenderingMode                       =c_int
#enum ends




#enum starts
HPDF_WMODE_HORIZONTAL                        =0
HPDF_WMODE_VERTICAL                          =1
HPDF_WMODE_EOF                               =2
HPDF_WritingMode                             =c_int
#enum ends




#enum starts
HPDF_PAGE_LAYOUT_SINGLE                      =0
HPDF_PAGE_LAYOUT_ONE_COLUMN                  =1
HPDF_PAGE_LAYOUT_TWO_COLUMN_LEFT             =2
HPDF_PAGE_LAYOUT_TWO_COLUMN_RIGHT            =3
HPDF_PAGE_LAYOUT_EOF                         =4
HPDF_PageLayout                              =c_int
#enum ends




#enum starts
HPDF_PAGE_MODE_USE_NONE                      =0
HPDF_PAGE_MODE_USE_OUTLINE                   =1
HPDF_PAGE_MODE_USE_THUMBS                    =2
HPDF_PAGE_MODE_FULL_SCREEN                   =3
HPDF_PAGE_MODE_USE_OC                        =4     #???
HPDF_PAGE_MODE_USE_ATTACHMENTS               =5     #???
HPDF_PAGE_MODE_EOF                           =6
HPDF_PageMode                                =c_int
#enum ends




#enum starts
HPDF_PAGE_NUM_STYLE_DECIMAL                  =0
HPDF_PAGE_NUM_STYLE_UPPER_ROMAN              =1
HPDF_PAGE_NUM_STYLE_LOWER_ROMAN              =2
HPDF_PAGE_NUM_STYLE_UPPER_LETTERS            =3
HPDF_PAGE_NUM_STYLE_LOWER_LETTERS            =4
HPDF_PAGE_NUM_STYLE_EOF                      =5
HPDF_PageNumStyle                            =c_int
#enum ends




#enum starts
HPDF_XYZ                                     =0
HPDF_FIT                                     =1
HPDF_FIT_H                                   =2
HPDF_FIT_V                                   =3
HPDF_FIT_R                                   =4
HPDF_FIT_B                                   =5
HPDF_FIT_BH                                  =6
HPDF_FIT_BV                                  =7
HPDF_DST_EOF                                 =8
HPDF_DestinationType                         =c_int
#enum ends




#enum starts
HPDF_ANNOT_TEXT_NOTES                        =0
HPDF_ANNOT_LINK                              =1
HPDF_ANNOT_SOUND                             =2
HPDF_ANNOT_FREE_TEXT                         =3
HPDF_ANNOT_STAMP                             =4
HPDF_ANNOT_SQUARE                            =5
HPDF_ANNOT_CIRCLE                            =6
HPDF_ANNOT_STRIKE_OUT                        =7
HPDF_ANNOT_HIGHTLIGHT                        =8
HPDF_ANNOT_UNDERLINE                         =9
HPDF_ANNOT_INK                               =10
HPDF_ANNOT_FILE_ATTACHMENT                   =11
HPDF_ANNOT_POPUP                             =12
HPDF_AnnotType                               =c_int
#enum ends




#enum starts
HPDF_ANNOT_INVISIBLE                         =0
HPDF_ANNOT_HIDDEN                            =1
HPDF_ANNOT_PRINT                             =2
HPDF_ANNOT_NOZOOM                            =3
HPDF_ANNOT_NOROTATE                          =4
HPDF_ANNOT_NOVIEW                            =5
HPDF_ANNOT_READONLY                          =6
HPDF_AnnotFlgs                               =c_int
#enum ends




#enum starts
HPDF_ANNOT_NO_HIGHTLIGHT                     =0
HPDF_ANNOT_INVERT_BOX                        =1
HPDF_ANNOT_INVERT_BORDER                     =2
HPDF_ANNOT_DOWN_APPEARANCE                   =3
HPDF_ANNOT_HIGHTLIGHT_MODE_EOF               =4
HPDF_AnnotHighlightMode                      =c_int
#enum ends




#enum starts
HPDF_ANNOT_ICON_COMMENT                      =0
HPDF_ANNOT_ICON_KEY                          =1
HPDF_ANNOT_ICON_NOTE                         =2
HPDF_ANNOT_ICON_HELP                         =3
HPDF_ANNOT_ICON_NEW_PARAGRAPH                =4
HPDF_ANNOT_ICON_PARAGRAPH                    =5
HPDF_ANNOT_ICON_INSERT                       =6
HPDF_ANNOT_ICON_EOF                          =7
HPDF_AnnotIcon                               =c_int
#enum ends





#----------------------------------------------------------------------------
#------ border stype --------------------------------------------------------

#enum starts
HPDF_BS_SOLID                                =0
HPDF_BS_DASHED                               =1
HPDF_BS_BEVELED                              =2
HPDF_BS_INSET                                =3
HPDF_BS_UNDERLINED                           =4
HPDF_BSSubtype                               =c_int
#enum ends




#----- blend modes ----------------------------------------------------------

#enum starts
HPDF_BM_NORMAL                               =0
HPDF_BM_MULTIPLY                             =1
HPDF_BM_SCREEN                               =2
HPDF_BM_OVERLAY                              =3
HPDF_BM_DARKEN                               =4
HPDF_BM_LIGHTEN                              =5
HPDF_BM_COLOR_DODGE                          =6
HPDF_BM_COLOR_BUM                            =7
HPDF_BM_HARD_LIGHT                           =8
HPDF_BM_SOFT_LIGHT                           =9
HPDF_BM_DIFFERENCE                           =10
HPDF_BM_EXCLUSHON                            =11
HPDF_BM_EOF                                  =12
HPDF_BlendMode                               =c_int
#enum ends



#----- slide show -----------------------------------------------------------

#enum starts
HPDF_TS_WIPE_RIGHT                           =0
HPDF_TS_WIPE_UP                              =1
HPDF_TS_WIPE_LEFT                            =2
HPDF_TS_WIPE_DOWN                            =3
HPDF_TS_BARN_DOORS_HORIZONTAL_OUT            =4
HPDF_TS_BARN_DOORS_HORIZONTAL_IN             =5
HPDF_TS_BARN_DOORS_VERTICAL_OUT              =6
HPDF_TS_BARN_DOORS_VERTICAL_IN               =7
HPDF_TS_BOX_OUT                              =8
HPDF_TS_BOX_IN                               =9
HPDF_TS_BLINDS_HORIZONTAL                    =10
HPDF_TS_BLINDS_VERTICAL                      =11
HPDF_TS_DISSOLVE                             =12
HPDF_TS_GLITTER_RIGHT                        =13
HPDF_TS_GLITTER_DOWN                         =14
HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT     =15
HPDF_TS_REPLACE                              =16
HPDF_TS_EOF                                  =17
HPDF_TransitionStyle                         =c_int
#enum ends



#----------------------------------------------------------------------------

#enum starts
HPDF_PAGE_SIZE_LETTER                        =0
HPDF_PAGE_SIZE_LEGAL                         =1
HPDF_PAGE_SIZE_A3                            =2
HPDF_PAGE_SIZE_A4                            =3
HPDF_PAGE_SIZE_A5                            =4
HPDF_PAGE_SIZE_B4                            =5
HPDF_PAGE_SIZE_B5                            =6
HPDF_PAGE_SIZE_EXECUTIVE                     =7
HPDF_PAGE_SIZE_US4x6                         =8
HPDF_PAGE_SIZE_US4x8                         =9
HPDF_PAGE_SIZE_US5x7                         =10
HPDF_PAGE_SIZE_COMM10                        =11
HPDF_PAGE_SIZE_EOF                           =12
HPDF_PageSizes                               =c_int
#enum ends




#enum starts
HPDF_PAGE_PORTRAIT                           =0
HPDF_PAGE_LANDSCAPE                          =1
HPDF_PageDirection                           =c_int
#enum ends




#enum starts
HPDF_ENCODER_TYPE_SINGLE_BYTE                =0
HPDF_ENCODER_TYPE_DOUBLE_BYTE                =1
HPDF_ENCODER_TYPE_UNINITIALIZED              =2
HPDF_ENCODER_UNKNOWN                         =3
HPDF_EncoderType                             =c_int
#enum ends




#enum starts
HPDF_BYTE_TYPE_SINGLE                        =0
HPDF_BYTE_TYPE_LEAD                          =1
HPDF_BYTE_TYPE_TRIAL                         =2
HPDF_BYTE_TYPE_UNKNOWN                       =3
HPDF_ByteType                                =c_int
#enum ends




#enum starts
HPDF_TALIGN_LEFT                             =0
HPDF_TALIGN_RIGHT                            =1
HPDF_TALIGN_CENTER                           =2
HPDF_TALIGN_JUSTIFY                          =3
HPDF_TextAlignment                           =c_int
#enum ends
