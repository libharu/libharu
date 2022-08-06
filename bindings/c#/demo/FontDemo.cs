/*
 * << Haru Free PDF Library 2.0.5 >> -- FontDemo.cs
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
using System.IO;
using HPdf;


public class FontDemo {
    public static void Main() {
        string[] font_list = new string[] {
            "Courier",
            "Courier-Bold",
            "Courier-Oblique",
            "Courier-BoldOblique",
            "Helvetica",
            "Helvetica-Bold",
            "Helvetica-Oblique",
            "Helvetica-BoldOblique",
            "Times-Roman",
            "Times-Bold",
            "Times-Italic",
            "Times-BoldItalic",
            "Symbol",
            "ZapfDingbats"
        };

        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion());

        try {
            const string page_title = "FontDemo";

            HPdfDoc pdf = new HPdfDoc();

            HPdfPage page = pdf.AddPage();

            float height = page.GetHeight();
            float width = page.GetWidth();

            /* Print the lines of the page. */
            page.SetLineWidth(1);
            page.Rectangle(50, 50, width - 100, height - 110);
            page.Stroke();

            /* Print the title of the page (with positioning center). */
            HPdfFont def_font = pdf.GetFont ("Helvetica", null);
            page.SetFontAndSize(def_font, 24);

            float tw = page.TextWidth(page_title);
            page.BeginText();
            page.TextOut((width - tw) / 2, height - 50, page_title);
            page.EndText();

            /* output subtitle. */
            page.BeginText();
            page.SetFontAndSize(def_font, 16);
            page.TextOut(60, height - 80, "<Standerd Type1 fonts samples>");
            page.EndText();

            page.BeginText();
            page.MoveTextPos(60, height - 105);

            for (int i = 0; i < font_list.Length; i++) {
                const string samp_text = "abcdefgABCDEFG12345!#$%&+-@?";
                HPdfFont font = pdf.GetFont(font_list[i], null);

                /* print a label of text */
                page.SetFontAndSize(def_font, 9);
                page.ShowText(font_list[i]);
                page.MoveTextPos(0, -18);

                /* print a sample text. */
                page.SetFontAndSize(font, 20);
                page.ShowText(samp_text);
                page.MoveTextPos(0, -20);
            }

            page.EndText();

            pdf.SaveToFile("FontDemo.pdf");
        } catch (Exception e) {
            Console.Error.WriteLine(e.Message);
        }
    }
}



