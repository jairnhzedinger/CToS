#include <stddef.h>
#include <stdint.h>

static uint16_t* const VIDEO = (uint16_t*)0xb8000;
static uint16_t cursor = 0;

static void putchar(char c) {
    VIDEO[cursor++] = (uint16_t)c | 0x0700;
}

static void print(const char* s) {
    while (*s) putchar(*s++);
}

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

static char getkey() {
    unsigned char sc;
    do {
        sc = inb(0x60);
    } while (sc & 0x80);

    switch(sc) {
        case 0x1c: return '\n';
        case 0x23: return 'h';
        case 0x12: return 'e';
        case 0x26: return 'l';
        case 0x19: return 'p';
        case 0x39: return ' ';
        default: return 0;
    }
}

void kernel_main() {
    print("Bem-vindo ao CToS!\nDigite 'help' para ajuda.\n> ");
    char buf[6];
    int pos = 0;
    while (1) {
        char c = getkey();
        if (!c) continue;
        if (c == '\n') {
            buf[pos] = '\0';
            if (pos > 0 && !__builtin_strcmp(buf, "help")) {
                print("\nCToS kernel inicial. Comandos: help\n> ");
            } else {
                print("\nComando desconhecido\n> ");
            }
            pos = 0;
        } else {
            if (pos < 5) buf[pos++] = c;
            putchar(c);
        }
    }
}
