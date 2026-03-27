/*
 * << Haru Free PDF Library >> -- hpdf_utils.c
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

#include <math.h>
#include <stdlib.h>
#include "hpdf_utils.h"
#include "hpdf_consts.h"
#include "hpdf_page_sizes.h"

/*---------------------------------------------------------------------------*/

HPDF_INT
HPDF_AToI  (const char  *s)
{
    HPDF_BOOL flg = HPDF_FALSE;
    HPDF_INT  v = 0;

    if (!s) {
        return 0;
    }

    /* increment pointer until the character of 's' is not
     * white-space-character.
     */
    while (*s) {
        if (HPDF_IS_WHITE_SPACE(*s))
            s++;
        else {
            if (*s == '-') {
                flg = HPDF_TRUE;
                s++;
            }
            break;
        }
    }

    while (*s >= '0' && *s <= '9') {
        v *= 10;
        v += *s - '0';
        s++;
    }

    if (flg)
        v *= -1;

    return v;
}


HPDF_DOUBLE
HPDF_AToF  (const char  *s)
{
    HPDF_BOOL flg = HPDF_FALSE;
    HPDF_INT i = 0;
    HPDF_DOUBLE v;
    HPDF_INT tmp = 1;

    /* increment pointer until the character of 's' is not
     * white-space-character.
     */
    while (*s) {
        if (HPDF_IS_WHITE_SPACE(*s))
            s++;
        else {
            if (*s == '-') {
                flg = HPDF_TRUE;
                s++;
            }
            break;
        }
    }

    while (*s >= '0' && *s <= '9') {
        if (i > 3276)
            break;

        i *= 10;
        i += *s - '0';
        s++;
    }

    if (*s == '.') {
        s++;
        while (*s >= '0' && *s <= '9') {
            if (i > 214748364)
                break;

            i *= 10;
            i += *s - '0';
            s++;
            tmp *= 10;
        }
    }

    v = (HPDF_DOUBLE)i / tmp;

    if (flg)
        v *= -1;

    return v;
}


char*
HPDF_IToA  (char        *s,
            HPDF_INT32   val,
            char        *eptr)
{
    char* t;
    char buf[HPDF_INT_LEN + 1];

    if (val < 0) {
        if (val < HPDF_LIMIT_MIN_INT)
            val = HPDF_LIMIT_MIN_INT;
        *s++ = '-';
        val = -val;
    } else if (val > HPDF_LIMIT_MAX_INT) {
        val = HPDF_LIMIT_MAX_INT;
    } else if (val == 0) {
        *s++ = '0';
    }

    t = buf + HPDF_INT_LEN;
    *t-- = 0;

    while (val > 0) {
        *t = (char)((char)(val % 10) + '0');
        val /= 10;
        t--;
    }

    t++;
    while (s < eptr && *t != 0)
      *s++ = *t++;
    *s = 0;

    return s;
}


char*
HPDF_IToA2  (char         *s,
             HPDF_UINT32   val,
             HPDF_UINT     len)
{
    char* t;
    char* u;

    if (val > HPDF_LIMIT_MAX_INT)
        val = HPDF_LIMIT_MAX_INT;

    u = s + len - 1;
    *u = 0;
    t = u - 1;
    while (val > 0 && t >= s) {
        *t = (char)((char)(val % 10) + '0');
        val /= 10;
        t--;
    }

    while (s <= t)
        *t-- = '0';

    return s + len - 1;
}


char*
HPDF_FToA  (char       *s,
            HPDF_REAL   val,
            char       *eptr)
{
    HPDF_REAL int_val;
    HPDF_REAL fpart_val;
    HPDF_REAL dig;
    char buf[HPDF_REAL_LEN + 1];
    char* sptr = s;
    char* t;
    HPDF_INT32 logVal;
    HPDF_UINT32 prec;

    if (val > HPDF_LIMIT_MAX_REAL)
        val = HPDF_LIMIT_MAX_REAL;
    else
    if (val < HPDF_LIMIT_MIN_REAL)
        val = HPDF_LIMIT_MIN_REAL;

    t = buf;
    *t++ = 0;

    if (val < 0) {
        *s++ = '-';
        val = -val;
    }

    /* compute the decimal precision to write at least 5 significant figures */
    logVal = (HPDF_INT32)(val > 1e-20 ? log10(val) : 0.);
    if (logVal >= 0) {
        prec = 5;
    }
    else {
        prec = -logVal + 5;
    }

    /* separate an integer part and a fractional part. */
    fpart_val = modff(val, &int_val);

    /* process integer part */
    do {
        dig = modff(int_val/10.0f, &int_val);
        *t++ = (char)(dig*10.0 + 0.5) + '0';
    } while (int_val > 0);

    /* copy to destination buffer */
    t--;
    while (s <= eptr && *t != 0)
        *s++ = *t--;

    /* process fractional part */
    *s++ = '.';
    if (fpart_val != 0.0) {
        HPDF_UINT32 i;
        for (i = 0; i < prec; i++) {
            fpart_val = modff(fpart_val*10.0f, &int_val);
            *s++ = (char)(int_val + 0.5) + '0';
        }
    }

    /* delete an excessive decimal portion. */
    s--;
    while (s > sptr) {
        if (*s == '0')
            *s = 0;
        else {
            if (*s == '.')
                *s = 0;
            break;
        }
        s--;
    }

    return (*s == 0) ? s : ++s;
}


HPDF_BYTE*
HPDF_MemCpy  (HPDF_BYTE*         out,
              const HPDF_BYTE   *in,
              HPDF_UINT          n)
{
    while (n > 0) {
        *out++ = *in++;
        n--;
    }

    return out;
}


HPDF_BYTE*
HPDF_StrCpy  (char          *out,
              const char    *in,
              char          *eptr)
{
    if (in != NULL) {
        while (eptr > out && *in != 0)
            *out++ = *in++;
    }

    *out = 0;

    return (HPDF_BYTE *)out;
}


HPDF_INT
HPDF_MemCmp  (const HPDF_BYTE   *s1,
              const HPDF_BYTE   *s2,
              HPDF_UINT          n)
{
    if (n == 0)
        return 0;

    while (*s1 == *s2) {
        n--;
        if (n == 0)
            return 0;
        s1++;
        s2++;
    }

    return *s1 - *s2;
}


HPDF_INT
HPDF_StrCmp  (const char   *s1,
              const char   *s2)
{
    if (!s1 || !s2) {
        if (!s1 && s2)
            return -1;
        else
            return 1;
    }

    while (*s1 == *s2) {
        s1++;
        s2++;
        if (*s1 == 0 || *s2 == 0)
            break;
    }

    return (HPDF_BYTE)*s1 - (HPDF_BYTE)*s2;
}


void*
HPDF_MemSet  (void        *s,
              HPDF_BYTE    c,
              HPDF_UINT    n)
{
    HPDF_BYTE* b = (HPDF_BYTE*)s;

    while (n > 0) {
        *b = c;
        b++;
        n--;
    }

    return b;
}


HPDF_UINT
HPDF_StrLen  (const char   *s,
              HPDF_INT      maxlen)
{
    HPDF_INT len = 0;

    if (!s)
        return 0;

    while (*s != 0 && (maxlen < 0 || len < maxlen)) {
        s++;
        len++;
    }

    return (HPDF_UINT)len;
}


const char*
HPDF_StrStr  (const char   *s1,
              const char   *s2,
              HPDF_UINT     maxlen)
{
    HPDF_UINT len = HPDF_StrLen (s2, -1);

    if (!s1)
        return NULL;

    if (len == 0)
        return s1;

    if (maxlen == 0)
        maxlen = HPDF_StrLen (s1, -1);

    if (maxlen < len)
        return NULL;

    maxlen -= len;
    maxlen++;

    while (maxlen > 0) {
        if (HPDF_MemCmp ((HPDF_BYTE *)s1, (HPDF_BYTE *)s2, len) == 0)
            return s1;

        s1++;
        maxlen--;
    }

    return NULL;
}


HPDF_Box
HPDF_ToBox  (HPDF_INT16   left,
             HPDF_INT16   bottom,
             HPDF_INT16   right,
             HPDF_INT16   top)
{
    HPDF_Box box;

    box.left = left;
    box.bottom = bottom;
    box.right = right;
    box.top = top;

    return box;
}


HPDF_Point
HPDF_ToPoint  (HPDF_INT16   x,
               HPDF_INT16   y)
{
    HPDF_Point point;

    point.x = x;
    point.y = y;

    return point;
}

HPDF_Rect
HPDF_ToRect  (HPDF_REAL   left,
              HPDF_REAL   bottom,
              HPDF_REAL   right,
              HPDF_REAL   top)
{
    HPDF_Rect rect;

    rect.left = left;
    rect.bottom = bottom;
    rect.right = right;
    rect.top = top;

    return rect;
}


void
HPDF_UInt16Swap  (HPDF_UINT16  *value)
{
    HPDF_BYTE u[2];

    HPDF_MemCpy (u, (HPDF_BYTE*)value, 2);
    *value = (HPDF_UINT16)((HPDF_UINT16)u[0] << 8 | (HPDF_UINT16)u[1]);
}

const char*
HPDF_PageSizeName (HPDF_PageSizes size)
{
    return HPDF_PREDEFINED_PAGE_SIZE_NAMES[size];
}

HPDF_TransMatrix
HPDF_Matrix_Multiply (HPDF_TransMatrix m, HPDF_TransMatrix n)
{
    HPDF_TransMatrix r;

    /*

    | a' b' 0 |   | a" b" 0 |   | a'a" b'c" 0'x"  a'b" b'd" 0'y"  a'0" b'0" 0'1" |
    | c' d' 0 | x | c" d" 0 | = | c'a" d'c" 0'x"  c'b" d'd" 0'y"  c'0" d'0" 0'1" |
    | x' y' 1 |   | x" y" 1 |   | x'a" y'c" 1'x"  x'b" y'd" 1'y"  x'0" y'0" 1'1" |

    | m.a m.b 0 |   | n.a n.b 0 |   | m.a*n.a+m.b*n.c      m.a*n.b+m.b*n.d      0 |
    | m.c m.d 0 | x | n.c n.d 0 | = | m.c*n.a+m.d*n.c      m.c*n.b+m.d*n.d      0 |
    | m.x m.y 1 |   | n.x n.y 1 |   | m.x*n.a+m.y*n.c+n.x  m.x*n.b+m.y*n.d+*n.y 1 |

    */

    r.a = m.a*n.a + m.b*n.c;
    r.b = m.a*n.b + m.b*n.d;
    r.c = m.c*n.a + m.d*n.c;
    r.d = m.c*n.b + m.d*n.d;
    r.x = m.x*n.a + m.y*n.c + n.x;
    r.y = m.x*n.b + m.y*n.d + n.y;

    return r;
}

HPDF_TransMatrix
HPDF_Matrix_Translate (HPDF_TransMatrix m, HPDF_REAL dx, HPDF_REAL dy)
{
    HPDF_TransMatrix translate = {1, 0, 0, 1, dx, dy};
    return HPDF_Matrix_Multiply (m, translate);
}

HPDF_TransMatrix
HPDF_Matrix_Scale (HPDF_TransMatrix m, HPDF_REAL sx, HPDF_REAL sy)
{
    HPDF_TransMatrix scale = {sx, 0, 0, sy, 0, 0};
    return HPDF_Matrix_Multiply (m, scale);
}

HPDF_TransMatrix
HPDF_Matrix_Rotate (HPDF_TransMatrix m, HPDF_REAL angle)
{
    HPDF_TransMatrix rotate = {cos(angle), sin(angle), -sin(angle), cos(angle), 0, 0};
    return HPDF_Matrix_Multiply (rotate, m);
}

HPDF_TransMatrix
HPDF_Matrix_RotateDeg (HPDF_TransMatrix m, HPDF_REAL degrees)
{
    HPDF_REAL angle = degrees * HPDF_PI / 180.0;

    HPDF_TransMatrix rotate = {cos(angle), sin(angle), -sin(angle), cos(angle), 0, 0};
    return HPDF_Matrix_Multiply (m, rotate);
}

HPDF_TransMatrix
HPDF_Matrix_Skew (HPDF_TransMatrix m, HPDF_REAL a, HPDF_REAL b)
{
    HPDF_TransMatrix skew = {1, tan(a), tan(b), 1, 0, 0};
    return HPDF_Matrix_Multiply (m, skew);
}
