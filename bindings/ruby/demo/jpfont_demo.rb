#
# << Alternative PDF Library 1.0.0 >> -- font_example.rb
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

SAMP_TEXT1 = "abcdefgABCDEFG123!#$\%&+-@?"
SAMP_TEXT2 = "アメンボ赤いなあいうえお。浮き藻に小エビもおよいでる。"

pdf = HPDFDoc.new

pdf.set_compression_mode(HPDFDoc::HPDF_COMP_ALL)
pdf.use_jp_fonts
pdf.use_jp_encodings

title_font = pdf.get_font("Helvetica", nil)

font = Array.new(16)

font[0] = pdf.get_font("MS-Mincyo", "90ms-RKSJ-H")
font[1] = pdf.get_font("MS-Mincyo,Bold", "90ms-RKSJ-H")
font[2] = pdf.get_font("MS-Mincyo,Italic", "90ms-RKSJ-H")
font[3] = pdf.get_font("MS-Mincyo,BoldItalic", "90ms-RKSJ-H")
font[4] = pdf.get_font("MS-PMincyo", "90msp-RKSJ-H")
font[5] = pdf.get_font("MS-PMincyo,Bold", "90msp-RKSJ-H")
font[6] = pdf.get_font("MS-PMincyo,Italic", "90msp-RKSJ-H")
font[7] = pdf.get_font("MS-PMincyo,BoldItalic", "90msp-RKSJ-H")
font[8] = pdf.get_font("MS-Gothic", "90ms-RKSJ-H")
font[9] = pdf.get_font("MS-Gothic,Bold", "90ms-RKSJ-H")
font[10] = pdf.get_font("MS-Gothic,Italic", "90ms-RKSJ-H")
font[11] = pdf.get_font("MS-Gothic,BoldItalic", "90ms-RKSJ-H")
font[12] = pdf.get_font("MS-PGothic", "90msp-RKSJ-H")
font[13] = pdf.get_font("MS-PGothic,Bold", "90msp-RKSJ-H")
font[14] = pdf.get_font("MS-PGothic,Italic", "90msp-RKSJ-H")
font[15] = pdf.get_font("MS-PGothic,BoldItalic","90msp-RKSJ-H")

# set page mode to use outlines.
pdf.set_page_mode(HPDFDoc::HPDF_PAGE_MODE_USE_OUTLINE)

encoder = pdf.get_encoder("90ms-RKSJ-H")

# create outline root.
root = pdf.create_outline(nil, "日本語フォント", encoder);

i = 0
while font[i]
  print font[i].get_font_name, "\n"
  page = pdf.add_page
  
  outline = pdf.create_outline(root, font[i].get_font_name, nil)
  dst = page.create_destination
  outline.set_destination(dst)
  
  page.set_font_and_size(title_font, 10.0)
  
  page.begin_text
  page.move_text_pos(10.0, 190.0)
  page.show_text(font[i].get_font_name)
  
  page.set_font_and_size(font[i], 15.0)
  page.move_text_pos(10.0, -20.0)
  page.show_text("abcdefghijklmnopqrstuvwxyz")
  page.move_text_pos(0.0, -20.0)
  page.show_text("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
  page.move_text_pos(0.0, -20.0)
  page.show_text("1234567890")
  page.move_text_pos(0.0, -20.0)
  
  page.set_font_and_size(font[i], 10.0);
  page.show_text(SAMP_TEXT2)
  page.move_text_pos(0.0, -18.0)
  
  page.set_font_and_size(font[i], 16.0);
  page.show_text(SAMP_TEXT2)
  page.move_text_pos(0.0, -27.0)
  
  page.set_font_and_size(font[i], 23.0);
  page.show_text(SAMP_TEXT2)
  page.move_text_pos(0.0, -36.0)
  
  page.set_font_and_size(font[i], 30.0);
  page.show_text(SAMP_TEXT2)
  
  p = page.get_current_text_pos
  page.end_text
  
  page.set_width(p[0] + 20)
  page.set_height(210.0)
  
  page.set_line_width(0.5)
  
  page.move_to(10.0, 185.0)
  page.line_to(p[0] + 10.0, 185.0)
  page.stroke
  
  page.move_to(10.0, 125.0)
  page.line_to(p[0] + 10.0, 125.0)
  page.stroke
  
  page.move_to(10.0, p[1] - 12.0)
  page.line_to(p[0] + 10.0, p[1] - 12)
  page.stroke
      
  i = i + 1
end

pdf.save_to_file($0 + ".pdf")

