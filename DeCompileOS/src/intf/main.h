#ifndef MAIN_KERNEL_H
#define MAIN_KERNEL_H

#include <stdint.h>
#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);

void kernel_stable();

void panic(const char *message);

void report_panic(const char *title, const char *message);

void post_a(const char *type, const char *use_type);

void boot_stable();
static int i = 0;

#endif // MAIN_KERNEL_H