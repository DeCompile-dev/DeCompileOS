#ifndef DRIVER_SUPPORT_H
#define DRIVER_SUPPORT_H

extern const char *driver[];
extern const char *modules[];
extern const char *table[];

extern const int MODULE_TABLE;
extern const int DRIVER_COUNT;
extern const int MODULE_COUNT;

void load_module(const char *module_name);

#endif // DRIVER_SUPPORT_H