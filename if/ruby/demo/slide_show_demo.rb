#
# << Haru Free PDF Library 2.0.6 >> -- slideshow_demo.rb
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

RAND_MAX = 255

def print_page(page, caption, font, style, prev, next_p)

  r = rand
  g = rand
  b = rand

  page.set_width(800)
  page.set_height(600)

  page.set_rgb_fill(r, g, b)
  page.rectangle(0, 0, 800, 600)
  page.fill()

  page.set_rgb_fill(1 - r, 1 - b, 1 - b)
  page.set_font_and_size(font, 30)

  page.begin_text()
  page.set_text_matrix(0.8, 0.0, 0.0, 1.0, 0.0, 0.0);   
  page.text_out(50, 530, caption)

  page.set_text_matrix(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);   
  page.set_font_and_size(font, 20)
  page.text_out(55, 300, "Type \"Ctrl+L\" in order to return from full screen mode.")
  page.end_text()

  page.set_slide_show(style, 5, 1)
  page.set_font_and_size(font, 20)

  if (next_p != nil) 
    page.begin_text()
    page.text_out(680, 50, "Next=>")
    page.end_text()

    dst = next_p.create_destination()
    dst.set_fit()
    annot = page.create_link_annot(680, 50, 680, 70, dst)
    annot.set_border_style(0, 0, 0)
    annot.set_highlight_mode(HPDFDoc::HPDF_ANNOT_INVERT_BOX)
  end

  if (prev != nil) 
    page.begin_text()
    page.text_out(50, 50, "<=Prev")
    page.end_text()

    dst = prev.create_destination()
    dst.set_fit()
    annot = page.create_link_annot(50, 50, 110, 70, dst)
    annot.set_border_style(0, 0, 0)
    annot.set_highlight_mode(HPDFDoc::HPDF_ANNOT_INVERT_BOX)
  end

end


pdf = HPDFDoc.new

font = pdf.get_font("Courier", nil)
page_0 = pdf.add_page()
page_1 = pdf.add_page()
page_2 = pdf.add_page()
page_3 = pdf.add_page()
page_4 = pdf.add_page()
page_5 = pdf.add_page()
page_6 = pdf.add_page()
page_7 = pdf.add_page()
page_8 = pdf.add_page()
page_9 = pdf.add_page()
page_10 = pdf.add_page()
page_11 = pdf.add_page()
page_12 = pdf.add_page()
page_13 = pdf.add_page()
page_14 = pdf.add_page()
page_15 = pdf.add_page()
page_16 = pdf.add_page()

print_page(page_0, "HPDFDoc::HPDF_TS_WIPE_RIGHT", font, 
    HPDFDoc::HPDF_TS_WIPE_RIGHT, nil, page_1);
print_page(page_1, "HPDFDoc::HPDF_TS_WIPE_UP", font, 
    HPDFDoc::HPDF_TS_WIPE_UP, page_0, page_2);
print_page(page_2, "HPDFDoc::HPDF_TS_WIPE_LEFT", font, 
    HPDFDoc::HPDF_TS_WIPE_LEFT, page_1, page_3);
print_page(page_3, "HPDFDoc::HPDF_TS_WIPE_DOWN", font, 
    HPDFDoc::HPDF_TS_WIPE_DOWN, page_2, page_4);
print_page(page_4, "HPDFDoc::HPDF_TS_BARN_DOORS_HORIZONTAL_OUT", font, 
    HPDFDoc::HPDF_TS_BARN_DOORS_HORIZONTAL_OUT, page_3, page_5);
print_page(page_5, "HPDFDoc::HPDF_TS_BARN_DOORS_HORIZONTAL_IN", font, 
    HPDFDoc::HPDF_TS_BARN_DOORS_HORIZONTAL_IN, page_4, page_6);
print_page(page_6, "HPDFDoc::HPDF_TS_BARN_DOORS_VERTICAL_OUT", font, 
    HPDFDoc::HPDF_TS_BARN_DOORS_VERTICAL_OUT, page_5, page_7);
print_page(page_7, "HPDFDoc::HPDF_TS_BARN_DOORS_VERTICAL_IN", font, 
    HPDFDoc::HPDF_TS_BARN_DOORS_VERTICAL_IN, page_6, page_8);
print_page(page_8, "HPDFDoc::HPDF_TS_BOX_OUT", font, 
    HPDFDoc::HPDF_TS_BOX_OUT, page_7, page_9);
print_page(page_9, "HPDFDoc::HPDF_TS_BOX_IN", font, 
    HPDFDoc::HPDF_TS_BOX_IN, page_8, page_10);
print_page(page_10, "HPDFDoc::HPDF_TS_BLINDS_HORIZONTAL", font, 
    HPDFDoc::HPDF_TS_BLINDS_HORIZONTAL, page_9, page_11);
print_page(page_11, "HPDFDoc::HPDF_TS_BLINDS_VERTICAL", font, 
    HPDFDoc::HPDF_TS_BLINDS_VERTICAL, page_10, page_12);
print_page(page_12, "HPDFDoc::HPDF_TS_DISSOLVE", font, 
    HPDFDoc::HPDF_TS_DISSOLVE, page_11, page_13);
print_page(page_13, "HPDFDoc::HPDF_TS_GLITTER_RIGHT", font, 
    HPDFDoc::HPDF_TS_GLITTER_RIGHT, page_12, page_14);
print_page(page_14, "HPDFDoc::HPDF_TS_GLITTER_DOWN", font, 
    HPDFDoc::HPDF_TS_GLITTER_DOWN, page_13, page_15);
print_page(page_15, "HPDFDoc::HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT", font, 
    HPDFDoc::HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT, page_14, page_16);
print_page(page_16, "HPDFDoc::HPDF_TS_REPLACE", font, 
    HPDFDoc::HPDF_TS_REPLACE, page_15, nil);

pdf.set_page_mode(HPDFDoc::HPDF_PAGE_MODE_FULL_SCREEN)

pdf.save_to_file($0 + ".pdf")

