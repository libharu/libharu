Imports HPdf

Module RawImageDemo

    Sub Main()
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion())

        Dim raw_image_data() As Byte = { _
           &HFF, &HFF, &HFF, &HFE, &HFF, &HFF, &HFF, &HFC, _
           &HFF, &HFF, &HFF, &HF8, &HFF, &HFF, &HFF, &HF0, _
           &HF3, &HF3, &HFF, &HE0, &HF3, &HF3, &HFF, &HC0, _
           &HF3, &HF3, &HFF, &H80, &HF3, &H33, &HFF, &H0, _
           &HF3, &H33, &HFE, &H0, &HF3, &H33, &HFC, &H0, _
           &HF8, &H7, &HF8, &H0, &HF8, &H7, &HF0, &H0, _
           &HFC, &HCF, &HE0, &H0, &HFC, &HCF, &HC0, &H0, _
           &HFF, &HFF, &H80, &H0, &HFF, &HFF, &H0, &H0, _
           &HFF, &HFE, &H0, &H0, &HFF, &HFC, &H0, &H0, _
           &HFF, &HF8, &HF, &HE0, &HFF, &HF0, &HF, &HE0, _
           &HFF, &HE0, &HC, &H30, &HFF, &HC0, &HC, &H30, _
           &HFF, &H80, &HF, &HE0, &HFF, &H0, &HF, &HE0, _
           &HFE, &H0, &HC, &H30, &HFC, &H0, &HC, &H30, _
           &HF8, &H0, &HF, &HE0, &HF0, &H0, &HF, &HE0, _
           &HE0, &H0, &H0, &H0, &HC0, &H0, &H0, &H0, _
           &H80, &H0, &H0, &H0, &H0, &H0, &H0, &H0 _
       }

        Try
            Dim pdf As HPdfDoc = New HPdfDoc()

            pdf.SetCompressionMode(HPdfDoc.HPDF_COMP_ALL)

            ' create default-font 
            Dim font As HPdfFont = pdf.GetFont("Helvetica", Nothing)

            ' add a new page object. 
            Dim page As HPdfPage = pdf.AddPage()

            page.SetWidth(172)
            page.SetHeight(80)

            page.BeginText()
            page.SetFontAndSize(font, 20)
            page.MoveTextPos(220, page.GetHeight() - 70)
            page.ShowText("RawImageDemo")
            page.EndText()

            ' load RGB raw-image file.
            Dim image As HPdfImage = pdf.LoadRawImageFromFile("demo\\rawimage\\32_32_rgb.dat", 32, 32, HPdfColorSpace.HPDF_CS_DEVICE_RGB)

            Dim x As Single = 20
            Dim y As Single = 20

            ' Draw image to the canvas. (normal-mode with actual size.)
            page.DrawImage(image, x, y, 32, 32)

            ' load GrayScale raw-image file. 
            image = pdf.LoadRawImageFromFile("demo\\rawimage\\32_32_gray.dat", 32, 32, HPdfColorSpace.HPDF_CS_DEVICE_GRAY)

            x = 70
            y = 20

            ' Draw image to the canvas. (normal-mode with actual size.)
            page.DrawImage(image, x, y, 32, 32)

            ' load GrayScale raw-image (1bit) file from memory.
            image = pdf.LoadRawImageFromMem(raw_image_data, 32, 32, HPdfColorSpace.HPDF_CS_DEVICE_GRAY, 1)

            x = 120
            y = 20

            ' Draw image to the canvas. (normal-mode with actual size.)
            page.DrawImage(image, x, y, 32, 32)

            ' save the document to a file 
            pdf.SaveToFile("RawImageDemo.pdf")

        Catch ex As Exception
            Console.Error.WriteLine(ex.Message)
        End Try
    End Sub
End Module
