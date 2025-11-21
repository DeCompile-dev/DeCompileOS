#include "modules/main.h"
#include "print.h"
#include "driver_support.h"
#include "string.h"

void main_module_start() {
    print_str("Main Module :: Core started\n");
    main_module_cmd("start_main");
}

void main_module_cmd(const char *cmd) {

    if (kstrcmp(cmd, "start_main") == 0) {
        print_str("Main Module :: CMD interface started\n");
        return;
    }

    if (kstrcmp(cmd, "main_debug") == 0) {
        print_str("Main Module :: CMD interface debug started\n");
        return;
    }

    print_str("Main Module :: CMD Unknown Prefix\n");
}