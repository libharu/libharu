
/*
 * << Haru Free PDF Library 2.0.0 >> -- converter_demo.c
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

int main (int argc, char **argv)
{
    const wchar_t *HELLO =
        L"Hello.\x09 مرحبا.\u200F สวัสดี\x0A नमस्कार.\x0C "
        L"שלום.\u200F 안녕하세요.\x0D 你好。こんにちは。"
        ;
    const wchar_t *ONCE_UPON_A_TIME =
        L"以前老夫婦が住んでいました。"
        L"老夫が山へ収穫に行きました。"
        L"老妻が川へ洗濯に行きました。\n"
        L"老夫婦住。"
        L"老丈夫去到了收穫的山。"
        L"老妻在河裡去洗。\n"
        L"老夫妇住。"
        L"老丈夫去到了收获的山。"
        L"老妻在河里去洗。\n"
        L"이전 노부부가 살고있었습니다． "
        L"늙은 남편이 산에 수확에갔습니다． "
        L"늙은 아내가 강에 세탁갔습니다．\n"
        L"Пожилая пара жила раньше. "
        L"Старый муж пошел в урожай в горы. "
        L"Старая жена пошла мыться в реке.\n"
        L"Elderly couple lived before. "
        L"Old hus\u00ADband went to the harvest to the moun\u00ADtain. "
        L"Old wife went to wash in the river.\n"
        L"Ηλικιωμένο ζευγάρι έζησε πριν. "
        L"Παλιά σύζυγος πήγε να τη συγκομιδή στο βουνό. "
        L"Παλιά η γυναίκα πήγε να πλύνει στο ποτάμι.\n"
        L"Տարեցների զույգը ապրում է. "
        L"Հին Ամուսինը գնաց բերքը լեռը. "
        L"Հին կինը գնաց լվանում է գետը.\u200E\n"
        L"عاش زوجين مسنين من قبل. "
        L"ذه\u0640ب الزوج القديم إلى الحص\u0640اد إلى الجبل. "
        L"زوجته البالغة من العمر ذه\u0640ب ليغسل في الن\u0640هر.\u200F\n"
        L"זוג קשישים חי בעבר. "
        L"הבעל ישן הלך לקציר להר. "
        L"אישה זקנה הלכה לרחוץ בנהר.\u200F\n"
        L"वृद्ध दम्पति से पहले रहते थे. "
        L"ओल्ड पति पहाड़ को फसल के लिए गया था. "
        L"पुरानी पत्नी नदी में धोने के लिए चला गया.\u200E\n"
        L"คู่สามีภรรยาสูงอายุ\u200Bอาศัยอยู่\u200Bก่อน\u200B"
        L"สามี\u200Bเก่า\u200Bไป\u200Bเก็บเกี่ยว\u200Bไปยังภูเขา\u200B"
        L"ภรรยา\u200Bเก่า\u200Bไป\u200Bล้าง\u200Bใน\u200Bแม่น้ำ\n"
        ;                                      

    HPDF_Doc  pdf;
    char fname[256];
    HPDF_Page page;
    HPDF_Font detail_font;
    HPDF_Font detail_font_v;
    HPDF_Font detail_font_v2;
    const char *detail_font_name;
    HPDF_Font relief_font;
    HPDF_REAL page_height;
    HPDF_REAL page_width;
    HPDF_UINT len;
    HPDF_Rect rect;

    if (1 < argc) {
        printf ("usage: converter_demo\n");
        return 1;
    }

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    HPDF_UseCNSEncodings (pdf);
    HPDF_UseCNTEncodings (pdf);
    HPDF_UseJPEncodings (pdf);
    HPDF_UseKREncodings (pdf);
    HPDF_UseUTFEncodings (pdf);

    HPDF_UseCNSFonts (pdf);
    HPDF_UseCNTFonts (pdf);
    HPDF_UseJPFonts (pdf);
    HPDF_UseKRFonts (pdf);


    /* Korean */
    detail_font_name = HPDF_LoadTTFontFromFile2 (pdf,
            "C:\\Windows\\Fonts\\gulim.ttc", 1,
            HPDF_FONTOPT_EMBEDDING /* | HPDF_FONTOPT_WITH_CID_MAP */);
    detail_font = HPDF_GetFont (pdf, detail_font_name, "UTF-8");

    /* Simplified Chinese, Traditional Chinese, Japanese */
    relief_font = detail_font;
    detail_font_name = HPDF_LoadTTFontFromFile2 (pdf,
            "C:\\Windows\\Fonts\\simsun.ttc", 1,
            HPDF_FONTOPT_EMBEDDING /* | HPDF_FONTOPT_WITH_CID_MAP */);
    detail_font = HPDF_GetFont (pdf, detail_font_name, "UTF-8");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    /* Devanagari */
    relief_font = detail_font;
    detail_font_name = HPDF_LoadTTFontFromFile (pdf,
            "C:\\Windows\\Fonts\\mangal.ttf",
            HPDF_FONTOPT_EMBEDDING /* | HPDF_FONTOPT_WITH_CID_MAP */);
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    /* Thai, Armenian */
    relief_font = detail_font;
    detail_font_name = HPDF_LoadTTFontFromFile (pdf,
            "C:\\Windows\\Fonts\\tahoma.ttf",
            HPDF_FONTOPT_EMBEDDING /* | HPDF_FONTOPT_WITH_CID_MAP */);
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    /* Latin, Cyrillic, Greek, Arabic, Hebrew */
    relief_font = detail_font;
    detail_font_name = HPDF_LoadTTFontFromFile (pdf,
            "C:\\Windows\\Fonts\\times.ttf",
            HPDF_FONTOPT_EMBEDDING /* | HPDF_FONTOPT_WITH_CID_MAP */);
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    HPDF_Font_PushBuiltInConverter (detail_font, "BiDi", NULL);
    HPDF_Font_SetCharacterEncoding (detail_font, HPDF_CHARENC_WCHAR_T);


    //detail_font_name = "MS-Mincho";
    //detail_font_v = HPDF_GetFont (pdf, detail_font_name, "UniJIS-UTF16-V");

    //relief_font = detail_font_v;
    detail_font_name = "Batang";
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "UniKS-UTF16-V");
    //HPDF_Font_SetReliefFont (detail_font_v, relief_font);

    relief_font = detail_font_v;
    detail_font_name = "SimHei";
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "UniGB-UTF16-V");
    HPDF_Font_SetReliefFont (detail_font_v, relief_font);

    HPDF_Font_SetCharacterEncoding (detail_font_v, HPDF_CHARENC_WCHAR_T);


    detail_font_name = "MS-Mincho";
    detail_font_v2 = HPDF_GetFont (pdf, detail_font_name, "90ms-RKSJ-V");


    /* Add a new page object. */
    page = HPDF_AddPage (pdf);

    page_height = 841.88976F;
    page_width  = 595.27559F;

    HPDF_Page_SetWidth  (page, page_width);
    HPDF_Page_SetHeight (page, page_height);

    rect.left   = 30;
    rect.bottom = page_height - 60;
    rect.right  = 50;
    rect.top    = page_height - 80;
    HPDF_Page_CreateTextAnnot (page, rect, (const char *)HELLO,
            HPDF_GetUTFEncoder (pdf, HPDF_CHARENC_WCHAR_T));

    HPDF_Page_BeginText (page);

    HPDF_Page_SetFontAndSize (page, detail_font, 15);

    HPDF_Page_SetWordSpace (page, 10);
    HPDF_Page_SetCharSpace (page, 0);

    HPDF_Page_MoveTextPos (page, 30, page_height - 40);
    HPDF_Page_ShowText (page, (const char *)HELLO);

    HPDF_Page_SetWordSpace (page, 6);
    HPDF_Page_SetCharSpace (page, 0);
    HPDF_Page_SetJustifyRatio (page, 10, 0, 1000);

    HPDF_Page_TextRect (page, 30, page_height - 90,
            page_width / 2 - 29, 30, (const char *)ONCE_UPON_A_TIME,
            HPDF_TALIGN_JUSTIFY | HPDF_TALIGNOPT_BIDI_EACH_PARAGRAPH | HPDF_TALIGNOPT_REMOVE_TATWEEL, &len);

    HPDF_Page_SetFontAndSize (page, detail_font_v, 15);

    HPDF_Page_SetWordSpace (page,  4);
    HPDF_Page_SetCharSpace (page, -2);
    HPDF_Page_SetJustifyRatio (page, 1, 1, 0);

    HPDF_Page_TextRect (page, page_width / 2 + 30, page_height - 90,
            page_width - 30, 450, (const char *)ONCE_UPON_A_TIME,
            HPDF_TALIGN_JUSTIFY, &len);

    HPDF_Page_SetFontAndSize (page, detail_font_v2, 15);

    HPDF_Page_SetWordSpace (page, -1);
    HPDF_Page_SetCharSpace (page,  4);
    HPDF_Page_SetJustifyRatio (page, 2, 1, 0);
    HPDF_Page_SetTextLeading (page, -10);

    HPDF_Page_TextRect (page, page_width / 2 + 30, 400, page_width - 30, 30,
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. "
            "A quick brown fox jumps over the lazy dog. ",
            HPDF_TALIGN_JUSTIFY, &len);

    /* Finish to print text. */
    HPDF_Page_EndText (page);


    HPDF_Page_SetLineWidth (page, 0.5);

    HPDF_Page_MoveTo (page, 10, page_height - 25);
    HPDF_Page_LineTo (page, page_width - 10, page_height - 25);
    HPDF_Page_Stroke (page);

    HPDF_Page_Rectangle (page, 30, page_height - 90,
            page_width / 2 - 29 - 30, 30 - (page_height - 90));
    HPDF_Page_Stroke (page);

    HPDF_Page_Rectangle (page, page_width / 2 + 30, page_height - 90,
            page_width - 30 - (page_width / 2 + 30), 450 - (page_height - 90));
    HPDF_Page_Stroke (page);

    HPDF_Page_Rectangle (page, page_width / 2 + 30, 400,
            page_width - 30 - (page_width / 2 + 30), 30 - 400);
    HPDF_Page_Stroke (page);


    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
