/*
 * << Haru Free PDF Library 2.0.6 >> -- hpdf.cs
 *
 * C# wrapper for libhpdf.dll
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
 */

using System;
using System.Runtime.InteropServices;


namespace HPdf {

public enum HPdfPageLayout : uint {
    HPDF_PAGE_LAYOUT_SINGLE = 0,
    HPDF_PAGE_LAYOUT_ONE_COLUMN,
    HPDF_PAGE_LAYOUT_TWO_CLUMN_LEFT,
    HPDF_PAGE_LAYOUT_TWO_CLUMN_RIGHT,
    HPDF_PAGE_LAYOUT_EOF
};

public enum HPdfPageMode : uint {
    HPDF_PAGE_MODE_USE_NONE = 0,
    HPDF_PAGE_MODE_USE_OUTLINE,
    HPDF_PAGE_MODE_USE_THUMBS,
    HPDF_PAGE_MODE_FULL_SCREEN,
    HPDF_PAGE_MODE_EOF
};

public enum HPdfPageSizes : uint {
    HPDF_PAGE_SIZE_LETTER = 0,
    HPDF_PAGE_SIZE_LEGAL,
    HPDF_PAGE_SIZE_A3,
    HPDF_PAGE_SIZE_A4,
    HPDF_PAGE_SIZE_A5,
    HPDF_PAGE_SIZE_B4,
    HPDF_PAGE_SIZE_B5,
    HPDF_PAGE_SIZE_EXECUTIVE,
    HPDF_PAGE_SIZE_US4x6,
    HPDF_PAGE_SIZE_US4x8,
    HPDF_PAGE_SIZE_US5x7,
    HPDF_PAGE_SIZE_COMM10,
    HPDF_PAGE_SIZE_EOF
};


public enum HPdfPageDirection : uint {
    HPDF_PAGE_PORTRAIT = 0,
    HPDF_PAGE_LANDSCAPE
};


public enum HPdfPageNumStyle : uint {
    HPDF_PAGE_NUM_STYLE_DECIMAL = 0,
    HPDF_PAGE_NUM_STYLE_UPPER_ROMAN,
    HPDF_PAGE_NUM_STYLE_LOWER_ROMAN,
    HPDF_PAGE_NUM_STYLE_UPPER_LETTERS,
    HPDF_PAGE_NUM_STYLE_LOWER_LETTERS,
    HPDF_PAGE_NUM_STYLE_EOF
};

public enum HPdfWritingMode : uint {
    HPDF_WMODE_HORIZONTAL = 0,
    HPDF_WMODE_VERTICAL,
    HPDF_WMODE_EOF
};


public enum HPdfEncoderType : uint {
    HPDF_ENCODER_TYPE_SINGLE_BYTE = 0,
    HPDF_ENCODER_TYPE_DOUBLE_BYTE,
    HPDF_ENCODER_TYPE_UNINITIALIZED,
    HPDF_ENCODER_UNKNOWN
};


public enum HPdfByteType : uint {
    HPDF_BYTE_TYPE_SINGLE = 0,
    HPDF_BYTE_TYPE_LEAD,
    HPDF_BYTE_TYPE_TRIAL,
    HPDF_BYTE_TYPE_UNKNOWN
};


public enum HPdfAnnotHighlightMode : uint {
    HPDF_ANNOT_NO_HIGHTLIGHT = 0,
    HPDF_ANNOT_INVERT_BOX,
    HPDF_ANNOT_INVERT_BORDER,
    HPDF_ANNOT_DOWN_APPEARANCE,
    HPDF_ANNOT_HIGHTLIGHT_MODE_EOF
};


public enum HPdfAnnotIcon : uint {
    HPDF_ANNOT_ICON_COMMENT = 0,
    HPDF_ANNOT_ICON_KEY,
    HPDF_ANNOT_ICON_NOTE,
    HPDF_ANNOT_ICON_HELP,
    HPDF_ANNOT_ICON_NEW_PARAGRAPH,
    HPDF_ANNOT_ICON_PARAGRAPH,
    HPDF_ANNOT_ICON_INSERT,
    HPDF_ANNOT_ICON_EOF
};

public enum HPdfColorSpace : uint {
    HPDF_CS_DEVICE_GRAY = 0,
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
};


public enum HPdfInfoType : uint {
    /* date-time type parameters */
    HPDF_INFO_CREATION_DATE = 0,
    HPDF_INFO_MOD_DATE = 1,

    /* string type parameters */
    HPDF_INFO_AUTHOR = 2,
    HPDF_INFO_CREATOR = 3,
    HPDF_INFO_PRODUCER = 4,
    HPDF_INFO_TITLE = 5,
    HPDF_INFO_SUBJECT = 6,
    HPDF_INFO_KEYWORDS = 7,
    HPDF_INFO_EOF = 8
};

public enum  HPdfEncryptMode: uint {
    HPDF_ENCRYPT_R2    = 2,
    HPDF_ENCRYPT_R3    = 3
};

public enum  HPdfTextRenderingMode: uint {
    HPDF_FILL = 0,
    HPDF_STROKE = 1,
    HPDF_FILL_THEN_STROKE = 2,
    HPDF_INVISIBLE = 3,
    HPDF_FILL_CLIPPING = 4,
    HPDF_STROKE_CLIPPING = 5,
    HPDF_FILL_STROKE_CLIPPING = 6,
    HPDF_CLIPPING = 7,
    HPDF_RENDERING_MODE_EOF = 8
};

public enum HPdfLineCap {
    HPDF_BUTT_END = 0,
    HPDF_ROUND_END = 1,
    HPDF_PROJECTING_SCUARE_END = 2,
    HPDF_LINECAP_EOF = 3
};

public enum HPdfLineJoin {
    HPDF_MITER_JOIN = 0,
    HPDF_ROUND_JOIN = 1,
    HPDF_BEVEL_JOIN = 2,
    HPDF_LINEJOIN_EOF = 3
};

public enum HPdfTextAlignment {
    HPDF_TALIGN_LEFT = 0,
    HPDF_TALIGN_RIGHT = 1,
    HPDF_TALIGN_CENTER = 2,
    HPDF_TALIGN_JUSTIFY = 3
};

public enum HPdfTransitionStyle {
    HPDF_TS_WIPE_RIGHT = 0,
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
};


public enum HPdfBlendMode {
    HPDF_BM_NORMAL = 0,
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
};

[StructLayout(LayoutKind.Sequential)]
public struct HPdfRect {
    public float left;
    public float  bottom;
    public float  right;
    public float  top;
}

[StructLayout(LayoutKind.Sequential)]
public struct HPdfBox {
    public float left;
    public float  bottom;
    public float  right;
    public float  top;
}

[StructLayout(LayoutKind.Sequential)]
public struct HPdfPoint {
    public float  x;
    public float  y;
}

[StructLayout(LayoutKind.Sequential)]
public struct HPdfDate {
    public int    year;
    public int    month;
    public int    day;
    public int    hour;
    public int    minutes;
    public int    seconds;
    public char   ind;
    public int    off_hour;
    public int    off_minutes;
};

[StructLayout(LayoutKind.Sequential)]
public struct HPdfTextWidth {
    public uint numchars;

    /* don't use this value (it may be change in the feature).
       use numspace as alternated. */
    public uint numwords;

    public uint width;
    public uint numspace;
}

[StructLayout(LayoutKind.Sequential)]
public struct HPdfTransMatrix {
    public float    a;
    public float    b;
    public float    c;
    public float    d;
    public float    x;
    public float    y;
};

[StructLayout(LayoutKind.Sequential)]
public struct HPdfDashMode_Internal {
    public ushort  ptn0;
    public ushort  ptn1;
    public ushort  ptn2;
    public ushort  ptn3;
    public ushort  ptn4;
    public ushort  ptn5;
    public ushort  ptn6;
    public ushort  ptn7;
    public uint    num_ptn;
    public uint    phase;
};

public struct HPdfDashMode {
    public ushort[]  ptn;
    public uint      phase;
};

[StructLayout(LayoutKind.Sequential)]
public struct HPdfRGBColor {
    public float   r;
    public float   g;
    public float   b;
};

[StructLayout(LayoutKind.Sequential)]
public struct HPdfCMYKColor {
    public float   c;
    public float   y;
    public float   m;
    public float   k;
};


/* error handler (call back function) */
public delegate void HPDF_ErrorHandler(uint error_no, uint detail_no,
        IntPtr user_data);

public class HPdfDoc: IDisposable {
    public const int HPDF_TRUE = 1;
    public const int HPDF_FALSE = 0;
    public const uint HPDF_COMP_NONE = 0;
    public const uint HPDF_COMP_TEXT = 1;
    public const uint HPDF_COMP_IMAGE = 2;
    public const uint HPDF_COMP_METADATA = 4;
    public const uint HPDF_COMP_ALL = 15;

    public const uint HPDF_HIDE_TOOLBAR = 1;
    public const uint HPDF_HIDE_MENUBAR = 2;
    public const uint HPDF_HIDE_WINDOW_UI = 4;
    public const uint HPDF_FIT_WINDOW = 8;
    public const uint HPDF_CENTER_WINDOW = 16;

    public const uint HPDF_ENABLE_READ = 0;
    public const uint HPDF_ENABLE_PRINT = 4;
    public const uint HPDF_ENABLE_EDIT_ALL = 8;
    public const uint HPDF_ENABLE_COPY = 16;
    public const uint HPDF_ENABLE_EDIT = 32;


    [DllImport("libhpdf.dll")]
    private extern static string HPDF_GetVersion();

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_New(HPDF_ErrorHandler user_error_fn,
            IntPtr user_data);

    [DllImport("libhpdf.dll")]
    private extern static void HPDF_Free(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_NewDoc(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_FreeDoc(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_FreeDocAll(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_HasDoc(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SaveToFile(IntPtr pdf, string file_name);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_GetError(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_GetErrorDetail(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static void HPDF_ResetError(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetPagesConfiguration(IntPtr pdf,
            uint page_per_pages);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_GetPageByIndex(IntPtr pdf,
            uint index);

    [DllImport("libhpdf.dll")]
    private extern static HPdfPageLayout HPDF_GetPageLayout(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetPageLayout(IntPtr pdf,
            HPdfPageLayout layout);

    [DllImport("libhpdf.dll")]
    private extern static HPdfPageMode HPDF_GetPageMode(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetPageMode(IntPtr pdf, HPdfPageMode mode);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetOpenAction(IntPtr pdf,
            IntPtr open_action);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_GetViewerPreference(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetViewerPreference(IntPtr pdf, uint value);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_GetCurrentPage(IntPtr  pdf);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_AddPage(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_InsertPage(IntPtr pdf,
                    IntPtr  page);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_GetFont(IntPtr pdf, string font_name,
                    string encoding_name);

    [DllImport("libhpdf.dll")]
    private extern static string HPDF_LoadType1FontFromFile(IntPtr pdf,
                    string afmfilename, string pfmfilename);

    [DllImport("libhpdf.dll")]
    private extern static string HPDF_LoadTTFontFromFile(IntPtr pdf,
                    string file_name, int embedding);

    [DllImport("libhpdf.dll")]
    private extern static string HPDF_LoadTTFontFromFile2(IntPtr pdf,
                    string file_name, uint index, int embedding);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_AddPageLabel(IntPtr pdf, uint page_num,
                  HPdfPageNumStyle style, uint first_page, string prefix);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseJPFonts(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseKRFonts(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseCNSFonts(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseCNTFonts(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_CreateOutline(IntPtr pdf, IntPtr parent,
                    string title, IntPtr encoder);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_GetEncoder(IntPtr pdf,
                    string encoding_name);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_GetCurrentEncoder(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetCurrentEncoder(IntPtr pdf,
                    string encoding_name);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseJPEncodings(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseKREncodings(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseCNSEncodings(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_UseCNTEncodings(IntPtr pdf);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_LoadPngImageFromFile(IntPtr pdf,
                    string filename);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_LoadPngImageFromFile2(IntPtr pdf,
                    string filename);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_LoadJpegImageFromFile(IntPtr pdf,
                    string filename);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_LoadRawImageFromFile(IntPtr pdf,
                    string filename, uint width, uint height,
                    HPdfColorSpace color_space);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_LoadRawImageFromMem(IntPtr pdf,
                    byte[] data, int width, int height,
                    HPdfColorSpace color_space,
                    uint bits_per_component);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetInfoAttr(IntPtr pdf,
                    HPdfInfoType type, string value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetInfoDateAttr(IntPtr pdf,
                    HPdfInfoType type, HPdfDate value);

    [DllImport("libhpdf.dll")]
    private extern static string HPDF_GetInfoAttr(IntPtr pdf,
                    HPdfInfoType type);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetPassword(IntPtr pdf,
                    string owner_passwd, string user_passwd);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetPermission(IntPtr pdf,
                    uint permission);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetEncryptionMode(IntPtr pdf,
                    HPdfEncryptMode mode, uint key_len);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_SetCompressionMode(IntPtr pdf,
                    uint mode);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_CreateExtGState(IntPtr pdf);

    // handle to an instance of a HPdfDoc object.
    private IntPtr hpdf;

    public HPdfDoc() {
        HPDF_ErrorHandler error_handler =
                new HPDF_ErrorHandler(HPdfDoc.ErrorProc);
        hpdf = HPDF_New(error_handler, IntPtr.Zero);
        if (hpdf == IntPtr.Zero) {
            throw new Exception("cannot create HPdfDoc object.");
        }
    }

    void IDisposable.Dispose() {
        if (hpdf != IntPtr.Zero) {
            HPDF_Free(hpdf);
        }

        hpdf = IntPtr.Zero;
    }

    ~HPdfDoc() {
        if (hpdf != IntPtr.Zero) {
            HPDF_Free(hpdf);
        }
    }

    public static string HPdfGetVersion() {
        return HPDF_GetVersion();
    }

    public static void ErrorProc(uint error_no, uint detail_no,
            IntPtr user_data) {
        string s = "error-code=0x" + error_no.ToString("X") + " detail-code=" + detail_no;
        throw new Exception(s);
    }

    public void NewDoc() {
        HPDF_NewDoc(hpdf);
    }

    public void FreeDoc() {
        HPDF_FreeDoc(hpdf);
    }

    public void FreeDocAll() {
        HPDF_FreeDocAll(hpdf);
    }

    public bool HasDoc() {
        return (HPDF_HasDoc(hpdf) != 0);
    }

    public void SaveToFile(string file_name) {
        HPDF_SaveToFile(hpdf, file_name);
    }

    public uint GetError() {
        return HPDF_GetError(hpdf);
    }

    public uint GetErrorDetail() {
        return HPDF_GetErrorDetail(hpdf);
    }

    public void ResetError() {
        HPDF_ResetError(hpdf);
    }

    public void SetPagesConfiguration(uint page_per_pages) {
        HPDF_SetPagesConfiguration(hpdf, page_per_pages);
    }

    public HPdfPage GetPageByIndex(uint index) {
        IntPtr hpage;

        hpage = HPDF_GetPageByIndex(hpdf, index);
        return new HPdfPage(hpage);
    }

    public HPdfPageLayout GetPageLayout() {
        return HPDF_GetPageLayout(hpdf);
    }

    public void SetPageLayout(HPdfPageLayout layout) {
        HPDF_SetPageLayout(hpdf, layout);
    }

    public HPdfPageMode GetPageMode() {
        return HPDF_GetPageMode(hpdf);
    }

    public void SetPageMode(HPdfPageMode mode) {
        HPDF_SetPageMode(hpdf, mode);
    }

    public void SetOpenAction(HPdfDestination open_action) {
        if (open_action == null) {
            // ERROR!!
        } else {
            HPDF_SetOpenAction(hpdf, open_action.GetHandle());
        }
    }

    public uint GetViewerPreference() {
        return HPDF_GetViewerPreference(hpdf);
    }

    public void SetViewerPreference(uint value) {
        HPDF_SetViewerPreference(hpdf, value);
    }

    public HPdfPage GetCurrentPage() {
        IntPtr hpage;

        hpage = HPDF_GetCurrentPage(hpdf);
        return new HPdfPage(hpage);
    }

    public HPdfPage AddPage() {
        IntPtr hpage;

        hpage = HPDF_AddPage(hpdf);
        return new HPdfPage(hpage);
    }

    public HPdfPage InsertPage(HPdfPage page) {
        IntPtr hpage;

        hpage = HPDF_InsertPage(hpdf, page.GetHandle());
        return new HPdfPage(hpage);
    }

    public HPdfFont GetFont(string font_name, string encoding_name) {
        IntPtr hfont;

        hfont = HPDF_GetFont(hpdf, font_name, encoding_name);
        return new HPdfFont(hfont);
    }

    public string LoadType1FontFromFile(string afmfilename,
            string pfmfilename) {
        string font_name;

        font_name = HPDF_LoadType1FontFromFile(hpdf, afmfilename, pfmfilename);
        return font_name;
    }

    public string LoadTTFontFromFile(string file_name, bool embedding) {
        string font_name;
        int emb;

        if (embedding)
            emb = HPDF_TRUE;
        else
            emb = HPDF_FALSE;

        font_name = HPDF_LoadTTFontFromFile(hpdf, file_name, emb);
        return font_name;
    }

    public string LoadTTFontFromFile2(string file_name, uint index,
            bool embedding) {
        string font_name;
        int emb;

        if (embedding)
            emb = HPDF_TRUE;
        else
            emb = HPDF_FALSE;

        font_name = HPDF_LoadTTFontFromFile2(hpdf, file_name, index, emb);
        return font_name;
    }

    public void AddPageLabel(uint page_num, HPdfPageNumStyle style,
            uint first_page, string prefix) {
        HPDF_AddPageLabel(hpdf, page_num, style, first_page, prefix);
    }

    public uint UseJPFonts() {
        return HPDF_UseJPFonts(hpdf);
    }

    public uint UseKRFonts() {
        return HPDF_UseKRFonts(hpdf);
    }

    public uint UseCNSFonts() {
        return HPDF_UseCNSFonts(hpdf);
    }

    public uint UseCNTFonts() {
        return HPDF_UseCNTFonts(hpdf);
    }

    public HPdfOutline CreateOutline(HPdfOutline parent, string title,
            HPdfEncoder encoder) {
        IntPtr hparent;
        IntPtr hencoder;
        IntPtr houtline;

        if (encoder != null)
            hencoder = encoder.GetHandle();
        else
            hencoder = IntPtr.Zero;

        if (parent != null)
            hparent = parent.GetHandle();
        else
            hparent = IntPtr.Zero;

        houtline = HPDF_CreateOutline(hpdf, hparent, title, hencoder);
        return new HPdfOutline(houtline);
    }

    public HPdfEncoder GetEncoder(string encoding_name) {
        IntPtr hencoder;

        hencoder = HPDF_GetEncoder(hpdf, encoding_name);

        return new HPdfEncoder(hencoder);
    }

    public HPdfEncoder GetCurrentEncoder() {
        IntPtr hencoder;

        hencoder = HPDF_GetCurrentEncoder(hpdf);

        return new HPdfEncoder(hencoder);
    }

    public void SetCurrentEncoder(string encoding_name) {
        HPDF_SetCurrentEncoder(hpdf, encoding_name);
    }

    public uint UseJPEncodings() {
        return HPDF_UseJPEncodings(hpdf);
    }

    public uint UseKREncodings() {
        return HPDF_UseKREncodings(hpdf);
    }

    public uint UseCNSEncodings() {
        return HPDF_UseCNSEncodings(hpdf);
    }

    public uint UseCNTEncodings() {
        return HPDF_UseCNTEncodings(hpdf);
    }

    public HPdfImage LoadPngImageFromFile(string filename) {
        IntPtr hobj;

        hobj = HPDF_LoadPngImageFromFile(hpdf, filename);

        return new HPdfImage(hobj);
    }

    public HPdfImage LoadPngImageFromFile2(string filename) {
        IntPtr hobj;

        hobj = HPDF_LoadPngImageFromFile2(hpdf, filename);

        return new HPdfImage(hobj);
    }

    public HPdfImage LoadJpegImageFromFile(string filename) {
        IntPtr hobj;

        hobj = HPDF_LoadJpegImageFromFile(hpdf, filename);

        return new HPdfImage(hobj);
    }

    public HPdfImage LoadRawImageFromFile(string filename,
                    uint width, uint height,
                    HPdfColorSpace color_space) {
        IntPtr hobj;

        hobj = HPDF_LoadRawImageFromFile(hpdf, filename, width, height,
                    color_space);

        return new HPdfImage(hobj);
    }

    public HPdfImage LoadRawImageFromMem(byte[] data, int width, int height,
                    HPdfColorSpace color_space, uint bits_per_component) {
        if (width * height < data.Length) {
            string s = "error-code=0x1030 detail-code=0";
            throw new Exception(s);
        }
        IntPtr hobj;

        hobj = HPDF_LoadRawImageFromMem(hpdf, data, width, height, color_space,
            bits_per_component);

        return new HPdfImage(hobj);
    }

    public void SetInfoAttr(HPdfInfoType type, string value) {
        HPDF_SetInfoAttr(hpdf, type, value);
    }

    public void SetInfoDateAttr(HPdfInfoType type, HPdfDate value) {
        HPDF_SetInfoDateAttr(hpdf, type, value);
    }

    public string GetInfoAttr(HPdfInfoType type) {
        return HPDF_GetInfoAttr(hpdf, type);
    }

    public void SetPassword(string owner_passwd, string user_passwd) {
        HPDF_SetPassword(hpdf, owner_passwd, user_passwd);
    }

    public void SetPermission(uint permission) {
        HPDF_SetPermission(hpdf, permission);
    }

    public void SetEncryptionMode(HPdfEncryptMode mode, uint key_len) {
        HPDF_SetEncryptionMode(hpdf, mode, key_len);
    }

    public void SetCompressionMode(uint mode) {
        HPDF_SetCompressionMode(hpdf, mode);
    }

    public HPdfExtGState CreateExtGState() {
        IntPtr hgstate;

        hgstate = HPDF_CreateExtGState(hpdf);

        return new HPdfExtGState(hgstate);
    }
}

public class HPdfPage{
    public const int HPDF_TRUE = 1;
    public const int HPDF_FALSE = 0;

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetWidth(IntPtr page, float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetHeight(IntPtr page, float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetSize(IntPtr page,
            HPdfPageSizes size, HPdfPageDirection direction);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetRotate(IntPtr page, ushort angle);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_Page_CreateDestination(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_Page_CreateTextAnnot(IntPtr page,
        HPdfRect rect, string text, IntPtr encoder);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_Page_CreateLinkAnnot(IntPtr page,
        HPdfRect rect, IntPtr dst);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_Page_CreateURILinkAnnot(IntPtr page,
        HPdfRect rect, string url);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_TextWidth(IntPtr page,
        string text);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_MeasureText(IntPtr page,
        string text, float width, int wordwrap, ref float real_width);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetWidth(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetHeight(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static ushort HPDF_Page_GetGMode(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfPoint HPDF_Page_GetCurrentPos(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfPoint HPDF_Page_GetCurrentTextPos(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static IntPtr HPDF_Page_GetCurrentFont(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetCurrentFontSize(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfTransMatrix HPDF_Page_GetTransMatrix(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetLineWidth(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfLineCap HPDF_Page_GetLineCap(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfLineJoin HPDF_Page_GetLineJoin(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetMiterLimit(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfDashMode_Internal HPDF_Page_GetDash(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetFlat(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetCharSpace(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetWordSpace(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetHorizontalScalling(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetTextLeading(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfTextRenderingMode HPDF_Page_GetTextRenderingMode(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetTextRaise(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfRGBColor HPDF_Page_GetRGBFill(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfRGBColor HPDF_Page_GetRGBStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfCMYKColor HPDF_Page_GetCMYKFill(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfCMYKColor HPDF_Page_GetCMYKStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetGrayFill(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static float HPDF_Page_GetGrayStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfColorSpace HPDF_Page_GetStrokingColorSpace(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfColorSpace HPDF_Page_GetFillingColorSpace(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static HPdfTransMatrix HPDF_Page_GetTextMatrix(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_GetGStateDepth(IntPtr page);

/*--- General graphics state -----------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetLineWidth(IntPtr page,
                float line_width);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetLineCap(IntPtr page,
                HPdfLineCap line_cap);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetLineJoin(IntPtr page,
                HPdfLineJoin line_join);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetMiterLimit(IntPtr page,
                float miter_limit);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetDash(IntPtr page,
                ushort[] array, uint num_param, uint phase);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetFlat(IntPtr page,
                float flatness);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetExtGState(IntPtr page,
                IntPtr ext_gstate);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_GSave(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_GRestore(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Concat(IntPtr page,
            float a, float b, float c, float d, float x, float y);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_MoveTo(IntPtr page,
            float x, float y);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_LineTo(IntPtr page,
            float x, float y);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_CurveTo(IntPtr page,
            float x1, float y1, float x2, float y2, float x3, float y3);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_CurveTo2(IntPtr page,
            float x2, float y2, float x3, float y3);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_CurveTo3(IntPtr page,
            float x1, float y1, float x3, float y3);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ClosePath(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Rectangle(IntPtr page,
            float x, float y, float width, float height);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Stroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ClosePathStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Fill(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Eofill(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_FillStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_EofillStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ClosePathFillStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ClosePathEofillStroke(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_EndPath(IntPtr page);

/*--- Clipping paths operator --------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Clip(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Eoclip(IntPtr page);

/*--- Text object operator -----------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_BeginText(IntPtr page);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_EndText(IntPtr page);

/*--- Text state ---------------------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetCharSpace(IntPtr page,
                float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetWordSpace(IntPtr page,
                float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetHorizontalScalling(IntPtr page,
                float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetTextLeading(IntPtr page,
                float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetFontAndSize(IntPtr page,
                IntPtr hfont, float size);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetTextRenderingMode(IntPtr page,
                HPdfTextRenderingMode  mode);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetTextRaise(IntPtr page,
                float value);

/*--- Text positioning ---------------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_MoveTextPos(IntPtr page,
            float x, float y);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_MoveTextPos2(IntPtr page,
            float x, float y);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetTextMatrix(IntPtr page,
            float a, float b, float c, float d, float x, float y);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_MoveToNextLine(IntPtr page);

/*--- Text showing -------------------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ShowText(IntPtr page,
                string text);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ShowTextNextLine(IntPtr page,
                string text);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ShowTextNextLineEx(IntPtr page,
                float word_space, float char_space, string text);

/*--- Color showing ------------------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetGrayFill(IntPtr page,
                float gray);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetGrayStroke(IntPtr page,
                float gray);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetRGBFill(IntPtr page,
                float r, float g, float b);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetRGBStroke(IntPtr page,
                float r, float g, float b);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetCMYKFill(IntPtr page,
                float c, float m, float y, float k);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetCMYKStroke(IntPtr page,
                float c, float m, float y, float k);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_ExecuteXObject(IntPtr page,
                IntPtr obj);

/*---------------------------------------------------------------------*/

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_DrawImage(IntPtr page,
                IntPtr image, float x, float y, float width, float height);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Circle(IntPtr page,
                float x, float y, float ray);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Arc(IntPtr page,
                float x, float y, float ray, float ang1, float ang2);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_Ellipse(IntPtr page,
                float x, float y, float xray, float yray);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_TextOut(IntPtr page,
                float xpos, float ypos, string text);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_TextRect(IntPtr page,
                float left, float top, float right, float bottom,
                string text, HPdfTextAlignment align, ref uint len);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Page_SetSlideShow(IntPtr page,
                HPdfTransitionStyle type, float disp_time, float trans_time);


    // handle to an instance of a HPDF_Doc object.
    private IntPtr hpage;

    public HPdfPage(IntPtr hpage) {
        if (hpage == IntPtr.Zero) {
            throw new Exception("cannot create HPdfPage object.");
        }

        this.hpage = hpage;
    }

    public void SetWidth(float value) {
        HPDF_Page_SetWidth(hpage, value);
    }

    public void SetHeight(float value) {
        HPDF_Page_SetHeight(hpage, value);
    }

    public void SetSize(HPdfPageSizes size,
            HPdfPageDirection direction) {
        HPDF_Page_SetSize(hpage, size, direction);
    }

    public void SetRotate(ushort angle) {
        HPDF_Page_SetRotate(hpage, angle);
    }

    public HPdfDestination CreateDestination() {
        IntPtr hdest;

        hdest = HPDF_Page_CreateDestination(hpage);
        return new HPdfDestination(hdest);
    }

    public HPdfAnnotation CreateTextAnnot(HPdfRect rect, string text,
            HPdfEncoder encoder) {
        IntPtr hannot;

        hannot = HPDF_Page_CreateTextAnnot(hpage, rect, text, encoder.GetHandle());
        return new HPdfAnnotation(hannot);
    }

    public HPdfAnnotation CreateLinkAnnot(HPdfRect rect, HPdfDestination dst) {
        IntPtr hannot;

        hannot = HPDF_Page_CreateLinkAnnot(hpage, rect, dst.GetHandle());
        return new HPdfAnnotation(hannot);
    }

    public HPdfAnnotation CreateURILinkAnnot(HPdfRect rect, string uri) {
        IntPtr hannot;

        hannot = HPDF_Page_CreateURILinkAnnot(hpage, rect, uri);
        return new HPdfAnnotation(hannot);
    }


    public float TextWidth(string text) {
        return HPDF_Page_TextWidth(hpage, text);
    }

    public uint MeasureText(string text, float width, bool wordwrap,
                ref float real_width) {
        int ww;

        if (wordwrap)
            ww = HPDF_TRUE;
        else
            ww = HPDF_FALSE;

        return HPDF_Page_MeasureText(hpage, text, width, ww, ref real_width);
    }

    public uint MeasureText(string text, float width, bool wordwrap) {
        float dummy = 0;
        int ww;

        if (wordwrap)
            ww = HPDF_TRUE;
        else
            ww = HPDF_FALSE;

        return HPDF_Page_MeasureText(hpage, text, width, ww, ref dummy);
    }

    public float GetWidth() {
        return HPDF_Page_GetWidth(hpage);
    }

    public float GetHeight() {
        return HPDF_Page_GetHeight(hpage);
    }

    public ushort GetGMode() {
        return HPDF_Page_GetGMode(hpage);
    }

    public HPdfPoint GetCurrentPos() {
        return HPDF_Page_GetCurrentPos(hpage);
    }

    public HPdfPoint GetCurrentTextPos() {
        return HPDF_Page_GetCurrentTextPos(hpage);
    }

    public HPdfFont GetCurrentFont() {
        return new HPdfFont(HPDF_Page_GetCurrentFont(hpage));
    }

    public float GetCurrentFontSize() {
        return HPDF_Page_GetCurrentFontSize(hpage);
    }

    public HPdfTransMatrix GetTransMatrix() {
        return HPDF_Page_GetTransMatrix(hpage);
    }

    public float GetLineWidth() {
        return HPDF_Page_GetLineWidth(hpage);
    }

    public HPdfLineCap GetLineCap() {
        return HPDF_Page_GetLineCap(hpage);
    }

    public HPdfLineJoin GetLineJoin() {
        return HPDF_Page_GetLineJoin(hpage);
    }

    public float GetMiterLimit() {
        return HPDF_Page_GetMiterLimit(hpage);
    }

    public HPdfDashMode GetDash() {
        HPdfDashMode_Internal mode1 = HPDF_Page_GetDash(hpage);
        HPdfDashMode mode2;

        mode2.phase = mode1.phase;
        mode2.ptn = new ushort[mode1.num_ptn];

        if (mode1.num_ptn >= 1)
            mode2.ptn[0] = mode1.ptn0;

        if (mode1.num_ptn >= 2)
            mode2.ptn[1] = mode1.ptn1;

        if (mode1.num_ptn >= 3)
            mode2.ptn[2] = mode1.ptn2;

        if (mode1.num_ptn >= 4)
            mode2.ptn[3] = mode1.ptn3;

        if (mode1.num_ptn >= 5)
            mode2.ptn[4] = mode1.ptn4;

        if (mode1.num_ptn >= 6)
            mode2.ptn[5] = mode1.ptn5;

        if (mode1.num_ptn >= 7)
            mode2.ptn[6] = mode1.ptn6;

        if (mode1.num_ptn >= 8)
            mode2.ptn[7] = mode1.ptn7;

        return mode2;
    }

    public float GetFlat() {
        return HPDF_Page_GetFlat(hpage);
    }

    public float GetCharSpace() {
        return HPDF_Page_GetCharSpace(hpage);
    }

    public float GetWordSpace() {
        return HPDF_Page_GetWordSpace(hpage);
    }

    public float GetHorizontalScalling() {
        return HPDF_Page_GetHorizontalScalling(hpage);
    }

    public float GetTextLeading() {
        return HPDF_Page_GetTextLeading(hpage);
    }

    public HPdfTextRenderingMode GetTextRenderingMode() {
        return HPDF_Page_GetTextRenderingMode(hpage);
    }

    public float GetTextRaise() {
        return HPDF_Page_GetTextRaise(hpage);
    }

    public HPdfRGBColor GetRGBFill() {
        return HPDF_Page_GetRGBFill(hpage);
    }

    public HPdfRGBColor GetRGBStroke() {
        return HPDF_Page_GetRGBStroke(hpage);
    }

    public HPdfCMYKColor GetCMYKFill() {
        return HPDF_Page_GetCMYKFill(hpage);
    }

    public HPdfCMYKColor GetCMYKStroke() {
        return HPDF_Page_GetCMYKStroke(hpage);
    }

    public float GetGrayFill() {
        return HPDF_Page_GetGrayFill(hpage);
    }

    public float GetGrayStroke() {
        return HPDF_Page_GetGrayStroke(hpage);
    }

    public HPdfColorSpace GetStrokingColorSpace() {
        return HPDF_Page_GetStrokingColorSpace(hpage);
    }

    public HPdfColorSpace GetFillingColorSpace() {
        return HPDF_Page_GetFillingColorSpace(hpage);
    }

    public HPdfTransMatrix GetTextMatrix() {
        return HPDF_Page_GetTextMatrix(hpage);
    }

    public uint GetGStateDepth() {
        return HPDF_Page_GetGStateDepth(hpage);
    }

    public void SetLineWidth(float line_width) {
        HPDF_Page_SetLineWidth(hpage, line_width);
    }

    public void SetLineCap(HPdfLineCap line_cap) {
        HPDF_Page_SetLineCap(hpage, line_cap);
    }

    public void SetLineJoin(HPdfLineJoin line_join) {
        HPDF_Page_SetLineJoin(hpage, line_join);
    }

    public void SetMiterLimit(float miter_limit) {
        HPDF_Page_SetMiterLimit(hpage, miter_limit);
    }

    public void SetDash(ushort[] dash_ptn, uint phase) {
        if (dash_ptn == null) {
            HPDF_Page_SetDash(hpage, dash_ptn, 0, 0);
            return;
        }

        int len = dash_ptn.Length;

        HPDF_Page_SetDash(hpage, dash_ptn, (uint)len, phase);
    }

    public void SetFlat(float flatness) {
        HPDF_Page_SetFlat(hpage, flatness);
    }

    public void SetExtGState(HPdfExtGState gstate) {
        HPDF_Page_SetExtGState(hpage, gstate.GetHandle());
    }

    public void GSave() {
        HPDF_Page_GSave(hpage);
    }

    public void GRestore() {
        HPDF_Page_GRestore(hpage);
    }

    public void Concat(float a, float b, float c, float d, float x, float y) {
        HPDF_Page_Concat(hpage, a, b, c, d, x, y);
    }

    public void MoveTo(float x, float y) {
        HPDF_Page_MoveTo(hpage, x, y);
    }

    public void LineTo(float x, float y) {
        HPDF_Page_LineTo(hpage, x, y);
    }

    public void CurveTo(float x1, float y1, float x2, float y2,
                float x3, float y3) {
        HPDF_Page_CurveTo(hpage, x1, y1, x2, y2, x3, y3);
    }

    public void CurveTo2(float x2, float y2, float x3, float y3) {
        HPDF_Page_CurveTo2(hpage, x2, y2, x3, y3);
    }

    public void CurveTo3(float x1, float y1, float x3, float y3) {
        HPDF_Page_CurveTo2(hpage, x1, y1, x3, y3);
    }

    public void ClosePath() {
        HPDF_Page_ClosePath(hpage);
    }

    public void Rectangle(float x, float y, float width, float height) {
        HPDF_Page_Rectangle(hpage, x, y, width, height);
    }

    public void Stroke() {
        HPDF_Page_Stroke(hpage);
    }

    public void ClosePathStroke() {
        HPDF_Page_ClosePathStroke(hpage);
    }

    public void Fill() {
        HPDF_Page_Fill(hpage);
    }

    public void Eofill() {
        HPDF_Page_Eofill(hpage);
    }

    public void FillStroke() {
        HPDF_Page_FillStroke(hpage);
    }

    public void EofillStroke() {
        HPDF_Page_EofillStroke(hpage);
    }

    public void ClosePathFillStroke() {
        HPDF_Page_ClosePathFillStroke(hpage);
    }

    public void ClosePathEofillStroke() {
        HPDF_Page_ClosePathEofillStroke(hpage);
    }

    public void EndPath() {
        HPDF_Page_EndPath(hpage);
    }

    public void Clip() {
        HPDF_Page_Clip(hpage);
    }

    public void Eoclip() {
        HPDF_Page_Eoclip(hpage);
    }

    public void BeginText() {
        HPDF_Page_BeginText(hpage);
    }

    public void EndText() {
        HPDF_Page_EndText(hpage);
    }

    public void SetCharSpace(float value) {
        HPDF_Page_SetCharSpace(hpage, value);
    }

    public void SetWordSpace(float value) {
        HPDF_Page_SetWordSpace(hpage, value);
    }

    public void SetHorizontalScalling(float value) {
        HPDF_Page_SetHorizontalScalling(hpage, value);
    }

    public void SetTextLeading(float value) {
        HPDF_Page_SetTextLeading(hpage, value);
    }

    public void SetFontAndSize(HPdfFont font, float size) {
        HPDF_Page_SetFontAndSize(hpage, font.GetHandle(), size);
    }

    public void SetTextRenderingMode(HPdfTextRenderingMode  mode) {
        HPDF_Page_SetTextRenderingMode(hpage, mode);
    }

    public void SetTextRaise(float  value) {
        HPDF_Page_SetTextRaise(hpage, value);
    }

    public void MoveTextPos(float x, float y) {
        HPDF_Page_MoveTextPos(hpage, x, y);
    }

    public void MoveTextPos2(float x, float y) {
        HPDF_Page_MoveTextPos2(hpage, x, y);
    }

    public void SetTextMatrix(float a, float b, float c, float d, float x, float y) {
        HPDF_Page_SetTextMatrix(hpage, a, b, c, d, x, y);
    }

    public void MoveToNextLine() {
        HPDF_Page_MoveToNextLine(hpage);
    }

    public void ShowText(string text) {
        HPDF_Page_ShowText(hpage, text);
    }

    public void ShowTextNextLine(string text) {
        HPDF_Page_ShowTextNextLine(hpage, text);
    }

    public void ShowTextNextLineEx(float word_space, float char_space,
                string text) {
        HPDF_Page_ShowTextNextLineEx(hpage, word_space, char_space, text);
    }

    public void SetGrayFill(float gray) {
        HPDF_Page_SetGrayFill(hpage, gray);
    }

    public void SetGrayStroke(float gray) {
        HPDF_Page_SetGrayStroke(hpage, gray);
    }

    public void SetRGBFill(float r, float g, float b) {
        HPDF_Page_SetRGBFill(hpage, r, g, b);
    }

    public void SetRGBStroke(float r, float g, float b) {
        HPDF_Page_SetRGBStroke(hpage, r, g, b);
    }

    public void SetCMYKFill(float c, float m, float y, float k) {
        HPDF_Page_SetCMYKFill(hpage, c, m, y, k);
    }

    public void SetCMYKStroke(float c, float m, float y, float k) {
        HPDF_Page_SetCMYKStroke(hpage, c, m, y, k);
    }

    public void ExecuteXObject(HPdfImage xobj) {
        HPDF_Page_ExecuteXObject(hpage, xobj.GetHandle());
    }

    public void DrawImage(HPdfImage image, float x, float y,
                float width, float height) {
        HPDF_Page_DrawImage(hpage, image.GetHandle(), x, y, width, height);
    }

    public void Circle(float x, float y, float ray) {
        HPDF_Page_Circle(hpage, x, y, ray);
    }

    public void Arc(float x, float y, float ray, float ang1, float ang2) {
        HPDF_Page_Arc(hpage, x, y, ray, ang1, ang2);
    }

    public void TextOut(float xpos, float ypos, string text) {
        HPDF_Page_TextOut(hpage, xpos, ypos, text);
    }

    public void TextRect(float left, float top, float right,
                float bottom, string text, HPdfTextAlignment align,
                ref uint len) {
        HPDF_Page_TextRect(hpage, left, top, right, bottom, text, align, ref len);
    }

    public void SetSlideShow(HPdfTransitionStyle type, float disp_time,
                float trans_time) {
        HPDF_Page_SetSlideShow(hpage, type, disp_time, trans_time);
    }

    public IntPtr GetHandle() {
        return hpage;
    }
}

public class HPdfFont {
    [DllImport("libhpdf.dll")]
    private extern static string HPDF_Font_GetFontName(IntPtr hfont);

    [DllImport("libhpdf.dll")]
    private extern static string HPDF_Font_GetEncodingName(IntPtr hfont);

    [DllImport("libhpdf.dll")]
    private extern static int HPDF_Font_GetUnicodeWidth(IntPtr hfont,
            ushort code);

    [DllImport("libhpdf.dll")]
    private extern static HPdfBox HPDF_Font_GetBBox(IntPtr hfont);

    [DllImport("libhpdf.dll")]
    private extern static int HPDF_Font_GetAscent(IntPtr hfont);

    [DllImport("libhpdf.dll")]
    private extern static int HPDF_Font_GetDescent(IntPtr hfont);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Font_GetXHeight(IntPtr hfont);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Font_GetCapHeight(IntPtr hfont);

    [DllImport("libhpdf.dll")]
    private extern static HPdfTextWidth HPDF_Font_TextWidth(IntPtr hfont,
            string text, uint len);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Font_MeasureText(IntPtr hfont,
            string text, uint len, float width, float font_size,
            float char_space, float word_space, int wordwrap,
            ref float real_width);


    IntPtr hfont;

    public HPdfFont(IntPtr hfont) {
        if (hfont == IntPtr.Zero) {
            throw new Exception("cannot create HPdfFont object.");
        }

        this.hfont = hfont;
    }

    public IntPtr GetHandle() {
        return hfont;
    }

    public string GetFontName() {
        return HPDF_Font_GetFontName(hfont);
    }

    public string GetEncodingName() {
        return HPDF_Font_GetEncodingName(hfont);
    }

    public int GetUnicodeWidth(ushort code) {
        return HPDF_Font_GetUnicodeWidth(hfont, code);
    }

    public HPdfBox GetBBox() {
        return HPDF_Font_GetBBox(hfont);
    }

    public int GetAscent() {
        return HPDF_Font_GetAscent(hfont);
    }

    public int GetDescent() {
        return HPDF_Font_GetDescent(hfont);
    }

    public uint GetXHeight() {
        return HPDF_Font_GetXHeight(hfont);
    }

    public uint GetCapHeight() {
        return HPDF_Font_GetCapHeight(hfont);
    }

    public HPdfTextWidth TextWidth(string text, uint len) {
        return HPDF_Font_TextWidth(hfont, text, len);
    }

    public uint MeasureText(string text, uint len, float width,
            float font_size, float char_space, float word_space,
            int wordwrap, ref float real_width) {
        return HPDF_Font_MeasureText(hfont, text, len, width, font_size,
            char_space, word_space, wordwrap,
            ref real_width);
    }
}

public class HPdfOutline {
    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Outline_SetOpened(IntPtr houtline,
        int opened);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Outline_SetDestination(IntPtr houtline,
        IntPtr hdest);

    IntPtr houtline;

    public HPdfOutline(IntPtr houtline) {
        if (houtline == IntPtr.Zero) {
            throw new Exception("cannot create HPdfOutline object.");
        }

        this.houtline = houtline;
    }

    public IntPtr GetHandle() {
        return houtline;
    }

    public void SetOpened(bool opened) {
        int iopened;

        if (opened)
            iopened = HPdfDoc.HPDF_TRUE;
        else
            iopened = HPdfDoc.HPDF_FALSE;

        HPDF_Outline_SetOpened(houtline, iopened);
    }

    public void SetDestination(HPdfDestination dest) {
        HPDF_Outline_SetDestination(houtline, dest.GetHandle());
    }
}

public class HPdfEncoder {
    IntPtr hencoder;

    public HPdfEncoder(IntPtr hencoder) {
        if (hencoder == IntPtr.Zero) {
            throw new Exception("cannot create HPdfEncoder object.");
        }

        this.hencoder = hencoder;
    }

    [DllImport("libhpdf.dll")]
    private extern static HPdfEncoderType HPDF_Encoder_GetType(IntPtr
                hencoder);

    [DllImport("libhpdf.dll")]
    private extern static HPdfByteType HPDF_Encoder_GetByteType(IntPtr
                hencoder, string text, uint index);

    [DllImport("libhpdf.dll")]
    private extern static ushort HPDF_Encoder_GetUnicode(IntPtr
                hencoder, ushort code);

    [DllImport("libhpdf.dll")]
    private extern static HPdfWritingMode HPDF_Encoder_GetWritingMode(IntPtr
                hencoder);


    public IntPtr GetHandle() {
        return hencoder;
    }

    public HPdfEncoderType GetEncoderType() {
        return HPDF_Encoder_GetType(hencoder);
    }

    public HPdfByteType GetByteType(string text, uint index) {
        return HPDF_Encoder_GetByteType(hencoder, text, index);
    }

    public ushort GetUnicode(ushort code) {
        return HPDF_Encoder_GetUnicode(hencoder, code);
    }

    public HPdfWritingMode GetWritingMode() {
        return HPDF_Encoder_GetWritingMode(hencoder);
    }

}

public class HPdfDestination {
    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetXYZ(IntPtr hdest,
        float left, float top, float zoom);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetFit(IntPtr hdest);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetFitH(IntPtr hdest,
        float top);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetFitV(IntPtr hdest,
        float left);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetFitR(IntPtr hdest,
        float left, float bottom, float right, float top);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetFitB(IntPtr hdest);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetFitBH(IntPtr hdest,
        float top);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Destination_SetFitBV(IntPtr hdest,
        float left);

    IntPtr hdest;

    public HPdfDestination(IntPtr hdest) {
        if (hdest == IntPtr.Zero) {
            throw new Exception("cannot create HPdfDestination object.");
        }

        this.hdest = hdest;
    }

    public void SetXYZ(float left, float top, float zoom) {
        HPDF_Destination_SetXYZ(hdest, left, top, zoom);
    }

    public void SetFit() {
        HPDF_Destination_SetFit(hdest);
    }

    public void SetFitH(float top) {
        HPDF_Destination_SetFitH(hdest, top);
    }

    public void SetFitV(float left) {
        HPDF_Destination_SetFitV(hdest, left);
    }

    public void SetFitR(float left, float bottom, float right, float top) {
        HPDF_Destination_SetFitR(hdest, left, bottom, right, top);
    }

    public void SetFitB() {
        HPDF_Destination_SetFitB(hdest);
    }

    public void SetFitBH(float top) {
        HPDF_Destination_SetFitBH(hdest, top);
    }

    public void SetFitBV(float left) {
        HPDF_Destination_SetFitBV(hdest, left);
    }

    public IntPtr GetHandle() {
        return hdest;
    }
}

public class HPdfAnnotation {
    IntPtr hannot;

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_LinkAnnot_SetHighlightMode(IntPtr hannot,
        HPdfAnnotHighlightMode mode);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_LinkAnnot_SetBorderStyle(IntPtr hannot,
        float width, ushort dash_on, ushort dash_off);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_TextAnnot_SetIcon(IntPtr hannot,
        HPdfAnnotIcon icon);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_TextAnnot_SetOpened(IntPtr hannot,
        int opened);


    public HPdfAnnotation(IntPtr hannot) {
        if (hannot == IntPtr.Zero) {
            throw new Exception("cannot create HPdfAnnotation object.");
        }

        this.hannot = hannot;
    }

    public IntPtr GetHandle() {
        return hannot;
    }

    public void SetHighlightMode(HPdfAnnotHighlightMode mode) {
        HPDF_LinkAnnot_SetHighlightMode(hannot, mode);
    }

    public void SetBorderStyle(float width, ushort dash_on, ushort dash_off) {
        HPDF_LinkAnnot_SetBorderStyle(hannot, width, dash_on, dash_off);
    }

    public void SetIcon(HPdfAnnotIcon icon) {
        HPDF_TextAnnot_SetIcon(hannot, icon);
    }

    public void SetOpened(bool opened) {
        int flg;

        if (opened)
            flg = HPdfDoc.HPDF_TRUE;
        else
            flg = HPdfDoc.HPDF_FALSE;

        HPDF_TextAnnot_SetOpened(hannot, flg);
    }

}

public class HPdfXObject {
    protected IntPtr hobj;

    public HPdfXObject(IntPtr hobj) {
        if (hobj == IntPtr.Zero) {
            throw new Exception("cannot create HPdfImage object.");
        }

        this.hobj = hobj;
    }

    public IntPtr GetHandle() {
        return hobj;
    }
}

public class HPdfImage: HPdfXObject {

    [DllImport("libhpdf.dll")]
    private extern static HPdfPoint HPDF_Image_GetSize(IntPtr image);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Image_GetWidth(IntPtr image);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Image_GetHeight(IntPtr image);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Image_GetBitsPerComponent(IntPtr image);

    [DllImport("libhpdf.dll")]
    private extern static string HPDF_Image_GetColorSpace(IntPtr image);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_Image_SetColorMask(IntPtr image,
        uint rmin, uint rmax, uint gmin, uint gmax, uint bmin, uint bmax);

    [DllImport("libhpdf.dll")]
    private extern static string HPDF_Image_SetMaskImage(IntPtr image,
        IntPtr mask_image);

    public HPdfImage(IntPtr hobj): base (hobj)  {
    }

    public HPdfPoint GetSize() {
        return HPDF_Image_GetSize(hobj);
    }

    public uint GetWidth() {
        return HPDF_Image_GetWidth(hobj);
    }

    public uint GetHeight() {
        return HPDF_Image_GetHeight(hobj);
    }

    public uint GetBitsPerComponent() {
        return HPDF_Image_GetBitsPerComponent(hobj);
    }

    public string GetColorSpace() {
        return HPDF_Image_GetColorSpace(hobj);
    }

    public void SetColorMask(uint rmin, uint rmax, uint gmin, uint gmax,
            uint bmin, uint bmax) {
        HPDF_Image_SetColorMask(hobj, rmin, rmax, gmin, gmax,
            bmin, bmax);
    }

    public void SetMaskImage(HPdfImage mask_image) {
        HPDF_Image_SetMaskImage(hobj, mask_image.GetHandle());
    }
}

public class HPdfExtGState {
    protected IntPtr hgstate;

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_ExtGState_SetAlphaStroke(IntPtr gstate,
        float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_ExtGState_SetAlphaFill(IntPtr gstate,
        float value);

    [DllImport("libhpdf.dll")]
    private extern static uint HPDF_ExtGState_SetBlendMode(IntPtr gstate,
        HPdfBlendMode mode);

    public HPdfExtGState(IntPtr hgstate) {
        if (hgstate == IntPtr.Zero) {
            throw new Exception("cannot create HPdfImage object.");
        }

        this.hgstate = hgstate;
    }

    public IntPtr GetHandle() {
        return hgstate;
    }

    public void SetAlphaStroke(float value) {
        HPDF_ExtGState_SetAlphaStroke(hgstate, value);
    }

    public void SetAlphaFill(float value) {
        HPDF_ExtGState_SetAlphaFill(hgstate, value);
    }

    public void SetBlendMode(HPdfBlendMode mode) {
        HPDF_ExtGState_SetBlendMode(hgstate, mode);
    }




}

}


