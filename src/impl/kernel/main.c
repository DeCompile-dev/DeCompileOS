#include "io.h"
#include "print.h"
#include "register.h"
#include "keyboard_driver.h"
#include "memory.h"
#include "main.h"
#include "modules/main.h"
#include "driver_support.h"
#include "test_app.h"
#include "idt/idt.h"

#define COMMAND_BUFFER_SIZE 256
char command_buffer[COMMAND_BUFFER_SIZE];

int strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int str_starts_with(const char *s1, const char *s2) {
    while (*s2) {
        if (*s1 != *s2) {
            return 0;
        }
        s1++;
        s2++;
    }
    return 1;
}

void execute_command(const char *cmd) {
    if (cmd[0] == '\0') {
        return; 
    }

    if (strcmp(cmd, "help") == 0) {
        print_str("Available commands: help, version, test, echo [text], clear, cmd_debug\n");
    } 
    else if (strcmp(cmd, "version") == 0) {
        print_str("|DeCompileOS veresion: Beta 0.1.4|\n");
        print_str("|Type: normal_type has version: 0.0.1|\n");
        print_str("|Kernel built on: ");
        print_str(__DATE__);
        print_str("|\n");
    }
    else if (strcmp(cmd, "test") == 0) {
        print_str("|Starting test application...|\n");
        test_app_start(); 
    }
    else if (strcmp(cmd, "clear") == 0) {
        print_clear();
    }
    else if (strcmp(cmd, "cmd_debug") == 0) {
        main_module_cmd("main_debug");
    }
    else if (str_starts_with(cmd, "echo")) {
        if (strcmp(cmd, "echo") == 0) {
            print_str("\n");
            return;
        }

        const char *echo_prefix = "echo ";
        int prefix_len = strlen(echo_prefix);

        if (str_starts_with(cmd, echo_prefix)) {
            print_str(cmd + prefix_len);
            print_str("\n");
        } else {
            print_str("|Unknown command: ");
            print_str(cmd);
            print_str("|\n");
        }
    }
    else {
        print_str("|Unknown command: ");
        print_str(cmd);
        print_str("|\n");
    }
}

int read_line(char *buffer, int max_len) {
    int count = 0;
    char c = 0;
    
    print_str("<DeCompileOS (ROOT) :: CMD> ");

    while (count < max_len - 1) {
        if (!get_char_from_keyboard(&c)) {
            asm volatile("hlt");
            continue; 
        }

        if (c == '\b') {
            if (count > 0) {
                count--;
                print_str("\b \b"); 
            }
            continue;
        }

        if (c == '\n') {
            buffer[count] = '\0'; 
            print_str("\n");
            return count;
        }

        if (c >= ' ' && c <= '~') {
            buffer[count++] = c;
            char str[2] = {c, '\0'};
            print_str(str); 
        }
    }

    buffer[count] = '\0';
    return count;
}

void kernel_main() {
    boot_stable();
    kernel_stable();
    
    init_page_frame_allocator(); 
    for (uint64_t i = 0; i < 0x1000000; i += PAGE_SIZE) { 
        map_page(i, i, PTE_PRESENT | PTE_WRITEABLE);
    }
    enable_paging();
    
    idt_init();
    driver_keyboard_init();
    
    print_clear();
    print_str("|DeCompileOS veresion: Beta 0.1.4|\n");
    print_str("|Starting Module: Main|\n");
    main_module_start();
    print_str("|Welcome to OS console. Type 'help' for commands.|\n");
    print_str("|Data: Auto, Mode: Root, Print_Type: normal_type|\n");

    asm volatile("sti");

    while (1) {
        int len = read_line(command_buffer, COMMAND_BUFFER_SIZE);      
        if (len > 0) {
            execute_command(command_buffer);
        }
    }
}