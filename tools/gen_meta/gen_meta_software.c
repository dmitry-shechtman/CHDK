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
#include "cli.h"
#include "dancingbits.h"

typedef struct
{
	const char* name;
	const char* version;
	const char* versionPrefix;
	const char* language;
	const char* created;
}
meta_product_t;

static void meta_product_init(meta_product_t* product)
{
	product->name = NULL;
	product->version = NULL;
	product->versionPrefix = NULL;
	product->language = NULL;
	product->created = NULL;
}

static int meta_software_category_write(const meta_category_t* category, JSON* json)
{
	json_write_string("category", json);
	json_write_prop_sep(json);
	return meta_category_write(category, json);
}

static int meta_software_hash_write(const meta_hash_t* hash, JSON* json)
{
	json_write_string("hash", json);
	json_write_prop_sep(json);
	return meta_hash_write(hash, json);
}

static int meta_product_write(const meta_product_t* product, JSON* json)
{
	int result = 0;
	json_write_string("product", json);
	json_write_prop_sep(json);
	json_write_object_start(json);

	if (!meta_prop_write_str("name", product->name, json))
	{
		fprintf(stderr, "Missing product name\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("version", product->version, json))
	{
		fprintf(stderr, "Missing product version\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("language", product->language, json))
	{
		fprintf(stderr, "Missing product language\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("created", product->created, json))
	{
		fprintf(stderr, "Missing product creation date\n");
		result = -1;
	}

	if (product->versionPrefix)
	{
		json_write_object_array_sep(json);
		meta_prop_write_str("versionPrefix", product->versionPrefix, json);
	}

	json_write_object_end(json);
	return result;
}

typedef struct
{
	const char* platform;
	const char* revision;
}
meta_camera_t;

static void meta_camera_init(meta_camera_t* camera)
{
	camera->platform = NULL;
	camera->revision = NULL;
}

static int meta_camera_write(const meta_camera_t* camera, JSON* json)
{
	int result = 0;
	json_write_string("camera", json);
	json_write_prop_sep(json);
	json_write_object_start(json);

	if (!meta_prop_write_str("platform", camera->platform, json))
	{
		fprintf(stderr, "Missing camera platform\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("revision", camera->revision, json))
	{
		fprintf(stderr, "Missing camera revision\n");
		result = -1;
	}

	json_write_object_end(json);
	return result;
}

typedef struct
{
	const char* name;
	const char* status;
	const char* changeset;
	const char* creator;
}
meta_build_t;

static void meta_build_init(meta_build_t* build)
{
	build->name = NULL;
	build->status = NULL;
	build->changeset = NULL;
	build->creator = NULL;
}

static int meta_build_write(const meta_build_t* build, JSON* json)
{
	int result = 0;
	json_write_string("build", json);
	json_write_prop_sep(json);
	json_write_object_start(json);

	if (!meta_prop_write_str("name", build->name, json))
	{
		fprintf(stderr, "Missing build name\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("status", build->status, json))
	{
		fprintf(stderr, "Missing build status\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("changeset", build->changeset, json))
	{
		fprintf(stderr, "Missing build changeset\n");
		result = -1;
	}

	if (build->creator != NULL)
	{
		json_write_object_array_sep(json);
		meta_prop_write_str("creator", build->creator, json);
	}

	json_write_object_end(json);
	return result;
}

typedef struct
{
	const char* name;
	const char* platform;
	const char* version;
}
meta_compiler_t;

static void meta_compiler_init(meta_compiler_t* compiler)
{
	compiler->name = NULL;
	compiler->platform = NULL;
	compiler->version = NULL;
}

static int meta_compiler_write(const meta_compiler_t* compiler, JSON* json)
{
	int result = 0;
	json_write_string("compiler", json);
	json_write_prop_sep(json);
	json_write_object_start(json);

	if (!meta_prop_write_str("name", compiler->name, json))
	{
		fprintf(stderr, "Missing compiler name\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("platform", compiler->platform, json))
	{
		fprintf(stderr, "Missing compiler platform\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("version", compiler->version, json))
	{
		fprintf(stderr, "Missing compiler version\n");
		result = -1;
	}

	json_write_object_end(json);
	return result;
}

typedef struct
{
	const char* name;
	const char* channel;
	const char* url;
}
meta_source_t;

static void meta_source_init(meta_source_t* source)
{
	source->name = NULL;
	source->channel = NULL;
	source->url = NULL;
}

static int meta_source_write(const meta_source_t* source, JSON* json)
{
	int result = 0;
	json_write_string("source", json);
	json_write_prop_sep(json);
	json_write_object_start(json);

	if (!meta_prop_write_str("name", source->name, json))
	{
		fprintf(stderr, "Missing source name\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("channel", source->channel, json))
	{
		fprintf(stderr, "Missing source channel\n");
		result = -1;
	}
	else
	{
		json_write_object_array_sep(json);
	}

	if (!meta_prop_write_str("url", source->url, json))
	{
		fprintf(stderr, "Missing source url\n");
		result = -1;
	}

	json_write_object_end(json);
	return result;
}

typedef struct
{
	const char* name;
	int version;
}
meta_encoding_t;

static void meta_encoding_init(meta_encoding_t* encoding)
{
	encoding->name = NULL;
	encoding->version = 0;
}

static int meta_encoding_write(const meta_encoding_t* encoding, JSON* json)
{
	int result = 0;

	json_write_string("encoding", json);
	json_write_prop_sep(json);
	json_write_object_start(json);
	if (!meta_prop_write_str("name", encoding->name, json))
	{
		fprintf(stderr, "Missing encoding name\n");
		result = -1;
	}

	if (encoding->version > 0 && encoding->version <= VITALY)
	{
		if (encoding->name != NULL)
			json_write_object_array_sep(json);
		static char str[12];
		int i, j;
		j = 0;
		str[j++] = '0';
		str[j++] = 'x';
		for (i = 7; i >= 0; i--)
			str[j++] = _chr_[encoding->version - 1][i] + 0x30;
		str[j] = 0;
		json_write_prop_string("data", str, json);
	}
	json_write_object_end(json);

	return result;
}

typedef struct
{
	meta_category_t category;
	meta_product_t product;
	meta_camera_t camera;
	meta_build_t build;
	meta_compiler_t compiler;
	meta_source_t source;
	meta_encoding_t encoding;
	meta_hash_t hash;
}
meta_software_t;

static void meta_software_init(meta_software_t* software)
{
	meta_category_init(&software->category);
	meta_product_init(&software->product);
	meta_camera_init(&software->camera);
	meta_build_init(&software->build);
	meta_compiler_init(&software->compiler);
	meta_source_init(&software->source);
	meta_encoding_init(&software->encoding);
	meta_hash_init(&software->hash);
}

static int meta_software_write(const meta_software_t* software, JSON* json)
{
	int result = 0;
	json_write_object_start(json);
	result |= ~meta_prop_write_str("version", "1.0", json);
	json_write_object_array_sep(json);
	result |= meta_software_category_write(&software->category, json);
	json_write_object_array_sep(json);
	result |= meta_product_write(&software->product, json);
	json_write_object_array_sep(json);
	result |= meta_camera_write(&software->camera, json);
	json_write_object_array_sep(json);
	result |= meta_build_write(&software->build, json);
	json_write_object_array_sep(json);
	result |= meta_compiler_write(&software->compiler, json);
	json_write_object_array_sep(json);
	if (software->source.url != NULL)
	{
		result |= meta_source_write(&software->source, json);
		json_write_object_array_sep(json);
	}
	result |= meta_encoding_write(&software->encoding, json);
	json_write_object_array_sep(json);
	result |= meta_software_hash_write(&software->hash, json);
	json_write_object_end(json);
	return result;
}

static int usage()
{
	printf("\nUsage:\n");
	printf("\tgen_meta_software <category> <filename> [<basepath>] <flags>\n");
	printf("\nParams:\n");
	printf("\t<category>  Category name (EOS or PS)\n");
	printf("\t<filename>  File name (AUTOEXEC.BIN or DISKBOOT.BIN)\n");
	printf("\t<basepath>  Base path (optional)\n");
	printf("\nFlags:\n");
	printf("\t--product-name            Product name\n");
	printf("\t--product-version         Product version\n");
	printf("\t--product-version-prefix  Product version prefix (optional)\n");
	printf("\t--product-language        Product language\n");
	printf("\t--product-created         Product creation date\n");
	printf("\t--camera-platform         Camera platform\n");
	printf("\t--camera-revision         Camera revision\n");
	printf("\t--build-name              Build name (optional)\n");
	printf("\t--build-status            Build status (optional)\n");
	printf("\t--build-changeset         Build changeset\n");
	printf("\t--build-creator           Build creator (optional)\n");
	printf("\t--compiler-name           Compiler name\n");
	printf("\t--compiler-platform       Compiler platform\n");
	printf("\t--compiler-version        Compiler version\n");
	printf("\t--source-name             Source name\n");
	printf("\t--source-channel          Source channel (optional)\n");
	printf("\t--source-url              Source url (optional)\n");
	printf("\t--encoding-name           Encoding name (optional)\n");
	printf("\t--encoding-version        Encoding version (optional)\n");
	printf("\t--hash-name               Hash name (optional)\n");
	return -1;
}

static int version()
{
	printf("gen_meta_software version 1.0\n");
	return 1;
}

static int parse_args(int argc, char const* argv[], meta_software_t* software, char const** category, char const** filename, char const** basepath)
{
	int i = 1;
	while (i < argc)
	{
		if (cli_flag_bool("--version", argc, argv, &i))
			return 1;
		if (cli_flag_bool("--help", argc, argv, &i))
			return -1;
		if (!cli_flag_str("--product-name", argc, argv, &i, &software->product.name)
			&& !cli_flag_str("--product-version", argc, argv, &i, &software->product.version)
			&& !cli_flag_str("--product-version-prefix", argc, argv, &i, &software->product.versionPrefix)
			&& !cli_flag_str("--product-language", argc, argv, &i, &software->product.language)
			&& !cli_flag_str("--product-created", argc, argv, &i, &software->product.created)
			&& !cli_flag_str("--camera-platform", argc, argv, &i, &software->camera.platform)
			&& !cli_flag_str("--camera-revision", argc, argv, &i, &software->camera.revision)
			&& !cli_flag_str("--build-name", argc, argv, &i, &software->build.name)
			&& !cli_flag_str("--build-status", argc, argv, &i, &software->build.status)
			&& !cli_flag_str("--build-changeset", argc, argv, &i, &software->build.changeset)
			&& !cli_flag_str("--build-creator", argc, argv, &i, &software->build.creator)
			&& !cli_flag_str("--compiler-name", argc, argv, &i, &software->compiler.name)
			&& !cli_flag_str("--compiler-platform", argc, argv, &i, &software->compiler.platform)
			&& !cli_flag_str("--compiler-version", argc, argv, &i, &software->compiler.version)
			&& !cli_flag_str("--source-name", argc, argv, &i, &software->source.name)
			&& !cli_flag_str("--source-channel", argc, argv, &i, &software->source.channel)
			&& !cli_flag_str("--source-url", argc, argv, &i, &software->source.url)
			&& !cli_flag_str("--encoding-name", argc, argv, &i, &software->encoding.name)
			&& !cli_flag_int("--encoding-version", argc, argv, &i, &software->encoding.version)
			&& !cli_flag_str("--hash-name", argc, argv, &i, &software->hash.name))
		{
			if (*category == NULL)
				*category = argv[i];
			else if (*filename == NULL)
				*filename = argv[i];
			else if (*basepath == NULL)
				*basepath = argv[i];
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
	meta_software_t software;
	const char* category = NULL;
	const char* filename = NULL;
	const char* basepath = NULL;
	meta_hash_item_t hash_item;
	char out_path[64];
	int result;
	FILE* fout;
	JSON* json;

	meta_software_init(&software);

	software.build.name = "";
	software.build.status = "";
	software.source.channel = "";
	software.encoding.name = "";

	if ((result = parse_args(argc, argv, &software, &category, &filename, &basepath)) == 0)
	{
		if (category == NULL)
		{
			fprintf(stderr, "Missing category\n");
			result = -1;
		}
		if (filename == NULL)
		{
			fprintf(stderr, "Missing filename\n");
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

	if (basepath == NULL)
		basepath = ".";

	if (software.hash.name == NULL)
		software.hash.name = "sha256";

	software.category.name = category;

	hash_item.filename = (char*)filename;
	hash_item.size = 0;
	software.hash.items = &hash_item;
	software.hash.count = 1;
	meta_hash_calc(basepath, &hash_item, software.hash.name);

	sprintf(out_path, "_HDKMETA/%s/SOFTWARE.JSN", category);
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

	if ((result = meta_software_write(&software, json)))
	{
		usage();
	}

	json_close(json);
	fclose(fout);

	return result;
}
