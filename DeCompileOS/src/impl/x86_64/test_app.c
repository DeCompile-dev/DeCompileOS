#include "print.h"
#include "test_app.h"
#include "modules/starting.h"

const char *app_table[] = {
    NULL, // Start of table
    "0x1566",
    "APP_START",
    "TEST_APP", // APP Name here
    NULL // End of table
};

void test_app_start() {
    main_starting_module();
}
