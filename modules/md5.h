/*
 * MD5 internal definitions
 * Copyright (c) 2003-2005, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 * modified for CHDK by buttim@hotmail.com
 */

#ifndef MD5_I_H
#define MD5_I_H

#include <stddef.h>

#include "crypto.h"

struct MD5Context {
	u32 buf[4];
	u32 bits[2];
	u8 in[64];
};

#define MD5_MAC_LEN 16

void md5_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac);

typedef struct MD5Context MD5_CTX;

#ifndef CONFIG_CRYPTO_INTERNAL
void MD5Init(struct MD5Context *context);
int MD5Update(struct MD5Context *context, unsigned char const *buf, unsigned len);
int MD5Final(struct MD5Context *context, unsigned char digest[16]);
#endif /* CONFIG_CRYPTO_INTERNAL */

#endif /* MD5_I_H */
