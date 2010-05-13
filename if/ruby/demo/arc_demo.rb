#
# << Haru Free PDF Library 2.0.2 >> -- arc_demo.rb
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

pdf = HPDFDoc.new

# add a new page object. #
page = pdf.add_page

page.set_height(220)
page.set_width(200)

# draw pie chart
#
#   A: 45% Red
#   B: 25% Blue
#   C: 15% green
#   D: other yellow
#

# A #
page.set_rgb_fill(1.0, 0, 0)
page.move_to(100, 100)
page.line_to(100, 180)
page.arc(100, 100, 80, 0, 360 * 0.45)
pos = page.get_current_pos
page.line_to(100, 100)
page.fill

# B #
page.set_rgb_fill(0, 0, 1.0)
page.move_to(100, 100)
page.line_to(pos[0], pos[1])
page.arc(100, 100, 80, 360 * 0.45, 360 * 0.7)
pos = page.get_current_pos
page.line_to(100, 100)
page.fill

# C #
page.set_rgb_fill(0, 1.0, 0)
page.move_to(100, 100)
page.line_to(pos[0], pos[1])
page.arc(100, 100, 80, 360 * 0.7, 360 * 0.85)
pos = page.get_current_pos
page.line_to(100, 100)
page.fill

# D #
page.set_rgb_fill(1.0, 1.0, 0)
page.move_to(100, 100)
page.line_to(pos[0], pos[1])
page.arc(100, 100, 80, 360 * 0.85, 360)
pos = page.get_current_pos
page.line_to(100, 100)
page.fill

# draw center circle #
page.set_gray_stroke(0)
page.set_gray_fill(1)
page.circle(100, 100, 30)
page.fill

pdf.save_to_file($0 + ".pdf")

