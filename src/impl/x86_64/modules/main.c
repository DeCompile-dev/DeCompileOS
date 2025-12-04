#include "modules/main.h"
#include "print.h"
#include "driver_support.h"
#include "string.h"
#include "game_engine.h"


void main_module_start() {
    print_str("Main Module :: Core started\n");
    main_module_cmd("start_main");
}

void main_module_cmd(const char *cmd) {

    if (kstrcmp(cmd, "start_main") == 0) {
        print_str("Main Module :: CMD interface started\n");
        return;
    }

    if (kstrcmp(cmd, "engine_test") == 0) {
        print_str("|Running a game engine|\n");
        on_game_engine = 1;
        return;
    }

    if (kstrcmp(cmd, "main_debug") == 0) {
        print_str("Main Module :: CMD interface debug started\n");
        return;
    }

    print_str("Main Module :: CMD Unknown Prefix\n");
}

#include "game_engine.h"
#include "print.h"

int on_game_engine = 0;

void print_box() {
    print_str("\n**********\n*        *\n*        *\n*        *\n**********\n");
}

void print_line() {
    print_str("***********\n");
}

//void print_nothing() {
//    // TODO: PRINTG A NOTHING
//}

void game_2d() {
    print_box();
    print_line();
}
