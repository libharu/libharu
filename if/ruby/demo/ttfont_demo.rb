#
# << Haru Free PDF Library 2.0.2 >> -- ttfont_demo.rb
#
# http://libharu.org/
#
# Copyright (c) 1999-2006 Takeshi Kanno
#
# Permission to use, copy, modify, distribute and sell this software
# and its documentation for any purpose is hereby granted without fee,
# provided that the above copyright notice appear in all copies and
# that both that copyright notice and this permission notice appear
# in supporting documentation.
# It is provided "as is" without express or implied warranty.
#

require "hpdf"

SAMP_TXT = "The quick brown fox jumps over the lazy dog."

font_name = ARGV.shift
flg = ARGV.shift

if !font_name
   print 'usage: ttfont_demo.rb [path to font file] -E(embedding font).'
   exit(1)
end

pdf = HPDFDoc.new

pdf.set_compression_mode(HPDFDoc::HPDF_COMP_ALL)

# Add a new page object. #
page = pdf.add_page

title_font = pdf.get_font("Helvetica", nil)

if (flg == "-E")
  embed = HPDFDoc::HPDF_TRUE
else
  embed = HPDFDoc::HPDF_FALSE
end

detail_font_name = pdf.load_ttfont_from_file(font_name, embed)
print font_name, ' load OK.[', detail_font_name, ']'

detail_font = pdf.get_font(detail_font_name, nil)

page.set_font_and_size(title_font, 10)

page.begin_text

# Move the position of the text to top of the page. #
page.move_text_pos(10, 190)
page.show_text(detail_font_name)

if (embed)
  page.show_text("(Embedded Subset)")
end

page.set_font_and_size(detail_font, 15)
page.move_text_pos(10, -20)
page.show_text("abcdefghijklmnopqrstuvwxyz")
page.move_text_pos(0, -20)
page.show_text("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
page.move_text_pos(0, -20)
page.show_text("1234567890")
page.move_text_pos(0, -20)

page.set_font_and_size(detail_font, 10)
page.show_text(SAMP_TXT)
page.move_text_pos(0, -18)

page.set_font_and_size(detail_font, 16)
page.show_text(SAMP_TXT)
page.move_text_pos(0, -27)

page.set_font_and_size(detail_font, 23)
page.show_text(SAMP_TXT)
page.move_text_pos(0, -36)

page.set_font_and_size(detail_font, 30)
page.show_text(SAMP_TXT)
page.move_text_pos(0, -36)

tw = page.text_width(SAMP_TXT)
page_height = 210
page_width = tw + 40

page.set_width(page_width)
page.set_height(page_height)

# Finish to print text. #
page.end_text

page.set_line_width(0.5)

page.move_to(10, page_height - 25)
page.line_to(page_width - 10, page_height - 25)
page.stroke

page.move_to(10, page_height - 85)
page.line_to(page_width - 10, page_height - 85)
page.stroke

pdf.save_to_file($0 + ".pdf")

