Imports HPdf

Module OutlineDemo
    Private Sub PrintPage(ByRef page As HPdfPage, ByVal page_num As Integer)
        page.SetWidth(800)
        page.SetHeight(800)

        page.BeginText()
        page.MoveTextPos(30, 740)
        Dim buf As String = "Page:" & page_num
        page.ShowText(buf)
        page.EndText()
    End Sub

    Sub Main()
        Console.WriteLine("libhpdf-" & HPdfDoc.HPdfGetVersion())

        Try
            Dim pdf As HPdfDoc = New HPdfDoc()

            pdf.SetCompressionMode(HPdfDoc.HPDF_COMP_ALL)

            ' create default-font
            Dim font As HPdfFont = pdf.GetFont("Helvetica", Nothing)

            pdf.SetPageMode(HPdfPageMode.HPDF_PAGE_MODE_USE_OUTLINE)

            ' add a new page object. '
            ' Add 3 pages to the document. '
            Dim page0 As HPdfPage = pdf.AddPage()
            page0.SetFontAndSize(font, 30)
            PrintPage(page0, 1)

            Dim page1 As HPdfPage = pdf.AddPage()
            page1.SetFontAndSize(font, 30)
            PrintPage(page1, 2)

            Dim page2 As HPdfPage = pdf.AddPage()
            page2.SetFontAndSize(font, 30)
            PrintPage(page2, 3)

            ' create outline root.
            Dim root As HPdfOutline = pdf.CreateOutline(Nothing, "OutlineRoot", Nothing)
            root.SetOpened(True)

            Dim outline0 As HPdfOutline = pdf.CreateOutline(root, "page1", Nothing)
            Dim outline1 As HPdfOutline = pdf.CreateOutline(root, "page2", Nothing)

            ' create outline with test which is ISO8859-2 encoding '
            Dim outline2 As HPdfOutline = pdf.CreateOutline(root, "ISO8859-2 text гдежзий", pdf.GetEncoder("ISO8859-2"))

            ' create destination objects on each pages
            ' and link it to outline items.
            '
            Dim dst As HPdfDestination = page0.CreateDestination()
            dst.SetXYZ(0, page0.GetHeight(), 1)
            outline0.SetDestination(dst)

            dst = page1.CreateDestination()
            dst.SetXYZ(0, page1.GetHeight(), 1)
            outline1.SetDestination(dst)

            dst = page2.CreateDestination()
            dst.SetXYZ(0, page2.GetHeight(), 1)
            outline2.SetDestination(dst)

            ' save the document to a file
            pdf.SaveToFile("OutlineDemo.pdf")

        Catch ex As Exception
            Console.Error.WriteLine(ex.Message)
        End Try
    End Sub

End Module
    