#ifndef META_MODULES_H
#define META_MODULES_H

#include "meta.h"

typedef struct {
    char* name;
}
meta_modules_product_t;

typedef struct {
    char* type;
    int typeId;
    char* title;
    int titleId;
    int imageId;
    const char* created;
    const char* changeset;
    meta_hash_t hash;
}
meta_module_t;

typedef struct meta_modules_item_t {
    char* key;
    meta_module_t value;
}
meta_modules_item_t;

typedef struct {
    char* version;
    meta_category_t category;
    meta_modules_product_t product;
    meta_modules_item_t* modules;
    int count;
}
meta_modules_t;

int meta_modules_get(meta_modules_t* modules, const char* path, const char* created, const char* changeset);
void meta_modules_free(meta_modules_t* modules);
void meta_modules_write(meta_modules_t* modules, JSON* json);

#endif // META_MODULES_H
