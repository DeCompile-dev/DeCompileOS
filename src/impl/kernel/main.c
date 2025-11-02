#include "io.h"
#include "print.h"
#include "register.h"
#include "keyboard_driver.h"
#include "memory.h"

#define PS2_DATA_PORT 0x60
#define PS2_CMD_PORT 0x64

void init_keyboard() {
    inb(PS2_DATA_PORT); 
    
    outb(PS2_CMD_PORT, 0xAD); 
    io_wait(); 
    
    outb(PS2_DATA_PORT, 0xF0); 
}

void kernel_main() {
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    
    print_str("DeCompileOS Kernel Initializing...\n");

    print_str("Initializing Page Frame Allocator...\n");
    init_page_frame_allocator(); 
    print_str("Completed.\n");

    print_str("Building Identity Mapping for Kernel...\n");
    for (uint64_t i = 0; i < 0x1000000; i += PAGE_SIZE) { 
        map_page(i, i, PTE_PRESENT | PTE_WRITEABLE);
    }
    print_str("Completed.\n");

    print_str("Enabling Paging...\n");
    enable_paging();
    print_str("Completed.\n");
    
    print_str("CR3 address: \n");
    
    print_str("Hardware Keyboard Controller (PS/2) Initialization...\n");
    init_keyboard();
    print_str("Completed.\n");

    print_str("Running Register Software\n");

    print_str("Software Keyboard Driver Initialization (IRQ 1 Unmasking)...\n");
    driver_keyboard_init();
    print_str("Completed.\n");

    print_str("\n");
    print_str("DeCompileOS Kernel ready! Start typing.\n");
    print_str("\n");
    
    for(;;) __asm__("hlt"); 
}