/*
 * << Haru Free PDF Library 2.0.5 >> -- Encryption.cs
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


public class Encryption {

    public static void Main() {
        string owner_passwd = "owner";
        string user_passwd = "user";
        string text = "This is an encrypt document example.";
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion());

        try {
            HPdfDoc pdf = new HPdfDoc();

            /* create default-font */
            HPdfFont font = pdf.GetFont("Helvetica", null);

            /* add a new page object. */
            HPdfPage page = pdf.AddPage();

            page.SetSize(HPdfPageSizes.HPDF_PAGE_SIZE_B5, 
                    HPdfPageDirection.HPDF_PAGE_LANDSCAPE);

            page.BeginText();
            page.SetFontAndSize(font, 20);
            float tw = page.TextWidth(text);
            page.MoveTextPos((page.GetWidth() - tw) / 2,
                (page.GetHeight()  - 20) / 2);
            page.ShowText(text);
            page.EndText();

            pdf.SetPassword(owner_passwd, user_passwd);

            /* save the document to a file */
            pdf.SaveToFile("Encryption.pdf");

        } catch (Exception e) {
            Console.Error.WriteLine(e.Message);
        }
    }
}



