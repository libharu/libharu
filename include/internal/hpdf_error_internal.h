#ifndef HPDF_ERROR_INTERNAL_H
#define HPDF_ERROR_INTERNAL_H

typedef struct  _HPDF_Error_Rec {
    HPDF_STATUS             error_no;
    HPDF_STATUS             detail_no;
    HPDF_Error_Handler      error_fn;
    void                    *user_data;
} HPDF_Error_Rec;

#endif /* HPDF_ERROR_INTERNAL_H */