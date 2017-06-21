/*
 * CHDK menu metadata generator
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

#include "stdlib.h"
#include "gui_mbox.h"
#include "gui.h"
#include "gui_lang.h"
#include "gui_menu.h"
#include "lang.h"
#include "json.h"

#define FILENAME "A/_HDKMETA/PS/MENUS.JSN"

void menumeta_finish(unsigned dummy);

void write_menu(const CMenu* menu, char* buf, JSON* json) {
    int i;

    json_write_array_start(json);

    for (i = 0; menu->menu[i].text; i++) {
        if (menu->menu[i].text == LANG_MENU_USER_MENU || menu->menu[i].type == MENUITEM_UP)
            continue;

        if (i > 0)
            json_write_object_array_sep(json);

        json_write_object_start(json);

        sprintf(buf, "%d", menu->menu[i].text);
        json_write_prop_string("textId", buf, json);

        json_write_object_array_sep(json);

        sprintf(buf, "%d", menu->menu[i].symbol);
        json_write_prop_string("imageId", buf, json);

        json_write_object_array_sep(json);

        json_write_prop_string("text", lang_str(menu->menu[i].text), json);

        if (menu->menu[i].type == MENUITEM_SUBMENU) {
            json_write_object_array_sep(json);
            json_write_string("menu", json);
            json_write_prop_sep(json);
            write_menu((CMenu*)menu->menu[i].value, buf, json);
        }

        json_write_object_end(json);
    }

    json_write_array_end(json);
}

long mkdir_if_not_exist(const char *dirname)
{
    // Check if directory exists and create it if it does not.
    if (stat(dirname, 0) != 0) return mkdir(dirname);
    return 0;   // Success
}

void menumeta_write_file(void) {
    static char buf[128];
    FILE *f;

    mkdir_if_not_exist("A/_HDKMETA");
    mkdir_if_not_exist("A/_HDKMETA/PS");

    if (!(f = fopen(FILENAME, "wb"))) {
        gui_mbox_init((int)"Write menu metadata", LANG_ERROR, MBOX_FUNC_RESTORE | MBOX_TEXT_CENTER, menumeta_finish);
        return;
    }

    JSON* json = json_open(f);
    json_write_object_start(json);
    json_write_prop_string("version", "1.0", json);
    json_write_object_array_sep(json);
    json_write_string("menu", json);
    json_write_prop_sep(json);
    write_menu(&root_menu, buf, json);
    json_write_object_end(json);
    json_close(json);

    fclose(f);

    gui_mbox_init((int)"Write menu metadata", LANG_SUCCESS, MBOX_FUNC_RESTORE | MBOX_TEXT_CENTER, menumeta_finish);
}

int basic_module_init() {
    menumeta_write_file();
    return 1;
}

// =========  MODULE INIT =================
#include "simple_module.c"

void menumeta_finish(unsigned dummy) {
    running = 0;
}

ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(ModuleInfo),
    SIMPLE_MODULE_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0, OPT_ARCHITECTURE,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (uint32_t)"Write menu metadata",  // Module name
    MTYPE_TOOL,

    &_librun.base,

    ANY_VERSION,                // CONF version
    ANY_VERSION,                // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
