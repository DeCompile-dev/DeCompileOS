#include "io.h"
#include "print.h"
#include "register.h"
#include "keyboard_driver.h"
#include "memory.h"
#include "main.h"

#define PS2_DATA_PORT 0x60
#define PS2_CMD_PORT 0x64

void init_keyboard() {
    inb(PS2_DATA_PORT); 
    
    outb(PS2_CMD_PORT, 0xAD); 
    io_wait(); 
    
    outb(PS2_DATA_PORT, 0xF0); 
}

void kernel_main() {
    boot_stable();
    kernel_stable();
    init_page_frame_allocator(); 
    for (uint64_t i = 0; i < 0x1000000; i += PAGE_SIZE) { 
        map_page(i, i, PTE_PRESENT | PTE_WRITEABLE);
    }
    enable_paging();
    init_keyboard();
    driver_keyboard_init();
    keyboard_interrupt_handler();
    bootscreen();   
}