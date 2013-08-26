/*
 * << Haru Free PDF Library >> -- hpdf_encoder_utf.c
 *
 * URL: http://libharu.org
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2007-2008 Antony Dovgal <tony@daylessday.org>
 * Copyright (c) 2010      Sergey Konovalov <webmaster@crynet.ru>
 * Copyright (c) 2011      Koen Deforche <koen@emweb.be>
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
#include "hpdf_encoder.h"
#include "hpdf.h"


static HPDF_CID
Haru_Modern1_ToCID  (HPDF_Encoder  encoder,
                     HPDF_UCS4     ucs4)
{
    HPDF_UNUSED (encoder);

    return (HPDF_CID)((                   ucs4 <= 0x0D7FF)?  ucs4:
                      (0x0E000 <= ucs4 && ucs4 <= 0x0FFFF)? (ucs4 - 0x0E000 + 0xD800):
                      (0x1F000 <= ucs4 && ucs4 <= 0x1F7FF)? (ucs4 - 0x1F000 + 0xF800):
                      0);
}


static HPDF_STATUS
SetHaruModern1  (HPDF_Encoder     encoder,
                 HPDF_Doc         pdf,
                 HPDF_INT         supplement,
                 HPDF_WritingMode writing_mode)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_CMapInfo info;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->to_cid_fn = Haru_Modern1_ToCID;
    attr->supplement = supplement;
    attr->max_cid = 0xFFFF;

    info = HPDF_Doc_GetCMap (pdf, "Haru", "Modern1",
            writing_mode, sizeof (HPDF_CMapInfo_Rec));

    if (!info)
        return HPDF_CheckError (&pdf->error);

    attr->cmap = info;

    info->pdf_version = HPDF_Doc_RecommendVersion (pdf, HPDF_VER_16);

    return HPDF_OK;
}


static HPDF_CID
Haru_Ancient1_ToCID  (HPDF_Encoder  encoder,
                      HPDF_UCS4     ucs4)
{
    HPDF_UNUSED (encoder);

    return (HPDF_CID)((                   ucs4 <= 0x02FFF)?  ucs4:
                      (0x0A000 <= ucs4 && ucs4 <= 0x0D7FF)? (ucs4 - 0x0A000 + 0x3000):
                      (0x0E000 <= ucs4 && ucs4 <= 0x117FF)? (ucs4 - 0x0E000 + 0x6800):
                      (0x12000 <= ucs4 && ucs4 <= 0x127FF)? (ucs4 - 0x12000 + 0xA000):
                      (0x13000 <= ucs4 && ucs4 <= 0x137FF)? (ucs4 - 0x13000 + 0xA800):
                      (0x16800 <= ucs4 && ucs4 <= 0x16FFF)? (ucs4 - 0x16800 + 0xB000):
                      (0x1D000 <= ucs4 && ucs4 <= 0x1D7FF)? (ucs4 - 0x1D000 + 0xB800):
                      (0x1E800 <= ucs4 && ucs4 <= 0x1F7FF)? (ucs4 - 0x1E800 + 0xC000):
                      0);
}


static HPDF_STATUS
SetHaruAncient1  (HPDF_Encoder     encoder,
                  HPDF_Doc         pdf,
                  HPDF_INT         supplement,
                  HPDF_WritingMode writing_mode)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_CMapInfo info;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->to_cid_fn = Haru_Ancient1_ToCID;
    attr->supplement = supplement;
    attr->max_cid = 0xCFFF;

    info = HPDF_Doc_GetCMap (pdf, "Haru", "Ancient1",
            writing_mode, sizeof (HPDF_CMapInfo_Rec));

    if (!info)
        return HPDF_CheckError (&pdf->error);

    attr->cmap = info;

    info->pdf_version = HPDF_Doc_RecommendVersion (pdf, HPDF_VER_16);

    return HPDF_OK;
}


static const HPDF_CidRange_Rec UTF32_NOTDEF_RANGE = {0x00000000, 0x00001F, 4, 1};


static HPDF_UCS4
UTF32_ToUcs4  (HPDF_Encoder     encoder,
               const HPDF_BYTE *text,
               HPDF_UINT        bytes)
{
    HPDF_UNUSED (encoder);

    return HPDF_UTF32BEToUcs4 (text, bytes);
}


static HPDF_STATUS
UTF32_AddCodeSpaceRange (HPDF_Encoder    encoder)
{
    HPDF_CidRange_Rec code_space_range1 = {0x00000000, 0x0001FFFF, 4, 0};

    if (HPDF_CMapEncoder_AddCodeSpaceRange (encoder, code_space_range1)
                    != HPDF_OK)
        return encoder->error->error_no;

    return HPDF_OK;
}


static const HPDF_CidRange_Rec UCS2LE_NOTDEF_RANGE = {0x0000, 0x1F00, 2, 1};


static HPDF_UCS4
UCS2LE_ToUcs4  (HPDF_Encoder     encoder,
                const HPDF_BYTE *text,
                HPDF_UINT        bytes)
{
    HPDF_UNUSED (encoder);

    return HPDF_UTF16LEToUcs4 (text, bytes);
}


static HPDF_STATUS
UCS2LE_AddCodeSpaceRange (HPDF_Encoder    encoder)
{
    /* These code space ranges are *NOT* asceding order,
       might cause something.... */
    HPDF_CidRange_Rec code_space_range1 = {0x0000, 0xFFD7, 2, 0};
    HPDF_CidRange_Rec code_space_range2 = {0x00E0, 0xFFFF, 2, 0};

    if (HPDF_CMapEncoder_AddCodeSpaceRange (encoder, code_space_range1)
                    != HPDF_OK)
        return encoder->error->error_no;

    if (HPDF_CMapEncoder_AddCodeSpaceRange (encoder, code_space_range2)
                    != HPDF_OK)
        return encoder->error->error_no;

    return HPDF_OK;
}


static const HPDF_CidRange_Rec UTF32LE_NOTDEF_RANGE = {0x00000000, 0x1F000000, 4, 1};


static HPDF_UCS4
UTF32LE_ToUcs4  (HPDF_Encoder     encoder,
                 const HPDF_BYTE *text,
                 HPDF_UINT        bytes)
{
    HPDF_UNUSED (encoder);

    return HPDF_UTF32LEToUcs4 (text, bytes);
}


static HPDF_STATUS
UTF32LE_AddCodeSpaceRange (HPDF_Encoder    encoder)
{
    HPDF_CidRange_Rec code_space_range1 = {0x00000000, 0xFFFF0100, 4, 0};

    if (HPDF_CMapEncoder_AddCodeSpaceRange (encoder, code_space_range1)
                    != HPDF_OK)
        return encoder->error->error_no;

    return HPDF_OK;
}


static HPDF_STATUS
Modern_UTF8_H_Init  (HPDF_Encoder  encoder,
                     HPDF_Doc      pdf)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_UTF8Encoder_Init (encoder, pdf)) != HPDF_OK)
        return ret;

    if ((ret = SetHaruModern1 (encoder, pdf, 0, HPDF_WMODE_HORIZONTAL))
            != HPDF_OK)
        return ret;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->uid_offset = -1;
    /* Not sure about this
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_MULTI_BYTE;

    return HPDF_OK;
}


static HPDF_STATUS
Modern_UTF16_H_Init  (HPDF_Encoder  encoder,
                      HPDF_Doc      pdf)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_UTF16Encoder_Init (encoder, pdf)) != HPDF_OK)
        return ret;

    if ((ret = SetHaruModern1 (encoder, pdf, 0, HPDF_WMODE_HORIZONTAL))
            != HPDF_OK)
        return ret;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->uid_offset = -1;
    /* Not sure about this
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_MULTI_BYTE;

    return HPDF_OK;
}


static HPDF_STATUS
Modern_UTF32_H_Init  (HPDF_Encoder  encoder,
                      HPDF_Doc      pdf)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    encoder->to_ucs4_fn = UTF32_ToUcs4;
    encoder->charenc = HPDF_CHARENC_UTF32BE;

    if ((ret = HPDF_CMapEncoder_InitAttr (encoder)) != HPDF_OK)
        return ret;

    if ((ret = SetHaruModern1 (encoder, pdf, 0, HPDF_WMODE_HORIZONTAL))
            != HPDF_OK)
        return ret;

    if ((ret = UTF32_AddCodeSpaceRange (encoder)) != HPDF_OK)
        return ret;

    if (HPDF_CMapEncoder_AddNotDefRange (encoder, UTF32_NOTDEF_RANGE)
                != HPDF_OK)
        return encoder->error->error_no;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->uid_offset = -1;
    /* Not sure about this
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_MULTI_BYTE;

    return HPDF_OK;
}


static HPDF_STATUS
Modern_UCS2LE_H_Init  (HPDF_Encoder  encoder,
                       HPDF_Doc      pdf)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    encoder->to_ucs4_fn = UCS2LE_ToUcs4;
    encoder->charenc = HPDF_CHARENC_UTF16LE;

    if ((ret = HPDF_CMapEncoder_InitAttr (encoder)) != HPDF_OK)
        return ret;

    if ((ret = SetHaruModern1 (encoder, pdf, 0, HPDF_WMODE_HORIZONTAL))
            != HPDF_OK)
        return ret;

    if ((ret = UCS2LE_AddCodeSpaceRange (encoder)) != HPDF_OK)
        return ret;

    if (HPDF_CMapEncoder_AddNotDefRange (encoder, UCS2LE_NOTDEF_RANGE)
                != HPDF_OK)
        return encoder->error->error_no;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->max_cid = 0xF7FF;     /* override to limit in UCS2 */
    attr->uid_offset = -1;
    /* Not sure about this
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_MULTI_BYTE;

    return HPDF_OK;
}


static HPDF_STATUS
Modern_UTF32LE_H_Init  (HPDF_Encoder  encoder,
                        HPDF_Doc      pdf)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    encoder->to_ucs4_fn = UTF32LE_ToUcs4;
    encoder->charenc = HPDF_CHARENC_UTF32LE;

    if ((ret = HPDF_CMapEncoder_InitAttr (encoder)) != HPDF_OK)
        return ret;

    if ((ret = SetHaruModern1 (encoder, pdf, 0, HPDF_WMODE_HORIZONTAL))
            != HPDF_OK)
        return ret;

    if ((ret = UTF32LE_AddCodeSpaceRange (encoder)) != HPDF_OK)
        return ret;

    if (HPDF_CMapEncoder_AddNotDefRange (encoder, UTF32LE_NOTDEF_RANGE)
                != HPDF_OK)
        return encoder->error->error_no;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->uid_offset = -1;
    /* Not sure about this
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_MULTI_BYTE;

    return HPDF_OK;
}


static HPDF_STATUS
Ancient_UTF8_H_Init  (HPDF_Encoder  encoder,
                       HPDF_Doc      pdf)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_UTF8Encoder_Init (encoder, pdf)) != HPDF_OK)
        return ret;

    if ((ret = SetHaruAncient1 (encoder, pdf, 0, HPDF_WMODE_HORIZONTAL))
            != HPDF_OK)
        return ret;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->uid_offset = -1;
    /* Not sure about this
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_MULTI_BYTE;

    return HPDF_OK;
}


static HPDF_STATUS
Ancient_UTF16_H_Init  (HPDF_Encoder  encoder,
                       HPDF_Doc      pdf)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_UTF16Encoder_Init (encoder, pdf)) != HPDF_OK)
        return ret;

    if ((ret = SetHaruAncient1 (encoder, pdf, 0, HPDF_WMODE_HORIZONTAL))
            != HPDF_OK)
        return ret;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    attr->uid_offset = -1;
    /* Not sure about this
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_MULTI_BYTE;

    return HPDF_OK;
}


/*--------------------------------------------------------------------------*/

static const char MODERN_ENCODERS[][17] = {
  "",
  "Modern-UTF8-H",
  "Modern-UTF16-H",
  "Modern-UTF32-H",
  "Modern-UCS2LE-H",
  "Modern-UTF32LE-H",
};


HPDF_EXPORT(HPDF_STATUS)
HPDF_UseUTFEncodings   (HPDF_Doc   pdf)
{
    HPDF_Encoder encoder;
    HPDF_STATUS ret;

    if (!HPDF_HasDoc (pdf))
        return HPDF_INVALID_DOCUMENT;

    encoder = HPDF_CMapEncoder_New (pdf->mmgr,
            MODERN_ENCODERS[HPDF_CHARENC_UTF8], Modern_UTF8_H_Init);

    if ((ret = HPDF_Doc_RegisterEncoder (pdf, encoder)) != HPDF_OK)
        return ret;

    encoder = HPDF_CMapEncoder_New (pdf->mmgr,
            MODERN_ENCODERS[HPDF_CHARENC_UTF16BE], Modern_UTF16_H_Init);

    if ((ret = HPDF_Doc_RegisterEncoder (pdf, encoder)) != HPDF_OK)
        return ret;

    encoder = HPDF_CMapEncoder_New (pdf->mmgr,
            MODERN_ENCODERS[HPDF_CHARENC_UTF32BE], Modern_UTF32_H_Init);

    if ((ret = HPDF_Doc_RegisterEncoder (pdf, encoder)) != HPDF_OK)
        return ret;

    encoder = HPDF_CMapEncoder_New (pdf->mmgr,
            MODERN_ENCODERS[HPDF_CHARENC_UTF16LE], Modern_UCS2LE_H_Init);

    if ((ret = HPDF_Doc_RegisterEncoder (pdf, encoder)) != HPDF_OK)
        return ret;

    encoder = HPDF_CMapEncoder_New (pdf->mmgr,
            MODERN_ENCODERS[HPDF_CHARENC_UTF32LE], Modern_UTF32LE_H_Init);

    if ((ret = HPDF_Doc_RegisterEncoder (pdf, encoder)) != HPDF_OK)
        return ret;

    encoder = HPDF_CMapEncoder_New (pdf->mmgr,
            "Ancient-UTF8-H", Ancient_UTF8_H_Init);

    if ((ret = HPDF_Doc_RegisterEncoder (pdf, encoder)) != HPDF_OK)
        return ret;

    encoder = HPDF_CMapEncoder_New (pdf->mmgr,
            "Ancient-UTF16-H", Ancient_UTF16_H_Init);

    if ((ret = HPDF_Doc_RegisterEncoder (pdf, encoder)) != HPDF_OK)
        return ret;

    return HPDF_OK;
}


HPDF_EXPORT(HPDF_Encoder)
HPDF_GetUTFEncoder  (HPDF_Doc      pdf,
                     HPDF_CharEnc  charenc)
{
    HPDF_Encoder encoder;

    HPDF_PTRACE ((" HPDF_GetUTFEncoder\n"));

    if (!HPDF_HasDoc (pdf))
        return NULL;

    HPDF_NormalizeCharEnc (&charenc);

    if (charenc == HPDF_CHARENC_UNSUPPORTED) {
        HPDF_RaiseError (&pdf->error, HPDF_NOT_UTF_ENCODING, 0);
        return NULL;
    }

    encoder = HPDF_Doc_FindEncoder (pdf, MODERN_ENCODERS[charenc]);

    return encoder;
}
