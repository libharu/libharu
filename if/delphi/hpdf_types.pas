{*
 * << Haru Free PDF Library 2.0.6 >> -- hpdf_types.pas
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

unit hpdf_types;

interface

uses
  SysUtils;

type

{*----------------------------------------------------------------------------*}
{*----- type definition ------------------------------------------------------*}


{*  native OS integer types *}
  HPDF_INT = Integer;
  HPDF_UINT = Cardinal;
  HPDF_PUINT = ^Cardinal;

{*  32bit integer types
 *}
  HPDF_INT32 = Longint;
  HPDF_UINT32 = Longword;
  HPDF_PUINT32 = ^Longword;


{*  16bit integer types
 *}
  HPDF_INT16 = SmallInt;
  HPDF_UINT16 = Word;
  HPDF_PUINT16 = ^Word;



{*  8bit integer types
 *}
  HPDF_INT8 = Shortint;
  HPDF_UINT8 = Byte;


{*  8bit charactor types
 *}
  HPDF_CHAR = char;


{*  8bit binary types
 *}
  HPDF_BYTE = Byte;
  HPDF_PBYTE = ^Byte;


{*  float type (32bit IEEE754)
 *}
  HPDF_REAL = Single;
  HPDF_PREAL = ^HPDF_REAL;


{*  double type (64bit IEEE754)
 *}
  HPDF_DOUBLE = Double;


{*  boolean type (0: False, 1: True)
 *}
  HPDF_BOOL = Integer;


{*  error-no type (32bit unsigned integer)
 *}
  HPDF_STATUS = Cardinal;


{*  charactor-code type (16bit)
 *}
  HPDF_CID = Word;
  HPDF_UNICODE = Word;

{*  null terminated character *}
  HPDF_PCHAR = PChar;


{*  HPDF_Box struct
 *}
  THPDF_Box = packed record
    left: HPDF_REAL;
    bottom: HPDF_REAL;
    right: HPDF_REAL;
    top: HPDF_REAL;
  end;


{*  HPDF_Point struct
 *}
  THPDF_Point = packed record
    x: HPDF_REAL;
    y: HPDF_REAL;
  end;
  PHPDF_Point = ^THPDF_Point;


{*  HPDF_Rect struct
 *}
  THPDF_Rect = packed record
    left: HPDF_REAL;
    bottom: HPDF_REAL;
    right: HPDF_REAL;
    top: HPDF_REAL;
  end;


{* HPDF_Date struct
 *}
  THPDF_Date = packed record
    year: HPDF_INT;
    month: HPDF_INT;
    day: HPDF_INT;
    hour: HPDF_INT;
    minutes: HPDF_INT;
    seconds: HPDF_INT;
    ind: HPDF_CHAR;
    off_hour: HPDF_INT;
    off_minutes: HPDF_INT;
  end;


  THPDF_InfoType = (
    HPDF_INFO_CREATION_DATE,
    HPDF_INFO_MOD_DATE,
    HPDF_INFO_AUTHOR,
    HPDF_INFO_CREATOR,
    HPDF_INFO_PRODUCER,
    HPDF_INFO_TITLE,
    HPDF_INFO_SUBJECT,
    HPDF_INFO_KEYWORDS,
    HPDF_INFO_EOF
  );


  THPDF_EncryptMode = (
    HPDF_ENCRYPT_R2,
    HPDF_ENCRYPT_R3
  );




{*---------------------------------------------------------------------------*}
{*------ text width struct --------------------------------------------------*}

  THPDF_TextWidth = packed record
    numchars: HPDF_UINT;
    numwords: HPDF_UINT;   {* don't use this value. *}
    width: HPDF_UINT;
    numspace: HPDF_UINT;
  end;


{*---------------------------------------------------------------------------*}
{*------ dash mode ----------------------------------------------------------*}

  THPDF_DashMode = packed record
    ptn: array[0..7] of HPDF_UINT16;
    num_ptn: HPDF_UINT16;
    phase: HPDF_UINT16;
  end;


{*---------------------------------------------------------------------------*}
{*----- HPDF_TransMatrix struct ---------------------------------------------*}

  THPDF_TransMatrix = packed record
    a: HPDF_REAL;
    b: HPDF_REAL;
    c: HPDF_REAL;
    d: HPDF_REAL;
    x: HPDF_REAL;
    y: HPDF_REAL;
  end;


{*---------------------------------------------------------------------------*}

  THPDF_ColorSpace = (
    HPDF_CS_DEVICE_GRAY,
    HPDF_CS_DEVICE_RGB,
    HPDF_CS_DEVICE_CMYK,
    HPDF_CS_CAL_GRAY,
    HPDF_CS_CAL_RGB,
    HPDF_CS_LAB,
    HPDF_CS_ICC_BASED,
    HPDF_CS_SEPARATION,
    HPDF_CS_DEVICE_N,
    HPDF_CS_INDEXED,
    HPDF_CS_PATTERN,
    HPDF_CS_EOF
  );

{*---------------------------------------------------------------------------*}
{*----- HPDF_RGBColor struct ------------------------------------------------*}

  THPDF_RGBColor = packed record
    r: HPDF_REAL;
    g: HPDF_REAL;
    b: HPDF_REAL;
  end;

{*---------------------------------------------------------------------------*}
{*----- HPDF_CMYKColor struct -----------------------------------------------*}

  THPDF_CMYKColor = packed record
    c: HPDF_REAL;
    m: HPDF_REAL;
    y: HPDF_REAL;
    k: HPDF_REAL;
  end;

{*---------------------------------------------------------------------------*}
{*------ The line cap style -------------------------------------------------*}

  THPDF_LineCap = (
    HPDF_BUTT_END,
    HPDF_ROUND_END,
    HPDF_PROJECTING_SCUARE_END
  );

{*----------------------------------------------------------------------------*}
{*------ The line join style -------------------------------------------------*}

  THPDF_LineJoin = (
    HPDF_MITER_JOIN,
    HPDF_ROUND_JOIN,
    HPDF_BEVEL_JOIN
  );

{*----------------------------------------------------------------------------*}
{*------ The text rendering mode ---------------------------------------------*}

  THPDF_TextRenderingMode = (
    HPDF_FILL,
    HPDF_STROKE,
    HPDF_FILL_THEN_STROKE,
    HPDF_INVISIBLE,
    HPDF_FILL_CLIPPING,
    HPDF_STROKE_CLIPPING,
    HPDF_FILL_STROKE_CLIPPING,
    HPDF_CLIPPING,
    HPDF_RENDERING_MODE_EOF
  );


  THPDF_WritingMode = (
    HPDF_WMODE_HORIZONTAL,
    HPDF_WMODE_VERTICAL
  );


  THPDF_PageLayout = (
    HPDF_PAGE_LAYOUT_SINGLE,
    HPDF_PAGE_LAYOUT_ONE_COLUMN,
    HPDF_PAGE_LAYOUT_TWO_COLUMN_LEFT,
    HPDF_PAGE_LAYOUT_TWO_COLUMN_RIGHT
  );


  THPDF_PageMode = (
    HPDF_PAGE_MODE_USE_NONE,
    HPDF_PAGE_MODE_USE_OUTLINE,
    HPDF_PAGE_MODE_USE_THUMBS,
    HPDF_PAGE_MODE_FULL_SCREEN
{*  HPDF_PAGE_MODE_USE_OC,
    HPDF_PAGE_MODE_USE_ATTACHMENTS
 *}
  );


  THPDF_PageNumStyle = (
    HPDF_PAGE_NUM_STYLE_DECIMAL,
    HPDF_PAGE_NUM_STYLE_UPPER_ROMAN,
    HPDF_PAGE_NUM_STYLE_LOWER_ROMAN,
    HPDF_PAGE_NUM_STYLE_UPPER_LETTERS,
    HPDF_PAGE_NUM_STYLE_LOWER_LETTERS
  );


  THPDF_DestinationType = (
    HPDF_XYZ,
    HPDF_FIT,
    HPDF_FIT_H,
    HPDF_FIT_V,
    HPDF_FIT_R,
    HPDF_FIT_B,
    HPDF_FIT_BH,
    HPDF_FIT_BV,
    HPDF_DST_EOF
  );


  THPDF_AnnotType = (
    HPDF_ANNOT_TEXT_NOTES,
    HPDF_ANNOT_LINK,
    HPDF_ANNOT_SOUND,
    HPDF_ANNOT_FREE_TEXT,
    HPDF_ANNOT_STAMP,
    HPDF_ANNOT_SQUARE,
    HPDF_ANNOT_CIRCLE,
    HPDF_ANNOT_STRIKE_OUT,
    HPDF_ANNOT_HIGHTLIGHT,
    HPDF_ANNOT_UNDERLINE,
    HPDF_ANNOT_INK,
    HPDF_ANNOT_FILE_ATTACHMENT,
    HPDF_ANNOT_POPUP
  );


  THPDF_AnnotFlgs = (
    HPDF_ANNOT_INVISIBLE,
    HPDF_ANNOT_HIDDEN,
    HPDF_ANNOT_PRINT,
    HPDF_ANNOT_NOZOOM,
    HPDF_ANNOT_NOROTATE,
    HPDF_ANNOT_NOVIEW,
    HPDF_ANNOT_READONLY
  );


  THPDF_AnnotHighlightMode = (
    HPDF_ANNOT_NO_HIGHTLIGHT,
    HPDF_ANNOT_INVERT_BOX,
    HPDF_ANNOT_INVERT_BORDER,
    HPDF_ANNOT_DOWN_APPEARANCE
  );


  THPDF_AnnotIcon = (
    HPDF_ANNOT_ICON_COMMENT,
    HPDF_ANNOT_ICON_KEY,
    HPDF_ANNOT_ICON_NOTE,
    HPDF_ANNOT_ICON_HELP,
    HPDF_ANNOT_ICON_NEW_PARAGRAPH,
    HPDF_ANNOT_ICON_PARAGRAPH,
    HPDF_ANNOT_ICON_INSERT
  );


{*----------------------------------------------------------------------------*}
{*------ border stype --------------------------------------------------------*}

  THPDF_BSSubtype = (
    HPDF_BS_SOLID,
    HPDF_BS_DASHED,
    HPDF_BS_BEVELED,
    HPDF_BS_INSET,
    HPDF_BS_UNDERLINED
  );


  THPDF_PageSizes = (
    HPDF_PAGE_SIZE_LETTER,
    HPDF_PAGE_SIZE_LEGAL,
    HPDF_PAGE_SIZE_A3,
    HPDF_PAGE_SIZE_A4,
    HPDF_PAGE_SIZE_A5,
    HPDF_PAGE_SIZE_B5,
    HPDF_PAGE_SIZE_EXECUTIVE,
    HPDF_PAGE_SIZE_US4x6,
    HPDF_PAGE_SIZE_US4x8,
    HPDF_PAGE_SIZE_US5x7,
    HPDF_PAGE_SIZE_COMM10
  );


  THPDF_PageDirection = (
    HPDF_PAGE_PORTRAIT,
    HPDF_PAGE_LANDSCAPE
  );


  THPDF_EncoderType = (
    HPDF_ENCODER_TYPE_SINGLE_BYTE,
    HPDF_ENCODER_TYPE_DOUBLE_BYTE,
    HPDF_ENCODER_TYPE_UNINITIALIZED,
    HPDF_ENCODER_UNKNOWN
  );


  THPDF_ByteType = (
    HPDF_BYTE_TYPE_SINGLE,
    HPDF_BYTE_TYPE_LEAD,
    HPDF_BYTE_TYPE_TRIAL,
    HPDF_BYTE_TYPE_UNKNOWN
  );


  THPDF_TextAlignment = (
    HPDF_TALIGN_LEFT,
    HPDF_TALIGN_RIGHT,
    HPDF_TALIGN_CENTER,
    HPDF_TALIGN_JUSTIFY
  );


  THPDF_BlendMode = (
    HPDF_BM_NORMAL,
    HPDF_BM_MULTIPLY,
    HPDF_BM_SCREEN,
    HPDF_BM_OVERLAY,
    HPDF_BM_DARKEN,
    HPDF_BM_LIGHTEN,
    HPDF_BM_COLOR_DODGE,
    HPDF_BM_COLOR_BUM,
    HPDF_BM_HARD_LIGHT,
    HPDF_BM_SOFT_LIGHT,
    HPDF_BM_DIFFERENCE,
    HPDF_BM_EXCLUSHON,
    HPDF_BM_EOF
  );


  THPDF_TransitionStyle = (
    HPDF_TS_WIPE_RIGHT,
    HPDF_TS_WIPE_UP,
    HPDF_TS_WIPE_LEFT,
    HPDF_TS_WIPE_DOWN,
    HPDF_TS_BARN_DOORS_HORIZONTAL_OUT,
    HPDF_TS_BARN_DOORS_HORIZONTAL_IN,
    HPDF_TS_BARN_DOORS_VERTICAL_OUT,
    HPDF_TS_BARN_DOORS_VERTICAL_IN,
    HPDF_TS_BOX_OUT,
    HPDF_TS_BOX_IN,
    HPDF_TS_BLINDS_HORIZONTAL,
    HPDF_TS_BLINDS_VERTICAL,
    HPDF_TS_DISSOLVE,
    HPDF_TS_GLITTER_RIGHT,
    HPDF_TS_GLITTER_DOWN,
    HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT,
    HPDF_TS_REPLACE,
    HPDF_TS_EOF
  );


THPDF_ErrorFunc = procedure (error_no: HPDF_STATUS; detail_no: HPDF_STATUS;
                user_data: Pointer); stdcall;

THPDF_AllocFunc = procedure (size: Cardinal); stdcall;

THPDF_FreeFunc = procedure (aptr: Pointer); stdcall;

implementation

end.
