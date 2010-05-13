#
# << Haru Free PDF Library 2.0.2 >> -- line_demo.rb
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

def draw_line(page, x, y, text)
  page.begin_text
  page.move_text_pos(x, y - 10)
  page.show_text(text)
  page.end_text

  page.move_to(x, y - 15)
  page.line_to(x + 220, y - 15)
  page.stroke
end

def draw_line2(page, x, y, text)
  page.begin_text
  page.move_text_pos(x, y)
  page.show_text(text)
  page.end_text

  page.move_to(x + 30, y - 25)
  page.line_to(x + 160, y - 25)
  page.stroke
end

def draw_rect(page, x, y, text)
  page.begin_text
  page.move_text_pos(x, y - 10)
  page.show_text(text)
  page.end_text

  page.rectangle(x, y - 40, 220, 25)
end

pdf = HPDFDoc.new

pdf.set_compression_mode(HPDFDoc::HPDF_COMP_ALL)

font = pdf.get_font("Helvetica", nil)

page = pdf.add_page

#print the lines of the page.#
page.set_line_width(1)
x = page.get_width - 100
y = page.get_height - 110
page.rectangle(50, 50, x, y)
page.stroke

#print the title of the page (with positioning center).#
page.set_font_and_size(font, 24)
tw = page.text_width('Line Demo')
page.begin_text

x =(page.get_width - tw) / 2
y = page.get_height - 50
page.move_text_pos(x, y)

page.show_text('Line Demo')
page.end_text

page.set_font_and_size(font, 10)

#Draw verious widths of lines.#
page.set_line_width(0)
draw_line(page, 60, 770, 'line width = 0')

page.set_line_width(1.0)
draw_line(page, 60, 740, 'line width = 1.0')

page.set_line_width(2.0)
draw_line(page, 60, 710, 'line width = 2.0')

#Line dash pattern#
page.set_line_width(1.0)

page.set_dash([3], 1)
draw_line(page, 60, 680, 'dash_ptn=[3], phase=1 -- 2 on, 3 off, 3 on...')

page.set_dash([7, 3], 2)
draw_line(page, 60, 650, 'dash_ptn=[7, 3], phase=2 -- 5 on 3 off, 7 on,...')

page.set_dash([8, 7, 2, 7], 0)
draw_line(page, 60, 620, 'dash_ptn=[8, 7, 2, 7], phase=0')

page.set_dash([], 0)

page.set_line_width(30)
page.set_rgb_stroke(0.0, 0.5, 0.0)

#Line Cap Style#
page.set_line_cap(HPDFDoc::HPDF_BUTT_END)
draw_line2(page, 60, 570, 'HPDF_BUTT_END')

page.set_line_cap(HPDFDoc::HPDF_ROUND_END)
draw_line2(page, 60, 505, 'HPDF_ROUND_END')

page.set_line_cap(HPDFDoc::HPDF_PROJECTING_SCUARE_END)
draw_line2(page, 60, 440, 'HPDF_PROJECTING_SCUARE_END')

#Line Join Style#
page.set_line_width(30)
page.set_rgb_stroke(0.0, 0.0, 0.5)

page.set_line_join(HPDFDoc::HPDF_MITER_JOIN)
page.move_to(120, 300)
page.line_to(160, 340)
page.line_to(200, 300)
page.stroke

page.begin_text
page.move_text_pos(60, 360)
page.show_text('HPDF_MITER_JOIN')
page.end_text

page.set_line_join(HPDFDoc::HPDF_ROUND_JOIN)
page.move_to(120, 195)
page.line_to(160, 235)
page.line_to(200, 195)
page.stroke

page.begin_text
page.move_text_pos(60, 255)
page.show_text('HPDF_ROUND_JOIN')
page.end_text

page.set_line_join(HPDFDoc::HPDF_BEVEL_JOIN)
page.move_to(120, 90)
page.line_to(160, 130)
page.line_to(200, 90)
page.stroke

page.begin_text
page.move_text_pos(60, 150)
page.show_text('HPDF_BEVEL_JOIN')
page.end_text

# Draw rectangle #
page.set_line_width(2)
page.set_rgb_stroke(0, 0, 0)
page.set_rgb_fill(0.75, 0.0, 0.0)

draw_rect(page, 300, 770, 'stroke')
page.stroke

draw_rect(page, 300, 720, 'Fill')
page.fill

draw_rect(page, 300, 670, 'Fill then stroke')
page.fill_stroke

#clip Rect#
page.gsave  # Save the current graphic state#
draw_rect(page, 300, 620, 'Clip rectangle')
page.clip
page.stroke
page.set_font_and_size(font, 13)

page.begin_text
page.move_text_pos(290, 600)
page.set_text_leading(12)
page.show_text('Clip Clip Clip Clip Clip Clipi Clip Clip Clip')
page.show_text_next_line('Clip Clip Clip Clip Clip Clip Clip Clip Clip')
page.show_text_next_line('Clip Clip Clip Clip Clip Clip Clip Clip Clip')
page.end_text
page.grestore

x0 = 330
y0 = 440
x1 = 430
y1 = 530
x2 = 480
y2 = 470
x3 = 480
y3 = 90

#Curve Example(curve_to2)#
page.set_rgb_fill(0, 0, 0)

page.begin_text
page.move_text_pos(300, 540)
page.show_text('curve_to2(x1, y1, x2. y2)')
page.end_text

page.begin_text
page.move_text_pos(x0 + 5, y0 - 5)
page.show_text('Current point')
page.move_text_pos(x1 - x0, y1 - y0)
page.show_text('(x1, y1)')
page.move_text_pos(x2 - x1, y2 - y1)
page.show_text('(x2, y2)')
page.end_text

page.set_dash([], 0)

page.set_line_width(0.5)
page.move_to(x1, y1)
page.line_to(x2, y2)
page.stroke

page.set_dash([], 0)

page.set_line_width(1.5)

page.move_to(x0, y0)
page.curve_to2(x1, y1, x2, y2)
page.stroke

#Curve Example(curve_to3)#
y0 = y0 - 150
y1 = y1 - 150
y2 = y2 - 150

page.begin_text
page.move_text_pos(300, 390)
page.show_text('curve_to3(x1, y1, x2. y2)')
page.end_text

page.begin_text
page.move_text_pos(x0 + 5, y0 - 5)
page.show_text('Current point')
page.move_text_pos(x1 - x0, y1 - y0)
page.show_text('(x1, y1)')
page.move_text_pos(x2 - x1, y2 - y1)
page.show_text('(x2, y2)')
page.end_text

page.set_dash([3], 1)

page.set_line_width(0.5)
page.move_to(x0, y0)
page.line_to(x1, y1)
page.stroke

page.set_dash([], 0)

page.set_line_width(1.5)
page.move_to(x0, y0)
page.curve_to3(x1, y1, x2, y2)
page.stroke

# Curve Example(curve_to)
y0 = y0 - 150
y1 = y1 - 160
y2 = y2 - 130
x2 = x2 + 10

page.begin_text
page.move_text_pos(300, 240)
page.show_text('curve_to(x1, y1, x2. y2, x3, y3)')
page.end_text

page.begin_text
page.move_text_pos(x0 + 5, y0 - 5)
page.show_text('Current point')
page.move_text_pos(x1 - x0, y1 - y0)
page.show_text('(x1, y1)')
page.move_text_pos(x2 - x1, y2 - y1)
page.show_text('(x2, y2)')
page.move_text_pos(x3 - x2, y3 - y2)
page.show_text('(x3, y3)')
page.end_text

page.set_dash([3], 1)

page.set_line_width(0.5)
page.move_to(x0, y0)
page.line_to(x1, y1)
page.stroke
page.move_to(x2, y2)
page.line_to(x3, y3)
page.stroke

page.set_dash([], 0)

page.set_line_width(1.5)
page.move_to(x0, y0)
page.curve_to(x1, y1, x2, y2, x3, y3)
page.stroke

pdf.save_to_file($0 + ".pdf")

