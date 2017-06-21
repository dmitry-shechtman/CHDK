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

#include "gen_meta.h"

#define BUFFER_SIZE 4096

#define SHA256_HASH_SIZE 32

static int sha256(FILE* f, meta_hash_item_t* hash)
{
	struct sha256_state ctx;
	size_t len;
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
		fprintf(stderr, "Missing hash name\n");
		return -1;
	}

	if (basepath != NULL)
		sprintf(in_path, "%s/%s", basepath, hash->filename);
	else
		sprintf(in_path, hash->filename);

	if ((fin = fopen(in_path, "rb")) == NULL)
	{
		fprintf(stderr, "Error opening %s\n", in_path);
		return -1;
	}

	if (!strcmp(name, "sha256"))
		result = sha256(fin, hash);
	else
		result = -2;

	fclose(fin);

	if (result == -1)
	{
		fprintf(stderr, "Error processing %s\n", in_path);
		return -1;
	}
	if (result == -2)
	{
		fprintf(stderr, "Invalid hash name: %s\n", name);
		return -1;
	}

	return 0;
}

void meta_map_write_start(FILE *fout)
{
	fputc('{', fout);
}

void meta_map_write_end(FILE* fout)
{
	fputc('}', fout);
}

void meta_map_write_delim(FILE* fout)
{
	fputc(',', fout);
}

static void meta_str_write(const char* s, FILE* fout)
{
	fputc('"', fout);
	fputs(s, fout);
	fputc('"', fout);
}

void meta_prop_write(const char* s, FILE* fout)
{
	meta_str_write(s, fout);
	fputc(':', fout);
}

int meta_prop_write_str(const char* name, const char* value, FILE* fout)
{
	if (!value)
		return 0;
	meta_prop_write(name, fout);
	meta_str_write(value, fout);
	return -1;
}

void meta_category_init(meta_category_t* category)
{
	category->name = NULL;
}

int meta_category_write(const meta_category_t* category, FILE* fout)
{
	int result = 0;
	meta_prop_write("category", fout);
	meta_map_write_start(fout);
	if (!meta_prop_write_str("name", category->name, fout))
	{
		fprintf(stderr, "Missing category name\n");
		result = -1;
	}
	meta_map_write_end(fout);
	return result;
}

static void meta_hash_char_write(unsigned char c, FILE* fout)
{
	putc(c <= 9 ? c + 0x30 : c + 0x57, fout);
}

static void meta_hash_str_write(const meta_hash_item_t* hash, FILE* fout)
{
	int i;
	fputc('"', fout);
	for (i = 0; i < hash->size; i++)
	{
		meta_hash_char_write(hash->hash[i] / 16, fout);
		meta_hash_char_write(hash->hash[i] % 16, fout);
	}
	fputc('"', fout);
}

static void meta_hash_item_write(const meta_hash_item_t* hash, FILE* fout)
{
	size_t i;
	char lower[64];
	for (i = 0; i < strlen(hash->filename); i++)
		lower[i] = tolower(hash->filename[i]);
	lower[i] = '\0';
	meta_prop_write(lower, fout);
	meta_hash_str_write(hash, fout);
}

void meta_hash_init(meta_hash_t* hash)
{
	hash->name = NULL;
	hash->items = NULL;
	hash->count = 0;
}

int meta_hash_write(const meta_hash_t* hash, FILE* fout)
{
	size_t i;
	meta_prop_write("hash", fout);
	meta_map_write_start(fout);
	if (hash->name != NULL)
	{
		meta_prop_write("name", fout);
		meta_str_write(hash->name, fout);
		meta_map_write_delim(fout);
	}
	if (hash->items != NULL)
	{
		meta_prop_write("values", fout);
		meta_map_write_start(fout);
		for (i = 0; i < hash->count; i++)
		{
			meta_hash_item_write(&hash->items[i], fout);
			if (i < hash->count - 1)
				meta_map_write_delim(fout);
		}
		meta_map_write_end(fout);
	}
	meta_map_write_end(fout);
	return 0;
}

int cli_flag_bool(const char* name, int argc, char const* argv[], int* i)
{
	if (!strcmp(name, argv[*i]))
	{
		return -1;
	}
	return 0;
}

int cli_flag_int(const char* name, int argc, char const* argv[], int* i, int* value)
{
	if (!strcmp(name, argv[*i]) && *i < argc - 1)
	{
		if (*value != 0)
		{
			fprintf(stderr, "Value already set\n");
			return 0;
		}
		*value = atoi(argv[*i + 1]);
		(*i)++;
		return -1;
	}
	return 0;
}

int cli_flag_str(const char* name, int argc, char const* argv[], int* i, const char** value)
{
	if (!strcmp(name, argv[*i]) && *i < argc - 1)
	{
		if (*value != NULL && **value != '\0')
		{
			fprintf(stderr, "Value already set\n");
			return 0;
		}
		*value = argv[*i + 1];
		(*i)++;
		return -1;
	}
	return 0;
}
