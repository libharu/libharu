#include "hpdf_conf.h"
#include "hpdf_utils.h"
#include "hpdf.h"


HPDF_U3D
HPDF_U3D_LoadU3D  (HPDF_MMgr        mmgr,
				   HPDF_Stream      u3d_data,
				   HPDF_Xref        xref);

static const char u3d[] = "U3D";
static const char prc[] = "PRC";

static HPDF_STATUS Get3DStreamType (HPDF_Stream  stream, const char **type)
{
	HPDF_BYTE tag[4];
	HPDF_UINT len;

	HPDF_PTRACE ((" HPDF_U3D_Get3DStreamType\n"));

	len = 4;
	if (HPDF_Stream_Read (stream, tag, &len) != HPDF_OK) {
		return HPDF_Error_GetCode (stream->error);
	}

	if (HPDF_Stream_Seek (stream, 0, HPDF_SEEK_SET) != HPDF_OK) {
		return HPDF_Error_GetCode (stream->error);
	}

	if (HPDF_MemCmp(tag, (HPDF_BYTE *)u3d, 4/* yes, \0 is required */) == 0) {
		*type = u3d;
		return HPDF_OK;
	}

	if (HPDF_MemCmp(tag, (HPDF_BYTE *)prc, 3) == 0) {
		*type = prc;
		return HPDF_OK;
	}

	return HPDF_INVALID_U3D_DATA;
}


HPDF_EXPORT(HPDF_U3D)
HPDF_U3D_LoadU3DFromMem	(	HPDF_MMgr          mmgr,
							const HPDF_BYTE   *buf,
							HPDF_UINT		   size,
							HPDF_Xref          xref )
{
	HPDF_Dict image;
	HPDF_STATUS ret = HPDF_OK;

	HPDF_PTRACE ((" HPDF_U3D_LoadU3DFromMem\n"));

	image = HPDF_DictStream_New (mmgr, xref);
	if (!image) {
		return NULL;
	}

	image->header.obj_class |= HPDF_OSUBCLASS_XOBJECT;
	ret += HPDF_Dict_AddName (image, "Type", "XObject");
	ret += HPDF_Dict_AddName (image, "Subtype", "Image");
	if (ret != HPDF_OK) {
		return NULL;
	}

	if (HPDF_Stream_Write (image->stream, buf, size) != HPDF_OK) {
		return NULL;
	}

	return image;
}


HPDF_EXPORT(HPDF_Image)
HPDF_LoadU3DFromFile  (HPDF_Doc     pdf,
						const char  *filename)
{
	HPDF_Stream imagedata;
	HPDF_Image image;

	HPDF_PTRACE ((" HPDF_LoadU3DFromFile\n"));

	if (!HPDF_HasDoc (pdf)) {
		return NULL;
	}

	/* create file stream */
	imagedata = HPDF_FileReader_New (pdf->mmgr, filename);

	if (HPDF_Stream_Validate (imagedata)) {
		image = HPDF_U3D_LoadU3D (pdf->mmgr, imagedata, pdf->xref);
	} else {
		image = NULL;
	}

	/* destroy file stream */
	HPDF_Stream_Free (imagedata);

	if (!image) {
		HPDF_CheckError (&pdf->error);
	}
	return image;
}

HPDF_U3D
HPDF_U3D_LoadU3D   (HPDF_MMgr        mmgr,
					HPDF_Stream      u3d_data,
					HPDF_Xref        xref)
{
	HPDF_Dict u3d;
	const char *type;

	HPDF_PTRACE ((" HPDF_U3D_LoadU3D\n"));

	u3d = HPDF_DictStream_New (mmgr, xref);
	if (!u3d) {
		return NULL;
	}

	u3d->header.obj_class |= HPDF_OSUBCLASS_XOBJECT;

	/* add required elements */
	u3d->filter = HPDF_STREAM_FILTER_NONE;

	if (HPDF_Dict_AddName (u3d, "Type", "3D") != HPDF_OK) {
		return NULL;
	}

	if (Get3DStreamType (u3d_data, &type) != HPDF_OK) {
		return NULL;
	}

	if (HPDF_Dict_AddName (u3d, "Subtype", type) != HPDF_OK) {
		return NULL;
	}

	for (;;) {
		HPDF_BYTE buf[HPDF_STREAM_BUF_SIZ];
		HPDF_UINT len = HPDF_STREAM_BUF_SIZ;
		HPDF_STATUS ret = HPDF_Stream_Read (u3d_data, buf, &len);

		if (ret != HPDF_OK) {
			if (ret == HPDF_STREAM_EOF) {
				if (len > 0) {
					ret = HPDF_Stream_Write (u3d->stream, buf, len);
					if (ret != HPDF_OK) {
						return NULL;
					}
				}
				break;
			} else
				return NULL;
		}

		if (HPDF_Stream_Write (u3d->stream, buf, len) != HPDF_OK) {
			return NULL;
		}
	}

	return u3d;
}

