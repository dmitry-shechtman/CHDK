/*
 * Simple JSON writer
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

#include "json.h"

#define JSON_BUFFER_SIZE 4096

JSON* json_open(FILE* f)
{
    JSON* json;

    if (f == NULL)
        return NULL;
    if ((json = malloc(sizeof(JSON))) == NULL)
        return NULL;
    if ((json->buffer = malloc(JSON_BUFFER_SIZE)) == NULL) {
        free(json);
        return NULL;
    }

    json->file = f;
    json->index = 0;

    return json;
}

void json_flush(JSON* json) {
    if (json == NULL)
        return;

    if (json->index == 0)
        return;

    fwrite(json->buffer, json->index, 1, json->file);
    json->index = 0;
}

void json_close(JSON* json) {
    if (json == NULL)
        return;

    json_flush(json);
    free(json->buffer);
    free(json);
}

static void json_write_char(char c, JSON* json) {
    if (json == NULL)
        return;

    if (json->index == JSON_BUFFER_SIZE - 1) {
        json_flush(json);
    }

    json->buffer[json->index++] = c;
}

static void json_write_literal(const char* str, JSON* json) {
    if (json == NULL)
        return;

    if (json->index + strlen(str) >= JSON_BUFFER_SIZE) {
        json_flush(json);
    }

    json->index += sprintf(&json->buffer[json->index], str);
}

void json_write_null(JSON* json) {
    json_write_literal("null", json);
}

static void json_write_false(JSON* json) {
    json_write_literal("false", json);
}

static void json_write_true(JSON* json) {
    json_write_literal("true", json);
}

void json_write_bool(int value, JSON* json) {
    if (value)
        json_write_true(json);
    else
        json_write_false(json);
}

void json_write_string(const char* str, JSON* json) {
    int i, j;

    if (json == NULL)
        return;

    if (!str) {
        json_write_null(json);
        return;
    }

    j = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] == '"' || str[i] == '\\')
            j++;
        j++;
    }

    if (json->index + j >= JSON_BUFFER_SIZE - 2) {
        json_flush(json);
    }

    json->buffer[json->index++] = '"';
    for (i = 0; str[i]; i++) {
        if (str[i] == '"' || str[i] == '\\')
            json->buffer[json->index++] = '\\';
        json->buffer[json->index++] = str[i];
    }
    json->buffer[json->index++] = '"';
}

void json_write_prop_bool(const char* name, int value, JSON* json) {
    json_write_string(name, json);
    json_write_prop_sep(json);
    json_write_bool(value, json);
}

void json_write_prop_string(const char* name, const char* value, JSON* json) {
    json_write_string(name, json);
    json_write_prop_sep(json);
    json_write_string(value, json);
}

void json_write_object_start(JSON* json) {
    json_write_char('{', json);
}

void json_write_object_end(JSON* json) {
    json_write_char('}', json);
}

void json_write_array_start(JSON* json) {
    json_write_char('[', json);
}

void json_write_array_end(JSON* json) {
    json_write_char(']', json);
}

void json_write_prop_sep(JSON* json) {
    json_write_char(':', json);
}

void json_write_object_array_sep(JSON* json) {
    json_write_char(',', json);
}
