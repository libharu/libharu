#
# << Haru Free PDF Library 2.0.0 >> -- encryption.rb
#
# Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
#
# Permission to use, copy, modify, distribute and sell this software
# and its documentation for any purpose is hereby granted without fee,
# provided that the above copyright notice appear in all copies and
# that both that copyright notice and this permission notice appear
# in supporting documentation.
# It is provided "as is" without express or implied warranty.
#

require "hpdf"

pdf = HPDFDoc.new

text = "This is an encrypt document example."
owner_passwd = "owner"
user_passwd = "user"

font1 = pdf.get_font("Helvetica", nil)

page = pdf.add_page

page.set_size(HPDFDoc::HPDF_PAGE_SIZE_B5, HPDFDoc::HPDF_PAGE_LANDSCAPE)

page.begin_text
page.set_font_and_size(font1, 20)
page.text_rect(0, page.get_height / 2 + 20, page.get_width, page.get_height / 2 -10, text, HPDFDoc::HPDF_TALIGN_CENTER)
page.end_text

pdf.set_password(owner_passwd, user_passwd)

pdf.save_to_file($0 + ".pdf")

