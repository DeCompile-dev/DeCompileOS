#include "io.h"
#include "print.h"
#include "register.h"
#include "keyboard_driver.h"

#define PS2_DATA_PORT 0x60
#define PS2_CMD_PORT  0x64

void init_keyboard() {
    inb(PS2_DATA_PORT); 
    
    outb(PS2_CMD_PORT, 0xAD); 
    io_wait(); 
    
    outb(PS2_DATA_PORT, 0xF0); 
}
void kernel_main() {
    // Pre-run section

    char buffer[32];
    // Stiill in progress... 

    // Pre-run section
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    
    print_str("DeCompileOS Kernel Initializing...\n");
    print_str("Hardware Keyboard Controller (PS/2) Initialization...");
    init_keyboard();
    print_str("Completed.\n");

    print_str("Running Register Softwere\n");
    read_cr3(0x000);
    print_str("CR3 Loaded.\n");

    print_str("Software Keyboard Driver Initialization (IRQ 1 Unmasking)...");
    driver_keyboard_init();
    print_str("Completed.\n");

    print_str("\n");
    print_str("DeCompileOS Kernel ready! Start typing.\n");
    print_str("\n");
}
