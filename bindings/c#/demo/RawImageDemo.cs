/*
 * << Haru Free PDF Library 2.0.5 >> -- RawImageDemo.cs
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


public class RawImageDemo {

    public static void Main() {
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion());

        byte[] raw_image_data = new byte[] {
            0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xfc,
            0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xf0,
            0xf3, 0xf3, 0xff, 0xe0, 0xf3, 0xf3, 0xff, 0xc0,
            0xf3, 0xf3, 0xff, 0x80, 0xf3, 0x33, 0xff, 0x00,
            0xf3, 0x33, 0xfe, 0x00, 0xf3, 0x33, 0xfc, 0x00,
            0xf8, 0x07, 0xf8, 0x00, 0xf8, 0x07, 0xf0, 0x00,
            0xfc, 0xcf, 0xe0, 0x00, 0xfc, 0xcf, 0xc0, 0x00,
            0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00,
            0xff, 0xfe, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00,
            0xff, 0xf8, 0x0f, 0xe0, 0xff, 0xf0, 0x0f, 0xe0,
            0xff, 0xe0, 0x0c, 0x30, 0xff, 0xc0, 0x0c, 0x30,
            0xff, 0x80, 0x0f, 0xe0, 0xff, 0x00, 0x0f, 0xe0,
            0xfe, 0x00, 0x0c, 0x30, 0xfc, 0x00, 0x0c, 0x30,
            0xf8, 0x00, 0x0f, 0xe0, 0xf0, 0x00, 0x0f, 0xe0,
            0xe0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };

        try {
            HPdfDoc pdf = new HPdfDoc();

            pdf.SetCompressionMode(HPdfDoc.HPDF_COMP_ALL);

            /* create default-font */
            HPdfFont font = pdf.GetFont("Helvetica", null);

            /* add a new page object. */
            HPdfPage page = pdf.AddPage();

            page.SetWidth(172);
            page.SetHeight(80);

            page.BeginText();
            page.SetFontAndSize(font, 20);
            page.MoveTextPos(220, page.GetHeight() - 70);
            page.ShowText("RawImageDemo");
            page.EndText();

            /* load RGB raw-image file. */
            HPdfImage image = pdf.LoadRawImageFromFile("demo\\rawimage\\32_32_rgb.dat",
                    32, 32, HPdfColorSpace.HPDF_CS_DEVICE_RGB);

            float x = 20;  
            float y = 20;

            /* Draw image to the canvas. (normal-mode with actual size.)*/
            page.DrawImage(image, x, y, 32, 32);

            /* load GrayScale raw-image file. */
            image = pdf.LoadRawImageFromFile("demo\\rawimage\\32_32_gray.dat",
                    32, 32, HPdfColorSpace.HPDF_CS_DEVICE_GRAY);

            x = 70;
            y = 20;

            /* Draw image to the canvas. (normal-mode with actual size.)*/
            page.DrawImage(image, x, y, 32, 32);

            /* load GrayScale raw-image (1bit) file from memory. */
            image = pdf.LoadRawImageFromMem(raw_image_data, 32, 32,
                        HPdfColorSpace.HPDF_CS_DEVICE_GRAY, 1);

            x = 120;
            y = 20;

            /* Draw image to the canvas. (normal-mode with actual size.)*/
            page.DrawImage(image, x, y, 32, 32);

            /* save the document to a file */
            pdf.SaveToFile("RawImageDemo.pdf");

        } catch (Exception e) {
            Console.Error.WriteLine(e.Message);
        }
    }
}



