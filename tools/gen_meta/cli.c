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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

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
