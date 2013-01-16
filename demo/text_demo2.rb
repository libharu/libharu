#
# << Haru Free PDF Library 2.0.0 >> -- text_demo2.rb
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

samp_text = "The quick brown fox jumps over the lazy dog. "

pdf = HPDFDoc.new

page = pdf.add_page
page.set_size(HPDFDoc::HPDF_PAGE_SIZE_A5, HPDFDoc::HPDF_PAGE_PORTRAIT)
height = page.get_height

font = pdf.get_font("Helvetica", nil)
page.set_text_leading(20)

# HPDF_TALIGN_LEFT
left = 25
top = 545
right = 200
bottom = top - 40

page.rectangle(left, bottom, right - left, top - bottom)
page.stroke

page.begin_text
page.set_font_and_size(font, 10)
page.text_out(left, top + 3, "HPDF_TALIGN_LEFT")

page.set_font_and_size(font, 13)
page.text_rect(left, top, right, bottom, samp_text, HPDFDoc::HPDF_TALIGN_LEFT)
page.end_text

# HPDF_TALIGN_RIGHT
left = 220
right = 395

page.rectangle(left, bottom, right - left, top - bottom)
page.stroke

page.begin_text
page.set_font_and_size(font, 10)
page.text_out(left, top + 3, "HPDF_TALIGN_RIGHT")

page.set_font_and_size(font, 13)
page.text_rect(left, top, right, bottom, samp_text, HPDFDoc::HPDF_TALIGN_RIGHT)
page.end_text

# HPDF_TALIGN_CENTER
left = 25
top = 475
right = 200
bottom = top - 40

page.rectangle(left, bottom, right - left, top - bottom)
page.stroke

page.begin_text
page.set_font_and_size(font, 10)
page.text_out(left, top + 3, "HPDF_TALIGN_CENTER")

page.set_font_and_size(font, 13)
page.text_rect(left, top, right, bottom, samp_text, HPDFDoc::HPDF_TALIGN_CENTER)
page.end_text

# HPDF_TALIGN_JUSTIFY
left = 220
right = 395

page.rectangle(left, bottom, right - left, top - bottom)
page.stroke

page.begin_text
page.set_font_and_size(font, 10)
page.text_out(left, top + 3, "HPDF_TALIGN_JUSTIFY")

page.set_font_and_size(font, 13)
page.text_rect(left, top, right, bottom, samp_text, HPDFDoc::HPDF_TALIGN_JUSTIFY)
page.end_text


# Skewed coordinate system

angle1 = 5.0
angle2 = 10.0
rad1 = angle1 / 180 * 3.141592
rad2 = angle2 / 180 * 3.141592

page.gsave

page.concat(1, Math.tan(rad1), Math.tan(rad2), 1, 25, 350)
    left = 0
    top = 40
    right = 175
    bottom = 0

page.rectangle(left, bottom, right - left,
                top - bottom)
page.stroke

page.begin_text

page.set_font_and_size(font, 10)
page.text_out(left, top + 3, "Skewed coordinate system")

page.set_font_and_size(font, 13)
page.text_rect(left, top, right, bottom, samp_text, HPDFDoc::HPDF_TALIGN_LEFT)

page.end_text

page.grestore


# Rotated coordinate system
page.gsave

angle1 = 5.0
rad1 = angle1 / 180 * 3.141592

page.concat(Math.cos(rad1), Math.sin(rad1), -Math.sin(rad1), Math.cos(rad1), 220, 350)
left = 0
top = 40
right = 175
bottom = 0

page.rectangle(left, bottom, right - left,
                top - bottom)
page.stroke

page.begin_text

page.set_font_and_size(font, 10)
page.text_out(left, top + 3, "Rotated coordinate system")

page.set_font_and_size(font, 13)
page.text_rect(left, top, right, bottom, samp_text, HPDFDoc::HPDF_TALIGN_LEFT)

page.end_text

page.grestore


# text along a circle
page.set_gray_stroke(0)
page.circle(210, 190, 145)
page.circle(210, 190, 113)
page.stroke

angle1 = 360.0 / samp_text.length
angle2 = 180.0

page.begin_text
font = pdf.get_font("Courier-Bold", nil)
page.set_font_and_size(font, 30)

i = 0
while i < samp_text.length
  rad1 = (angle2 - 90) / 180 * 3.141592
  rad2 = angle2 / 180 * 3.141592

  x = 210.0 + Math.cos(rad2) * 122
  y = 190.0 + Math.sin(rad2) * 122

  page.set_text_matrix(Math.cos(rad1), Math.sin(rad1), -Math.sin(rad1), Math.cos(rad1), x, y)

  page.show_text(samp_text[i, 1])
  angle2 -= angle1
  i = i + 1
end

page.end_text


pdf.save_to_file($0 + ".pdf")


