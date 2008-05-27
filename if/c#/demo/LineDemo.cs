/*
 * << Haru Free PDF Library 2.0.5 >> -- LineDemo.cs
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


public class LineDemo {
    private static void DrawLine(HPdfPage page, float x, float y, string label) {
        page.BeginText();
        page.MoveTextPos(x, y - 10);
        page.ShowText(label);
        page.EndText();

        page.MoveTo(x, y - 15);
        page.LineTo(x + 220, y - 15);
        page.Stroke();
    }

    private static void DrawLine2(HPdfPage page, float x, float y, string label) {
        page.BeginText();
        page.MoveTextPos(x, y);
        page.ShowText(label);
        page.EndText();

        page.MoveTo(x + 30, y - 25);
        page.LineTo(x + 160, y - 25);
        page.Stroke();
    }

    private static void DrawRect(HPdfPage page, float x, float y, string label) {
        page.BeginText();
        page.MoveTextPos(x, y - 10);
        page.ShowText(label);
        page.EndText();

        page.Rectangle(x, y - 40, 220, 25);
    }

    public static void Main() {
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion());

        try {
            const string page_title = "LineDemo";

            HPdfDoc pdf = new HPdfDoc();

            /* create default-font */
            HPdfFont font = pdf.GetFont ("Helvetica", null);

            /* add a new page object. */
            HPdfPage page = pdf.AddPage();

            /* print the lines of the page. */
            page.SetLineWidth(1);
            page.Rectangle(50, 50, page.GetWidth() - 100,
                        page.GetHeight() - 110);
            page.Stroke();

            /* print the title of the page (with positioning center). */
            page.SetFontAndSize(font, 24);
            float tw = page.TextWidth(page_title);
            page.BeginText();
            page.MoveTextPos ((page.GetWidth() - tw) / 2,
                        page.GetHeight() - 50);
            page.ShowText(page_title);
            page.EndText();

            page.SetFontAndSize(font, 10);

            /* Draw verious widths of lines. */
            page.SetLineWidth(0);
            DrawLine(page, 60, 770, "line width = 0");

            page.SetLineWidth(1.0f);
            DrawLine(page, 60, 740, "line width = 1.0");

            page.SetLineWidth(2.0f);
            DrawLine(page, 60, 710, "line width = 2.0");

            /* Line dash pattern */
            ushort[] dash_mode1 = new ushort[] {3};
            ushort[] dash_mode2 = new ushort[] {3, 7};
            ushort[] dash_mode3 = new ushort[] {8, 7, 2, 7};

            page.SetLineWidth(1.0f);

            page.SetDash(dash_mode1, 1);
            DrawLine(page, 60, 680, "dash_ptn=[3], phase=1 -- 2 on, 3 off, 3 on...");

            Console.Error.WriteLine("001");
            page.SetDash(dash_mode2, 2);
            DrawLine(page, 60, 650, "dash_ptn=[7, 3], phase=2 -- 5 on 3 off, 7 on,...");

            page.SetDash(dash_mode3, 0);
            DrawLine(page, 60, 620, "dash_ptn=[8, 7, 2, 7], phase=0");

            page.SetDash(null, 0);

            page.SetLineWidth(30);
            page.SetRGBStroke(0.0f, 0.5f, 0.0f);

            /* Line Cap Style */
            page.SetLineCap(HPdfLineCap.HPDF_BUTT_END);
            DrawLine2(page, 60, 570, "HPDF_BUTT_END");

            page.SetLineCap(HPdfLineCap.HPDF_ROUND_END);
            DrawLine2(page, 60, 505, "HPDF_ROUND_END");

            page.SetLineCap(HPdfLineCap.HPDF_PROJECTING_SCUARE_END);
            DrawLine2(page, 60, 440, "HPDF_PROJECTING_SCUARE_END");

            /* Line Join Style */
            page.SetLineWidth(30);
            page.SetRGBStroke(0.0f, 0.0f, 0.5f);

            page.SetLineJoin(HPdfLineJoin.HPDF_MITER_JOIN);
            page.MoveTo(120, 300);
            page.LineTo(160, 340);
            page.LineTo(200, 300);
            page.Stroke();

            page.BeginText();
            page.MoveTextPos(60, 360);
            page.ShowText("HPDF_MITER_JOIN");
            page.EndText();

            page.SetLineJoin(HPdfLineJoin.HPDF_ROUND_JOIN);
            page.MoveTo(120, 195);
            page.LineTo(160, 235);
            page.LineTo(200, 195);
            page.Stroke();

            page.BeginText();
            page.MoveTextPos(60, 255);
            page.ShowText("HPDF_ROUND_JOIN");
            page.EndText();

            page.SetLineJoin(HPdfLineJoin.HPDF_BEVEL_JOIN);
            page.MoveTo(120, 90);
            page.LineTo(160, 130);
            page.LineTo(200, 90);
            page.Stroke();

            page.BeginText();
            page.MoveTextPos(60, 150);
            page.ShowText("HPDF_BEVEL_JOIN");
            page.EndText();

            /* Draw Rectangle */
            page.SetLineWidth(2);
            page.SetRGBStroke(0, 0, 0);
            page.SetRGBFill(0.75f, 0.0f, 0.0f);

            DrawRect(page, 300, 770, "Stroke");
            page.Stroke();

            DrawRect(page, 300, 720, "Fill");
            page.Fill();

            DrawRect(page, 300, 670, "Fill then Stroke");
            page.FillStroke();

            /* Clip Rect */
            page.GSave();  /* Save the current graphic state */
            DrawRect(page, 300, 620, "Clip Rectangle");
            page.Clip();
            page.Stroke();
            page.SetFontAndSize(font, 13);

            page.BeginText();
            page.MoveTextPos(290, 600);
            page.SetTextLeading(12);
            page.ShowText("Clip Clip Clip Clip Clip Clipi Clip Clip Clip");
            page.ShowTextNextLine("Clip Clip Clip Clip Clip Clip Clip Clip Clip");
            page.ShowTextNextLine("Clip Clip Clip Clip Clip Clip Clip Clip Clip");
            page.EndText();
            page.GRestore();

            /* Curve Example(CurveTo2) */
            float x = 330;
            float y = 440;
            float x1 = 430;
            float y1 = 530;
            float x2 = 480;
            float y2 = 470;
            float x3 = 480;
            float y3 = 90;

            page.SetRGBFill(0, 0, 0);

            page.BeginText();
            page.MoveTextPos(300, 540);
            page.ShowText("CurveTo2(x1, y1, x2. y2)");
            page.EndText();

            page.BeginText();
            page.MoveTextPos(x + 5, y - 5);
            page.ShowText("Current point");
            page.MoveTextPos(x1 - x, y1 - y);
            page.ShowText("(x1, y1)");
            page.MoveTextPos(x2 - x1, y2 - y1);
            page.ShowText("(x2, y2)");
            page.EndText();

            page.SetDash(dash_mode1, 0);

            page.SetLineWidth(0.5f);
            page.MoveTo(x1, y1);
            page.LineTo(x2, y2);
            page.Stroke();

            page.SetDash(null, 0);

            page.SetLineWidth(1.5f);

            page.MoveTo(x, y);
            page.CurveTo2(x1, y1, x2, y2);
            page.Stroke();

            /* Curve Example(CurveTo3) */
            y -= 150;
            y1 -= 150;
            y2 -= 150;

            page.BeginText();
            page.MoveTextPos(300, 390);
            page.ShowText("CurveTo3(x1, y1, x2. y2)");
            page.EndText();

            page.BeginText();
            page.MoveTextPos(x + 5, y - 5);
            page.ShowText("Current point");
            page.MoveTextPos(x1 - x, y1 - y);
            page.ShowText("(x1, y1)");
            page.MoveTextPos(x2 - x1, y2 - y1);
            page.ShowText("(x2, y2)");
            page.EndText();

            page.SetDash(dash_mode1, 0);

            page.SetLineWidth(0.5f);
            page.MoveTo(x, y);
            page.LineTo(x1, y1);
            page.Stroke();

            page.SetDash(null, 0);

            page.SetLineWidth(1.5f);
            page.MoveTo(x, y);
            page.CurveTo3(x1, y1, x2, y2);
            page.Stroke();

            /* Curve Example(CurveTo) */
            y -= 150;
            y1 -= 160;
            y2 -= 130;
            x2 += 10;

            page.BeginText();
            page.MoveTextPos(300, 240);
            page.ShowText("CurveTo(x1, y1, x2. y2, x3, y3)");
            page.EndText();

            page.BeginText();
            page.MoveTextPos(x + 5, y - 5);
            page.ShowText("Current point");
            page.MoveTextPos(x1 - x, y1 - y);
            page.ShowText("(x1, y1)");
            page.MoveTextPos(x2 - x1, y2 - y1);
            page.ShowText("(x2, y2)");
            page.MoveTextPos(x3 - x2, y3 - y2);
            page.ShowText("(x3, y3)");
            page.EndText();

            page.SetDash(dash_mode1, 0);

            page.SetLineWidth(0.5f);
            page.MoveTo(x, y);
            page.LineTo(x1, y1);
            page.Stroke();
            page.MoveTo(x2, y2);
            page.LineTo(x3, y3);
            page.Stroke();

            page.SetDash(null, 0);

            page.SetLineWidth(1.5f);
            page.MoveTo(x, y);
            page.CurveTo(x1, y1, x2, y2, x3, y3);
            page.Stroke();

            pdf.SaveToFile("LineDemo.pdf");
        } catch (Exception e) {
            Console.Error.WriteLine(e.Message);
        }
    }
}



