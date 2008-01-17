{*
 * << Haru Free PDF Library 2.0.5 >> -- ExtGStateDemo.dpr
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided 'as is' without express or implied warranty.
 *
 *}
program LineDemo;

{$APPTYPE CONSOLE}

uses
  SysUtils, hpdf, hpdf_types, hpdf_consts;

procedure
error_handler (error_no: HPDF_STATUS; detail_no: HPDF_STATUS;
              user_data: Pointer); stdcall;
var
  message: string;
begin
  message := 'ERROR: ' + IntToStr(error_no) + '-' + IntToStr(detail_no);
  raise Exception.Create(message);
end;

procedure draw_circles (page: HPDF_Page; const description: PChar; x: 
            HPDF_REAL; y: HPDF_REAL);
begin
    HPDF_Page_SetLineWidth (page, 1.0);
    HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);
    HPDF_Page_SetRGBFill (page, 1.0, 0.0, 0.0);
    HPDF_Page_Circle (page,x +  40, y + 40, 40);
    HPDF_Page_FillStroke (page);
    HPDF_Page_SetRGBFill (page, 0.0, 1.0, 0.0);
    HPDF_Page_Circle (page, x + 100, y + 40, 40);
    HPDF_Page_FillStroke (page);
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 1.0);
    HPDF_Page_Circle (page, x + 70, y + 74.64, 40);
    HPDF_Page_FillStroke (page);

    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);
    HPDF_Page_BeginText (page);
    HPDF_Page_TextOut (page, x + 0.0, y + 130.0, description);
    HPDF_Page_EndText (page);
end;

procedure make_pdf ();
const
  fname: string = 'ExtGStateDemo.pdf';
  PAGE_WIDTH: HPDF_REAL = 600;
  PAGE_HEIGHT: HPDF_REAL = 900;
var
  pdf: HPDF_Doc;
  font: HPDF_Font;
  page: HPDF_Page;
  gstate: HPDF_ExtGState;
begin
  pdf := HPDF_New(@error_handler, nil);
  if pdf = nil then
  begin
    WriteLn('error: cannot create PdfDoc object\n');
    Halt (1);
  end;

  try
//    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    {* create default-font *}
    font := HPDF_GetFont (pdf, 'Helvetica-Bold', nil);

    {* add a new page object. *}
    page := HPDF_AddPage(pdf);
    HPDF_Page_SetFontAndSize (page, font, 10);

    HPDF_Page_SetHeight (page, PAGE_HEIGHT);
    HPDF_Page_SetWidth (page, PAGE_WIDTH);
    

    {* normal *}
    HPDF_Page_GSave (page);
    draw_circles (page, 'normal', 40.0, PAGE_HEIGHT - 170);
    HPDF_Page_GRestore (page);

    {* alpha fill *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetAlphaFill (gstate, 0.8);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'alpha fill = 0.8', 230.0, PAGE_HEIGHT - 170);
    HPDF_Page_GRestore (page);

    {* alpha stroke *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetAlphaFill (gstate, 0.4);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'alpha fill = 0.4', 420.0, PAGE_HEIGHT - 170);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_MULTIPLY *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_MULTIPLY);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_MULTIPLY', 40.0, PAGE_HEIGHT - 340);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_SCREEN *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_SCREEN);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_SCREEN', 230.0, PAGE_HEIGHT - 340);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_OVERLAY *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_OVERLAY);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_OVERLAY', 420.0, PAGE_HEIGHT - 340);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_DARKEN *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_DARKEN);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_DARKEN', 40.0, PAGE_HEIGHT - 510);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_LIGHTEN *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_LIGHTEN);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_LIGHTEN', 230.0, PAGE_HEIGHT - 510);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_COLOR_DODGE *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_COLOR_DODGE);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_COLOR_DODGE', 420.0, PAGE_HEIGHT - 510);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_COLOR_BUM *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_COLOR_BUM);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_COLOR_BUM', 40.0, PAGE_HEIGHT - 680);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_HARD_LIGHT *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_HARD_LIGHT);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_HARD_LIGHT', 230.0, PAGE_HEIGHT - 680);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_SOFT_LIGHT *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_SOFT_LIGHT);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_SOFT_LIGHT', 420.0, PAGE_HEIGHT - 680);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_DIFFERENCE *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_DIFFERENCE);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_DIFFERENCE', 40.0, PAGE_HEIGHT - 850);
    HPDF_Page_GRestore (page);

    {* blend-mode=HPDF_BM_EXCLUSHON *}
    HPDF_Page_GSave (page);
    gstate := HPDF_CreateExtGState (pdf);
    HPDF_ExtGState_SetBlendMode (gstate, HPDF_BM_EXCLUSHON);
    HPDF_Page_SetExtGState (page, gstate);
    draw_circles (page, 'HPDF_BM_EXCLUSHON', 230.0, PAGE_HEIGHT - 850);
    HPDF_Page_GRestore (page);

    {* save the document to a file *}
    HPDF_SaveToFile (pdf, PChar(fname));

  except
    on e: Exception do
    begin
      Writeln (e.message);
      HPDF_Free (pdf);
      Halt (1);
    end;
  end;

  {* clean up *}
  HPDF_Free (pdf);
end;

begin
  make_pdf;
end.

