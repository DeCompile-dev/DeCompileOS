#include "keyboard_driver.h"
#include "print.h"
#include "io.h"

// ===========================================
// SCANCODE MAP (US QWERTY - basic unshifted keys only)
// 0xFF means no mapping (e.g., function keys, Control, Alt)
// Array is indexed by the scancode (only "make codes" - key press)
// ===========================================
static const char us_scancode_map[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0F
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // 0x10 - 0x1D
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,      // 0x1E - 0x2B (0x1D is Enter, 0x2A is Left Shift, 0x2B is \)
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ',   // 0x2C - 0x39
    // Simplified mapping for the rest of the scancodes
};

// ===========================================
// PS/2 Controller Helper Functions
// ===========================================

/**
 * @brief Flushes the keyboard data buffer.
 * Reads data from port 0x60 to ensure the buffer is clear.
 */
static void keyboard_flush_buffer() {
    inb(PS2_DATA_PORT); 
}

/**
 * @brief Sends End of Interrupt (EOI) to the PIC.
 * Required after every IRQ handling.
 */
static void send_eoi() {
    // EOI for Master PIC (IRQ 0-7)
    outb(PIC1_COMMAND_PORT, 0x20); 
    // If a Slave PIC is used (IRQ 8-15), EOI must also be sent to 0xA0
}

// ===========================================
// KEYBOARD DRIVER INITIALIZATION
// ===========================================

void driver_keyboard_init() {
    // 1. Enable keyboard interrupts (IRQ 1)
    // Read the current mask of the Master PIC (0x21)
    uint8_t mask = inb(PIC1_DATA_PORT); 
    
    // Unmask IRQ 1 (bit 1) in the Master PIC (0x21)
    // Masking is setting the bit to 1, unmasking is setting it to 0.
    // ~0x02 = 1111 1101b.
    outb(PIC1_DATA_PORT, mask & ~0x02); 
    
    print_str("Keyboard driver initialized. IRQ 1 unmasked.\n");
}

// ===========================================
// INTERRUPT HANDLER (called by the assembly stub)
// ===========================================

void keyboard_interrupt_handler() {
    // 1. Read the scancode from the PS/2 data port (0x60)
    uint8_t scancode = inb(PS2_DATA_PORT); 
    
    // 2. Handle "break" codes (key release)
    // "Break" codes have the 8th bit set (e.g., 0x80 for Q release)
    if (scancode & 0x80) {
        // This is a "break" code (key released).
        // In an advanced driver: unset Shift/Ctrl/Alt flags here.
    } else {
        // This is a "make" code (key pressed)
        if (scancode < sizeof(us_scancode_map) / sizeof(us_scancode_map[0])) {
            char ascii_char = us_scancode_map[scancode];
            
            if (ascii_char != 0) {
                // Convert and print the character
                char str[2] = {ascii_char, '\0'};
                print_str(str);
            }
        }
    }
    
    // 3. Send EOI to the PIC to allow further interrupts
    send_eoi();
}