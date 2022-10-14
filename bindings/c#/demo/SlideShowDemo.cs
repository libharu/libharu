/*
 * << Haru Free PDF Library 2.0.5 >> -- SlideShow.cs
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


public class TextDemo {
    private static Random rand;

    private static void PrintPage (HPdfPage page, string caption, HPdfFont font,
            HPdfTransitionStyle type, HPdfPage prev, HPdfPage next) {
        float r = (float)rand.Next(255) / 255;
        float g = (float)rand.Next(255) / 255;
        float b = (float)rand.Next(255) / 255;
        HPdfRect rect;
        HPdfDestination dst;
        HPdfAnnotation annot;
    
        page.SetWidth (800);
        page.SetHeight (600);
    
        page.SetRGBFill (r, g, b);
    
        page.Rectangle ( 0, 0, 800, 600);
        page.Fill ();
    
        page.SetRGBFill (1.0f - r, 1.0f - g, 1.0f - b);
    
        page.SetFontAndSize (font, 30);
    
        page.BeginText ();
        page.SetTextMatrix (0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);   
        page.TextOut (50, 530, caption);
    
        page.SetTextMatrix (1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);   
        page.SetFontAndSize (font, 20);
        page.TextOut (55, 300, 
                "Type \"Ctrl+L\" in order to return from full screen mode.");
        page.EndText ();
    
        page.SetSlideShow (type, 5.0f, 1.0f);
    
        page.SetFontAndSize (font, 20);
    
        if (next != null) {
            page.BeginText ();
            page.TextOut (680, 50, "Next=>");
            page.EndText ();
    
            rect.left = 680;
            rect.right = 750;
            rect.top = 70;
            rect.bottom = 50;
            dst = next.CreateDestination();
            dst.SetFit();
            annot = page.CreateLinkAnnot (rect, dst);
            annot.SetBorderStyle (0, 0, 0);
            annot.SetHighlightMode (HPdfAnnotHighlightMode.HPDF_ANNOT_INVERT_BOX);
        } 
    
        if (prev != null) {
            page.BeginText ();
            page.TextOut (50, 50, "<=Prev");
            page.EndText ();
    
            rect.left = 50;
            rect.right = 110;
            rect.top = 70;
            rect.bottom = 50;
            dst = prev.CreateDestination();
            dst.SetFit();
            annot = page.CreateLinkAnnot (rect, dst);
            annot.SetBorderStyle (0, 0, 0);
            annot.SetHighlightMode (HPdfAnnotHighlightMode.HPDF_ANNOT_INVERT_BOX);
        }
    }


    public static void Main() {
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion());

        rand = new Random();

        try {
            HPdfDoc pdf = new HPdfDoc();
            HPdfPage[] page = new HPdfPage[17];

            /* create default-font */
            HPdfFont font = pdf.GetFont ("Courier", null);
        
            /* Add 17 pages to the document. */
            page[0] = pdf.AddPage();
            page[1] = pdf.AddPage();
            page[2] = pdf.AddPage();
            page[3] = pdf.AddPage();
            page[4] = pdf.AddPage();
            page[5] = pdf.AddPage();
            page[6] = pdf.AddPage();
            page[7] = pdf.AddPage();
            page[8] = pdf.AddPage();
            page[9] = pdf.AddPage();
            page[10] = pdf.AddPage();
            page[11] = pdf.AddPage();
            page[12] = pdf.AddPage();
            page[13] = pdf.AddPage();
            page[14] = pdf.AddPage();
            page[15] = pdf.AddPage();
            page[16] = pdf.AddPage();
        
            PrintPage(page[0], "HPDF_TS_WIPE_RIGHT", font, 
                    HPdfTransitionStyle.HPDF_TS_WIPE_RIGHT, null, page[1]);
            PrintPage(page[1], "HPDF_TS_WIPE_UP", font, 
                    HPdfTransitionStyle.HPDF_TS_WIPE_UP, page[0], page[2]);
            PrintPage(page[2], "HPDF_TS_WIPE_LEFT", font, 
                    HPdfTransitionStyle.HPDF_TS_WIPE_LEFT, page[1], page[3]);
            PrintPage(page[3], "HPDF_TS_WIPE_DOWN", font, 
                    HPdfTransitionStyle.HPDF_TS_WIPE_DOWN, page[2], page[4]);
            PrintPage(page[4], "HPDF_TS_BARN_DOORS_HORIZONTAL_OUT", font, 
                    HPdfTransitionStyle.HPDF_TS_BARN_DOORS_HORIZONTAL_OUT, page[3], page[5]);
            PrintPage(page[5], "HPDF_TS_BARN_DOORS_HORIZONTAL_IN", font, 
                    HPdfTransitionStyle.HPDF_TS_BARN_DOORS_HORIZONTAL_IN, page[4], page[6]);
            PrintPage(page[6], "HPDF_TS_BARN_DOORS_VERTICAL_OUT", font, 
                    HPdfTransitionStyle.HPDF_TS_BARN_DOORS_VERTICAL_OUT, page[5], page[7]);
            PrintPage(page[7], "HPDF_TS_BARN_DOORS_VERTICAL_IN", font, 
                    HPdfTransitionStyle.HPDF_TS_BARN_DOORS_VERTICAL_IN, page[6], page[8]);
            PrintPage(page[8], "HPDF_TS_BOX_OUT", font, 
                    HPdfTransitionStyle.HPDF_TS_BOX_OUT, page[7], page[9]);
            PrintPage(page[9], "HPDF_TS_BOX_IN", font, 
                    HPdfTransitionStyle.HPDF_TS_BOX_IN, page[8], page[10]);
            PrintPage(page[10], "HPDF_TS_BLINDS_HORIZONTAL", font, 
                    HPdfTransitionStyle.HPDF_TS_BLINDS_HORIZONTAL, page[9], page[11]);
            PrintPage(page[11], "HPDF_TS_BLINDS_VERTICAL", font, 
                    HPdfTransitionStyle.HPDF_TS_BLINDS_VERTICAL, page[10], page[12]);
            PrintPage(page[12], "HPDF_TS_DISSOLVE", font, 
                    HPdfTransitionStyle.HPDF_TS_DISSOLVE, page[11], page[13]);
            PrintPage(page[13], "HPDF_TS_GLITTER_RIGHT", font, 
                    HPdfTransitionStyle.HPDF_TS_GLITTER_RIGHT, page[12], page[14]);
            PrintPage(page[14], "HPDF_TS_GLITTER_DOWN", font, 
                    HPdfTransitionStyle.HPDF_TS_GLITTER_DOWN, page[13], page[15]);
            PrintPage(page[15], "HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT", font, 
                    HPdfTransitionStyle.HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT, page[14], page[16]);
            PrintPage(page[16], "HPDF_TS_REPLACE", font, 
                    HPdfTransitionStyle.HPDF_TS_REPLACE, page[15], null);
        
        
            pdf.SetPageMode (HPdfPageMode.HPDF_PAGE_MODE_FULL_SCREEN);
        
            /* save the document to a file */
            pdf.SaveToFile("SlideShowDemo.pdf");

        } catch (Exception e) {
            Console.Error.WriteLine(e.Message);
        }
    }
}



