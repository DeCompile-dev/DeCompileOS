/*
If Driver or Module is "Build In" That is Made by DeCompileOS
If you making own Driver or Module don't add a "Build In"

DeCopmile - Team
*/

#include "driver_support.h"
#include "main.h"
#include "modules/starting.h"

const char *driver[] = {
    "keyboard",
    "kernel",
    "idt", // Build In
    "proper_memory" // Build In
};

const char *modules[] = {
    "kernel", // Build In
    "starting",
    "main" // Build In
};

const char *table[] = {
    "entry_point_starting_module"
};

void load_module(const char *module_name) {
    // Loading module
    if (module_name == "starting") {
        main_starting_module();
    }
    // Kernel module isn't loaded here as it's part of the core kernel
    // Add more modules as needed
}

const int ENTRY_POINT_STARTING_MODULE = 0x100000;
const int DRIVER_COUNT = (sizeof(driver) / sizeof(driver[0]));
const int MODULE_COUNT = (sizeof(modules) / sizeof(modules[0]));
const int MODULE_TABLE = (sizeof(table) / sizeof(modules[0]));