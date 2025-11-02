#include "register.h"
#include "print.h"

void load_cr3(unsigned long cr3) {
    __asm__ volatile (
        "mov %0, %%cr3"
        :
        : "r" (cr3)
        : "memory"
    );
    print_str("CR3 register loaded with value: ");
    print_str(cr3);
    print_str("\n");
}

void read_cr3(unsigned long* cr3) {
    __asm__ volatile (
        "mov %%cr3, %0"
        : "=r" (*cr3)
        :
        : "memory"
    );
    print_str("CR3 register read with value: ");
    print_str(*cr3);
    print_str("\n");
}