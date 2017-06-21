/*
 * CHIMP metadata generator
 *
 * Copyright © 2017 Dmitry Shechtman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef GEN_META_H
#define GEN_META_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha256.h"
#include "json.h"

int meta_prop_write_str(const char* name, const char* value, JSON* json);

typedef struct
{
	const char* name;
}
meta_category_t;

void meta_category_init(meta_category_t* category);
int meta_category_write(const meta_category_t* category, JSON* json);

typedef struct
{
	const char* filename;
	unsigned char hash[SHA256_BLOCK_SIZE + 1];
	size_t size;
}
meta_hash_item_t;

int meta_hash_calc(const char* basepath, meta_hash_item_t* hash, const char* name);

typedef struct
{
	const char* name;
	meta_hash_item_t* items;
	int count;
}
meta_hash_t;

void meta_hash_init(meta_hash_t* hash);
int meta_hash_write(const meta_hash_t* hash, JSON* json);

int cli_flag_bool(const char* name, int argc, char const* argv[], int* i);
int cli_flag_int(const char* name, int argc, char const* argv[], int* i, int* value);
int cli_flag_str(const char* name, int argc, char const* argv[], int* i, const char** value);

#endif /* GEN_META_H */
