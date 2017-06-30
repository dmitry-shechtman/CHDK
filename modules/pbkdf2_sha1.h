/*
 * PBKDF2-SHA1 definitions
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

#ifndef PBKDF2_SHA1_H
#define PBKDF2_SHA1_H

#include <stddef.h>

#include "crypto.h"

void pbkdf2_sha1(const char *passphrase, const char *ssid, size_t ssid_len, int iterations, u8 *buf, size_t buflen);

#endif
