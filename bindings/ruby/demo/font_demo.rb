#
# << Haru Free PDF Library 2.0.0 >> -- font_example.rb
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

font_list = ["Courier", "Courier-Bold", "Courier-Oblique", "Courier-BoldOblique", "Helvetica", "Helvetica-Bold", "Helvetica-Oblique", "Helvetica-BoldOblique", "Times-Roman", "Times-Bold", "Times-Italic", "Times-BoldItalic", "Symbol", "ZapfDingbats", nil]

pdf = HPDFDoc.new

page = pdf.add_page
height = page.get_height
width = page.get_width

page.set_line_width(1.0)
page.rectangle(50.0, 50.0, width - 100.0, height - 110.0)
page.stroke

font1 = pdf.get_font("Helvetica", nil)

title = "Font Example"
page.set_font_and_size(font1, 24.0)
tw = page.text_width(title)
page.begin_text
page.text_out((width - tw) / 2, height - 50.0, title)
page.set_font_and_size(font1, 16.0)
page.text_out(60.0, height - 80.0, "<Standerd Type1 fonts samples>")
page.end_text

samp_text = "abcdefgABCDEFG12345!#$\%&+-@?"

page.begin_text
page.move_text_pos(60.0, height - 105.0)

i = 0
while font_list[i]
  font2 = pdf.get_font(font_list[i], nil)

  page.set_font_and_size(font1, 9.0)
  page.show_text(font_list[i])
  page.move_text_pos(0.0, -18.0)

  page.set_font_and_size(font2, 20.0)
  page.show_text(samp_text)
  page.move_text_pos(0.0, -20.0)

  i = i + 1
end

page.end_text
pdf.save_to_file($0 + ".pdf")

