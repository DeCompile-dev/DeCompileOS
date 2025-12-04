#include "keyboard_driver.h"
#include "print.h"
#include "main.h"
#include "io.h"
#include <stdint.h>

#define PS2_DATA_PORT 0x60
#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define KEYBOARD_BUFFER_SIZE 256

volatile char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
volatile unsigned int read_idx = 0;
volatile unsigned int write_idx = 0;
static int shift_pressed = 0;

static const char scan_map_lower[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static const char scan_map_upper[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};

void driver_keyboard_init() {
    uint8_t mask = inb(PIC1_DATA_PORT);
    outb(PIC1_DATA_PORT, mask & ~0x02);
}

int get_char_from_keyboard(char *out_char) {
    if (read_idx == write_idx) {
        return 0;
    }
    *out_char = keyboard_buffer[read_idx];
    read_idx = (read_idx + 1) % KEYBOARD_BUFFER_SIZE;
    return 1;
}

void keyboard_interrupt_handler() {
    uint8_t scancode = inb(PS2_DATA_PORT);

    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
    } else if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
    } else {
        if (!(scancode & 0x80)) {
            if (scancode < sizeof(scan_map_lower)) {
                char ascii_char;
                
                if (shift_pressed) {
                    ascii_char = scan_map_upper[scancode];
                } else {
                    ascii_char = scan_map_lower[scancode];
                }

                if (ascii_char != 0) {
                    unsigned int next_write_idx = (write_idx + 1) % KEYBOARD_BUFFER_SIZE;
                    if (next_write_idx != read_idx) {
                        keyboard_buffer[write_idx] = ascii_char;
                        write_idx = next_write_idx;
                    } else {
                        panic("Keyboard buffer overflow");
                    }
                }
            }
        }
    }
    outb(PIC1_COMMAND_PORT, 0x20);
}