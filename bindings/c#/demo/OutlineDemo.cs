/*
 * << Haru Free PDF Library 2.0.5 >> -- OutlineDemo.cs
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


public class OutlineDemo {
    private static void PrintPage(HPdfPage page, int page_num) {
        page.SetWidth(800);
        page.SetHeight(800);

        page.BeginText();
        page.MoveTextPos(30, 740);
        string buf = "Page:" + page_num;
        page.ShowText(buf);
        page.EndText();
    }

    public static void Main() {
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion());

        try {
            HPdfDoc pdf = new HPdfDoc();

            pdf.SetCompressionMode(HPdfDoc.HPDF_COMP_ALL);

            /* create default-font */
            HPdfFont font = pdf.GetFont("Helvetica", null);

            pdf.SetPageMode(HPdfPageMode.HPDF_PAGE_MODE_USE_OUTLINE);

            /* add a new page object. */
            /* Add 3 pages to the document. */
            HPdfPage page0 = pdf.AddPage();
            page0.SetFontAndSize (font, 30);
            PrintPage(page0, 1);

            HPdfPage page1 = pdf.AddPage();
            page1.SetFontAndSize(font, 30);
            PrintPage(page1, 2);

            HPdfPage page2 = pdf.AddPage();
            page2.SetFontAndSize(font, 30);
            PrintPage(page2, 3);

            /* create outline root. */
            HPdfOutline root = pdf.CreateOutline(null, "OutlineRoot", null);
            root.SetOpened (true);

            HPdfOutline outline0 = pdf.CreateOutline(root, "page1", null);
            HPdfOutline outline1 = pdf.CreateOutline(root, "page2", null);

            /* create outline with test which is ISO8859-2 encoding */
            HPdfOutline outline2 = pdf.CreateOutline(root, "ISO8859-2 text гдежзий",
                    pdf.GetEncoder("ISO8859-2"));

            /* create destination objects on each pages
             * and link it to outline items.
             */
            HPdfDestination dst = page0.CreateDestination();
            dst.SetXYZ(0, page0.GetHeight(), 1);
            outline0.SetDestination(dst);

            dst = page1.CreateDestination();
            dst.SetXYZ(0, page1.GetHeight(), 1);
            outline1.SetDestination(dst);

            dst = page2.CreateDestination();
            dst.SetXYZ(0, page2.GetHeight(), 1);
            outline2.SetDestination(dst);

            /* save the document to a file */
            pdf.SaveToFile("OutlineDemo.pdf");

        } catch (Exception e) {
            Console.Error.WriteLine(e.Message);
        }
    }
}



