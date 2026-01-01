#ifndef MAIN_MODULE_H
#define MAIN_MODULE_H
#include "driver_support.h"

extern const int ENTRY_POINT_STARTING_MODULE;

void main_module_start();
void main_module_cmd(const char *cmd);

#endif // MAIN_MODULE_H