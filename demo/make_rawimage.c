/*
 * << Haru Free PDF Library 2.0.0 >> -- make_rawimage.c
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hpdf.h"
#include "handler.h"

#ifdef LIBHPDF_HAVE_LIBPNG

int main (int argc, char **argv)
{
    HPDF_Doc  pdf;
    HPDF_Image image;
    HPDF_Stream stream;

    HPDF_UINT iw;
    HPDF_UINT ih;
    HPDF_UINT bits_per_comp;
    const char *cs;

    if (argc < 2) {
        printf ("usage: make_rawimage <in-file-name> <out-file-name>\n");
        return 1;
    }

    pdf = HPDF_New (demo_error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    /* error-handler */
    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    /* load image file. */
    image = HPDF_LoadPngImageFromFile (pdf, argv[1]);

    iw = HPDF_Image_GetWidth (image);
    ih = HPDF_Image_GetHeight (image);
    bits_per_comp = HPDF_Image_GetBitsPerComponent (image);
    cs = HPDF_Image_GetColorSpace (image);

    printf ("width=%u\n", iw);
    printf ("height=%u\n", ih);
    printf ("bits_per_comp=%u\n", bits_per_comp);
    printf ("color_space=%s\n", cs);

    /* save raw-data to file */
    stream = HPDF_FileWriter_New (pdf->mmgr, argv[2]);
    if (!stream)
        printf ("cannot open %s\n", argv[2]);
    else
        HPDF_Stream_WriteToStream(image->stream, stream, 0, NULL);

    HPDF_Stream_Free (stream);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}

#else

int main()
{
    printf("WARNING: make_rawimage app was not built correctly. \n"
           "Make sure libpng is installed and CMake is able to find it.\n");
    return 0;
}

#endif

