#include "keyboard_driver.h"
#include "print.h"
#include "io.h"

// ===========================================
// SCANCODE MAP
// ===========================================
static const char us_scancode_map[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0F
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // 0x10 - 0x1D
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,      // 0x1E - 0x2B (0x1D is Enter, 0x2A is Left Shift, 0x2B is \)
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ',   // 0x2C - 0x39
};

// ===========================================
// PS/2 Controller Helper Functions
// ===========================================

static void keyboard_flush_buffer() {
    inb(PS2_DATA_PORT); 
}

static void send_eoi() {
    outb(PIC1_COMMAND_PORT, 0x20); 
}

// ===========================================
// KEYBOARD DRIVER INITIALIZATION
// ===========================================

void driver_keyboard_init() {
    uint8_t mask = inb(PIC1_DATA_PORT); 
    outb(PIC1_DATA_PORT, mask & ~0x02); 
}

// ===========================================
// INTERRUPT HANDLER
// ===========================================

void keyboard_interrupt_handler() {
    uint8_t scancode = inb(PS2_DATA_PORT); 
    
    if (scancode & 0x80) {
    } else {
        if (scancode < sizeof(us_scancode_map) / sizeof(us_scancode_map[0])) {
            char ascii_char = us_scancode_map[scancode];
            
            if (ascii_char != 0) {
                char str[2] = {ascii_char, '\0'};
                print_str(str);
            }
        }
    }
    
    send_eoi();
}