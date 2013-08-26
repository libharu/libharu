/*
 * << Haru Free PDF Library >> -- hpdf_font_tt.c
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


static HPDF_STATUS
OnWrite  (HPDF_Dict    obj,
          HPDF_Stream  stream);


static HPDF_STATUS
BeforeWrite  (HPDF_Dict   obj);


static void
OnFree  (HPDF_Dict  obj);


static HPDF_INT
CharWidth  (HPDF_Font        font,
            HPDF_BOOL        converted,
            HPDF_BYTE        irf,
            const HPDF_BYTE *text,
            HPDF_UINT       *bytes,
            HPDF_UCS4       *ucs4);


static HPDF_STATUS
CreateDescriptor  (HPDF_Font  font);


HPDF_Font
HPDF_TTFont_New  (HPDF_MMgr        mmgr,
                  HPDF_FontDef     fontdef,
                  HPDF_Encoder     encoder,
                  HPDF_Xref        xref)
{
    HPDF_Dict font;
    HPDF_FontAttr attr;
    HPDF_TTFontDefAttr fontdef_attr;
    HPDF_BasicEncoderAttr encoder_attr;
    HPDF_STATUS ret = 0;

    HPDF_PTRACE ((" HPDF_TTFont_New\n"));

    font = HPDF_Dict_New (mmgr);
    if (!font)
        return NULL;

    font->header.obj_class |= HPDF_OSUBCLASS_FONT;

    /* check whether the fontdef object and the encoder object is valid. */
    if (encoder->type != HPDF_ENCODER_TYPE_SINGLE_BYTE) {
        HPDF_SetError(font->error, HPDF_INVALID_ENCODER_TYPE, 0);
        return NULL;
    }

    if (fontdef->type != HPDF_FONTDEF_TYPE_TRUETYPE) {
        HPDF_SetError(font->error, HPDF_INVALID_FONTDEF_TYPE, 0);
        return NULL;
    }

    attr = HPDF_GetMem (mmgr, sizeof(HPDF_FontAttr_Rec));
    if (!attr) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    HPDF_MemSet (attr, 0, sizeof(HPDF_FontAttr_Rec));

    font->header.obj_class |= HPDF_OSUBCLASS_FONT;
    font->write_fn = OnWrite;
    font->before_write_fn = BeforeWrite;
    font->free_fn = OnFree;
    font->attr = attr;

    attr->type = HPDF_FONT_TRUETYPE;
    attr->writing_mode = HPDF_WMODE_HORIZONTAL;
    attr->char_width_fn = CharWidth;
    attr->fontdef = fontdef;
    attr->encoder = encoder;
    attr->xref = xref;

    /* singlebyte-font has a widths-array which is an array of 256 signed
     * short integer.
     * in the case of type1-font, widths-array for all letters is made in
     * constructer. but in the case of true-type-font, the array is
     * initialized at 0, and set when the corresponding character was used
     * for the first time.
     */
    attr->widths = HPDF_GetMem (mmgr, sizeof(HPDF_INT16) * 256);
    if (!attr->widths) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    HPDF_MemSet (attr->widths, 0, sizeof(HPDF_INT16) * 256);

    attr->used = HPDF_GetMem (mmgr, sizeof(HPDF_BYTE) * 256);
    if (!attr->used) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    HPDF_MemSet (attr->used, 0, sizeof(HPDF_BYTE) * 256);

    fontdef_attr = (HPDF_TTFontDefAttr)fontdef->attr;

    ret += HPDF_Dict_AddName (font, "Type", "Font");
    ret += HPDF_Dict_AddName (font, "BaseFont", fontdef_attr->base_font);
    ret += HPDF_Dict_AddName (font, "Subtype", "TrueType");

    encoder_attr = (HPDF_BasicEncoderAttr)encoder->attr;

    ret += HPDF_Dict_AddNumber (font, "FirstChar", encoder_attr->first_char);
    ret += HPDF_Dict_AddNumber (font, "LastChar", encoder_attr->last_char);
    if (fontdef->missing_width != 0)
        ret += HPDF_Dict_AddNumber (font, "MissingWidth",
                fontdef->missing_width);

    if (ret != HPDF_OK) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    if (HPDF_Xref_Add (xref, font) != HPDF_OK)
        return NULL;

    return font;
}


static HPDF_STATUS
CreateDescriptor  (HPDF_Font  font)
{
    HPDF_FontAttr font_attr = (HPDF_FontAttr)font->attr;
    HPDF_FontDef def = font_attr->fontdef;
    HPDF_TTFontDefAttr def_attr = (HPDF_TTFontDefAttr)def->attr;

    HPDF_PTRACE ((" HPDF_TTFont_CreateDescriptor\n"));

    if (!font_attr->fontdef->descriptor) {
        HPDF_Dict descriptor = HPDF_Dict_New (font->mmgr);
        HPDF_STATUS ret = 0;
        HPDF_Array array;

        if (!descriptor)
            return HPDF_Error_GetCode (font->error);

        ret += HPDF_Xref_Add (font_attr->xref, descriptor);
        ret += HPDF_Dict_AddName (descriptor, "Type", "FontDescriptor");
        ret += HPDF_Dict_AddNumber (descriptor, "Ascent", def->ascent);
        ret += HPDF_Dict_AddNumber (descriptor, "Descent", def->descent);
        ret += HPDF_Dict_AddNumber (descriptor, "CapHeight", def->cap_height);
        ret += HPDF_Dict_AddNumber (descriptor, "Flags", def->flags);

        array = HPDF_Box_Array_New (font->mmgr, def->font_bbox);
        ret += HPDF_Dict_Add (descriptor, "FontBBox", array);

        ret += HPDF_Dict_AddName (descriptor, "FontName", def_attr->base_font);
        ret += HPDF_Dict_AddNumber (descriptor, "ItalicAngle",
                def->italic_angle);
        ret += HPDF_Dict_AddNumber (descriptor, "StemV", def->stemv);
        ret += HPDF_Dict_AddNumber (descriptor, "XHeight", def->x_height);

        if (def_attr->char_set)
            ret += HPDF_Dict_AddName (descriptor, "CharSet",
                        def_attr->char_set);

        if (ret != HPDF_OK)
            return HPDF_Error_GetCode (font->error);

        if (def_attr->options & HPDF_FONTOPT_EMBEDDING) {
            HPDF_Dict font_data = HPDF_DictStream_New (font->mmgr,
                    font_attr->xref);

            if (!font_data)
                return HPDF_Error_GetCode (font->error);

            if (HPDF_TTFontDef_SaveFontData (font_attr->fontdef,
                font_data->stream) != HPDF_OK)
                return HPDF_Error_GetCode (font->error);

            ret += HPDF_Dict_Add (descriptor, "FontFile2", font_data);
            ret += HPDF_Dict_AddNumber (font_data, "Length1",
                    def_attr->length1);
            ret += HPDF_Dict_AddNumber (font_data, "Length2", 0);
            ret += HPDF_Dict_AddNumber (font_data, "Length3", 0);

            font_data->filter = font->filter;
        }

        if (ret != HPDF_OK)
            return HPDF_Error_GetCode (font->error);

        font_attr->fontdef->descriptor = descriptor;
    }

    return HPDF_Dict_Add (font, "FontDescriptor",
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
    HPDF_CODE code = (HPDF_CODE)text[0];
    HPDF_UCS4 tmp_ucs4;

    if (!ucs4 && !converted)
        ucs4 = &tmp_ucs4;

    if (ucs4)
        *ucs4 = HPDF_Encoder_GetUcs4 (attr->encoder, text, bytes);
    else if (bytes)
        *bytes = 1;

    if (converted) {
        while (irf-- && font)
            font = ((HPDF_FontAttr)font->attr)->relief_font;
    } else {
        font = HPDF_Font_GetReliefFont (font, *ucs4, NULL);
    }
    if (!font)
        return attr->fontdef->missing_width;

    attr = (HPDF_FontAttr)font->attr;

    if (attr->used[code] == 0) {
        if (!ucs4) {
            ucs4 = &tmp_ucs4;
            *ucs4 = HPDF_Encoder_GetUcs4 (attr->encoder, text, bytes);
        }

        attr->used[code] = 1;
        attr->widths[code] = HPDF_TTFontDef_GetCharWidth(attr->fontdef, *ucs4);
    }

    return attr->widths[code];
}


static HPDF_STATUS
OnWrite  (HPDF_Dict    obj,
          HPDF_Stream  stream)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)obj->attr;
    HPDF_BasicEncoderAttr encoder_attr =
                    (HPDF_BasicEncoderAttr)attr->encoder->attr;
    HPDF_UINT i;
    HPDF_STATUS ret;
    char buf[128];
    char *pbuf = buf;
    char *eptr = buf + 127;

    HPDF_PTRACE ((" HPDF_Font_OnWrite\n"));

    /* Widths entry */
    if ((ret = HPDF_Stream_WriteEscapeName (stream, "Widths")) != HPDF_OK)
        return ret;

    if ((ret = HPDF_Stream_WriteStr (stream, " [\012")) != HPDF_OK)
        return ret;

    for (i = encoder_attr->first_char; i <= encoder_attr->last_char; i++) {

        pbuf = HPDF_IToA (pbuf, attr->widths[i], eptr);
        *pbuf++ = ' ';

        if ((i + 1) % 16 == 0) {
            HPDF_StrCpy(pbuf, "\012", eptr);
            if ((ret = HPDF_Stream_WriteStr (stream, buf)) != HPDF_OK)
                return ret;
            pbuf = buf;
        }

    }

    HPDF_StrCpy (pbuf, "]\012", eptr);

    if ((ret = HPDF_Stream_WriteStr (stream, buf)) != HPDF_OK)
        return ret;

    return attr->encoder->write_fn (attr->encoder, stream);
}


static HPDF_STATUS
BeforeWrite  (HPDF_Dict   obj)
{
    HPDF_PTRACE ((" HPDF_TTFont_BeforeWrite\n"));

    return CreateDescriptor (obj);
}


static void
OnFree  (HPDF_Dict  obj)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)obj->attr;

    HPDF_PTRACE ((" HPDF_TTFont_OnFree\n"));

    HPDF_Font_FreeConvertersListAll ((HPDF_Font)obj);

    if (attr) {
        if (attr->widths) {
            HPDF_FreeMem (obj->mmgr, attr->widths);
        }

        if (attr->used) {
            HPDF_FreeMem (obj->mmgr, attr->used);
        }

        HPDF_FreeMem (obj->mmgr, attr);
    }
}
