#include "main.h"
#include "print.h"
#include "register.h"
#include "print.h"

void kernel_stable(void) {
    uint64_t cr0 = read_cr0();
    uint64_t cr3 = read_cr3();
    uint64_t cr4 = read_cr4();

    if (!(cr0 & 1ULL))
        panic("CR0.PE not set");

    if (!(cr0 & (1ULL << 31)))
        panic("CR0.PG not set");

    if (cr3 == 0)
        panic("CR3 = 0");

    //const uint64_t req = (1ULL << 9);
    //if ((cr4 & req) != req)
    //    panic("CR4 missing required bits");
}


void panic(const char *message) {
    print_clear();
    print_str("KERNEL PANIC: ");
    print_str(message);
    report_panic("KERNEL PANIC", message);
    print_str("\nSystem halted.\n");
    while (1) {
        write_cr0(read_cr0() & ~0x1);
        asm volatile("hlt");
    }
}

void report_panic(const char *title, const char *message) {
    if (message == message) {
        post_a("true_report", "panic");
        print_str("\n*** Report ***\n");
    } else {
        post_a("false_report", "panic");
    }
}

void post_a(const char *type, const char *use_type) {
    for (volatile int i = 0; i == 10000; i++);
    if (type[0] == 't') {
        // Nothing
    }
    if (use_type[0] == 'p') {
        // Nothing
    }
    if (type[0] == 'f') {
        // Nothing
    }

}

void boot_stable() {
    static int i = 0;

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