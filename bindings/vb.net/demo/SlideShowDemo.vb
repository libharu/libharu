Imports HPdf

Module SlideShowDemo

    Private rand As Random = New Random

    Private Sub PrintPage(ByRef page As HPdfPage, ByVal caption As String, ByRef font As HPdfFont, _
                                 ByVal type As HPdfTransitionStyle, ByRef prevpage As HPdfPage, ByRef nextpage As HPdfPage)

        Dim r As Single = rand.Next(255) / 255
        Dim g As Single = rand.Next(255) / 255
        Dim b As Single = rand.Next(255) / 255
        Dim rect As HPdfRect
        Dim dst As HPdfDestination
        Dim annot As HPdfAnnotation

        page.SetWidth(800)
        page.SetHeight(600)

        page.SetRGBFill(r, g, b)

        page.Rectangle(0, 0, 800, 600)
        page.Fill()

        page.SetRGBFill(1.0F - r, 1.0F - g, 1.0F - b)

        page.SetFontAndSize(font, 30)

        page.BeginText()
        page.SetTextMatrix(0.8F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F)
        page.TextOut(50, 530, caption)

        page.SetTextMatrix(1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F)
        page.SetFontAndSize(font, 20)
        page.TextOut(55, 300, "Type ""Ctrl+L"" in order to return from full screen mode.")
        page.EndText()

        page.SetSlideShow(type, 5.0F, 1.0F)

        page.SetFontAndSize(font, 20)

        If (Not nextpage Is Nothing) Then
            page.BeginText()
            page.TextOut(680, 50, "Next=>")
            page.EndText()

            rect.left = 680
            rect.right = 750
            rect.top = 70
            rect.bottom = 50
            dst = nextpage.CreateDestination()
            dst.SetFit()
            annot = page.CreateLinkAnnot(rect, dst)
            annot.SetBorderStyle(0, 0, 0)
            annot.SetHighlightMode(HPdfAnnotHighlightMode.HPDF_ANNOT_INVERT_BOX)
        End If

        If (Not prevpage Is Nothing) Then
            page.BeginText()
            page.TextOut(50, 50, "<=Prev")
            page.EndText()

            rect.left = 50
            rect.right = 110
            rect.top = 70
            rect.bottom = 50
            dst = prevpage.CreateDestination()
            dst.SetFit()
            annot = page.CreateLinkAnnot(rect, dst)
            annot.SetBorderStyle(0, 0, 0)
            annot.SetHighlightMode(HPdfAnnotHighlightMode.HPDF_ANNOT_INVERT_BOX)
        End If


    End Sub

    Sub Main()
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion())

        Try
            Dim pdf As HPdfDoc = New HPdfDoc()
            Dim page(17) As HPdfPage

            ' create default-font 
            Dim font As HPdfFont = pdf.GetFont("Courier", Nothing)

            ' Add 17 pages to the document. '
            For i As Integer = 1 To 17
                page(i) = pdf.AddPage()
            Next

            PrintPage(page(1), "HPDF_TS_WIPE_RIGHT", font, HPdfTransitionStyle.HPDF_TS_WIPE_RIGHT, Nothing, page(1))
            PrintPage(page(2), "HPDF_TS_WIPE_UP", font, HPdfTransitionStyle.HPDF_TS_WIPE_UP, page(0), page(2))
            PrintPage(page(3), "HPDF_TS_WIPE_LEFT", font, HPdfTransitionStyle.HPDF_TS_WIPE_LEFT, page(1), page(3))
            PrintPage(page(4), "HPDF_TS_WIPE_DOWN", font, HPdfTransitionStyle.HPDF_TS_WIPE_DOWN, page(2), page(4))
            PrintPage(page(5), "HPDF_TS_BARN_DOORS_HORIZONTAL_OUT", font, HPdfTransitionStyle.HPDF_TS_BARN_DOORS_HORIZONTAL_OUT, page(3), page(5))
            PrintPage(page(6), "HPDF_TS_BARN_DOORS_HORIZONTAL_IN", font, HPdfTransitionStyle.HPDF_TS_BARN_DOORS_HORIZONTAL_IN, page(4), page(6))
            PrintPage(page(7), "HPDF_TS_BARN_DOORS_VERTICAL_OUT", font, HPdfTransitionStyle.HPDF_TS_BARN_DOORS_VERTICAL_OUT, page(5), page(7))
            PrintPage(page(8), "HPDF_TS_BARN_DOORS_VERTICAL_IN", font, HPdfTransitionStyle.HPDF_TS_BARN_DOORS_VERTICAL_IN, page(6), page(8))
            PrintPage(page(9), "HPDF_TS_BOX_OUT", font, HPdfTransitionStyle.HPDF_TS_BOX_OUT, page(7), page(9))
            PrintPage(page(10), "HPDF_TS_BOX_IN", font, HPdfTransitionStyle.HPDF_TS_BOX_IN, page(8), page(10))
            PrintPage(page(11), "HPDF_TS_BLINDS_HORIZONTAL", font, HPdfTransitionStyle.HPDF_TS_BLINDS_HORIZONTAL, page(9), page(11))
            PrintPage(page(12), "HPDF_TS_BLINDS_VERTICAL", font, HPdfTransitionStyle.HPDF_TS_BLINDS_VERTICAL, page(10), page(12))
            PrintPage(page(13), "HPDF_TS_DISSOLVE", font, HPdfTransitionStyle.HPDF_TS_DISSOLVE, page(11), page(13))
            PrintPage(page(14), "HPDF_TS_GLITTER_RIGHT", font, HPdfTransitionStyle.HPDF_TS_GLITTER_RIGHT, page(12), page(14))
            PrintPage(page(15), "HPDF_TS_GLITTER_DOWN", font, HPdfTransitionStyle.HPDF_TS_GLITTER_DOWN, page(13), page(15))
            PrintPage(page(16), "HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT", font, HPdfTransitionStyle.HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT, page(14), page(16))
            PrintPage(page(17), "HPDF_TS_REPLACE", font, HPdfTransitionStyle.HPDF_TS_REPLACE, page(15), Nothing)

            pdf.SetPageMode(HPdfPageMode.HPDF_PAGE_MODE_FULL_SCREEN)


            ' save the document to a file 
            pdf.SaveToFile("SlideShowDemo.pdf")

        Catch ex As Exception
            Console.Error.WriteLine(ex.Message)
        End Try
    End Sub
End Module
