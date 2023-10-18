/*
 * << Haru Free PDF Library 2.0.8 >> -- hpdf.h
 *
 * URL http://libharu.org/
 *
 * Copyright (c) 1999-2006 Takeshi Kanno
 * Copyright (c) 2023 Dmitry Solomennikov
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#ifndef _HPDF_H
#define _HPDF_H

#include "hpdf_config.h"
#include "hpdf_version.h"

#define HPDF_UNUSED(a) ((void)(a))

#ifdef HPDF_DLL_MAKE
#    define HPDF_EXPORT(A)  __declspec(dllexport) A  __stdcall
#else
#    ifdef HPDF_DLL_MAKE_CDECL
#        define HPDF_EXPORT(A)  __declspec(dllexport) A
#    else
#        ifdef HPDF_SHARED_MAKE
#            define HPDF_EXPORT(A)  extern A
#        endif /* HPDF_SHARED_MAKE */
#    endif /* HPDF_DLL_MAKE_CDECL */
#endif /* HPDF_DLL_MAKE */

#ifdef HPDF_DLL
#    define HPDF_SHARED
#    define HPDF_EXPORT(A)  __declspec(dllimport) A  __stdcall
#    define HPDF_HANDLER(A) A __stdcall
#else
#    ifdef HPDF_DLL_CDECL
#        define HPDF_SHARED
#        define HPDF_EXPORT(A)  __declspec(dllimport) A
#    endif /* HPDF_DLL_CDECL */
#    define HPDF_HANDLER(A) A
#endif /* HPDF_DLL */

#ifdef HPDF_SHARED

#ifndef HPDF_EXPORT
#define HPDF_EXPORT(A) extern A
#endif /* HPDF_EXPORT */

#include "hpdf_consts.h"
#include "hpdf_types.h"

typedef void         *HPDF_HANDLE;
typedef HPDF_HANDLE   HPDF_Boolean;
typedef HPDF_HANDLE   HPDF_Doc;
typedef HPDF_HANDLE   HPDF_Page;
typedef HPDF_HANDLE   HPDF_Pages;
typedef HPDF_HANDLE   HPDF_Stream;
typedef HPDF_HANDLE   HPDF_Image;
typedef HPDF_HANDLE   HPDF_Font;
typedef HPDF_HANDLE   HPDF_Outline;
typedef HPDF_HANDLE   HPDF_Encoder;
typedef HPDF_HANDLE   HPDF_3DMeasure;
typedef HPDF_HANDLE   HPDF_ExData;
typedef HPDF_HANDLE   HPDF_Destination;
typedef HPDF_HANDLE   HPDF_XObject;
typedef HPDF_HANDLE   HPDF_Annotation;
typedef HPDF_HANDLE   HPDF_ExtGState;
typedef HPDF_HANDLE   HPDF_FontDef;
typedef HPDF_HANDLE   HPDF_U3D;
typedef HPDF_HANDLE   HPDF_JavaScript;
typedef HPDF_HANDLE   HPDF_Error;
typedef HPDF_HANDLE   HPDF_MMgr;
typedef HPDF_HANDLE   HPDF_Dict;
typedef HPDF_HANDLE   HPDF_EmbeddedFile;
typedef HPDF_HANDLE   HPDF_OutputIntent;
typedef HPDF_HANDLE   HPDF_Xref;
typedef HPDF_HANDLE   HPDF_Shading;

#else

#ifndef HPDF_EXPORT
#define HPDF_EXPORT(A)  A
#endif /* HPDF_EXPORT  */

#include "hpdf_consts.h"
#include "hpdf_doc.h"
#include "hpdf_error.h"
#include "hpdf_pdfa.h"

#endif /* HPDF_SHARED */

#ifdef __cplusplus
extern "C" {
#endif

HPDF_EXPORT(const char *)
HPDF_GetVersion  (void);

/**

  \ingroup doc
  \brief Create an instance of a document object and initialize it.

  \param user_error_fn User-defined error handler which is invoked when an error occurred.
  \param user_alloc_fn User-defined memory allocation function. If \c NULL is specified, `malloc()` is used.
  \param user_free_fn  User-defined memory freeing function. If \c NULL is specified, `free()` is used.
  \param mem_pool_buf_size \parblock \c libHaru does not use memory pool by default.

  A memory allocation function is called on demand from an application.

  If this parameter set to non-zero value, memory management will be done as following:
  - Memory is allocated per \c mem_pool_buf_size.
  - Memory manager gives memory of requested size to an application, and pools remaining memory to use at next request.
  - If the size of requested memory is larger than the remaining memory, a new memory block is allocated.
  - Unused memory is not released immediately. It is released all together when HPDF_Free() is invoked.
  \endparblock
  \param user_data User-defined void pointer. This pointer is used by error handling.

  \return A handle of document object on success and \c NULL on failure.

  \see
    HPDF_New()
    HPDF_Free()

*/
HPDF_EXPORT(HPDF_Doc)
HPDF_NewEx  (HPDF_Error_Handler   user_error_fn,
             HPDF_Alloc_Func      user_alloc_fn,
             HPDF_Free_Func       user_free_fn,
             HPDF_UINT            mem_pool_buf_size,
             void                *user_data);

/**

  \ingroup doc
  \brief Create an instance of a document object and initialize it.

  \param user_error_fn User-defined error handler which is invoked when an error occurred.
  \param user_data User-defined void pointer. This pointer is used by error handling.

  \return A handle of document object on success and \c NULL on failure.

  \see
    HPDF_NewEx()
    HPDF_Free()

  \note Same as \code{.c}
  HPDF_NewEx(user_error_fn, NULL, NULL, 0, user_data)
  \endcode

*/
HPDF_EXPORT(HPDF_Doc)
HPDF_New  (HPDF_Error_Handler   user_error_fn,
           void                *user_data);

/**

  \ingroup doc
  \brief Set a user-defined error handler for document. If subsequent function calls fail, the error handler is called.

  \copydoc dox_param_pdf
  \param user_error_fn User-defined error handler. If \c NULL, previous error handler is revoked.

  \return \ref HPDF_OK on success, otherwise returns \ref HPDF_INVALID_DOCUMENT.

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetErrorHandler  (HPDF_Doc            pdf,
                       HPDF_Error_Handler  user_error_fn);

/**

  \ingroup doc
  \brief Revoke a document object and all resources.

  \copydoc dox_param_pdf

  \see
    HPDF_New()
    HPDF_NewEx()

*/
HPDF_EXPORT(void)
HPDF_Free  (HPDF_Doc  pdf);

HPDF_EXPORT(HPDF_MMgr)
HPDF_GetDocMMgr  (HPDF_Doc doc);

/**

  \ingroup doc
  \brief Create a new document. If \c doc object already has a document, the current document is revoked.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM

  \see
    HPDF_FreeDoc()

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_NewDoc  (HPDF_Doc  pdf);

/**

  \ingroup doc
  \brief Revoke the current document.

  HPDF_FreeDoc() keeps and recycles loaded resources (such as fonts and encodings) when new document requires these resources.

  \copydoc dox_param_pdf

  \see
    HPDF_NewDoc()
    HPDF_FreeDocAll()

*/
HPDF_EXPORT(void)
HPDF_FreeDoc  (HPDF_Doc  pdf);

/**

  \ingroup doc
  \brief Check if document handle is valid

  \copydoc dox_param_pdf

  \return \ref HPDF_TRUE if the specified document handle is valid. Otherwise return \ref HPDF_FALSE, set error code and call error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT

  \see
    HPDF_NewDoc()

*/
HPDF_EXPORT(HPDF_BOOL)
HPDF_HasDoc  (HPDF_Doc  pdf);


/**

  \ingroup doc
  \brief Revoke the current document.

  HPDF_FreeDocAll() revokes the current document and all resources.

  \copydoc dox_param_pdf

  \see
    HPDF_NewDoc()
    HPDF_FreeDoc()

*/
HPDF_EXPORT(void)
HPDF_FreeDocAll  (HPDF_Doc  pdf);

/**

  \ingroup doc
  \brief Saves the current document to a temporary stream of a document object.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SaveToStream  (HPDF_Doc   pdf);

HPDF_EXPORT(HPDF_STATUS)
HPDF_GetContents   (HPDF_Doc   pdf,
                   HPDF_BYTE  *buf,
                 HPDF_UINT32  *size);

/**

  \ingroup doc
  \brief Gets the size of the temporary stream of the document.

  \copydoc dox_param_pdf

  \return \parblock One of the values:
  - Size of the temporary stream on success.
  - \ref HPDF_FALSE if temporary stream is invalid or document is invalid
  - \ref HPDF_INVALID_DOCUMENT
  \endparblock

  \see
    HPDF_HasDoc()
    HPDF_Stream_Validate()

*/
HPDF_EXPORT(HPDF_UINT32)
HPDF_GetStreamSize  (HPDF_Doc   pdf);

/**

  \ingroup doc
  \brief Copies the data from the temporary stream of the document into buffer \c buf.

  \copydoc dox_param_pdf
  \param buf Pointer to the buffer.
  \param size The size of buffer.
  After HPDF_ReadFromStream() is executed, the number of bytes read is set into \c size.

  \return \ref HPDF_OK or \ref HPDF_STREAM_EOF on success, otherwise, it returns error-code and error-handler is invoked.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_INVALID_OPERATION
  - \ref HPDF_INVALID_PARAMETER

  \note Even if the result of HPDF_ReadFromStream() is \ref HPDF_STREAM_EOF, if the value of \c size parameter is more than 0, data is read into the buffer.

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_ReadFromStream  (HPDF_Doc       pdf,
                      HPDF_BYTE     *buf,
                      HPDF_UINT32   *size);


/**

  \ingroup doc
  \brief Rewind temporary stream of the document.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_INVALID_OPERATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_ResetStream  (HPDF_Doc     pdf);

/**

  \ingroup doc
  \brief Saves the current document to file.

  \copydoc dox_param_pdf
  \param filename The name of file to save.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_FILE_IO_ERROR

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SaveToFile  (HPDF_Doc     pdf,
                  const char  *filename);

/**

  \ingroup error
  \brief Return the last error code of specified document object.

  \copydoc dox_param_pdf

  \return Last error code of document object, or \ref HPDF_OK if no last error.

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_GetError  (HPDF_Doc   pdf);


HPDF_EXPORT(HPDF_STATUS)
HPDF_GetErrorDetail  (HPDF_Doc   pdf);

/**

  \ingroup error
  \brief Cleanup document error

  Once an error code is set, IO processing functions cannot be invoked.
  In case of executing a function after the cause of the error is fixed,
  an application has to invoke HPDF_ResetError() to clear error-code before executing functions.

  \copydoc dox_param_pdf

*/
HPDF_EXPORT(void)
HPDF_ResetError  (HPDF_Doc   pdf);

/**

  \ingroup error
  \brief Check error code

  Function returns error code if it is not equal to \ref HPDF_OK.
  If error code is not equal to \ref HPDF_OK and error handler is set, then error handler is called.

  \param error Error to be checked

  \return Error code from \c error parameter.

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_CheckError  (HPDF_Error   error);

/**

  \ingroup doc
  \brief Specify number of pages `Pages` object can own.

  In the default setting, a \ref HPDF_Doc object has one `Pages` object as root of pages.
  All `Page` objects are created as a child of `Pages` object. Since `Pages` object can
  own only 8191 child objects, the maximum number of pages are 8191 pages. Additionally,
  the case when there are a lot of "Page" object under one "Pages" object is not good,
  since it causes performance degradation of a viewer application.

  An application can change the setting of a pages tree by invoking HPDF_SetPagesConfiguration().
  If `page_per_pages` parameter is set to more than zero, a two-tier pages tree is created.
  A root `Pages` object can own 8191 `Pages` object, and each lower `Pages` object can own
  \c page_per_pages `Page` objects. As a result, the maximum number of pages becomes
  \a 8191 * \a page_per_pages pages. An application cannot invoke HPDF_SetPageConfiguration()
  after a page is added to document.

  \copydoc dox_param_pdf
  \param page_per_pages Numbers of pages `Pages` object can own.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_INVALID_PARAMETER
  - \ref HPDF_INVALID_DOCUMENT_STATE
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetPagesConfiguration  (HPDF_Doc    pdf,
                             HPDF_UINT   page_per_pages);


HPDF_EXPORT(HPDF_Page)
HPDF_GetPageByIndex  (HPDF_Doc    pdf,
                      HPDF_UINT   index);


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

HPDF_EXPORT(HPDF_MMgr)
HPDF_GetPageMMgr    (HPDF_Page  page);

/**

  \ingroup page
  \brief Return page display layout.

  \copydoc dox_param_pdf

  \return Page display layout on success. If page layout is not set, returns \ref HPDF_PAGE_LAYOUT_EOF.

*/
HPDF_EXPORT(HPDF_PageLayout)
HPDF_GetPageLayout  (HPDF_Doc   pdf);

/**

  \ingroup page
  \brief Set page display layout. If attribute is not set, the setting of the viewer application is used.

  \copydoc dox_param_pdf
  \param layout \parblock One of the following values:

    Layout                                 | Description
    -------                                | -----------
    \ref HPDF_PAGE_LAYOUT_SINGLE           | Only one page is displayed
    \ref HPDF_PAGE_LAYOUT_ONE_COLUMN       | Display the pages in one column
    \ref HPDF_PAGE_LAYOUT_TWO_COLUMN_LEFT  | Display in two columns. Odd page number is displayed left
    \ref HPDF_PAGE_LAYOUT_TWO_COLUMN_RIGHT | Display in two columns. Odd page number is displayed right
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_PAGE_LAYOUT_OUT_OF_RANGE

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetPageLayout  (HPDF_Doc          pdf,
                     HPDF_PageLayout   layout);

/**

  \ingroup page
  \brief Return page display mode.

  \copydoc dox_param_pdf

  \return Page display mode on success.

*/
HPDF_EXPORT(HPDF_PageMode)
HPDF_GetPageMode  (HPDF_Doc   pdf);

/**

  \ingroup page
  \brief Set document display mode.

  \copydoc dox_param_pdf
  \param mode \parblock One of the following values:

    Mode                            | Description
    -----                           |-------------
    \ref HPDF_PAGE_MODE_USE_NONE    | Display the document with neither outline nor thumbnail.
    \ref HPDF_PAGE_MODE_USE_OUTLINE | Display the document with outline pane.
    \ref HPDF_PAGE_MODE_USE_THUMBS  | Display the document with thumbnail pane.
    \ref HPDF_PAGE_MODE_FULL_SCREEN | Display the document with full screen mode.
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_PAGE_MODE_OUT_OF_RANGE

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetPageMode  (HPDF_Doc        pdf,
                   HPDF_PageMode   mode);


HPDF_EXPORT(HPDF_UINT)
HPDF_GetViewerPreference  (HPDF_Doc   pdf);


HPDF_EXPORT(HPDF_STATUS)
HPDF_SetViewerPreference  (HPDF_Doc     pdf,
                           HPDF_UINT    value);

/**

  \ingroup page
  \brief Set the first page to appear when a document is opened.

  \copydoc dox_param_pdf
  \param open_action Set a valid destination object.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_PAGE_MODE_OUT_OF_RANGE

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetOpenAction  (HPDF_Doc           pdf,
                     HPDF_Destination   open_action);


/*---------------------------------------------------------------------------*/
/*----- page handling -------------------------------------------------------*/

/**

  \ingroup page
  \brief Get handle of current page object

  \copydoc dox_param_pdf

  \return Current page object on success, otherwise returns \c NULL.

*/
HPDF_EXPORT(HPDF_Page)
HPDF_GetCurrentPage  (HPDF_Doc  pdf);

/**

  \ingroup page
  \brief Create new page and add it after the last page of document

  \copydoc dox_param_pdf

  \return Handle of created page object on success, otherwise, it returns error code and error handler is called.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_Page)
HPDF_AddPage  (HPDF_Doc   pdf);

/**

  \ingroup page
  \brief Create new page and insert it just before specified page.

  \copydoc dox_param_pdf
  \param page Specify page handle object to insert newly created page right before.

  \return Handle of created \ref HPDF_Page object on success, otherwise, returns \c NULL and error-handler is called.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_PAGE - An invalid page handle was set.

*/
HPDF_EXPORT(HPDF_Page)
HPDF_InsertPage  (HPDF_Doc    pdf,
                  HPDF_Page   page);

/**

  \ingroup page
  \brief Add page labeling range for document.

  The page label is shown in the thumbnails view.

  \copydoc dox_param_pdf
  \param page_num First page applies labeling range
  \param style \parblock One of the following numbering styles:

  - \ref HPDF_PAGE_NUM_STYLE_DECIMAL Arabic numerals (1 2 3 4)
  - \ref HPDF_PAGE_NUM_STYLE_UPPER_ROMAN Uppercase roman numerals (I II III IV)
  - \ref HPDF_PAGE_NUM_STYLE_LOWER_ROMAN Lowercase roman numerals (i ii iii iv)
  - \ref HPDF_PAGE_NUM_STYLE_UPPER_LETTERS Uppercase letters (A B C D)
  - \ref HPDF_PAGE_NUM_STYLE_LOWER_LETTERS Lowercase letters (a b c d)
  \endparblock
  \param first_page First page number to use
  \param prefix Prefix for the page label (\c NULL is allowed.)

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM Memory allocation failed.
  - \ref HPDF_PAGE_NUM_STYLE_OUT_OF_RANGE An invalid page numbering style is specified.

  \par Sample
  \code{.c}
  HPDF_AddPageLabel(pdf, 0, HPDF_PAGE_NUM_STYLE_LOWER_ROMAN, 1, "");
  HPDF_AddPageLabel(pdf, 4, HPDF_PAGE_NUM_STYLE_DECIMAL, 1, "");
  HPDF_AddPageLabel(pdf, 7, HPDF_PAGE_NUM_STYLE_DECIMAL, 8, "A-");
  \endcode

  \par Output
  Pages in document will be labeled as follows:

  \verbatim
  i, ii, iii, iv, 1, 2, 3, A-8, A-9, ...
  \endverbatim

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_AddPageLabel  (HPDF_Doc            pdf,
                    HPDF_UINT           page_num,
                    HPDF_PageNumStyle   style,
                    HPDF_UINT           first_page,
                    const char         *prefix);


/**

  \ingroup page
  \brief Change page width.

  \copydoc dox_param_page
  \param value New page width. Valid values are between \c 3 and \c 14400.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_PAGE_INVALID_SIZE
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetWidth  (HPDF_Page   page,
                     HPDF_REAL   value);


/**

  \ingroup page
  \brief Change page height.

  \copydoc dox_param_page
  \param value New page height. Valid values are between \c 3 and \c 14400.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_PAGE_INVALID_SIZE
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetHeight  (HPDF_Page   page,
                      HPDF_REAL   value);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetBoundary  (HPDF_Page           page,
                        HPDF_PageBoundary   boundary,
                        HPDF_REAL           left,
                        HPDF_REAL           bottom,
                        HPDF_REAL           right,
                        HPDF_REAL           top);

/**

  \ingroup page
  \brief Change page size and direction to a predefined ones.

  \copydoc dox_param_page
  \param size Specify a predefined page size value. See \ref _HPDF_PageSizes.
  \param direction Specify the direction of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_PAGE_INVALID_SIZE
  - \ref HPDF_PAGE_INVALID_DIRECTION
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetSize  (HPDF_Page            page,
                    HPDF_PageSizes       size,
                    HPDF_PageDirection   direction);

/**

  \ingroup page
  \brief Set rotation angle of the page.

  \copydoc dox_param_page
  \param angle Specify the rotation angle of the page. It must be a multiple of \c 90 degrees.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_PAGE_INVALID_ROTATE_VALUE

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetRotate  (HPDF_Page     page,
                      HPDF_UINT16   angle);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetZoom  (HPDF_Page     page,
                    HPDF_REAL     zoom);

/*---------------------------------------------------------------------------*/
/*----- font handling -------------------------------------------------------*/

/**

  \ingroup font
  \brief Get requested font object handle.

  \copydoc dox_param_pdf
  \param font_name Valid font name.
  \param encoding_name Valid encoding name.

  \return Font object handle on success, otherwise returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_INVALID_FONT_NAME
  - \ref HPDF_INVALID_ENCODING_NAME
  - \ref HPDF_UNSUPPORTED_FONT_TYPE

  \see \ref fonts, \ref encodings
*/
HPDF_EXPORT(HPDF_Font)
HPDF_GetFont  (HPDF_Doc     pdf,
               const char  *font_name,
               const char  *encoding_name);


/**

  \ingroup font
  \brief Load Type1 font from external file and register it in the document object.

  \copydoc dox_param_pdf
  \param afm_filename Path of AFM file
  \param data_filename Path of PFA/PFB file. If \c NULL, glyph data of font file is not embedded into the PDF file


  \return Name of the font on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_FONT_EXISTS
  - \ref HPDF_INVALID_AFM_HEADER
  - \ref HPDF_INVALID_CHAR_MATRICS_DATA
  - \ref HPDF_INVALID_N_DATA
  - \ref HPDF_UNSUPPORTED_TYPE1_FONT

  \see \ref fonts

*/
HPDF_EXPORT(const char*)
HPDF_LoadType1FontFromFile  (HPDF_Doc     pdf,
                             const char  *afm_filename,
                             const char  *data_filename);


HPDF_EXPORT(HPDF_FontDef)
HPDF_GetTTFontDefFromFile (HPDF_Doc     pdf,
                           const char  *filename,
                           HPDF_BOOL    embedding);
/**

  \ingroup font
  \brief Load TrueType font from external `.ttf` file and register it in the document object.

  \copydoc dox_param_pdf
  \param filename Path of TrueType font file (`.ttf`)
  \param embedding If this parameter is set to \ref HPDF_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file.

  \return Name of the font on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_FONT_EXISTS
  - \ref HPDF_INVALID_TTC_INDEX
  - \ref HPDF_INVALID_TTC_FILE
  - \ref HPDF_TTF_INVALID_CMAP
  - \ref HPDF_TTF_INVALID_FOMAT
  - \ref HPDF_TTF_MISSING_TABLE
  - \ref HPDF_TTF_CANNOT_EMBEDDING_FONT

  \see \ref fonts

*/
HPDF_EXPORT(const char*)
HPDF_LoadTTFontFromFile (HPDF_Doc     pdf,
                         const char  *filename,
                         HPDF_BOOL    embedding);

/**

  \ingroup font
  \brief Load TrueType font from TrueType collection file `*.ttc` and register it in the document object.

  \copydoc dox_param_pdf
  \param filename Path of TrueType font file (`.ttc`)
  \param index Index of font in collection to be loaded.
  \param embedding If this parameter is set to \ref HPDF_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file.

  \return Name of the font on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_FONT_EXISTS
  - \ref HPDF_INVALID_TTC_INDEX
  - \ref HPDF_INVALID_TTC_FILE
  - \ref HPDF_TTF_INVALID_CMAP
  - \ref HPDF_TTF_INVALID_FOMAT
  - \ref HPDF_TTF_MISSING_TABLE
  - \ref HPDF_TTF_CANNOT_EMBEDDING_FONT
  - \ref HPDF_INVALID_TTC_INDEX

  \see \ref fonts, \ref encodings

*/
HPDF_EXPORT(const char*)
HPDF_LoadTTFontFromFile2 (HPDF_Doc     pdf,
                          const char  *filename,
                          HPDF_UINT    index,
                          HPDF_BOOL    embedding);



/**

  \ingroup font
  \brief Enable Japanese fonts. Application can use following Japanese fonts after HPDF_UseJPFonts() call:

  | Font name             |
  | ---------             |
  | MS-Mincyo             |
  | MS-Mincyo,Bold        |
  | MS-Mincyo,Italic      |
  | MS-Mincyo,BoldItalic  |
  | MS-Gothic             |
  | MS-Gothic,Bold        |
  | MS-Gothic,Italic      |
  | MS-Gothic,BoldItalic  |
  | MS-PMincyo            |
  | MS-PMincyo,Bold       |
  | MS-PMincyo,Italic     |
  | MS-PMincyo,BoldItalic |
  | MS-PGothic            |
  | MS-PGothic,Bold       |
  | MS-PGothic,Italic     |
  | MS-PGothic,BoldItalic |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseJPFonts   (HPDF_Doc   pdf);

/**

  \ingroup font
  \brief Enable Korean fonts. Application can use following Korean fonts after HPDF_UseKRFonts() call:
  | Font name            |
  | ---------            |
  | DotumChe             |
  | DotumChe,Bold        |
  | DotumChe,Italic      |
  | DotumChe,BoldItalic  |
  | Dotum                |
  | Dotum,Bold           |
  | Dotum,Italic         |
  | Dotum,BoldItalic     |
  | BatangChe            |
  | BatangChe,Bold       |
  | BatangChe,Italic     |
  | BatangChe,BoldItalic |
  | Batang               |
  | Batang,Bold          |
  | Batang,Italic        |
  | Batang,BoldItalic    |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseKRFonts   (HPDF_Doc   pdf);

/**

  \ingroup font
  \brief Enable simplified Chinese fonts. Application can use following simplified Chinese fonts after HPDF_UseCNSFonts() call:
    | Font name         |
    | ---------         |
    | SimSun            |
    | SimSun,Bold       |
    | SimSun,Italic     |
    | SimSun,BoldItalic |
    | SimHei            |
    | SimHei,Bold       |
    | SimHei,Italic     |
    | SimHei,BoldItalic |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseCNSFonts   (HPDF_Doc   pdf);

/**

  \ingroup font
  \brief Enable traditional Chinese fonts. Application can use following traditional Chinese fonts after HPDF_UseCNTFonts() call:

    | Font name          |
    | ---------          |
    | MingLiU            |
    | MingLiU,Bold       |
    | MingLiU,Italic     |
    | MingLiU,BoldItalic |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseCNTFonts   (HPDF_Doc   pdf);


/*--------------------------------------------------------------------------*/
/*----- outline ------------------------------------------------------------*/

/**

  \ingroup outline
  \brief Create new outline object.

  \copydoc dox_param_pdf
  \param parent Outline object handle which comes to the parent of the created outline object. If \c NULL, the outline is created as a root outline.
  \param title Caption of the outline object.
  \param encoder Encoding object handle applied to the title. If \c NULL, PDFDocEncoding is used.

  \return Created outline object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_OUTLINE

  \todo Clarify which object is returned when encoder is \c NULL

*/
HPDF_EXPORT(HPDF_Outline)
HPDF_CreateOutline  (HPDF_Doc       pdf,
                     HPDF_Outline   parent,
                     const char    *title,
                     HPDF_Encoder   encoder);


/**

  \ingroup outline
  \brief Set whether this outline node is opened when the outline is displayed for the first time.

  \copydoc dox_param_outline
  \param opened Specify whether outline node is opened or not.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_OUTLINE
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Outline_SetOpened  (HPDF_Outline  outline,
                         HPDF_BOOL     opened);


/**

  \ingroup outline
  \brief Set target destination object to jump to when outline object is clicked.

  \copydoc dox_param_outline
  \param dst Destination object handle

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_OUTLINE
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_DESTINATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Outline_SetDestination (HPDF_Outline      outline,
                             HPDF_Destination  dst);


/*--------------------------------------------------------------------------*/
/*----- destination --------------------------------------------------------*/

/**

  \ingroup link
  \brief Create new destination object for the page.

  \copydoc dox_param_page

  \return New destination object handle. If it failed, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_Destination)
HPDF_Page_CreateDestination  (HPDF_Page   page);

/**

  \ingroup link
  \brief Define page appearance with three parameters which are \c left, \c top and \c zoom.

  \copydoc dox_param_dst
  \param left The left coordinate of the page.
  \param top  The top coordinate of the page.
  \param zoom The page magnified factor. Value must be between 0.08 (8%) to 32 (3200%).

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetXYZ  (HPDF_Destination  dst,
                          HPDF_REAL         left,
                          HPDF_REAL         top,
                          HPDF_REAL         zoom);


/**

  \ingroup link
  \brief Set page appearance to display entire page within the window.

  \copydoc dox_param_dst

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFit  (HPDF_Destination  dst);


/**

  \ingroup link
  \brief Define page appearance to fit page width within the window and set top position of the page \c top parameter.

  \copydoc dox_param_dst
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitH  (HPDF_Destination  dst,
                           HPDF_REAL         top);


/**

  \ingroup link
  \brief Define page appearance to fit page height within the window and set left position of the page \c left parameter.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitV  (HPDF_Destination  dst,
                           HPDF_REAL         left);


/**

  \ingroup link
  \brief Define page appearance to fit page within the rectangle specified by \c left, \c bottom, \c right and \c top.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.
  \param bottom Bottom coordinate of the page.
  \param right Right coordinate of the page.
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitR  (HPDF_Destination  dst,
                           HPDF_REAL         left,
                           HPDF_REAL         bottom,
                           HPDF_REAL         right,
                           HPDF_REAL         top);


/**

  \ingroup link
  \brief Define page appearance to fit page bounding box  within the window.

  \copydoc dox_param_dst

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitB  (HPDF_Destination  dst);

/**

  \ingroup link
  \brief Define page appearance to fit page bounding box width within the window and set top position of page to value of \c top parameter.

  \copydoc dox_param_dst
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitBH  (HPDF_Destination  dst,
                            HPDF_REAL         top);


/**

  \ingroup link
  \brief Define page appearance to fit page bounding box height within the window and set left position of page to value of \c left parameter.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DESTINATION
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Destination_SetFitBV  (HPDF_Destination  dst,
                            HPDF_REAL         left);

/*--------------------------------------------------------------------------*/
/*----- encoder ------------------------------------------------------------*/

/**

  \ingroup encode
  \brief Get encoder object handle by specified encoding name.

  \copydoc dox_param_pdf
  \param encoding_name Valid encoding name

  \return Encoder object handle on success, otherwise, it returns \c NULL and call error handler

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_ENCODING_NAME

*/
HPDF_EXPORT(HPDF_Encoder)
HPDF_GetEncoder  (HPDF_Doc     pdf,
                  const char  *encoding_name);

/**

  \ingroup encode
  \brief Get current encoder handle of document object.

  The current encoder is set by invoking HPDF_SetCurrentEncoder() and
  it is used to processing a text when application calls HPDF_Info_SetInfoAttr().

  The default value is \c NULL.

  \copydoc dox_param_pdf

  \return Encoder object handle or \c NULL.

  \see HPDF_Info_SetInfoAttr()
*/
HPDF_EXPORT(HPDF_Encoder)
HPDF_GetCurrentEncoder  (HPDF_Doc   pdf);

/**

  \ingroup encode
  \brief Set current encoder for document

  \copydoc dox_param_pdf
  \param encoding_name Valid encoding name

  \return Encoder object handle on success, otherwise returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_ENCODING_NAME

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetCurrentEncoder  (HPDF_Doc     pdf,
                         const char  *encoding_name);

/**

  \ingroup encode
  \brief Get encoder object type.

  \copydoc dox_param_encoder

  \return Encoder object type value.

  \see \ref _HPDF_EncoderType

*/
HPDF_EXPORT(HPDF_EncoderType)
HPDF_Encoder_GetType  (HPDF_Encoder   encoder);


/**

  \ingroup encode
  \brief Get byte type of a \c text char at \c index position.

  \copydoc dox_param_encoder
  \param text Text to analyze.
  \param index Character index.

  \return Character byte type value.

  \see \ref _HPDF_ByteType

*/
HPDF_EXPORT(HPDF_ByteType)
HPDF_Encoder_GetByteType  (HPDF_Encoder    encoder,
                           const char     *text,
                           HPDF_UINT       index);


/**

  \ingroup encode
  \brief Convert a specified character code to Unicode value.

  \copydoc dox_param_encoder
  \param code Character code to convert.

  \return Character Unicode value.

*/
HPDF_EXPORT(HPDF_UNICODE)
HPDF_Encoder_GetUnicode  (HPDF_Encoder   encoder,
                          HPDF_UINT16    code);

/**

  \ingroup encode
  \brief Get writing mode for the encoding object.

  \copydoc dox_param_encoder

  \return Encoder writing mode value.

  \see \ref _HPDF_WritingMode
*/
HPDF_EXPORT(HPDF_WritingMode)
HPDF_Encoder_GetWritingMode (HPDF_Encoder   encoder);

/**

  \ingroup encode
  \brief Enable Japanese encodings.

  Application can following Japanese encodings after HPDF_UseJPEncodings() call:

  | Encoding     |
  | --------     |
  | 90ms-RKSJ-H  |
  | 90ms-RKSJ-V  |
  | 90msp-RKSJ-H |
  | EUC-H        |
  | EUC-V        |


  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseJPEncodings   (HPDF_Doc   pdf);

/**

  \ingroup encode
  \brief Enable Korean encodings.

  Application can following Korean encodings after HPDF_UseKREncodings() call:

  | Encoding       |
  | --------       |
  | KSC-EUC-H      |
  | KSC-EUC-V      |
  | KSCms-UHC-H    |
  | KSCms-UHC-HW-H |
  | KSCms-UHC-HW-V |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseKREncodings   (HPDF_Doc   pdf);

/**

  \ingroup encode
  \brief Enable simplified Chinese encodings.

  Application can following simplified Chinese encodings after HPDF_UseCNSEncodings() call:

  | Encoding  |
  | --------  |
  | GB-EUC-H  |
  | GB-EUC-V  |
  | GBK-EUC-H |
  | GBK-EUC-V |


  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseCNSEncodings   (HPDF_Doc   pdf);


/**

  \ingroup encode
  \brief Enable traditional Chinese encodings.

  Application can following traditional Chinese encodings after HPDF_UseCNTEncodings() call:

  | Encoding  |
  | --------  |
  | GB-EUC-H  |
  | GB-EUC-V  |
  | GBK-EUC-H |
  | GBK-EUC-V |


  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseCNTEncodings   (HPDF_Doc   pdf);

/**

  \ingroup encode
  \brief Enable UTF-8 encoding.

  Application can include UTF-8 encoded Unicode text (up to 3-byte UTF-8 sequences).

  \note UTF-8 encoding works only with TrueType fonts.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_DUPLICATE_REGISTRATION

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_UseUTFEncodings   (HPDF_Doc   pdf);


/*--------------------------------------------------------------------------*/
/*----- XObject ------------------------------------------------------------*/

HPDF_EXPORT(HPDF_XObject)
HPDF_Page_CreateXObjectFromImage    (HPDF_Doc       pdf,
                                     HPDF_Page      page,
                                     HPDF_Rect      rect,
                                     HPDF_Image     image,
                                     HPDF_BOOL      zoom);

HPDF_EXPORT(HPDF_XObject)
HPDF_Page_CreateXObjectAsWhiteRect  (HPDF_Doc   pdf,
                                     HPDF_Page  page,
                                     HPDF_Rect  rect);

/*--------------------------------------------------------------------------*/
/*----- annotation ---------------------------------------------------------*/

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_Create3DAnnot    (HPDF_Page       page,
                            HPDF_Rect       rect,
                            HPDF_BOOL       tb,
                            HPDF_BOOL       np,
                            HPDF_U3D        u3d,
                            HPDF_Image      ap);

/**

  \ingroup link
  \brief Create new text annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle where annotation is displayed.
  \param text Text to be displayed.
  \param encoder Encoder handle which is used to encode text. If it is \c NULL, PDFDocEncoding is used.

  \return New annotation object handle. If it failed, it returns \c NULL.

  \todo Clarify what PDFDocEncoding is.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_ENCODER

*/
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateTextAnnot  (HPDF_Page       page,
                            HPDF_Rect       rect,
                            const char     *text,
                            HPDF_Encoder    encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateFreeTextAnnot  (HPDF_Page       page,
                                HPDF_Rect       rect,
                                const char     *text,
                                HPDF_Encoder    encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateLineAnnot  (HPDF_Page       page,
                            const char     *text,
                            HPDF_Encoder    encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint (HPDF_Doc   pdf,
                                                 HPDF_Page  page,
                                                 HPDF_Rect  rect);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateWidgetAnnot (HPDF_Page  page,
                             HPDF_Rect  rect);

/**

  \ingroup link
  \brief Create new link annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle clickable area.
  \param dst Handle of destination object to jump to.

  \return New annotation object handle. If it fails, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_DESTINATION

*/
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateLinkAnnot  (HPDF_Page          page,
                            HPDF_Rect          rect,
                            HPDF_Destination   dst);


/**

  \ingroup link
  \brief Create new web link annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle of clickable area.
  \param uri Destination URI to jump to.

  \return New annotation object handle. If it fails, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateURILinkAnnot  (HPDF_Page     page,
                               HPDF_Rect     rect,
                               const char   *uri);


HPDF_Annotation
HPDF_Page_CreateTextMarkupAnnot  (HPDF_Page        page,
                                  HPDF_Rect        rect,
                                  const char      *text,
                                  HPDF_Encoder     encoder,
                                  HPDF_AnnotType   subType);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateHighlightAnnot  (HPDF_Page      page,
                                 HPDF_Rect      rect,
                                 const char    *text,
                                 HPDF_Encoder   encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateUnderlineAnnot  (HPDF_Page      page,
                                 HPDF_Rect      rect,
                                 const char    *text,
                                 HPDF_Encoder   encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateSquigglyAnnot  (HPDF_Page      page,
                                HPDF_Rect      rect,
                                const char    *text,
                                HPDF_Encoder   encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateStrikeOutAnnot  (HPDF_Page      page,
                                 HPDF_Rect      rect,
                                 const char    *text,
                                 HPDF_Encoder   encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreatePopupAnnot  (HPDF_Page         page,
                             HPDF_Rect         rect,
                             HPDF_Annotation   parent);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateStampAnnot  (HPDF_Page             page,
                             HPDF_Rect             rect,
                             HPDF_StampAnnotName   name,
                             const char           *text,
                             HPDF_Encoder          encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateProjectionAnnot  (HPDF_Page      page,
                                  HPDF_Rect      rect,
                                  const char    *text,
                                  HPDF_Encoder   encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateSquareAnnot  (HPDF_Page      page,
                              HPDF_Rect      rect,
                              const char    *text,
                              HPDF_Encoder   encoder);

HPDF_EXPORT(HPDF_Annotation)
HPDF_Page_CreateCircleAnnot  (HPDF_Page      page,
                              HPDF_Rect      rect,
                              const char    *text,
                              HPDF_Encoder   encoder);

/**

  \ingroup link
  \brief Define link annotation mouse click appearance.

  \copydoc dox_param_annot
  \param mode Link annotation highlight mode.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_FAILD_TO_ALLOC_MEM

  \see _HPDF_AnnotHighlightMode
*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_LinkAnnot_SetHighlightMode  (HPDF_Annotation           annot,
                                  HPDF_AnnotHighlightMode   mode);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LinkAnnot_SetJavaScript  (HPDF_Annotation   annot,
                               HPDF_JavaScript   javascript);

/**

  \ingroup link
  \brief Define link annotation border style.

  \copydoc dox_param_annot
  \param width Annotation border width
  \param dash_on, dash_off Dash style parameters

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_INVALID_PARAMETER
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_LinkAnnot_SetBorderStyle  (HPDF_Annotation   annot,
                                HPDF_REAL         width,
                                HPDF_UINT16       dash_on,
                                HPDF_UINT16       dash_off);


/**

  \ingroup link
  \brief Define link annotation icon.

  \copydoc dox_param_annot
  \param icon Link annotation icon type.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_ANNOT_INVALID_ICON
  - \ref HPDF_FAILD_TO_ALLOC_MEM

  \see _HPDF_AnnotIcon

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_TextAnnot_SetIcon  (HPDF_Annotation   annot,
                         HPDF_AnnotIcon    icon);


/**

  \ingroup link
  \brief Define whether link annotation is initially opened.

  \copydoc dox_param_annot
  \param opened \ref HPDF_TRUE if annotation initially displayed open.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_TextAnnot_SetOpened  (HPDF_Annotation   annot,
                          HPDF_BOOL          opened);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetRGBColor  (HPDF_Annotation   annot,
                         HPDF_RGBColor     color);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetCMYKColor  (HPDF_Annotation   annot,
                          HPDF_CMYKColor    color);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetGrayColor  (HPDF_Annotation   annot,
                          HPDF_REAL         color);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_SetNoColor  (HPDF_Annotation annot);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetTitle  (HPDF_Annotation   annot,
                            const char       *name);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetSubject  (HPDF_Annotation   annot,
                              const char       *name);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetCreationDate  (HPDF_Annotation   annot,
                                   HPDF_Date         value);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetTransparency  (HPDF_Annotation   annot,
                                   HPDF_REAL         value);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetIntent  (HPDF_Annotation    annot,
                             HPDF_AnnotIntent   intent);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetPopup  (HPDF_Annotation   annot,
                            HPDF_Annotation   popup);

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetRectDiff (HPDF_Annotation   annot,
                              HPDF_Rect         rect); /* RD entry */

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetCloudEffect (HPDF_Annotation   annot,
                                 HPDF_INT          cloudIntensity); /* BE entry */

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorRGBColor  (HPDF_Annotation   annot,
                                       HPDF_RGBColor     color); /* IC with RGB entry */

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorCMYKColor  (HPDF_Annotation   annot,
                                        HPDF_CMYKColor    color); /* IC with CMYK entry */

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorGrayColor  (HPDF_Annotation   annot,
                                        HPDF_REAL         color); /* IC with Gray entry */

HPDF_EXPORT(HPDF_STATUS)
HPDF_MarkupAnnot_SetInteriorTransparent  (HPDF_Annotation   annot); /* IC with No Color entry */

HPDF_EXPORT(HPDF_STATUS)
HPDF_TextMarkupAnnot_SetQuadPoints  (HPDF_Annotation   annot,
                                     HPDF_Point        lb,
                                     HPDF_Point        rb,
                                     HPDF_Point        rt,
                                     HPDF_Point        lt); /* l-left, r-right, b-bottom, t-top positions */

HPDF_EXPORT(HPDF_STATUS)
HPDF_Annot_Set3DView  (HPDF_MMgr        mmgr,
                       HPDF_Annotation  annot,
                       HPDF_Annotation  annot3d,
                       HPDF_Dict        view);

HPDF_EXPORT(HPDF_STATUS)
HPDF_PopupAnnot_SetOpened  (HPDF_Annotation   annot,
                            HPDF_BOOL         opened);

HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_SetLineEndingStyle  (HPDF_Annotation annot, HPDF_LineAnnotEndingStyle startStyle, HPDF_LineAnnotEndingStyle endStyle);

HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_Set3PointCalloutLine  (HPDF_Annotation   annot,
                                          HPDF_Point        startPoint,
                                          HPDF_Point        kneePoint,
                                          HPDF_Point        endPoint); /* Callout line will be in default user space */

HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_Set2PointCalloutLine  (HPDF_Annotation   annot,
                                          HPDF_Point        startPoint,
                                          HPDF_Point        endPoint); /* Callout line will be in default user space */

HPDF_EXPORT(HPDF_STATUS)
HPDF_FreeTextAnnot_SetDefaultStyle  (HPDF_Annotation   annot,
                                     const char*       style);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LineAnnot_SetPosition  (HPDF_Annotation             annot,
                             HPDF_Point                  startPoint,
                             HPDF_LineAnnotEndingStyle   startStyle,
                             HPDF_Point                  endPoint,
                             HPDF_LineAnnotEndingStyle   endStyle);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LineAnnot_SetLeader  (HPDF_Annotation   annot,
                           HPDF_INT          leaderLen,
                           HPDF_INT          leaderExtLen,
                           HPDF_INT          leaderOffsetLen);

HPDF_EXPORT(HPDF_STATUS)
HPDF_LineAnnot_SetCaption  (HPDF_Annotation             annot,
                            HPDF_BOOL                   showCaption,
                            HPDF_LineAnnotCapPosition   position,
                            HPDF_INT                    horzOffset,
                            HPDF_INT                    vertOffset);

/**

  \ingroup link
  \brief Define text annotation border appearance.

  \copydoc dox_param_annot
  \param subtype Border style subtype. See \ref _HPDF_BSSubtype.
  \param width Annotation border width
  \param dash_on, dash_off, dash_phase Dash style

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_ANNOTATION
  - \ref HPDF_FAILD_TO_ALLOC_MEM

  \see _HPDF_BSSubtype

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Annotation_SetBorderStyle  (HPDF_Annotation   annot,
                                 HPDF_BSSubtype    subtype,
                                 HPDF_REAL         width,
                                 HPDF_UINT16       dash_on,
                                 HPDF_UINT16       dash_off,
                                 HPDF_UINT16       dash_phase);

HPDF_EXPORT(HPDF_STATUS)
HPDF_ProjectionAnnot_SetExData(HPDF_Annotation annot, HPDF_ExData exdata);


/*--------------------------------------------------------------------------*/
/*----- 3D Measure ---------------------------------------------------------*/
HPDF_EXPORT(HPDF_3DMeasure)
HPDF_Page_Create3DC3DMeasure  (HPDF_Page      page,
                               HPDF_Point3D   firstanchorpoint,
                               HPDF_Point3D   textanchorpoint);

HPDF_EXPORT(HPDF_3DMeasure)
HPDF_Page_CreatePD33DMeasure  (HPDF_Page      page,
                               HPDF_Point3D   annotationPlaneNormal,
                               HPDF_Point3D   firstAnchorPoint,
                               HPDF_Point3D   secondAnchorPoint,
                               HPDF_Point3D   leaderLinesDirection,
                               HPDF_Point3D   measurementValuePoint,
                               HPDF_Point3D   textYDirection,
                               HPDF_REAL      value,
                               const char    *unitsString);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DMeasure_SetName  (HPDF_3DMeasure   measure,
                         const char      *name);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DMeasure_SetColor  (HPDF_3DMeasure   measure,
                          HPDF_RGBColor    color);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DMeasure_SetTextSize  (HPDF_3DMeasure   measure,
                             HPDF_REAL        textsize);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DC3DMeasure_SetTextBoxSize  (HPDF_3DMeasure   measure,
                                   HPDF_INT32       x,
                                   HPDF_INT32       y);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DC3DMeasure_SetText  (HPDF_3DMeasure   measure,
                            const char      *text,
                            HPDF_Encoder     encoder);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DC3DMeasure_SetProjectionAnotation  (HPDF_3DMeasure    measure,
                                           HPDF_Annotation   projectionanotation);

/*--------------------------------------------------------------------------*/
/*----- External Data ---------------------------------------------------------*/

HPDF_EXPORT(HPDF_ExData)
HPDF_Page_Create3DAnnotExData  (HPDF_Page   page);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DAnnotExData_Set3DMeasurement  (HPDF_ExData      exdata,
                                      HPDF_3DMeasure   measure);

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*----- 3D View ---------------------------------------------------------*/

HPDF_EXPORT(HPDF_Dict)
HPDF_Page_Create3DView  (HPDF_Page         page,
                         HPDF_U3D          u3d,
                         HPDF_Annotation   annot3d,
                         const char       *name);

HPDF_EXPORT(HPDF_STATUS)
HPDF_3DView_Add3DC3DMeasure  (HPDF_Dict        view,
                              HPDF_3DMeasure   measure);

/*--------------------------------------------------------------------------*/
/*----- image data ---------------------------------------------------------*/

/**

  \ingroup image
  \brief Load PNG image from buffer.

  \copydoc dox_param_pdf
  \param buf Pointer to the image data.
  \param size Size of the data in buffer.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_PNG_IMAGE

*/
HPDF_EXPORT(HPDF_Image)
HPDF_LoadPngImageFromMem  (HPDF_Doc           pdf,
                           const HPDF_BYTE   *buf,
                           HPDF_UINT          size);

/**

  \ingroup image
  \brief Load external PNG image file.

  \copydoc dox_param_pdf
  \param filename Path to PNG image file.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_UNSUPPORTED_FUNC
  - \ref HPDF_LIBPNG_ERROR
  - \ref HPDF_INVALID_PNG_IMAGE

*/
HPDF_EXPORT(HPDF_Image)
HPDF_LoadPngImageFromFile (HPDF_Doc      pdf,
                           const char    *filename);

/**

  \ingroup image
  \brief Load external PNG image file.

  Unlike HPDF_LoadPngImageFromFile(), HPDF_LoadPngImageFromFile2() does not load
  all the data immediately (only size and color properties are loaded).
  The main data are loaded just before the image object is written to PDF, and then loaded data is deleted.

  \copydoc dox_param_pdf
  \param filename Path to PNG image file.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_UNSUPPORTED_FUNC
  - \ref HPDF_LIBPNG_ERROR
  - \ref HPDF_INVALID_PNG_IMAGE

*/
HPDF_EXPORT(HPDF_Image)
HPDF_LoadPngImageFromFile2 (HPDF_Doc      pdf,
                            const char    *filename);


/**

  \ingroup image
  \brief Load external JPEG image file.

  \copydoc dox_param_pdf
  \param filename Path to JPEG image file.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_JPEG_DATA
  - \ref HPDF_UNSUPPORTED_JPEG_FORMAT

  \see HPDF_LoadJpegImageFromMem()

*/
HPDF_EXPORT(HPDF_Image)
HPDF_LoadJpegImageFromFile (HPDF_Doc      pdf,
                            const char    *filename);
/**
  \ingroup image
  \brief Load JPEG image from buffer.

  \copydoc dox_param_pdf
  \param buf Pointer to the image data.
  \param size Size of the data in buffer.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_JPEG_DATA
  - \ref HPDF_UNSUPPORTED_JPEG_FORMAT

  \see HPDF_LoadJpegImageFromFile()

*/
HPDF_EXPORT(HPDF_Image)
HPDF_LoadJpegImageFromMem   (HPDF_Doc      pdf,
                      const HPDF_BYTE     *buf,
                            HPDF_UINT      size);

HPDF_EXPORT(HPDF_Image)
HPDF_LoadU3DFromFile (HPDF_Doc     pdf,
                    const char    *filename);

HPDF_EXPORT(HPDF_Image)
HPDF_LoadU3DFromMem  (HPDF_Doc      pdf,
               const HPDF_BYTE     *buffer,
                     HPDF_UINT      size);

HPDF_EXPORT(HPDF_Image)
HPDF_Image_LoadRaw1BitImageFromMem ( HPDF_Doc          pdf,
                              const HPDF_BYTE         *buf,
                                    HPDF_UINT          width,
                                    HPDF_UINT          height,
                                    HPDF_UINT          line_width,
                                    HPDF_BOOL          black_is1,
                                    HPDF_BOOL          top_is_first);

/**

  \ingroup image
  \brief Load raw format image.

  This function loads image data from file without any conversion, it is usually faster than the other functions.

  \copydoc dox_param_pdf
  \param filename Path to image file
  \param width Width of image file
  \param height Height of image file
  \param color_space One of \ref HPDF_CS_DEVICE_GRAY, \ref HPDF_CS_DEVICE_RGB or \ref HPDF_CS_DEVICE_CMYK values.

  \return Image object handle on success, otherwise, it returns \c NULL and call error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_COLOR_SPACE
  - \ref HPDF_INVALID_IMAGE
  - \ref HPDF_FILE_IO_ERROR

  \see \ref colorspaces, HPDF_LoadRawImageFromMem()
*/
HPDF_EXPORT(HPDF_Image)
HPDF_LoadRawImageFromFile  (HPDF_Doc          pdf,
                            const char       *filename,
                            HPDF_UINT         width,
                            HPDF_UINT         height,
                            HPDF_ColorSpace   color_space);

/**

  \ingroup image
  \brief Load raw format image.

  This function loads image data from buffer without any conversion, it is usually faster than the other functions.

  \copydoc dox_param_pdf
  \param buf Pointer to image data
  \param width Width of image file
  \param height Height of image file
  \param color_space One of \ref HPDF_CS_DEVICE_GRAY, \ref HPDF_CS_DEVICE_RGB or \ref HPDF_CS_DEVICE_CMYK values.
  \param bits_per_component Bit size of each color component. Valid values are \a 1, \a 2, \a 4 and \a 8.

  \return Image object handle on success, otherwise, it returns \c NULL and call error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_COLOR_SPACE
  - \ref HPDF_INVALID_IMAGE

  \see \ref colorspaces, HPDF_LoadRawImageFromFile()

*/
HPDF_EXPORT(HPDF_Image)
HPDF_LoadRawImageFromMem  (HPDF_Doc           pdf,
                           const HPDF_BYTE   *buf,
                           HPDF_UINT          width,
                           HPDF_UINT          height,
                           HPDF_ColorSpace    color_space,
                           HPDF_UINT          bits_per_component);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Image_AddSMask  (HPDF_Image    image,
                      HPDF_Image    smask);

/**

  \ingroup image
  \brief Get size of the image of an image object.

  \copydoc dox_param_image

  \return \ref HPDF_Point structure which includes image size, otherwise it returns `HPDF_Point{0, 0}`.

*/
HPDF_EXPORT(HPDF_Point)
HPDF_Image_GetSize (HPDF_Image  image);


/**

  \ingroup image
  \brief Get size of the image of an image object to parameter.

  In contrast with HPDF_Image_GetWidth() this function returns \ref HPDF_OK on success and writes size value to \c size parameter.

  \copydoc dox_param_image
  \param size Variable to return size of image to.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_IMAGE

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Image_GetSize2 (HPDF_Image  image, HPDF_Point *size);

/**

  \ingroup image
  \brief Get image width of an image object.

  \copydoc dox_param_image

  \return Image width on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Image_GetWidth  (HPDF_Image   image);

/**

  \ingroup image
  \brief Get image height of an image object.

  \copydoc dox_param_image

  \return Image height on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Image_GetHeight  (HPDF_Image   image);

/**

  \ingroup image
  \brief Get bit count used to describe each color component.

  \copydoc dox_param_image

  \return Bit count on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Image_GetBitsPerComponent (HPDF_Image  image);

/**

  \ingroup image
  \brief Get image color space name.

  \copydoc dox_param_image

  \return Color space name on success, otherwise it returns \c NULL.

  \see \ref colorspaces

*/
HPDF_EXPORT(const char*)
HPDF_Image_GetColorSpace (HPDF_Image  image);

/**

  \ingroup image
  \brief Sets transparent color of the image by the RGB range values.

  The color within the range is displayed as a transparent color. The \c image must have RGB color space.

  \copydoc dox_param_image
  \param rmin, rmax Lower and upper limits of red color. Must be in a range \c 0 and \c 255.
  \param gmin, gmax Lower and upper limits of green color. Must be in a range \c 0 and \c 255.
  \param bmin, bmax Lower and upper limits of blue color. Must be in a range \c 0 and \c 255.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_IMAGE
  - \ref HPDF_INVALID_COLOR_SPACE
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_PARAMETER

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Image_SetColorMask (HPDF_Image   image,
                         HPDF_UINT    rmin,
                         HPDF_UINT    rmax,
                         HPDF_UINT    gmin,
                         HPDF_UINT    gmax,
                         HPDF_UINT    bmin,
                         HPDF_UINT    bmax);


/**

  \ingroup image
  \brief Set image mask

  \copydoc dox_param_image
  \param mask_image Specify image object handle which is used as image mask. This image must be 1-bit gray-scale color image.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_IMAGE
  - \ref HPDF_INVALID_BIT_PER_COMPONENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Image_SetMaskImage  (HPDF_Image   image,
                          HPDF_Image   mask_image);


/*--------------------------------------------------------------------------*/
/*----- info dictionary ----------------------------------------------------*/

/**

  \ingroup prop
  \brief Set the text of \c info dictionary attribute using current encoding of the document.
  If encoding is not set, PDFDocEncoding is used.

  \todo Clarify what PDFDocEncoding is.

  \copydoc dox_param_pdf
  \param type \parblock One of the following values:
    - \ref HPDF_INFO_AUTHOR
    - \ref HPDF_INFO_CREATOR
    - \ref HPDF_INFO_TITLE
    - \ref HPDF_INFO_SUBJECT
    - \ref HPDF_INFO_KEYWORDS
    \endparblock
  \param value Attribute text to be set.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

    - \ref HPDF_INVALID_DOCUMENT
    - \ref HPDF_FAILD_TO_ALLOC_MEM
    - \ref HPDF_INVALID_PARAMETER

  \see HPDF_GetInfoAttr(), HPDF_SetInfoDateAttr()

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetInfoAttr (HPDF_Doc        pdf,
                  HPDF_InfoType   type,
                  const char     *value);

/**

  \ingroup prop
  \brief Get attribute value from \c info dictionary.

  \copydoc dox_param_pdf
  \param type \parblock One of the following values:
    - \ref HPDF_INFO_CREATION_DATE
    - \ref HPDF_INFO_MOD_DATE
    - \ref HPDF_INFO_AUTHOR
    - \ref HPDF_INFO_CREATOR
    - \ref HPDF_INFO_TITLE
    - \ref HPDF_INFO_SUBJECT
    - \ref HPDF_INFO_KEYWORDS
    \endparblock

  \return String value from \c info dictionary. If the infomation has not been set or an error has occurred, it returns \c NULL.

  \copydoc dox_error_codes

    - \ref HPDF_INVALID_DOCUMENT
    - \ref HPDF_FAILD_TO_ALLOC_MEM
    - \ref HPDF_INVALID_PARAMETER

  \see HPDF_SetInfoAttr(), HPDF_SetInfoDateAttr()

*/
HPDF_EXPORT(const char*)
HPDF_GetInfoAttr (HPDF_Doc        pdf,
                  HPDF_InfoType   type);

/**

  \ingroup prop
  \brief Set datetime attribute at \c info dictionary.

  \copydoc dox_param_pdf
  \param type \parblock One of the following attributes:
    - \ref HPDF_INFO_CREATION_DATE
    - \ref HPDF_INFO_MOD_DATE
    \endparblock
  \param value New attribute value

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_INVALID_PARAMETER
  - \ref HPDF_INVALID_DATE_TIME

  \see HPDF_GetInfoAttr(), HPDF_SetInfoAttr(), \ref _HPDF_Date
*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetInfoDateAttr (HPDF_Doc        pdf,
                      HPDF_InfoType   type,
                      HPDF_Date       value);


/*--------------------------------------------------------------------------*/
/*----- encryption ---------------------------------------------------------*/

/**

  \ingroup security
  \brief Sets a password for the document. If the password is set, document contents is encrypted.

  \copydoc dox_param_pdf
  \param owner_password Owner password of the document. The owner can change document permission. \c NULL, zero-length string and the same value as user password are not allowed.
  \param user_password User password of the document. The \c user_password may be set to \c NULL or zero-length string.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_ENCRYPT_INVALID_PASSWORD

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetPassword  (HPDF_Doc      pdf,
                   const char   *owner_password,
                   const char   *user_password);

/**

  \ingroup security
  \brief Set the permission flags for the document.

  \copydoc dox_param_pdf
  \param permission \parblock One or more of the following values, combined together using binary \c OR:
  | Permission                | Description                                                                        |
  | ----------                | -----------                                                                        |
  | \ref HPDF_ENABLE_READ     | User can read the document.                                                        |
  | \ref HPDF_ENABLE_PRINT    | User can print the document.                                                       |
  | \ref HPDF_ENABLE_EDIT_ALL | User can edit the contents of the document other than annotations and form fields. |
  | \ref HPDF_ENABLE_COPY     | User can copy the text and the graphics of the document.                           | 
  | \ref HPDF_ENABLE_EDIT     | User can add or modify the annotations and form fields of the document.            |
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetPermission  (HPDF_Doc    pdf,
                     HPDF_UINT   permission);

/**

  \ingroup security
  \brief Set the encryption mode. As the side effect, ups the version of PDF to 1.4 when the mode is set to \ref HPDF_ENCRYPT_R3.

  \copydoc dox_param_pdf
  \param mode \parblock One of the following values:
  | Mode                 | Description                                                                    |
  | ----                 | -----------                                                                    |
  | \ref HPDF_ENCRYPT_R2 | Use "Revision 2" algorithm.<br/>\c key_len automatically set to 5 (40 bits).   |
  | \ref HPDF_ENCRYPT_R3 | Use "Revision 3" algorithm.<br/>\c key_len can be 5 (40 bits) to 16 (128bits). |
  \endparblock

  \param key_len Specify byte length of encryption key. Only valid for \ref HPDF_ENCRYPT_R3, length between 5 (40 bits) and 16 (128 bits) can be specified.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_INVALID_ENCRYPT_KEY_LEN
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetEncryptionMode  (HPDF_Doc           pdf,
                         HPDF_EncryptMode   mode,
                         HPDF_UINT          key_len);


/*--------------------------------------------------------------------------*/
/*----- compression --------------------------------------------------------*/

/**

  \ingroup security
  \brief Set compression mode.

  \copydoc dox_param_pdf
  \param mode \parblock One or more of the following values, combined together using binary \c OR:
  | Mode                    | Description                                                 |
  | ----                    | -----------                                                 |
  | \ref HPDF_COMP_NONE     | No compression                                              |
  | \ref HPDF_COMP_TEXT     | Compress the contents stream of the page                    |
  | \ref HPDF_COMP_IMAGE    | Compress the streams of the image objects.                  |
  | \ref HPDF_COMP_METADATA | Other stream datas (fonts, cmaps and so on) are compressed. |
  | \ref HPDF_COMP_ALL      | All stream datas are compressed <br/>(combination of \ref HPDF_COMP_TEXT, \ref HPDF_COMP_IMAGE and \ref HPDF_COMP_METADATA). |
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_DOCUMENT
  - \ref HPDF_INVALID_COMPRESSION_MODE
  - \ref HPDF_FAILD_TO_ALLOC_MEM

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_SetCompressionMode  (HPDF_Doc    pdf,
                          HPDF_UINT   mode);


/*--------------------------------------------------------------------------*/
/*----- font ---------------------------------------------------------------*/

/**

  \ingroup font
  \brief Get name of the font.

  \copydoc dox_param_font

  \return Font name on success, otherwise returns \c NULL

*/
HPDF_EXPORT(const char*)
HPDF_Font_GetFontName  (HPDF_Font    font);


/**

  \ingroup font
  \brief Get encoding name of the font.

  \copydoc dox_param_font

  \return Font encoding name on success, otherwise returns \c NULL

*/
HPDF_EXPORT(const char*)
HPDF_Font_GetEncodingName  (HPDF_Font    font);


/**

  \ingroup font
  \brief Get width of a Unicode character in a specific font.

  Actual character width on the page can be calculated as follows:

  \code
  HPDF_INT char_width = HPDF_Font_GetUnicodeWidth (font, UNICODE);
  float actual_width = char_width * FONT_SIZE / 1000;
  \endcode

  \copydoc dox_param_font
  \param code Unicode character

  \todo Clarify what is \c FONT_SIZE

  \return Character width on success, otherwise returns \c 0

*/
HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetUnicodeWidth  (HPDF_Font       font,
                            HPDF_UNICODE    code);

/**

  \ingroup font
  \brief Get bounding box of the font.

  \copydoc dox_param_font

  \return \ref HPDF_Box structure specifying font bounding box, otherwise returns `HPDF_Box{0, 0, 0, 0}`.

*/
HPDF_EXPORT(HPDF_Box)
HPDF_Font_GetBBox  (HPDF_Font    font);

/**

  \ingroup font
  \brief Get vertical ascent of the font.

  \copydoc dox_param_font

  \return Font vertical ascent on success, otherwise returns \c 0.

*/
HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetAscent  (HPDF_Font  font);

/**

  \ingroup font
  \brief Get vertical descent of the font.

  \copydoc dox_param_font

  \return Font vertical descent on success, otherwise returns \c 0.

*/
HPDF_EXPORT(HPDF_INT)
HPDF_Font_GetDescent  (HPDF_Font  font);

/**

  \ingroup font
  \brief Get the distance from the baseline and the mean line of lowercase letters in a font.

  \copydoc dox_param_font

  \return Font x-height value on success, otherwise returns \c 0.

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Font_GetXHeight  (HPDF_Font  font);

/**

  \ingroup font
  \brief Get the distance from the baseline and the mean line of uppercase letters in a font.

  \copydoc dox_param_font

  \return Font cap height value on success, otherwise returns \c 0.

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Font_GetCapHeight  (HPDF_Font  font);


/**

  \ingroup font
  \brief Get total width of the text, number of characters, and number of words.

  \copydoc dox_param_font
  \param text The text to get width.
  \param len - The byte length of the text.

  \return \ref HPDF_TextWidth struct with calculation results, otherwise, returns `HPDF_TextWidth{0, 0, 0, 0}`.

  \todo What is the meaning of fourth param?
  \todo Byte length or character length?

*/
HPDF_EXPORT(HPDF_TextWidth)
HPDF_Font_TextWidth  (HPDF_Font          font,
                      const HPDF_BYTE   *text,
                      HPDF_UINT          len);


/**

  \ingroup font
  \brief Calculate byte length which can be included within the specified width.

  \copydoc dox_param_font
  \param text Text to get width
  \param len Length of the text.
  \param width Width of the area to put text.
  \param font_size The size of the font.
  \param char_space The character spacing value.
  \param word_space The word spacing value.
  \param wordwrap \parblock Word wrap flag.
  When there are three words of \a "ABCDE", \a "FGH", and \a "IJKL", and
  the substring until \a "J" can be included within the width, if \c word_wrap
  parameter is \ref HPDF_FALSE it returns \c 12, and if \c word_wrap parameter
  is \ref HPDF_TRUE, it returns \c 10 (the end of the previous word).
  \image html img/measuretext.png
  \endparblock
  \param real_width If this parameter is not \c NULL, the real widths of the \c text is set.
  An application can set it to \c NULL, if it is unnecessary.

  \return Byte length which can be included within the specified width in
  current font size, character spacing and word spacing. Otherwise it returns \c 0 and calls error handler.

  \todo Check if function return byte length or character lenght, it differs in multiple cases.

  \todo \c len is byte length or character length?

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Font_MeasureText (HPDF_Font          font,
                       const HPDF_BYTE   *text,
                       HPDF_UINT          len,
                       HPDF_REAL          width,
                       HPDF_REAL          font_size,
                       HPDF_REAL          char_space,
                       HPDF_REAL          word_space,
                       HPDF_BOOL          wordwrap,
                       HPDF_REAL         *real_width);


/*--------------------------------------------------------------------------*/
/*----- attachments -------------------------------------------------------*/

HPDF_EXPORT(HPDF_EmbeddedFile)
HPDF_AttachFile  (HPDF_Doc    pdf,
                  const char *file);


/*--------------------------------------------------------------------------*/
/*----- extended graphics state --------------------------------------------*/

HPDF_EXPORT(HPDF_ExtGState)
HPDF_CreateExtGState  (HPDF_Doc  pdf);


HPDF_EXPORT(HPDF_STATUS)
HPDF_ExtGState_SetAlphaStroke  (HPDF_ExtGState   ext_gstate,
                                HPDF_REAL        value);


HPDF_EXPORT(HPDF_STATUS)
HPDF_ExtGState_SetAlphaFill  (HPDF_ExtGState   ext_gstate,
                              HPDF_REAL        value);



HPDF_EXPORT(HPDF_STATUS)
HPDF_ExtGState_SetBlendMode  (HPDF_ExtGState   ext_gstate,
                              HPDF_BlendMode   mode);


/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

/**

  \ingroup page
  \brief Get text width in current font size, character spacing and word spacing.

  \copydoc dox_param_page
  \param text Text to get width

  \return Text width in current font size, character spacing and word spacing. Otherwise it returns \c 0 and calls error handler.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_FAILD_TO_ALLOC_MEM
  - \ref HPDF_PAGE_FONT_NOT_FOUND

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_TextWidth  (HPDF_Page    page,
                      const char  *text);


/**

  \ingroup page
  \brief Calculate byte length which can be included within the specified width.

  \copydoc dox_param_page
  \param text Text to get width
  \param width Width of the area to put text.
  \param wordwrap \parblock Word wrap flag.
  When there are three words of \a "ABCDE", \a "FGH", and \a "IJKL", and
  the substring until \a "J" can be included within the width, if \c word_wrap
  parameter is \ref HPDF_FALSE it returns \c 12, and if \c word_wrap parameter
  is \ref HPDF_TRUE, it returns \c 10 (the end of the previous word).
  \image html img/measuretext.png
  \endparblock
  \param real_width If this parameter is not \c NULL, the real widths of the \c text is set.
  An application can set it to \c NULL, if it is unnecessary.

  \return Byte length which can be included within the specified width in 
  current font size, character spacing and word spacing. Otherwise it returns \c 0 and calls error handler.

  \todo Check if function return byte length or character lenght, it differs in multiple cases.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE
  - \ref HPDF_PAGE_FONT_NOT_FOUND

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Page_MeasureText  (HPDF_Page    page,
                        const char  *text,
                        HPDF_REAL    width,
                        HPDF_BOOL    wordwrap,
                        HPDF_REAL   *real_width);

/**

  \ingroup page
  \brief Get page width.

  \copydoc dox_param_page

  \return Page width on success, otherwise returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetWidth  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page height.

  \copydoc dox_param_page

  \return Page height on success, otherwise returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetHeight  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get current graphics mode.

  \copydoc dox_param_page

  \return Current graphics mode of the page on success, otherwise returns \c 0.

*/
HPDF_EXPORT(HPDF_UINT16)
HPDF_Page_GetGMode  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get current position for path painting.

  Application can call HPDF_Page_GetCurrentPos() only when graphics mode is \ref HPDF_GMODE_PATH_OBJECT.

  \copydoc dox_param_page

  \return \ref HPDF_Point struct with current position for path painting of the page. Otherwise it returns `HPDF_Point{0, 0}`.

  \copydoc dox_error_codes

  - \ref HPDF_INVALID_PAGE

*/
HPDF_EXPORT(HPDF_Point)
HPDF_Page_GetCurrentPos  (HPDF_Page   page);


HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_GetCurrentPos2  (HPDF_Page    page,
                           HPDF_Point  *pos);


/**

  \ingroup page
  \brief Get current position for text showing.

  Application can call HPDF_Page_GetCurrentTextPos() only when graphics mode is \ref HPDF_GMODE_TEXT_OBJECT.

  \copydoc dox_param_page

  \return \ref HPDF_Point struct with current position for text showing of the page. Otherwise it returns `HPDF_Point{0, 0}`.

*/
HPDF_EXPORT(HPDF_Point)
HPDF_Page_GetCurrentTextPos (HPDF_Page   page);


HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_GetCurrentTextPos2  (HPDF_Page    page,
                               HPDF_Point  *pos);


/**

  \ingroup page
  \brief Get page current font handle.

  \copydoc dox_param_page

  \return Page current font handle on success, otherwise it returns \c NULL.

*/
HPDF_EXPORT(HPDF_Font)
HPDF_Page_GetCurrentFont  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current font size.

  \copydoc dox_param_page

  \return Page current font size on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetCurrentFontSize  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current transformation matrix.

  \copydoc dox_param_page

  \return Page current transfomation matrix \ref HPDF_TransMatrix on success, otherwise it returns default transformation matrix `HPDF_TransMatrix{1, 0, 0, 1, 0, 0}`.

  \see HPDF_Page_Concat()

*/
HPDF_EXPORT(HPDF_TransMatrix)
HPDF_Page_GetTransMatrix  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current line width.

  \copydoc dox_param_page

  \return Page current line width for path painting on success, otherwise it returns \ref HPDF_DEF_LINEWIDTH.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetLineWidth  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current line cap.

  \copydoc dox_param_page

  \return Page current line cap for path painting on success, otherwise it returns \ref HPDF_DEF_LINECAP.

*/
HPDF_EXPORT(HPDF_LineCap)
HPDF_Page_GetLineCap  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current line join.

  \copydoc dox_param_page

  \return Page current line join for path painting on success, otherwise it returns \ref HPDF_DEF_LINEJOIN.

*/
HPDF_EXPORT(HPDF_LineJoin)
HPDF_Page_GetLineJoin  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current miter limit.

  \copydoc dox_param_page

  \return Page current line miter limit for path painting on success, otherwise it returns \ref HPDF_DEF_MITERLIMIT.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetMiterLimit  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current line dash pattern.

  \copydoc dox_param_page

  \return Page current line dash pattern \ref HPDF_DashMode for path painting on success,
  otherwise it returns `HPDF_DashMode{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}`.

*/
HPDF_EXPORT(HPDF_DashMode)
HPDF_Page_GetDash  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current flatness value.

  \copydoc dox_param_page

  \return Page current flatness value on success, otherwise it returns \ref HPDF_DEF_FLATNESS.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetFlat  (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current character spacing value.

  \copydoc dox_param_page

  \return Page current character spacing value on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetCharSpace  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current word spacing value.

  \copydoc dox_param_page

  \return Page current word spacing value on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetWordSpace  (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current horizontal scaling value for text showing.

  \copydoc dox_param_page

  \return Page current horizontal scaling value for text showing on success, otherwise it returns \ref HPDF_DEF_HSCALING.

  \todo Deprecate and rename function

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetHorizontalScalling  (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current text leading value.

  \copydoc dox_param_page

  \return Page current text leading value on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetTextLeading  (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current text rendering mode.

  \copydoc dox_param_page

  \return Page current text rendering mode on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_TextRenderingMode)
HPDF_Page_GetTextRenderingMode  (HPDF_Page   page);


/**

  \deprecated This function is obsolete. Use HPDF_Page_GetTextRise() instead.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetTextRaise  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current text rise value.

  \copydoc dox_param_page

  \return Page current text rise value on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetTextRise  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current filling color value (RGB).

  HPDF_Page_GetRGBFill() is valid only when the page's filling color space is \ref HPDF_CS_DEVICE_RGB.

  \copydoc dox_param_page

  \return Page current filling color value (RGB) on success, otherwise it returns `HPDF_RGBColor{0, 0, 0}`.

*/
HPDF_EXPORT(HPDF_RGBColor)
HPDF_Page_GetRGBFill  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current stroke color value (RGB).

  HPDF_Page_GetRGBStroke() is valid only when the page's stroke color space is \ref HPDF_CS_DEVICE_RGB.

  \copydoc dox_param_page

  \return Page current stroke color value (RGB) on success, otherwise it returns `HPDF_RGBColor{0, 0, 0}`.

*/
HPDF_EXPORT(HPDF_RGBColor)
HPDF_Page_GetRGBStroke  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current filling color value (CMYK).

  HPDF_Page_GetCMYKFill() is valid only when the page's filling color space is \ref HPDF_CS_DEVICE_CMYK.

  \copydoc dox_param_page

  \return Page current filling color value (CMYK) on success, otherwise it returns `HPDF_CMYKColor{0, 0, 0, 0}`.

*/
HPDF_EXPORT(HPDF_CMYKColor)
HPDF_Page_GetCMYKFill  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current stroke color value (CMYK).

  HPDF_Page_GetCMYKStroke() is valid only when the page's stroke color space is \ref HPDF_CS_DEVICE_CMYK.

  \copydoc dox_param_page

  \return Page current stroke color value (CMYK) on success, otherwise it returns `HPDF_CMYKColor{0, 0, 0, 0}`.

*/
HPDF_EXPORT(HPDF_CMYKColor)
HPDF_Page_GetCMYKStroke  (HPDF_Page   page);


/**

  \ingroup page
  \brief Get page current filling color value (Gray).

  HPDF_Page_GetGrayFill() is valid only when the page's filling color space is \ref HPDF_CS_DEVICE_GRAY.

  \copydoc dox_param_page

  \return Page current filling color value (Gray) on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetGrayFill  (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current stroke color value (Gray).

  HPDF_Page_GetGrayStroke() is valid only when the page's stroke color space is \ref HPDF_CS_DEVICE_GRAY.

  \copydoc dox_param_page

  \return Page current stroke color value (Gray) on success, otherwise it returns \c 0.

*/
HPDF_EXPORT(HPDF_REAL)
HPDF_Page_GetGrayStroke  (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current stroke color space.

  \copydoc dox_param_page

  \return Page current stroke color space on success, otherwise it returns \ref HPDF_CS_EOF.

*/
HPDF_EXPORT(HPDF_ColorSpace)
HPDF_Page_GetStrokingColorSpace (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current filling color space.

  \copydoc dox_param_page

  \return Page current filling color space on success, otherwise it returns \ref HPDF_CS_EOF.

*/
HPDF_EXPORT(HPDF_ColorSpace)
HPDF_Page_GetFillingColorSpace (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current text transformation matrix.

  \copydoc dox_param_page

  \return Page current \ref HPDF_TransMatrix on success, otherwise it returns `HPDF_TransMatrix{1, 0, 0, 1, 0, 0}`.

*/
HPDF_EXPORT(HPDF_TransMatrix)
HPDF_Page_GetTextMatrix  (HPDF_Page   page);

/**

  \ingroup page
  \brief Get page current graphics state stack depth.

  \copydoc dox_param_page

  \return Page current graphics state stack depth on success, otherwise it returns \c 0.

  \see \ref HPDF_LIMIT_MAX_GSTATE, HPDF_GState_New()

*/
HPDF_EXPORT(HPDF_UINT)
HPDF_Page_GetGStateDepth  (HPDF_Page   page);


/*--------------------------------------------------------------------------*/
/*----- GRAPHICS OPERATORS -------------------------------------------------*/


/*--- General graphics state ---------------------------------------------*/

/**

  \ingroup graphics
  \brief Set width of the line used to stroke paths.

  \copydoc dox_param_page
  \param line_width The line width to use.

  Default \c line_width is \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok


  \copydoc dox_pdf_cmd
  \c w

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetLineWidth  (HPDF_Page  page,
                         HPDF_REAL  line_width);

/**

  \ingroup graphics
  \brief Set lines endpoints shape style.

  \copydoc dox_param_page
  \param line_cap The line cap style (one of the following).

  | Value                           | Image                    | Description                                                             |
  | -----                           | -----                    | -----------                                                             |
  | \ref HPDF_BUTT_END              | \image html linecap1.png | Line is squared off at path endpoint.                                   |
  | \ref HPDF_ROUND_END             | \image html linecap2.png | End of line becomes a semicircle with center  at path endpoint.         |
  | \ref HPDF_PROJECTING_SQUARE_END | \image html linecap3.png | Line continues beyond endpoint, goes on half the endpoint stroke width. |

  Default \c line_cap is \ref HPDF_BUTT_END

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c J

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetLineCap  (HPDF_Page     page,
                       HPDF_LineCap  line_cap);

/**

  \ingroup graphics
  \brief Set line join shape style.

  \copydoc dox_param_page
  \param line_join The line join style (one of the following).

  | Value                | Image                     | Description                                                                                                                      |
  | -----                | -----                     | -----------                                                                                                                      |
  | \ref HPDF_MITER_JOIN | \image html linejoin1.png | Outer edges of the strokes for the two segments are extended until they meet at an angle.                                        |
  | \ref HPDF_ROUND_JOIN | \image html linejoin2.png | An arc of a circle with a diameter equal to the line width is drawn around the point where the two segments meet.                |
  | \ref HPDF_BEVEL_JOIN | \image html linejoin3.png | The two segments are finished with butt caps and the resulting notch beyond the ends of the segments are filled with a triangle. |

  Default \c line_join is \ref HPDF_MITER_JOIN.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c j

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetLineJoin  (HPDF_Page      page,
                        HPDF_LineJoin  line_join);

/**

  \ingroup graphics
  \brief Set miter limit for line joins.

  \copydoc dox_param_page
  \param miter_limit Miter limit value.

  Default \c miter_limit is \ref HPDF_DEF_MITERLIMIT.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \note A miter limit of 1.414 converts miters to bevels for \c angle less than \c 90 degrees,
  a limit of \c 2.0 converts them for \c angle less than 60 degrees, and a limit of 10.0
  converts them for angle less than approximately 11.5 degrees.

  \copydoc dox_pdf_cmd
  \c M

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetMiterLimit  (HPDF_Page  page,
                          HPDF_REAL  miter_limit);

/**

  \ingroup graphics
  \brief Set dash pattern for lines in the page.

  \copydoc dox_param_page
  \param dash_pattern Pattern of dashes and gaps used to stroke paths.
  \param num_elem Number of elements in dash_pattern, `0 <= num_param <= 8`.
  \param phase Phase in which pattern begins (default is \c 0).

  \copydoc dox_graphics_mode
  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \par Examples

  `dash_ptn = NULL`, `num_elem = 0`, `phase = 0` (default for new page)

  \image html setdash1.png

  `dash_ptn = [3]`, `num_elem = 1`, `phase = 1`

  \image html setdash2.png

  `dash_ptn = [7,]`, `num_elem = 2`, `phase = 2`

  \image html setdash3.png

  `dash_ptn = [8,]`, `num_elem = 4`, `phase = 0`

  \image html setdash4.png

  \copydoc dox_pdf_cmd
  \c d

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetDash  (HPDF_Page           page,
                    const HPDF_REAL    *dash_pattern,
                    HPDF_UINT           num_elem,
                    HPDF_REAL           phase);



/* ri --not implemented yet */

/* i */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetFlat  (HPDF_Page    page,
                    HPDF_REAL    flatness);

/**

  \ingroup graphics
  \brief Apply graphics state to page

  \copydoc dox_param_page
  \param ext_gstate Extended graphics state object handle.

  \copydoc dox_graphics_mode
  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c gs

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetExtGState  (HPDF_Page        page,
                         HPDF_ExtGState   ext_gstate);

/* sh */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetShading  (HPDF_Page    page,
                       HPDF_Shading shading);


/*--- Special graphic state operator --------------------------------------*/

/**

  \ingroup graphics
  \brief Save the page's current graphics state to the stack.

  Application can call HPDF_Page_GSave() and can restore saved state by calling HPDF_Page_GRestore().

  Saved by HPDF_Page_GSave() state parameters are:

    - Character Spacing
    - Clipping Path
    - Dash Mode
    - Filling Color
    - Flatness
    - Font
    - Font Size
    - Horizontal Scalling
    - Line Width
    - Line Cap Style
    - Line Join Style
    - Miter Limit
    - Rendering Mode
    - Stroking Color
    - Text Leading
    - Text Rise
    - Transformation Matrix
    - Word Spacing

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c q

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_GSave  (HPDF_Page    page);

/**

  \ingroup graphics
  \brief Restore graphics state which is saved by HPDF_Page_GSave().

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Q

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_GRestore  (HPDF_Page    page);

/**

  \ingroup graphics
  \brief Concatenate the page's transformation matrix and specified matrix.

  For example, if you want to rotate the coordinate system of the page by 45 degrees, use HPDF_Page_Concat() as follows.

  \code
  float rad1 = 45 / 180 * 3.141592;
  HPDF_Page_Concat (page, cos (rad1), sin (rad1), -sin (rad1), cos (rad1), 220, 350);
  \endcode

  To change the coordinate system of the page to 300 dpi, use HPDF_Page_Concat() as follows.

  \code
  HPDF_Page_Concat (page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);
  \endcode

  Invoke HPDF_Page_GSave() before HPDF_Page_Concat(). Then the change by HPDF_Page_Concat() can be restored by invoking HPDF_Page_GRestore().

  \code
  // Save current graphics state
  HPDF_Page_GSave (page);

  //Concatenate transformation matrix
  HPDF_Page_Concat (page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);

  // Show text on translated coordinates
  HPDF_Page_BeginText (page);
  HPDF_Page_MoveTextPos (page, 50, 100);
  HPDF_Page_ShowText (page, "Text on the translated coordinates");
  HPDF_Page_EndText (page);

  // Restore the graphics states
  HPDF_Page_GRestore (page);
  \endcode

  Application can call HPDF_Page_GSave() when graphics mode is \ref HPDF_GMODE_PAGE_DESCRIPTION.

  \copydoc dox_param_page
  \param a, b, c, d, x, y - Transformation matrix to concatenate.

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c cm

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Concat  (HPDF_Page    page,
                   HPDF_REAL    a,
                   HPDF_REAL    b,
                   HPDF_REAL    c,
                   HPDF_REAL    d,
                   HPDF_REAL    x,
                   HPDF_REAL    y);

/*--- Path construction operator ------------------------------------------*/

/**

  \ingroup graphics
  \brief Start new subpath and move current point for drawing path.

  HPDF_Page_MoveTo() set starting point for the path to (x, y).

  \copydoc dox_param_page
  \param x, y Starting point for drawing path

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c m

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveTo  (HPDF_Page    page,
                   HPDF_REAL    x,
                   HPDF_REAL    y);

/**

  \ingroup graphics
  \brief Append path from current point to specified point.

  \copydoc dox_param_page
  \param x, y End point of the path

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c l

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_LineTo  (HPDF_Page    page,
                   HPDF_REAL    x,
                   HPDF_REAL    y);

/**

  \ingroup graphics
  \brief Append Bézier curve to current path using control points
  (x<sub>1</sub>, y<sub>1</sub>) and (x<sub>2</sub>, y<sub>2</sub>)
  and (x<sub>3</sub>, y<sub>3</sub>), then set current point
  to (x<sub>3</sub>, y<sub>3</sub>).

  \image html img/curveto.png

  \copydoc dox_param_page
  \param x1, y1, x2, y2, x3, y3 Control points for Bézier curve.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c c

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_CurveTo  (HPDF_Page    page,
                    HPDF_REAL    x1,
                    HPDF_REAL    y1,
                    HPDF_REAL    x2,
                    HPDF_REAL    y2,
                    HPDF_REAL    x3,
                    HPDF_REAL    y3);

/**

  \ingroup graphics
  \brief Append Bézier curve to current path using current point and (x<sub>2</sub>, y<sub>2</sub>)
  and (x<sub>3</sub>, y<sub>3</sub>) as control points. Then current point is set to (x<sub>3</sub>, y<sub>3</sub>).

  \image html img/curveto2.png

  \copydoc dox_param_page
  \param x2, y2, x3, y3 Control points for Bézier curve along with current point.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c v

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_CurveTo2  (HPDF_Page    page,
                     HPDF_REAL    x2,
                     HPDF_REAL    y2,
                     HPDF_REAL    x3,
                     HPDF_REAL    y3);

/**

  \ingroup graphics
  \brief Append Bézier curve to the current path using two spesified points.
  The point (x<sub>1</sub>, y<sub>1</sub>) and the point (x<sub>3</sub>, y<sub>3</sub>)
  are used as the control points for a Bézier curve and current point is moved to the point
  (x<sub>3</sub>, y<sub>3</sub>).

  \image html img/curveto3.png

  \copydoc dox_param_page
  \param x1, y1, x3, y3 Control points for Bézier curve along with current point.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c y

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_CurveTo3  (HPDF_Page  page,
                     HPDF_REAL  x1,
                     HPDF_REAL  y1,
                     HPDF_REAL  x3,
                     HPDF_REAL  y3);


/**

  \ingroup graphics
  \brief Append straight line from current point to the start point of subpath.

  Current point is moved to the start point of subpath.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c h

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePath  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Append rectangle to the current path.

  \copydoc dox_param_page
  \param x, y Lower-left point of the rectangle.
  \param width Width of the rectangle.
  \param height Height of the rectangle.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c re

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Rectangle  (HPDF_Page  page,
                      HPDF_REAL  x,
                      HPDF_REAL  y,
                      HPDF_REAL  width,
                      HPDF_REAL  height);


/*--- Path painting operator ---------------------------------------------*/

/**

  \ingroup graphics
  \brief Paint current path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c S

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Stroke  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Close and paint current path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c s

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePathStroke  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Fill current path using non-zero winding number rule.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c f

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Fill  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Fill current path using even-odd rule.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c f*

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Eofill  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Fill current path using the even-odd rule.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c B

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_FillStroke  (HPDF_Page  page);


/**

  \ingroup graphics
  \brief Fill current path using the even-odd rule and then paint the path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode
  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c B*

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_EofillStroke  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Close current path, fill current path using the non-zero winding number rule, then paint path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode
  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c b

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePathFillStroke  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Close current path, fill current path using the even-odd rule and then paint the path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode
  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c b*

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ClosePathEofillStroke  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Finish path object without filling or painting.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c n

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_EndPath  (HPDF_Page  page);


/*--- Clipping paths operator --------------------------------------------*/

/**

  \ingroup graphics
  \brief Modify current clipping path by intersecting it with current path using the nonzero winding number rule.

  The clipping path is only modified after the succeeding painting operator.
  To avoid painting the current path, use the function HPDF_Page_EndPath().

  Following painting operations will only affect the regions of the page contained by the clipping path.
  Initially, the clipping path includes the entire page. There is no way to enlarge the current clipping path
  or to replace the clipping path with a new one. The functions HPDF_Page_GSave() and HPDF_Page_GRestore()
  may be used to save and restore the current graphics state, including the clipping path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \see HPDF_Page_EndPath(), HPDF_Page_GSave(), HPDF_Page_GRestore()

  \copydoc dox_pdf_cmd
  \c W

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Clip  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Modifies the current clipping path by intersecting it with  current path using the even-odd rule.
  Clipping path is only modified after succeeding painting operator. To avoid painting current path, use HPDF_Page_EndPath().

  Following painting operations will only affect page regions contained by the clipping path.
  Clipping path includes entire page initially. There is no way to enlarge current clipping path
  or to replace clipping path with new one. Functions HPDF_Page_GSave() and HPDF_Page_GRestore()
  may be used to save and restore the current graphics state, including the clipping path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \see HPDF_Page_EndPath(), HPDF_Page_GSave(), HPDF_Page_GRestore(), HPDF_Page_Clip()

  \copydoc dox_pdf_cmd
  \c W*

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Eoclip  (HPDF_Page  page);


/*--- Text object operator -----------------------------------------------*/

/**
  \ingroup graphics
  \brief Begin text object and set text position to `(0, 0)`.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see HPDF_Page_EndText()

  \copydoc dox_pdf_cmd
  \c BT

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_BeginText  (HPDF_Page  page);

/**

  \ingroup graphics
  \brief Finish text object

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \see HPDF_Page_BeginText()

  \copydoc dox_pdf_cmd
  \c ET

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_EndText  (HPDF_Page  page);

/*--- Text state ---------------------------------------------------------*/

/**

  \ingroup graphics
  \brief Set text character spacing.

  \copydoc dox_param_page
  \param value Character spacing (initial value is \c 0).

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Tc

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetCharSpace  (HPDF_Page  page,
                         HPDF_REAL  value);

/**

  \ingroup graphics
  \brief Set text word spacing.

  \copydoc dox_param_page
  \param value Word spacing (initial value is \c 0).

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Tw

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetWordSpace  (HPDF_Page  page,
                         HPDF_REAL  value);

/**

  \ingroup graphics
  \brief Set text horizontal scaling.

  \copydoc dox_param_page
  \param value Value of horizontal scaling (initially \c 100).

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Deprecate and rename function

  \copydoc dox_pdf_cmd
  \c Tz

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetHorizontalScalling  (HPDF_Page  page,
                                  HPDF_REAL  value);

/**

  \ingroup graphics
  \brief Set text leading (line spacing).

  \copydoc dox_param_page
  \param value Value of text leading (initially \c 0).

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c TL

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextLeading  (HPDF_Page  page,
                           HPDF_REAL  value);

/**

  \ingroup graphics
  \brief Set the type of font and size leading.

  \copydoc dox_param_page
  \param font Font object handle.
  \param size Font size.

  \copydoc dox_graphics_mode
  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Tf

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetFontAndSize  (HPDF_Page  page,
                           HPDF_Font  font,
                           HPDF_REAL  size);

/**

  \ingroup graphics
  \brief Set text rendering mode.

  \copydoc dox_param_page
  \param mode Text rendering mode (one of the following).

  | Value                          | Image                    | Description                                          |
  | -----                          | :-----:                  | -----------                                          |
  | \ref HPDF_FILL                 | \image html rndmode1.png | Fill text.                                           |
  | \ref HPDF_STROKE               | \image html rndmode2.png | Stroke text.                                         |
  | \ref HPDF_FILL_THEN_STROKE     | \image html rndmode3.png | Fill, then stroke text.                              |
  | \ref HPDF_INVISIBLE            | &mdash;                  | Neither fill nor stroke text (invisible).            |
  | \ref HPDF_FILL_CLIPPING        | \image html rndmode4.png | Fill text and add to path for clipping.              |
  | \ref HPDF_STROKE_CLIPPING      | \image html rndmode5.png | Stroke text and add to path for clipping.            |
  | \ref HPDF_FILL_STROKE_CLIPPING | \image html rndmode6.png | Fill, then stroke text and add to path for clipping. |
  | \ref HPDF_CLIPPING             | &mdash;                  | Add text to path for clipping.                       |

  Default \c mode is \ref HPDF_FILL.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Add picture for \ref HPDF_CLIPPING

  \copydoc dox_pdf_cmd
  \c Tr

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextRenderingMode  (HPDF_Page               page,
                                 HPDF_TextRenderingMode  mode);

/**

  \ingroup graphics
  \brief Move text position in vertical direction by the amount of \c value.

  Useful for making subscripts or superscripts.

  \copydoc dox_param_page
  \param value Text rise, in user space units.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Add picture for \ref HPDF_CLIPPING

  \see HPDF_Page_SetTextRaise()

  \copydoc dox_pdf_cmd
  \c Ts

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextRise  (HPDF_Page   page,
                        HPDF_REAL   value);

/**

  \deprecated Use HPDF_Page_SetTextRise() instead.

  \ingroup graphics
  \brief Move text position in vertical direction by the amount of \c value.

  Useful for making subscripts or superscripts.

  \copydoc dox_param_page
  \param value Text rise, in user space units.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Add picture for \ref HPDF_CLIPPING

  \see HPDF_Page_SetTextRise()

  \copydoc dox_pdf_cmd
  \c Ts

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextRaise  (HPDF_Page   page,
                         HPDF_REAL   value);

/*--- Text positioning ---------------------------------------------------*/

/**

  \ingroup graphics
  \brief Change current text position using the specified offset values.

  If the current text position is (x<sub>1</sub>, y<sub>1</sub>), the new text position will be (x<sub>1</sub> + x, y<sub>1</sub> + y).

  \copydoc dox_param_page
  \param x, y Offset to new text position.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Td

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveTextPos  (HPDF_Page   page,
                        HPDF_REAL   x,
                        HPDF_REAL   y);

/**

  \ingroup graphics
  \brief Change current text position using the specified offset values.

  If the current text position is (x<sub>1</sub>, y<sub>1</sub>), the new text position will be (x<sub>1</sub> + x, y<sub>1</sub> + y).

  Also, text leading is set to \a -y.

  \copydoc dox_param_page
  \param x, y Offset to new text position.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c TD

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveTextPos2  (HPDF_Page  page,
                         HPDF_REAL   x,
                         HPDF_REAL   y);

/* Tm */
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetTextMatrix  (HPDF_Page         page,
                          HPDF_REAL    a,
                          HPDF_REAL    b,
                          HPDF_REAL    c,
                          HPDF_REAL    d,
                          HPDF_REAL    x,
                          HPDF_REAL    y);


/**

  \ingroup graphics
  \brief Move current position for text showing depending on current text showing point and text leading.

  New position is calculated with current text transition matrix.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c T*

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_MoveToNextLine  (HPDF_Page  page);

/*--- Text showing -------------------------------------------------------*/

/**

  \ingroup graphics
  \brief Put text at the current text position on the page.

  \copydoc dox_param_page
  \param text Text to put to page.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see HPDF_Page_BeginText(), HPDF_Page_EndText()

  \copydoc dox_pdf_cmd
  \c Tj

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ShowText  (HPDF_Page    page,
                     const char  *text);

/* TJ */

/**

  \ingroup graphics
  \brief Move current text position to the start of the next line, then put the text at the current text position on the page.

  \copydoc dox_param_page
  \param text Text to put to page.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see HPDF_Page_BeginText(), HPDF_Page_EndText()

  \copydoc dox_pdf_cmd
  \c ' (apostrophe)
*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ShowTextNextLine  (HPDF_Page    page,
                             const char  *text);

/**

  \ingroup graphics
  \brief Move current text position to the start of the next line, then set word spacing and character spacing, finally put the text at the current text position on the page.

  \copydoc dox_param_page
  \param text Text to put to page.
  \param word_space Word spacing value
  \param char_space Char spacing value

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Write note: same as aw Tw; ac Tc; string ', Table 109 of PDF book

  \see HPDF_Page_BeginText(), HPDF_Page_EndText()

  \copydoc dox_pdf_cmd
  \c " (quote)

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ShowTextNextLineEx  (HPDF_Page    page,
                               HPDF_REAL    word_space,
                               HPDF_REAL    char_space,
                               const char  *text);


/*--- Color showing ------------------------------------------------------*/

/* cs --not implemented yet */
/* CS --not implemented yet */
/* sc --not implemented yet */
/* scn --not implemented yet */
/* SC --not implemented yet */
/* SCN --not implemented yet */

/**

  \ingroup graphics
  \brief Set the filling color (Gray).

  \copydoc dox_param_page
  \param value Value of the gray level between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see HPDF_Page_GetGrayFill()

  \copydoc dox_pdf_cmd
  \c g

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetGrayFill  (HPDF_Page   page,
                        HPDF_REAL   value);

/**

  \ingroup graphics
  \brief Set stroking color (Gray).

  \copydoc dox_param_page
  \param value Value of the gray level between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see HPDF_Page_GetGrayStroke()

  \copydoc dox_pdf_cmd
  \c G

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetGrayStroke  (HPDF_Page   page,
                          HPDF_REAL   value);

/**

  \ingroup graphics
  \brief Set filling color (RGB).

  \copydoc dox_param_page
  \param r, g, b Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see HPDF_Page_GetRGBFill()

  \copydoc dox_pdf_cmd
  \c rg

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetRGBFill  (HPDF_Page  page,
                       HPDF_REAL  r,
                       HPDF_REAL  g,
                       HPDF_REAL  b);

/**

  \ingroup graphics
  \brief Set stroke color (RGB).

  \copydoc dox_param_page
  \param r, g, b Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see HPDF_Page_GetRGBStroke()

  \copydoc dox_pdf_cmd
  \c RG

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetRGBStroke  (HPDF_Page  page,
                         HPDF_REAL  r,
                         HPDF_REAL  g,
                         HPDF_REAL  b);

/**

  \ingroup graphics
  \brief Set stroke color (RGB) using \ref HPDF_UINT8 values.

  \copydoc dox_param_page
  \param r, g, b Level of each color element. They must be between \c 0x00 and \c 0xFF.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see HPDF_Page_GetRGBStroke(), HPDF_Page_SetRGBStroke()

  \copydoc dox_pdf_cmd
  \c RG

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetRGBStrokeHex  (HPDF_Page  page,
                            HPDF_UINT8  r,
                            HPDF_UINT8  g,
                            HPDF_UINT8  b);

/**

  \ingroup graphics
  \brief Set filling color (CMYK).

  \copydoc dox_param_page
  \param c, m, y, k Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see HPDF_Page_GetCMYKFill()

  \copydoc dox_pdf_cmd
  \c k

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetCMYKFill  (HPDF_Page  page,
                        HPDF_REAL  c,
                        HPDF_REAL  m,
                        HPDF_REAL  y,
                        HPDF_REAL  k);

/**

  \ingroup graphics
  \brief Set stroke color (CMYK).

  \copydoc dox_param_page
  \param c, m, y, k Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see HPDF_Page_GetCMYKStroke()

  \copydoc dox_pdf_cmd
  \c K

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetCMYKStroke  (HPDF_Page  page,
                          HPDF_REAL  c,
                          HPDF_REAL  m,
                          HPDF_REAL  y,
                          HPDF_REAL  k);

/*--- Shading patterns ---------------------------------------------------*/

/* Notes for docs:
 * - ShadingType must be HPDF_SHADING_FREE_FORM_TRIANGLE_MESH (the only
 *   defined option...)
 * - colorSpace must be HPDF_CS_DEVICE_RGB for now.
 */
HPDF_EXPORT(HPDF_Shading)
HPDF_Shading_New  (HPDF_Doc           pdf,
                   HPDF_ShadingType   type,
                   HPDF_ColorSpace    colorSpace,
                   HPDF_REAL          xMin,
                   HPDF_REAL          xMax,
                   HPDF_REAL          yMin,
                   HPDF_REAL          yMax);

HPDF_EXPORT(HPDF_STATUS)
HPDF_Shading_AddVertexRGB(HPDF_Shading                                shading,
                          HPDF_Shading_FreeFormTriangleMeshEdgeFlag   edgeFlag,
                          HPDF_REAL                                   x,
                          HPDF_REAL                                   y,
                          HPDF_UINT8                                  r,
                          HPDF_UINT8                                  g,
                          HPDF_UINT8                                  b);

/*--- In-line images -----------------------------------------------------*/

/* BI --not implemented yet */
/* ID --not implemented yet */
/* EI --not implemented yet */

/*--- XObjects -----------------------------------------------------------*/

/**

  \ingroup graphics
  \brief Draw XObject using current graphics context.

  This is used by HPDF_Page_DrawImage() to draw the \ref HPDF_Image by first calling
  HPDF_Page_GSave() and HPDF_Page_Concat() and then calling HPDF_Page_GRestore() 
  after HPDF_Page_ExecuteXObject(). It could be used manually to rotate an image.

  \copydoc dox_param_page
  \param obj XObject handle like an image.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Do

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_ExecuteXObject  (HPDF_Page      page,
                           HPDF_XObject   obj);

/*--- Content streams ----------------------------------------------------*/

/**

  \ingroup page
  \brief Create new content stream on the page.

  The call can return a reference to the new content stream in \c new_stream.
  This reference can be used on a later pages to call HPDF_Page_Insert_Shared_Content_Stream().

  The use case is when you need to place a considerable amount of identical content on multiple pages.
  On the first occurrence of the content, call HPDF_Page_New_Content_Stream() before you start creating
  the content in order to place the content in a separate stream.
  Call HPDF_Page_New_Content_Stream() again after you have finished the content.
  Then, on subsequent pages, call HPDF_Page_Insert_Shared_Content_Stream() to place the content on that page.

  \copydoc dox_param_page
  \param new_stream Reference to \ref HPDF_Dict identifying new stream.

  \copydoc dox_return_ok

  \see HPDF_Page_Insert_Shared_Content_Stream()

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_New_Content_Stream  (HPDF_Page   page,
                               HPDF_Dict  *new_stream);
/**

  \ingroup page
  \brief Insert content stream to the page.

  \copydoc dox_param_page
  \param shared_stream Reference to \ref HPDF_Dict, previously created by HPDF_Page_New_Content_Stream()

  \copydoc dox_return_ok

  \see HPDF_Page_Insert_Shared_Content_Stream()

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Insert_Shared_Content_Stream  (HPDF_Page page,
                                         HPDF_Dict shared_stream);


/*--- Marked content -----------------------------------------------------*/

/* BMC --not implemented yet */
/* BDC --not implemented yet */
/* EMC --not implemented yet */
/* MP --not implemented yet */
/* DP --not implemented yet */

/*--- Compatibility ------------------------------------------------------*/

/* BX --not implemented yet */
/* EX --not implemented yet */

/**

  \ingroup graphics
  \brief Show an image in one operation.

  \copydoc dox_param_page
  \param image Image object handle
  \param x, y Lower-left point of the region where image is displayed.
  \param width Width of the region where image is displayed.
  \param height Height of the region where image is displayed.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION
  \arg After \ref HPDF_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_DrawImage  (HPDF_Page    page,
                      HPDF_Image   image,
                      HPDF_REAL    x,
                      HPDF_REAL    y,
                      HPDF_REAL    width,
                      HPDF_REAL    height);

/**

  \ingroup graphics
  \brief Append circle to current path.

  \copydoc dox_param_page
  \param x, y Center point of the circle.
  \param radius Circle radius

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Circle  (HPDF_Page     page,
                   HPDF_REAL     x,
                   HPDF_REAL     y,
                   HPDF_REAL     radius);


/**

  \ingroup graphics
  \brief Append ellipse to current path.

  \copydoc dox_param_page
  \param x, y Center point of the ellipse.
  \param x_radius, y_radius Horizontal and vertical radii of the ellipse.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PATH_OBJECT
  \arg After \ref HPDF_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Ellipse  (HPDF_Page    page,
                    HPDF_REAL    x,
                    HPDF_REAL    y,
                    HPDF_REAL    x_radius,
                    HPDF_REAL    y_radius);

/**

  \ingroup graphics
  \brief Append circle arc to current path.

  Angles are given in degrees, with 0 degrees being vertical, upward, from the `(x, y)` position.

  \copydoc dox_param_page
  \param x, y Center point of the circle.
  \param radius Radius of the circle.
  \param ang1 Angle at the begining of the arc.
  \param ang2 Angle at the end of the arc. It must be greater than \c ang1.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_PAGE_DESCRIPTION or \ref HPDF_GMODE_PATH_OBJECT.
  \arg After \ref HPDF_GMODE_PATH_OBJECT.

  \copydoc dox_return_ok

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_Arc  (HPDF_Page    page,
                HPDF_REAL    x,
                HPDF_REAL    y,
                HPDF_REAL    radius,
                HPDF_REAL    ang1,
                HPDF_REAL    ang2);

/**

  \ingroup graphics
  \brief Put text to the specified position.

  \copydoc dox_param_page
  \param xpos, ypos Point position where the text is displayed.
  \param text Text to show.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_TextOut  (HPDF_Page    page,
                    HPDF_REAL    xpos,
                    HPDF_REAL    ypos,
                    const char  *text);


/**

  \ingroup graphics
  \brief Put text inside the specified region.

  \copydoc dox_param_page
  \param left, top, right, bottom Coordinates of corners of the region to output text.
  \param text Text to show.
  \param align \parblock Text alignment (one of the following).

  | Value                    | Description                                                       |
  | -----                    | -----------                                                       |
  | \ref HPDF_TALIGN_LEFT    | The text is aligned to left.                                      |
  | \ref HPDF_TALIGN_RIGHT   | The text is aligned to right.                                     |
  | \ref HPDF_TALIGN_CENTER  | The text is aligned to center.                                    |
  | \ref HPDF_TALIGN_JUSTIFY | Add spaces between the words to justify both left and right side. |
  \endparblock
  \param len If not \c NULL, the number of characters printed in the area is returned.

  \copydoc dox_graphics_mode

  \arg Before \ref HPDF_GMODE_TEXT_OBJECT
  \arg After \ref HPDF_GMODE_TEXT_OBJECT

  \return \ref HPDF_OK on success. May return \ref HPDF_PAGE_INSUFFICIENT_SPACE on success but whole text doesn't fit into declared space. 
  Otherwise, returns error code and calls error handler.

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_TextRect  (HPDF_Page            page,
                     HPDF_REAL            left,
                     HPDF_REAL            top,
                     HPDF_REAL            right,
                     HPDF_REAL            bottom,
                     const char          *text,
                     HPDF_TextAlignment   align,
                     HPDF_UINT           *len);


/**

  \ingroup page
  \brief Configure slide transition of the page.

  \copydoc dox_param_page
  \param type The transition style. See \ref HPDF_TransitionStyle.
  \param disp_time Page display duration (in seconds).
  \param trans_time Transition effect duration (in seconds). Default is 1 second.

  \copydoc dox_return_ok

*/
HPDF_EXPORT(HPDF_STATUS)
HPDF_Page_SetSlideShow  (HPDF_Page              page,
                         HPDF_TransitionStyle   type,
                         HPDF_REAL              disp_time,
                         HPDF_REAL              trans_time);


HPDF_EXPORT(HPDF_OutputIntent)
HPDF_ICC_LoadIccFromMem (HPDF_Doc   pdf,
                        HPDF_MMgr   mmgr,
                        HPDF_Stream iccdata,
                        HPDF_Xref   xref,
                        int         numcomponent);

HPDF_EXPORT(HPDF_OutputIntent)
HPDF_LoadIccProfileFromFile  (HPDF_Doc     pdf,
                              const char  *icc_file_name,
                              int          numcomponent);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPDF_H */
