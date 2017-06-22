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

#include "meta.h"

#define BUFFER_SIZE 4096

#define SHA256_HASH_SIZE 32

int meta_prop_write_str(const char* name, const char* value, JSON* json)
{
    if (!value)
        return 0;
    json_write_prop_string(name, value, json);
    return -1;
}

static int sha256(FILE* f, meta_hash_item_t* hash)
{
	struct sha256_state ctx;
	int len;
	unsigned char buffer[BUFFER_SIZE];

	sha256_init(&ctx);

	while ((len = (fread(buffer, 1, BUFFER_SIZE, f))) > 0)
		if (sha256_process(&ctx, buffer, len))
			return -1;

	if (sha256_done(&ctx, hash->hash))
		return -1;

	hash->size = SHA256_HASH_SIZE;
	return 0;
}

int meta_hash_calc(const char* basepath, meta_hash_item_t* hash, const char* name)
{
	char in_path[64];
	FILE* fin;
	int result;

	if (name == NULL)
	{
#if GEN_META
        fprintf(stderr, "Missing hash name\n");
#endif
		return -1;
	}

	if (basepath != NULL)
		sprintf(in_path, "%s/%s", basepath, hash->filename);
	else
		sprintf(in_path, hash->filename);

	if ((fin = fopen(in_path, "rb")) == NULL)
	{
#if GEN_META
        fprintf(stderr, "Error opening %s\n", in_path);
#endif
		return -1;
	}

	if (!strcmp(name, "sha256"))
		result = sha256(fin, hash);
	else
		result = -2;

	fclose(fin);

	if (result == -1)
	{
#if GEN_META
        fprintf(stderr, "Error processing %s\n", in_path);
#endif
		return -1;
	}
	if (result == -2)
	{
#if GEN_META
        fprintf(stderr, "Invalid hash name: %s\n", name);
#endif
		return -1;
	}

	return 0;
}

void meta_category_init(meta_category_t* category)
{
	category->name = NULL;
}

int meta_category_write(const meta_category_t* category, JSON* json)
{
	int result = 0;
	json_write_string("category", json);
	json_write_prop_sep(json);
	json_write_object_start(json);
	if (!meta_prop_write_str("name", category->name, json))
	{
#if GEN_META
        fprintf(stderr, "Missing category name\n");
#endif
		result = -1;
	}
	json_write_object_end(json);
	return result;
}

static char meta_hash_get_char(unsigned char c)
{
	return c <= 9 ? c + 0x30 : c + 0x57;
}

static void meta_hash_str_write(const meta_hash_item_t* hash, JSON* json)
{
	static char str[SHA256_BLOCK_SIZE + 1];
	int i, j;
	for (i = 0, j = 0; i < hash->size; i++)
	{
		str[j++] = meta_hash_get_char(hash->hash[i] / 16);
		str[j++] = meta_hash_get_char(hash->hash[i] % 16);
	}
	str[j] = 0;
	json_write_string(str, json);
}

static void meta_hash_item_write(const meta_hash_item_t* hash, JSON* json)
{
	int i;
	char lower[64];
	for (i = 0; i < strlen(hash->filename); i++)
		lower[i] = tolower(hash->filename[i]);
	lower[i] = '\0';
	json_write_string(lower, json);
	json_write_prop_sep(json);
	meta_hash_str_write(hash, json);
}

void meta_hash_init(meta_hash_t* hash)
{
	hash->name = NULL;
	hash->items = NULL;
	hash->count = 0;
}

int meta_hash_write(const meta_hash_t* hash, JSON* json)
{
	int i;
	json_write_string("hash", json);
	json_write_prop_sep(json);
	json_write_object_start(json);
	if (hash->name != NULL)
	{
		json_write_string("name", json);
		json_write_prop_sep(json);
		json_write_string(hash->name, json);
		json_write_object_array_sep(json);
	}
	if (hash->items != NULL)
	{
		json_write_string("values", json);
		json_write_prop_sep(json);
		json_write_object_start(json);
		for (i = 0; i < hash->count; i++)
		{
			meta_hash_item_write(&hash->items[i], json);
			if (i < hash->count - 1)
				json_write_object_array_sep(json);
		}
		json_write_object_end(json);
	}
	json_write_object_end(json);
	return 0;
}
