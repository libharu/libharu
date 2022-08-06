#
# << Haru Free PDF Library 2.0.0 >> -- demo.rb
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

if ARGV.empty?
  line = 'Ruby Rocks'
else
  line = ARGV.join(" ")
end

pdf = HPDFDoc.new

page = pdf.add_page

x = 578
r1 = 25

40.step(1, -3) do |xw|
  tone = 1.0 - (xw / 40.0) * 0.2

  page.set_line_width(xw.to_f)
  page.set_rgb_stroke(tone, 1.0, tone)
  page.circle(50.0, 750.0, r1.to_f)
  page.stroke
  r1 += xw
end

40.step(1, -3) do |xw|
  tone = 1.0 - (xw / 40.0) * 0.2

  page.set_line_width(xw.to_f)
  page.set_rgb_stroke(tone, tone, 1.0)
  page.move_to(x.to_f, 0.0)
  page.line_to(x.to_f, 842.0)
  page.stroke
  x = (x - xw - 2)
end

page.set_rgb_stroke(0.0, 0.0, 0.0)
page.set_line_width(1.0)
page.rectangle(20.0, 20.0, 558.0, 802.0)
page.stroke

font = pdf.get_font("Helvetica", nil)
bbox = font.get_bbox

y = 800
50.step(5, -5) do |size|
  height = (bbox[3] - bbox[1]) / 1000 * size
  y = y - height

  page.begin_text
  page.set_font_and_size(font, size.to_f)
  page.text_out(30.0, y.to_f, line)
  page.end_text
end

(0...360).step(20) do |angle|
  page.set_rgb_fill(rand, rand, rand)

  page.begin_text
  rad = angle / 180.0 * 3.141592
  page.set_font_and_size(font, 20.0)
  page.set_text_matrix(Math.cos(rad),
                        Math.sin(rad),
                        -Math.sin(rad), 
                        Math.cos(rad),
                        300 + Math.cos(rad) * 40,
                        300 + Math.sin(rad) * 40)
  page.show_text(line)
  page.end_text
end

pdf.save_to_file("demo.pdf")

