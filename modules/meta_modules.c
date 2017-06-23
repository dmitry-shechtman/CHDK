#include <stdlib.h>

#include "versions.h"
#include "flt.h"
#include "meta_modules.h"
#include "sha256.h"

#ifndef HASH_BUFFER_SIZE
#define HASH_BUFFER_SIZE 4096
#endif

static void get_module_path(char *path, const char* modPath, const char *name)
{
    // Check if full path supplied?
    if ((tolower(name[0]) != 'a') || (name[1] != '/'))
    {
        strcpy(path, modPath);
        strcat(path, "/");
    }
    else
        path[0] = 0;
    // Add supplied name to path
    strcat(path, name);
}

int get_module_info_and_hash(const char* modPath, const char *name, ModuleInfo *mi, char *modName, int modNameLen, unsigned char* sha256)
{
    memset(mi, 0, sizeof(ModuleInfo));
    if (modName)
        modName[0] = 0;     // Only used if module name stored in file (not a LANG string)

    // Get full path to module file, and hash of path
    char path[60];
    get_module_path(path, modPath, name);

    // open file
    FILE* f;
    if (!(f = fopen(path, "rb")))
        return 0;

    static unsigned char buffer[HASH_BUFFER_SIZE];
    struct sha256_state ctx;
    int len;

    sha256_init(&ctx);

    // Read module header to get size info
    flat_hdr flat;
    fread(&flat, 1, sizeof(flat_hdr), f);

    sha256_process(&ctx, (unsigned char*)&flat, sizeof(flat_hdr));

    while ((len = fread(buffer, 1, HASH_BUFFER_SIZE, f)) > 0)
        sha256_process(&ctx, buffer, len);

    sha256_done(&ctx, sha256);

    // Check version and magic number - make sure it is a CHDK module file
    if ((flat.rev == FLAT_VERSION) && (flat.magic == FLAT_MAGIC_NUMBER))
    {
        fseek(f, flat._module_info_offset, SEEK_SET);
        fread(mi, 1, sizeof(ModuleInfo), f);

        if ((mi->moduleName >= 0) && modName)
        {
            // Load module name string
            fseek(f, mi->moduleName, SEEK_SET);
            fread(modName, 1, modNameLen - 1, f);
            modName[modNameLen - 1] = 0;
        }
    }

    fclose(f);

    return 1;
}

#define MODULE_TYPE_COUNT 5

static char* module_types[MODULE_TYPE_COUNT] = { 0, "extension", "game", "tool", "script" };

int meta_modules_get(meta_modules_t* modules, const char* path, const char* created, const char* changeset) {
    DIR *d;
    struct dirent *de;
    static ModuleInfo mi;
    static char modName[33];
    static unsigned char sha256[SHA256_BLOCK_SIZE];
    meta_modules_item_t* item;
    int i = 0;
    if (!modules || !path) {
        return 0;
    }
    if (!(d = opendir(path))) {
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
    if (!(d = opendir(path))) {
        free(modules->modules);
        modules->modules = 0;
        modules->count = 0;
        return 0;
    }
    while ((de = readdir(d))) {
        if (de->d_name[0] != 0xE5 && strcmp(de->d_name, ".") && strcmp(de->d_name, "..") && strcmp(de->d_name, "CFG")) {
            item = &modules->modules[i++];
            get_module_info_and_hash(path, de->d_name, &mi, modName, sizeof(modName), sha256);
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
            item->value.hash.name = "sha256";
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
    return 1;
}

void meta_modules_free(meta_modules_t* modules) {
    meta_modules_item_t* item;
    int i;
    if (!modules || modules->modules) {
        return;
    }
    for (i = 0; i < modules->count; i++) {
        item = &modules->modules[i];
        if (item->key) {
            free(item->key);
        }
        if (item->value.title) {
            free(item->value.title);
        }
        if (item->value.hash.items) {
            free(item->value.hash.items[0].filename);
            free(item->value.hash.items);
        }
        free(item);
    }
    free(modules->modules);
}

static void meta_modules_product_write(meta_modules_product_t* product, JSON* json) {
    if (!product) {
        json_write_null(json);
        return;
    }
    json_write_object_start(json);
    json_write_prop_string("name", product->name, json);
    json_write_object_end(json);
}

static void meta_module_write(meta_module_t* module, JSON* json) {
    static char buf[16];
    if (!module) {
        json_write_null(json);
        return;
    }
    json_write_object_start(json);
    json_write_prop_string("type", module->type, json);
    json_write_object_array_sep(json);
    sprintf(buf, "%d", module->typeId);
    json_write_prop_string("typeId", buf, json);
    json_write_object_array_sep(json);
    json_write_prop_string("title", module->title, json);
    json_write_object_array_sep(json);
    sprintf(buf, "%d", module->titleId);
    json_write_prop_string("titleId", buf, json);
    json_write_object_array_sep(json);
    sprintf(buf, "%d", module->imageId);
    json_write_prop_string("imageId", buf, json);
    json_write_object_array_sep(json);
    json_write_prop_string("created", module->created, json);
    json_write_object_array_sep(json);
    json_write_prop_string("changeset", module->changeset, json);
    json_write_object_array_sep(json);
    json_write_string("hash", json);
    json_write_prop_sep(json);
    meta_hash_write(&module->hash, json);
    json_write_object_end(json);
}

static void meta_modules_modules_write(meta_modules_item_t* items, int count, JSON* json) {
    int i;
    if (!items) {
        json_write_null(json);
        return;
    }
    json_write_object_start(json);
    for (i = 0; i < count; i++) {
        if (i > 0)
            json_write_object_array_sep(json);
        json_write_string(items[i].key, json);
        json_write_prop_sep(json);
        meta_module_write(&items[i].value, json);
    }
    json_write_object_end(json);
}

void meta_modules_write(meta_modules_t* modules, JSON* json) {
    if (!modules) {
        json_write_null(json);
        return;
    }
    json_write_object_start(json);
    json_write_prop_string("version", modules->version, json);
    json_write_object_array_sep(json);
    json_write_string("category", json);
    json_write_prop_sep(json);
    meta_category_write(&modules->category, json);
    json_write_object_array_sep(json);
    json_write_string("product", json);
    json_write_prop_sep(json);
    meta_modules_product_write(&modules->product, json);
    json_write_object_array_sep(json);
    json_write_string("modules", json);
    json_write_prop_sep(json);
    meta_modules_modules_write(modules->modules, modules->count, json);
    json_write_object_end(json);
}
