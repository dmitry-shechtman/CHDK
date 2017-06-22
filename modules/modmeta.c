#include "stdlib.h"
#include "gui_mbox.h"
#include "gui.h"
#include "gui_lang.h"
#include "gui_menu.h"
#include "lang.h"
#include "module_load.h"

#include "build_defs.h"
#include "meta_modules.h"

void modmeta_finish(unsigned dummy);

long mkdir_if_not_exist(const char *dirname)
{
    // Check if directory exists and create it if it does not.
    if (stat(dirname, 0) != 0) return mkdir(dirname);
    return 0;   // Success
}

#define MODULES_DIR "A/CHDK/MODULES"

void modmeta_write_file(void) {
    meta_modules_t meta = { "1.0", { "PS" }, { "CHDK" }, 0 };
    static char dateTime[21];
    FILE *f;

    sprintf(dateTime, "%04d-%02d-%02dT%02d:%02d:%02d", BUILD_YEAR, BUILD_MONTH, BUILD_DAY, BUILD_HOUR, BUILD_MIN, BUILD_SEC);

    if (!meta_modules_get(&meta, MODULES_DIR, dateTime, BUILD_SVNREV)) {
        gui_mbox_init((int)"Write module metadata", LANG_ERROR, MBOX_FUNC_RESTORE | MBOX_TEXT_CENTER, modmeta_finish);
        return;
    }

    mkdir_if_not_exist("A/_HDKMETA");
    mkdir_if_not_exist("A/_HDKMETA/PS");

    if (!(f = fopen("A/_HDKMETA/PS/MODULES.JSN", "wb"))) {
        meta_modules_free(&meta);
        gui_mbox_init((int)"Write module metadata", LANG_ERROR, MBOX_FUNC_RESTORE | MBOX_TEXT_CENTER, modmeta_finish);
        return;
    }

    JSON* json = json_open(f);
    meta_modules_write(&meta, json);
    json_close(json);
    
    fclose(f);

    meta_modules_free(&meta);

    gui_mbox_init((int)"Write module metadata", LANG_SUCCESS, MBOX_FUNC_RESTORE | MBOX_TEXT_CENTER, modmeta_finish);
}

int basic_module_init() {
    modmeta_write_file();
    return 1;
}

// =========  MODULE INIT =================
#include "simple_module.c"

void modmeta_finish(unsigned dummy) {
    running = 0;
}

ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(ModuleInfo),
    SIMPLE_MODULE_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0, OPT_ARCHITECTURE,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (uint32_t)"Write module metadata",  // Module name
    MTYPE_TOOL,

    &_librun.base,

    ANY_VERSION,                // CONF version
    ANY_VERSION,                // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
