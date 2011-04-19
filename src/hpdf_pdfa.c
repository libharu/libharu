/*
 * << Haru Free PDF Library >> -- hpdf_pdfa.c
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

#include <time.h>
#include "hpdf_utils.h"
#include "hpdf.h"


#define XMP_HEADER "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?><?adobe-xap-filters esc=\"CRLF\"?><x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='XMP toolkit 2.9.1-13, framework 1.6'><rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' xmlns:iX='http://ns.adobe.com/iX/1.0/'>"
#define XMP_FOOTER "</rdf:RDF></x:xmpmeta><?xpacket end='w'?>"
#define XMP_PDFA1A "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='1' pdfaid:conformance='A'/>"
#define XMP_PDFA1B "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='1' pdfaid:conformance='B'/>"
#define XMP_PRODUCER_STARTTAG "<rdf:Description rdf:about='' xmlns:pdf='http://ns.adobe.com/pdf/1.3/' pdf:Producer='"
#define XMP_PRODUCER_ENDTAG "'/>"
#define XMP_INFODATA_STARTTAG "<rdf:Description rdf:about='' xmlns:xmp='http://ns.adobe.com/xap/1.0/'>"
#define XMP_INFODATA_ENDTAG "</rdf:Description>"
#define XMP_CREATE_DATE_STARTTAG "<xmp:CreateDate>"
#define XMP_CREATE_DATE_ENDTAG "</xmp:CreateDate>"
#define XMP_MOD_DATE_STARTTAG "<xmp:ModifyDate>"
#define XMP_MOD_DATE_ENDTAG "</xmp:ModifyDate>"
#define XMP_CREATORTOOL_STARTTAG "<xmp:CreatorTool>"
#define XMP_CREATORTOOL_ENDTAG "</xmp:CreatorTool>"


/* Write XMP Metadata for PDF/A */

HPDF_STATUS
HPDF_PDFA_SetPDFAConformance (HPDF_Doc pdf,HPDF_PDFAType pdfatype)
{
    HPDF_OutputIntent xmp;
    HPDF_STATUS ret;
    const char *info = NULL;
    
    if (!HPDF_HasDoc(pdf)) {
      return HPDF_INVALID_DOCUMENT;
    }
    
    xmp = HPDF_DictStream_New(pdf->mmgr,pdf->xref);
    if (!xmp) {
      return HPDF_INVALID_STREAM;
    }
    
    HPDF_Dict_AddName(xmp,"Type","Metadata");
    HPDF_Dict_AddName(xmp,"SubType","XML");

    ret = HPDF_OK;
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_HEADER);
    
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_PRODUCER_STARTTAG);
   
    info = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_PRODUCER);
    ret += HPDF_Stream_WriteStr(xmp->stream, info);
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_PRODUCER_ENDTAG);
    
    /* Add CreateDate, ModifyDate, and CreatorTool */
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_INFODATA_STARTTAG);
    
    info = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_CREATION_DATE);
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATE_DATE_STARTTAG);    
    ret += HPDF_Stream_WriteStr(xmp->stream, info);
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATE_DATE_ENDTAG);
    
    info = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_MOD_DATE);
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_MOD_DATE_STARTTAG);    
    ret += HPDF_Stream_WriteStr(xmp->stream, info);
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_MOD_DATE_ENDTAG);
    
    info = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_CREATOR);
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATORTOOL_STARTTAG);    
    ret += HPDF_Stream_WriteStr(xmp->stream, info);
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATORTOOL_ENDTAG);
    
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_INFODATA_ENDTAG);
    
    switch(pdfatype) {
      case HPDF_PDFA_1A:
	    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_PDFA1A);
        break;
      case HPDF_PDFA_1B:
	    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_PDFA1B);
        break;
    }
    ret += HPDF_Stream_WriteStr(xmp->stream, XMP_FOOTER);

    if (ret != HPDF_OK) {
      return HPDF_INVALID_STREAM;
    }
    
    if ((ret = HPDF_Dict_Add(pdf->catalog, "Metadata", xmp)) != HPDF_OK) {
      return ret;
    }
    
    return HPDF_PDFA_GenerateID(pdf);
}

/* Generate an ID for the trailer dict, PDF/A needs this. 
   TODO: Better algorithm for generate unique ID.
*/
HPDF_STATUS
HPDF_PDFA_GenerateID(HPDF_Doc pdf)
{
    HPDF_BYTE *currentTime;
    HPDF_BYTE idkey[HPDF_MD5_KEY_LEN];
    HPDF_MD5_CTX md5_ctx;
    time_t ltime; 
    HPDF_Array id;

    ltime = time(NULL); 
    currentTime = (HPDF_BYTE *)ctime(&ltime);
    

    id = HPDF_Dict_GetItem(pdf->trailer, "ID", HPDF_OCLASS_ARRAY);
    if (!id) {
       id = HPDF_Array_New(pdf->mmgr);

       if (!id || HPDF_Dict_Add(pdf->trailer, "ID", id) != HPDF_OK)
	     return pdf->error.error_no;
       
       HPDF_MD5Init(&md5_ctx);
       HPDF_MD5Update(&md5_ctx, (HPDF_BYTE *) "libHaru", sizeof("libHaru") - 1);
       HPDF_MD5Update(&md5_ctx, currentTime, HPDF_StrLen((const char *)currentTime, -1));
       HPDF_MD5Final(idkey, &md5_ctx);
       
       if (HPDF_Array_Add (id, HPDF_Binary_New (pdf->mmgr, idkey, HPDF_MD5_KEY_LEN)) != HPDF_OK)
	     return pdf->error.error_no;

	   if (HPDF_Array_Add (id, HPDF_Binary_New (pdf->mmgr,idkey,HPDF_MD5_KEY_LEN)) != HPDF_OK)
	     return pdf->error.error_no;
	
	   return HPDF_OK;
    }
    
    return HPDF_OK;
}
