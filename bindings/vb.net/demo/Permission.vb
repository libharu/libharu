Imports HPdf

Module Permission

    Sub Main()
        Const owner_passwd As String = "owner"
        Const user_passwd As String = ""
        Const text As String = "User cannot print and copy this document."
        Console.WriteLine("libhpdf-" + HPdfDoc.HPdfGetVersion())

        Try
            Dim pdf As HPdfDoc = New HPdfDoc()

            ' create default-font 
            Dim font As HPdfFont = pdf.GetFont("Helvetica", Nothing)

            ' add a new page object. 
            Dim page As HPdfPage = pdf.AddPage()

            page.SetSize(HPdfPageSizes.HPDF_PAGE_SIZE_B5, HPdfPageDirection.HPDF_PAGE_LANDSCAPE)

            page.BeginText()
            page.SetFontAndSize(font, 20)
            Dim tw As Single = page.TextWidth(text)
            page.MoveTextPos((page.GetWidth() - tw) / 2, (page.GetHeight() - 20) / 2)
            page.ShowText(text)
            page.EndText()

            pdf.SetPassword(owner_passwd, user_passwd)
            pdf.SetPermission(HPdfDoc.HPDF_ENABLE_READ)

            ' use 128 bit revision 3 encryption
            pdf.SetEncryptionMode(HPdfEncryptMode.HPDF_ENCRYPT_R3, 16)

            ' save the document to a file
            pdf.SaveToFile("Permission.pdf")

        Catch ex As Exception
            Console.Error.WriteLine(ex.Message)
        End Try
    End Sub
End Module
