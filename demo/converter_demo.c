
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
        L"Hello.\x09 \uFFF9مرحبا.\u200F\uFFFAmarḥába\uFFFB สวัสดี\x0A नमस्कार.\x0C "
        L"שלום.\u200F 안녕하세요．\x0D\uFFF9你好\uFFFAnǐhǎo\uFFFB。こんにちは。"
        ;
    const wchar_t *HELLO_ru =
        L"Здравствуйте. "
        ;
    const wchar_t *ONCE_UPON_A_TIME =
        L"以前老夫婦が住んでいました。"
        L"老夫が山へ\uFFF9収穫\uFFFAしばかり\uFFFBに行きました。"
        L"老妻が川へ洗濯に行きました。\n"
        L"老夫婦住。"
        L"老丈夫去到了收穫的山。"
        L"老妻在河裡去洗。\n"
        L"老夫妇住。"
        L"老丈夫去到了收获的山。"
        L"老妻在河里去洗。\n"
        L"이전 노부부가 살고있었습니다．"
        L"늙은 남편이 산에 수확에갔습니다．"
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
        L"ذهـب الزوج القديم إلى الحصـاد إلى الجبل. "
        L"زوجته البالغة من العمر ذهـب ليغسل في النـهر.\u200F\n"
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
    HPDF_Font detail_font, detail_font_v, relief_font;
    const char *detail_font_name;
    HPDF_REAL page_width, page_height;
    HPDF_UINT len;
    HPDF_Rect rect;
    HPDF_INT ttopt;

    if (2 < argc || (1 < argc &&
            (argv[1][0] != '-' || argv[1][1] != 'c' || argv[1][2] != 0))) {
        printf ("usage: converter_demo [-c]\n");
        return 1;
    }

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    ttopt = HPDF_FONTOPT_EMBEDDING;
    if (1 < argc)
        ttopt |= HPDF_FONTOPT_WITHOUT_CID_MAP;

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    HPDF_SetCompressionMode (pdf, HPDF_COMP_IMAGE | HPDF_COMP_METADATA);

    HPDF_UseCNSEncodings (pdf);
    //HPDF_UseCNTEncodings (pdf);
    //HPDF_UseJPEncodings (pdf);
    HPDF_UseKREncodings (pdf);
    HPDF_UseUTFEncodings (pdf);

    HPDF_UseCNSFonts (pdf);
    //HPDF_UseCNTFonts (pdf);
    //HPDF_UseJPFonts (pdf);
    HPDF_UseKRFonts (pdf);


    /* Devanagari */
    detail_font_name = HPDF_LoadTTFontFromFile (pdf,
            "C:\\Windows\\Fonts\\mangal.ttf", ttopt);
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF16-H");

    /* Thai, Armenian */
    detail_font_name = HPDF_LoadTTFontFromFile (pdf,
            "C:\\Windows\\Fonts\\tahoma.ttf", ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);
    relief_font = detail_font_v;
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF16-H");
    HPDF_Font_SetReliefFont (detail_font_v, relief_font);

    /* Korean */
    detail_font_name = HPDF_LoadTTFontFromFile2 (pdf,
            "C:\\Windows\\Fonts\\gulim.ttc", 1, ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "UniKS-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    /* Simplified Chinese, Traditional Chinese, Japanese */
    detail_font_name = HPDF_LoadTTFontFromFile2 (pdf,
            "C:\\Windows\\Fonts\\simsun.ttc", 1, ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "UniGB-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    /* Latin, Cyrillic, Greek, Arabic, Hebrew */
    detail_font_name = HPDF_LoadTTFontFromFile (pdf,
            "C:\\Windows\\Fonts\\times.ttf", ttopt);
    relief_font = detail_font;
    detail_font = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF8-H");
    HPDF_Font_SetReliefFont (detail_font, relief_font);

    HPDF_Font_PushBuiltInConverter (detail_font, "BiDi", NULL);
    HPDF_Font_SetCharacterEncoding (detail_font, HPDF_CHARENC_WCHAR_T);


    //detail_font_name = HPDF_LoadTTFontFromFile2 (pdf,
    //        "C:\\Windows\\Fonts\\batang.ttc", 1, ttopt);
    detail_font_name = "Batang";
    relief_font = detail_font_v;
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "UniKS-UTF16-V");
    HPDF_Font_SetReliefFont (detail_font_v, relief_font);

    //detail_font_name = HPDF_LoadTTFontFromFile (pdf,
    //        "C:\\Windows\\Fonts\\simhei.ttf", ttopt);
    detail_font_name = "SimHei";
    relief_font = detail_font_v;
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "UniGB-UTF16-V");
    HPDF_Font_SetReliefFont (detail_font_v, relief_font);

    detail_font_name = HPDF_LoadTTFontFromFile (pdf,
            "C:\\Windows\\Fonts\\arial.ttf", ttopt);
    relief_font = detail_font_v;
    detail_font_v = HPDF_GetFont (pdf, detail_font_name, "Ancient-UTF16-H");
    HPDF_Font_SetReliefFont (detail_font_v, relief_font);

    HPDF_Font_PushBuiltInConverter (detail_font_v, "BiDi", NULL);
    HPDF_Font_SetCharacterEncoding (detail_font_v, HPDF_CHARENC_WCHAR_T);


    /* Add a new page object. */
    page = HPDF_AddPage (pdf);

    page_width  = 595.27559F;
    page_height = 841.88976F;

    HPDF_Page_SetWidth  (page, page_width);
    HPDF_Page_SetHeight (page, page_height);

    rect.left   = page_width / 2 - 10;
    rect.bottom = page_height - 60;
    rect.right  = page_width / 2 + 10;
    rect.top    = page_height - 80;
    HPDF_Page_CreateTextAnnot (page, rect, (const char *)HELLO,
            HPDF_GetUTFEncoder (pdf, HPDF_CHARENC_WCHAR_T));

    HPDF_Page_BeginText (page);

    HPDF_Page_SetFontAndSize (page, detail_font, 15);
    HPDF_Page_SetWordSpace (page, 5);
    HPDF_Page_SetCharSpace (page, 0);

    HPDF_Page_TextOut (page, 20, page_height - 50, (const char *)HELLO);
    HPDF_Page_ShowText (page, (const char *)HELLO_ru);

    HPDF_Page_SetTextLeading (page, 0);
    HPDF_Page_SetJustifyRatio (page, 1, 1, 100);

    HPDF_Page_TextRect (page, 30, page_height - 60,
            page_width / 2 - 29, 30, (const char *)ONCE_UPON_A_TIME,
            HPDF_TALIGN_JUSTIFY | HPDF_VALIGN_JUSTIFY_ALL |
            HPDF_ALIGNOPT_BIDI_EACH_PARAGRAPH | HPDF_ALIGNOPT_REMOVE_TATWEEL,
            &len);

    HPDF_Page_SetFontAndSize (page, detail_font_v, 15);
    HPDF_Page_SetWordSpace (page, 0);

    HPDF_Page_SetTextLeading (page, 30);
    HPDF_Page_TextOut (page, page_width / 2 + 20, page_height - 90,
            (const char *)HELLO_ru);
    HPDF_Page_ShowText (page, (const char *)HELLO);
    HPDF_Page_ShowTextNextLine (page, NULL);
    HPDF_Page_ShowText (page, (const char *)HELLO_ru);
    HPDF_Page_ShowText (page, (const char *)L"!!!!");

    HPDF_Page_SetTextLeading (page, 0);

    HPDF_Page_TextRect (page, page_width / 2 + 40, page_height - 60,
            page_width - 30, 405, (const char *)ONCE_UPON_A_TIME,
            HPDF_TALIGN_JUSTIFY | HPDF_VALIGN_JUSTIFY, &len);

    HPDF_Page_SetTextLeading (page, -20);

    HPDF_Page_TextRect (page, page_width / 2 + 40, 380, page_width - 30, 30,
            (const char *)ONCE_UPON_A_TIME + len,
            HPDF_TALIGN_JUSTIFY | HPDF_VALIGN_JUSTIFY |
            HPDF_ALIGNOPT_BIDI_EACH_PARAGRAPH | HPDF_ALIGNOPT_REMOVE_TATWEEL,
            &len);

    /* Finish to print text. */
    HPDF_Page_EndText (page);


    HPDF_Page_SetLineWidth (page, 0.5);

    HPDF_Page_MoveTo (page, 10, page_height - 25);
    HPDF_Page_LineTo (page, page_width - 10, page_height - 25);
    HPDF_Page_Stroke (page);

    HPDF_Page_Rectangle (page, 30, page_height - 60,
            page_width / 2 - 29 - 30, 30 - (page_height - 60));
    HPDF_Page_Stroke (page);

    HPDF_Page_Rectangle (page, page_width / 2 + 40, page_height - 60,
            page_width - 30 - (page_width / 2 + 40), 405 - (page_height - 60));
    HPDF_Page_Stroke (page);

    HPDF_Page_Rectangle (page, page_width / 2 + 40, 380,
            page_width - 30 - (page_width / 2 + 40), 30 - 380);
    HPDF_Page_Stroke (page);


    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
