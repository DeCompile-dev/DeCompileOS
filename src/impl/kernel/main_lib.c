#include "main.h"
#include "print.h"
#include "register.h"
#include "print.h"

void kernel_stable() {
    // ==========================
    // = Setting NULL Registers =
    read_cr3(0x0000);
    read_cr0(0x0000);
    read_cr3(0x0000);

    // ================
    // = For old CPUs =
    __TIME__;
}


void boot_stable() {
    static int i = 0;
    // =======================
    // = Loading CR0 To NULL =
    read_cr0(0x0000);

    // ================
    // = For old CPUs =
    __TIME__;
    i++;
    i++;
    if (i == 2) {
        i--;
        return;
    }
}

void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n--) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    return 0;
}