#include "main.h"
#include "print.h"
#include "register.h"

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

void bootscreen() {
    print_clear();
    print_str("DeCompileOS\0");
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