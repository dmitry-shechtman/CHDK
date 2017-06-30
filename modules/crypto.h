/*
 * Based on work by Dave Hansen <dave@sr71.net>
 * original licensing:
 * This software may be redistributed and/or modified under the terms of
 * the GNU General Public License ("GPL") version 2 as published by the
 * Free Software Foundation.
 */

#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdlib.h>

#ifndef __FLT_H__
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef signed short int16_t;
#endif

typedef unsigned long long uint64_t;
typedef unsigned char uint8_t;
typedef signed long long int64_t;
typedef signed char int8_t;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

#ifndef os_memset
#define os_memset(d, s, n) memset((d), (s), (n))
#endif

#ifndef os_memcpy
#define os_memcpy(d, s, n) memcpy((d), (s), (n))
#endif

static inline u32 WPA_GET_BE32(const u8 *a)
{
    return ((u32)a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3];
}

static inline void WPA_PUT_BE32(u8 *a, u32 val)
{
    a[0] = (val >> 24) & 0xff;
    a[1] = (val >> 16) & 0xff;
    a[2] = (val >> 8) & 0xff;
    a[3] = val & 0xff;
}

static inline u64 WPA_GET_BE64(const u8 *a)
{
    return (((u64)a[0]) << 56) | (((u64)a[1]) << 48) |
        (((u64)a[2]) << 40) | (((u64)a[3]) << 32) |
        (((u64)a[4]) << 24) | (((u64)a[5]) << 16) |
        (((u64)a[6]) << 8) | ((u64)a[7]);
}

static inline void WPA_PUT_BE64(u8 *a, u64 val)
{
    a[0] = val >> 56;
    a[1] = val >> 48;
    a[2] = val >> 40;
    a[3] = val >> 32;
    a[4] = val >> 24;
    a[5] = val >> 16;
    a[6] = val >> 8;
    a[7] = val & 0xff;
}

#endif /* CRYPTO_H */
