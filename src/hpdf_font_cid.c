/*
 * << Haru Free PDF Library >> -- hpdf_font_cid.c
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
#include "hpdf_font.h"
#include "hpdf.h"

static HPDF_Font
CIDFontType0_New (HPDF_Font parent,
                  HPDF_Xref xref);


static HPDF_Font
CIDFontType2_New (HPDF_Font parent,
                  HPDF_Xref xref);


static HPDF_INT
CharWidth  (HPDF_Font        font,
            HPDF_BOOL        converted,
            HPDF_BYTE        irf,
            const HPDF_BYTE *text,
            HPDF_UINT       *bytes,
            HPDF_UCS4       *ucs4);


static char*
CidRangeToHex  (char     *s,
                HPDF_CidRange_Rec *range,
                char     *eptr);


typedef enum _HPDF_CMapType
{
    HPDF_CMapType_CodeToCid,
    HPDF_CMapType_CodeToUnicode,
    HPDF_CMapType_CidToUnicode,
} HPDF_CMapType;


static HPDF_Dict
CreateCMap  (HPDF_Encoder   encoder,
             HPDF_Xref      xref,
             HPDF_CMapType  cmaptype);


static void
OnFree_Func  (HPDF_Dict  obj);


static HPDF_STATUS
CIDFontType2_BeforeWrite_Func  (HPDF_Dict   obj);


/*--------------------------------------------------------------------------*/

HPDF_Font
HPDF_Type0Font_New  (HPDF_MMgr        mmgr,
                     HPDF_FontDef     fontdef,
                     HPDF_Encoder     encoder,
                     HPDF_Xref        xref)
{
    HPDF_Dict font;
    HPDF_FontAttr attr;
    HPDF_CMapEncoderAttr encoder_attr;
    HPDF_TTFontDefAttr ttfontdef_attr = NULL;
    HPDF_STATUS ret = 0;
    HPDF_Array descendant_fonts;

    HPDF_PTRACE ((" HPDF_Type0Font_New\n"));

    font = HPDF_Dict_New (mmgr);
    if (!font)
        return NULL;

    font->header.obj_class |= HPDF_OSUBCLASS_FONT;

    /* check whether the fontdef object and the encoder object is valid. */
    if (encoder->type != HPDF_ENCODER_TYPE_MULTI_BYTE) {
        HPDF_SetError(font->error, HPDF_INVALID_ENCODER_TYPE, 0);
        return NULL;
    }

    if (fontdef->type != HPDF_FONTDEF_TYPE_CID &&
        fontdef->type != HPDF_FONTDEF_TYPE_TRUETYPE) {
        HPDF_SetError(font->error, HPDF_INVALID_FONTDEF_TYPE, 0);
        return NULL;
    }

    attr = HPDF_GetMem (mmgr, sizeof(HPDF_FontAttr_Rec));
    if (!attr) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    font->header.obj_class |= HPDF_OSUBCLASS_FONT;
    font->write_fn = NULL;
    font->free_fn = OnFree_Func;
    font->attr = attr;

    encoder_attr = (HPDF_CMapEncoderAttr)encoder->attr;

    HPDF_MemSet (attr, 0, sizeof(HPDF_FontAttr_Rec));

    attr->writing_mode = encoder_attr->cmap->writing_mode;
    attr->char_width_fn = CharWidth;
    attr->fontdef = fontdef;
    attr->encoder = encoder;
    attr->xref = xref;

    if (HPDF_Xref_Add (xref, font) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_AddName (font, "Type", "Font");
    ret += HPDF_Dict_AddName (font, "BaseFont", fontdef->base_font);
    ret += HPDF_Dict_AddName (font, "Subtype", "Type0");

    if (fontdef->type == HPDF_FONTDEF_TYPE_CID) {
        ret += HPDF_Dict_AddName (font, "Encoding", encoder->name);
    } else {
        ttfontdef_attr = (HPDF_TTFontDefAttr)fontdef->attr;
        if (ttfontdef_attr->options & HPDF_FONTOPT_WITHOUT_CID_MAP) {
            ret += HPDF_Dict_AddName (font, "Encoding",
                    ((attr->writing_mode == HPDF_WMODE_HORIZONTAL)?
                     "Identity-H": "Identity-V"));
        } else {
            attr->cmap_stream =
                    CreateCMap (encoder, xref, HPDF_CMapType_CodeToCid);

            if (attr->cmap_stream) {
                ret += HPDF_Dict_Add (font, "Encoding", attr->cmap_stream);
            } else
              return NULL;
        }
    }

    if (ttfontdef_attr &&
        !(ttfontdef_attr->options & HPDF_FONTOPT_WITHOUT_TOUNICODE_MAP)) {
        if (ttfontdef_attr->options & HPDF_FONTOPT_WITHOUT_CID_MAP)
            attr->to_unicode_stream =
                    CreateCMap (encoder, xref, HPDF_CMapType_CidToUnicode);
        else
            attr->to_unicode_stream =
                    CreateCMap (encoder, xref, HPDF_CMapType_CodeToUnicode);

        if (attr->to_unicode_stream) {
            ret += HPDF_Dict_Add (font, "ToUnicode", attr->to_unicode_stream);
        } else
            return NULL;
    }

    if (ret != HPDF_OK)
        return NULL;

    descendant_fonts = HPDF_Array_New (mmgr);
    if (!descendant_fonts)
        return NULL;

    if (HPDF_Dict_Add (font, "DescendantFonts", descendant_fonts) != HPDF_OK)
        return NULL;

    if (fontdef->type == HPDF_FONTDEF_TYPE_CID) {
        attr->descendant_font = CIDFontType0_New (font, xref);
        attr->type = HPDF_FONT_TYPE0_CID;
    } else {
        attr->descendant_font = CIDFontType2_New (font, xref);
        attr->type = HPDF_FONT_TYPE0_TT;
    }

    if (!attr->descendant_font)
        return NULL;
    else
        if (HPDF_Array_Add (descendant_fonts, attr->descendant_font) !=
                HPDF_OK)
            return NULL;

    return font;
}

static void
OnFree_Func  (HPDF_Dict  obj)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)obj->attr;

    HPDF_PTRACE ((" HPDF_Type0Font_OnFree\n"));

    HPDF_Font_FreeConvertersListAll ((HPDF_Font)obj);

    if (attr)
        HPDF_FreeMem (obj->mmgr, attr);
}

static HPDF_Font
CIDFontType0_New (HPDF_Font parent, HPDF_Xref xref)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_FontAttr attr = (HPDF_FontAttr)parent->attr;
    HPDF_FontDef fontdef = attr->fontdef;
    HPDF_CIDFontDefAttr fontdef_attr = (HPDF_CIDFontDefAttr)fontdef->attr;
    HPDF_Encoder encoder = attr->encoder;
    HPDF_CMapEncoderAttr encoder_attr =
                (HPDF_CMapEncoderAttr)encoder->attr;

    HPDF_CID save_cid = 0;
    HPDF_Font font;
    HPDF_Array array;
    HPDF_Array sub_array = NULL;
    HPDF_UINT i;

    HPDF_Dict descriptor;
    HPDF_Dict cid_system_info;

    HPDF_PTRACE ((" HPDF_CIDFontType0_New\n"));

    font = HPDF_Dict_New (parent->mmgr);
    if (!font)
        return NULL;

    if (HPDF_Xref_Add (xref, font) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_AddName (font, "Type", "Font");
    ret += HPDF_Dict_AddName (font, "Subtype", "CIDFontType0");
    ret += HPDF_Dict_AddNumber (font, "DW", fontdef_attr->DW);
    ret += HPDF_Dict_AddName (font, "BaseFont", fontdef->base_font);
    if (ret != HPDF_OK)
        return NULL;

    /* add 'DW2' element */
    array = HPDF_Array_New (parent->mmgr);
    if (!array)
        return NULL;

    if (HPDF_Dict_Add (font, "DW2", array) != HPDF_OK)
        return NULL;

    ret += HPDF_Array_AddNumber (array, fontdef_attr->DW2[0]);
    ret += HPDF_Array_AddNumber (array, fontdef_attr->DW2[1]);

    if (ret != HPDF_OK)
        return NULL;

    /* add 'W' element */
    array = HPDF_Array_New (parent->mmgr);
    if (!array)
        return NULL;

    if (HPDF_Dict_Add (font, "W", array) != HPDF_OK)
        return NULL;

    /* Create W array. */
    for (i = 0; i< fontdef_attr->widths->count; i++) {
        HPDF_CID_Width *w =
                (HPDF_CID_Width *)HPDF_List_ItemAt (fontdef_attr->widths, i);

        if (w->cid != save_cid + 1 || !sub_array) {
            sub_array = HPDF_Array_New (parent->mmgr);
            if (!sub_array)
                return NULL;

            ret += HPDF_Array_AddNumber (array, w->cid);
            ret += HPDF_Array_Add (array, sub_array);
        }

        ret += HPDF_Array_AddNumber (sub_array, w->width);
        save_cid = w->cid;

        if (ret != HPDF_OK)
            return NULL;
    }

    /* create descriptor */
    descriptor = HPDF_Dict_New (parent->mmgr);
    if (!descriptor)
        return NULL;

    if (HPDF_Xref_Add (xref, descriptor) != HPDF_OK)
        return NULL;

    if (HPDF_Dict_Add (font, "FontDescriptor", descriptor) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_AddName (descriptor, "Type", "FontDescriptor");
    ret += HPDF_Dict_AddName (descriptor, "FontName", fontdef->base_font);
    ret += HPDF_Dict_AddNumber (descriptor, "Ascent", fontdef->ascent);
    ret += HPDF_Dict_AddNumber (descriptor, "Descent", fontdef->descent);
    ret += HPDF_Dict_AddNumber (descriptor, "CapHeight",
                fontdef->cap_height);
    ret += HPDF_Dict_AddNumber (descriptor, "MissingWidth",
                fontdef->missing_width);
    ret += HPDF_Dict_AddNumber (descriptor, "Flags", fontdef->flags);

    if (ret != HPDF_OK)
        return NULL;

    array = HPDF_Box_Array_New (parent->mmgr, fontdef->font_bbox);
    if (!array)
        return NULL;

    ret += HPDF_Dict_Add (descriptor, "FontBBox", array);
    ret += HPDF_Dict_AddNumber (descriptor, "ItalicAngle",
            fontdef->italic_angle);
    ret += HPDF_Dict_AddNumber (descriptor, "StemV", fontdef->stemv);

    if (ret != HPDF_OK)
        return NULL;

    /* create CIDSystemInfo dictionary */
    cid_system_info = HPDF_Dict_New (parent->mmgr);
    if (!cid_system_info)
        return NULL;

    if (HPDF_Dict_Add (font, "CIDSystemInfo", cid_system_info) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_Add (cid_system_info, "Registry",
            HPDF_String_New (parent->mmgr, encoder_attr->cmap->registry, NULL));
    ret += HPDF_Dict_Add (cid_system_info, "Ordering",
            HPDF_String_New (parent->mmgr, encoder_attr->cmap->ordering, NULL));
    ret += HPDF_Dict_AddNumber (cid_system_info, "Supplement",
            encoder_attr->supplement);

    if (ret != HPDF_OK)
        return NULL;

    return font;
}

static HPDF_Font
CIDFontType2_New (HPDF_Font parent, HPDF_Xref xref)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_FontAttr attr = (HPDF_FontAttr)parent->attr;
    HPDF_FontDef fontdef = attr->fontdef;
    HPDF_TTFontDefAttr fontdef_attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_Encoder encoder = attr->encoder;
    HPDF_CMapEncoderAttr encoder_attr =
                (HPDF_CMapEncoderAttr)encoder->attr;

    HPDF_Font font;
    HPDF_Array array;
    HPDF_UINT i;
    HPDF_UNICODE tmp_map[65536];
    HPDF_Dict cid_system_info;

    HPDF_UINT16 max = 0;

    HPDF_UINT index;
    HPDF_CODE code;

    HPDF_PTRACE ((" HPDF_CIDFontType2_New\n"));

    font = HPDF_Dict_New (parent->mmgr);
    if (!font)
        return NULL;

    if (HPDF_Xref_Add (xref, font) != HPDF_OK)
        return NULL;

    parent->before_write_fn = CIDFontType2_BeforeWrite_Func;

    ret += HPDF_Dict_AddName (font, "Type", "Font");
    ret += HPDF_Dict_AddName (font, "Subtype", "CIDFontType2");
    ret += HPDF_Dict_AddNumber (font, "DW", fontdef->missing_width);
    if (ret != HPDF_OK)
        return NULL;

    /* add 'DW2' element */
    array = HPDF_Array_New (font->mmgr);
    if (!array)
        return NULL;

    if (HPDF_Dict_Add (font, "DW2", array) != HPDF_OK)
        return NULL;

    ret += HPDF_Array_AddNumber (array, (HPDF_INT32)(fontdef->font_bbox.top));
    ret += HPDF_Array_AddNumber (array, (HPDF_INT32)(fontdef->font_bbox.bottom -
                fontdef->font_bbox.top));

    HPDF_MemSet (tmp_map, 0, sizeof(HPDF_UNICODE) * 65536);

    if (ret != HPDF_OK)
        return NULL;

    index = 0;
    code = 0;
    while (0 < (i = HPDF_CMapEncoder_NextCode (encoder, &index, &code))) {
        HPDF_UCS4 ucs4 = HPDF_Encoder_CodeToUcs4 (encoder, code, i);
        HPDF_CID cid = HPDF_CMapEncoder_ToCID (encoder, ucs4);
        if (cid != 0) {
            HPDF_UINT16 gid = HPDF_TTFontDef_GetGlyphid (fontdef, ucs4);
            tmp_map[cid] = gid;
            if (max < cid)
                max = cid;
        }
    }

    if (max > 0) {
        HPDF_INT16 dw = fontdef->missing_width;
        HPDF_UNICODE *ptmp_map = tmp_map;
        HPDF_Array tmp_array = NULL;

        /* add 'W' element */
        array = HPDF_Array_New (font->mmgr);
        if (!array)
            return NULL;

        if (HPDF_Dict_Add (font, "W", array) != HPDF_OK)
            return NULL;

        for (i = 0; i < max; i++, ptmp_map++) {
            HPDF_INT w = HPDF_TTFontDef_GetGidWidth (fontdef, *ptmp_map);

            if (w != dw) {
                if (!tmp_array) {
                    if (HPDF_Array_AddNumber (array, i) != HPDF_OK)
                        return NULL;

                    tmp_array = HPDF_Array_New (font->mmgr);
                    if (!tmp_array)
                        return NULL;

                    if (HPDF_Array_Add (array, tmp_array) != HPDF_OK)
                        return NULL;
                }

                if ((ret = HPDF_Array_AddNumber (tmp_array, w)) != HPDF_OK)
                    return NULL;
            } else
                  tmp_array = NULL;
        }

        /* create "CIDToGIDMap" data */
        if (fontdef_attr->options & HPDF_FONTOPT_EMBEDDING) {
            attr->map_stream = HPDF_DictStream_New (font->mmgr, xref);
            if (!attr->map_stream)
                return NULL;

            if (HPDF_Dict_Add (font, "CIDToGIDMap", attr->map_stream) != HPDF_OK)
                return NULL;

            for (i = 0; i < max; i++) {
                HPDF_BYTE u[2];
                HPDF_UINT16 gid = tmp_map[i];

                u[0] = (HPDF_BYTE)(gid >> 8);
                u[1] = (HPDF_BYTE)gid;

                HPDF_MemCpy ((HPDF_BYTE *)(tmp_map + i), u, 2);
            }

            if ((ret = HPDF_Stream_Write (attr->map_stream->stream,
                            (HPDF_BYTE *)tmp_map, max * 2)) != HPDF_OK)
                return NULL;
        }
    } else {
        HPDF_SetError (font->error, HPDF_INVALID_FONTDEF_DATA, 0);
        return 0;
    }

    /* create CIDSystemInfo dictionary */
    cid_system_info = HPDF_Dict_New (parent->mmgr);
    if (!cid_system_info)
        return NULL;

    if (HPDF_Dict_Add (font, "CIDSystemInfo", cid_system_info) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_Add (cid_system_info, "Registry",
            HPDF_String_New (parent->mmgr, encoder_attr->cmap->registry, NULL));
    ret += HPDF_Dict_Add (cid_system_info, "Ordering",
            HPDF_String_New (parent->mmgr, encoder_attr->cmap->ordering, NULL));
    ret += HPDF_Dict_AddNumber (cid_system_info, "Supplement",
            encoder_attr->supplement);

    if (ret != HPDF_OK)
        return NULL;

    return font;
}


static HPDF_STATUS
CIDFontType2_BeforeWrite_Func  (HPDF_Dict obj)
{
    HPDF_FontAttr font_attr = (HPDF_FontAttr)obj->attr;
    HPDF_FontDef def = font_attr->fontdef;
    HPDF_TTFontDefAttr def_attr = (HPDF_TTFontDefAttr)def->attr;
    HPDF_STATUS ret = 0;

    HPDF_PTRACE ((" CIDFontType2_BeforeWrite_Func\n"));

    if (font_attr->map_stream)
        font_attr->map_stream->filter = obj->filter;

    if (font_attr->cmap_stream)
        font_attr->cmap_stream->filter = obj->filter;

    if (font_attr->to_unicode_stream)
        font_attr->to_unicode_stream->filter = obj->filter;

    if (!font_attr->fontdef->descriptor) {
        HPDF_Dict descriptor = HPDF_Dict_New (obj->mmgr);
        HPDF_Array array;

        if (!descriptor)
            return HPDF_Error_GetCode (obj->error);

        if (def_attr->options & HPDF_FONTOPT_EMBEDDING) {
            HPDF_Dict font_data = HPDF_DictStream_New (obj->mmgr,
                    font_attr->xref);

            if (!font_data)
                return HPDF_Error_GetCode (obj->error);

            if (HPDF_TTFontDef_SaveFontData (font_attr->fontdef,
                font_data->stream) != HPDF_OK)
                return HPDF_Error_GetCode (obj->error);

            ret += HPDF_Dict_Add (descriptor, "FontFile2", font_data);
            ret += HPDF_Dict_AddNumber (font_data, "Length1",
                    def_attr->length1);
            ret += HPDF_Dict_AddNumber (font_data, "Length2", 0);
            ret += HPDF_Dict_AddNumber (font_data, "Length3", 0);

            font_data->filter = obj->filter;

            if (ret != HPDF_OK)
                return HPDF_Error_GetCode (obj->error);
        }

        ret += HPDF_Xref_Add (font_attr->xref, descriptor);
        ret += HPDF_Dict_AddName (descriptor, "Type", "FontDescriptor");
        ret += HPDF_Dict_AddNumber (descriptor, "Ascent", def->ascent);
        ret += HPDF_Dict_AddNumber (descriptor, "Descent", def->descent);
        ret += HPDF_Dict_AddNumber (descriptor, "CapHeight", def->cap_height);
        ret += HPDF_Dict_AddNumber (descriptor, "Flags", def->flags);

        array = HPDF_Box_Array_New (obj->mmgr, def->font_bbox);
        ret += HPDF_Dict_Add (descriptor, "FontBBox", array);

        ret += HPDF_Dict_AddName (descriptor, "FontName", def_attr->base_font);
        ret += HPDF_Dict_AddNumber (descriptor, "ItalicAngle",
                def->italic_angle);
        ret += HPDF_Dict_AddNumber (descriptor, "StemV", def->stemv);
        ret += HPDF_Dict_AddNumber (descriptor, "XHeight", def->x_height);

        if (ret != HPDF_OK)
            return HPDF_Error_GetCode (obj->error);

        font_attr->fontdef->descriptor = descriptor;
    }

    if ((ret = HPDF_Dict_AddName (obj, "BaseFont",
                def_attr->base_font)) != HPDF_OK)
        return ret;

    if ((ret = HPDF_Dict_AddName (font_attr->descendant_font, "BaseFont",
                def_attr->base_font)) != HPDF_OK)
        return ret;

    return HPDF_Dict_Add (font_attr->descendant_font, "FontDescriptor",
                font_attr->fontdef->descriptor);
}


static HPDF_INT
CharWidth  (HPDF_Font        font,
            HPDF_BOOL        converted,
            HPDF_BYTE        irf,
            const HPDF_BYTE *text,
            HPDF_UINT       *bytes,
            HPDF_UCS4       *ucs4)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_UCS4 code;
    HPDF_UINT w;

    if (converted) {
        code = HPDF_Encoder_GetUcs4 (attr->encoder, text, bytes);
        while (irf-- && font)
            font = ((HPDF_FontAttr)font->attr)->relief_font;
    } else {
        code = HPDF_Font_GetUcs4 (font, (const char *)text, bytes);
        font = HPDF_Font_GetReliefFont (font, code, NULL);
    }

    if (ucs4)
        *ucs4 = code;

    if (!font)
        return attr->fontdef->missing_width;

    attr = (HPDF_FontAttr)font->attr;

    if (attr->writing_mode == HPDF_WMODE_HORIZONTAL) {
        if (attr->fontdef->type == HPDF_FONTDEF_TYPE_CID) {
            /* cid-based font */
            HPDF_CID cid = HPDF_CMapEncoder_ToCID (attr->encoder, code);
            w = HPDF_CIDFontDef_GetCIDWidth (attr->fontdef, cid);
        } else {
            /* unicode-based font */
            w = HPDF_TTFontDef_GetCharWidth (attr->fontdef, code);
        }
    } else {
        HPDF_INT dw2;
        if (attr->fontdef->type == HPDF_FONTDEF_TYPE_CID) {
            HPDF_CIDFontDefAttr cid_fontdef_attr =
                        (HPDF_CIDFontDefAttr)attr->fontdef->attr;
            dw2 = cid_fontdef_attr->DW2[1];
        } else {
            dw2 = (HPDF_INT)(attr->fontdef->font_bbox.bottom -
                        attr->fontdef->font_bbox.top);
        }
        w = -dw2;
    }

    return w;
}


static char
ToHex(HPDF_BYTE b)
{
    char c = (char)b;
    if (c <= 9)
        c += 0x30;
    else
        c += 0x41 - 10;
    return c;
}


static char*
CidRangeToHex  (char     *s,
                HPDF_CidRange_Rec *range,
                char     *eptr)
{
    HPDF_INT i;

    if (eptr - s < range->bytes * 4 + 6)
        return s;

    *s++ = '<';
    i = range->bytes;
    while (0 <= --i) {
        HPDF_BYTE b = (HPDF_BYTE)(range->from >> (i * 8));
        *s++ = ToHex(b >> 4);
        *s++ = ToHex(b & 0x0F);
    }
    *s++ = '>';

    *s++ = ' ';

    *s++ = '<';
    i = range->bytes;
    while (0 <= --i) {
        HPDF_BYTE b = (HPDF_BYTE)(range->to >> (i * 8));
        *s++ = ToHex(b >> 4);
        *s++ = ToHex(b & 0x0F);
    }
    *s++ = '>';

    *s = 0;

    return s;
}


static char*
Ucs4ToUtf16Hex  (char     *s,
                 HPDF_UCS4 ucs4,
                 char     *eptr)
{
    HPDF_BYTE buf[4];
    HPDF_UINT i;
    HPDF_UINT bytes = HPDF_Ucs4ToUTF16BE(buf, ucs4);

    for (i = 0; i < bytes && s + 3 < eptr; i++) {
        *s++ = ToHex(buf[i] >> 4);
        *s++ = ToHex(buf[i] & 0x0F);
    }

    *s = 0;

    return s;
}


static HPDF_Dict
CreateCMap  (HPDF_Encoder   encoder,
             HPDF_Xref      xref,
             HPDF_CMapType  cmaptype)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_Dict cmap = HPDF_DictStream_New (encoder->mmgr, xref);
    HPDF_CMapEncoderAttr attr = (HPDF_CMapEncoderAttr)encoder->attr;
    char buf[4096];
    char *pbuf;
    char *eptr = buf + sizeof buf - 1;
    HPDF_UINT i;
    HPDF_Dict sysinfo;
    HPDF_CidRange_Rec *range, tmp_range;
    HPDF_UINT n, index;
    HPDF_CODE prev_key, key;
    HPDF_CODE prev_target, target, range_target;
    const char *beginrange, *endrange;

    if (!cmap)
        return NULL;

    ret += HPDF_Dict_AddName (cmap, "Type", "CMap");
    ret += HPDF_Dict_AddName (cmap, "CMapName", encoder->name);

    sysinfo = HPDF_Dict_New (encoder->mmgr);
    if (!sysinfo)
        return NULL;

    if (HPDF_Dict_Add (cmap, "CIDSystemInfo", sysinfo) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_Add (sysinfo, "Registry", HPDF_String_New (encoder->mmgr,
                    attr->cmap->registry, NULL));
    ret += HPDF_Dict_Add (sysinfo, "Ordering", HPDF_String_New (encoder->mmgr,
                    attr->cmap->ordering, NULL));
    ret += HPDF_Dict_AddNumber (sysinfo, "Supplement", attr->supplement);
    ret += HPDF_Dict_AddNumber (cmap, "WMode",
                    (HPDF_UINT32)attr->cmap->writing_mode);

    /* create cmap data from encoding data */
    ret += HPDF_Stream_WriteStr (cmap->stream,
                "%!PS-Adobe-3.0 Resource-CMap\r\n");
    ret += HPDF_Stream_WriteStr (cmap->stream,
                "%%DocumentNeededResources: ProcSet (CIDInit)\r\n");
    ret += HPDF_Stream_WriteStr (cmap->stream,
                "%%IncludeResource: ProcSet (CIDInit)\r\n");

    pbuf = (char *)HPDF_StrCpy (buf, "%%BeginResource: CMap (", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, encoder->name, eptr);
    HPDF_StrCpy (pbuf, ")\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    pbuf = (char *)HPDF_StrCpy (buf, "%%Title: (", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, encoder->name, eptr);
    *pbuf++ = ' ';
    pbuf = (char *)HPDF_StrCpy (pbuf, attr->cmap->registry, eptr);
    *pbuf++ = ' ';
    pbuf = (char *)HPDF_StrCpy (pbuf, attr->cmap->ordering, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_IToA (pbuf, attr->supplement, eptr);
    HPDF_StrCpy (pbuf, ")\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    ret += HPDF_Stream_WriteStr (cmap->stream, "%%Version: 1.0\r\n");
    ret += HPDF_Stream_WriteStr (cmap->stream, "%%EndComments\r\n");

    ret += HPDF_Stream_WriteStr (cmap->stream,
                "/CIDInit /ProcSet findresource begin\r\n\r\n");

    /* Adobe CMap and CIDFont Files Specification recommends to allocate
     * five more elements to this dictionary than existing elements.
     */
    ret += HPDF_Stream_WriteStr (cmap->stream, "12 dict begin\r\n\r\n");

    ret += HPDF_Stream_WriteStr (cmap->stream, "begincmap\r\n\r\n");
    ret += HPDF_Stream_WriteStr (cmap->stream,
                "/CIDSystemInfo 3 dict dup begin\r\n");

    pbuf = (char *)HPDF_StrCpy (buf, "  /Registry (", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, attr->cmap->registry, eptr);
    HPDF_StrCpy (pbuf, ") def\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    pbuf = (char *)HPDF_StrCpy (buf, "  /Ordering (", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, attr->cmap->ordering, eptr);
    HPDF_StrCpy (pbuf, ") def\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    pbuf = (char *)HPDF_StrCpy (buf, "  /Supplement ", eptr);
    pbuf = HPDF_IToA (pbuf, attr->supplement, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " def\r\n", eptr);
    HPDF_StrCpy (pbuf, "end def\r\n\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    pbuf = (char *)HPDF_StrCpy (buf, "/CMapName /", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, encoder->name, eptr);
    HPDF_StrCpy (pbuf, " def\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    ret += HPDF_Stream_WriteStr (cmap->stream, "/CMapVersion 1.0 def\r\n");
    if (cmaptype == HPDF_CMapType_CodeToCid) {
        ret += HPDF_Stream_WriteStr (cmap->stream, "/CMapType 1 def\r\n\r\n");

        if (attr->uid_offset >= 0) {
            pbuf = (char *)HPDF_StrCpy (buf, "/UIDOffset ", eptr);
            pbuf = HPDF_IToA (pbuf, attr->uid_offset, eptr);
            HPDF_StrCpy (pbuf, " def\r\n\r\n", eptr);
            ret += HPDF_Stream_WriteStr (cmap->stream, buf);
        }

        if (attr->xuid[0] || attr->xuid[1] || attr->xuid[2]) {
            pbuf = (char *)HPDF_StrCpy (buf, "/XUID [", eptr);
            pbuf = HPDF_IToA (pbuf, attr->xuid[0], eptr);
            *pbuf++ = ' ';
            pbuf = HPDF_IToA (pbuf, attr->xuid[1], eptr);
            *pbuf++ = ' ';
            pbuf = HPDF_IToA (pbuf, attr->xuid[2], eptr);
            HPDF_StrCpy (pbuf, "] def\r\n\r\n", eptr);
            ret += HPDF_Stream_WriteStr (cmap->stream, buf);
        }
    } else {
        ret += HPDF_Stream_WriteStr (cmap->stream, "/CMapType 2 def\r\n\r\n");
    }

    pbuf = (char *)HPDF_StrCpy (buf, "/WMode ", eptr);
    pbuf = HPDF_IToA (pbuf, (HPDF_UINT32)attr->cmap->writing_mode, eptr);
    HPDF_StrCpy (pbuf, " def\r\n\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    /* add code-space-range */
    if (cmaptype == HPDF_CMapType_CidToUnicode)
        n = 1;
    else
        n = attr->code_space_range->count;
    pbuf = HPDF_IToA (buf, n, eptr);
    HPDF_StrCpy (pbuf, " begincodespacerange\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    for (i = 0; i < n; i++) {
        if (cmaptype == HPDF_CMapType_CidToUnicode) {
            range = &tmp_range;
            range->from  = 0;
            range->to    = 0xFFFF;
            range->bytes = 2;
        } else {
            range = HPDF_List_ItemAt (attr->code_space_range, i);
        }

        pbuf = CidRangeToHex (buf, range, eptr);
        HPDF_StrCpy (pbuf, "\r\n", eptr);

        ret += HPDF_Stream_WriteStr (cmap->stream, buf);

        if (ret != HPDF_OK)
          return NULL;
    }

    HPDF_StrCpy (buf, "endcodespacerange\r\n\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);
    if (ret != HPDF_OK)
        return NULL;

    if (cmaptype == HPDF_CMapType_CodeToCid) {
        /* add not-def-range */
        pbuf = HPDF_IToA (buf, attr->notdef_range->count, eptr);
        HPDF_StrCpy (pbuf, " beginnotdefrange\r\n", eptr);
        ret += HPDF_Stream_WriteStr (cmap->stream, buf);

        for (i = 0; i < attr->notdef_range->count; i++) {
            range = HPDF_List_ItemAt (attr->notdef_range, i);

            pbuf = CidRangeToHex (buf, range, eptr);
            *pbuf++ = ' ';
            pbuf = HPDF_IToA (pbuf, range->cid, eptr);
            HPDF_StrCpy (pbuf, "\r\n", eptr);

            ret += HPDF_Stream_WriteStr (cmap->stream, buf);

            if (ret != HPDF_OK)
                return NULL;
        }

        HPDF_StrCpy (buf, "endnotdefrange\r\n\r\n", eptr);
        ret += HPDF_Stream_WriteStr (cmap->stream, buf);
        if (ret != HPDF_OK)
            return NULL;
    }

    /* add cid-range */
    i = 0;
    range = &tmp_range;
    range->from = 0;
    index = 0;
    prev_key = key = 0;
    prev_target = range_target = 0;
    if (cmaptype == HPDF_CMapType_CodeToCid) {
        beginrange = "100 begincidrange\r\n";
        endrange = "endcidrange\r\n";
    } else {
        beginrange = "100 beginbfrange\r\n";
        endrange = "endbfrange\r\n";
    }
    pbuf = (char *)HPDF_StrCpy (buf, beginrange, eptr);
    if (cmaptype == HPDF_CMapType_CidToUnicode) {
        HPDF_UCS4 tmp_map[65536];
        HPDF_MemSet (tmp_map, 0, sizeof(HPDF_UCS4) * 65536);
        while (0 < (n = HPDF_CMapEncoder_NextCode (encoder, &index, &key))) {
            HPDF_CID cid;
            target = HPDF_Encoder_CodeToUcs4 (encoder, key, n);
            cid = HPDF_CMapEncoder_ToCID (encoder, target);
            if (cid)
                tmp_map[cid] = target;
        }

        i = 0;
        range->bytes = 2;
        for (key = 1; key <= 0xFFFF; key++) {
            target = tmp_map[key];
            if (range && (! target || target != prev_target + 1 ||
                          ((n & 0xFF00) != (prev_key & 0xFF00) &&
                           (range->from & 0xFF)))) {
                range->to = prev_key;
                if ((range->from != 0 || range->to != 0 || range_target != 0) &&
                    (range_target <= 0xFFFF ||
                     HPDF_VER_16 <= attr->cmap->pdf_version)) {
                    pbuf = CidRangeToHex (pbuf, range, eptr);

                    *pbuf++ = ' ';
                    *pbuf++ = '<';
                    pbuf = Ucs4ToUtf16Hex(pbuf, range_target, eptr);
                    *pbuf++ = '>';
                    pbuf = (char *)HPDF_StrCpy (pbuf, "\r\n", eptr);

                    if (++i == 100) {
                        HPDF_StrCpy (pbuf, endrange, eptr);
                        ret += HPDF_Stream_WriteStr (cmap->stream, buf);
                        i = 0;
                    }
                }
                range = 0;
            }

            if (! range && target) {
                range = &tmp_range;
                range->from  = key;
                range_target = target;

                if (i == 0)
                    pbuf = (char *)HPDF_StrCpy (buf, beginrange, eptr);
            }

            prev_key    = key;
            prev_target = target;
        }
    } else {
        range->bytes = -1;
        while (0 < (n = HPDF_CMapEncoder_NextCode (encoder, &index, &key))) {
            HPDF_UCS4 ucs4 = HPDF_Encoder_CodeToUcs4 (encoder, key, n);
            HPDF_CID cid = HPDF_CMapEncoder_ToCID (encoder, ucs4);
            if (cmaptype == HPDF_CMapType_CodeToCid)
                target = cid;
            else
                target = (cid? ucs4: 0);

            if (range && range->bytes == -1)
                range->bytes = n;

            if (range &&
                (! target || key != prev_key + 1 || target != prev_target + 1 ||
                 ((key & 0xFFFFFF00) != (prev_key & 0xFFFFFF00) &&
                  (range->from & 0xFF)))) {
                range->to = prev_key;
                if ((range->from != 0 || range->to != 0 || range_target != 0) &&
                    (range_target <= 0xFFFF ||
                     HPDF_VER_16 <= attr->cmap->pdf_version)) {
                    pbuf = CidRangeToHex (pbuf, range, eptr);

                    *pbuf++ = ' ';

                    if (cmaptype == HPDF_CMapType_CodeToCid) {
                        pbuf = HPDF_IToA (pbuf, range_target, eptr);
                    } else {
                        *pbuf++ = '<';
                        pbuf = Ucs4ToUtf16Hex(pbuf, range_target, eptr);
                        *pbuf++ = '>';
                    }
                    pbuf = (char *)HPDF_StrCpy (pbuf, "\r\n", eptr);

                    if (++i == 100) {
                        HPDF_StrCpy (pbuf, endrange, eptr);
                        ret += HPDF_Stream_WriteStr (cmap->stream, buf);
                        i = 0;
                    }
                }
                range = 0;
            }

            if (! range && target ) {
                range = &tmp_range;
                range->from  = key;
                range->bytes = n;
                range_target = target;

                if (i == 0)
                    pbuf = (char *)HPDF_StrCpy (buf, beginrange, eptr);
            }

            prev_key    = key;
            prev_target = target;
        }
    }

    if (range) {
        range->to = prev_key;
        if ((range->from != 0 || range->to != 0 || range_target != 0) &&
            (range_target <= 0xFFFF ||
             HPDF_VER_16 <= attr->cmap->pdf_version)) {
            pbuf = CidRangeToHex (pbuf, range, eptr);

            *pbuf++ = ' ';

            if (cmaptype == HPDF_CMapType_CodeToCid) {
                pbuf = HPDF_IToA (pbuf, range_target, eptr);
            } else {
                *pbuf++ = '<';
                pbuf = Ucs4ToUtf16Hex(pbuf, range_target, eptr);
                *pbuf++ = '>';
            }
            pbuf = (char *)HPDF_StrCpy (pbuf, "\r\n", eptr);

            ++i;
        }
        range = 0;
    }

    if (i) {
        HPDF_StrCpy (pbuf, endrange, eptr);
        if (i < 100) {
            if (i < 10) {
                pbuf = buf + 2;
                pbuf[0] = (char)(i | '0');
            } else {
                pbuf = buf + 1;
                pbuf[0] = (char)((i / 10) | '0');
                pbuf[1] = (char)((i % 10) | '0');
            }
        }
        ret += HPDF_Stream_WriteStr (cmap->stream, pbuf);
    }

    pbuf = (char *)HPDF_StrCpy (buf, "endcmap\r\n", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, "CMapName currentdict /CMap "
            "defineresource pop\r\n", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, "end\r\n", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, "end\r\n\r\n", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, "%%EndResource\r\n", eptr);
    HPDF_StrCpy (pbuf, "%%EOF\r\n", eptr);
    ret += HPDF_Stream_WriteStr (cmap->stream, buf);

    if (ret != HPDF_OK)
        return NULL;

    return cmap;
}
