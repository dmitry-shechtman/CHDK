/*
 * SHA-512 internal definitions
 * Copyright (c) 2015, Pali Rohár <pali.rohar@gmail.com>
 *
 * Modified for CHDK by Dmitry Shechtman
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef SHA512_I_H
#define SHA512_I_H

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

#define SHA512_BLOCK_SIZE 128

struct sha512_state {
	u64 length, state[8];
	u32 curlen;
	u8 buf[SHA512_BLOCK_SIZE];
};

void sha512_init(struct sha512_state *md);
int sha512_process(struct sha512_state *md, const unsigned char *in,
		   unsigned long inlen);
int sha512_done(struct sha512_state *md, unsigned char *out);

#endif /* SHA512_I_H */
