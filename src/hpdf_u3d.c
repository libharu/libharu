#include "hpdf_conf.h"
#include "hpdf_utils.h"
#include "hpdf.h"


HPDF_U3D
HPDF_U3D_LoadU3D  (HPDF_MMgr        mmgr,
				   HPDF_Stream      u3d_data,
				   HPDF_Xref        xref);


static HPDF_STATUS
LoadU3DHeader  (HPDF_U3D     image,
				HPDF_Stream  stream)
{
	HPDF_UINT tag;
	HPDF_UINT len;

	HPDF_PTRACE ((" HPDF_U3D_LoadU3DHeader\n"));

	len = 4;
	if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&tag, &len) != HPDF_OK) {
		return HPDF_Error_GetCode (stream->error);
	}

	if (tag != 0x00443355) {
		return HPDF_INVALID_U3D_DATA;
	}

	return HPDF_OK;
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
HPDF_U3D_LoadU3D  (HPDF_MMgr        mmgr,
				   HPDF_Stream      u3d_data,
				   HPDF_Xref        xref)
{
	HPDF_Dict u3d;
	HPDF_STATUS ret = HPDF_OK;

	HPDF_PTRACE ((" HPDF_U3D_LoadU3D\n"));

	u3d = HPDF_DictStream_New (mmgr, xref);
	if (!u3d) {
		return NULL;
	}

	u3d->header.obj_class |= HPDF_OSUBCLASS_XOBJECT;

	/* add requiered elements */
	u3d->filter = HPDF_STREAM_FILTER_NONE;
	ret += HPDF_Dict_AddName (u3d, "Type", "3D");
	ret += HPDF_Dict_AddName (u3d, "Subtype", "U3D");
	if (ret != HPDF_OK) {
		return NULL;
	}

	if (LoadU3DHeader (u3d, u3d_data) != HPDF_OK) {
		return NULL;
	}

	if (HPDF_Stream_Seek (u3d_data, 0, HPDF_SEEK_SET) != HPDF_OK) {
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

