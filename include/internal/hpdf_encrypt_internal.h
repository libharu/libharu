#ifndef HPDF_ENCRYPT_INTERNAL_H
#define HPDF_ENCRYPT_INTERNAL_H

#include "hpdf_encrypt.h"

typedef struct _HPDF_ARC4_Ctx_Rec {
    HPDF_BYTE    idx1;
    HPDF_BYTE    idx2;
    HPDF_BYTE    state[HPDF_ARC4_BUF_SIZE];
} HPDF_ARC4_Ctx_Rec;

typedef struct _HPDF_Encrypt_Rec {
    HPDF_EncryptMode   mode;

    /* key_len must be a multiple of 8, and between 40 to 128 */
    HPDF_UINT          key_len;

    /* owner-password (not encrypted) */
    HPDF_BYTE          owner_passwd[HPDF_PASSWD_LEN];

    /* user-password (not encrypted) */
    HPDF_BYTE          user_passwd[HPDF_PASSWD_LEN];

    /* owner-password (encrypted) */
    HPDF_BYTE          owner_key[HPDF_PASSWD_LEN];

    /* user-password (encrypted) */
    HPDF_BYTE          user_key[HPDF_PASSWD_LEN];

    HPDF_INT           permission;
    HPDF_BYTE          encrypt_id[HPDF_ID_LEN];
    HPDF_BYTE          encryption_key[HPDF_MD5_KEY_LEN + 5];
    HPDF_BYTE          md5_encryption_key[HPDF_MD5_KEY_LEN];
    HPDF_ARC4_Ctx_Rec  arc4ctx;
} HPDF_Encrypt_Rec;

#endif /* HPDF_ENCRYPT_INTERNAL_H */