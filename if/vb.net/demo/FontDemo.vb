Imports HPdf

Module TextDemo

    Dim font_list As String() = {"Courier", _
                                    "Courier-Bold", _
                                    "Courier-Oblique", _
                                    "Courier-BoldOblique", _
                                    "Helvetica", _
                                    "Helvetica-Bold", _
                                    "Helvetica-Oblique", _
                                    "Helvetica-BoldOblique", _
                                    "Times-Roman", _
                                    "Times-Bold", _
                                    "Times-Italic", _
                                    "Times-BoldItalic", _
                                    "Symbol", _
                                    "ZapfDingbats"}

    Sub Main()
        Console.WriteLine("libhpdf-" & HPdfDoc.HPdfGetVersion())

        Try
            Const page_title As String = "FontDemo"

            Dim pdf As HPdfDoc = New HPdfDoc()
            Dim page As HPdfPage = pdf.AddPage()

            Dim height As Single = page.GetHeight()
            Dim width As Single = page.GetWidth()

            ' Print the lines of the page. 
            page.SetLineWidth(1)
            page.Rectangle(50, 50, width - 100, height - 110)
            page.Stroke()

            ' Print the title of the page (with positioning center). 
            Dim def_font As HPdfFont = pdf.GetFont("Helvetica", Nothing)
            page.SetFontAndSize(def_font, 24)

            Dim tw As Single = page.TextWidth(page_title)
            page.BeginText()
            page.TextOut((width - tw) / 2, height - 50, page_title)
            page.EndText()

            ' output subtitle.
            page.BeginText()
            page.SetFontAndSize(def_font, 16)
            page.TextOut(60, height - 80, "<Standard Type1 fonts samples>")
            page.EndText()

            page.BeginText()
            page.MoveTextPos(60, height - 105)

            For i As Integer = 1 To font_list.Length - 1

                Const samp_text As String = "abcdefgABCDEFG12345!#$%&+-@?"
                Dim font As HPdfFont = pdf.GetFont(font_list(i), Nothing)

                ' print a label of text 
                page.SetFontAndSize(def_font, 9)
                page.ShowText(font_list(i))
                page.MoveTextPos(0, -18)

                ' print a sample text. 
                page.SetFontAndSize(font, 20)
                page.ShowText(samp_text)
                page.MoveTextPos(0, -20)
            Next

            page.EndText()

            pdf.SaveToFile("FontDemo.pdf")

        Catch ex As Exception
            Console.Error.WriteLine(ex.Message)
        End Try
    End Sub

End Module
    