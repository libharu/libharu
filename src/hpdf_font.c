/*
 * << Haru Free PDF Library >> -- hpdf_font.c
 *
 * URL: http://libharu.org
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2007-2009 Antony Dovgal <tony@daylessday.org>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#include "hpdf_conf.h"
#include "hpdf_utils.h"
#include "hpdf.h"

#ifdef LIBHPDF_ENABLE_BIDI
# include "fribidi.h"
#endif


static const HPDF_UINT8 MINBYTES[] = {
    1,
    1,
    2,
    4,
    2,
    4,
};

static HPDF_UTFBytes_Func BYTES_FNS[] = {
    NULL,
    HPDF_UTF8Bytes,
    HPDF_UTF16BEBytes,
    HPDF_UTF32BEBytes,
    HPDF_UTF16LEBytes,
    HPDF_UTF32LEBytes,
};

static HPDF_UTFToUcs4_Func TOUCS4_FNS[] = {
    NULL,
    HPDF_UTF8ToUcs4,
    HPDF_UTF16BEToUcs4,
    HPDF_UTF32BEToUcs4,
    HPDF_UTF16LEToUcs4,
    HPDF_UTF32LEToUcs4,
};

static HPDF_Ucs4ToUTF_Func UCS4TO_FNS[] = {
    NULL,
    HPDF_Ucs4ToUTF8,
    HPDF_Ucs4ToUTF16BE,
    HPDF_Ucs4ToUTF32BE,
    HPDF_Ucs4ToUTF16LE,
    HPDF_Ucs4ToUTF32LE,
};


static HPDF_BOOL
IsCIDText  (HPDF_Font font,
            HPDF_UINT index);


static HPDF_UINT
MeasureTextEx  (HPDF_Font          font,
                HPDF_REAL          width,
                HPDF_REAL          font_size,
                HPDF_REAL          char_space,
                HPDF_REAL          word_space,
                HPDF_INT           options,
                HPDF_REAL         *real_width,
                HPDF_UINT         *numtatweels);


static HPDF_BOOL
CanBreakAfter  (HPDF_UCS4 b);


static HPDF_BOOL
CanBreakBefore  (HPDF_UCS4 b);


static HPDF_UINT
GetUncovertedBytes  (HPDF_Font   font,
                     const char *text,
                     HPDF_UINT   len,
                     HPDF_UINT  *numbytes);


static HPDF_CharEnc
GetSourceCharEnc  (HPDF_Font font);


static void
SetReliefFontIndex  (HPDF_Font font);


HPDF_EXPORT(HPDF_TextWidth)
HPDF_Font_TextWidth  (HPDF_Font        font,
                      const HPDF_BYTE *text,
                      HPDF_UINT        len)
{
    HPDF_TextWidth tw = {0, 0, 0, 0};
    HPDF_FontAttr attr;
    HPDF_UINT i;
    HPDF_UCS4 b;
    HPDF_BYTE *pirf;
    HPDF_UINT bytes;

    HPDF_PTRACE ((" HPDF_Font_TextWidth\n"));

    if (!HPDF_Font_Validate(font))
        return tw;

    if (len > HPDF_LIMIT_MAX_STRING_LEN) {
        HPDF_RaiseError (font->error, HPDF_STRING_OUT_OF_RANGE, 0);
        return tw;
    }

    attr = (HPDF_FontAttr)font->attr;

    if (!attr->char_width_fn) {
        HPDF_SetError (font->error, HPDF_INVALID_OBJECT, 0);
        return tw;
    }

    if (text) {
        HPDF_Font_CheckBiDi (font, HPDF_FALSE);
        if (HPDF_Font_ConvertText (font, 0, (const char *)text, len) != HPDF_OK)
            return tw;
    } else if (attr->tw_cache.width) {
        return attr->tw_cache;
    }

    text = attr->text_cache;
    pirf = attr->text_cache + (attr->text_cache_allocated / 2);
    len  = attr->text_cache_len;
    b = 0;
    i = 0;

    while (i < len) {
        HPDF_UINT cw;

        cw = attr->char_width_fn (font, HPDF_TRUE, *pirf, text, &bytes, &b);
        tw.width += cw;

        tw.numchars++;

        if (b == 0x20 && bytes == 1 && !IsCIDText (font, *pirf)) {
            tw.numwords++;
            tw.numspace++;
        }

        pirf += bytes;
        text += bytes;
        i    += bytes;
    }

    /* 2006.08.19 add. */
    if (b == 0x20 && bytes == 1 && !IsCIDText (font, *pirf))
        ; /* do nothing. */
    else
        tw.numwords++;

    attr->tw_cache = tw;

    return tw;
}


HPDF_EXPORT(HPDF_UINT)
HPDF_Font_MeasureText (HPDF_Font          font,
                       const HPDF_BYTE   *text,
                       HPDF_UINT          len,
                       HPDF_REAL          width,
                       HPDF_REAL          font_size,
                       HPDF_REAL          char_space,
                       HPDF_REAL          word_space,
                       HPDF_INT           options,
                       HPDF_REAL         *real_width)
{
    HPDF_PTRACE ((" HPDF_Font_MeasureText\n"));

    return HPDF_Font_MeasureTextEx (font, (const char *)text, len, width,
            font_size, char_space, word_space, options, real_width,
            NULL, NULL, NULL, NULL);
}


HPDF_EXPORT(HPDF_UINT)
HPDF_Font_MeasureTextEx  (HPDF_Font          font,
                          const char        *text,
                          HPDF_UINT          len,
                          HPDF_REAL          width,
                          HPDF_REAL          font_size,
                          HPDF_REAL          char_space,
                          HPDF_REAL          word_space,
                          HPDF_INT           options,
                          HPDF_REAL         *real_width,
                          HPDF_UINT         *numbytes,
                          HPDF_UINT         *numchars,
                          HPDF_UINT         *numspaces,
                          HPDF_UINT         *numtatweels)
{
    HPDF_FontAttr attr;
    HPDF_UINT cvt_len, tmp_len, tatweels;
    HPDF_REAL rw, margin;

    HPDF_PTRACE ((" HPDF_Font_MeasureTextEx\n"));

    if (!HPDF_Font_Validate(font) || !text)
        return 0;

    if (len > HPDF_LIMIT_MAX_STRING_LEN) {
        HPDF_RaiseError (font->error, HPDF_STRING_OUT_OF_RANGE, 0);
        return 0;
    }

    attr = (HPDF_FontAttr)font->attr;

    if (!attr->char_width_fn) {
        HPDF_RaiseError (font->error, HPDF_INVALID_OBJECT, 0);
        return 0;
    }

    if (!real_width)
        real_width = &rw;
    if (!numtatweels)
        numtatweels = &tatweels;

    margin = 1.25F;             /* margin 25% */
    do { /* estimate result length and convert only the length+margin */
        if (!attr->width_per_byte) /* expect average width is missing_width/2 */
            attr->width_per_byte = (HPDF_REAL)attr->fontdef->missing_width / 2 /
                    MINBYTES[GetSourceCharEnc (font)];

        cvt_len = (HPDF_UINT)(width / font_size * 1000 / attr->width_per_byte
                * margin);
        if (len < cvt_len)
            cvt_len = len;

        if (HPDF_Font_ConvertText (font, HPDF_CONVERT_HOLD_CHARACTERS,
                text, cvt_len) != HPDF_OK)
            return 0;
        
        tmp_len = MeasureTextEx (font, width, font_size, char_space, word_space,
                options, real_width, numtatweels);
        
        if (numchars)
            *numchars = attr->tw_cache.numchars;
        if (numspaces)
            *numspaces = attr->tw_cache.numspace;

        tmp_len = GetUncovertedBytes (font, text, tmp_len, numbytes);

        if (8 < tmp_len)        /* ignore too short sample */
            attr->width_per_byte = *real_width / font_size * 1000 / tmp_len;
        margin += 0.25F;        /* margin +25% */
    } while (cvt_len <= tmp_len + 4 && cvt_len < len); /* while misestimate */

    return tmp_len;
}


static HPDF_UINT
MeasureTextEx  (HPDF_Font          font,
                HPDF_REAL          width,
                HPDF_REAL          font_size,
                HPDF_REAL          char_space,
                HPDF_REAL          word_space,
                HPDF_INT           options,
                HPDF_REAL         *real_width,
                HPDF_UINT         *numtatweels)
{
    HPDF_FontAttr attr;
    HPDF_REAL w;
    HPDF_REAL v;
    HPDF_UINT nch, nsp, ntt;
    HPDF_UINT len, tmp_len, i;
    HPDF_BOOL can_break = HPDF_FALSE;
    HPDF_BYTE *text;
    HPDF_BYTE *pirf;
    HPDF_REAL hyphen_w = 0;
    HPDF_UINT bytes;
    HPDF_UINT tw;

    HPDF_PTRACE ((" MeasureTextEx\n"));

    attr = (HPDF_FontAttr)font->attr;

    text = attr->text_cache;
    pirf = attr->text_cache + (attr->text_cache_allocated / 2);
    len  = attr->text_cache_len;
    attr->text_cache_len = 0;
    HPDF_MemSet (&attr->tw_cache, 0, sizeof attr->tw_cache);
    *real_width = 0;
    tmp_len = 0;
    nch = nsp = ntt = 0;
    tw = 0;
    w = v = 0;

    for (i = 0; i < len; i += bytes) {
        HPDF_UCS4 b;
        HPDF_REAL tmp_w;
        HPDF_INT cw;

        cw = attr->char_width_fn (font, HPDF_TRUE, pirf[i], text + i, &bytes, &b);

        if (HPDF_IS_WHITE_SPACE(b)) {
            tmp_len = i + bytes;
            attr->text_cache_len = i;
            *real_width = w;
            attr->tw_cache.width = tw;
            attr->tw_cache.numchars = nch;
            attr->tw_cache.numspace = attr->tw_cache.numwords = nsp;
            *numtatweels = ntt;

            if (width < w || b == 0x0A || b == 0x0C || b == 0x0D)
                return tmp_len;

            if (b != 0x20) {
                continue;
            } else if (bytes == 1 && !IsCIDText (font, pirf[i])) {
                nsp++;
                w += word_space;
            }
        } else if (b == 0xAD) { /* SHY */
            tmp_w = 0;
            if (options & HPDF_MEASURE_WORD_WRAP) {
                if (!hyphen_w) {
                    HPDF_BYTE hyphen[8] = {'-'};
                    if (attr->encoder->charenc != HPDF_CHARENC_UNSUPPORTED)
                        UCS4TO_FNS[attr->encoder->charenc] (hyphen, '-');
                    cw = attr->char_width_fn (font, HPDF_TRUE, 0, hyphen, 0, 0);
                    hyphen_w = (HPDF_REAL)cw * font_size / 1000;
                    hyphen_w += char_space;
                }
                tmp_w = hyphen_w;
                if (width < v + tmp_w ||
                    (!(options & HPDF_MEASURE_CAN_SHORTEN) &&
                     width < w + tmp_w))
                    return tmp_len;
            }

            tmp_len = i + bytes;
            attr->text_cache_len = i + bytes;
            *real_width = w + tmp_w;
            attr->tw_cache.width = tw + cw;
            attr->tw_cache.numchars = nch;
            attr->tw_cache.numspace = attr->tw_cache.numwords = nsp;
            *numtatweels = ntt;

            if (width < w + tmp_w)
                return tmp_len;

            continue;
        } else if (b == 0x200B) { /* ZWSP */
            tmp_len = i + bytes;
            attr->text_cache_len = i;
            *real_width = w;
            attr->tw_cache.width = tw;
            attr->tw_cache.numchars = nch;
            attr->tw_cache.numspace = attr->tw_cache.numwords = nsp;
            *numtatweels = ntt;

            if (width < w)
                return tmp_len;

            continue;
        } else if ((b <= 0x001F) ||
                   (0x007F <= b && b <= 0x009F) ||
                   (0x200C <= b && b <= 0x200F) ||
                   (0x202A <= b && b <= 0x202E) ||
                   (0xFE00 <= b && b <= 0xFE0F) ||
                   (0xFEFF == b)                ||
                   (0xFFF0 <= b && b <= 0xFFFF)) { /* control codes */
            continue;
        } else if (!(options & HPDF_MEASURE_WORD_WRAP) ||
                    (can_break && CanBreakBefore (b))) {
            tmp_len = i;
            attr->text_cache_len = i;
            *real_width = w;
            attr->tw_cache.width = tw;
            attr->tw_cache.numchars = nch;
            attr->tw_cache.numspace = attr->tw_cache.numwords = nsp;
            *numtatweels = ntt;

            if (width < w)
                return tmp_len;
        }

        if ((options & HPDF_MEASURE_WORD_WRAP) &&
            (attr->type == HPDF_FONT_TYPE0_CID ||
             attr->type == HPDF_FONT_TYPE0_TT))
            can_break = CanBreakAfter (b);

        nch++;

        tw += cw;
        tmp_w = (HPDF_REAL)cw * font_size / 1000;

        if (b == 0x0640) {      /* Arabic tatweel */
            ntt++;
            if (!(options & HPDF_MEASURE_IGNORE_TATWEEL)) {
                w += tmp_w;
                if (0 < i)
                    w += char_space;
            }
        } else {
            w += tmp_w;
            v += tmp_w;
            if (0 < i) {
                w += char_space;
                v += char_space;
            }
        }

        if (width < v || (!(options & HPDF_MEASURE_CAN_SHORTEN) && width < w))
            return tmp_len;
    }

    /* all of text can be put in the specified width */
    tmp_len = i;
    attr->text_cache_len = i;
    *real_width = w;
    attr->tw_cache.width = tw;
    attr->tw_cache.numchars = nch;
    attr->tw_cache.numspace = attr->tw_cache.numwords = nsp;
    *numtatweels = ntt;

    return tmp_len;
}


static HPDF_BOOL
CanBreakAfter  (HPDF_UCS4 b)
{
  return ((0x03000 <= b && b <= 0x03007) ||
          (0x03008 <= b && b <= 0x0301B && (b & 1)) ||
          (0x0301C == b) ||
          (0x0301E <= b && b <= 0x09FFF) ||
          (0x0AC00 <= b && b <= 0x0D7AF) ||
          (0x0F900 <= b && b <= 0x0FAFF) ||
          (0x20000 <= b && b <= 0x2FFFF));
}


static HPDF_BOOL
CanBreakBefore  (HPDF_UCS4 b)
{
    if      (0x030A1 <= b && b <= 0x030F6)
        b -= 0x030A1 - 0x03041;
    else if (0x0FF01 <= b && b <= 0x0FF5E)
        b -= 0x0FF01 - 0x00021;

    return !(('!' == b) ||
             (')' == b) ||
             (',' == b) ||
             ('-' == b) ||
             ('.' == b) ||
             (':' == b) ||
             (';' == b) ||
             ('=' == b) ||
             ('?' == b) ||
             (']' == b) ||
             ('}' == b) ||
             (0x03001 <= b && b <= 0x03005) ||
             (0x03008 <= b && b <= 0x0301B && (b & 1)) ||
             (0x0301F == b) ||
             (0x03031 <= b && b <= 0x03035) ||
             (0x03041 <= b && b <= 0x0304A && (b & 1)) ||
             (0x03063 == b) ||
             (0x03083 == b) ||
             (0x03085 == b) ||
             (0x03087 == b) ||
             (0x0308E == b) ||
             (0x03095 == b) ||
             (0x03096 == b) ||
             (0x03099 <= b && b <= 0x0309E) ||
             (0x030FB <= b && b <= 0x030FE) ||
             (0x0FF60 == b) ||
             (0x0FF61 == b) ||
             (0x0FF63 <= b && b <= 0x0FF65) ||
             (0x0FF66 <= b && b <= 0x0FF70) ||
             (0x0FF9E == b) ||
             (0x0FF9F == b));
}


HPDF_EXPORT(const char*)
HPDF_Font_GetFontName  (HPDF_Font font)
{
    HPDF_FontAttr attr;

    HPDF_PTRACE((" HPDF_Font_GetFontName\n"));

    if (!HPDF_Font_Validate(font))
        return NULL;

    attr = (HPDF_FontAttr)font->attr;

    return attr->fontdef->base_font;
}


HPDF_EXPORT(const char*)
HPDF_Font_GetEncodingName  (HPDF_Font font)
{
    HPDF_FontAttr attr;

    HPDF_PTRACE((" HPDF_Font_GetEncodingName\n"));

    if (!HPDF_Font_Validate(font))
        return NULL;

    attr = (HPDF_FontAttr)font->attr;

    return attr->encoder->name;
}


HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetUnicodeWidth  (HPDF_Font       font,
                            HPDF_UNICODE    code)
{
    HPDF_PTRACE((" HPDF_Font_GetUnicodeWidth\n"));

    return HPDF_Font_GetUcs4Width (font, code);
}


HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetUcs4Width  (HPDF_Font       font,
                         HPDF_UCS4       ucs4)
{
    HPDF_FontAttr attr;
    HPDF_FontDef fontdef;

    HPDF_PTRACE((" HPDF_Font_GetUcs4Width\n"));

    if (!HPDF_Font_Validate(font))
        return 0;

    if (!(font = HPDF_Font_GetReliefFont (font, ucs4, NULL)))
        return 0;

    attr = (HPDF_FontAttr)font->attr;
    fontdef = attr->fontdef;

    if (fontdef->type == HPDF_FONTDEF_TYPE_TYPE1) {
        return HPDF_Type1FontDef_GetWidth (fontdef, ucs4);
    } else if (fontdef->type == HPDF_FONTDEF_TYPE_TRUETYPE) {
        return HPDF_TTFontDef_GetCharWidth (fontdef, ucs4);
    } else if (fontdef->type == HPDF_FONTDEF_TYPE_CID) {
        HPDF_CID cid = HPDF_CMapEncoder_ToCID(attr->encoder, ucs4);
        if (0 < cid)
            return HPDF_CIDFontDef_GetCIDWidth (fontdef, cid);
    }

    HPDF_PTRACE((" HPDF_Font_GetUcs4Width not found (0x%08X)\n", ucs4));

    return 0;
}


HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetCharWidth  (HPDF_Font   font,
                         const char *text,
                         HPDF_UINT  *bytes,
                         HPDF_UCS4  *ucs4)
{
    HPDF_FontAttr attr;

    HPDF_PTRACE((" HPDF_Font_GetCharWidth\n"));

    if (!HPDF_Font_Validate(font) || !text)
        return 0;

    attr = (HPDF_FontAttr)font->attr;

    return attr->char_width_fn (font, HPDF_FALSE, 0, text, bytes, ucs4);
}


HPDF_EXPORT(HPDF_Box)
HPDF_Font_GetBBox  (HPDF_Font  font)
{
    HPDF_Box bbox = {0, 0, 0, 0};

    HPDF_PTRACE((" HPDF_Font_GetBBox\n"));
    if (HPDF_Font_Validate(font))
        return ((HPDF_FontAttr)font->attr)->fontdef->font_bbox;

    return bbox;
}

HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetAscent  (HPDF_Font  font)
{
    HPDF_PTRACE((" HPDF_Font_GetAscent\n"));

    if (HPDF_Font_Validate(font))
        return ((HPDF_FontAttr)font->attr)->fontdef->ascent;

    return 0;
}

HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetDescent  (HPDF_Font  font)
{
    HPDF_PTRACE((" HPDF_Font_GetDescent\n"));

    if (HPDF_Font_Validate(font))
        return ((HPDF_FontAttr)font->attr)->fontdef->descent;

    return 0;
}

HPDF_EXPORT(HPDF_UINT)
HPDF_Font_GetXHeight  (HPDF_Font  font)
{
    HPDF_PTRACE((" HPDF_Font_GetXHeight\n"));

    if (HPDF_Font_Validate(font))
        return ((HPDF_FontAttr)font->attr)->fontdef->x_height;

    return 0;
}

HPDF_EXPORT(HPDF_UINT)
HPDF_Font_GetCapHeight  (HPDF_Font  font)
{
    HPDF_PTRACE((" HPDF_Font_GetCapHeight\n"));

    if (HPDF_Font_Validate(font))
        return ((HPDF_FontAttr)font->attr)->fontdef->cap_height;

    return 0;
}


HPDF_BOOL
HPDF_Font_Validate  (HPDF_Font font)
{
    HPDF_PTRACE((" HPDF_Font_Validate\n"));

    if (!font || !font->attr || font->header.obj_class !=
            (HPDF_OSUBCLASS_FONT | HPDF_OCLASS_DICT))
        return HPDF_FALSE;

    return HPDF_TRUE;
}


static HPDF_CharEnc
GetSourceCharEnc  (HPDF_Font font)
{
    HPDF_FontAttr attr;
    HPDF_List list;
    HPDF_Converter converter;
    HPDF_CharEnc charenc;

    HPDF_PTRACE ((" GetSourceCharEnc\n"));

    attr = (HPDF_FontAttr)font->attr;
    list = attr->converters_list[attr->converters_index];

    if (list && list->count) {
        converter = (HPDF_Converter)HPDF_List_ItemAt (list, list->count - 1);
        charenc = converter->src_charenc;
    } else {
        if (!attr->text_cache)
            HPDF_NormalizeCharEnc (&attr->encoder->charenc);
        charenc = attr->encoder->charenc;
    }

    return charenc;
}


HPDF_UINT
HPDF_Font_StrLen  (HPDF_Font        font,
                   const char      *s,
                   HPDF_INT         maxlen)
{
    HPDF_INT i, min, len;

    HPDF_PTRACE ((" HPDF_Font_StrLen\n"));

    if (!s)
        return 0;

    min = MINBYTES[GetSourceCharEnc (font)];
    len = 0;
    while (maxlen < 0 || len < maxlen) {
        for (i = 0; i < min && s[i] == 0; i++)
            ;
        if (i == min)
            break;
        s   += min;
        len += min;
    }

    return (HPDF_UINT)len;
}


#ifdef LIBHPDF_ENABLE_BIDI
typedef struct _HPDF_ConverterBiDi_Rec *HPDF_ConverterBiDi;

typedef struct _HPDF_ConverterBiDi_Rec {
    HPDF_Converter_Rec            hdr;
    HPDF_ConverterBiDi_Param_Rec *par;
    HPDF_Alloc_Func               alloc_fn;
    HPDF_Free_Func                free_fn;
    HPDF_UINT                     dst_tatweels;
    HPDF_UINT                     src_tatweels;
} HPDF_ConverterBiDi_Rec;


static void
BiDi_FreeArrays  (HPDF_ConverterBiDi bidi)
{
    if (bidi->par->bidi_types)
        bidi->free_fn (bidi->par->bidi_types);
    if (bidi->par->ar_props)
        bidi->free_fn (bidi->par->ar_props);
    if (bidi->par->embedding_levels)
        bidi->free_fn (bidi->par->embedding_levels);
    if (bidi->par->positions_L_to_V)
        bidi->free_fn (bidi->par->positions_L_to_V);
    if (bidi->par->positions_V_to_L)
        bidi->free_fn (bidi->par->positions_V_to_L);

    bidi->par->bidi_types       = NULL;
    bidi->par->ar_props         = NULL;
    bidi->par->embedding_levels = NULL;
    bidi->par->positions_L_to_V = NULL;
    bidi->par->positions_V_to_L = NULL;

    bidi->par->max_chars = 0;
}


static HPDF_UINT HPDF_STDCALL 
BiDi  (HPDF_Converter   converter,
       HPDF_UINT32      flags,
       const HPDF_BYTE *src,
       HPDF_UINT        src_bytes,
       HPDF_BYTE       *dst)
{
    HPDF_ConverterBiDi bidi = (HPDF_ConverterBiDi)converter;
    const HPDF_UCS4 *s = (const HPDF_UCS4 *)src;
    HPDF_UINT len = src_bytes / sizeof (HPDF_UCS4);
    HPDF_UCS4 *d = (HPDF_UCS4 *)dst;

    if (bidi->par->max_chars < len) {
        HPDF_UINT32 max_chars = bidi->par->max_chars;
        if (!max_chars)
            max_chars = HPDF_TEXT_DEFAULT_LEN / sizeof (HPDF_UCS4);
        while (max_chars < len)
            max_chars *= 2;

        BiDi_FreeArrays (bidi);

        bidi->par->bidi_types       = bidi->alloc_fn
                (max_chars * sizeof bidi->par->bidi_types[0]);
        bidi->par->ar_props         = bidi->alloc_fn
                (max_chars * sizeof bidi->par->ar_props[0]);
        bidi->par->embedding_levels = bidi->alloc_fn
                (max_chars * sizeof bidi->par->embedding_levels[0]);
        bidi->par->positions_L_to_V = bidi->alloc_fn
                (max_chars * sizeof bidi->par->positions_L_to_V[0]);
        bidi->par->positions_V_to_L = bidi->alloc_fn
                (max_chars * sizeof bidi->par->positions_V_to_L[0]);

        if (!bidi->par->bidi_types       ||
            !bidi->par->ar_props         ||
            !bidi->par->embedding_levels ||
            !bidi->par->positions_L_to_V ||
            !bidi->par->positions_V_to_L)
            return 0;

        bidi->par->max_chars = max_chars;
    }

    fribidi_get_bidi_types (s, len, (FriBidiCharType *)bidi->par->bidi_types);
    fribidi_get_par_embedding_levels ((FriBidiCharType *)bidi->par->bidi_types,
            len, (FriBidiParType *)&bidi->par->base_dir,
            bidi->par->embedding_levels);

    HPDF_MemCpy (dst, src, src_bytes);

    /* Arabic joining */
    fribidi_get_joining_types (s, len, bidi->par->ar_props);
    fribidi_join_arabic ((FriBidiCharType *)bidi->par->bidi_types, len,
            bidi->par->embedding_levels, bidi->par->ar_props);
    fribidi_shape ((FRIBIDI_FLAGS_DEFAULT | FRIBIDI_FLAGS_ARABIC),
            bidi->par->embedding_levels, len, bidi->par->ar_props, d);

    if (!(flags & HPDF_CONVERT_HOLD_CHARACTERS)) {
        HPDF_UINT i;

        for (i = 0; i < len; i++)
            bidi->par->positions_V_to_L[i] = i;

        fribidi_reorder_line ((FRIBIDI_FLAGS_DEFAULT | FRIBIDI_FLAGS_ARABIC),
                (FriBidiCharType *)bidi->par->bidi_types, len, 0,
                (FriBidiParType)bidi->par->base_dir,
                bidi->par->embedding_levels, d,
                bidi->par->positions_V_to_L);

        if (bidi->dst_tatweels < bidi->src_tatweels) {
            s = d;
            for (i = 0; i < len; i++) {
                if (!bidi->src_tatweels || *s != 0x0640) {
                    *d++ = *s++;
                } else {
                    HPDF_UINT ntt = bidi->dst_tatweels / bidi->src_tatweels;
                    s++;
                    bidi->src_tatweels--;
                    while (ntt-- && bidi->dst_tatweels) {
                        *d++ = 0x0640;
                        bidi->dst_tatweels--;
                    }
                }
            }
            len = (HPDF_UINT)(d - (HPDF_UCS4 *)dst);
        } else if (bidi->src_tatweels < bidi->dst_tatweels) {
            s = d + len;
            len += bidi->dst_tatweels - bidi->src_tatweels;
            d += len;
            while ((HPDF_UCS4 *)dst < d) {
                if (!bidi->src_tatweels || s[-1] != 0x0640) {
                    *--d = *--s;
                } else {
                    HPDF_UINT ntt = bidi->dst_tatweels / bidi->src_tatweels;
                    --s;
                    bidi->src_tatweels--;
                    while (ntt-- && bidi->dst_tatweels &&
                            (HPDF_UCS4 *)dst < d) {
                        *--d = 0x0640;
                        bidi->dst_tatweels--;
                    }
                }
            }
        }
    }
    bidi->src_tatweels = bidi->dst_tatweels = 0;
    bidi->hdr.chars_factor = 1;

    return len * sizeof (HPDF_UCS4);
}


static void HPDF_STDCALL
BiDi_Delete  (HPDF_Converter   converter,
              HPDF_Free_Func   free_fn)
{
    HPDF_ConverterBiDi bidi = (HPDF_ConverterBiDi)converter;

    HPDF_PTRACE((" BiDi_Delete\n"));

    BiDi_FreeArrays (bidi);
    free_fn (bidi);
}


static HPDF_Converter HPDF_STDCALL
BiDi_New   (HPDF_Alloc_Func alloc_fn,
            HPDF_Free_Func  free_fn,
            void           *param)
{
    HPDF_ConverterBiDi_Param_Rec *par;
    HPDF_ConverterBiDi bidi;
    HPDF_UINT size;

    HPDF_PTRACE((" BiDi_New\n"));

    par = (HPDF_ConverterBiDi_Param_Rec *)param;
    bidi = 0;
    size = sizeof *bidi;
    if (!par)
        size += sizeof *par;
    bidi = (HPDF_ConverterBiDi)alloc_fn (size);
    if (!bidi)
        return NULL;

    HPDF_MemSet (bidi, 0, size);

    if (par) {
        HPDF_MemSet (par, 0, sizeof *par);
        bidi->par = par;
    } else {
        bidi->par = (HPDF_ConverterBiDi_Param_Rec *)(bidi + 1);
    }

    bidi->hdr.convert_fn   = BiDi;
    bidi->hdr.delete_fn    = BiDi_Delete;
    bidi->hdr.src_charenc  = HPDF_CHARENC_UCS4;
    bidi->hdr.dst_charenc  = HPDF_CHARENC_UCS4;
    bidi->hdr.bytes_factor = 1;
    bidi->hdr.chars_factor = 1;
    bidi->par->base_dir = 0x111; /* Letter strong RTL */
    bidi->alloc_fn = alloc_fn;
    bidi->free_fn  = free_fn;

    return &bidi->hdr;
}
#endif /* LIBHPDF_ENABLE_BIDI */


static HPDF_UINT HPDF_STDCALL 
EncConv  (HPDF_Converter   converter,
          HPDF_UINT32      flags,
          const HPDF_BYTE *src,
          HPDF_UINT        src_bytes,
          HPDF_BYTE       *dst)
{
    HPDF_UINT dst_bytes, bytes, i;
    HPDF_UCS4 ucs4;
    HPDF_UTFBytes_Func  bytes_fn  =  BYTES_FNS[converter->src_charenc];
    HPDF_UTFToUcs4_Func toucs4_fn = TOUCS4_FNS[converter->src_charenc];
    HPDF_Ucs4ToUTF_Func ucs4to_fn = UCS4TO_FNS[converter->dst_charenc];

    HPDF_UNUSED (flags);

    dst_bytes = 0;
    i = 0;

    while (i < src_bytes) {
        bytes = bytes_fn (src + i);
        if (src_bytes < i + bytes)
            break;
        ucs4 = toucs4_fn (src + i, bytes);
        i += bytes;
        dst_bytes += ucs4to_fn (dst + dst_bytes, ucs4);
    }

    return dst_bytes;
}


static HPDF_UINT HPDF_STDCALL 
Swap16  (HPDF_Converter   converter,
         HPDF_UINT32      flags,
         const HPDF_BYTE *src,
         HPDF_UINT        src_bytes,
         HPDF_BYTE       *dst)
{
    HPDF_INT i;

    HPDF_UNUSED (converter);
    HPDF_UNUSED (flags);

    for (i = 0; i < (HPDF_INT)src_bytes - 1; i += 2) {
        dst[i + 0] = src[i + 1];
        dst[i + 1] = src[i + 0];
    }

    return src_bytes;
}


static HPDF_UINT HPDF_STDCALL 
Swap32  (HPDF_Converter   converter,
         HPDF_UINT32      flags,
         const HPDF_BYTE *src,
         HPDF_UINT        src_bytes,
         HPDF_BYTE       *dst)
{
    HPDF_INT i;

    HPDF_UNUSED (converter);
    HPDF_UNUSED (flags);

    for (i = 0; i < (HPDF_INT)src_bytes - 3; i += 4) {
        dst[i + 0] = src[i + 3];
        dst[i + 1] = src[i + 2];
        dst[i + 2] = src[i + 1];
        dst[i + 3] = src[i + 0];
    }

    return src_bytes;
}


static HPDF_Converter_Convert_Func ENCCONV_FNS[6][6] = {
    /* dst:    UTF8     UTF16BE  UTF32BE  UTF16LE  UTF32LE */
    { NULL,    NULL,    NULL,    NULL,    NULL,    NULL,    }, /* src:    */
    { NULL,    NULL,    EncConv, EncConv, EncConv, EncConv, }, /* UTF8    */
    { NULL,    EncConv, NULL,    EncConv, Swap16,  EncConv, }, /* UTF16BE */
    { NULL,    EncConv, EncConv, NULL,    EncConv, Swap32,  }, /* UTF32BE */
    { NULL,    EncConv, Swap16,  EncConv, NULL,    EncConv, }, /* UTF16LE */
    { NULL,    EncConv, EncConv, Swap32,  EncConv, NULL,    }, /* UTF32LE */
};

static const HPDF_UINT8 ENCCONV_FCTS[6][6] = {
    /* dst:    UTF8     UTF16BE  UTF32BE  UTF16LE  UTF32LE */
    { 1,       1,       1,       1,       1,       1,       }, /* src:    */
    { 1,       1,       2,       4,       2,       4,       }, /* UTF8    */
    { 1,       2,       1,       2,       1,       2,       }, /* UTF16BE */
    { 1,       1,       1,       1,       1,       1,       }, /* UTF32BE */
    { 1,       2,       1,       2,       1,       2,       }, /* UTF16LE */
    { 1,       1,       1,       1,       1,       1,       }, /* UTF32LE */
};

static struct _HPDF_BuiltInConverter_Rec {
  char                    name[8];
  HPDF_Converter_New_Func new_fn;
} BUILTIN[] = {
#ifdef LIBHPDF_ENABLE_BIDI
    { "BiDi",    BiDi_New,    },
#endif
    { "",        NULL,        },
};

typedef struct _HPDF_ConverterEnc_Param_Rec {
    HPDF_CharEnc                src_charenc;
    HPDF_CharEnc                dst_charenc;
} HPDF_ConverterEnc_Param_Rec;


static void HPDF_STDCALL
EncConv_Delete  (HPDF_Converter   converter,
                 HPDF_Free_Func   free_fn)
{
    HPDF_PTRACE((" EncConv_Delete\n"));

    free_fn (converter);
}


static HPDF_Converter HPDF_STDCALL
EncConv_New   (HPDF_Alloc_Func alloc_fn,
               HPDF_Free_Func  free_fn,
               void           *param)
{
    HPDF_Converter converter;
    const HPDF_ConverterEnc_Param_Rec *par;

    HPDF_PTRACE((" EncConv_New\n"));

    if (!(converter = (HPDF_Converter)alloc_fn (sizeof (HPDF_Converter_Rec))))
        return NULL;

    par = (const HPDF_ConverterEnc_Param_Rec *)param;

    converter->convert_fn = ENCCONV_FNS[par->src_charenc][par->dst_charenc];
    converter->delete_fn = EncConv_Delete;
    converter->src_charenc = par->src_charenc;
    converter->dst_charenc = par->dst_charenc;
    converter->bytes_factor = ENCCONV_FCTS[par->src_charenc][par->dst_charenc];
    converter->chars_factor = 1;

    return converter;
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Font_SelectConverters  (HPDF_Font  font,
                             HPDF_INT   index)
{
    HPDF_FontAttr attr;

    HPDF_PTRACE((" HPDF_Font_SelectConverters\n"));

    if (!HPDF_Font_Validate (font))
        return HPDF_INVALID_FONT;

    if (index < 0)
        index = 0;
    else if (HPDF_MAX_CONVERTERS < index)
        index = HPDF_MAX_CONVERTERS;

    attr = (HPDF_FontAttr)font->attr;
    attr->converters_index = index;

    return HPDF_OK;
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Font_SetCharacterEncoding  (HPDF_Font     font,
                                 HPDF_CharEnc  charenc)
{
    HPDF_ConverterEnc_Param_Rec param;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Font_SetCharacterEncoding\n"));

    if (!HPDF_Font_Validate (font))
        return HPDF_INVALID_FONT;

    HPDF_NormalizeCharEnc (&charenc);
    param.src_charenc = charenc;
    param.dst_charenc = GetSourceCharEnc (font);

    if (param.src_charenc == HPDF_CHARENC_UNSUPPORTED ||
        param.dst_charenc == HPDF_CHARENC_UNSUPPORTED)
        return HPDF_RaiseError (font->error, HPDF_NOT_UTF_ENCODING, 0);

    if (param.src_charenc == param.dst_charenc)
        return HPDF_OK;

    ret = HPDF_Font_PushConverter (font, EncConv_New, &param);

    return ret;
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Font_PushConverter  (HPDF_Font                font,
                          HPDF_Converter_New_Func  new_fn,
                          void                    *param)
{
    HPDF_FontAttr attr;
    HPDF_List list;
    HPDF_Converter converter;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Font_PushConverter\n"));

    if (!HPDF_Font_Validate (font))
        return HPDF_INVALID_FONT;

    attr = (HPDF_FontAttr)font->attr;
    list = attr->converters_list[attr->converters_index];

    if (!list) {
        list = HPDF_List_New (font->mmgr, HPDF_DEF_ITEMS_PER_BLOCK);
        if (!list)
            return HPDF_CheckError (font->error);

        attr->converters_list[attr->converters_index] = list;
    }

    converter = new_fn (font->mmgr->alloc_fn, font->mmgr->free_fn, param);
    if (!converter)
        return HPDF_RaiseError (font->error, HPDF_FAILD_TO_NEW_CONVERTER, 0);

    HPDF_NormalizeCharEnc (&converter->src_charenc);
    HPDF_NormalizeCharEnc (&converter->dst_charenc);

    if ((ret = HPDF_Font_SetCharacterEncoding (font, converter->dst_charenc))
            != HPDF_OK) {
        converter->delete_fn (converter, font->mmgr->free_fn);
        return ret;
    }

    if ((ret = HPDF_List_Add (list, converter)) != HPDF_OK) {
        converter->delete_fn (converter, font->mmgr->free_fn);
        return HPDF_RaiseError (font->error, ret, 0);
    }

    return HPDF_OK;
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Font_PushBuiltInConverter  (HPDF_Font   font,
                                 const char *name,
                                 void       *param)
{
    HPDF_UINT i;

    HPDF_PTRACE((" HPDF_Font_PushBuiltInConverter\n"));

    if (!HPDF_Font_Validate (font))
        return HPDF_INVALID_FONT;

    for (i = 0; BUILTIN[i].name[0]; i++)
        if (HPDF_StrCmp (name, BUILTIN[i].name) == 0)
            break;

    if (!BUILTIN[i].name[0])
        return HPDF_RaiseError (font->error, HPDF_CONVERTER_NOT_FOUND, 0);

    return HPDF_Font_PushConverter (font, BUILTIN[i].new_fn, param);
}


void
HPDF_Font_FreeConvertersListAll (HPDF_Font font)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_INT i, j;

    HPDF_PTRACE((" HPDF_Font_FreeConvertersListAll\n"));

    if (!attr)
        return;

    if (attr->text_cache)
        HPDF_FreeMem (font->mmgr, attr->text_cache);
    attr->text_cache = NULL;
    attr->text_cache_len = 0;
    attr->text_cache_allocated = 0;
    HPDF_MemSet (&attr->tw_cache, 0, sizeof attr->tw_cache);

    for (i = 0; i <= HPDF_MAX_CONVERTERS; i++) {
        HPDF_List list = attr->converters_list[i];

        if (!list)
            continue;

        for (j = list->count - 1; 0 <= j; --j) {
            HPDF_Converter converter;
            converter = (HPDF_Converter)HPDF_List_ItemAt (list, j);
            converter->delete_fn (converter, font->mmgr->free_fn);
        }

        HPDF_List_Free (list);

        attr->converters_list[i] = NULL;
    }
}


HPDF_STATUS
HPDF_Font_ConvertText  (HPDF_Font        font,
                        HPDF_UINT32      flags,
                        const char      *text,
                        HPDF_UINT        len)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_List list;
    HPDF_Converter converter;
    HPDF_UINT bytes_factor, chars_factor, allocated, i;
    HPDF_BYTE *dst;

    HPDF_PTRACE((" HPDF_Font_ConvertText\n"));

    if (!text)
        return HPDF_OK;

    if (!attr->text_cache)
        HPDF_NormalizeCharEnc (&attr->encoder->charenc);

    attr->text_cache_len = 0;
    HPDF_MemSet (&attr->tw_cache, 0, sizeof attr->tw_cache);

    list = attr->converters_list[attr->converters_index];

    bytes_factor = 1;
    chars_factor = 1;
    if (list && list->count) {
        for (i = 0; i < (HPDF_INT)list->count; i++) {
            converter = (HPDF_Converter)HPDF_List_ItemAt (list, i);
            if (bytes_factor < converter->bytes_factor)
                bytes_factor = converter->bytes_factor;
            chars_factor *= converter->chars_factor;
        }
    }

    attr->text_cache_len = len;
    len *= bytes_factor;
    len *= chars_factor;
    len *= 2;

    allocated = attr->text_cache_allocated;
    if (!attr->text_cache_allocated)
        attr->text_cache_allocated = HPDF_TEXT_DEFAULT_LEN;
    while (attr->text_cache_allocated < len)
        attr->text_cache_allocated *= 2;
    if (attr->text_cache_allocated != allocated) {
        if (attr->text_cache)
            HPDF_FreeMem (font->mmgr, attr->text_cache);
        attr->text_cache = HPDF_GetMem (font->mmgr, attr->text_cache_allocated);
        if (!attr->text_cache)
            return HPDF_CheckError (font->error);
    }

    if (!list || list->count <= 0) {
        HPDF_MemCpy (attr->text_cache, text, attr->text_cache_len);
        text = (char *)(dst = attr->text_cache);
    } else {
        for (i = list->count; i--;) {
            dst = attr->text_cache;
            if (i & 1)
                dst += (attr->text_cache_allocated / 2);
            converter = (HPDF_Converter)HPDF_List_ItemAt (list, i);
            attr->text_cache_len = converter->convert_fn (converter, flags,
                    text, attr->text_cache_len, dst);
            text = (char *)dst;
        }
    }

    if (!(flags & HPDF_CONVERT_HOLD_CHARACTERS)) {
        HPDF_UINT bytes;
        HPDF_UCS4 b = 0;

        for (i = 0; i < attr->text_cache_len;) {
            b = HPDF_Encoder_GetUcs4 (attr->encoder, (const HPDF_BYTE *)text,
                    &bytes);
            i += bytes;
            if ((b <= 0x001F) ||
                (0x007F <= b && b <= 0x009F) ||
                (b == 0x00AD) ||
                (0x200B <= b && b <= 0x200F) ||
                (0x202A <= b && b <= 0x202E) ||
                (0xFE00 <= b && b <= 0xFE0F) ||
                (0xFEFF == b)                ||
                (0xFFF0 <= b && b <= 0xFFFF)) /* control codes */
                text += bytes;
            else
                while (bytes--)
                    *dst++ = *(const HPDF_BYTE *)text++;
        }
        if (b == 0x00AD) {
            if (attr->encoder->charenc == HPDF_CHARENC_UNSUPPORTED ||
                attr->encoder->charenc == HPDF_CHARENC_UTF8)
                *dst++ = '-';
            else
                dst += UCS4TO_FNS[attr->encoder->charenc] (dst, '-');
        }
        attr->text_cache_len = dst - attr->text_cache;
    }

    /* set relief font index */
    HPDF_MemSet (attr->text_cache + (attr->text_cache_allocated / 2),
                 0,                  attr->text_cache_allocated / 2);
    if (attr->relief_font)
        SetReliefFontIndex (font);

    return HPDF_OK;
}


static HPDF_UINT
GetUncovertedBytes  (HPDF_Font   font,
                     const char *text,
                     HPDF_UINT   len,
                     HPDF_UINT  *numbytes)
{
    HPDF_FontAttr attr;
    HPDF_CharEnc src_charenc;
    HPDF_CharEnc dst_charenc;
    HPDF_UINT i, j, tmp_len;

    attr = (HPDF_FontAttr)font->attr;
    dst_charenc = attr->encoder->charenc;

    if (dst_charenc == HPDF_CHARENC_UNSUPPORTED) {
        if (numbytes)
            *numbytes = attr->text_cache_len;
        return len;
    }

    src_charenc = GetSourceCharEnc (font);

    i = 0;
    j = 0;
    tmp_len = 0;
    while (i < len) {
        i += BYTES_FNS[dst_charenc] (attr->text_cache + i);
        j += BYTES_FNS[src_charenc] ((const HPDF_BYTE *)text + j);
        if (attr->text_cache_len == i)
            tmp_len = j;
    }

    if (numbytes)
        *numbytes = tmp_len;

    return j;
}


HPDF_BOOL
HPDF_Font_IsRtL  (HPDF_Font font)
{
    HPDF_BOOL ret = HPDF_FALSE;
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_List list = attr->converters_list[attr->converters_index];

    HPDF_PTRACE ((" HPDF_Font_IsRtL\n"));

#ifdef LIBHPDF_ENABLE_BIDI
    if (list) {
        HPDF_UINT i;
        HPDF_ConverterBiDi bidi;

        for (i = 0; i < list->count; i++) {
            bidi = (HPDF_ConverterBiDi)HPDF_List_ItemAt (list, i);
            if (bidi->hdr.convert_fn == BiDi) {
                ret = ((bidi->par->base_dir & FRIBIDI_MASK_RTL) != 0);
                break;
            }
        }
    }
#endif

    return ret;
}


void
HPDF_Font_CheckBiDi  (HPDF_Font font,
                      HPDF_BOOL even_users)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_List list = attr->converters_list[attr->converters_index];

    HPDF_PTRACE ((" HPDF_Font_CheckBiDi\n"));

#ifdef LIBHPDF_ENABLE_BIDI
    if (list) {
        HPDF_UINT i;
        HPDF_ConverterBiDi bidi;

        for (i = 0; i < list->count; i++) {
            bidi = (HPDF_ConverterBiDi)HPDF_List_ItemAt (list, i);
            if (bidi->hdr.convert_fn == BiDi) {
                if (even_users ||
                        bidi->par == (HPDF_ConverterBiDi_Param_Rec *)(bidi + 1))
                    bidi->par->base_dir = 0;
                break;
            }
        }
    }
#endif
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Font_SetTatweelCount (HPDF_Font font,
                           HPDF_UINT dst_tatweels,
                           HPDF_UINT src_tatweels,
                           HPDF_UINT numchars)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_List list = attr->converters_list[attr->converters_index];

    HPDF_PTRACE ((" HPDF_Font_SetTatweelCount\n"));

    if (!HPDF_Font_Validate (font))
        return HPDF_INVALID_FONT;

#ifdef LIBHPDF_ENABLE_BIDI
    if (list) {
        HPDF_UINT i;
        HPDF_ConverterBiDi bidi;

        for (i = 0; i < list->count; i++) {
            bidi = (HPDF_ConverterBiDi)HPDF_List_ItemAt (list, i);
            if (bidi->hdr.convert_fn == BiDi) {
                bidi->dst_tatweels = dst_tatweels;
                bidi->src_tatweels = src_tatweels;
                bidi->hdr.chars_factor = (numchars - 1 +
                        numchars + dst_tatweels - src_tatweels) / numchars;
                if (!bidi->hdr.chars_factor)
                    bidi->hdr.chars_factor = 1;
                break;
            }
        }
    }
#endif

    return HPDF_OK;
}


void
HPDF_Font_SetParseText  (HPDF_Font            font,
                         HPDF_ParseText_Rec  *state,
                         const char          *text,
                         HPDF_UINT            len)
{
    HPDF_FontAttr attr;

    HPDF_PTRACE ((" HPDF_Font_SetParseText\n"));

    attr = (HPDF_FontAttr)font->attr;
    HPDF_Encoder_SetParseText (attr->encoder, state, (const HPDF_BYTE *)text, len);

    state->charenc = GetSourceCharEnc (font);
}


HPDF_EXPORT(HPDF_ByteType)
HPDF_Font_GetByteType  (HPDF_Font     font,
                        const char   *text,
                        HPDF_UINT     index)
{
    HPDF_Encoder encoder;
    HPDF_ParseText_Rec parse_state;
    HPDF_ByteType btype;
    HPDF_UINT bytes;

    HPDF_PTRACE ((" HPDF_Font_GetByteType\n"));

    if (!HPDF_Font_Validate (font))
        return HPDF_INVALID_FONT;

    if (HPDF_Font_StrLen (font, text, index + 4) < index)
        return HPDF_BYTE_TYPE_UNKNOWN;

    encoder = ((HPDF_FontAttr)font->attr)->encoder;

    if (encoder->type != HPDF_ENCODER_TYPE_MULTI_BYTE)
        return HPDF_BYTE_TYPE_SINGLE;

    HPDF_Font_SetParseText (font, &parse_state, text, index + 4);

    for (;;) {
        btype = HPDF_CMapEncoder_ByteType (encoder, &parse_state, &bytes);

        if (index == 0)
            break;

        text++;
        index--;
    }

    return btype;
}


HPDF_EXPORT(HPDF_UCS4)
HPDF_Font_GetUcs4  (HPDF_Font   font,
                    const char *text,
                    HPDF_UINT  *bytes)
{
    HPDF_FontAttr attr;
    HPDF_CharEnc charenc;
    HPDF_UCS4 ucs4;
    HPDF_UINT tmp_bytes;

    HPDF_PTRACE ((" HPDF_Font_GetUcs4\n"));

    if (!HPDF_Font_Validate (font))
        return 0;

    attr = (HPDF_FontAttr)font->attr;

    charenc = GetSourceCharEnc (font);

    if (charenc == HPDF_CHARENC_UNSUPPORTED)
        return HPDF_Encoder_GetUcs4 (attr->encoder, (const HPDF_BYTE *)text,
                bytes);

    tmp_bytes = BYTES_FNS[charenc] ((const HPDF_BYTE *)text);
    ucs4 = TOUCS4_FNS[charenc] ((const HPDF_BYTE *)text, tmp_bytes);

    if (bytes)
        *bytes = tmp_bytes;

    return ucs4;
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Font_SetReliefFont  (HPDF_Font   font,
                          HPDF_Font   relief_font)
{
    HPDF_FontAttr attr, rf_attr;

    HPDF_PTRACE ((" HPDF_Font_SetReliefFont\n"));

    if (!HPDF_Font_Validate (font))
        return HPDF_INVALID_FONT;

    attr = (HPDF_FontAttr)font->attr;

    if (!relief_font) {
        attr->relief_font = relief_font;
        return HPDF_OK;
    }

    if (!HPDF_Font_Validate (relief_font))
        return HPDF_INVALID_FONT;

    rf_attr = (HPDF_FontAttr)relief_font->attr;

    if (attr->type == HPDF_FONT_TYPE1 ||
        rf_attr->type == HPDF_FONT_TYPE1)
        return HPDF_RaiseError (font->error,
            HPDF_UNSUPPORTED_FONT_TYPE, 0);

    if (!attr->text_cache)
        HPDF_NormalizeCharEnc (&attr->encoder->charenc);
    if (!rf_attr->text_cache)
        HPDF_NormalizeCharEnc (&rf_attr->encoder->charenc);

    if (rf_attr->encoder != attr->encoder &&
        (rf_attr->encoder->charenc == HPDF_CHARENC_UNSUPPORTED ||
         rf_attr->encoder->charenc != attr->encoder->charenc ||
         rf_attr->writing_mode     != attr->writing_mode))
        return HPDF_RaiseError (font->error,
            HPDF_UNMATCHED_RELIEF_FONT, 0);

    for (font = relief_font; font;
            font = ((HPDF_FontAttr)font->attr)->relief_font)
        if ((HPDF_FontAttr)font->attr == attr)
            return HPDF_RaiseError (font->error,
                    HPDF_LOOPED_RELIEF_FONT, 0);

    attr->relief_font = relief_font;

    return HPDF_OK;
}


HPDF_Font
HPDF_Font_GetReliefFont  (HPDF_Font  font,
                          HPDF_UCS4  ucs4,
                          HPDF_BYTE *index)
{
    HPDF_BYTE irf = 0;
    HPDF_Font rf = font;
    HPDF_FontAttr rfattr = (HPDF_FontAttr)rf->attr;

    if (rfattr->fontdef->type != HPDF_FONT_TYPE1) {
        for (; rf; rf = rfattr->relief_font, irf++) {
            rfattr = (HPDF_FontAttr)rf->attr;
            if (rfattr->fontdef->type == HPDF_FONTDEF_TYPE_CID) {
                /* cid-based font */
                if (HPDF_CMapEncoder_ToCID (rfattr->encoder, ucs4))
                    break;
            } else {
                /* unicode-based font */
                HPDF_UINT16 gid;
                HPDF_TTFontDefAttr ttattr;
                ttattr = (HPDF_TTFontDefAttr)rfattr->fontdef->attr;
                gid = HPDF_TTFontDef_GetGlyphid (rfattr->fontdef, ucs4);
                if (gid && gid < ttattr->num_glyphs)
                    break;
            }
        }
    }

    if (rf && index)
        *index = irf;

    return rf;
}


static void
SetReliefFontIndex  (HPDF_Font font)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_Encoder encoder = attr->encoder;
    HPDF_BYTE irf = 0;
    HPDF_ParseText_Rec parse_state;
    HPDF_UINT i;
    HPDF_BYTE *pirf = attr->text_cache + (attr->text_cache_allocated / 2);

    HPDF_PTRACE ((" HPDF_CIDFont_SetReliefFontIndex\n"));

    HPDF_Encoder_SetParseText (encoder, &parse_state, attr->text_cache,
            attr->text_cache_len);

    for (i = 0; i < attr->text_cache_len; i++) {
        HPDF_UINT bytes;
        HPDF_ByteType btype;
        btype = HPDF_CMapEncoder_ByteType (encoder, &parse_state, &bytes);

        if (btype != HPDF_BYTE_TYPE_TRIAL) {
            HPDF_UCS4 b = HPDF_Encoder_ToUcs4 (encoder,
                    attr->text_cache + i, bytes);

            if (!HPDF_Font_GetReliefFont (font, b, &irf))
                irf = 0xFF;
        }
        pirf[i] = irf;
    }
}


static HPDF_BOOL
IsCIDText  (HPDF_Font font,
            HPDF_UINT index)
{
    HPDF_FontAttr rfattr = (HPDF_FontAttr)font->attr;

    if (index != 0xFF)
        while (index-- && rfattr) {
            if (!(font = rfattr->relief_font))
                break;
            rfattr = (HPDF_FontAttr)font->attr;
        }

    return (rfattr->type == HPDF_FONT_TYPE0_TT &&
            !(((HPDF_TTFontDefAttr)rfattr->fontdef->attr)->options &
             HPDF_FONTOPT_WITH_CID_MAP));
}
