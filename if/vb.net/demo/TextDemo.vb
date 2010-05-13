Imports HPdf

Module TextDemo

    Private Sub ShowStripePattern(ByRef page As HPdfPage, ByVal x As Single, ByVal y As Single)
        Dim iy As Integer = 0

        Do While (iy < 50)
            page.SetRGBStroke(0.0F, 0.0F, 0.5F)
            page.SetLineWidth(1)
            page.MoveTo(x, y + iy)
            page.LineTo(x + page.TextWidth("ABCabc123"), y + iy)
            page.Stroke()
            iy += 3

        Loop

        page.SetLineWidth(2.5F)
    End Sub

    Private Sub ShowDescription(ByRef page As HPdfPage, ByVal x As Single, ByVal y As Single, ByVal text As String)
        Dim fsize As Single = page.GetCurrentFontSize()
        Dim font As HPdfFont = page.GetCurrentFont()
        Dim c As HPdfRGBColor = page.GetRGBFill()

        page.BeginText()
        page.SetRGBFill(0, 0, 0)
        page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_FILL)
        page.SetFontAndSize(font, 10)
        page.TextOut(x, y - 12, text)
        page.EndText()

        page.SetFontAndSize(font, fsize)
        page.SetRGBFill(c.r, c.g, c.b)
    End Sub

    Sub Main()
        Const page_title As String = "Text Demo"
        Const samp_text As String = "abcdefgABCDEFG123!#$%&+-@?"
        Const samp_text2 As String = "The quick brown fox jumps over the lazy dog."
        Console.WriteLine("libhpdf-" & HPdfDoc.HPdfGetVersion())

        Try
            Dim pdf As HPdfDoc = New HPdfDoc()

            pdf.SetCompressionMode(HPdfDoc.HPDF_COMP_ALL)

            ' create default-font 
            Dim font As HPdfFont = pdf.GetFont("Helvetica", Nothing)

            ' add a new page object. 
            Dim page As HPdfPage = pdf.AddPage()

            ' print the title of the page (with positioning center).
            page.SetFontAndSize(font, 24)
            Dim tw As Single = page.TextWidth(page_title)
            page.BeginText()
            page.TextOut((page.GetWidth() - tw) / 2, page.GetHeight() - 50, page_title)
            page.EndText()

            page.BeginText()
            page.MoveTextPos(60, page.GetHeight() - 60)

            '
            ' font size
            '
            Dim fsize As Single = 8
            While (fsize < 60)

                ' set style and size of font.
                page.SetFontAndSize(font, fsize)

                ' set the position of the text.
                page.MoveTextPos(0, -5 - fsize)

                ' measure the number of characters which included in the page.
                Dim tlen As UInt32 = page.MeasureText(samp_text, page.GetWidth() - 120, False)

                page.ShowText(samp_text.Substring(0, tlen))

                ' print the description.
                page.MoveTextPos(0, -10)
                page.SetFontAndSize(font, 8)
                page.ShowText("Fontsize=" & fsize)

                fsize *= 1.5
            End While

            '
            ' font color
            '
            page.SetFontAndSize(font, 8)
            page.MoveTextPos(0, -30)
            page.ShowText("Font color")

            page.SetFontAndSize(font, 18)
            page.MoveTextPos(0, -20)
            Dim len As Integer = samp_text.Length

            For i As Integer = 0 To len - 1
                Dim buf As String

                Dim r As Single = i / len
                Dim g As Single = 1 - (i / len)
                buf = samp_text.Substring(i, 1)

                page.SetRGBFill(r, g, 0)
                page.ShowText(buf)
            Next

            page.MoveTextPos(0, -25)

            For i As Integer = 0 To len - 1
                Dim buf As String

                Dim r As Single = i / len
                Dim b As Single = 1 - (i / len)
                buf = samp_text.Substring(i, 1)

                page.SetRGBFill(r, 0, b)
                page.ShowText(buf)
            Next

            page.MoveTextPos(0, -25)

            For i As Integer = 0 To len - 1
                Dim buf As String

                Dim b As Single = i / len
                Dim g As Single = 1 - (i / len)
                buf = samp_text.Substring(i, 1)

                page.SetRGBFill(0, g, b)
                page.ShowText(buf)
            Next

            page.EndText()

            Dim ypos As Integer = 450

            '
            ' Font rendering mode
            '
            page.SetFontAndSize(font, 32)
            page.SetRGBFill(0.5F, 0.5F, 0)
            page.SetLineWidth(1.5F)

            ' PDF_FILL 
            ShowDescription(page, 60, ypos, "RenderingMode=PDF_FILL")
            page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_FILL)
            page.BeginText()
            page.TextOut(60, ypos, "ABCabc123")
            page.EndText()

            ' PDF_STROKE
            ShowDescription(page, 60, ypos - 50, "RenderingMode=PDF_STROKE")
            page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_STROKE)
            page.BeginText()
            page.TextOut(60, ypos - 50, "ABCabc123")
            page.EndText()

            ' PDF_FILL_THEN_STROKE
            ShowDescription(page, 60, ypos - 100, "RenderingMode=PDF_FILL_THEN_STROKE")
            page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_FILL_THEN_STROKE)
            page.BeginText()
            page.TextOut(60, ypos - 100, "ABCabc123")
            page.EndText()

            ' PDF_FILL_CLIPPING 
            ShowDescription(page, 60, ypos - 150, "RenderingMode=PDF_FILL_CLIPPING")
            page.GSave()
            page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_FILL_CLIPPING)
            page.BeginText()
            page.TextOut(60, ypos - 150, "ABCabc123")
            page.EndText()
            ShowStripePattern(page, 60, ypos - 150)
            page.GRestore()

            ' PDF_STROKE_CLIPPING
            ShowDescription(page, 60, ypos - 200, "RenderingMode=PDF_STROKE_CLIPPING")
            page.GSave()
            page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_STROKE_CLIPPING)
            page.BeginText()
            page.TextOut(60, ypos - 200, "ABCabc123")
            page.EndText()
            ShowStripePattern(page, 60, ypos - 200)
            page.GRestore()

            ' PDF_FILL_STROKE_CLIPPING
            ShowDescription(page, 60, ypos - 250, "RenderingMode=PDF_FILL_STROKE_CLIPPING")
            page.GSave()
            page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_FILL_STROKE_CLIPPING)
            page.BeginText()
            page.TextOut(60, ypos - 250, "ABCabc123")
            page.EndText()
            ShowStripePattern(page, 60, ypos - 250)
            page.GRestore()

            ' Reset text attributes
            page.SetTextRenderingMode(HPdfTextRenderingMode.HPDF_FILL)
            page.SetRGBFill(0, 0, 0)
            page.SetFontAndSize(font, 30)


            '
            ' Rotating text
            '
            Dim angle1 As Single = 30                       ' A rotation of 30 degrees.
            Dim rad1 As Single = angle1 / 180 * 3.141592F   ' Calculate the radian value.

            ShowDescription(page, 320, ypos - 60, "Rotating text")
            page.BeginText()
            page.SetTextMatrix(Math.Cos(rad1), Math.Sin(rad1), -Math.Sin(rad1), Math.Cos(rad1), 330, ypos - 60)
            page.ShowText("ABCabc123")
            page.EndText()


            '
            ' Skewing text.
            '
            ShowDescription(page, 320, ypos - 120, "Skewing text")
            page.BeginText()

            angle1 = 10
            Dim angle2 As Single = 20
            rad1 = angle1 / 180 * 3.141592F
            Dim rad2 As Single = angle2 / 180 * 3.141592F

            page.SetTextMatrix(1, Math.Tan(rad1), Math.Tan(rad2), 1, 320, ypos - 120)
            page.ShowText("ABCabc123")
            page.EndText()


            '
            ' scaling text (X direction)
            '
            ShowDescription(page, 320, ypos - 175, "Scaling text (X direction)")
            page.BeginText()
            page.SetTextMatrix(1.5F, 0, 0, 1, 320, ypos - 175)
            page.ShowText("ABCabc12")
            page.EndText()


            '
            ' scaling text (Y direction)
            '
            ShowDescription(page, 320, ypos - 250, "Scaling text (Y direction)")
            page.BeginText()
            page.SetTextMatrix(1, 0, 0, 2, 320, ypos - 250)
            page.ShowText("ABCabc123")
            page.EndText()


            '
            ' char spacing, word spacing
            '

            ShowDescription(page, 60, 140, "char-spacing 0")
            ShowDescription(page, 60, 100, "char-spacing 1.5")
            ShowDescription(page, 60, 60, "char-spacing 1.5, word-spacing 2.5")

            page.SetFontAndSize(font, 20)
            page.SetRGBFill(0.1F, 0.3F, 0.1F)

            ' char-spacing 0
            page.BeginText()
            page.TextOut(60, 140, samp_text2)
            page.EndText()

            ' char-spacing 1.5
            page.SetCharSpace(1.5F)

            page.BeginText()
            page.TextOut(60, 100, samp_text2)
            page.EndText()

            ' char-spacing 1.5, word-spacing 3.5
            page.SetWordSpace(2.5F)

            page.BeginText()
            page.TextOut(60, 60, samp_text2)
            page.EndText()

            ' save the document to a file
            pdf.SaveToFile("TextDemo.pdf")


        Catch ex As Exception
            Console.Error.WriteLine(ex.Message)
        End Try
    End Sub

End Module
