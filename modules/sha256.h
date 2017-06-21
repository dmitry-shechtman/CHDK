/*
 * SHA-256 internal definitions
 * Copyright (c) 2003-2011, Jouni Malinen <j@w1.fi>
 *
 * Modified for CHDK by Dmitry Shechtman
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef SHA256_I_H
#define SHA256_I_H

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

#define SHA256_BLOCK_SIZE 64

struct sha256_state {
	u64 length;
	u32 state[8], curlen;
	u8 buf[SHA256_BLOCK_SIZE];
};

void sha256_init(struct sha256_state *md);
int sha256_process(struct sha256_state *md, const unsigned char *in,
		   unsigned long inlen);
int sha256_done(struct sha256_state *md, unsigned char *out);

#endif /* SHA256_I_H */
