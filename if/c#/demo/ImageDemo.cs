/*
 * << Haru Free PDF Library 2.0.5 >> -- ImageDemo.cs
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


public class ImageDemo {
    private static void ShowDescription(HPdfPage page, float x, float y,
            string text) {
        string buf;

        page.MoveTo(x, y - 10);
        page.LineTo(x, y + 10);
        page.MoveTo(x - 10, y);
        page.LineTo(x + 10, y);
        page.Stroke();

        page.SetFontAndSize(page.GetCurrentFont(), 8);
        page.SetRGBFill(0, 0, 0);

        page.BeginText();

        buf = "(x=" + x + ",y=" + y + ")";
        page.MoveTextPos(x - page.TextWidth(buf) - 5,
            y - 10);
        page.ShowText(buf);
        page.EndText();

        page.BeginText();
        page.MoveTextPos(x - 20, y - 25);
        page.ShowText(text);
        page.EndText();
    }

    public static void Main() {
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion());

        try {
            HPdfDoc pdf = new HPdfDoc();

            pdf.SetCompressionMode(HPdfDoc.HPDF_COMP_ALL);

            /* create default-font */
            HPdfFont font = pdf.GetFont("Helvetica", null);

            /* add a new page object. */
            HPdfPage page = pdf.AddPage();

            page.SetWidth(550);
            page.SetHeight(500);

            HPdfDestination dst = page.CreateDestination();
            dst.SetXYZ(0, page.GetHeight(), 1);
            pdf.SetOpenAction(dst);

            page.BeginText();
            page.SetFontAndSize(font, 20);
            page.MoveTextPos(220, page.GetHeight() - 70);
            page.ShowText("ImageDemo");
            page.EndText();

            /* load image file. */
            HPdfImage image = pdf.LoadPngImageFromFile("demo\\pngsuite\\basn3p02.png");

            /* image1 is masked by image2. */
            HPdfImage image1 = pdf.LoadPngImageFromFile("demo\\pngsuite\\basn3p02.png");

            /* image2 is a mask image. */
            HPdfImage image2 = pdf.LoadPngImageFromFile("demo\\pngsuite\\basn0g01.png");

            /* image3 is a RGB-color image. we use this image for color-mask
             * demo.
             */
            HPdfImage image3 = pdf.LoadPngImageFromFile("demo\\pngsuite\\maskimage.png");

            float iw = image.GetWidth();
            float ih = image.GetHeight();

            page.SetLineWidth(0.5f);

            float x = 100;
            float y = page.GetHeight() - 150;

            /* Draw image to the canvas. (normal-mode with actual size.)*/
            page.DrawImage(image, x, y, iw, ih);

            ShowDescription(page, x, y, "Actual Size");

            x += 150;

            /* Scalling image (X direction) */
            page.DrawImage(image, x, y, iw * 1.5f, ih);

            ShowDescription(page, x, y, "Scalling image (X direction)");

            x += 150;

            /* Scalling image (Y direction). */
            page.DrawImage(image, x, y, iw, ih * 1.5f);
            ShowDescription(page, x, y, "Scalling image (Y direction)");

            x = 100;
            y -= 120;

            /* Skewing image. */
            float angle1 = 10;
            float angle2 = 20;
            float rad1 = angle1 / 180 * 3.141592f;
            float rad2 = angle2 / 180 * 3.141592f;

            page.GSave();

            page.Concat(iw, (float)Math.Tan(rad1) * iw, (float)Math.Tan(rad2) * ih, 
                    ih, x, y);

            page.ExecuteXObject(image);
            page.GRestore();

            ShowDescription(page, x, y, "Skewing image");

            x += 150;

            /* Rotating image */
            float angle = 30;     /* rotation of 30 degrees. */
            float rad = angle / 180 * 3.141592f; /* Calcurate the radian value. */

            page.GSave();

            page.Concat((float)(iw * Math.Cos(rad)),
                (float)(iw * Math.Sin(rad)),
                (float)(ih * -Math.Sin(rad)),
                (float)(ih * Math.Cos(rad)),
                x, y);

            page.ExecuteXObject(image);
            page.GRestore();

            ShowDescription(page, x, y, "Rotating image");

                x += 150;

            /* draw masked image. */

            /* Set image2 to the mask image of image1 */
            image1.SetMaskImage (image2);

            page.SetRGBFill(0, 0, 0);
            page.BeginText();
            page.MoveTextPos(x - 6, y + 14);
            page.ShowText("MASKMASK");
            page.EndText();

            page.DrawImage(image1, x - 3, y - 3, iw + 6, ih + 6);

            ShowDescription(page, x, y, "masked image");

            x = 100;
            y -= 120;

            /* color mask. */
            page.SetRGBFill(0, 0, 0);
            page.BeginText();
            page.MoveTextPos(x - 6, y + 14);
            page.ShowText("MASKMASK");
            page.EndText();

            image3.SetColorMask (0, 255, 0, 0, 0, 255);
            page.DrawImage(image3, x, y, iw, ih);

            ShowDescription(page, x, y, "Color Mask");

            /* save the document to a file */
            pdf.SaveToFile("ImageDemo.pdf");

        } catch (Exception e) {
            Console.Error.WriteLine(e.Message);
        }
    }
}



