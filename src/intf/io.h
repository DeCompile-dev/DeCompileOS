#ifndef IO_H
#define IO_H

#include <stdint.h>

// --- OUT Functions ---

static inline void outb(uint16_t port, uint8_t data) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(data), "Nd"(port));
}

static inline void outw(uint16_t port, uint16_t data) {
    __asm__ __volatile__ ("outw %0, %1" : : "a"(data), "Nd"(port));
}

static inline void outl(uint16_t port, uint32_t data) {
    __asm__ __volatile__ ("outl %0, %1" : : "a"(data), "Nd"(port));
}

// --- IN Functions ---

static inline uint8_t inb(uint16_t port) {
    uint8_t data;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t data;
    __asm__ __volatile__ ("inw %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

static inline uint32_t inl(uint16_t port) {
    uint32_t data;
    __asm__ __volatile__ ("inl %1, %0" : : "Nd"(port));
    return data;
}

// --- Delay function ---

static inline void io_wait(void) {
    outb(0x80, 0); 
}


#endif // IO_H
