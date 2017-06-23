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

#include <dirent.h>

#include "../include/versions.h"
#include "flt.h"
#include "meta_modules.h"
#include "cli.h"

static int usage()
{
	printf("\nUsage:\n");
	printf("\tgen_meta_modules <category> <modpath> <flags>\n");
	printf("\nParams:\n");
	printf("\t<category>  Category name (EOS or PS)\n");
	printf("\t<modpath>   Modules path\n");
	printf("\nFlags:\n");
	printf("\t--product-name            Product name\n");
	printf("\t--product-created         Product creation date\n");
	printf("\t--build-changeset         Build changeset\n");
	return -1;
}

static int version()
{
	printf("gen_meta_modules version 1.0\n");
	return 1;
}

static int parse_args(int argc, char const* argv[], char const** category, char const** modpath, char const** product, char const** created, char const** changeset)
{
	int i = 1;
    while (i < argc)
	{
		if (cli_flag_bool("--version", argc, argv, &i))
			return 1;
		if (cli_flag_bool("--help", argc, argv, &i))
			return -1;
		if (!cli_flag_str("--product-name", argc, argv, &i, product)
			&& !cli_flag_str("--product-created", argc, argv, &i, created)
            && !cli_flag_str("--build-changeset", argc, argv, &i, changeset))
		{
			if (*category == NULL)
				*category = argv[i];
			else if (*modpath == NULL)
				*modpath = argv[i];
			else
			{
				fprintf(stderr, "Invalid option: %s\n", argv[i]);
				return -1;
			}
		}
		i++;
	}

	return 0;
}

#define MODULE_TYPE_COUNT 5

static char* module_types[MODULE_TYPE_COUNT] = { 0, "extension", "game", "tool", "script" };

static int gen_meta_modules_get(meta_modules_t* modules, const char* modPath, const char* created, const char* changeset) {
    DIR *d;
    struct dirent *de;
    static ModuleInfo mi;
    static char modName[33];
    static const char hash_name[] = "sha256";
    static unsigned char sha256[SHA256_HASH_SIZE];
    meta_modules_item_t* item;
    int i = 0;
    if (!modules || !modPath) {
        return 0;
    }
    if (!(d = opendir(modPath))) {
        return 0;
    }
    modules->count = 0;
    while ((de = readdir(d))) {
        if (de->d_name[0] != 0xE5 && strcmp(de->d_name, ".") && strcmp(de->d_name, "..") && strcmp(de->d_name, "CFG")) {
            modules->count++;
        }
    }
    closedir(d);
    if (!(modules->modules = malloc(modules->count * sizeof(meta_modules_item_t)))) {
        return 0;
    }
    if (!(d = opendir(modPath))) {
        free(modules->modules);
        modules->modules = 0;
        modules->count = 0;
        return 0;
    }
    while ((de = readdir(d))) {
        if (de->d_name[0] != 0xE5 && strcmp(de->d_name, ".") && strcmp(de->d_name, "..") && strcmp(de->d_name, "CFG")) {
            item = &modules->modules[i++];
            get_module_info_and_hash(modPath, de->d_name, &mi, modName, sizeof(modName), sha256);
            if ((item->key = malloc(strlen(de->d_name) + 1))) {
                meta_strtolower(item->key, de->d_name);
            }
            item->value.typeId = mi.moduleType & MTYPE_MASK;
            if (item->value.typeId < MODULE_TYPE_COUNT)
                item->value.type = module_types[item->value.typeId];
            else
                item->value.type = 0;
            item->value.titleId = mi.moduleName < 0 ? -mi.moduleName : 0;
            if (mi.moduleName < 0) {
                item->value.title = 0;
            }
            else if ((item->value.title = malloc(strlen(modName) + 1))) {
                strcpy(item->value.title, modName);
            }
            item->value.imageId = mi.symbol;
            item->value.created = created;
            item->value.changeset = changeset;
            item->value.hash.name = hash_name;
            if ((item->value.hash.items = malloc(sizeof(meta_hash_item_t)))) {
                if ((item->value.hash.items[0].filename = malloc(strlen(de->d_name) + 14))) {
                    sprintf(item->value.hash.items[0].filename, "CHDK\\MODULES\\%s", item->key);
                }
                memcpy(item->value.hash.items[0].hash, sha256, SHA256_HASH_SIZE);
                item->value.hash.items[0].size = SHA256_HASH_SIZE;
                item->value.hash.count = 1;
            }
        }
    }
    closedir(d);
    return -1;
}

int main(int argc, char const* argv[])
{
    meta_modules_t modules;
    const char* category = NULL;
    const char* product = NULL;
	const char* modpath = NULL;
    const char* created = NULL;
    const char* changeset = NULL;
    char out_path[64];
	int result;
	FILE* fout;
	JSON* json;

    if ((result = parse_args(argc, argv, &category, &modpath, &product, &created, &changeset)) == 0)
	{
        if (category == NULL)
		{
			fprintf(stderr, "Missing category name\n");
			result = -1;
		}
        if (modpath == NULL)
		{
			fprintf(stderr, "Missing module path\n");
			result = -1;
		}
        if (product == NULL)
        {
            fprintf(stderr, "Missing product name\n");
            result = -1;
        }
        if (created == NULL)
        {
            fprintf(stderr, "Missing creation date\n");
            result = -1;
        }
        if (changeset == NULL)
        {
            fprintf(stderr, "Missing changeset\n");
            result = -1;
        }
    }

	if (result == -1)
	{
		return usage();
	}
	if (result == 1)
	{
		return version();
	}

    modules.version = "1.0";
    modules.category.name = category;
    modules.product.name = product;

    if (!gen_meta_modules_get(&modules, modpath, created, changeset))
    {
        fprintf(stderr, "Error scanning %s\n", modpath);
        return -1;
    }

    sprintf(out_path, "_HDKMETA/%s/MODULES.JSN", modules.category.name);
	if ((fout = fopen(out_path, "w")) == NULL)
	{
		fprintf(stderr, "Error opening %s\n", out_path);
		return -1;
	}

	if ((json = json_open(fout)) == NULL)
	{
		fprintf(stderr, "Error opening JSON\n");
		fclose(fout);
		return -1;
	}

    meta_modules_write(&modules, json);
	json_close(json);
	fclose(fout);

    meta_modules_free(&modules);

	return result;
}
