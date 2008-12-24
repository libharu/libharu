#
# << Haru Free PDF Library 2.0.6 >> -- ext_gstate_demo.rb
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

def draw_circles(page, description, x, y)
  page.set_line_width(1)
  page.set_rgb_stroke(0, 0, 0)

  page.set_rgb_fill(1, 0, 0)
  page.circle(x + 40, y + 40, 40)
  page.close_path_fill_stroke()

  page.set_rgb_fill(0, 1, 0)
  page.circle(x + 100, y + 40, 40)
  page.close_path_fill_stroke()

  page.set_rgb_fill(0, 0, 1)
  page.circle(x + 70, y + 74.64, 40)
  page.close_path_fill_stroke()

  page.set_rgb_fill(0, 0, 0)
  page.begin_text()
  page.text_out(x + 0.0, y + 130.0, description)
  page.end_text()
end

pdf = HPDFDoc.new

PAGE_WIDTH = 600
PAGE_HEIGHT = 900

# add a new page object. #
page = pdf.add_page
page.set_height(PAGE_HEIGHT)
page.set_width(PAGE_WIDTH)

font = pdf.get_font("Helvetica-Bold", nil)

page.set_font_and_size(font, 10)

# normal
page.gsave()
draw_circles(page, "normal", 40, PAGE_HEIGHT - 170)
page.grestore()

# transparency (0.8)
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_alpha_fill(0.8)
gstate.set_alpha_stroke(0.8)
page.set_ext_gstate(gstate)
draw_circles(page, "alpha fill = 0.8", 230, PAGE_HEIGHT - 170)
page.grestore()

# transparency (0.4)
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_alpha_fill(0.4)
gstate.set_alpha_stroke(0.4)
page.set_ext_gstate(gstate)
draw_circles(page, "alpha fill = 0.4", 420, PAGE_HEIGHT - 170)
page.grestore()

# blend-mode=HPDF_BM_MULTIPLY
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_MULTIPLY)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_MULTIPLY", 40, PAGE_HEIGHT - 340)
page.grestore()

# blend-mode=HPDF_BM_SCREEN
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_SCREEN)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_SCREEN", 230, PAGE_HEIGHT - 340)
page.grestore()

# blend-mode=HPDF_BM_OVERLAY
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_OVERLAY)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_OVERLAY", 420, PAGE_HEIGHT - 340)
page.grestore()

# blend-mode=HPDF_BM_DARKEN
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_DARKEN)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_DARKEN", 40, PAGE_HEIGHT - 510)
page.grestore()

# blend-mode=HPDF_BM_LIGHTEN
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_LIGHTEN)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_LIGHTEN", 230, PAGE_HEIGHT - 510)
page.grestore()

# blend-mode=HPDF_BM_COLOR_DODGE
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_COLOR_DODGE)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_COLOR_DODGE", 420, PAGE_HEIGHT - 510)
page.grestore()

# blend-mode=HPDF_BM_COLOR_BUM
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_COLOR_BUM)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_COLOR_BUM", 40, PAGE_HEIGHT - 680)
page.grestore()

# blend-mode=HPDF_BM_HARD_LIGHT
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_HARD_LIGHT)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_HARD_LIGHT", 230, PAGE_HEIGHT - 680)
page.grestore()

# blend-mode=HPDF_BM_SOFT_LIGHT
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_SOFT_LIGHT)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_SOFT_LIGHT", 420, PAGE_HEIGHT - 680)
page.grestore()

# blend-mode=HPDF_BM_DIFFERENCE
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_DIFFERENCE)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_DIFFERENCE", 40, PAGE_HEIGHT - 850)
page.grestore()

# blend-mode=HPDF_BM_EXCLUSHON
page.gsave()
gstate = pdf.create_ext_gstate()
gstate.set_blend_mode(HPDFDoc::HPDF_BM_EXCLUSHON)
page.set_ext_gstate(gstate)
draw_circles(page, "HPDF_BM_EXCLUSHON", 230, PAGE_HEIGHT - 850)
page.grestore()

pdf.save_to_file($0 + ".pdf")

