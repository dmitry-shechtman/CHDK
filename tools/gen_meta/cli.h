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

#ifndef CLI_H
#define CLI_H

int cli_flag_bool(const char* name, int argc, char const* argv[], int* i);
int cli_flag_int(const char* name, int argc, char const* argv[], int* i, int* value);
int cli_flag_str(const char* name, int argc, char const* argv[], int* i, const char** value);

#endif /* CLI_H */
