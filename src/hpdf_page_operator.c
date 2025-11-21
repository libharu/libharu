/*
 * << Haru Free PDF Library >> -- hpdf_page_operator.c
 *
 * URL: http://libharu.org
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2007-2009 Antony Dovgal <tony@daylessday.org>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#include "hpdf_conf.h"
#include "hpdf_utils.h"
#include "hpdf_pages.h"
#include "hpdf_structure_element.h"
#include "hpdf_field.h"
#include "hpdf.h"

static const HPDF_Point INIT_POS = {0, 0};
static const HPDF_DashMode INIT_MODE = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0, 0.0f};


static HPDF_STATUS
InternalWriteText  (HPDF_PageAttr    attr,
                    const char      *text);

static HPDF_STATUS
InternalTextRect  (HPDF_Page            page,
                   HPDF_REAL            left,
                   HPDF_REAL            top,
                   HPDF_REAL            right,
                   HPDF_REAL            bottom,
                   const char          *text,
                   HPDF_TextAlignment   align,
                   HPDF_UINT           *len,
                   HPDF_BOOL            force);

static HPDF_STATUS
InternalArc  (HPDF_Page    page,
              HPDF_REAL    x,
              HPDF_REAL    y,
              HPDF_REAL    ray,
              HPDF_REAL    ang1,
              HPDF_REAL    ang2,
              HPDF_BOOL    cont_flg);


static HPDF_STATUS
InternalShowTextNextLine  (HPDF_Page    page,
                           const char  *text,
                           HPDF_UINT    len);

static HPDF_STATUS
InternalBeginMarkedContentSequence  (HPDF_Page   page,
                                     const char *tag,
                                     HPDF_Dict   props);

static HPDF_UINT
InternalOperatorStackSize  (HPDF_Page page);

static char*
InternalWriteColorToBuf  (char       *pbuf,
                          char       *eptr,
                          HPDF_Color  color,
                          HPDF_BOOL   fill);

static HPDF_Array
InternalAnnotationMatrix  (HPDF_MMgr mmgr,
                           HPDF_REAL width,
                           HPDF_REAL height,
                           HPDF_REAL rotation);

/*--- General graphics state ---------------------------------------------*/

/* w */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetLineWidth  (HPDF_Page  page,
                         HPDF_REAL  line_width)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetLineWidth\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (line_width < 0)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, line_width) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " w\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->line_width = line_width;

    return ret;
}

/* J */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetLineCap  (HPDF_Page     page,
                       HPDF_LineCap  line_cap)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetLineCap\n"));

    if (ret != HPDF_OK)
        return ret;

    if (line_cap >= HPDF_LINECAP_EOF)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE,
                (HPDF_STATUS)line_cap);

    attr = (HPDF_PageAttr)page->attr;

    if ((ret = HPDF_Stream_WriteInt (attr->stream,
                (HPDF_UINT)line_cap)) != HPDF_OK)
        return ret;

    if ((ret = HPDF_Stream_WriteStr (attr->stream,
                " J\012")) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->line_cap = line_cap;

    return ret;
}

/* j */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetLineJoin  (HPDF_Page      page,
                        HPDF_LineJoin  line_join)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetLineJoin\n"));

    if (ret != HPDF_OK)
        return ret;

    if (line_join >= HPDF_LINEJOIN_EOF)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE,
                (HPDF_STATUS)line_join);

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteInt (attr->stream, (HPDF_UINT)line_join) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " j\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->line_join = line_join;

    return ret;
}

/* M */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetMiterLimit  (HPDF_Page  page,
                          HPDF_REAL  miter_limit)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetMitterLimit\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (miter_limit < 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, miter_limit) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " M\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->miter_limit = miter_limit;

    return ret;
}

/* d */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetDash  (HPDF_Page           page,
                    const HPDF_REAL    *dash_ptn,
                    HPDF_UINT           num_param,
                    HPDF_REAL           phase)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    const HPDF_REAL *pdash_ptn = dash_ptn;
    HPDF_PageAttr attr;
    HPDF_UINT i;

    HPDF_PTRACE ((" HPDF_Page_SetDash\n"));

    if (ret != HPDF_OK)
        return ret;

    if (num_param == 0 && phase > 0)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE,
                phase);

    if (!dash_ptn && num_param > 0)
        return HPDF_RaiseError (page->error, HPDF_INVALID_PARAMETER,
                phase);

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);
    *pbuf++ = '[';

    for (i = 0; i < num_param; i++) {
        if (*pdash_ptn == 0 || *pdash_ptn > HPDF_MAX_DASH_PATTERN)
            return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

        pbuf = HPDF_FToA (pbuf, *pdash_ptn, eptr);
        *pbuf++ = ' ';
        pdash_ptn++;
    }

    *pbuf++ = ']';
    *pbuf++ = ' ';

    pbuf = HPDF_FToA (pbuf, phase, eptr);
    HPDF_StrCpy (pbuf, " d\012", eptr);

    attr = (HPDF_PageAttr)page->attr;

    if ((ret = HPDF_Stream_WriteStr (attr->stream, buf)) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->dash_mode = INIT_MODE;
    attr->gstate->dash_mode.num_ptn = num_param;
    attr->gstate->dash_mode.phase = phase;

    pdash_ptn = dash_ptn;
    for (i = 0; i < num_param; i++) {
        attr->gstate->dash_mode.ptn[i] = *pdash_ptn;
        pdash_ptn++;
    }

    return ret;
}


/* ri --not implemented yet */

/* i */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetFlat  (HPDF_Page  page,
                    HPDF_REAL  flatness)
{
    HPDF_PageAttr attr;
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);

    HPDF_PTRACE ((" HPDF_Page_SetFlat\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (flatness > 100 || flatness < 0)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, flatness) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " i\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->flatness = flatness;

    return ret;
}

/* gs */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetExtGState  (HPDF_Page        page,
                         HPDF_ExtGState   ext_gstate)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION);
    HPDF_PageAttr attr;
    const char *local_name;

    HPDF_PTRACE ((" HPDF_Page_SetExtGState\n"));

    if (ret != HPDF_OK)
        return ret;

    if (!HPDF_ExtGState_Validate (ext_gstate))
        return HPDF_RaiseError (page->error, HPDF_INVALID_OBJECT, 0);

    if (page->mmgr != ext_gstate->mmgr)
        return HPDF_RaiseError (page->error, HPDF_INVALID_EXT_GSTATE, 0);

    attr = (HPDF_PageAttr)page->attr;
    local_name = HPDF_Page_GetExtGStateName (page, ext_gstate);

    if (!local_name)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteEscapeName (attr->stream, local_name) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " gs\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    /* change objct class to read only. */
    ext_gstate->header.obj_class = (HPDF_OSUBCLASS_EXT_GSTATE_R | HPDF_OCLASS_DICT);

    return ret;
}


/*--- Special graphic state operator --------------------------------------*/

/* q */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_GSave  (HPDF_Page  page)
{
    HPDF_GState new_gstate;
    HPDF_PageAttr attr;
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION);

    HPDF_PTRACE ((" HPDF_Page_GSave\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    new_gstate = HPDF_GState_New (page->mmgr, attr->gstate);
    if (!new_gstate)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, "q\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate = new_gstate;

    return ret;
}

/* Q */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_GRestore  (HPDF_Page  page)
{
    HPDF_GState new_gstate;
    HPDF_PageAttr attr;
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION);

    HPDF_PTRACE ((" HPDF_Page_GRestore\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (!attr->gstate->prev)
        return HPDF_RaiseError (page->error, HPDF_PAGE_CANNOT_RESTORE_GSTATE,
                0);

    new_gstate = HPDF_GState_Free (page->mmgr, attr->gstate);

    attr->gstate = new_gstate;

    if (HPDF_Stream_WriteStr (attr->stream, "Q\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    return ret;
}

/* cm */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Concat  (HPDF_Page         page,
                   HPDF_REAL         a,
                   HPDF_REAL         b,
                   HPDF_REAL         c,
                   HPDF_REAL         d,
                   HPDF_REAL         x,
                   HPDF_REAL         y)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;
    HPDF_TransMatrix tm;

    HPDF_PTRACE ((" HPDF_Page_Concat\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, a, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, b, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, d, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    HPDF_StrCpy (pbuf, " cm\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    tm = attr->gstate->trans_matrix;

    attr->gstate->trans_matrix.a = tm.a * a + tm.b * c;
    attr->gstate->trans_matrix.b = tm.a * b + tm.b * d;
    attr->gstate->trans_matrix.c = tm.c * a + tm.d * c;
    attr->gstate->trans_matrix.d = tm.c * b + tm.d * d;
    attr->gstate->trans_matrix.x = tm.x + x * tm.a + y * tm.c;
    attr->gstate->trans_matrix.y = tm.y + x * tm.b + y * tm.d;

    return ret;
}

/*--- Path construction operator ------------------------------------------*/

/* m */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveTo  (HPDF_Page  page,
                   HPDF_REAL  x,
                   HPDF_REAL  y)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_MoveTo\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    HPDF_StrCpy (pbuf, " m\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x;
    attr->cur_pos.y = y;
    attr->str_pos = attr->cur_pos;
    attr->gmode = HPDF_GMODE_PATH_OBJECT;

    return ret;
}

/* l */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_LineTo  (HPDF_Page  page,
                   HPDF_REAL  x,
                   HPDF_REAL  y)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_LineTo\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    HPDF_StrCpy (pbuf, " l\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x;
    attr->cur_pos.y = y;

    return ret;
}

/* c */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_CurveTo  (HPDF_Page  page,
                    HPDF_REAL  x1,
                    HPDF_REAL  y1,
                    HPDF_REAL  x2,
                    HPDF_REAL  y2,
                    HPDF_REAL  x3,
                    HPDF_REAL  y3)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_CurveTo\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x1, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y1, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x2, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y2, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x3, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y3, eptr);
    HPDF_StrCpy (pbuf, " c\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x3;
    attr->cur_pos.y = y3;

    return ret;
}

/* v */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_CurveTo2  (HPDF_Page  page,
                     HPDF_REAL  x2,
                     HPDF_REAL  y2,
                     HPDF_REAL  x3,
                     HPDF_REAL  y3)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_CurveTo2\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x2, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y2, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x3, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y3, eptr);
    HPDF_StrCpy (pbuf, " v\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x3;
    attr->cur_pos.y = y3;

    return ret;
}

/* y */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_CurveTo3  (HPDF_Page  page,
                     HPDF_REAL  x1,
                     HPDF_REAL  y1,
                     HPDF_REAL  x3,
                     HPDF_REAL  y3)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_CurveTo3\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x1, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y1, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x3, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y3, eptr);
    HPDF_StrCpy (pbuf, " y\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x3;
    attr->cur_pos.y = y3;

    return ret;
}

/* h */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePath  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_ClosePath\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "h\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos = attr->str_pos;

    return ret;
}

/* re */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Rectangle  (HPDF_Page  page,
                      HPDF_REAL  x,
                      HPDF_REAL  y,
                      HPDF_REAL  width,
                      HPDF_REAL  height)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Rectangle\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, width, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, height, eptr);
    HPDF_StrCpy (pbuf, " re\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x;
    attr->cur_pos.y = y;
    attr->str_pos = attr->cur_pos;
    attr->gmode = HPDF_GMODE_PATH_OBJECT;

    return ret;
}


/*--- Path painting operator ---------------------------------------------*/

/* S */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Stroke  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
        HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Stroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "S\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* s */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePathStroke  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_ClosePathStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "s\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* f */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Fill  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Fill\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "f\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* f* */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Eofill  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Eofill\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "f*\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* B */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_FillStroke  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_FillStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "B\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* B* */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_EofillStroke  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_EofillStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "B*\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;

    return ret;
}

/* b */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePathFillStroke  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_ClosePathFillStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "b\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* b* */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePathEofillStroke  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_ClosePathEofillStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "b*\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* n */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_EndPath  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_PageEndPath\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "n\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}


/*--- Clipping paths operator --------------------------------------------*/

/* W */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Clip  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Clip\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "W\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_CLIPPING_PATH;

    return ret;
}

/* W* */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Eoclip  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Eoclip\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "W*\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_CLIPPING_PATH;

    return ret;
}


/*--- Text object operator -----------------------------------------------*/

/* BT */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_BeginText  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION);
    HPDF_PageAttr attr;
    const HPDF_TransMatrix INIT_MATRIX = {1, 0, 0, 1, 0, 0};

    HPDF_PTRACE ((" HPDF_Page_BeginText\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "BT\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_TEXT_OBJECT;
    attr->text_pos = INIT_POS;
    attr->text_matrix = INIT_MATRIX;
    attr->text_stack = InternalOperatorStackSize (page) + 1;

    return ret;
}

/* ET */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_EndText  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_EndText\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (attr->text_stack <= attr->marked_content_stack)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_OPERATOR_STACK, 0);

    if (HPDF_Stream_WriteStr (attr->stream, "ET\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->text_pos = INIT_POS;
    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->text_stack = 0;

    return ret;
}

/*--- Text state ---------------------------------------------------------*/

/* Tc */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetCharSpace  (HPDF_Page  page,
                         HPDF_REAL  value)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetCharSpace\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (value < HPDF_MIN_CHARSPACE || value > HPDF_MAX_CHARSPACE)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, value) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Tc\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->char_space = value;

    return ret;
}

/* Tw */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetWordSpace  (HPDF_Page  page,
                         HPDF_REAL  value)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetWordSpace\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (value < HPDF_MIN_WORDSPACE || value > HPDF_MAX_WORDSPACE)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, value) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Tw\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->word_space = value;

    return ret;
}

/* Tz */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetHorizontalScalling  (HPDF_Page  page,
                                  HPDF_REAL  value)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetHorizontalScalling\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (value < HPDF_MIN_HORIZONTALSCALING ||
            value > HPDF_MAX_HORIZONTALSCALING)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, value) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Tz\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->h_scalling = value;

    return ret;
}

/* TL */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextLeading  (HPDF_Page  page,
                           HPDF_REAL  value)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetTextLeading\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteReal (attr->stream, value) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " TL\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->text_leading = value;

    return ret;
}

/* Tf */

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetFontAndSize  (HPDF_Page  page,
                           HPDF_Font  font,
                           HPDF_REAL  size)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    const char *local_name;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetFontAndSize\n"));

    if (ret != HPDF_OK)
        return ret;

    if (!HPDF_Font_Validate (font))
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);

    if (size <= 0 || size > HPDF_MAX_FONTSIZE)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT_SIZE, size);

    if (page->mmgr != font->mmgr)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);

    attr = (HPDF_PageAttr)page->attr;
    local_name = HPDF_Page_GetLocalFontName (page, font);

    if (!local_name)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);

    if (HPDF_Stream_WriteEscapeName (attr->stream, local_name) != HPDF_OK)
        return HPDF_CheckError (page->error);

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, size, eptr);
    HPDF_StrCpy (pbuf, " Tf\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->font = font;
    attr->gstate->font_size = size;
    attr->gstate->writing_mode = ((HPDF_FontAttr)font->attr)->writing_mode;

    return ret;
}

/* Tr */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextRenderingMode  (HPDF_Page               page,
                                 HPDF_TextRenderingMode  mode)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetTextRenderingMode\n"));

    if (ret != HPDF_OK)
        return ret;

    if (mode >= HPDF_RENDERING_MODE_EOF)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE,
                (HPDF_STATUS)mode);

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteInt (attr->stream, (HPDF_INT)mode) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Tr\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->rendering_mode = mode;

    return ret;
}

/* Ts */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextRaise  (HPDF_Page  page,
                         HPDF_REAL  value)
{
    return HPDF_Page_SetTextRise (page, value);
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextRise  (HPDF_Page  page,
                        HPDF_REAL  value)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetTextRaise\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteReal (attr->stream, value) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Ts\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->text_rise = value;

    return ret;
}

/*--- Text positioning ---------------------------------------------------*/

/* Td */

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveTextPos  (HPDF_Page  page,
                        HPDF_REAL  x,
                        HPDF_REAL  y)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_MoveTextPos\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA2 (pbuf, x, eptr, attr->text_placement_accuracy);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA2 (pbuf, y, eptr, attr->text_placement_accuracy);
    HPDF_StrCpy (pbuf, " Td\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    float round = HPDF_DECIMAL_ROUND_COEFFICIENT[attr->text_placement_accuracy];
    x = roundf(x * round) / round;
    y = roundf(y * round) / round;

    attr->text_matrix.x += x * attr->text_matrix.a + y * attr->text_matrix.c;
    attr->text_matrix.y += y * attr->text_matrix.d + x * attr->text_matrix.b;
    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    return ret;
}

/* TD */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveTextPos2  (HPDF_Page  page,
                         HPDF_REAL  x,
                         HPDF_REAL  y)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_MoveTextPos2\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA2 (pbuf, x, eptr, attr->text_placement_accuracy);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA2 (pbuf, y, eptr, attr->text_placement_accuracy);
    HPDF_StrCpy (pbuf, " TD\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    float round = HPDF_DECIMAL_ROUND_COEFFICIENT[attr->text_placement_accuracy];
    x = roundf(x * round) / round;
    y = roundf(y * round) / round;

    attr->text_matrix.x += x * attr->text_matrix.a + y * attr->text_matrix.c;
    attr->text_matrix.y += y * attr->text_matrix.d + x * attr->text_matrix.b;
    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;
    attr->gstate->text_leading = -y;

    return ret;
}

/* Tm */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextMatrix  (HPDF_Page         page,
                          HPDF_REAL    a,
                          HPDF_REAL    b,
                          HPDF_REAL    c,
                          HPDF_REAL    d,
                          HPDF_REAL    x,
                          HPDF_REAL    y)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetTextMatrix\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if ((a == 0 || d == 0) && (b == 0 || c == 0))
        return HPDF_RaiseError (page->error, HPDF_INVALID_PARAMETER, 0);

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, a, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, b, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, d, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    HPDF_StrCpy (pbuf, " Tm\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->text_matrix.a = a;
    attr->text_matrix.b = b;
    attr->text_matrix.c = c;
    attr->text_matrix.d = d;
    attr->text_matrix.x = x;
    attr->text_matrix.y = y;
    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    return ret;
}


/* T* */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveToNextLine  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_MoveToNextLine\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "T*\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    /* calculate the reference point of text */
    attr->text_matrix.x -= attr->gstate->text_leading * attr->text_matrix.c;
    attr->text_matrix.y -= attr->gstate->text_leading * attr->text_matrix.d;

    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    return ret;
}

/*--- Text showing -------------------------------------------------------*/

/* Tj */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ShowText  (HPDF_Page    page,
                     const char  *text)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;
    HPDF_REAL tw;

    HPDF_PTRACE ((" HPDF_Page_ShowText\n"));

    if (ret != HPDF_OK || text == NULL || text[0] == 0)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font)
        return HPDF_RaiseError (page->error, HPDF_PAGE_FONT_NOT_FOUND, 0);

    tw = HPDF_Page_TextWidth (page, text);

    if (InternalWriteText (attr, text) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Tj\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    /* calculate the reference point of text */
    if (attr->gstate->writing_mode == HPDF_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}

/* TJ */
/* ' */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ShowTextNextLine  (HPDF_Page    page,
                             const char  *text)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;
    HPDF_REAL tw;

    HPDF_PTRACE ((" HPDF_Page_ShowTextNextLine\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font)
        return HPDF_RaiseError (page->error, HPDF_PAGE_FONT_NOT_FOUND, 0);

    if (text == NULL || text[0] == 0)
        return HPDF_Page_MoveToNextLine(page);

    if (InternalWriteText (attr, text) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " \'\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    tw = HPDF_Page_TextWidth (page, text);

    /* calculate the reference point of text */
    attr->text_matrix.x -= attr->gstate->text_leading * attr->text_matrix.c;
    attr->text_matrix.y -= attr->gstate->text_leading * attr->text_matrix.d;

    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    if (attr->gstate->writing_mode == HPDF_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}

/* " */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ShowTextNextLineEx  (HPDF_Page    page,
                               HPDF_REAL    word_space,
                               HPDF_REAL    char_space,
                               const char  *text)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;
    HPDF_REAL tw;
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;

    HPDF_PTRACE ((" HPDF_Page_ShowTextNextLineEX\n"));

    if (ret != HPDF_OK)
        return ret;

    if (word_space < HPDF_MIN_WORDSPACE || word_space > HPDF_MAX_WORDSPACE)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (char_space < HPDF_MIN_CHARSPACE || char_space > HPDF_MAX_CHARSPACE)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    attr = (HPDF_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font)
        return HPDF_RaiseError (page->error, HPDF_PAGE_FONT_NOT_FOUND, 0);

    if (text == NULL || text[0] == 0)
        return HPDF_Page_MoveToNextLine(page);

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);
    pbuf = HPDF_FToA (pbuf, word_space, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, char_space, eptr);
    *pbuf = ' ';

    if (InternalWriteText (attr, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (InternalWriteText (attr, text) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " \"\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->word_space = word_space;
    attr->gstate->char_space = char_space;

    tw = HPDF_Page_TextWidth (page, text);

    /* calculate the reference point of text */
    attr->text_matrix.x += attr->gstate->text_leading * attr->text_matrix.b;
    attr->text_matrix.y -= attr->gstate->text_leading * attr->text_matrix.a;

    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    if (attr->gstate->writing_mode == HPDF_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}


/*--- Color showing ------------------------------------------------------*/

/* cs --not implemented yet */
/* CS --not implemented yet */
/* sc --not implemented yet */
/* scn --not implemented yet */
/* SC --not implemented yet */
/* SCN --not implemented yet */

/* g */

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetGrayFill  (HPDF_Page  page,
                        HPDF_REAL  gray)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetGrayFill\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (gray < 0 || gray > 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, gray) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " g\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->gray_fill = gray;
    attr->gstate->cs_fill = HPDF_CS_DEVICE_GRAY;

    return ret;
}

/* G */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetGrayStroke  (HPDF_Page  page,
                          HPDF_REAL  gray)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetGrayStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (gray < 0 || gray > 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (HPDF_Stream_WriteReal (attr->stream, gray) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " G\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->gray_stroke = gray;
    attr->gstate->cs_stroke = HPDF_CS_DEVICE_GRAY;

    return ret;
}

/* rg */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetRGBFill  (HPDF_Page  page,
                       HPDF_REAL  r,
                       HPDF_REAL  g,
                       HPDF_REAL  b)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT |
                    HPDF_GMODE_PAGE_DESCRIPTION);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetRGBFill\n"));

    if (ret != HPDF_OK)
        return ret;

    if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, r, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, g, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, b, eptr);
    HPDF_StrCpy (pbuf, " rg\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->rgb_fill.r = r;
    attr->gstate->rgb_fill.g = g;
    attr->gstate->rgb_fill.b = b;
    attr->gstate->cs_fill = HPDF_CS_DEVICE_RGB;

    return ret;
}

/* RG */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetRGBStroke  (HPDF_Page  page,
                         HPDF_REAL  r,
                         HPDF_REAL  g,
                         HPDF_REAL  b)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT |
                    HPDF_GMODE_PAGE_DESCRIPTION);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetRGBStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, r, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, g, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, b, eptr);
    HPDF_StrCpy (pbuf, " RG\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->rgb_stroke.r = r;
    attr->gstate->rgb_stroke.g = g;
    attr->gstate->rgb_stroke.b = b;
    attr->gstate->cs_stroke = HPDF_CS_DEVICE_RGB;

    return ret;
}

/* k */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetCMYKFill  (HPDF_Page  page,
                        HPDF_REAL  c,
                        HPDF_REAL  m,
                        HPDF_REAL  y,
                        HPDF_REAL  k)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT |
                    HPDF_GMODE_PAGE_DESCRIPTION);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetCMYKFill\n"));

    if (ret != HPDF_OK)
        return ret;

    if (c < 0 || c > 1 || m < 0 || m > 1 || y < 0 || y > 1 || k < 0 || k > 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, m, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, k, eptr);
    HPDF_StrCpy (pbuf, " k\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->cmyk_fill.c = c;
    attr->gstate->cmyk_fill.m = m;
    attr->gstate->cmyk_fill.y = y;
    attr->gstate->cmyk_fill.k = k;
    attr->gstate->cs_fill = HPDF_CS_DEVICE_CMYK;

    return ret;
}

/* K */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetCMYKStroke  (HPDF_Page  page,
                          HPDF_REAL  c,
                          HPDF_REAL  m,
                          HPDF_REAL  y,
                          HPDF_REAL  k)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT |
                    HPDF_GMODE_PAGE_DESCRIPTION);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetCMYKStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    if (c < 0 || c > 1 || m < 0 || m > 1 || y < 0 || y > 1 || k < 0 || k > 1)
        return HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, m, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, k, eptr);
    HPDF_StrCpy (pbuf, " K\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->cmyk_stroke.c = c;
    attr->gstate->cmyk_stroke.m = m;
    attr->gstate->cmyk_stroke.y = y;
    attr->gstate->cmyk_stroke.k = k;
    attr->gstate->cs_stroke = HPDF_CS_DEVICE_CMYK;

    return ret;
}

/*--- Shading patterns ---------------------------------------------------*/

/* sh --not implemented yet */

/*--- In-line images -----------------------------------------------------*/

/* BI --not implemented yet */
/* ID --not implemented yet */
/* EI --not implemented yet */

/*--- XObjects -----------------------------------------------------------*/

/* Do */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ExecuteXObject  (HPDF_Page     page,
                           HPDF_XObject  obj)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION);
    HPDF_PageAttr attr;
    const char *local_name;

    HPDF_PTRACE ((" HPDF_Page_ExecuteXObject\n"));

    if (ret != HPDF_OK)
        return ret;

    if (!obj || obj->header.obj_class != (HPDF_OSUBCLASS_XOBJECT |
            HPDF_OCLASS_DICT))
        return HPDF_RaiseError (page->error, HPDF_INVALID_OBJECT, 0);

    if (page->mmgr != obj->mmgr)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_XOBJECT, 0);

    attr = (HPDF_PageAttr)page->attr;
    local_name = HPDF_Page_GetXObjectName (page, obj);

    if (!local_name)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_XOBJECT, 0);

    if (HPDF_Stream_WriteEscapeName (attr->stream, local_name) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (HPDF_Stream_WriteStr (attr->stream, " Do\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    return ret;
}

/*--- Marked content -----------------------------------------------------*/

/* BMC --not implemented yet */
/* BDC --not implemented yet */
/* EMC --not implemented yet */
/* MP --not implemented yet */
/* DP --not implemented yet */

/* BDC */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_BeginStructureElementReference  (HPDF_Page             page,
                                           HPDF_StructureElement structure_element)
{
    HPDF_PageAttr attr;
    HPDF_Name structure_type;
    HPDF_STATUS ret;

    HPDF_PTRACE ((" HPDF_Page_BeginReferenceToStructureElement\n"));

    attr = (HPDF_PageAttr)page->attr;

    structure_type = (HPDF_Name)HPDF_Dict_GetItem (structure_element, "S", HPDF_OCLASS_NAME);
    if (!structure_type)
        return HPDF_RaiseError (page->error, HPDF_INVALID_OBJECT, 0);

    HPDF_UINT marked_content_id = attr->marked_content_id;
    attr->marked_content_id++;

    HPDF_Dict props = HPDF_Dict_New (page->mmgr);
    if (!props)
        return HPDF_Error_GetCode (page->error);

    ret = HPDF_Dict_AddNumber (props, "MCID", marked_content_id);
    if (ret != HPDF_OK) {
        HPDF_Dict_Free (props);
        return ret;
    }

    // output begin of marked content sequence e.g. /Document << MCID 0 >> BDC
    ret = InternalBeginMarkedContentSequence (page, HPDF_Name_GetValue (structure_type), props);
    HPDF_Dict_Free (props);
    if (ret != HPDF_OK)
        return ret;

    ret = HPDF_StructureElement_AddMarkedContentSequence (structure_element, marked_content_id, page);
    if (ret != HPDF_OK)
        return ret;

    // handle parent tree
    HPDF_Array parent_tree_entry = attr->parent_tree_entry;
    if (!parent_tree_entry) {
        parent_tree_entry = HPDF_Array_New (page->mmgr);
        if (!parent_tree_entry)
            return HPDF_Error_GetCode (page->error);

        HPDF_StructureElementAttr se_attr = (HPDF_StructureElementAttr)structure_element->attr;
        HPDF_UINT32 parent_tree_key = HPDF_StructTreeRoot_AddParentTreeEntry (se_attr->struct_tree_root, parent_tree_entry);
        if (!parent_tree_key)
            return HPDF_Error_GetCode (page->error);

        ret = HPDF_Dict_AddNumber (page, "StructParents", parent_tree_key);
        if (ret != HPDF_OK)
            return ret;

        attr->parent_tree_entry = parent_tree_entry;
    }

    ret = HPDF_Array_Add (parent_tree_entry, structure_element);
    if (ret != HPDF_OK)
        return ret;

    return HPDF_OK;
}

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_BeginArtifact  (HPDF_Page     page,
                          HPDF_Artifact artifact)
{
    return InternalBeginMarkedContentSequence (page, "Artifact", artifact);
}

/* BMC / BDC */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_BeginMarkedContentSequence  (HPDF_Page          page,
                                       HPDF_MarkedContent marked_content)
{
    HPDF_MarkedContentAttr attr = (HPDF_MarkedContentAttr)marked_content->attr;

    return InternalBeginMarkedContentSequence (page, attr->tag, marked_content);
}

HPDF_STATUS
InternalBeginMarkedContentSequence  (HPDF_Page   page,
                                     const char *tag,
                                     HPDF_Dict   props)
{
    HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteEscapeName (attr->stream, tag) != HPDF_OK)
        return HPDF_CheckError (page->error);

    if (props != NULL) {
        if (HPDF_Dict_Write (props, attr->stream, NULL) != HPDF_OK)
            return HPDF_CheckError (page->error);

        if (HPDF_Stream_WriteStr (attr->stream, " BDC\012") != HPDF_OK)
            return HPDF_CheckError (page->error);
    } else {
        if (HPDF_Stream_WriteStr (attr->stream, " BMC\012") != HPDF_OK)
            return HPDF_CheckError (page->error);
    }

    attr->marked_content_stack = InternalOperatorStackSize (page) + 1;

    return HPDF_OK;
}

/* EMC */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_EndMarkedContentSequence (HPDF_Page page)
{
    HPDF_PTRACE ((" HPDF_Page_EndStructureElementReference\n"));

    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION | HPDF_GMODE_TEXT_OBJECT);
    if (ret != HPDF_OK)
        return ret;

    HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;
    if (attr->marked_content_stack <= attr->text_stack)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_OPERATOR_STACK, 0);

    if (HPDF_Stream_WriteStr (attr->stream, "EMC\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->marked_content_stack--;
    if (attr->marked_content_stack != 0 && attr->marked_content_stack == attr->text_stack)
        attr->marked_content_stack--;

    return HPDF_OK;
}

static HPDF_UINT
InternalOperatorStackSize  (HPDF_Page page)
{
    HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;
    if (attr->marked_content_stack > attr->text_stack) {
        return attr->marked_content_stack;
    } else {
        return attr->text_stack;
    }
}

/*--- Compatibility ------------------------------------------------------*/

/* BX --not implemented yet */
/* EX --not implemented yet */


/*--- combined function --------------------------------------------------*/

static const HPDF_REAL KAPPA = 0.552F;

static char*
QuarterCircleA  (char   *pbuf,
                 char   *eptr,
                 HPDF_REAL    x,
                 HPDF_REAL    y,
                 HPDF_REAL    ray)
{
    pbuf = HPDF_FToA (pbuf, x -ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x -ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + ray, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

static char*
QuarterCircleB  (char   *pbuf,
                 char   *eptr,
                 HPDF_REAL    x,
                 HPDF_REAL    y,
                 HPDF_REAL    ray)
{
    pbuf = HPDF_FToA (pbuf, x + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x + ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x + ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

static char*
QuarterCircleC  (char   *pbuf,
                 char   *eptr,
                 HPDF_REAL    x,
                 HPDF_REAL    y,
                 HPDF_REAL    ray)
{
    pbuf = HPDF_FToA (pbuf, x + ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

static char*
QuarterCircleD  (char   *pbuf,
                 char   *eptr,
                 HPDF_REAL    x,
                 HPDF_REAL    y,
                 HPDF_REAL    ray)
{
    pbuf = HPDF_FToA (pbuf, x - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x - ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x - ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Circle  (HPDF_Page     page,
                   HPDF_REAL     x,
                   HPDF_REAL     y,
                   HPDF_REAL     ray)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
            HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ * 2];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Circle\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x - ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " m\012", eptr);

    pbuf = QuarterCircleA (pbuf, eptr, x, y, ray);
    pbuf = QuarterCircleB (pbuf, eptr, x, y, ray);
    pbuf = QuarterCircleC (pbuf, eptr, x, y, ray);
    QuarterCircleD (pbuf, eptr, x, y, ray);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x - ray;
    attr->cur_pos.y = y;
    attr->str_pos = attr->cur_pos;
    attr->gmode = HPDF_GMODE_PATH_OBJECT;

    return ret;
}


static char*
QuarterEllipseA  (char      *pbuf,
                  char      *eptr,
                  HPDF_REAL  x,
                  HPDF_REAL  y,
                  HPDF_REAL  xray,
                  HPDF_REAL  yray)
{
    pbuf = HPDF_FToA (pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x -xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + yray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + yray, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

static char*
QuarterEllipseB  (char      *pbuf,
                  char      *eptr,
                  HPDF_REAL  x,
                  HPDF_REAL  y,
                  HPDF_REAL  xray,
                  HPDF_REAL  yray)
{
    pbuf = HPDF_FToA (pbuf, x + xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + yray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x + xray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y + yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x + xray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

static char*
QuarterEllipseC  (char      *pbuf,
                  char      *eptr,
                  HPDF_REAL  x,
                  HPDF_REAL  y,
                  HPDF_REAL  xray,
                  HPDF_REAL  yray)
{
    pbuf = HPDF_FToA (pbuf, x + xray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x + xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - yray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - yray, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

static char*
QuarterEllipseD  (char      *pbuf,
                  char      *eptr,
                  HPDF_REAL  x,
                  HPDF_REAL  y,
                  HPDF_REAL  xray,
                  HPDF_REAL  yray)
{
    pbuf = HPDF_FToA (pbuf, x - xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - yray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Ellipse  (HPDF_Page   page,
                    HPDF_REAL   x,
                    HPDF_REAL   y,
                    HPDF_REAL  xray,
                    HPDF_REAL  yray)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
            HPDF_GMODE_PATH_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_Ellipse\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " m\012", eptr);

    pbuf = QuarterEllipseA (pbuf, eptr, x, y, xray, yray);
    pbuf = QuarterEllipseB (pbuf, eptr, x, y, xray, yray);
    pbuf = QuarterEllipseC (pbuf, eptr, x, y, xray, yray);
    QuarterEllipseD (pbuf, eptr, x, y, xray, yray);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = x - xray;
    attr->cur_pos.y = y;
    attr->str_pos = attr->cur_pos;
    attr->gmode = HPDF_GMODE_PATH_OBJECT;

    return ret;
}


/*
 * this function is based on the code which is contributed by Riccardo Cohen.
 *
 * from http://www.tinaja.com/glib/bezarc1.pdf coming from
 * http://www.whizkidtech.redprince.net/bezier/circle/
 */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Arc  (HPDF_Page    page,
                HPDF_REAL    x,
                HPDF_REAL    y,
                HPDF_REAL    ray,
                HPDF_REAL    ang1,
                HPDF_REAL    ang2)
{
    HPDF_BOOL cont_flg = HPDF_FALSE;

    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_PATH_OBJECT);

    HPDF_PTRACE ((" HPDF_Page_Arc\n"));

    if (fabs(ang2 - ang1) >= 360)
        HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (ret != HPDF_OK)
        return ret;

    while (ang1 < 0 || ang2 < 0) {
        ang1 = ang1 + 360;
        ang2 = ang2 + 360;
    }


    for (;;) {
        if (fabs(ang2 - ang1) <= 90)
            return InternalArc (page, x, y, ray, ang1, ang2, cont_flg);
        else {
	    HPDF_REAL tmp_ang = (ang2 > ang1 ? ang1 + 90 : ang1 - 90);

            if ((ret = InternalArc (page, x, y, ray, ang1, tmp_ang, cont_flg))
                    != HPDF_OK)
                return ret;

            ang1 = tmp_ang;
        }

        if (fabs(ang1 - ang2) < 0.1)
            break;

        cont_flg = HPDF_TRUE;
    }

    return HPDF_OK;
}


static HPDF_STATUS
InternalArc  (HPDF_Page    page,
              HPDF_REAL    x,
              HPDF_REAL    y,
              HPDF_REAL    ray,
              HPDF_REAL    ang1,
              HPDF_REAL    ang2,
              HPDF_BOOL    cont_flg)
{
    const HPDF_REAL PIE = 3.14159F;

    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_PageAttr attr;
    HPDF_STATUS ret;

    HPDF_DOUBLE rx0, ry0, rx1, ry1, rx2, ry2, rx3, ry3;
    HPDF_DOUBLE x0, y0, x1, y1, x2, y2, x3, y3;
    HPDF_DOUBLE delta_angle;
    HPDF_DOUBLE new_angle;

    HPDF_PTRACE ((" HPDF_Page_InternalArc\n"));

    attr = (HPDF_PageAttr)page->attr;

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    delta_angle = (90 - (HPDF_DOUBLE)(ang1 + ang2) / 2) / 180 * PIE;
    new_angle = (HPDF_DOUBLE)(ang2 - ang1) / 2 / 180 * PIE;

    rx0 = ray * HPDF_COS (new_angle);
    ry0 = ray * HPDF_SIN (new_angle);
    rx2 = (ray * 4.0 - rx0) / 3.0;
    ry2 = ((ray * 1.0 - rx0) * (rx0 - ray * 3.0)) / (3.0 * ry0);
    rx1 = rx2;
    ry1 = -ry2;
    rx3 = rx0;
    ry3 = -ry0;

    x0 = rx0 * HPDF_COS (delta_angle) - ry0 * HPDF_SIN (delta_angle) + x;
    y0 = rx0 * HPDF_SIN (delta_angle) + ry0 * HPDF_COS (delta_angle) + y;
    x1 = rx1 * HPDF_COS (delta_angle) - ry1 * HPDF_SIN (delta_angle) + x;
    y1 = rx1 * HPDF_SIN (delta_angle) + ry1 * HPDF_COS (delta_angle) + y;
    x2 = rx2 * HPDF_COS (delta_angle) - ry2 * HPDF_SIN (delta_angle) + x;
    y2 = rx2 * HPDF_SIN (delta_angle) + ry2 * HPDF_COS (delta_angle) + y;
    x3 = rx3 * HPDF_COS (delta_angle) - ry3 * HPDF_SIN (delta_angle) + x;
    y3 = rx3 * HPDF_SIN (delta_angle) + ry3 * HPDF_COS (delta_angle) + y;

    if (!cont_flg) {
        pbuf = HPDF_FToA (pbuf, (HPDF_REAL)x0, eptr);
        *pbuf++ = ' ';
        pbuf = HPDF_FToA (pbuf, (HPDF_REAL)y0, eptr);

        if (attr->gmode == HPDF_GMODE_PATH_OBJECT)
            pbuf = (char *)HPDF_StrCpy (pbuf, " l\012", eptr);
        else
            pbuf = (char *)HPDF_StrCpy (pbuf, " m\012", eptr);
    }

    pbuf = HPDF_FToA (pbuf, (HPDF_REAL)x1, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, (HPDF_REAL)y1, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, (HPDF_REAL)x2, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, (HPDF_REAL)y2, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, (HPDF_REAL)x3, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, (HPDF_REAL)y3, eptr);
    HPDF_StrCpy (pbuf, " c\012", eptr);

    if ((ret = HPDF_Stream_WriteStr (attr->stream, buf)) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->cur_pos.x = (HPDF_REAL)x3;
    attr->cur_pos.y = (HPDF_REAL)y3;
    attr->str_pos = attr->cur_pos;
    attr->gmode = HPDF_GMODE_PATH_OBJECT;

    return ret;
}

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Arc2  (HPDF_Page    page,
                HPDF_REAL    x,
                HPDF_REAL    y,
                HPDF_REAL    ray,
                HPDF_REAL    ang1,
                HPDF_REAL    ang2)
{
    HPDF_BOOL cont_flg = HPDF_FALSE;

    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_PATH_OBJECT);

    HPDF_PTRACE ((" HPDF_Page_Arc2\n"));

    if (fabs(ang2 - ang1) > 360)
        HPDF_RaiseError (page->error, HPDF_PAGE_OUT_OF_RANGE, 0);

    if (ret != HPDF_OK)
        return ret;

    while (ang1 < 0 || ang2 < 0) {
        ang1 = ang1 + 360;
        ang2 = ang2 + 360;
    }


    for (;;) {
        if (fabs(ang2 - ang1) <= 90)
            return InternalArc (page, x, y, ray, ang1, ang2, cont_flg);
        else {
	    HPDF_REAL tmp_ang = (ang2 > ang1 ? ang1 + 90 : ang1 - 90);

            if ((ret = InternalArc (page, x, y, ray, ang1, tmp_ang, cont_flg))
                    != HPDF_OK)
                return ret;

            ang1 = tmp_ang;
        }

        if (fabs(ang1 - ang2) < 0.1)
            break;

        cont_flg = HPDF_TRUE;
    }

    return HPDF_OK;
}

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_DrawImage  (HPDF_Page    page,
                      HPDF_Image   image,
                      HPDF_REAL    x,
                      HPDF_REAL    y,
                      HPDF_REAL    width,
                      HPDF_REAL    height)
{
    HPDF_STATUS ret;

    if ((ret = HPDF_Page_GSave (page)) != HPDF_OK)
        return ret;

    if ((ret = HPDF_Page_Concat (page, width, 0, 0, height, x, y)) != HPDF_OK)
        return ret;

    if ((ret = HPDF_Page_ExecuteXObject (page, image)) != HPDF_OK)
        return ret;

    return HPDF_Page_GRestore (page);
}


static HPDF_STATUS
InternalWriteText  (HPDF_PageAttr      attr,
                    const char        *text)
{
    HPDF_FontAttr font_attr = (HPDF_FontAttr)attr->gstate->font->attr;
    HPDF_STATUS ret;

    HPDF_PTRACE ((" InternalWriteText\n"));

    if (font_attr->type == HPDF_FONT_TYPE0_TT ||
            font_attr->type == HPDF_FONT_TYPE0_CID) {
        HPDF_Encoder encoder;
	HPDF_UINT len;

        if ((ret = HPDF_Stream_WriteStr (attr->stream, "<")) != HPDF_OK)
            return ret;

        encoder = font_attr->encoder;
        len = HPDF_StrLen (text, HPDF_LIMIT_MAX_STRING_LEN);

        if (encoder->encode_text_fn == NULL) {
	    if ((ret = HPDF_Stream_WriteBinary (attr->stream, (HPDF_BYTE *)text,
						len, NULL))
		!= HPDF_OK)
	        return ret;
        } else {
	    char *encoded;
	    HPDF_UINT length;

	    encoded = (encoder->encode_text_fn)(encoder, text, len, &length);

	    ret = HPDF_Stream_WriteBinary (attr->stream, (HPDF_BYTE *)encoded,
					   length, NULL);

	    free(encoded);

	    if (ret != HPDF_OK)
                return ret;
        }

        return HPDF_Stream_WriteStr (attr->stream, ">");
    }

    return HPDF_Stream_WriteEscapeText (attr->stream, text);
}


/*
 * Convert a user space text position from absolute to relative coordinates.
 * Absolute values are passed in xAbs and yAbs, relative values are returned
 * to xRel and yRel. The latter two must not be NULL.
 */
static void
TextPos_AbsToRel (HPDF_TransMatrix text_matrix,
                  HPDF_REAL xAbs,
                  HPDF_REAL yAbs,
                  HPDF_REAL *xRel,
                  HPDF_REAL *yRel)
{
    if (text_matrix.a == 0) {
        *xRel = (yAbs - text_matrix.y - (xAbs - text_matrix.x) *
            text_matrix.d / text_matrix.c) / text_matrix.b;
        *yRel  = (xAbs - text_matrix.x) / text_matrix.c;
    } else {
        HPDF_REAL y = (yAbs - text_matrix.y - (xAbs - text_matrix.x) *
            text_matrix.b / text_matrix.a) / (text_matrix.d -
            text_matrix.c * text_matrix.b / text_matrix.a);
        *xRel = (xAbs - text_matrix.x - y * text_matrix.c) /
            text_matrix.a;
        *yRel = y;
    }
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_TextOut  (HPDF_Page    page,
                    HPDF_REAL    xpos,
                    HPDF_REAL    ypos,
                    const char  *text)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_REAL x;
    HPDF_REAL y;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_TextOut\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;
    TextPos_AbsToRel (attr->text_matrix, xpos, ypos, &x, &y);
    if ((ret = HPDF_Page_MoveTextPos (page, x, y)) != HPDF_OK)
        return ret;

    return  HPDF_Page_ShowText (page, text);
}


HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_TextRect  (HPDF_Page            page,
                     HPDF_REAL            left,
                     HPDF_REAL            top,
                     HPDF_REAL            right,
                     HPDF_REAL            bottom,
                     const char          *text,
                     HPDF_TextAlignment   align,
                     HPDF_UINT           *len
                     )
{
    return InternalTextRect(page, left, top, right, bottom, text, align, len, HPDF_FALSE);
}

static HPDF_STATUS
InternalTextRect  (HPDF_Page            page,
                   HPDF_REAL            left,
                   HPDF_REAL            top,
                   HPDF_REAL            right,
                   HPDF_REAL            bottom,
                   const char          *text,
                   HPDF_TextAlignment   align,
                   HPDF_UINT           *len,
                   HPDF_BOOL            force)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;
    const char *ptr = text;
    HPDF_BOOL pos_initialized = HPDF_FALSE;
    HPDF_REAL save_char_space = 0;
    HPDF_BOOL is_insufficient_space = HPDF_FALSE;
    HPDF_UINT num_rest;
    HPDF_Box bbox;
    HPDF_BOOL char_space_changed = HPDF_FALSE;

    HPDF_PTRACE ((" HPDF_Page_TextRect\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr )page->attr;

    /* no font exists */
    if (!attr->gstate->font) {
        return HPDF_RaiseError (page->error, HPDF_PAGE_FONT_NOT_FOUND, 0);
    }

    bbox = HPDF_Font_GetBBox (attr->gstate->font);

    if (len)
        *len = 0;
    num_rest = HPDF_StrLen (text, HPDF_LIMIT_MAX_STRING_LEN + 1);

    if (num_rest > HPDF_LIMIT_MAX_STRING_LEN) {
        return HPDF_RaiseError (page->error, HPDF_STRING_OUT_OF_RANGE, 0);
    } else if (!num_rest)
        return HPDF_OK;

    if (attr->gstate->text_leading == 0)
        HPDF_Page_SetTextLeading (page, (bbox.top - bbox.bottom) / 1000 *
                attr->gstate->font_size);

    top = top - bbox.top / 1000 * attr->gstate->font_size +
                attr->gstate->text_leading;
    bottom = bottom - bbox.bottom / 1000 * attr->gstate->font_size;

    if (align == HPDF_TALIGN_JUSTIFY) {
        save_char_space = attr->gstate->char_space;
        attr->gstate->char_space = 0;
    }

    for (;;) {
        HPDF_REAL x, y;
        HPDF_UINT line_len, tmp_len;
        HPDF_REAL rw;
        HPDF_BOOL LineBreak;

        attr->gstate->char_space = 0;
        line_len = tmp_len = HPDF_Page_MeasureText (page, ptr, right - left, HPDF_TRUE, &rw);
        if (force && line_len == 0) {
            line_len = tmp_len = HPDF_Page_MeasureText (page, ptr, right - left, HPDF_FALSE, &rw);
        }
        if (line_len == 0) {
            is_insufficient_space = HPDF_TRUE;
            break;
        }

        if (len)
            *len += line_len;
        num_rest -= line_len;

        /* Shorten tmp_len by trailing whitespace and control characters. */
        LineBreak = HPDF_FALSE;
        while (tmp_len > 0 && HPDF_IS_WHITE_SPACE(ptr[tmp_len - 1])) {
            tmp_len--;
            if (ptr[tmp_len] == 0x0A || ptr[tmp_len] == 0x0D) {
                LineBreak = HPDF_TRUE;
            }
        }

        switch (align) {

            case HPDF_TALIGN_RIGHT:
                TextPos_AbsToRel (attr->text_matrix, right - rw, top, &x, &y);
                if (!pos_initialized) {
                    pos_initialized = HPDF_TRUE;
                } else {
                    y = 0;
                }
                if ((ret = HPDF_Page_MoveTextPos (page, x, y)) != HPDF_OK)
                    return ret;
                break;

            case HPDF_TALIGN_CENTER:
                TextPos_AbsToRel (attr->text_matrix, left + (right - left - rw) / 2, top, &x, &y);
                if (!pos_initialized) {
                    pos_initialized = HPDF_TRUE;
                } else {
                    y = 0;
                }
                if ((ret = HPDF_Page_MoveTextPos (page, x, y)) != HPDF_OK)
                    return ret;
                break;

            case HPDF_TALIGN_JUSTIFY:
                if (!pos_initialized) {
                    pos_initialized = HPDF_TRUE;
                    TextPos_AbsToRel (attr->text_matrix, left, top, &x, &y);
                    if ((ret = HPDF_Page_MoveTextPos (page, x, y)) != HPDF_OK)
                        return ret;
                }

                /* Do not justify last line of paragraph or text. */
                if (LineBreak || num_rest <= 0) {
                    if ((ret = HPDF_Page_SetCharSpace (page, save_char_space))
                                    != HPDF_OK)
                        return ret;
                    char_space_changed = HPDF_FALSE;
                } else {
                    HPDF_REAL x_adjust;
                    HPDF_ParseText_Rec state;
                    HPDF_UINT i = 0;
                    HPDF_UINT num_char = 0;
                    HPDF_Encoder encoder = ((HPDF_FontAttr)attr->gstate->font->attr)->encoder;
                    const char *tmp_ptr = ptr;
                    HPDF_Encoder_SetParseText (encoder, &state, (HPDF_BYTE *)tmp_ptr, tmp_len);
                    while (*tmp_ptr) {
                        HPDF_ByteType btype = HPDF_Encoder_ByteType (encoder, &state);
                        if (btype != HPDF_BYTE_TYPE_TRIAL)
                            num_char++;
                        i++;
                        if (i >= tmp_len)
                            break;
                        tmp_ptr++;
                    }

                    x_adjust = num_char == 0 ? 0 : (right - left - rw) / (num_char - 1);
                    if ((ret = HPDF_Page_SetCharSpace (page, x_adjust)) != HPDF_OK)
                        return ret;
                    char_space_changed = HPDF_TRUE;
                }
                break;

            default:
                if (!pos_initialized) {
                    pos_initialized = HPDF_TRUE;
                    TextPos_AbsToRel (attr->text_matrix, left, top, &x, &y);
                    if ((ret = HPDF_Page_MoveTextPos (page, x, y)) != HPDF_OK)
                        return ret;
                }
        }

        if (InternalShowTextNextLine (page, ptr, tmp_len) != HPDF_OK)
            return HPDF_CheckError (page->error);

        if (num_rest <= 0)
            break;

        if (!force && attr->text_pos.y - attr->gstate->text_leading < bottom) {
            is_insufficient_space = HPDF_TRUE;
            break;
        }

        ptr += line_len;
    }

    if (char_space_changed && save_char_space != attr->gstate->char_space) {
        if ((ret = HPDF_Page_SetCharSpace (page, save_char_space)) != HPDF_OK)
            return ret;
    }

    if (is_insufficient_space)
        return HPDF_PAGE_INSUFFICIENT_SPACE;
    else
        return HPDF_OK;
}


static HPDF_STATUS
InternalShowTextNextLine  (HPDF_Page    page,
                           const char  *text,
                           HPDF_UINT    len)
{
    HPDF_STATUS ret;
    HPDF_PageAttr attr;
    HPDF_REAL tw;
    HPDF_FontAttr font_attr;

    HPDF_PTRACE ((" ShowTextNextLine\n"));

    attr = (HPDF_PageAttr)page->attr;
    font_attr = (HPDF_FontAttr)attr->gstate->font->attr;

    if (font_attr->type == HPDF_FONT_TYPE0_TT ||
            font_attr->type == HPDF_FONT_TYPE0_CID) {
        HPDF_Encoder encoder = font_attr->encoder;

        if ((ret = HPDF_Stream_WriteStr (attr->stream, "<")) != HPDF_OK)
            return ret;

        if (encoder->encode_text_fn == NULL) {
	    if ((ret = HPDF_Stream_WriteBinary (attr->stream, (HPDF_BYTE *)text,
						len, NULL))
		!= HPDF_OK)
	        return ret;
        } else {
	    char *encoded;
	    HPDF_UINT length;

	    encoded = (encoder->encode_text_fn)(encoder, text, len, &length);
	    ret = HPDF_Stream_WriteBinary (attr->stream, (HPDF_BYTE *)encoded,
					   length, NULL);
	    free(encoded);

	    if (ret != HPDF_OK)
	        return ret;
        }

        if ((ret = HPDF_Stream_WriteStr (attr->stream, ">")) != HPDF_OK)
            return ret;
    } else  if ((ret = HPDF_Stream_WriteEscapeText2 (attr->stream, text,
                len)) != HPDF_OK)
        return ret;

    if ((ret = HPDF_Stream_WriteStr (attr->stream, " \'\012")) != HPDF_OK)
        return ret;

    tw = HPDF_Page_TextWidth (page, text);

    /* calculate the reference point of text */
    attr->text_matrix.x -= attr->gstate->text_leading * attr->text_matrix.c;
    attr->text_matrix.y -= attr->gstate->text_leading * attr->text_matrix.d;

    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    if (attr->gstate->writing_mode == HPDF_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}


/*
 *  This function is contributed by Adrian Nelson (adenelson).
 */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetSlideShow  (HPDF_Page            page,
                         HPDF_TransitionStyle   type,
                         HPDF_REAL            disp_time,
                         HPDF_REAL            trans_time)
    {
    HPDF_STATUS ret = HPDF_OK;
    HPDF_Dict dict;

    HPDF_PTRACE((" HPDF_Page_SetSlideShow\n"));

    if (!HPDF_Page_Validate (page))
        return HPDF_INVALID_PAGE;

    if (disp_time < 0)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_DISPLAY_TIME,
                    (HPDF_STATUS)disp_time);

    if (trans_time < 0)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_TRANSITION_TIME,
                    (HPDF_STATUS)trans_time);

    dict = HPDF_Dict_New(page->mmgr);

    if (!dict)
        return HPDF_Error_GetCode (page->error);

    if (HPDF_Dict_AddName (dict, "Type", "Trans") != HPDF_OK)
        goto Fail;

    if (HPDF_Dict_AddReal (dict, "D", trans_time) != HPDF_OK)
        goto Fail;

    switch (type) {
        case HPDF_TS_WIPE_RIGHT:
            ret += HPDF_Dict_AddName (dict, "S", "Wipe");
            ret += HPDF_Dict_AddNumber (dict, "Di", 0);
            break;
        case HPDF_TS_WIPE_UP:
            ret += HPDF_Dict_AddName (dict, "S", "Wipe");
            ret += HPDF_Dict_AddNumber (dict, "Di", 90);
            break;
        case HPDF_TS_WIPE_LEFT:
            ret += HPDF_Dict_AddName (dict, "S", "Wipe");
            ret += HPDF_Dict_AddNumber (dict, "Di", 180);
            break;
        case HPDF_TS_WIPE_DOWN:
            ret += HPDF_Dict_AddName (dict, "S", "Wipe");
            ret += HPDF_Dict_AddNumber    (dict, "Di", 270);
            break;
        case HPDF_TS_BARN_DOORS_HORIZONTAL_OUT:
            ret += HPDF_Dict_AddName (dict, "S", "Split");
            ret += HPDF_Dict_AddName (dict, "Dm", "H");
            ret += HPDF_Dict_AddName (dict, "M", "O");
            break;
        case HPDF_TS_BARN_DOORS_HORIZONTAL_IN:
            ret += HPDF_Dict_AddName (dict, "S", "Split");
            ret += HPDF_Dict_AddName (dict, "Dm", "H");
            ret += HPDF_Dict_AddName (dict, "M", "I");
            break;
        case HPDF_TS_BARN_DOORS_VERTICAL_OUT:
            ret += HPDF_Dict_AddName (dict, "S", "Split");
            ret += HPDF_Dict_AddName (dict, "Dm", "V");
            ret += HPDF_Dict_AddName (dict, "M", "O");
            break;
        case HPDF_TS_BARN_DOORS_VERTICAL_IN:
            ret += HPDF_Dict_AddName (dict, "S", "Split");
            ret += HPDF_Dict_AddName (dict, "Dm", "V");
            ret += HPDF_Dict_AddName (dict, "M", "I");
            break;
        case HPDF_TS_BOX_OUT:
            ret += HPDF_Dict_AddName (dict, "S", "Box");
            ret += HPDF_Dict_AddName (dict, "M", "O");
            break;
        case HPDF_TS_BOX_IN:
            ret += HPDF_Dict_AddName (dict, "S", "Box");
            ret += HPDF_Dict_AddName (dict, "M", "I");
            break;
        case HPDF_TS_BLINDS_HORIZONTAL:
            ret += HPDF_Dict_AddName (dict, "S", "Blinds");
            ret += HPDF_Dict_AddName (dict, "Dm", "H");
            break;
        case HPDF_TS_BLINDS_VERTICAL:
            ret += HPDF_Dict_AddName (dict, "S", "Blinds");
            ret += HPDF_Dict_AddName (dict, "Dm", "V");
            break;
        case HPDF_TS_DISSOLVE:
            ret += HPDF_Dict_AddName (dict, "S", "Dissolve");
            break;
        case HPDF_TS_GLITTER_RIGHT:
            ret += HPDF_Dict_AddName (dict, "S", "Glitter");
            ret += HPDF_Dict_AddNumber (dict, "Di", 0);
            break;
        case HPDF_TS_GLITTER_DOWN:
            ret += HPDF_Dict_AddName (dict, "S", "Glitter");
            ret += HPDF_Dict_AddNumber (dict, "Di", 270);
            break;
        case HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT:
            ret += HPDF_Dict_AddName (dict, "S", "Glitter");
            ret += HPDF_Dict_AddNumber (dict, "Di", 315);
            break;
        case HPDF_TS_REPLACE:
            ret += HPDF_Dict_AddName  (dict, "S", "R");
            break;
        default:
            ret += HPDF_SetError(page->error, HPDF_INVALID_PAGE_SLIDESHOW_TYPE, 0);
    }

    if (ret != HPDF_OK)
        goto Fail;

    if (HPDF_Dict_AddReal (page, "Dur", disp_time) != HPDF_OK)
        goto Fail;

    if ((ret = HPDF_Dict_Add (page, "Trans", dict)) != HPDF_OK)
        return ret;

    return HPDF_OK;

Fail:
    HPDF_Dict_Free (dict);
    return HPDF_Error_GetCode (page->error);
}


/*
 *  This function is contributed by Finn Arildsen.
 */

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_New_Content_Stream  (HPDF_Page page,
                               HPDF_Dict* new_stream)
{
    /* Call this function to start a new content stream on a page. The
       handle is returned to new_stream.
       new_stream can later be used on other pages as a shared content stream;
       insert using HPDF_Page_Insert_Shared_Content_Stream */

    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;
    HPDF_UINT filter;
    HPDF_Array contents_array;

    HPDF_PTRACE((" HPDF_Page_New_Content_Stream\n"));

    attr = (HPDF_PageAttr)page->attr;
    filter = attr->contents->filter;

    /* check if there is already an array of contents */
    contents_array = (HPDF_Array) HPDF_Dict_GetItem(page,"Contents", HPDF_OCLASS_ARRAY);
    if (!contents_array) {
        HPDF_Error_Reset (page->error);
        /* no contents_array already -- create one
           and replace current single contents item */
        contents_array = HPDF_Array_New(page->mmgr);
        if (!contents_array)
            return HPDF_Error_GetCode (page->error);
        ret += HPDF_Array_Add(contents_array,attr->contents);
        ret += HPDF_Dict_Add (page, "Contents", contents_array);
    }

    /* create new contents stream and add it to the page's contents array */
    attr->contents = HPDF_DictStream_New (page->mmgr, attr->xref);
    attr->contents->filter = filter;
    attr->stream = attr->contents->stream;

    if (!attr->contents)
        return HPDF_Error_GetCode (page->error);

    ret += HPDF_Array_Add (contents_array,attr->contents);

    /* return the value of the new stream, so that
       the application can use it as a shared contents stream */
    if (ret == HPDF_OK && new_stream != NULL)
        *new_stream = attr->contents;

    return ret;
}


/*
 *  This function is contributed by Finn Arildsen.
 */

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Insert_Shared_Content_Stream  (HPDF_Page page,
                               HPDF_Dict shared_stream)
{
    /* Call this function to insert a previously (with HPDF_New_Content_Stream) created content stream
       as a shared content stream on this page */

    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_Array contents_array;

    HPDF_PTRACE((" HPDF_Page_Insert_Shared_Content_Stream\n"));

    /* check if there is already an array of contents */
    contents_array = (HPDF_Array) HPDF_Dict_GetItem(page,"Contents", HPDF_OCLASS_ARRAY);
    if (!contents_array) {
        HPDF_PageAttr attr;
        HPDF_Error_Reset (page->error);
        /* no contents_array already -- create one
           and replace current single contents item */
        contents_array = HPDF_Array_New(page->mmgr);
        if (!contents_array)
            return HPDF_Error_GetCode (page->error);
        attr = (HPDF_PageAttr)page->attr;
        ret += HPDF_Array_Add(contents_array,attr->contents);
        ret += HPDF_Dict_Add (page, "Contents", contents_array);
    }

    ret += HPDF_Array_Add (contents_array,shared_stream);

    /* Continue with a new stream */
    ret += HPDF_Page_New_Content_Stream (page, NULL);

    return ret;
}

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_WriteComment  (HPDF_Page    page,
                         const char  *text)
{
    HPDF_PageAttr attr;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, text) != HPDF_OK)
        return HPDF_CheckError (page->error);
    return HPDF_OK;
}

/*
 * Inserts a form text field.
 * Parameter:
 * page - The Page on which the text field should be inserted
 * pdf - The PDF Document
 * left, top, right, bottom - The coordinates of the text field
 * name - The name of the text field
 * value - The value of the text field
 * encoder - The encoder used to encode the value
 * encoded_text - The text encoded in the font's encoding (will be used in the appearance stream)
 * flag - A flag specifying various characteristics of the field( One or more of the HPDF_FIELD_* variables or'ed together )
 * print - If set, the text field will be printed when the page gets printed
 * max_len - The maximum number of characters
 * alignment - The text alignment ( 0 - Left-justified, 1 - Centered, 2 - Right-justified )
 * rotation - The rotation
 * font - The text fields font
 * font_size - The font_size
 * color - The text color
 */
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_TextField  (HPDF_Page      page,
                      HPDF_Doc       pdf,
                      HPDF_REAL      left,
                      HPDF_REAL      top,
                      HPDF_REAL      right,
                      HPDF_REAL      bottom,
                      const char    *name,
                      const char    *value,
                      HPDF_Encoder   encoder,
                      const char    *encoded_text,
                      HPDF_UINT      flag,
                      HPDF_BOOL      print,
                      HPDF_UINT      max_len,
                      HPDF_UINT      alignment,
                      HPDF_INT       rotation,
                      HPDF_Font      font,
                      HPDF_REAL      font_size,
                      HPDF_Color     color)
{
    HPDF_Dict textField;
    HPDF_STATUS ret;
    const char *local_name;

    HPDF_PTRACE((" HPDF_Page_TextField\n"));

    textField = HPDF_Dict_New (page->mmgr);
    if (!textField) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    if ((ret = HPDF_Xref_Add (pdf->xref, textField)) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_AddName (textField, "Type", "Annot");
    ret += HPDF_Dict_AddName (textField, "Subtype", "Widget");

    if (print) {
        ret += HPDF_Dict_AddNumber (textField, "F", 4);
    } else {
        ret += HPDF_Dict_AddNumber (textField, "F", 0);
    }

    /* Rect */
    HPDF_Array rectArray = HPDF_Array_New (page->mmgr);
    if (!rectArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (rectArray, left);
    ret += HPDF_Array_AddReal (rectArray, bottom);
    ret += HPDF_Array_AddReal (rectArray, right);
    ret += HPDF_Array_AddReal (rectArray, top);

    ret += HPDF_Dict_Add (textField, "Rect", rectArray);

    /* FT */
    ret += HPDF_Dict_AddName (textField, "FT", "Tx");

    /* T */
    HPDF_String textFieldName = HPDF_String_New (page->mmgr, name, NULL);
    if (!textFieldName) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (textField, "T", textFieldName);

    /* V */
    HPDF_String textFieldValue = HPDF_String_New (page->mmgr, value, encoder);
    if (!textFieldValue) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (textField, "V", textFieldValue);

    /* DR */
    HPDF_Dict resource = HPDF_Dict_New (page->mmgr);
    if (!resource) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    HPDF_Dict f = HPDF_Dict_New (page->mmgr);
    if (!f) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    local_name = HPDF_Catalog_GetLocalFontName (pdf->catalog, font);
    if (!local_name) {
        HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);
        return NULL;
    }

    ret += HPDF_Dict_Add (f, local_name, font);
    ret += HPDF_Dict_Add (resource, "Font", f);
    ret += HPDF_Dict_Add (textField, "DR", resource);

    /* DA */
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = InternalWriteColorToBuf (pbuf, eptr, color, HPDF_TRUE);

    pbuf = (char *)HPDF_StrCpy (pbuf, " /", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, local_name, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, font_size, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " Tf", eptr);

    HPDF_String daValue = HPDF_String_New(page->mmgr, buf, NULL);
    if (!daValue) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (textField, "DA", daValue);

    /* MK */
    if (rotation && rotation != 0 && (rotation % 90) == 0)
    {
        HPDF_Dict mk = HPDF_Dict_New (page->mmgr);
        if (!mk) {
            HPDF_CheckError (page->error);
            return NULL;
        }
        ret += HPDF_Dict_AddNumber (mk, "R", rotation);
        ret += HPDF_Dict_Add (textField, "MK", mk);
    }

    /* ALIGNMENT */
    if (alignment > 0 && alignment <= 2)
    {
        ret += HPDF_Dict_AddNumber (textField, "Q", alignment);
    }

    /* FF */
    if (flag > 0)
        ret += HPDF_Dict_AddNumber (textField, "Ff", flag);

    /* MaxLen */
    if (max_len > 0)
        ret += HPDF_Dict_AddNumber (textField, "MaxLen", max_len);

    /* AP - APPEARANCE DICTIONARY */
    HPDF_Dict ap = HPDF_Dict_New (page->mmgr);
    if (!ap) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    HPDF_Dict ap_stream = HPDF_DictStream_New (page->mmgr, pdf->xref);
    if (!ap_stream) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (ap, "N", ap_stream);
    ret += HPDF_Dict_Add (textField, "AP", ap);

    ret += HPDF_Dict_AddName (ap_stream, "Type", "XObject");
    ret += HPDF_Dict_AddName (ap_stream, "Subtype", "Form");

    HPDF_REAL field_width;
    HPDF_REAL field_height;
    if (rotation == 90 || rotation == 270) {
        field_width = fabs(top - bottom);
        field_height = fabs(right - left);
    } else {
        field_width = fabs(right - left);
        field_height = fabs(top - bottom);
    }

    /* Matrix */
    if (rotation != 0) {
        HPDF_Array matrix = InternalAnnotationMatrix (page->mmgr, field_width, field_height, rotation);
        if (!matrix) {
            HPDF_CheckError (page->error);
            return NULL;
        }

        ret += HPDF_Dict_Add (ap_stream, "Matrix", matrix);
    }

    /* BBOX */
    HPDF_Array bbox = HPDF_Array_New (page->mmgr);
    if (!bbox) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (bbox, 0);
    ret += HPDF_Array_AddReal (bbox, 0);
    ret += HPDF_Array_AddReal (bbox, field_width);
    ret += HPDF_Array_AddReal (bbox, field_height);
    ret += HPDF_Dict_Add (ap_stream, "BBox", bbox);

    /* RESOURCES */
    HPDF_Dict resource2 = HPDF_Dict_New (page->mmgr);
    if (!resource2) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    HPDF_Dict font2 = HPDF_Dict_New (page->mmgr);
    if (!font2) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    ret += HPDF_Dict_Add (font2, local_name, font);
    ret += HPDF_Dict_Add (resource2, "Font", font2);
    ret += HPDF_Dict_Add (ap_stream, "Resources", resource2);

    /* STREAM */
    // create a fake page that will be used to generate the appearance stream
    HPDF_Page fake_page = HPDF_Page_New_Fake(page->mmgr, pdf->xref, ap_stream);
    HPDF_PageAttr attr = (HPDF_PageAttr)fake_page->attr;
    attr->fonts = font2;
    attr->text_placement_accuracy = pdf->text_placement_accuracy;


    ret += HPDF_Stream_WriteStr (ap_stream->stream, "/Tx BMC\n");
    ret += HPDF_Page_BeginText(fake_page);

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);
    pbuf = InternalWriteColorToBuf (buf, eptr, color, HPDF_TRUE);
    *pbuf++ = '\012';
    ret += HPDF_Stream_WriteStr (ap_stream->stream, buf);

    ret += HPDF_Page_SetFontAndSize(fake_page, font, font_size);

    HPDF_REAL padding = 2.0;
    if (flag & HPDF_FIELD_MULTILINE) {
        HPDF_TextAlignment talign = HPDF_TALIGN_LEFT;
        switch (alignment) {
            case 0:
                talign = HPDF_TALIGN_LEFT;
                break;
            case 1:
                talign = HPDF_TALIGN_CENTER;
                break;
            case 2:
                talign = HPDF_TALIGN_RIGHT;
                break;
        }

        HPDF_Box bbox = HPDF_Font_GetBBox (font);
        HPDF_REAL text_lead = font_size + ((HPDF_REAL)HPDF_Font_GetDescent(font) / -1000.0 * font_size);
        HPDF_REAL y_offset;
        if (field_height < text_lead) {
            y_offset = (bbox.top - bbox.bottom) / 1000.0*font_size + 1.0;
        } else {
            y_offset = field_height - (HPDF_REAL)HPDF_Font_GetDescent(font) / -1000.0 * font_size - padding;
        }
        ret += InternalTextRect(fake_page, padding, y_offset, field_width - padding, 0, encoded_text, talign, NULL, HPDF_TRUE);
    } else {
        HPDF_REAL x_offset = padding;
        if (alignment != 0) {
            HPDF_REAL text_width = HPDF_Page_TextWidth(fake_page, encoded_text);
            if (text_width < field_width - padding*2.0) {
                if (alignment == 1) {
                    x_offset = (field_width - text_width) / 2.0;
                } else if (alignment == 2) {
                    x_offset = field_width - text_width - padding;
                }
            }
        }

        HPDF_REAL y_offset;
        if (field_height < font_size) {
            y_offset = (HPDF_REAL)HPDF_Font_GetDescent(font) / -1000.0 * font_size + 1.0;
        } else {
            y_offset = field_height/2.0 - font_size/2.0 + 0.129*font_size;
        }
        ret += HPDF_Page_TextOut(fake_page, x_offset, y_offset, encoded_text);
    }
    ret += HPDF_Page_EndText(fake_page);
    ret += HPDF_Stream_WriteStr (ap_stream->stream, "EMC\012");

    ret += HPDF_Page_CreateFieldAnnotation (page, textField);

    ret += HPDF_Catalog_AddInteractiveField (pdf->catalog, textField);

    HPDF_Dict_Free (fake_page);

    if (ret != HPDF_OK) {
        return NULL;
    }

    return textField;
}


/*
 * Inserts a form signature field.
 * Parameter:
 * page - The Page on which the signature field should be inserted
 * pdf - The PDF Document
 * left, top, right, bottom - The coordinates of the signature field
 * name - The name of the signature field
 * print - If set, the text field will be printed when the page gets printed
 * rotation - The rotation
 */
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_SignatureField (HPDF_Page      page,
                          HPDF_Doc       pdf,
                          HPDF_REAL      left,
                          HPDF_REAL      top,
                          HPDF_REAL      right,
                          HPDF_REAL      bottom,
                          const char     *name,
                          HPDF_BOOL      print,
                          HPDF_INT       rotation)
{
    HPDF_Dict signatureField;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Page_SignatureField\n"));

    signatureField = HPDF_Dict_New (page->mmgr);
    if (!signatureField) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    if ((ret = HPDF_Xref_Add (pdf->xref, signatureField)) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_AddName (signatureField, "Type", "Annot");
    ret += HPDF_Dict_AddName (signatureField, "Subtype", "Widget");

    if (print) {
        ret += HPDF_Dict_AddNumber (signatureField, "F", 4);
    } else {
        ret += HPDF_Dict_AddNumber (signatureField, "F", 0);
    }

    /* Rect */
    HPDF_Array rectArray = HPDF_Array_New (page->mmgr);
    if (!rectArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (rectArray, left);
    ret += HPDF_Array_AddReal (rectArray, bottom);
    ret += HPDF_Array_AddReal (rectArray, right);
    ret += HPDF_Array_AddReal (rectArray, top);

    ret += HPDF_Dict_Add (signatureField, "Rect", rectArray);

    /* FT */
    ret += HPDF_Dict_AddName (signatureField, "FT", "Sig");

    /* T */
    HPDF_String signatureFieldName = HPDF_String_New (page->mmgr, name, NULL);
    if (!signatureFieldName) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (signatureField, "T", signatureFieldName);

    /* MK */
    if (rotation && rotation != 0 && (rotation % 90) == 0)
    {
        HPDF_Dict mk = HPDF_Dict_New (page->mmgr);
        if (!mk) {
            HPDF_CheckError (page->error);
            return NULL;
        }
        ret += HPDF_Dict_AddNumber (mk, "R", rotation);
        ret += HPDF_Dict_Add (signatureField, "MK", mk);
    }

    /* DA */
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    /* Gray Color Space */
    pbuf = HPDF_FToA (pbuf, 0, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " g ", eptr);

    pbuf = HPDF_FToA (pbuf, 0, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " Tf", eptr);

    HPDF_String daValue = HPDF_String_New(page->mmgr, buf, NULL);
    if (!daValue) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (signatureField, "DA", daValue);

    /* AP - APPEARANCE DICTIONARY */
    HPDF_Dict ap = HPDF_Dict_New (page->mmgr);
    if (!ap) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    HPDF_Dict ap_stream = HPDF_DictStream_New (page->mmgr, pdf->xref);
    if (!ap_stream) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (ap, "N", ap_stream);

    ret += HPDF_Dict_Add (signatureField, "AP", ap);

    ret += HPDF_Dict_AddName (ap_stream, "Type", "XObject");
    ret += HPDF_Dict_AddName (ap_stream, "Subtype", "Form");

    /* BBOX */
    HPDF_Array bbox = HPDF_Array_New (page->mmgr);
    if (!bbox) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (bbox, 0);
    ret += HPDF_Array_AddReal (bbox, 0);
    ret += HPDF_Array_AddReal (bbox, right - left);
    ret += HPDF_Array_AddReal (bbox, top - bottom);
    ret += HPDF_Dict_Add (ap_stream, "BBox", bbox);

    ret += HPDF_Page_CreateFieldAnnotation (page, signatureField);

    ret += HPDF_Catalog_AddInteractiveField (pdf->catalog, signatureField);

    if (ret != HPDF_OK) {
        return NULL;
    }

    return signatureField;
}


/*
 * Inserts a form checkbox field.
 * Parameter:
 * page - The Page on which the checkbox field should be inserted
 * pdf - The PDF Document
 * left, top, right, bottom - The coordinates of the checkbox field
 * name - The name of the checkbox field
 * print - If set, the checkbox field will be printed when the page gets printed
 * rotation - The rotation
 * color - The checkbox color
 * checked - States if the checkbox should be checked
 */
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CheckboxField  (HPDF_Page      page,
                          HPDF_Doc       pdf,
                          HPDF_REAL      left,
                          HPDF_REAL      top,
                          HPDF_REAL      right,
                          HPDF_REAL      bottom,
                          const char     *name,
                          HPDF_BOOL      print,
                          HPDF_INT       rotation,
                          HPDF_Color     color,
                          HPDF_BOOL      checked)
{
    HPDF_Dict checkboxField;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Page_CheckboxField\n"));

    checkboxField = HPDF_Dict_New (page->mmgr);
    if (!checkboxField) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    if ((ret = HPDF_Xref_Add (pdf->xref, checkboxField)) != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_AddName (checkboxField, "Type", "Annot");
    ret += HPDF_Dict_AddName (checkboxField, "Subtype", "Widget");

    if (print) {
        ret += HPDF_Dict_AddNumber (checkboxField, "F", 4);
    } else {
        ret += HPDF_Dict_AddNumber (checkboxField, "F", 0);
    }

    /* Rect */
    HPDF_Array rectArray = HPDF_Array_New (page->mmgr);
    if (!rectArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (rectArray, left);
    ret += HPDF_Array_AddReal (rectArray, bottom);
    ret += HPDF_Array_AddReal (rectArray, right);
    ret += HPDF_Array_AddReal (rectArray, top);

    ret += HPDF_Dict_Add (checkboxField, "Rect", rectArray);

    /* FT */
    ret += HPDF_Dict_AddName (checkboxField, "FT", "Btn");

    /* T */
    HPDF_String checkboxFieldName = HPDF_String_New (page->mmgr, name, NULL);
    if (!checkboxFieldName) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (checkboxField, "T", checkboxFieldName);

    /* V and AS */
    if (checked){
        ret += HPDF_Dict_AddName (checkboxField, "V", "Yes");
        ret += HPDF_Dict_AddName (checkboxField, "AS", "Yes");
    } else {
        ret += HPDF_Dict_AddName (checkboxField, "V", "Off");
        ret += HPDF_Dict_AddName (checkboxField, "AS", "Off");
    }

    /* DR */
    HPDF_Dict resource = HPDF_Dict_New (page->mmgr);
    if (!resource) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    HPDF_Dict f = HPDF_Dict_New (page->mmgr);
    if (!f) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (checkboxField, "DR", resource);

    HPDF_Font font = HPDF_GetFont (pdf, "ZapfDingbats", NULL);
    if (!font) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    const char *local_name = HPDF_Catalog_GetLocalFontName (pdf->catalog, font);
    if (!local_name) {
        HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);
        return NULL;
    }

    /* DA */
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = InternalWriteColorToBuf (pbuf, eptr, color, HPDF_TRUE);
    pbuf = (char *)HPDF_StrCpy (pbuf, " /", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, local_name, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " 0 Tf", eptr);

    HPDF_String daValue = HPDF_String_New(page->mmgr, buf, NULL);
    if (!daValue) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (checkboxField, "DA", daValue);


    /* MK */
    HPDF_Dict mk = HPDF_Dict_New (page->mmgr);
    if (!mk) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    // /BG
    HPDF_Array bgArray = HPDF_Array_New (page->mmgr);
    if (!bgArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddNumber (bgArray, 1);
    ret += HPDF_Dict_Add (mk, "BG", bgArray);

    // /BC
    HPDF_Array bcArray = HPDF_Array_New (page->mmgr);
    if (!bcArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddNumber (bcArray, 0);
    ret += HPDF_Dict_Add (mk, "BC", bcArray);

    // /CA
    HPDF_String textFieldValue = HPDF_String_New (page->mmgr, "8", NULL);
    if (!textFieldValue) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (mk, "CA", textFieldValue);

    if (rotation && rotation != 0 && (rotation % 90) == 0)
    {
        ret += HPDF_Dict_AddNumber (mk, "R", rotation);
    }
    ret += HPDF_Dict_Add (checkboxField, "MK", mk);

    /* AP - APPEARANCE DICTIONARY */
    HPDF_Dict ap = HPDF_Dict_New (page->mmgr);
    if (!ap) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    HPDF_Dict n_ap = HPDF_Dict_New (page->mmgr);
    if (!n_ap) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    // /Yes
    HPDF_Dict yes_stream = HPDF_DictStream_New (page->mmgr, pdf->xref);
    if (!yes_stream) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    char yes_buf[HPDF_TMP_BUF_SIZ];
    pbuf = yes_buf;
    eptr = yes_buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (yes_buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = InternalWriteColorToBuf (pbuf, eptr, color, HPDF_FALSE);

    // Print X
    HPDF_REAL field_width;
    HPDF_REAL field_height;
    if (rotation == 90 || rotation == 270) {
        field_width = fabs(top - bottom);
        field_height = fabs(right - left);
    } else {
        field_width = fabs(right - left);
        field_height = fabs(top - bottom);
    }
    HPDF_REAL cross_width = field_width;
    HPDF_REAL cross_height = field_height;
    HPDF_REAL cross_x_offset = 0;
    HPDF_REAL cross_y_offset = 0;
    if ( cross_width < cross_height )
    {
        cross_y_offset = ( cross_height - cross_width ) / 2;
        cross_height = cross_width + cross_y_offset;
    }
    else
    {
        cross_x_offset = ( cross_width - cross_height ) / 2;
        cross_width = cross_height + cross_x_offset;
    }
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, cross_x_offset, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, cross_y_offset, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " m ", eptr);
    pbuf = HPDF_FToA (pbuf, cross_width, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, cross_height, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " l S ", eptr);

    pbuf = HPDF_FToA (pbuf, cross_x_offset, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, cross_height, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " m ", eptr);
    pbuf = HPDF_FToA (pbuf, cross_width, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, cross_y_offset, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " l S ", eptr);

    // Print Box []
    pbuf = HPDF_FToA (pbuf, 0, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " G", eptr);

    pbuf = (char *)HPDF_StrCpy (pbuf, " 2 w 0 0 m ", eptr);
    pbuf = HPDF_FToA (pbuf, field_width, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " 0 l ", eptr);
    pbuf = HPDF_FToA (pbuf, field_width, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, field_height, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " l 0 ", eptr);
    pbuf = HPDF_FToA (pbuf, field_height, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " l 0 0 l S", eptr);

    ret += HPDF_Stream_WriteStr (yes_stream->stream, yes_buf);

    HPDF_Array yes_bbox = HPDF_Array_New (page->mmgr);
    if (!yes_bbox) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (yes_bbox, 0);
    ret += HPDF_Array_AddReal (yes_bbox, 0);
    ret += HPDF_Array_AddReal (yes_bbox, field_width);
    ret += HPDF_Array_AddReal (yes_bbox, field_height);
    ret += HPDF_Dict_Add (yes_stream, "BBox", yes_bbox);
    ret += HPDF_Dict_AddName (yes_stream, "Type", "XObject");
    ret += HPDF_Dict_AddName (yes_stream, "Subtype", "Form");

    // Matrix
    if (rotation != 0) {
        HPDF_Array matrix = InternalAnnotationMatrix (page->mmgr, field_width, field_height, rotation);
        if (!matrix) {
            HPDF_CheckError (page->error);
            return NULL;
        }

        ret += HPDF_Dict_Add (yes_stream, "Matrix", matrix);
    }

    // /Off
    HPDF_Dict off_stream = HPDF_DictStream_New (page->mmgr, pdf->xref);
    if (!off_stream) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    char off_buf[HPDF_TMP_BUF_SIZ];
    pbuf = off_buf;
    eptr = off_buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (off_buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = HPDF_FToA (pbuf, 0, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " G", eptr);

    pbuf = (char *)HPDF_StrCpy (pbuf, " 2 w 0 0 m ", eptr);
    pbuf = HPDF_FToA (pbuf, field_width, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " 0 l ", eptr);
    pbuf = HPDF_FToA (pbuf, field_width, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, field_height, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " l 0 ", eptr);
    pbuf = HPDF_FToA (pbuf, field_height, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " l 0 0 l S", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " 0 0 l S", eptr);
    ret += HPDF_Stream_WriteStr (off_stream->stream, off_buf);

    HPDF_Array off_bbox = HPDF_Array_New (page->mmgr);
    if (!off_bbox) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (off_bbox, 0);
    ret += HPDF_Array_AddReal (off_bbox, 0);
    ret += HPDF_Array_AddReal (off_bbox, field_width);
    ret += HPDF_Array_AddReal (off_bbox, field_height);
    ret += HPDF_Dict_Add (off_stream, "BBox", off_bbox);
    ret += HPDF_Dict_AddName (off_stream, "Type", "XObject");
    ret += HPDF_Dict_AddName (off_stream, "Subtype", "Form");

    // Matrix
    if (rotation != 0) {
        HPDF_Array matrix = InternalAnnotationMatrix (page->mmgr, field_width, field_height, rotation);
        if (!matrix) {
            HPDF_CheckError (page->error);
            return NULL;
        }

        ret += HPDF_Dict_Add (off_stream, "Matrix", matrix);
    }

    ret += HPDF_Dict_Add (ap, "N", n_ap);
    ret += HPDF_Dict_Add (n_ap, "Yes", yes_stream);
    ret += HPDF_Dict_Add (n_ap, "Off", off_stream);

    ret += HPDF_Dict_Add (checkboxField, "AP", ap);

    /* STREAM */
    ret += HPDF_Page_CreateFieldAnnotation (page, checkboxField);

    ret += HPDF_Catalog_AddInteractiveField (pdf->catalog, checkboxField);

    if (ret != HPDF_OK) {
        return NULL;
    }

    return checkboxField;
}

static char*
InternalWriteColorToBuf  (char       *pbuf,
                          char       *eptr,
                          HPDF_Color  color,
                          HPDF_BOOL   fill)
{
    if (color.cs == HPDF_CS_DEVICE_GRAY) {
        /* Gray Color Space */
        pbuf = HPDF_FToA (pbuf, color.gray, eptr);
        pbuf = (char *)HPDF_StrCpy (pbuf, fill ? " g" : " G", eptr);
    } else if (color.cs == HPDF_CS_DEVICE_RGB) {
        /* RGB Color Space */
        pbuf = HPDF_FToA (pbuf, color.rgb.r, eptr);
        *pbuf++ = ' ';
        pbuf = HPDF_FToA (pbuf, color.rgb.g, eptr);
        *pbuf++ = ' ';
        pbuf = HPDF_FToA (pbuf, color.rgb.b, eptr);
        pbuf = (char *)HPDF_StrCpy (pbuf, fill ? " rg" : " RG", eptr);
    } else if (color.cs == HPDF_CS_DEVICE_CMYK) {
        /* CMYK Color Space */
        pbuf = HPDF_FToA (pbuf, color.cmyk.c, eptr);
        *pbuf++ = ' ';
        pbuf = HPDF_FToA (pbuf, color.cmyk.m, eptr);
        *pbuf++ = ' ';
        pbuf = HPDF_FToA (pbuf, color.cmyk.y, eptr);
        *pbuf++ = ' ';
        pbuf = HPDF_FToA (pbuf, color.cmyk.k, eptr);
        pbuf = (char *)HPDF_StrCpy (pbuf, fill ? " k" : " K", eptr);
    }
    return pbuf;
}

static HPDF_Array
InternalAnnotationMatrix  (HPDF_MMgr mmgr,
                           HPDF_REAL width,
                           HPDF_REAL height,
                           HPDF_REAL rotation)
{
    HPDF_Array matrix = HPDF_Array_New (mmgr);
    if (!matrix)
        return NULL;

    HPDF_STATUS ret = HPDF_OK;
    if (rotation == 90) {
        ret += HPDF_Array_AddReal (matrix, 0);
        ret += HPDF_Array_AddReal (matrix, 1);
        ret += HPDF_Array_AddReal (matrix, -1);
        ret += HPDF_Array_AddReal (matrix, 0);
        ret += HPDF_Array_AddReal (matrix, height);
        ret += HPDF_Array_AddReal (matrix, 0);
    } else if (rotation == 180) {
        ret += HPDF_Array_AddReal (matrix, -1);
        ret += HPDF_Array_AddReal (matrix, 0);
        ret += HPDF_Array_AddReal (matrix, 0);
        ret += HPDF_Array_AddReal (matrix, -1);
        ret += HPDF_Array_AddReal (matrix, width);
        ret += HPDF_Array_AddReal (matrix, height);
    } else if (rotation == 270) {
        ret += HPDF_Array_AddReal (matrix, 0);
        ret += HPDF_Array_AddReal (matrix, -1);
        ret += HPDF_Array_AddReal (matrix, 1);
        ret += HPDF_Array_AddReal (matrix, 0);
        ret += HPDF_Array_AddReal (matrix, 0);
        ret += HPDF_Array_AddReal (matrix, width);
    }

    if (ret != HPDF_OK) {
        HPDF_Array_Free (matrix);
        return NULL;
    }

    return matrix;
}

/*
 * Inserts a form radio button field.
 * Parameter:
 * page - The Page on which the radio button field should be inserted
 * pdf - The PDF Document
 * radioField - The radio field to which the radio button belongs
 * left, top, right, bottom - The coordinates of the radio button field
 * value - The value of the radio button field
 * encoder - The encoder which will be used to encode value
 * print - If set, the radio button field will be printed when the page gets printed
 * rotation - The rotation
 * color - The radio button color
 * selected - States if the radio button should be selected
 */
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_RadioButtonField  (HPDF_Page              page,
                             HPDF_Doc               pdf,
                             HPDF_RadioButtonField  radio_field,
                             HPDF_REAL              left,
                             HPDF_REAL              top,
                             HPDF_REAL              right,
                             HPDF_REAL              bottom,
                             const char            *value,
                             HPDF_Encoder           encoder,
                             HPDF_BOOL              print,
                             HPDF_INT               rotation,
                             HPDF_Color             color,
                             HPDF_BOOL              selected)
{
    HPDF_Dict annot;
    HPDF_STATUS ret = HPDF_OK;

    HPDF_PTRACE((" HPDF_Page_RadioButtonField\n"));

    annot = HPDF_Dict_New (page->mmgr);
    if (!annot) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    if (HPDF_Xref_Add (pdf->xref, annot) != HPDF_OK)
        return NULL;

    if (HPDF_RadioButtonField_AddChild (radio_field, annot) != HPDF_OK) {
        HPDF_CheckError (radio_field->error);
        return NULL;
    }

    HPDF_INT opt_idx = HPDF_RadioButtonField_AddOpt (radio_field, value, encoder);
    if (opt_idx == -1) {
        HPDF_CheckError (radio_field->error);
        return NULL;
    }

    char opt_idx_buf[HPDF_INT_LEN + 1];
    HPDF_IToA (opt_idx_buf, opt_idx, opt_idx_buf + HPDF_INT_LEN);

    if (selected) {
        ret += HPDF_RadioButtonField_SetSelected (radio_field, opt_idx_buf);
    }

    ret += HPDF_Dict_AddName (annot, "Type", "Annot");
    ret += HPDF_Dict_AddName (annot, "Subtype", "Widget");

    if (print) {
        ret += HPDF_Dict_AddNumber (annot, "F", 4);
    } else {
        ret += HPDF_Dict_AddNumber (annot, "F", 0);
    }

    // BS
    HPDF_Dict bs = HPDF_Dict_New (page->mmgr);
    if (!bs) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_AddName (bs, "S", "S");
    ret += HPDF_Dict_AddNumber (bs, "W", 1);
    ret += HPDF_Dict_Add (annot, "BS", bs);

    // Rect
    HPDF_Array rectArray = HPDF_Array_New (page->mmgr);
    if (!rectArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (rectArray, left);
    ret += HPDF_Array_AddReal (rectArray, bottom);
    ret += HPDF_Array_AddReal (rectArray, right);
    ret += HPDF_Array_AddReal (rectArray, top);
    ret += HPDF_Dict_Add (annot, "Rect", rectArray);

    // AS
    if (selected) {
        ret += HPDF_Dict_AddName (annot, "AS", opt_idx_buf);
    } else {
        ret += HPDF_Dict_AddName (annot, "AS", "Off");
    }

    HPDF_Font font = HPDF_GetFont (pdf, "ZapfDingbats", NULL);
    if (!font) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    const char *local_name = HPDF_Catalog_GetLocalFontName (pdf->catalog, font);
    if (!local_name) {
        HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);
        return NULL;
    }

    // DA
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);

    pbuf = InternalWriteColorToBuf (pbuf, eptr, color, HPDF_TRUE);
    pbuf = (char *)HPDF_StrCpy (pbuf, " /", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, local_name, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " 0 Tf", eptr);

    HPDF_String daValue = HPDF_String_New(page->mmgr, buf, NULL);
    if (!daValue) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Dict_Add (annot, "DA", daValue);

    // MK
    HPDF_Dict mk = HPDF_Dict_New (page->mmgr);
    if (!mk) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    // /BG
    HPDF_Array bgArray = HPDF_Array_New (page->mmgr);
    if (!bgArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddNumber (bgArray, 1);
    ret += HPDF_Dict_Add (mk, "BG", bgArray);

    // /BC
    HPDF_Array bcArray = HPDF_Array_New (page->mmgr);
    if (!bcArray) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddNumber (bcArray, 0);
    ret += HPDF_Dict_Add (mk, "BC", bcArray);

    if (rotation && rotation != 0 && (rotation % 90) == 0) {
        ret += HPDF_Dict_AddNumber (mk, "R", rotation);
    }

    ret += HPDF_Dict_Add (annot, "MK", mk);

    // AP - APPEARANCE DICTIONARY
    HPDF_Dict ap = HPDF_Dict_New (page->mmgr);
    if (!ap) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    HPDF_Dict n_ap = HPDF_Dict_New (page->mmgr);
    if (!n_ap) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    // /<- value -> appearance stream
    HPDF_Dict selected_stream = HPDF_DictStream_New (page->mmgr, pdf->xref);
    if (!selected_stream) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    char selected_buf[HPDF_TMP_BUF_SIZ];
    pbuf = selected_buf;
    eptr = selected_buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (selected_buf, 0, HPDF_TMP_BUF_SIZ);

    // draw circle
    HPDF_REAL field_width;
    HPDF_REAL field_height;
    if (rotation == 90 || rotation == 270) {
        field_width = fabs(top - bottom);
        field_height = fabs(right - left);
    } else {
        field_width = fabs(right - left);
        field_height = fabs(top - bottom);
    }
    HPDF_REAL circle_dia = field_width < field_height ? field_width : field_height;
    HPDF_REAL circle_ray = circle_dia / 2.0;
    HPDF_REAL circle_x_offset = field_width / 2;
    HPDF_REAL circle_y_offset = field_height / 2;
    circle_ray -= 0.5;

    // draw outer circle
    pbuf = HPDF_FToA (pbuf, 0, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " G\012", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, "1 w\012", eptr);
    pbuf = HPDF_FToA (pbuf, circle_x_offset - circle_ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, circle_y_offset, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " m\012", eptr);

    pbuf = QuarterCircleA (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = QuarterCircleB (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = QuarterCircleC (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = QuarterCircleD (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = (char *)HPDF_StrCpy (pbuf, "s\012", eptr);

    // draw inner dot
    HPDF_REAL dot_ray = (circle_dia / 4.0) - 0.5;
    pbuf = InternalWriteColorToBuf (pbuf, eptr, color, HPDF_TRUE);
    *pbuf++ = '\012';

    pbuf = HPDF_FToA (pbuf, circle_x_offset - dot_ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, circle_y_offset, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " m\012", eptr);

    pbuf = QuarterCircleA (pbuf, eptr, circle_x_offset, circle_y_offset, dot_ray);
    pbuf = QuarterCircleB (pbuf, eptr, circle_x_offset, circle_y_offset, dot_ray);
    pbuf = QuarterCircleC (pbuf, eptr, circle_x_offset, circle_y_offset, dot_ray);
    pbuf = QuarterCircleD (pbuf, eptr, circle_x_offset, circle_y_offset, dot_ray);
    pbuf = (char *)HPDF_StrCpy (pbuf, "f\012", eptr);

    ret += HPDF_Stream_WriteStr (selected_stream->stream, selected_buf);

    HPDF_Array selected_bbox = HPDF_Array_New (page->mmgr);
    if (!selected_bbox) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (selected_bbox, 0);
    ret += HPDF_Array_AddReal (selected_bbox, 0);
    ret += HPDF_Array_AddReal (selected_bbox, field_width);
    ret += HPDF_Array_AddReal (selected_bbox, field_height);
    ret += HPDF_Dict_Add (selected_stream, "BBox", selected_bbox);
    ret += HPDF_Dict_AddName (selected_stream, "Type", "XObject");
    ret += HPDF_Dict_AddName (selected_stream, "Subtype", "Form");

    // Matrix
    if (rotation != 0) {
        HPDF_Array matrix = InternalAnnotationMatrix (page->mmgr, field_width, field_height, rotation);
        if (!matrix) {
            HPDF_CheckError (page->error);
            return NULL;
        }

        ret += HPDF_Dict_Add (selected_stream, "Matrix", matrix);
    }

    // /Off appearance stream
    HPDF_Dict off_stream = HPDF_DictStream_New (page->mmgr, pdf->xref);
    if (!off_stream) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    char off_buf[HPDF_TMP_BUF_SIZ];
    pbuf = off_buf;
    eptr = off_buf + HPDF_TMP_BUF_SIZ - 1;
    HPDF_MemSet (off_buf, 0, HPDF_TMP_BUF_SIZ);

    // draw outer circle
    pbuf = HPDF_FToA (pbuf, 0, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " G\012", eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, "1 w\012", eptr);
    pbuf = HPDF_FToA (pbuf, circle_x_offset - circle_ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, circle_y_offset, eptr);
    pbuf = (char *)HPDF_StrCpy (pbuf, " m\012", eptr);

    pbuf = QuarterCircleA (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = QuarterCircleB (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = QuarterCircleC (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = QuarterCircleD (pbuf, eptr, circle_x_offset, circle_y_offset, circle_ray);
    pbuf = (char *)HPDF_StrCpy (pbuf, "s\012", eptr);

    ret += HPDF_Stream_WriteStr (off_stream->stream, off_buf);

    HPDF_Array off_bbox = HPDF_Array_New (page->mmgr);
    if (!off_bbox) {
        HPDF_CheckError (page->error);
        return NULL;
    }
    ret += HPDF_Array_AddReal (off_bbox, 0);
    ret += HPDF_Array_AddReal (off_bbox, 0);
    ret += HPDF_Array_AddReal (off_bbox, field_width);
    ret += HPDF_Array_AddReal (off_bbox, field_height);
    ret += HPDF_Dict_Add (off_stream, "BBox", off_bbox);
    ret += HPDF_Dict_AddName (off_stream, "Type", "XObject");
    ret += HPDF_Dict_AddName (off_stream, "Subtype", "Form");

    // Matrix
    if (rotation != 0) {
        HPDF_Array matrix = InternalAnnotationMatrix (page->mmgr, field_width, field_height, rotation);
        if (!matrix) {
            HPDF_CheckError (page->error);
            return NULL;
        }

        ret += HPDF_Dict_Add (off_stream, "Matrix", matrix);
    }

    ret += HPDF_Dict_Add (ap, "N", n_ap);
    ret += HPDF_Dict_Add (n_ap, opt_idx_buf, selected_stream);
    ret += HPDF_Dict_Add (n_ap, "Off", off_stream);

    ret += HPDF_Dict_Add (annot, "AP", ap);

    ret += HPDF_Page_CreateFieldAnnotation (page, annot);

    if (ret != HPDF_OK) {
        HPDF_CheckError (page->error);
        return NULL;
    }

    return annot;
}
