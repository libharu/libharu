Imports HPdf

Module ImageDemo
    Private Sub ShowDescription(ByRef page As HPdfPage, ByVal x As Single, ByVal y As Single, ByVal text As String)
        Dim buf As String

        page.MoveTo(x, y - 10)
        page.LineTo(x, y + 10)
        page.MoveTo(x - 10, y)
        page.LineTo(x + 10, y)
        page.Stroke()

        page.SetFontAndSize(page.GetCurrentFont(), 8)
        page.SetRGBFill(0, 0, 0)

        page.BeginText()

        buf = "(x=" & x & ",y=" & y & ")"
        page.MoveTextPos(x - page.TextWidth(buf) - 5, y - 10)
        page.ShowText(buf)
        page.EndText()

        page.BeginText()
        page.MoveTextPos(x - 20, y - 25)
        page.ShowText(text)
        page.EndText()
    End Sub

    Sub Main()
        Console.WriteLine("libhpdf-" & HPdfDoc.HPdfGetVersion())

        Try
            Dim pdf As HPdfDoc = New HPdfDoc()

            pdf.SetCompressionMode(HPdfDoc.HPDF_COMP_ALL)

            ' create default-font
            Dim font As HPdfFont = pdf.GetFont("Helvetica", Nothing)

            ' add a new page object.
            Dim page As HPdfPage = pdf.AddPage()

            page.SetWidth(550)
            page.SetHeight(500)

            Dim dst As HPdfDestination = page.CreateDestination()
            dst.SetXYZ(0, page.GetHeight(), 1)
            pdf.SetOpenAction(dst)

            page.BeginText()
            page.SetFontAndSize(font, 20)
            page.MoveTextPos(220, page.GetHeight() - 70)
            page.ShowText("ImageDemo")
            page.EndText()

            ' load image file. 
            Dim image As HPdfImage = pdf.LoadPngImageFromFile("demo\\pngsuite\\basn3p02.png")

            ' image1 is masked by image2.
            Dim image1 As HPdfImage = pdf.LoadPngImageFromFile("demo\\pngsuite\\basn3p02.png")

            ' image2 is a mask image. 
            Dim image2 As HPdfImage = pdf.LoadPngImageFromFile("demo\\pngsuite\\basn0g01.png")

            ' image3 is a RGB-color image. we use this image for color-mask
            ' demo.
            '
            Dim image3 As HPdfImage = pdf.LoadPngImageFromFile("demo\\pngsuite\\maskimage.png")

            Dim iw As Single = image.GetWidth()
            Dim ih As Single = image.GetHeight()

            page.SetLineWidth(0.5F)

            Dim x As Single = 100
            Dim y As Single = page.GetHeight() - 150

            ' Draw image to the canvas. (normal-mode with actual size.)
            page.DrawImage(image, x, y, iw, ih)

            ShowDescription(page, x, y, "Actual Size")

            x += 150

            ' Scalling image (X direction)
            page.DrawImage(image, x, y, iw * 1.5F, ih)

            ShowDescription(page, x, y, "Scalling image (X direction)")

            x += 150

            ' Scalling image (Y direction).
            page.DrawImage(image, x, y, iw, ih * 1.5F)
            ShowDescription(page, x, y, "Scalling image (Y direction)")

            x = 100
            y -= 120

            ' Skewing image. 
            Dim angle1 As Single = 10
            Dim angle2 As Single = 20
            Dim rad1 As Single = angle1 / 180 * 3.141592F
            Dim rad2 As Single = angle2 / 180 * 3.141592F

            page.GSave()

            page.Concat(iw, Math.Tan(rad1) * iw, Math.Tan(rad2) * ih, ih, x, y)

            page.ExecuteXObject(image)
            page.GRestore()

            ShowDescription(page, x, y, "Skewing image")

            x += 150

            ' Rotating image 
            Dim angle As Single = 30                        ' rotation of 30 degrees.
            Dim rad As Single = angle / 180 * 3.141592F     ' Calcurate the radian value.

            page.GSave()

            page.Concat((iw * Math.Cos(rad)), (iw * Math.Sin(rad)), (ih * -Math.Sin(rad)), (ih * Math.Cos(rad)), x, y)

            page.ExecuteXObject(image)
            page.GRestore()

            ShowDescription(page, x, y, "Rotating image")

            x += 150

            '  draw masked image.

            '  Set image2 to the mask image of image1
            image1.SetMaskImage(image2)

            page.SetRGBFill(0, 0, 0)
            page.BeginText()
            page.MoveTextPos(x - 6, y + 14)
            page.ShowText("MASKMASK")
            page.EndText()

            page.DrawImage(image1, x - 3, y - 3, iw + 6, ih + 6)

            ShowDescription(page, x, y, "masked image")

            x = 100
            y -= 120

            ' color mask.
            page.SetRGBFill(0, 0, 0)
            page.BeginText()
            page.MoveTextPos(x - 6, y + 14)
            page.ShowText("MASKMASK")
            page.EndText()

            image3.SetColorMask(0, 255, 0, 0, 0, 255)
            page.DrawImage(image3, x, y, iw, ih)

            ShowDescription(page, x, y, "Color Mask")

            ' save the document to a file 
            pdf.SaveToFile("ImageDemo.pdf")

        Catch ex As Exception
            Console.Error.WriteLine(ex.Message)
        End Try
    End Sub

End Module
    
