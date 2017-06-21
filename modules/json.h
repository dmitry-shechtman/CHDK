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

#ifndef JSON_H
#define JSON_H

typedef struct
{
    FILE* file;
    char* buffer;
    int index;
}
JSON;

JSON* json_open(FILE* f);
void json_flush(JSON* json);
void json_close(JSON* json);
void json_write_null(JSON* json);
void json_write_string(const char* str, JSON* json);
void json_write_prop_string(const char* name, const char* value, JSON* json);
void json_write_object_start(JSON* json);
void json_write_object_end(JSON* json);
void json_write_array_start(JSON* json);
void json_write_array_end(JSON* json);
void json_write_prop_sep(JSON* json);
void json_write_object_array_sep(JSON* json);

#endif /* JSON_H */