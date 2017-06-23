/*
 * SHA1 hash implementation and interface functions
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

#ifndef SHA1_I_H
#define SHA1_I_H

#include "eyefi.h"

struct SHA1Context {
    u32 state[5];
    u32 count[2];
    unsigned char buffer[64];
};

typedef struct SHA1Context SHA1_CTX;

#ifndef CONFIG_CRYPTO_INTERNAL
void SHA1Init(struct SHA1Context *context);
int SHA1Update(struct SHA1Context *context, const void *data, u32 len);
int SHA1Final(struct SHA1Context *context, unsigned char digest[20]);
#endif /* CONFIG_CRYPTO_INTERNAL */

#endif /* SHA256_I_H */
