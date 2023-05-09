/*
 * << Haru Free PDF Library >> -- hpdf_color_spaces.c
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
#include "hpdf.h"

static const char *COL_CMYK = "DeviceCMYK";
static const char *COL_RGB = "DeviceRGB";
static const char *COL_GRAY = "DeviceGray";

#define ICC_CS_OFFSET 16

HPDF_ColorSpaceObj
HPDF_New_IccBasedSpace (HPDF_MMgr        mmgr,
                        HPDF_UINT        profile_size,
                        unsigned char *  profile_buf,
                        HPDF_UINT *      num_samples,
                        HPDF_ColorSpace *color_space,
                        HPDF_Xref        xref)
{
  HPDF_STATUS ret = HPDF_OK;
  const char *space_name = NULL;
  unsigned long cs_sig = 0x01020304;
  unsigned char *cs_buf = (unsigned char*)&cs_sig;
  HPDF_UINT nSamples = 0;
  HPDF_Dict profile;
  HPDF_Array icc_space;

  HPDF_PTRACE((" HPDF_New_IccBasedSpace\n"));

  if (!profile_size || !profile_buf) {
    HPDF_SetError(mmgr->error, HPDF_INVALID_PROFILE, 0);
    return NULL;
  }

  //Get signature of profile colour space
  if (cs_buf[0] != 0x01) {
    cs_buf[0] = profile_buf[ICC_CS_OFFSET+3];
    cs_buf[1] = profile_buf[ICC_CS_OFFSET+2];
    cs_buf[2] = profile_buf[ICC_CS_OFFSET+1];
    cs_buf[3] = profile_buf[ICC_CS_OFFSET];
  }
  else {
    cs_buf[0] = profile_buf[ICC_CS_OFFSET];
    cs_buf[1] = profile_buf[ICC_CS_OFFSET+1];
    cs_buf[2] = profile_buf[ICC_CS_OFFSET+2];
    cs_buf[3] = profile_buf[ICC_CS_OFFSET+3];
  }

  if (cs_sig == 'RGB ') {
    space_name = COL_RGB;
    nSamples = 3;
    if (color_space) *color_space = HPDF_CS_DEVICE_RGB;
  }
  else if (cs_sig == 'CMYK') {
    space_name = COL_CMYK;
    nSamples = 4;
    if (color_space) *color_space = HPDF_CS_DEVICE_CMYK;
  }
  else if (cs_sig == 'GRAY') {
    space_name = COL_GRAY;
    nSamples = 1;
    if (color_space) *color_space = HPDF_CS_DEVICE_GRAY;
  }
  else  {
    HPDF_SetError(mmgr->error, HPDF_INVALID_COLOR_SPACE, 0);
    return NULL;
  }

  if (num_samples)
    *num_samples = nSamples;

  profile  = HPDF_DictStream_New(mmgr, xref);
  if (!profile)
    return NULL;

  if (HPDF_Dict_AddNumber(profile, "N", nSamples) != HPDF_OK)
    return NULL;

  if (HPDF_Dict_AddName(profile, "Alternate", space_name) != HPDF_OK)
    return NULL;

  if (HPDF_Stream_Write(profile->stream, profile_buf, profile_size) != HPDF_OK)
    return NULL;

    icc_space = HPDF_Array_New(mmgr);
    if (!icc_space)
      return NULL;

    if (HPDF_Array_AddName(icc_space, "ICCBased") != HPDF_OK)
      return NULL;

    if (HPDF_Array_Add(icc_space, profile) != HPDF_OK)
      return NULL;

    HPDF_Xref_Add(xref, icc_space);

  return icc_space;
}

HPDF_LabSpace
HPDF_New_LabSpace (HPDF_MMgr        mmgr,
                   HPDF_REAL        white_x,
                   HPDF_REAL        white_y,
                   HPDF_REAL        white_z,
                   HPDF_Xref        xref)
{
  HPDF_STATUS ret = HPDF_OK;
  HPDF_Dict lab_dict;
  HPDF_Array lab_space;
  HPDF_Array tmp_array;

  HPDF_PTRACE((" HPDF_New_LabSpace\n"));

  lab_dict = HPDF_Dict_New(mmgr);
  if (!lab_dict)
    return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(lab_dict, "BlackPoint", tmp_array) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, -128.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 127.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, -128.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 127.0) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(lab_dict, "Range", tmp_array) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, white_x) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, white_y) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, white_z) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(lab_dict, "WhitePoint", tmp_array) != HPDF_OK) return NULL;

  lab_space = HPDF_Array_New(mmgr);
  if (!lab_space)
    return NULL;

  if (HPDF_Array_AddName(lab_space, "Lab") != HPDF_OK) return NULL;
  if (HPDF_Array_Add(lab_space, lab_dict) != HPDF_OK) return NULL;

  HPDF_Xref_Add(xref, lab_space);

  return lab_space;
}


HPDF_ColorSpaceObj
HPDF_New_SepLabSpace (HPDF_MMgr        mmgr,
                      const char      *sep_name,
                      HPDF_LabSpace    lab_space,
                      HPDF_REAL        sep_L,
                      HPDF_REAL        sep_a,
                      HPDF_REAL        sep_b,
                      HPDF_Xref        xref)
{
  HPDF_STATUS ret = HPDF_OK;
  HPDF_Dict sep_dict;
  HPDF_Array sep_space;
  HPDF_Array tmp_array;

  HPDF_PTRACE((" HPDF_SepLabSpace_Define\n"));

  sep_dict = HPDF_Dict_New(mmgr);
  if (!sep_dict)
    return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, 100.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "C0", tmp_array) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, sep_L) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, sep_a) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, sep_b) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "C1", tmp_array) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddNumber(tmp_array, 0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddNumber(tmp_array, 1) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "Domain", tmp_array) != HPDF_OK) return NULL;

  if (HPDF_Dict_AddNumber(sep_dict, "FunctionType", 2) != HPDF_OK) return NULL;

  if (HPDF_Dict_AddReal(sep_dict, "N", 1.0) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 100.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, -128.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 127.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, -128.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 127.0) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "Range", tmp_array) != HPDF_OK) return NULL;
  sep_space = HPDF_Array_New(mmgr);
  if (!sep_space)
    return NULL;

  if (HPDF_Array_AddName(sep_space, "Separation") != HPDF_OK) return NULL;
  if (HPDF_Array_AddName(sep_space, sep_name) != HPDF_OK) return NULL;
  if (HPDF_Array_Add(sep_space, lab_space) != HPDF_OK) return NULL;
  if (HPDF_Array_Add(sep_space, sep_dict) != HPDF_OK) return NULL;

  HPDF_Xref_Add(xref, sep_space);

  return sep_space;
}


HPDF_ColorSpaceObj
HPDF_New_SepCmykSpace (HPDF_MMgr        mmgr,
                       const char* sep_name,
                       HPDF_REAL        sep_C,
                       HPDF_REAL        sep_M,
                       HPDF_REAL        sep_Y,
                       HPDF_REAL        sep_K,
                       HPDF_Xref        xref)
{
  HPDF_STATUS ret = HPDF_OK;
  HPDF_UINT nSamples = 0;
  HPDF_Dict sep_dict;
  HPDF_Array sep_space;
  HPDF_Array tmp_array;

  HPDF_PTRACE((" HPDF_SepCmykSpace_Define\n"));

  sep_dict = HPDF_Dict_New(mmgr);
  if (!sep_dict)
    return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "C0", tmp_array) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, sep_C) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, sep_M) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, sep_Y) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, sep_K) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "C1", tmp_array) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddNumber(tmp_array, 0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddNumber(tmp_array, 1) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "Domain", tmp_array) != HPDF_OK) return NULL;

  if (HPDF_Dict_AddNumber(sep_dict, "FunctionType", 2) != HPDF_OK) return NULL;

  if (HPDF_Dict_AddReal(sep_dict, "N", 1.0) != HPDF_OK) return NULL;

  tmp_array = HPDF_Array_New(mmgr);
  if (!tmp_array)
    return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 1.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 1.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 1.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 0.0) != HPDF_OK) return NULL;
  if (HPDF_Array_AddReal(tmp_array, 1.0) != HPDF_OK) return NULL;

  if (HPDF_Dict_Add(sep_dict, "Range", tmp_array) != HPDF_OK) return NULL;
  sep_space = HPDF_Array_New(mmgr);
  if (!sep_space)
    return NULL;

  if (HPDF_Array_AddName(sep_space, "Separation") != HPDF_OK) return NULL;
  if (HPDF_Array_AddName(sep_space, sep_name) != HPDF_OK) return NULL;
  if (HPDF_Array_AddName(sep_space, COL_CMYK) != HPDF_OK) return NULL;
  if (HPDF_Array_Add(sep_space, sep_dict) != HPDF_OK) return NULL;

  HPDF_Xref_Add(xref, sep_space);

  return sep_space;
}

