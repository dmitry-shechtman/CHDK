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

int main(int argc, char const* argv[])
{
    meta_modules_t modules = { "1.0" };
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

    modules.category.name = category;
    modules.product.name = product;

    if (!meta_modules_get(&modules, modpath, created, changeset))
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

	return result;
}
