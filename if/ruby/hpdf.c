/*
 * << Haru Free PDF Library 2.0.5 >> -- hpdf.c
 *
 * URL http://libharu.org/
 *
 * Copyright (c) 1999-2006 Takeshi Kanno
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 * 2006.08.03 update.
 */

#include "ruby.h"
#include "ruby/io.h"

#include "hpdf.h"
#include "hpdf_conf.h"
#include "hpdf_utils.h"
#include "hpdf_pages.h"

#include <stdlib.h>
#include <stdio.h>

static VALUE rb_cHPDFDoc;
static VALUE rb_cHPDFPage;
static VALUE rb_cHPDFImage;
static VALUE rb_cHPDFFont;
static VALUE rb_cHPDFOutline;
static VALUE rb_cHPDFEncoder;
static VALUE rb_cHPDFDestination;
static VALUE rb_cHPDFAnnotation;
static VALUE rb_cHPDFExtGState;
static VALUE rb_eHPDFError;

static void
hpdf_free (HPDF_Doc pdf);


static void
hpdf_error_handler  (HPDF_STATUS  error_no,
                     HPDF_STATUS  detail_no,
                     void         *user_data)
{
    char msg[256];

    snprintf(msg, 256, "ERROR 0x%04lX-0x%04lX", error_no, detail_no);

    rb_raise(rb_eHPDFError, "%s", msg);
}


static VALUE
hpdf_new ()
{
    HPDF_Doc pdf = HPDF_New(hpdf_error_handler, NULL);

    HPDF_PTRACE(("hpdf_new pdf=%p\n", pdf));

    if (!pdf)
        rb_raise(rb_eHPDFError, "cannot create HPDF_Doc object.");

    return Data_Wrap_Struct (rb_cHPDFDoc, 0, hpdf_free, pdf);
}

static void
hpdf_free (HPDF_Doc pdf)
{
    HPDF_PTRACE(("hpdf_free pdf=%p\n", pdf));

    HPDF_Free (pdf);
}

static VALUE
hpdf_new_doc (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_new_doc pdf=%p\n", pdf));

    ret = HPDF_NewDoc(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_free_doc (VALUE obj)
{
    HPDF_Doc pdf;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_free_doc pdf=%p\n", pdf));

    HPDF_FreeDoc(pdf);

    return Qnil;
}

static VALUE
hpdf_has_doc (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_has_doc pdf=%p\n", pdf));

    ret = HPDF_HasDoc(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_free_doc_all (VALUE obj)
{
    HPDF_Doc pdf;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_free_doc_all pdf=%p\n", pdf));

    HPDF_FreeDocAll(pdf);

    return Qnil;
}

static VALUE
hpdf_save_to_file (VALUE obj, VALUE file_name)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Check_Type(file_name, T_STRING);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_save_to_file pdf=%p\n", pdf));

    ret = HPDF_SaveToFile(pdf, StringValuePtr(file_name));

    return INT2NUM(ret);
}

static VALUE
hpdf_get_error (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_error pdf=%p\n", pdf));

    ret = HPDF_GetError(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_reset_error (VALUE obj)
{
    HPDF_Doc pdf;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_reset_error pdf=%p\n", pdf));

    HPDF_ResetError(pdf);

    return Qnil;
}

static VALUE
hpdf_set_page_configuration (VALUE obj, VALUE page_per_pages)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;
    HPDF_UINT i;

    i = NUM2INT(page_per_pages);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_set_page_configuration pdf=%p\n", pdf));

    ret = HPDF_SetPagesConfiguration(pdf, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_get_page_by_index (VALUE obj, VALUE index)
{
    HPDF_Page page;
    HPDF_Doc pdf;
    HPDF_UINT i;

    i = NUM2INT(index);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_page_by_index pdf=%p\n", pdf));

    page = HPDF_GetPageByIndex(pdf, i);

    return Data_Wrap_Struct (rb_cHPDFPage, 0, 0, page);
}

static VALUE
hpdf_get_page_layout (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_UINT layout;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_page_layout pdf=%p\n", pdf));

    layout = HPDF_GetPageLayout(pdf);

    return INT2NUM(layout);
}

static VALUE
hpdf_set_page_layout (VALUE obj, VALUE layout)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;
    HPDF_UINT i;

    i = NUM2INT(layout);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_set_page_layout pdf=%p\n", pdf));

    ret = HPDF_SetPageLayout(pdf, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_get_page_mode (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_UINT mode;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_page_mode pdf=%p\n", pdf));

    mode = HPDF_GetPageMode(pdf);

    return INT2NUM(mode);
}

static VALUE
hpdf_set_page_mode (VALUE obj, VALUE mode)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;
    HPDF_UINT i;

    i = NUM2INT(mode);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_set_page_mode pdf=%p\n", pdf));

    ret = HPDF_SetPageMode(pdf, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_set_open_action (VALUE obj, VALUE action)
{
    HPDF_Doc pdf;
    HPDF_Destination dst;
    HPDF_STATUS ret;

    if (HPDF_StrCmp(rb_obj_classname(action), "HPDFDestination") != 0)
        rb_raise(rb_eHPDFError, "invalid argument(1).");

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);
    Data_Get_Struct(action, HPDF_Array_Rec, dst);

    HPDF_PTRACE(("hpdf_set_open_action pdf=%p\n", pdf));

    ret = HPDF_SetOpenAction(pdf, dst);

    return INT2NUM(ret);
}

static VALUE
hpdf_get_viewer_preference (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_UINT mode;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_viewer_preference pdf=%p\n", pdf));

    mode = HPDF_GetViewerPreference(pdf);

    return INT2NUM(mode);
}

static VALUE
hpdf_set_viewer_preference (VALUE obj, VALUE value)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;
    HPDF_UINT i;

    i = NUM2INT(value);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_set_viewer_preference pdf=%p\n", pdf));

    ret = HPDF_SetViewerPreference(pdf, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_get_current_page (VALUE obj)
{
    HPDF_Page page;
    HPDF_Doc pdf;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_current_page pdf=%p\n", pdf));

    page = HPDF_GetCurrentPage(pdf);

    return Data_Wrap_Struct (rb_cHPDFPage, 0, 0, page);
}

static VALUE
hpdf_add_page (VALUE obj)
{
    HPDF_Page page;
    HPDF_Doc pdf;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_add_page pdf=%p\n", pdf));

    page = HPDF_AddPage(pdf);

    return Data_Wrap_Struct (rb_cHPDFPage, 0, 0, page);
}

static VALUE
hpdf_insert_page (VALUE obj, VALUE page)
{
    HPDF_Page target;
    HPDF_Page new_page;
    HPDF_Doc pdf;

    if (HPDF_StrCmp(rb_obj_classname(page), "HPDFPage") != 0)
        rb_raise(rb_eHPDFError, "invalid argument(1).");

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);
    Data_Get_Struct(page, HPDF_Dict_Rec, target);

    HPDF_PTRACE(("hpdf_insert_page pdf=%p\n", pdf));

    new_page = HPDF_InsertPage(pdf, target);

    return Data_Wrap_Struct (rb_cHPDFPage, 0, 0, new_page);
}

static VALUE
hpdf_page_set_width (VALUE obj, VALUE width)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(width);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_width page=%p\n", page));

    ret = HPDF_Page_SetWidth(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_height (VALUE obj, VALUE height)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(height);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_height page=%p\n", page));

    ret = HPDF_Page_SetHeight(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_size (VALUE obj, VALUE size, VALUE direction)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_INT i1;
    HPDF_INT i2;

    i1 = NUM2INT(size);
    i2 = NUM2INT(direction);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_size page=%p\n", page));

    ret = HPDF_Page_SetSize(page, i1, i2);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_rotate (VALUE obj, VALUE angle)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_INT i;

    i = NUM2INT(angle);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_rotate page=%p\n", page));

    ret = HPDF_Page_SetRotate(page, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_get_font (VALUE obj, VALUE font_name, VALUE encoding_name)
{
    HPDF_Font font;
    HPDF_Doc pdf;
    const char *s1;
    const char *s2;

    s1 = StringValuePtr(font_name);

    if (encoding_name == Qnil)
        s2 = NULL;
    else {
        s2 = StringValuePtr(encoding_name);

        if (HPDF_StrLen(s2, -1) == 0)
            s2 = NULL;
    }

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_font pdf=%p\n", pdf));

    font = HPDF_GetFont(pdf, s1, s2);

    return Data_Wrap_Struct (rb_cHPDFFont, 0, 0, font);
}

static VALUE
hpdf_load_type1font_from_file (VALUE obj, VALUE afm, VALUE pfa)
{
    const char* font_name;
    HPDF_Doc pdf;
    const char *s1;
    const char *s2;

    s1 = StringValuePtr(afm);
    s2 = StringValuePtr(pfa);

    if (HPDF_StrLen(s2, -1) == 0)
        s2 = NULL;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_load_type1font_from_file pdf=%p\n", pdf));

    font_name = HPDF_LoadType1FontFromFile(pdf, s1, s2);

    return rb_str_new2(font_name);
}

static VALUE
hpdf_load_ttfont_from_file (VALUE obj, VALUE file_name, VALUE embedding)
{
    const char* font_name;
    HPDF_Doc pdf;
    const char *s;
    HPDF_INT i;

    s = StringValuePtr(file_name);
    i = NUM2INT(embedding);

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_load_ttfont_from_file pdf=%p\n", pdf));

    font_name = HPDF_LoadTTFontFromFile(pdf, s, i);

    return rb_str_new2(font_name);
}

static VALUE
hpdf_load_ttfont_from_file2 (VALUE obj, VALUE file_name, VALUE index, VALUE embedding)
{
    const char* font_name;
    HPDF_Doc pdf;
    const char *s;
    HPDF_INT i1;
    HPDF_INT i2;

    s = StringValuePtr(file_name);
    i1 = NUM2INT(index);
    i2 = NUM2INT(embedding);

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_load_ttfont_from_file2 pdf=%p\n", pdf));

    font_name = HPDF_LoadTTFontFromFile2(pdf, s, i1, i2);

    return rb_str_new2(font_name);
}

static VALUE
hpdf_add_page_label (VALUE obj, VALUE page_num, VALUE style, VALUE first_page, VALUE prefix)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;
    HPDF_INT i1;
    HPDF_INT i2;
    HPDF_INT i3;
    const char *s;

    i1 = NUM2INT(page_num);
    i2 = NUM2INT(style);
    i3 = NUM2INT(first_page);
    s = StringValuePtr(prefix);

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_add_page_label pdf=%p\n", pdf));

    ret = HPDF_AddPageLabel(pdf, i1, i2, i3, s);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_jp_fonts (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_jp_fonts pdf=%p\n", pdf));

    ret = HPDF_UseJPFonts(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_kr_fonts (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_kr_fonts pdf=%p\n", pdf));

    ret = HPDF_UseKRFonts(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_cns_fonts (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_cns_fonts pdf=%p\n", pdf));

    ret = HPDF_UseCNSFonts(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_cnt_fonts (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_cnt_fonts pdf=%p\n", pdf));

    ret = HPDF_UseCNSFonts(pdf);

    return INT2NUM(ret);
}


static VALUE
hpdf_create_outline (VALUE obj, VALUE parent, VALUE title, VALUE encoder)
{
    HPDF_Doc pdf;
    HPDF_Outline outline1 = NULL;
    HPDF_Outline outline2;
    HPDF_Encoder e = NULL;
    const char *s;

    if (HPDF_StrCmp(rb_obj_classname(parent), "HPDFOutline") == 0)
        Data_Get_Struct(parent, HPDF_Dict_Rec, outline1);

    if (HPDF_StrCmp(rb_obj_classname(encoder), "HPDFEncoder") == 0)
        Data_Get_Struct(encoder, HPDF_Encoder_Rec, e);

    s = StringValuePtr(title);

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_create_outline pdf=%p\n", pdf));

    outline2 = HPDF_CreateOutline(pdf, outline1, s, e);

    return Data_Wrap_Struct (rb_cHPDFOutline, 0, 0, outline2);
}


static VALUE
hpdf_outline_set_opend (VALUE obj, VALUE opend)
{
    HPDF_Outline outline;
    HPDF_STATUS ret;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, outline);
    i = NUM2INT(opend);

    HPDF_PTRACE(("hpdf_outline_set_opend outline=%p\n", outline));

    ret = HPDF_Outline_SetOpened(outline, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_outline_set_destination (VALUE obj, VALUE dest)
{
    HPDF_Outline outline;
    HPDF_Destination d;
    HPDF_STATUS ret;

    if (HPDF_StrCmp(rb_obj_classname(dest), "HPDFDestination") != 0)
        rb_raise(rb_eHPDFError, "invalid argument(1).");

    Data_Get_Struct(obj, HPDF_Dict_Rec, outline);
    Data_Get_Struct(dest, HPDF_Array_Rec, d);

    HPDF_PTRACE(("hpdf_outline_set_destination outline=%p\n", outline));

    ret = HPDF_Outline_SetDestination(outline, d);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_create_destination (VALUE obj)
{
    HPDF_Page page;
    HPDF_Destination d;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_create_destination page=%p\n", page));

    d = HPDF_Page_CreateDestination(page);

    return Data_Wrap_Struct (rb_cHPDFDestination, 0, 0, d);
}

static VALUE
hpdf_destination_set_xyz (VALUE obj, VALUE left, VALUE top, VALUE zoom)
{
    HPDF_Destination d;
    HPDF_STATUS ret;
    HPDF_INT i1;
    HPDF_INT i2;
    HPDF_INT i3;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);
    i1 = NUM2INT(left);
    i2 = NUM2INT(top);
    i3 = NUM2INT(zoom);

    HPDF_PTRACE(("hpdf_destination_set_xyz destination=%p\n", d));

    ret = HPDF_Destination_SetXYZ(d, i1, i2, i3);

    return INT2NUM(ret);
}

static VALUE
hpdf_destination_set_fit (VALUE obj)
{
    HPDF_Destination d;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);

    HPDF_PTRACE(("hpdf_destination_set_fit destination=%p\n", d));

    ret = HPDF_Destination_SetFit(d);

    return INT2NUM(ret);
}

static VALUE
hpdf_destination_set_fit_h (VALUE obj, VALUE top)
{
    HPDF_Destination d;
    HPDF_STATUS ret;
    HPDF_INT i1;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);
    i1 = NUM2INT(top);

    HPDF_PTRACE(("hpdf_destination_set_fit_h destination=%p\n", d));

    ret = HPDF_Destination_SetFitH(d, i1);

    return INT2NUM(ret);
}

static VALUE
hpdf_destination_set_fit_v (VALUE obj, VALUE left)
{
    HPDF_Destination d;
    HPDF_STATUS ret;
    HPDF_INT i1;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);
    i1 = NUM2INT(left);

    HPDF_PTRACE(("hpdf_destination_set_fit_v destination=%p\n", d));

    ret = HPDF_Destination_SetFitV(d, i1);

    return INT2NUM(ret);
}

static VALUE
hpdf_destination_set_fit_b (VALUE obj)
{
    HPDF_Destination d;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);

    HPDF_PTRACE(("hpdf_destination_set_fit_b destination=%p\n", d));

    ret = HPDF_Destination_SetFitB(d);

    return INT2NUM(ret);
}

static VALUE
hpdf_destination_set_fit_bh (VALUE obj, VALUE top)
{
    HPDF_Destination d;
    HPDF_STATUS ret;
    HPDF_INT i1;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);
    i1 = NUM2INT(top);

    HPDF_PTRACE(("hpdf_destination_set_fit_bh destination=%p\n", d));

    ret = HPDF_Destination_SetFitBH(d, i1);

    return INT2NUM(ret);
}

static VALUE
hpdf_destination_set_fit_bv (VALUE obj, VALUE left)
{
    HPDF_Destination d;
    HPDF_STATUS ret;
    HPDF_INT i1;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);
    i1 = NUM2INT(left);

    HPDF_PTRACE(("hpdf_destination_set_fit_bv destination=%p\n", d));

    ret = HPDF_Destination_SetFitBV(d, i1);

    return INT2NUM(ret);
}


static VALUE
hpdf_destination_set_fit_r (VALUE obj, VALUE left, VALUE bottom, VALUE right, VALUE top)
{
    HPDF_Destination d;
    HPDF_STATUS ret;
    HPDF_INT i1;
    HPDF_INT i2;
    HPDF_INT i3;
    HPDF_INT i4;

    Data_Get_Struct(obj, HPDF_Array_Rec, d);
    i1 = NUM2INT(left);
    i2 = NUM2INT(bottom);
    i3 = NUM2INT(right);
    i4 = NUM2INT(top);

    HPDF_PTRACE(("hpdf_destination_set_fit_r destination=%p\n", d));

    ret = HPDF_Destination_SetFitR(d, i1, i2, i3, i4);

    return INT2NUM(ret);
}

static VALUE
hpdf_get_encoder (VALUE obj, VALUE encoding_name)
{
    HPDF_Encoder encoder;
    HPDF_Doc pdf;
    const char *s1;

    s1 = StringValuePtr(encoding_name);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_encoder pdf=%p\n", pdf));

    encoder = HPDF_GetEncoder(pdf, s1);

    return Data_Wrap_Struct (rb_cHPDFEncoder, 0, 0, encoder);
}

static VALUE
hpdf_get_current_encoder (VALUE obj)
{
    HPDF_Encoder encoder;
    HPDF_Doc pdf;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_current_encoder pdf=%p\n", pdf));

    encoder = HPDF_GetCurrentEncoder(pdf);

    return Data_Wrap_Struct (rb_cHPDFEncoder, 0, 0, encoder);
}

static VALUE
hpdf_set_current_encoder (VALUE obj, VALUE encoding_name)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;
    const char *s1;

    s1 = StringValuePtr(encoding_name);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_set_current_encoder pdf=%p\n", pdf));

    ret = HPDF_SetCurrentEncoder(pdf, s1);

    return INT2NUM(ret);
}

static VALUE
hpdf_encoder_get_type (VALUE obj)
{
    HPDF_Encoder encoder;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Encoder_Rec, encoder);

    HPDF_PTRACE(("hpdf_encoder_get_type encoder=%p\n", encoder));

    ret = HPDF_Encoder_GetType(encoder);

    return INT2NUM(ret);
}

static VALUE
hpdf_encoder_get_byte_type (VALUE obj, VALUE text, VALUE index)
{
    HPDF_Encoder encoder;
    const char *s;
    HPDF_INT i;
    HPDF_STATUS ret;

    s = StringValuePtr(text);
    i = NUM2INT(index);

    Data_Get_Struct(obj, HPDF_Encoder_Rec, encoder);

    HPDF_PTRACE(("hpdf_encoder_get_byte_type encoder=%p\n", encoder));

    ret = HPDF_Encoder_GetByteType(encoder, s, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_encoder_get_unicode (VALUE obj, VALUE code)
{
    HPDF_Encoder encoder;
    HPDF_INT i;
    HPDF_STATUS ret;

    i = NUM2INT(code);

    Data_Get_Struct(obj, HPDF_Encoder_Rec, encoder);

    HPDF_PTRACE(("hpdf_encoder_get_unicode encoder=%p\n", encoder));

    ret = HPDF_Encoder_GetUnicode(encoder, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_encoder_get_writing_mode (VALUE obj)
{
    HPDF_Encoder encoder;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Encoder_Rec, encoder);

    HPDF_PTRACE(("hpdf_encoder_get_writing_mode encoder=%p\n", encoder));

    ret = HPDF_Encoder_GetWritingMode(encoder);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_jp_encodings (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_jp_encodings pdf=%p\n", pdf));

    ret = HPDF_UseJPEncodings(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_kr_encodings (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_kr_encodings pdf=%p\n", pdf));

    ret = HPDF_UseKREncodings(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_cns_encodings (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_cns_encodings pdf=%p\n", pdf));

    ret = HPDF_UseCNSEncodings(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_use_cnt_encodings (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_use_cnt_encodings pdf=%p\n", pdf));

    ret = HPDF_UseCNTEncodings(pdf);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_create_text_annot (VALUE obj, VALUE left, VALUE bottom, VALUE right, VALUE top, VALUE text, VALUE encoder)
{
    HPDF_Page page;
    HPDF_Rect rect;
    HPDF_Encoder e = NULL;
    const char *s;
    HPDF_Annotation annot;

    if (HPDF_StrCmp(rb_obj_classname(encoder), "HPDFEncoder") == 0)
        Data_Get_Struct(encoder, HPDF_Encoder_Rec, e);

    s = StringValuePtr(text);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    rect.left = NUM2INT(left);
    rect.bottom = NUM2INT(bottom);
    rect.right = NUM2INT(right);
    rect.top = NUM2INT(top);

    HPDF_PTRACE(("hpdf_page_create_text_annot page=%p\n", page));

    annot = HPDF_Page_CreateTextAnnot(page, rect, s, e);

    return Data_Wrap_Struct (rb_cHPDFAnnotation, 0, 0, annot);
}


static VALUE
hpdf_page_create_link_annot (VALUE obj, VALUE left, VALUE bottom, VALUE right, VALUE top, VALUE dest)
{
    HPDF_Page page;
    HPDF_Rect rect;
    HPDF_Destination d = NULL;
    HPDF_Annotation annot;

    if (HPDF_StrCmp(rb_obj_classname(dest), "HPDFDestination") == 0)
        Data_Get_Struct(dest, HPDF_Array_Rec, d);

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    rect.left = NUM2INT(left);
    rect.bottom = NUM2INT(bottom);
    rect.right = NUM2INT(right);
    rect.top = NUM2INT(top);

    HPDF_PTRACE(("hpdf_page_create_link_annot page=%p\n", page));

    annot = HPDF_Page_CreateLinkAnnot(page, rect, d);

    return Data_Wrap_Struct (rb_cHPDFAnnotation, 0, 0, annot);
}

static VALUE
hpdf_page_create_uri_link_annot (VALUE obj, VALUE left, VALUE bottom, VALUE right, VALUE top, VALUE uri)
{
    HPDF_Page page;
    HPDF_Rect rect;
    const char *s;
    HPDF_Annotation annot;

    s = StringValuePtr(uri);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    rect.left = NUM2INT(left);
    rect.bottom = NUM2INT(bottom);
    rect.right = NUM2INT(right);
    rect.top = NUM2INT(top);

    HPDF_PTRACE(("hpdf_page_create_uri_link_annot page=%p\n", page));

    annot = HPDF_Page_CreateURILinkAnnot(page, rect, s);

    return Data_Wrap_Struct (rb_cHPDFAnnotation, 0, 0, annot);
}

static VALUE
hpdf_linkannot_set_highlight_mode (VALUE obj, VALUE mode)
{
    HPDF_Annotation annot;
    HPDF_STATUS ret;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, annot);
    i = NUM2INT(mode);

    HPDF_PTRACE(("hpdf_linkannot_set_highlight_mode annot=%p\n", annot));

    ret = HPDF_LinkAnnot_SetHighlightMode(annot, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_linkannot_set_border_style (VALUE obj, VALUE width, VALUE dash_on, VALUE dash_off)
{
    HPDF_Annotation annot;
    HPDF_STATUS ret;
    HPDF_INT i1;
    HPDF_INT i2;
    HPDF_INT i3;

    Data_Get_Struct(obj, HPDF_Dict_Rec, annot);
    i1 = NUM2INT(width);
    i2 = NUM2INT(dash_on);
    i3 = NUM2INT(dash_off);

    HPDF_PTRACE(("hpdf_linkannot_set_border_style annot=%p\n", annot));

    ret = HPDF_LinkAnnot_SetBorderStyle(annot, i1, i2, i3);

    return INT2NUM(ret);
}

static VALUE
hpdf_textannot_set_icon (VALUE obj, VALUE icon)
{
    HPDF_Annotation annot;
    HPDF_STATUS ret;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, annot);
    i = NUM2INT(icon);

    HPDF_PTRACE(("hpdf_textannot_set_highlight_mode annot=%p\n", annot));

    ret = HPDF_TextAnnot_SetIcon(annot, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_textannot_set_opened (VALUE obj, VALUE opened)
{
    HPDF_Annotation annot;
    HPDF_STATUS ret;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, annot);
    i = NUM2INT(opened);

    HPDF_PTRACE(("hpdf_textannot_set_opened annot=%p\n", annot));

    ret = HPDF_TextAnnot_SetOpened(annot, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_load_png_image_from_file (VALUE obj, VALUE file_name)
{
    HPDF_Doc pdf;
    HPDF_Image image;
    const char *s;

    s = StringValuePtr(file_name);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_load_png_image_from_file pdf=%p\n", pdf));

    image = HPDF_LoadPngImageFromFile(pdf, s);

    return Data_Wrap_Struct (rb_cHPDFImage, 0, 0, image);
}


static VALUE
hpdf_load_jpeg_image_from_file (VALUE obj, VALUE file_name)
{
    HPDF_Doc pdf;
    HPDF_Image image;
    const char *s;

    s = StringValuePtr(file_name);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_load_png_image_from_file pdf=%p\n", pdf));

    image = HPDF_LoadJpegImageFromFile(pdf, s);

    return Data_Wrap_Struct (rb_cHPDFImage, 0, 0, image);
}


static VALUE
hpdf_image_get_size (VALUE obj)
{
    HPDF_Image image;
    HPDF_Point p;
    VALUE ret;
    VALUE x;
    VALUE y;

    Data_Get_Struct(obj, HPDF_Dict_Rec, image);

    HPDF_PTRACE(("hpdf_image_get_size image=%p\n", image));

    p = HPDF_Image_GetSize(image);

    ret = rb_ary_new();
    x = rb_float_new(p.x);
    y = rb_float_new(p.y);
    rb_ary_push(ret, x);
    rb_ary_push(ret, y);

    return ret;
}


static VALUE
hpdf_image_get_width (VALUE obj)
{
    HPDF_Image image;
    HPDF_UINT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, image);

    HPDF_PTRACE(("hpdf_image_get_width image=%p\n", image));

    i = HPDF_Image_GetWidth(image);

    return INT2NUM(i);
}


static VALUE
hpdf_image_get_height (VALUE obj)
{
    HPDF_Image image;
    HPDF_UINT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, image);

    HPDF_PTRACE(("hpdf_image_get_height image=%p\n", image));

    i = HPDF_Image_GetHeight(image);

    return INT2NUM(i);
}

static VALUE
hpdf_image_get_bits_per_component (VALUE obj)
{
    HPDF_Image image;
    HPDF_UINT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, image);

    HPDF_PTRACE(("hpdf_encoder_get_unicode image=%p\n", image));

    i = HPDF_Image_GetBitsPerComponent(image);

    return INT2NUM(i);
}

static VALUE
hpdf_image_get_color_space (VALUE obj)
{
    const char* ret;
    HPDF_Image image;

    Data_Get_Struct(obj, HPDF_Dict_Rec, image);

    HPDF_PTRACE(("hpdf_image_get_color_space image=%p\n", image));

    ret = HPDF_Image_GetColorSpace(image);

    return rb_str_new2(ret);
}

static VALUE
hpdf_image_set_color_mask (VALUE obj, VALUE rmin, VALUE rmax, VALUE gmin, VALUE gmax, VALUE bmin, VALUE bmax)
{
    HPDF_Image image;
    HPDF_STATUS ret;
    HPDF_INT i1;
    HPDF_INT i2;
    HPDF_INT i3;
    HPDF_INT i4;
    HPDF_INT i5;
    HPDF_INT i6;

    Data_Get_Struct(obj, HPDF_Dict_Rec, image);
    i1 = NUM2INT(rmin);
    i2 = NUM2INT(rmax);
    i3 = NUM2INT(gmin);
    i4 = NUM2INT(gmax);
    i5 = NUM2INT(bmin);
    i6 = NUM2INT(bmax);

    HPDF_PTRACE(("hpdf_image_set_color_mask image=%p\n", image));

    ret = HPDF_Image_SetColorMask(image, i1, i2, i3, i4, i5, i6);

    return INT2NUM(ret);
}

static VALUE
hpdf_image_set_mask_image (VALUE obj, VALUE mask_image)
{
    HPDF_Image image1;
    HPDF_Image image2;
    HPDF_STATUS ret;

    if (HPDF_StrCmp(rb_obj_classname(mask_image), "HPDFImage") != 0)
        rb_raise(rb_eHPDFError, "invalid argument(1).");

    Data_Get_Struct(obj, HPDF_Dict_Rec, image1);
    Data_Get_Struct(mask_image, HPDF_Dict_Rec, image2);

    HPDF_PTRACE(("hpdf_image_set_mask_image image=%p\n", image1));

    ret = HPDF_Image_SetMaskImage(image1, image2);

    return INT2NUM(ret);
}

static VALUE
hpdf_set_info_attr (VALUE obj, VALUE type, VALUE value)
{
    HPDF_Doc pdf;
    const char *s;
    HPDF_INT i;
    HPDF_STATUS ret;

    i = NUM2INT(type);
    s = StringValuePtr(value);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_set_info_attr pdf=%p\n", pdf));

    ret = HPDF_SetInfoAttr(pdf, i, s);

    return INT2NUM(ret);
}

static VALUE
hpdf_get_info_attr (VALUE obj, VALUE type)
{
    HPDF_Doc pdf;
    HPDF_INT i;
    const char *ret;

    i = NUM2INT(type);
    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_get_info_attr pdf=%p\n", pdf));

    ret = HPDF_GetInfoAttr(pdf, i);

    return rb_str_new2(ret);
}

static VALUE
hpdf_set_info_date_attr (VALUE obj, VALUE type, VALUE year, VALUE month, VALUE day, VALUE hour, VALUE minutes, VALUE seconds, VALUE ind, VALUE off_hour, VALUE off_minuttes)
{
    HPDF_Doc pdf;
    const char *s;
    HPDF_INT tp;
    HPDF_Date dt;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);
    s = StringValuePtr(ind);
    if (HPDF_StrLen(s, -1) != 1 || (s[0] != '+' && s[0] != '-' && s[0] != 'Z' && s[0] != ' ')) {
        rb_raise(rb_eHPDFError, "The eighth argument must be either of '+','-','Z',' '.");
    }

    tp = NUM2INT(type);
    dt.year = NUM2INT(year);
    dt.month = NUM2INT(month);
    dt.day = NUM2INT(day);
    dt.hour = NUM2INT(hour);
    dt.minutes = NUM2INT(minutes);
    dt.seconds = NUM2INT(seconds);
    dt.ind = s[0];
    dt.off_hour = NUM2INT(off_hour);
    dt.off_minutes = NUM2INT(off_minuttes);

    HPDF_PTRACE(("hpdf_set_info_attr pdf=%p\n", pdf));

    ret = HPDF_SetInfoDateAttr(pdf, tp, dt);

    return INT2NUM(ret);
}

static VALUE
hpdf_set_password (VALUE obj, VALUE owner_passwd, VALUE user_passwd)
{
    HPDF_Doc pdf;
    const char *s1;
    const char *s2;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);
    s1 = StringValuePtr(owner_passwd);
    s2 = StringValuePtr(user_passwd);

    HPDF_PTRACE(("hpdf_set_password pdf=%p\n", pdf));

    ret = HPDF_SetPassword(pdf, s1, s2);

    return INT2NUM(ret);
}

static VALUE
hpdf_set_permission (VALUE obj, VALUE permission)
{
    HPDF_Doc pdf;
    HPDF_INT i;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);
    i = NUM2INT(permission);

    HPDF_PTRACE(("hpdf_set_permission pdf=%p\n", pdf));

    ret = HPDF_SetPermission(pdf, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_set_encryption_mode (VALUE obj, VALUE mode, VALUE key_len)
{
    HPDF_Doc pdf;
    HPDF_INT i1;
    HPDF_INT i2;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);
    i1 = NUM2INT(mode);
    i2 = NUM2INT(key_len);

    HPDF_PTRACE(("hpdf_set_encryption_mode pdf=%p\n", pdf));

    ret = HPDF_SetEncryptionMode(pdf, i1, i2);

    return INT2NUM(ret);
}

static VALUE
hpdf_set_compression_mode (VALUE obj, VALUE mode)
{
    HPDF_Doc pdf;
    HPDF_INT i;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);
    i = NUM2INT(mode);

    HPDF_PTRACE(("hpdf_set_compression_mode pdf=%p\n", pdf));

    ret = HPDF_SetCompressionMode(pdf, i);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_text_width (VALUE obj, VALUE text)
{
    HPDF_Page page;
    HPDF_REAL f;
    const char *s;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    s = StringValuePtr(text);

    HPDF_PTRACE(("hpdf_page_text_width page=%p\n", page));

    f = HPDF_Page_TextWidth(page, s);

    return rb_float_new(f);
}

static VALUE
hpdf_page_measure_text (VALUE obj, VALUE text, VALUE width, VALUE wordwrap)
{
    HPDF_Page page;
    const char *s;
    HPDF_INT i1;
    HPDF_INT i2;
    HPDF_INT ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    s = StringValuePtr(text);
    i1 = NUM2INT(width);
    i2 = NUM2INT(wordwrap);

    HPDF_PTRACE(("hpdf_page_test_width page=%p\n", page));

    ret = HPDF_Page_MeasureText(page, s, i1, i2, NULL);

    return INT2NUM(ret);
}


static VALUE
hpdf_create_ext_gstate (VALUE obj)
{
    HPDF_Doc pdf;
    HPDF_ExtGState gstate;

    Data_Get_Struct(obj, HPDF_Doc_Rec, pdf);

    HPDF_PTRACE(("hpdf_create_ext_gstate pdf=%p\n", pdf));

    gstate = HPDF_CreateExtGState(pdf);

    return Data_Wrap_Struct (rb_cHPDFExtGState, 0, 0, gstate);
}


static VALUE
hpdf_ext_gstate_set_alpha_stroke (VALUE obj, VALUE value)
{
    HPDF_ExtGState gstate;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(value);
    Data_Get_Struct(obj, HPDF_Dict_Rec, gstate);

    HPDF_PTRACE(("hpdf_ext_gstate_set_alpha_stroke page=%p\n", gstate));

    ret = HPDF_ExtGState_SetAlphaStroke(gstate, f);

    return INT2NUM(ret);
}


static VALUE
hpdf_ext_gstate_set_alpha_fill (VALUE obj, VALUE value)
{
    HPDF_ExtGState gstate;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(value);
    Data_Get_Struct(obj, HPDF_Dict_Rec, gstate);

    HPDF_PTRACE(("hpdf_ext_gstate_set_alpha_fill page=%p\n", gstate));

    ret = HPDF_ExtGState_SetAlphaFill(gstate, f);

    return INT2NUM(ret);
}


static VALUE
hpdf_ext_gstate_set_blend_mode (VALUE obj, VALUE mode)
{
    HPDF_ExtGState gstate;
    HPDF_STATUS ret;
    HPDF_INT i;

    i = NUM2INT(mode);
    Data_Get_Struct(obj, HPDF_Dict_Rec, gstate);

    HPDF_PTRACE(("hpdf_ext_gstate_set_blend_mode page=%p\n", gstate));

    ret = HPDF_ExtGState_SetBlendMode(gstate, i);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_set_ext_gstate (VALUE obj, VALUE gstate)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_ExtGState gs;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    Data_Get_Struct(gstate, HPDF_Dict_Rec, gs);

    HPDF_PTRACE(("hpdf_page_set_ext_gstate page=%p\n", page));

    ret = HPDF_Page_SetExtGState(page, gs);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_get_width (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_width page=%p\n", page));

    f = HPDF_Page_GetWidth(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_height (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_height page=%p\n", page));

    f = HPDF_Page_GetHeight(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_gmode (VALUE obj)
{
    HPDF_Page page;
    HPDF_UINT16 ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_gmode page=%p\n", page));

    ret = HPDF_Page_GetGMode(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_get_current_pos (VALUE obj)
{
    HPDF_Page page;
    HPDF_Point p;
    VALUE ret;
    VALUE x;
    VALUE y;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_current_pos page=%p\n", page));

    p = HPDF_Page_GetCurrentPos(page);

    ret = rb_ary_new();
    x = rb_float_new(p.x);
    y = rb_float_new(p.y);
    rb_ary_push(ret, x);
    rb_ary_push(ret, y);

    return ret;
}

static VALUE
hpdf_page_get_current_text_pos (VALUE obj)
{
    HPDF_Page page;
    HPDF_Point p;
    VALUE ret;
    VALUE x;
    VALUE y;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_current_text_pos page=%p\n", page));

    p = HPDF_Page_GetCurrentTextPos(page);

    ret = rb_ary_new();
    x = rb_float_new(p.x);
    y = rb_float_new(p.y);
    rb_ary_push(ret, x);
    rb_ary_push(ret, y);

    return ret;
}

static VALUE
hpdf_page_get_current_font (VALUE obj)
{
    HPDF_Page page;
    HPDF_Font font;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_current_font page=%p\n", page));

    font = HPDF_Page_GetCurrentFont(page);

    return Data_Wrap_Struct (rb_cHPDFFont, 0, 0, font);
}

static VALUE
hpdf_font_get_font_name (VALUE obj)
{
    HPDF_Font font;
    const char* font_name;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);

    HPDF_PTRACE(("hpdf_font_get_font_name font=%p\n", font));

    font_name = HPDF_Font_GetFontName(font);

    return rb_str_new2(font_name);
}

static VALUE
hpdf_font_get_encoding_name (VALUE obj)
{
    HPDF_Font font;
    const char* encoding_name;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);

    HPDF_PTRACE(("hpdf_font_get_encoding_name font=%p\n", font));

    encoding_name = HPDF_Font_GetEncodingName(font);

    return rb_str_new2(encoding_name);
}

static VALUE
hpdf_font_get_unicode_width (VALUE obj, VALUE code)
{
    HPDF_Font font;
    HPDF_UINT i;
    HPDF_INT ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);
    i = NUM2INT(code);

    HPDF_PTRACE(("hpdf_font_get_unicode_width font=%p\n", font));

    ret = HPDF_Font_GetUnicodeWidth(font, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_font_get_bbox (VALUE obj)
{
    HPDF_Font font;
    HPDF_Rect rect;
    VALUE ret;
    VALUE left;
    VALUE bottom;
    VALUE right;
    VALUE top;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);

    HPDF_PTRACE(("hpdf_font_get_bbox font=%p\n", font));

    rect = HPDF_Font_GetBBox(font);

    ret = rb_ary_new();
    left = rb_float_new(rect.left);
    bottom = rb_float_new(rect.bottom);
    right = rb_float_new(rect.right);
    top = rb_float_new(rect.top);
    rb_ary_push(ret, left);
    rb_ary_push(ret, bottom);
    rb_ary_push(ret, right);
    rb_ary_push(ret, top);

    return ret;
}

static VALUE
hpdf_font_get_ascent (VALUE obj)
{
    HPDF_Font font;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);

    HPDF_PTRACE(("hpdf_font_get_ascent font=%p\n", font));

    i = HPDF_Font_GetAscent(font);

    return NUM2INT(i);
}

static VALUE
hpdf_font_get_descent (VALUE obj)
{
    HPDF_Font font;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);

    HPDF_PTRACE(("hpdf_font_get_descent font=%p\n", font));

    i = HPDF_Font_GetDescent(font);

    return NUM2INT(i);
}

static VALUE
hpdf_font_get_x_height (VALUE obj)
{
    HPDF_Font font;
    HPDF_UINT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);

    HPDF_PTRACE(("hpdf_font_get_x_height font=%p\n", font));

    i = HPDF_Font_GetXHeight(font);

    return NUM2INT(i);
}

static VALUE
hpdf_font_get_cap_height (VALUE obj)
{
    HPDF_Font font;
    HPDF_UINT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, font);

    HPDF_PTRACE(("hpdf_font_get_cap_height font=%p\n", font));

    i = HPDF_Font_GetCapHeight(font);

    return NUM2INT(i);
}

static VALUE
hpdf_page_get_current_font_size (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_current_font_size page=%p\n", page));

    f = HPDF_Page_GetCurrentFontSize(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_trans_matrix (VALUE obj)
{
    HPDF_Page page;
    HPDF_TransMatrix tm;
    VALUE ret;
    VALUE a;
    VALUE b;
    VALUE c;
    VALUE d;
    VALUE x;
    VALUE y;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_trans_matrix page=%p\n", page));

    tm = HPDF_Page_GetTransMatrix(page);

    ret = rb_ary_new();
    a = rb_float_new(tm.a);
    b = rb_float_new(tm.b);
    c = rb_float_new(tm.c);
    d = rb_float_new(tm.d);
    x = rb_float_new(tm.x);
    y = rb_float_new(tm.y);
    rb_ary_push(ret, a);
    rb_ary_push(ret, b);
    rb_ary_push(ret, c);
    rb_ary_push(ret, d);
    rb_ary_push(ret, x);
    rb_ary_push(ret, y);

    return ret;
}

static VALUE
hpdf_page_get_line_width (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_line_width page=%p\n", page));

    f = HPDF_Page_GetLineWidth(page);

    return rb_float_new(f);
}


static VALUE
hpdf_page_get_line_cap (VALUE obj)
{
    HPDF_Page page;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_line_cap page=%p\n", page));

    i = HPDF_Page_GetLineCap(page);

    return NUM2INT(i);
}

static VALUE
hpdf_page_get_line_join (VALUE obj)
{
    HPDF_Page page;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_line_join page=%p\n", page));

    i = HPDF_Page_GetLineJoin(page);

    return NUM2INT(i);
}

static VALUE
hpdf_page_get_miter_limit (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_miter_limit page=%p\n", page));

    f = HPDF_Page_GetMiterLimit(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_dash (VALUE obj)
{
    HPDF_Page page;
    HPDF_DashMode dm;
    VALUE ret;
    VALUE num_ptn;
    VALUE phase;
    HPDF_UINT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_dash page=%p\n", page));

    dm = HPDF_Page_GetDash(page);

    ret = rb_ary_new();
    num_ptn = NUM2INT(dm.num_ptn);
    rb_ary_push(ret, num_ptn);

    for (i = 0; i < dm.num_ptn; i++) {
        VALUE ptn = NUM2INT(dm.ptn[i]);
        rb_ary_push(ret, ptn);
    }

    phase = NUM2INT(dm.phase);
    rb_ary_push(ret, phase);

    return ret;
}

static VALUE
hpdf_page_get_flat (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_flat page=%p\n", page));

    f = HPDF_Page_GetFlat(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_char_space (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_char_space page=%p\n", page));

    f = HPDF_Page_GetCharSpace(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_word_space (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_word_space page=%p\n", page));

    f = HPDF_Page_GetWordSpace(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_horizontal_scalling (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_horizontal_scalling page=%p\n", page));

    f = HPDF_Page_GetHorizontalScalling(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_text_leading (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_text_leading page=%p\n", page));

    f = HPDF_Page_GetTextLeading(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_text_rendering_mode (VALUE obj)
{
    HPDF_Page page;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_text_rendering_mode page=%p\n", page));

    i = HPDF_Page_GetTextRenderingMode(page);

    return NUM2INT(i);
}

static VALUE
hpdf_page_get_text_raise (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_text_raise page=%p\n", page));

    f = HPDF_Page_GetTextRaise(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_rgb_fill (VALUE obj)
{
    HPDF_Page page;
    HPDF_RGBColor c;
    VALUE ret;
    VALUE r;
    VALUE g;
    VALUE b;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_rgb_fill page=%p\n", page));

    c = HPDF_Page_GetRGBFill(page);

    ret = rb_ary_new();
    r = rb_float_new(c.r);
    g = rb_float_new(c.g);
    b = rb_float_new(c.b);
    rb_ary_push(ret, r);
    rb_ary_push(ret, g);
    rb_ary_push(ret, b);

    return ret;
}

static VALUE
hpdf_page_get_rgb_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_RGBColor col;
    VALUE ret;
    VALUE r;
    VALUE g;
    VALUE b;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_rgb_stroke page=%p\n", page));

    col = HPDF_Page_GetRGBStroke(page);

    ret = rb_ary_new();
    r = rb_float_new(col.r);
    g = rb_float_new(col.g);
    b = rb_float_new(col.b);
    rb_ary_push(ret, r);
    rb_ary_push(ret, g);
    rb_ary_push(ret, b);

    return ret;
}

static VALUE
hpdf_page_get_cmyk_fill (VALUE obj)
{
    HPDF_Page page;
    HPDF_CMYKColor col;
    VALUE ret;
    VALUE c;
    VALUE m;
    VALUE y;
    VALUE k;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_cmyk_fill page=%p\n", page));

    col = HPDF_Page_GetCMYKFill(page);

    ret = rb_ary_new();
    c = rb_float_new(col.c);
    m = rb_float_new(col.m);
    y = rb_float_new(col.y);
    k = rb_float_new(col.k);
    rb_ary_push(ret, c);
    rb_ary_push(ret, m);
    rb_ary_push(ret, y);
    rb_ary_push(ret, k);

    return ret;
}

static VALUE
hpdf_page_get_cmyk_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_CMYKColor col;
    VALUE ret;
    VALUE c;
    VALUE m;
    VALUE y;
    VALUE k;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_cmyk_stroke page=%p\n", page));

    col = HPDF_Page_GetCMYKStroke(page);

    ret = rb_ary_new();
    c = rb_float_new(col.c);
    m = rb_float_new(col.m);
    y = rb_float_new(col.y);
    k = rb_float_new(col.k);
    rb_ary_push(ret, c);
    rb_ary_push(ret, m);
    rb_ary_push(ret, y);
    rb_ary_push(ret, k);

    return ret;
}

static VALUE
hpdf_page_get_gray_fill (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_gray_fill page=%p\n", page));

    f = HPDF_Page_GetGrayFill(page);

    return rb_float_new(f);
}


static VALUE
hpdf_page_get_gray_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_gray_stroke page=%p\n", page));

    f = HPDF_Page_GetGrayStroke(page);

    return rb_float_new(f);
}

static VALUE
hpdf_page_get_stroking_color_space (VALUE obj)
{
    HPDF_Page page;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_stroking_color_space page=%p\n", page));

    i = HPDF_Page_GetStrokingColorSpace(page);

    return NUM2INT(i);
}

static VALUE
hpdf_page_get_filling_color_space (VALUE obj)
{
    HPDF_Page page;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_filling_color_space page=%p\n", page));

    i = HPDF_Page_GetFillingColorSpace(page);

    return NUM2INT(i);
}

static VALUE
hpdf_page_get_text_matrix (VALUE obj)
{
    HPDF_Page page;
    HPDF_TransMatrix tm;
    VALUE ret;
    VALUE a;
    VALUE b;
    VALUE c;
    VALUE d;
    VALUE x;
    VALUE y;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_text_matrix page=%p\n", page));

    tm = HPDF_Page_GetTextMatrix(page);

    ret = rb_ary_new();
    a = rb_float_new(tm.a);
    b = rb_float_new(tm.b);
    c = rb_float_new(tm.c);
    d = rb_float_new(tm.d);
    x = rb_float_new(tm.x);
    y = rb_float_new(tm.y);
    rb_ary_push(ret, a);
    rb_ary_push(ret, b);
    rb_ary_push(ret, c);
    rb_ary_push(ret, d);
    rb_ary_push(ret, x);
    rb_ary_push(ret, y);

    return ret;
}


static VALUE
hpdf_page_set_line_width (VALUE obj, VALUE line_width)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(line_width);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_line_width page=%p\n", page));

    ret = HPDF_Page_SetLineWidth(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_line_cap (VALUE obj, VALUE line_cap)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_INT i;

    i = NUM2INT(line_cap);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_line_cap page=%p\n", page));

    ret = HPDF_Page_SetLineCap(page, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_line_join (VALUE obj, VALUE line_join)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(line_join);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_line_join page=%p\n", page));

    ret = HPDF_Page_SetLineCap(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_miter_limit (VALUE obj, VALUE miter_limit)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(miter_limit);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_miter_limit page=%p\n", page));

    ret = HPDF_Page_SetMiterLimit(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_dash (VALUE obj, VALUE ptn, VALUE phase)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_UINT16 dash_ptn[8];
    HPDF_UINT num_ptn;
    VALUE *pptn;
    HPDF_UINT dash_phase;
    HPDF_UINT i;

    if (TYPE(ptn) != T_ARRAY)
        rb_raise(rb_eHPDFError, "argument 1 must be an array.");

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_dash page=%p\n", page));

    dash_phase = NUM2INT(phase);
    num_ptn = RARRAY_LEN(ptn);
    if (!num_ptn) {
        ret = HPDF_Page_SetDash(page, NULL, 0, 0);
        return INT2NUM(ret);
    }

    for (i = 0; i < 8; i++)
        dash_ptn[i] = 0;

    pptn = RARRAY_PTR(ptn);
    for (i = 0; i < num_ptn; i++) {
        dash_ptn[i] = NUM2INT(*pptn);

        pptn++;
    }

    ret = HPDF_Page_SetDash(page, dash_ptn, num_ptn, dash_phase);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_flat (VALUE obj, VALUE flatness)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    f = NUM2DBL(flatness);
    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_set_flat page=%p\n", page));

    ret = HPDF_Page_SetFlat(page, f);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_gsave (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_gsave page=%p\n", page));

    ret = HPDF_Page_GSave(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_grestore (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_grestore page=%p\n", page));

    ret = HPDF_Page_GRestore(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_get_gstate_depth (VALUE obj)
{
    HPDF_Page page;
    HPDF_UINT ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_get_gstate_depth page=%p\n", page));

    ret = HPDF_Page_GetGStateDepth(page);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_concat (VALUE obj, VALUE a, VALUE b, VALUE c, VALUE d, VALUE x, VALUE y)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;
    HPDF_REAL f5;
    HPDF_REAL f6;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(a);
    f2 = NUM2DBL(b);
    f3 = NUM2DBL(c);
    f4 = NUM2DBL(d);
    f5 = NUM2DBL(x);
    f6 = NUM2DBL(y);

    HPDF_PTRACE(("hpdf_page_concat page=%p\n", page));

    ret = HPDF_Page_Concat(page, f1, f2, f3, f4, f5, f6);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_move_to (VALUE obj, VALUE x, VALUE y)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);

    HPDF_PTRACE(("hpdf_page_move_to page=%p\n", page));

    ret = HPDF_Page_MoveTo(page, f1, f2);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_line_to (VALUE obj, VALUE x, VALUE y)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);

    HPDF_PTRACE(("hpdf_page_line_to page=%p\n", page));

    ret = HPDF_Page_LineTo(page, f1, f2);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_curve_to (VALUE obj, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;
    HPDF_REAL f5;
    HPDF_REAL f6;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x1);
    f2 = NUM2DBL(y1);
    f3 = NUM2DBL(x2);
    f4 = NUM2DBL(y2);
    f5 = NUM2DBL(x3);
    f6 = NUM2DBL(y3);

    HPDF_PTRACE(("hpdf_page_curve_to page=%p\n", page));

    ret = HPDF_Page_CurveTo(page, f1, f2, f3, f4, f5, f6);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_curve_to2 (VALUE obj, VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x2);
    f2 = NUM2DBL(y2);
    f3 = NUM2DBL(x3);
    f4 = NUM2DBL(y3);

    HPDF_PTRACE(("hpdf_page_curve_to2 page=%p\n", page));

    ret = HPDF_Page_CurveTo2(page, f1, f2, f3, f4);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_curve_to3 (VALUE obj, VALUE x1, VALUE y1, VALUE x3, VALUE y3)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x1);
    f2 = NUM2DBL(y1);
    f3 = NUM2DBL(x3);
    f4 = NUM2DBL(y3);

    HPDF_PTRACE(("hpdf_page_curve_to3 page=%p\n", page));

    ret = HPDF_Page_CurveTo3(page, f1, f2, f3, f4);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_close_path (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_close_path page=%p\n", page));

    ret = HPDF_Page_ClosePath(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_rectangle (VALUE obj, VALUE x, VALUE y, VALUE width, VALUE height)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);
    f3 = NUM2DBL(width);
    f4 = NUM2DBL(height);

    HPDF_PTRACE(("hpdf_page_curve_to page=%p\n", page));

    ret = HPDF_Page_Rectangle(page, f1, f2, f3, f4);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_stroke page=%p\n", page));

    ret = HPDF_Page_Stroke(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_close_path_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_close_path_stroke page=%p\n", page));

    ret = HPDF_Page_ClosePathStroke(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_fill (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_fill page=%p\n", page));

    ret = HPDF_Page_Fill(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_eofill (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_eofill page=%p\n", page));

    ret = HPDF_Page_Eofill(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_fill_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_fill_stroke page=%p\n", page));

    ret = HPDF_Page_FillStroke(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_eofill_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_eofill_stroke page=%p\n", page));

    ret = HPDF_Page_EofillStroke(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_close_path_fill_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_close_path_fill_stroke page=%p\n", page));

    ret = HPDF_Page_ClosePathFillStroke(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_close_path_eofill_stroke (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_close_path_eofill_stroke page=%p\n", page));

    ret = HPDF_Page_ClosePathEofillStroke(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_end_path (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_end_path page=%p\n", page));

    ret = HPDF_Page_EndPath(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_clip (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_end_path page=%p\n", page));

    ret = HPDF_Page_Clip(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_eoclip (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_eoclip page=%p\n", page));

    ret = HPDF_Page_Eoclip(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_begin_text (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_begin_text page=%p\n", page));

    ret = HPDF_Page_BeginText(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_end_text (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_end_text page=%p\n", page));

    ret = HPDF_Page_EndText(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_char_space (VALUE obj, VALUE char_space)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f = NUM2DBL(char_space);

    HPDF_PTRACE(("hpdf_page_set_char_space page=%p\n", page));

    ret = HPDF_Page_SetCharSpace(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_word_space (VALUE obj, VALUE word_space)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f = NUM2DBL(word_space);

    HPDF_PTRACE(("hpdf_page_set_word_space page=%p\n", page));

    ret = HPDF_Page_SetWordSpace(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_horizontal_scalling (VALUE obj, VALUE scalling)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f = NUM2DBL(scalling);

    HPDF_PTRACE(("hpdf_page_set_horizontal_scalling page=%p\n", page));

    ret = HPDF_Page_SetHorizontalScalling(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_text_leading (VALUE obj, VALUE leading)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f = NUM2DBL(leading);

    HPDF_PTRACE(("hpdf_page_set_text_leading page=%p\n", page));

    ret = HPDF_Page_SetTextLeading(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_font_and_size (VALUE obj, VALUE font, VALUE size)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;
    HPDF_Font fo;

    if (HPDF_StrCmp(rb_obj_classname(font), "HPDFFont") != 0)
        rb_raise(rb_eHPDFError, "invalid argument(1).");

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    Data_Get_Struct(font, HPDF_Dict_Rec, fo);
    f = NUM2DBL(size);

    HPDF_PTRACE(("hpdf_page_set_text_leading page=%p\n", page));

    ret = HPDF_Page_SetFontAndSize(page, fo, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_text_rendering_mode (VALUE obj, VALUE mode)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_INT i;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    i = NUM2INT(mode);

    HPDF_PTRACE(("hpdf_page_set_text_leading page=%p\n", page));

    ret = HPDF_Page_SetTextRenderingMode(page, i);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_text_raise (VALUE obj, VALUE raise)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f = NUM2DBL(raise);

    HPDF_PTRACE(("hpdf_page_set_text_raise page=%p\n", page));

    ret = HPDF_Page_SetTextRaise(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_move_text_pos (VALUE obj, VALUE x, VALUE y)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);

    HPDF_PTRACE(("hpdf_page_move_text_pos page=%p\n", page));

    ret = HPDF_Page_MoveTextPos(page, f1, f2);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_move_text_pos2 (VALUE obj, VALUE x, VALUE y)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);

    HPDF_PTRACE(("hpdf_page_move_text_pos2 page=%p\n", page));

    ret = HPDF_Page_MoveTextPos2(page, f1, f2);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_set_text_matrix (VALUE obj, VALUE a, VALUE b, VALUE c, VALUE d, VALUE x, VALUE y)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;
    HPDF_REAL f5;
    HPDF_REAL f6;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(a);
    f2 = NUM2DBL(b);
    f3 = NUM2DBL(c);
    f4 = NUM2DBL(d);
    f5 = NUM2DBL(x);
    f6 = NUM2DBL(y);

    HPDF_PTRACE(("hpdf_page_set_text_matrix page=%p\n", page));

    ret = HPDF_Page_SetTextMatrix(page, f1, f2, f3, f4, f5, f6);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_move_to_next_line (VALUE obj)
{
    HPDF_Page page;
    HPDF_STATUS ret;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);

    HPDF_PTRACE(("hpdf_page_move_to_next_line page=%p\n", page));

    ret = HPDF_Page_MoveToNextLine(page);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_show_text (VALUE obj, VALUE text)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    const char *s;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    s = StringValuePtr(text);

    HPDF_PTRACE(("hpdf_page_show_text page=%p\n", page));

    ret = HPDF_Page_ShowText(page, s);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_show_text_next_line (VALUE obj, VALUE text)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    const char *s;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    s = StringValuePtr(text);

    HPDF_PTRACE(("hpdf_page_show_text_next_line page=%p\n", page));

    ret = HPDF_Page_ShowTextNextLine(page, s);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_show_text_next_line_ex (VALUE obj, VALUE char_space, VALUE word_space, VALUE text)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    const char *s;
    HPDF_REAL f1;
    HPDF_REAL f2;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    s = StringValuePtr(text);
    f1 = NUM2DBL(char_space);
    f2 = NUM2DBL(word_space);

    HPDF_PTRACE(("hpdf_page_show_text_next_line_ex page=%p\n", page));

    ret = HPDF_Page_ShowTextNextLineEx(page, f1, f2, s);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_gray_fill (VALUE obj, VALUE gray)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f = NUM2DBL(gray);

    HPDF_PTRACE(("hpdf_page_set_gray_fill page=%p\n", page));

    ret = HPDF_Page_SetGrayFill(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_gray_stroke (VALUE obj, VALUE gray)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f = NUM2DBL(gray);

    HPDF_PTRACE(("hpdf_page_set_gray_stroke page=%p\n", page));

    ret = HPDF_Page_SetGrayStroke(page, f);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_rgb_fill (VALUE obj, VALUE r, VALUE g, VALUE b)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(r);
    f2 = NUM2DBL(g);
    f3 = NUM2DBL(b);

    HPDF_PTRACE(("hpdf_page_set_rgb_fill page=%p\n", page));

    ret = HPDF_Page_SetRGBFill(page, f1, f2, f3);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_rgb_stroke (VALUE obj, VALUE r, VALUE g, VALUE b)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(r);
    f2 = NUM2DBL(g);
    f3 = NUM2DBL(b);

    HPDF_PTRACE(("hpdf_page_set_rgb_stroke page=%p\n", page));

    ret = HPDF_Page_SetRGBStroke(page, f1, f2, f3);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_cmyk_fill (VALUE obj, VALUE c, VALUE m, VALUE y, VALUE k)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(c);
    f2 = NUM2DBL(m);
    f3 = NUM2DBL(y);
    f4 = NUM2DBL(k);

    HPDF_PTRACE(("hpdf_page_set_cmyk_fill page=%p\n", page));

    ret = HPDF_Page_SetCMYKFill(page, f1, f2, f3, f4);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_cmyk_stroke (VALUE obj, VALUE c, VALUE m, VALUE y, VALUE k)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(c);
    f2 = NUM2DBL(m);
    f3 = NUM2DBL(y);
    f4 = NUM2DBL(k);

    HPDF_PTRACE(("hpdf_page_set_cmyk_stroke page=%p\n", page));

    ret = HPDF_Page_SetCMYKStroke(page, f1, f2, f3, f4);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_execute_xobject (VALUE obj, VALUE xobj)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_Image img;

    if (HPDF_StrCmp(rb_obj_classname(xobj), "HPDFImage") != 0)
        rb_raise(rb_eHPDFError, "invalid argument(1).");

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    Data_Get_Struct(xobj, HPDF_Dict_Rec, img);

    HPDF_PTRACE(("hpdf_page_execute_xobject page=%p\n", page));

    ret = HPDF_Page_ExecuteXObject(page, img);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_draw_image (VALUE obj, VALUE image, VALUE x, VALUE y, VALUE width, VALUE height)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_Image img;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;

    if (HPDF_StrCmp(rb_obj_classname(image), "HPDFImage") != 0)
        rb_raise(rb_eHPDFError, "invalid argument(1).");

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    Data_Get_Struct(image, HPDF_Dict_Rec, img);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);
    f3 = NUM2DBL(width);
    f4 = NUM2DBL(height);

    HPDF_PTRACE(("hpdf_page_draw_image page=%p\n", page));

    ret = HPDF_Page_DrawImage(page, img, f1, f2, f3, f4);

    return INT2NUM(ret);
}


static VALUE
hpdf_page_circle (VALUE obj, VALUE x, VALUE y, VALUE ray)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);
    f3 = NUM2DBL(ray);

    HPDF_PTRACE(("hpdf_page_circle page=%p\n", page));

    ret = HPDF_Page_Circle(page, f1, f2, f3);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_arc (VALUE obj, VALUE x, VALUE y, VALUE ray, VALUE ang1, VALUE ang2)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;
    HPDF_REAL f5;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);
    f3 = NUM2DBL(ray);
    f4 = NUM2DBL(ang1);
    f5 = NUM2DBL(ang2);

    HPDF_PTRACE(("hpdf_page_arc page=%p\n", page));

    ret = HPDF_Page_Arc(page, f1, f2, f3, f4, f5);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_ellipse (VALUE obj, VALUE x, VALUE y, VALUE xray, VALUE yray)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(x);
    f2 = NUM2DBL(y);
    f3 = NUM2DBL(xray);
    f4 = NUM2DBL(yray);

    HPDF_PTRACE(("hpdf_page_ellipse page=%p\n", page));

    ret = HPDF_Page_Ellipse(page, f1, f2, f3, f4);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_text_out (VALUE obj, VALUE xpos, VALUE ypos, VALUE text)
{
    HPDF_Page page;
    HPDF_STATUS ret;
    const char *s;
    HPDF_REAL x;
    HPDF_REAL y;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    s = StringValuePtr(text);
    x = NUM2DBL(xpos);
    y = NUM2DBL(ypos);

    HPDF_PTRACE(("hpdf_page_text_out page=%p\n", page));

    ret = HPDF_Page_TextOut(page, x, y, s);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_text_rect (VALUE obj, VALUE left, VALUE top, VALUE right, VALUE bottom, VALUE text, VALUE align)

{
    HPDF_Page page;
    HPDF_STATUS ret;
    const char *s;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_REAL f3;
    HPDF_REAL f4;
    HPDF_UINT i1;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    s = StringValuePtr(text);
    f1 = NUM2DBL(left);
    f2 = NUM2DBL(top);
    f3 = NUM2DBL(right);
    f4 = NUM2DBL(bottom);
    i1 = NUM2INT(align);

    HPDF_PTRACE(("hpdf_page_text_rect page=%p\n", page));

    ret = HPDF_Page_TextRect(page, f1, f2, f3, f4, s, i1, NULL);

    return INT2NUM(ret);
}

static VALUE
hpdf_page_set_slide_show (VALUE obj, VALUE type, VALUE disp_time, VALUE trans_time)

{
    HPDF_Page page;
    HPDF_STATUS ret;
    HPDF_REAL f1;
    HPDF_REAL f2;
    HPDF_UINT i1;

    Data_Get_Struct(obj, HPDF_Dict_Rec, page);
    f1 = NUM2DBL(disp_time);
    f2 = NUM2DBL(trans_time);
    i1 = NUM2INT(type);

    HPDF_PTRACE(("hpdf_page_set_slide_show page=%p\n", page));

    ret = HPDF_Page_SetSlideShow(page, i1, f1, f2);

    return INT2NUM(ret);
}



void
Init_hpdf()
{
    rb_cHPDFDoc = rb_define_class("HPDFDoc", rb_cObject);
    rb_cHPDFPage = rb_define_class("HPDFPage", rb_cObject);
    rb_cHPDFImage = rb_define_class("HPDFImage", rb_cObject);
    rb_cHPDFFont = rb_define_class("HPDFFont", rb_cObject);
    rb_cHPDFOutline = rb_define_class("HPDFOutline", rb_cObject);
    rb_cHPDFEncoder = rb_define_class("HPDFEncoder", rb_cObject);
    rb_cHPDFDestination = rb_define_class("HPDFDestination", rb_cObject);
    rb_cHPDFAnnotation = rb_define_class("HPDFAnnotation", rb_cObject);
    rb_cHPDFExtGState = rb_define_class("HPDFExtGState", rb_cObject);


    rb_define_singleton_method(rb_cHPDFDoc, "new", hpdf_new, 0);
    rb_define_method(rb_cHPDFDoc, "new_doc", hpdf_new_doc, 0);
    rb_define_method(rb_cHPDFDoc, "free_doc", hpdf_free_doc, 0);
    rb_define_method(rb_cHPDFDoc, "has_doc", hpdf_has_doc, 0);
    rb_define_method(rb_cHPDFDoc, "free_doc_all", hpdf_free_doc_all, 0);
    rb_define_method(rb_cHPDFDoc, "save_to_file", hpdf_save_to_file, 1);
    rb_define_method(rb_cHPDFDoc, "get_error", hpdf_get_error, 0);
    rb_define_method(rb_cHPDFDoc, "reset_error", hpdf_reset_error, 0);
    rb_define_method(rb_cHPDFDoc, "set_page_configuration", hpdf_set_page_configuration, 1);
    rb_define_method(rb_cHPDFDoc, "get_page_by_index", hpdf_get_page_by_index, 1);
    rb_define_method(rb_cHPDFDoc, "get_page_layout", hpdf_get_page_layout, 0);
    rb_define_method(rb_cHPDFDoc, "set_page_layout", hpdf_set_page_layout, 1);
    rb_define_method(rb_cHPDFDoc, "get_page_mode", hpdf_get_page_mode, 0);
    rb_define_method(rb_cHPDFDoc, "set_page_mode", hpdf_set_page_mode, 1);
    rb_define_method(rb_cHPDFDoc, "set_open_action", hpdf_set_open_action, 1);
    rb_define_method(rb_cHPDFDoc, "get_viewer_preference", hpdf_get_viewer_preference, 0);
    rb_define_method(rb_cHPDFDoc, "set_viewer_preference", hpdf_set_viewer_preference, 1);
    rb_define_method(rb_cHPDFDoc, "get_current_page", hpdf_get_current_page, 0);
    rb_define_method(rb_cHPDFDoc, "add_page", hpdf_add_page, 0);
    rb_define_method(rb_cHPDFDoc, "insert_page", hpdf_insert_page, 1);

    rb_define_method(rb_cHPDFPage, "set_width", hpdf_page_set_width, 1);
    rb_define_method(rb_cHPDFPage, "set_height", hpdf_page_set_height, 1);
    rb_define_method(rb_cHPDFPage, "set_size", hpdf_page_set_size, 2);
    rb_define_method(rb_cHPDFPage, "set_rotate", hpdf_page_set_rotate, 1);

    rb_define_method(rb_cHPDFDoc, "get_font", hpdf_get_font, 2);
    rb_define_method(rb_cHPDFDoc, "load_type1font_from_file", hpdf_load_type1font_from_file, 2);
    rb_define_method(rb_cHPDFDoc, "load_ttfont_from_file", hpdf_load_ttfont_from_file, 2);
    rb_define_method(rb_cHPDFDoc, "load_ttfont_from_file2", hpdf_load_ttfont_from_file2, 3);
    rb_define_method(rb_cHPDFDoc, "add_page_label", hpdf_add_page_label, 4);
    rb_define_method(rb_cHPDFDoc, "use_jp_fonts", hpdf_use_jp_fonts, 0);
    rb_define_method(rb_cHPDFDoc, "use_kr_fonts", hpdf_use_kr_fonts, 0);
    rb_define_method(rb_cHPDFDoc, "use_cns_fonts", hpdf_use_cns_fonts, 0);
    rb_define_method(rb_cHPDFDoc, "use_cnt_fonts", hpdf_use_cnt_fonts, 0);

    rb_define_method(rb_cHPDFDoc, "create_outline", hpdf_create_outline, 3);
    rb_define_method(rb_cHPDFOutline, "set_opend", hpdf_outline_set_opend, 1);
    rb_define_method(rb_cHPDFOutline, "set_destination", hpdf_outline_set_destination, 1);

    rb_define_method(rb_cHPDFPage, "create_destination", hpdf_page_create_destination, 0);
    rb_define_method(rb_cHPDFDestination, "set_xyz", hpdf_destination_set_xyz, 3);
    rb_define_method(rb_cHPDFDestination, "set_fit", hpdf_destination_set_fit, 0);
    rb_define_method(rb_cHPDFDestination, "set_fit_h", hpdf_destination_set_fit_h, 1);
    rb_define_method(rb_cHPDFDestination, "set_fit_v", hpdf_destination_set_fit_v, 1);
    rb_define_method(rb_cHPDFDestination, "set_fit_r", hpdf_destination_set_fit_r, 4);
    rb_define_method(rb_cHPDFDestination, "set_fit_b", hpdf_destination_set_fit_b, 0);
    rb_define_method(rb_cHPDFDestination, "set_fit_bh", hpdf_destination_set_fit_bh, 1);
    rb_define_method(rb_cHPDFDestination, "set_fit_bv", hpdf_destination_set_fit_bv, 1);

    rb_define_method(rb_cHPDFDoc, "get_encoder", hpdf_get_encoder, 1);
    rb_define_method(rb_cHPDFDoc, "get_current_encoder", hpdf_get_current_encoder, 0);
    rb_define_method(rb_cHPDFDoc, "set_current_encoder", hpdf_set_current_encoder, 1);
    rb_define_method(rb_cHPDFEncoder, "get_type", hpdf_encoder_get_type, 0);
    rb_define_method(rb_cHPDFEncoder, "get_byte_type", hpdf_encoder_get_byte_type, 1);
    rb_define_method(rb_cHPDFEncoder, "get_unicode", hpdf_encoder_get_unicode, 1);
    rb_define_method(rb_cHPDFEncoder, "get_writing_mode", hpdf_encoder_get_writing_mode, 0);
    rb_define_method(rb_cHPDFDoc, "use_jp_encodings", hpdf_use_jp_encodings, 0);
    rb_define_method(rb_cHPDFDoc, "use_kr_encodings", hpdf_use_kr_encodings, 0);
    rb_define_method(rb_cHPDFDoc, "use_cns_encodings", hpdf_use_cns_encodings, 0);
    rb_define_method(rb_cHPDFDoc, "use_cnt_encodings", hpdf_use_cnt_encodings, 0);

    rb_define_method(rb_cHPDFPage, "create_text_annot", hpdf_page_create_text_annot, 6);
    rb_define_method(rb_cHPDFPage, "create_link_annot", hpdf_page_create_link_annot, 5);
    rb_define_method(rb_cHPDFPage, "create_uri_link_annot", hpdf_page_create_uri_link_annot, 5);
    rb_define_method(rb_cHPDFAnnotation, "set_highlight_mode", hpdf_linkannot_set_highlight_mode, 1);
    rb_define_method(rb_cHPDFAnnotation, "set_border_style", hpdf_linkannot_set_border_style, 3);
    rb_define_method(rb_cHPDFAnnotation, "set_icon", hpdf_textannot_set_icon, 1);
    rb_define_method(rb_cHPDFAnnotation, "set_opened", hpdf_textannot_set_opened, 1);

    rb_define_method(rb_cHPDFDoc, "load_png_image_from_file", hpdf_load_png_image_from_file, 1);
    rb_define_method(rb_cHPDFDoc, "load_jpeg_image_from_file", hpdf_load_jpeg_image_from_file, 1);
    rb_define_method(rb_cHPDFImage, "get_size", hpdf_image_get_size, 0);
    rb_define_method(rb_cHPDFImage, "get_width", hpdf_image_get_width, 0);
    rb_define_method(rb_cHPDFImage, "get_height", hpdf_image_get_height, 0);
    rb_define_method(rb_cHPDFImage, "get_bits_per_component", hpdf_image_get_bits_per_component, 0);
    rb_define_method(rb_cHPDFImage, "get_color_space", hpdf_image_get_color_space, 0);
    rb_define_method(rb_cHPDFImage, "set_color_mask", hpdf_image_set_color_mask, 6);
    rb_define_method(rb_cHPDFImage, "set_mask_image", hpdf_image_set_mask_image, 1);

    rb_define_method(rb_cHPDFDoc, "set_info_attr", hpdf_set_info_attr, 2);
    rb_define_method(rb_cHPDFDoc, "get_info_attr", hpdf_get_info_attr, 1);
    rb_define_method(rb_cHPDFDoc, "set_info_date_attr", hpdf_set_info_date_attr, 10);
    rb_define_method(rb_cHPDFDoc, "set_password", hpdf_set_password, 2);
    rb_define_method(rb_cHPDFDoc, "set_permission", hpdf_set_permission, 1);
    rb_define_method(rb_cHPDFDoc, "set_encryption_mode", hpdf_set_encryption_mode, 2);
    rb_define_method(rb_cHPDFDoc, "set_compression_mode", hpdf_set_compression_mode, 1);

    rb_define_method(rb_cHPDFPage, "text_width", hpdf_page_text_width, 1);
    rb_define_method(rb_cHPDFPage, "measure_text", hpdf_page_measure_text, 3);
    rb_define_method(rb_cHPDFPage, "get_width", hpdf_page_get_width, 0);
    rb_define_method(rb_cHPDFPage, "get_height", hpdf_page_get_height, 0);
    rb_define_method(rb_cHPDFPage, "get_gmode", hpdf_page_get_gmode, 0);
    rb_define_method(rb_cHPDFPage, "get_current_pos", hpdf_page_get_current_pos, 0);
    rb_define_method(rb_cHPDFPage, "get_current_text_pos", hpdf_page_get_current_text_pos, 0);
    rb_define_method(rb_cHPDFPage, "get_current_font", hpdf_page_get_current_font, 0);

    rb_define_method(rb_cHPDFFont, "get_font_name", hpdf_font_get_font_name, 0);
    rb_define_method(rb_cHPDFFont, "get_encoding_name", hpdf_font_get_encoding_name, 0);
    rb_define_method(rb_cHPDFFont, "get_unicode_width", hpdf_font_get_unicode_width, 1);
    rb_define_method(rb_cHPDFFont, "get_bbox", hpdf_font_get_bbox, 0);
    rb_define_method(rb_cHPDFFont, "get_ascent", hpdf_font_get_ascent, 0);
    rb_define_method(rb_cHPDFFont, "get_descent", hpdf_font_get_descent, 0);
    rb_define_method(rb_cHPDFFont, "get_x_height", hpdf_font_get_x_height, 0);
    rb_define_method(rb_cHPDFFont, "get_cap_height", hpdf_font_get_cap_height, 0);

    rb_define_method(rb_cHPDFPage, "get_current_font_size", hpdf_page_get_current_font_size, 0);
    rb_define_method(rb_cHPDFPage, "get_trans_matrix", hpdf_page_get_trans_matrix, 0);
    rb_define_method(rb_cHPDFPage, "get_line_width", hpdf_page_get_line_width, 0);
    rb_define_method(rb_cHPDFPage, "get_line_cap", hpdf_page_get_line_cap, 0);
    rb_define_method(rb_cHPDFPage, "get_line_join", hpdf_page_get_line_join, 0);
    rb_define_method(rb_cHPDFPage, "get_miter_limit", hpdf_page_get_miter_limit, 0);
    rb_define_method(rb_cHPDFPage, "get_dash", hpdf_page_get_dash, 0);
    rb_define_method(rb_cHPDFPage, "get_flat", hpdf_page_get_flat, 0);
    rb_define_method(rb_cHPDFPage, "get_char_space", hpdf_page_get_char_space, 0);
    rb_define_method(rb_cHPDFPage, "get_word_space", hpdf_page_get_word_space, 0);
    rb_define_method(rb_cHPDFPage, "get_horizontal_scalling", hpdf_page_get_horizontal_scalling, 0);
    rb_define_method(rb_cHPDFPage, "get_text_leading", hpdf_page_get_text_leading, 0);
    rb_define_method(rb_cHPDFPage, "get_text_rendering_mode", hpdf_page_get_text_rendering_mode, 0);
    rb_define_method(rb_cHPDFPage, "get_text_raise", hpdf_page_get_text_raise, 0);
    rb_define_method(rb_cHPDFPage, "get_rgb_fill", hpdf_page_get_rgb_fill, 0);
    rb_define_method(rb_cHPDFPage, "get_rgb_stroke", hpdf_page_get_rgb_stroke, 0);
    rb_define_method(rb_cHPDFPage, "get_cmyk_fill", hpdf_page_get_cmyk_fill, 0);
    rb_define_method(rb_cHPDFPage, "get_cmyk_stroke", hpdf_page_get_cmyk_stroke, 0);
    rb_define_method(rb_cHPDFPage, "get_gray_fill", hpdf_page_get_gray_fill, 0);
    rb_define_method(rb_cHPDFPage, "get_gray_stroke", hpdf_page_get_gray_stroke, 0);
    rb_define_method(rb_cHPDFPage, "get_stroking_color_space", hpdf_page_get_stroking_color_space, 0);
    rb_define_method(rb_cHPDFPage, "get_filling_color_space", hpdf_page_get_filling_color_space, 0);
    rb_define_method(rb_cHPDFPage, "get_text_matrix", hpdf_page_get_text_matrix, 0);

    rb_define_method(rb_cHPDFPage, "set_line_width", hpdf_page_set_line_width, 1);
    rb_define_method(rb_cHPDFPage, "set_line_cap", hpdf_page_set_line_cap, 1);
    rb_define_method(rb_cHPDFPage, "set_line_join", hpdf_page_set_line_join, 1);
    rb_define_method(rb_cHPDFPage, "set_miter_limit", hpdf_page_set_miter_limit, 1);
    rb_define_method(rb_cHPDFPage, "set_dash", hpdf_page_set_dash, 2);
    rb_define_method(rb_cHPDFPage, "set_flat", hpdf_page_set_flat, 1);
    rb_define_method(rb_cHPDFPage, "gsave", hpdf_page_gsave, 0);
    rb_define_method(rb_cHPDFPage, "grestore", hpdf_page_grestore, 0);
    rb_define_method(rb_cHPDFPage, "get_gstate_depth", hpdf_page_get_gstate_depth, 0);
    rb_define_method(rb_cHPDFPage, "concat", hpdf_page_concat, 6);
    rb_define_method(rb_cHPDFPage, "move_to", hpdf_page_move_to, 2);
    rb_define_method(rb_cHPDFPage, "line_to", hpdf_page_line_to, 2);
    rb_define_method(rb_cHPDFPage, "curve_to", hpdf_page_curve_to, 6);
    rb_define_method(rb_cHPDFPage, "curve_to2", hpdf_page_curve_to2, 4);
    rb_define_method(rb_cHPDFPage, "curve_to3", hpdf_page_curve_to3, 4);
    rb_define_method(rb_cHPDFPage, "close_path", hpdf_page_close_path, 0);
    rb_define_method(rb_cHPDFPage, "rectangle", hpdf_page_rectangle, 4);
    rb_define_method(rb_cHPDFPage, "stroke", hpdf_page_stroke, 0);
    rb_define_method(rb_cHPDFPage, "close_path_stroke", hpdf_page_close_path_stroke, 0);
    rb_define_method(rb_cHPDFPage, "fill", hpdf_page_fill, 0);
    rb_define_method(rb_cHPDFPage, "eofill", hpdf_page_eofill, 0);
    rb_define_method(rb_cHPDFPage, "fill_stroke", hpdf_page_fill_stroke, 0);
    rb_define_method(rb_cHPDFPage, "eofill_stroke", hpdf_page_eofill_stroke, 0);
    rb_define_method(rb_cHPDFPage, "close_path_fill_stroke", hpdf_page_close_path_fill_stroke, 0);
    rb_define_method(rb_cHPDFPage, "close_path_eofill_stroke", hpdf_page_close_path_eofill_stroke, 0);
    rb_define_method(rb_cHPDFPage, "end_path", hpdf_page_end_path, 0);
    rb_define_method(rb_cHPDFPage, "clip", hpdf_page_clip, 0);
    rb_define_method(rb_cHPDFPage, "page_clip", hpdf_page_clip, 0);
    rb_define_method(rb_cHPDFPage, "eoclip", hpdf_page_eoclip, 0);
    rb_define_method(rb_cHPDFPage, "begin_text", hpdf_page_begin_text, 0);
    rb_define_method(rb_cHPDFPage, "end_text", hpdf_page_end_text, 0);
    rb_define_method(rb_cHPDFPage, "set_char_space", hpdf_page_set_char_space, 1);
    rb_define_method(rb_cHPDFPage, "set_word_space", hpdf_page_set_word_space, 1);
    rb_define_method(rb_cHPDFPage, "set_horizontal_scalling", hpdf_page_set_horizontal_scalling, 1);
    rb_define_method(rb_cHPDFPage, "set_text_leading", hpdf_page_set_text_leading, 1);
    rb_define_method(rb_cHPDFPage, "set_font_and_size", hpdf_page_set_font_and_size, 2);
    rb_define_method(rb_cHPDFPage, "set_text_rendering_mode", hpdf_page_set_text_rendering_mode, 1);
    rb_define_method(rb_cHPDFPage, "set_text_raise", hpdf_page_set_text_raise, 1);
    rb_define_method(rb_cHPDFPage, "move_text_pos", hpdf_page_move_text_pos, 2);
    rb_define_method(rb_cHPDFPage, "move_text_pos2", hpdf_page_move_text_pos2, 2);
    rb_define_method(rb_cHPDFPage, "set_text_matrix", hpdf_page_set_text_matrix, 6);
    rb_define_method(rb_cHPDFPage, "move_to_next_line", hpdf_page_move_to_next_line, 0);
    rb_define_method(rb_cHPDFPage, "show_text", hpdf_page_show_text, 1);
    rb_define_method(rb_cHPDFPage, "show_text_next_line", hpdf_page_show_text_next_line, 1);
    rb_define_method(rb_cHPDFPage, "show_text_next_line_ex", hpdf_page_show_text_next_line_ex, 3);
    rb_define_method(rb_cHPDFPage, "set_gray_fill", hpdf_page_set_gray_fill, 1);
    rb_define_method(rb_cHPDFPage, "set_gray_stroke", hpdf_page_set_gray_stroke, 1);
    rb_define_method(rb_cHPDFPage, "set_rgb_fill", hpdf_page_set_rgb_fill, 3);
    rb_define_method(rb_cHPDFPage, "set_rgb_stroke", hpdf_page_set_rgb_stroke, 3);
    rb_define_method(rb_cHPDFPage, "set_cmyk_fill", hpdf_page_set_cmyk_fill, 4);
    rb_define_method(rb_cHPDFPage, "set_cmyk_stroke", hpdf_page_set_cmyk_stroke, 4);
    rb_define_method(rb_cHPDFPage, "execute_xobject", hpdf_page_execute_xobject, 1);
    rb_define_method(rb_cHPDFPage, "draw_image", hpdf_page_draw_image, 5);
    rb_define_method(rb_cHPDFPage, "circle", hpdf_page_circle, 3);
    rb_define_method(rb_cHPDFPage, "ellipse", hpdf_page_ellipse, 4);
    rb_define_method(rb_cHPDFPage, "arc", hpdf_page_arc, 5);
    rb_define_method(rb_cHPDFPage, "text_out", hpdf_page_text_out, 3);
    rb_define_method(rb_cHPDFPage, "text_rect", hpdf_page_text_rect, 6);

    rb_define_method(rb_cHPDFPage, "set_slide_show", hpdf_page_set_slide_show, 3);

    rb_define_method(rb_cHPDFDoc, "create_ext_gstate", hpdf_create_ext_gstate, 0);
    rb_define_method(rb_cHPDFExtGState, "set_alpha_stroke", hpdf_ext_gstate_set_alpha_stroke, 1);
    rb_define_method(rb_cHPDFExtGState, "set_alpha_fill", hpdf_ext_gstate_set_alpha_fill, 1);
    rb_define_method(rb_cHPDFExtGState, "set_blend_mode", hpdf_ext_gstate_set_blend_mode, 1);
    rb_define_method(rb_cHPDFPage, "set_ext_gstate", hpdf_page_set_ext_gstate, 1);

    rb_eHPDFError = rb_define_class("HPDFError", rb_eStandardError);

    rb_define_const(rb_cHPDFDoc, "HPDF_TRUE", INT2FIX(HPDF_TRUE));
    rb_define_const(rb_cHPDFDoc, "HPDF_FALSE", INT2FIX(HPDF_FALSE));
    rb_define_const(rb_cHPDFDoc, "HPDF_COMP_NONE", INT2FIX(HPDF_COMP_NONE));
    rb_define_const(rb_cHPDFDoc, "HPDF_COMP_TEXT", INT2FIX(HPDF_COMP_TEXT));
    rb_define_const(rb_cHPDFDoc, "HPDF_COMP_IMAGE", INT2FIX(HPDF_COMP_IMAGE));
    rb_define_const(rb_cHPDFDoc, "HPDF_COMP_METADATA", INT2FIX(HPDF_COMP_METADATA));
    rb_define_const(rb_cHPDFDoc, "HPDF_COMP_ALL", INT2FIX(HPDF_COMP_ALL));
    rb_define_const(rb_cHPDFDoc, "HPDF_HIDE_TOOLBAR", INT2FIX(HPDF_HIDE_TOOLBAR));
    rb_define_const(rb_cHPDFDoc, "HPDF_HIDE_MENUBAR", INT2FIX(HPDF_HIDE_MENUBAR));
    rb_define_const(rb_cHPDFDoc, "HPDF_HIDE_WINDOW_UI", INT2FIX(HPDF_HIDE_WINDOW_UI));
    rb_define_const(rb_cHPDFDoc, "HPDF_FIT_WINDOW", INT2FIX(HPDF_FIT_WINDOW));
    rb_define_const(rb_cHPDFDoc, "HPDF_CENTER_WINDOW", INT2FIX(HPDF_CENTER_WINDOW));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENABLE_READ", INT2FIX(HPDF_ENABLE_READ));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENABLE_PRINT", INT2FIX(HPDF_ENABLE_PRINT));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENABLE_EDIT_ALL", INT2FIX(HPDF_ENABLE_EDIT_ALL));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENABLE_COPY", INT2FIX(HPDF_ENABLE_COPY));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENABLE_EDIT", INT2FIX(HPDF_ENABLE_EDIT));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_CREATION_DATE", INT2FIX(HPDF_INFO_CREATION_DATE));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_MOD_DATE", INT2FIX(HPDF_INFO_MOD_DATE));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_AUTHOR", INT2FIX(HPDF_INFO_AUTHOR));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_CREATOR", INT2FIX(HPDF_INFO_CREATOR));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_PRODUCER", INT2FIX(HPDF_INFO_PRODUCER));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_TITLE", INT2FIX(HPDF_INFO_TITLE));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_SUBJECT", INT2FIX(HPDF_INFO_SUBJECT));
    rb_define_const(rb_cHPDFDoc, "HPDF_INFO_KEYWORDS", INT2FIX(HPDF_INFO_KEYWORDS));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENCRYPT_R2", INT2FIX(HPDF_ENCRYPT_R2));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENCRYPT_R3", INT2FIX(HPDF_ENCRYPT_R3));
    rb_define_const(rb_cHPDFDoc, "HPDF_CS_DEVICE_GRAY", INT2FIX(HPDF_CS_DEVICE_GRAY));
    rb_define_const(rb_cHPDFDoc, "HPDF_CS_DEVICE_RGB", INT2FIX(HPDF_CS_DEVICE_RGB));
    rb_define_const(rb_cHPDFDoc, "HPDF_CS_DEVICE_CMYK", INT2FIX(HPDF_CS_DEVICE_CMYK));
    rb_define_const(rb_cHPDFDoc, "HPDF_BUTT_END", INT2FIX(HPDF_BUTT_END));
    rb_define_const(rb_cHPDFDoc, "HPDF_ROUND_END", INT2FIX(HPDF_ROUND_END));
    rb_define_const(rb_cHPDFDoc, "HPDF_PROJECTING_SCUARE_END", INT2FIX(HPDF_PROJECTING_SCUARE_END));
    rb_define_const(rb_cHPDFDoc, "HPDF_MITER_JOIN", INT2FIX(HPDF_MITER_JOIN));
    rb_define_const(rb_cHPDFDoc, "HPDF_ROUND_JOIN", INT2FIX(HPDF_ROUND_JOIN));
    rb_define_const(rb_cHPDFDoc, "HPDF_BEVEL_JOIN", INT2FIX(HPDF_BEVEL_JOIN));
    rb_define_const(rb_cHPDFDoc, "HPDF_FILL", INT2FIX(HPDF_FILL));
    rb_define_const(rb_cHPDFDoc, "HPDF_STROKE", INT2FIX(HPDF_STROKE));
    rb_define_const(rb_cHPDFDoc, "HPDF_FILL_THEN_STROKE", INT2FIX(HPDF_FILL_THEN_STROKE));
    rb_define_const(rb_cHPDFDoc, "HPDF_INVISIBLE", INT2FIX(HPDF_INVISIBLE));
    rb_define_const(rb_cHPDFDoc, "HPDF_FILL_CLIPPING", INT2FIX(HPDF_FILL_CLIPPING));
    rb_define_const(rb_cHPDFDoc, "HPDF_STROKE_CLIPPING", INT2FIX(HPDF_STROKE_CLIPPING));
    rb_define_const(rb_cHPDFDoc, "HPDF_FILL_STROKE_CLIPPING", INT2FIX(HPDF_FILL_STROKE_CLIPPING));
    rb_define_const(rb_cHPDFDoc, "HPDF_CLIPPING", INT2FIX(HPDF_CLIPPING));
    rb_define_const(rb_cHPDFDoc, "HPDF_WMODE_HORIZONTAL", INT2FIX(HPDF_WMODE_HORIZONTAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_WMODE_VERTICAL", INT2FIX(HPDF_WMODE_VERTICAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_LAYOUT_SINGLE", INT2FIX(HPDF_PAGE_LAYOUT_SINGLE));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_LAYOUT_ONE_COLUMN", INT2FIX(HPDF_PAGE_LAYOUT_ONE_COLUMN));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_LAYOUT_TWO_COLUMN_LEFT", INT2FIX(HPDF_PAGE_LAYOUT_TWO_COLUMN_LEFT));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_LAYOUT_TWO_COLUMN_RIGHT", INT2FIX(HPDF_PAGE_LAYOUT_TWO_COLUMN_RIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_MODE_USE_NONE", INT2FIX(HPDF_PAGE_MODE_USE_NONE));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_MODE_USE_OUTLINE", INT2FIX(HPDF_PAGE_MODE_USE_OUTLINE));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_MODE_USE_THUMBS", INT2FIX(HPDF_PAGE_MODE_USE_THUMBS));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_MODE_FULL_SCREEN", INT2FIX(HPDF_PAGE_MODE_FULL_SCREEN));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_NUM_STYLE_DECIMAL", INT2FIX(HPDF_PAGE_NUM_STYLE_DECIMAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_NUM_STYLE_UPPER_ROMAN", INT2FIX(HPDF_PAGE_NUM_STYLE_UPPER_ROMAN));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_NUM_STYLE_LOWER_ROMAN", INT2FIX(HPDF_PAGE_NUM_STYLE_LOWER_ROMAN));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_NUM_STYLE_UPPER_LETTERS", INT2FIX(HPDF_PAGE_NUM_STYLE_UPPER_LETTERS));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_NUM_STYLE_LOWER_LETTERS", INT2FIX(HPDF_PAGE_NUM_STYLE_LOWER_LETTERS));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_NO_HIGHTLIGHT", INT2FIX(HPDF_ANNOT_NO_HIGHTLIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_INVERT_BOX", INT2FIX(HPDF_ANNOT_INVERT_BOX));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_INVERT_BORDER", INT2FIX(HPDF_ANNOT_INVERT_BORDER));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_DOWN_APPEARANCE", INT2FIX(HPDF_ANNOT_DOWN_APPEARANCE));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_ICON_COMMENT", INT2FIX(HPDF_ANNOT_ICON_COMMENT));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_ICON_KEY", INT2FIX(HPDF_ANNOT_ICON_KEY));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_ICON_NOTE", INT2FIX(HPDF_ANNOT_ICON_NOTE));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_ICON_HELP", INT2FIX(HPDF_ANNOT_ICON_HELP));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_ICON_NEW_PARAGRAPH", INT2FIX(HPDF_ANNOT_ICON_NEW_PARAGRAPH));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_ICON_PARAGRAPH", INT2FIX(HPDF_ANNOT_ICON_PARAGRAPH));
    rb_define_const(rb_cHPDFDoc, "HPDF_ANNOT_ICON_INSERT", INT2FIX(HPDF_ANNOT_ICON_INSERT));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_LETTER", INT2FIX(HPDF_PAGE_SIZE_LETTER));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_LEGAL", INT2FIX(HPDF_PAGE_SIZE_LEGAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_A3", INT2FIX(HPDF_PAGE_SIZE_A3));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_A4", INT2FIX(HPDF_PAGE_SIZE_A4));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_A5", INT2FIX(HPDF_PAGE_SIZE_A5));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_B4", INT2FIX(HPDF_PAGE_SIZE_B4));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_B5", INT2FIX(HPDF_PAGE_SIZE_B5));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_EXECUTIVE", INT2FIX(HPDF_PAGE_SIZE_EXECUTIVE));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_US4x6", INT2FIX(HPDF_PAGE_SIZE_US4x6));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_US4x8", INT2FIX(HPDF_PAGE_SIZE_US4x8));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_US5x7", INT2FIX(HPDF_PAGE_SIZE_US5x7));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_SIZE_COMM10", INT2FIX(HPDF_PAGE_SIZE_COMM10));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_PORTRAIT", INT2FIX(HPDF_PAGE_PORTRAIT));
    rb_define_const(rb_cHPDFDoc, "HPDF_PAGE_LANDSCAPE", INT2FIX(HPDF_PAGE_LANDSCAPE));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENCODER_TYPE_SINGLE_BYTE", INT2FIX(HPDF_ENCODER_TYPE_SINGLE_BYTE));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENCODER_TYPE_DOUBLE_BYTE", INT2FIX(HPDF_ENCODER_TYPE_DOUBLE_BYTE));
    rb_define_const(rb_cHPDFDoc, "HPDF_ENCODER_TYPE_UNINITIALIZED", INT2FIX(HPDF_ENCODER_TYPE_UNINITIALIZED));
    rb_define_const(rb_cHPDFDoc, "HPDF_BYTE_TYPE_SINGLE", INT2FIX(HPDF_BYTE_TYPE_SINGLE));
    rb_define_const(rb_cHPDFDoc, "HPDF_BYTE_TYPE_LEAD", INT2FIX(HPDF_BYTE_TYPE_LEAD));
    rb_define_const(rb_cHPDFDoc, "HPDF_BYTE_TYPE_TRIAL", INT2FIX(HPDF_BYTE_TYPE_TRIAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_GMODE_PAGE_DESCRIPTION", INT2FIX(HPDF_GMODE_PAGE_DESCRIPTION));
    rb_define_const(rb_cHPDFDoc, "HPDF_GMODE_PATH_OBJECT", INT2FIX(HPDF_GMODE_PATH_OBJECT));
    rb_define_const(rb_cHPDFDoc, "HPDF_GMODE_TEXT_OBJECT", INT2FIX(HPDF_GMODE_TEXT_OBJECT));
    rb_define_const(rb_cHPDFDoc, "HPDF_GMODE_CLIPPING_PATH", INT2FIX(HPDF_GMODE_CLIPPING_PATH));
    rb_define_const(rb_cHPDFDoc, "HPDF_GMODE_SHADING", INT2FIX(HPDF_GMODE_SHADING));
    rb_define_const(rb_cHPDFDoc, "HPDF_GMODE_INLINE_IMAGE", INT2FIX(HPDF_GMODE_INLINE_IMAGE));
    rb_define_const(rb_cHPDFDoc, "HPDF_GMODE_EXTERNAL_OBJECT", INT2FIX(HPDF_GMODE_EXTERNAL_OBJECT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TALIGN_LEFT", INT2FIX(HPDF_TALIGN_LEFT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TALIGN_RIGHT", INT2FIX(HPDF_TALIGN_RIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TALIGN_CENTER", INT2FIX(HPDF_TALIGN_CENTER));
    rb_define_const(rb_cHPDFDoc, "HPDF_TALIGN_JUSTIFY", INT2FIX(HPDF_TALIGN_JUSTIFY));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_NORMAL", INT2FIX(HPDF_BM_NORMAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_MULTIPLY", INT2FIX(HPDF_BM_MULTIPLY));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_SCREEN", INT2FIX(HPDF_BM_SCREEN));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_OVERLAY", INT2FIX(HPDF_BM_OVERLAY));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_DARKEN", INT2FIX(HPDF_BM_DARKEN));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_LIGHTEN", INT2FIX(HPDF_BM_LIGHTEN));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_COLOR_DODGE", INT2FIX(HPDF_BM_COLOR_DODGE));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_COLOR_BUM", INT2FIX(HPDF_BM_COLOR_BUM));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_HARD_LIGHT", INT2FIX(HPDF_BM_HARD_LIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_SOFT_LIGHT", INT2FIX(HPDF_BM_SOFT_LIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_DIFFERENCE", INT2FIX(HPDF_BM_DIFFERENCE));
    rb_define_const(rb_cHPDFDoc, "HPDF_BM_EXCLUSHON", INT2FIX(HPDF_BM_EXCLUSHON));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_WIPE_RIGHT", INT2FIX(HPDF_TS_WIPE_RIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_WIPE_UP", INT2FIX(HPDF_TS_WIPE_UP));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_WIPE_LEFT", INT2FIX(HPDF_TS_WIPE_LEFT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_WIPE_DOWN", INT2FIX(HPDF_TS_WIPE_DOWN));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BARN_DOORS_HORIZONTAL_OUT", INT2FIX(HPDF_TS_BARN_DOORS_HORIZONTAL_OUT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BARN_DOORS_HORIZONTAL_IN", INT2FIX(HPDF_TS_BARN_DOORS_HORIZONTAL_IN));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BARN_DOORS_VERTICAL_OUT", INT2FIX(HPDF_TS_BARN_DOORS_VERTICAL_OUT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BARN_DOORS_VERTICAL_IN", INT2FIX(HPDF_TS_BARN_DOORS_VERTICAL_IN));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BOX_OUT", INT2FIX(HPDF_TS_BOX_OUT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BOX_IN", INT2FIX(HPDF_TS_BOX_IN));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BLINDS_HORIZONTAL", INT2FIX(HPDF_TS_BLINDS_HORIZONTAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_BLINDS_VERTICAL", INT2FIX(HPDF_TS_BLINDS_VERTICAL));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_DISSOLVE", INT2FIX(HPDF_TS_DISSOLVE));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_GLITTER_RIGHT", INT2FIX(HPDF_TS_GLITTER_RIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_GLITTER_DOWN", INT2FIX(HPDF_TS_GLITTER_DOWN));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT", INT2FIX(HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT));
    rb_define_const(rb_cHPDFDoc, "HPDF_TS_REPLACE", INT2FIX(HPDF_TS_REPLACE));
}

