#include <stddef.h>
#include <stdint.h>

static uint16_t* const VIDEO = (uint16_t*)0xb8000;
static uint16_t cursor = 0;

static void putchar(char c) {
    if (c == '\n') {
        cursor = (cursor / 80 + 1) * 80;
        if (cursor >= 80 * 25) cursor = 0;
        return;
    }
    VIDEO[cursor++] = (uint16_t)c | 0x0700;
    if (cursor >= 80 * 25) cursor = 0;
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
        case 0x1e: return 'a';
        case 0x30: return 'b';
        case 0x2e: return 'c';
        case 0x18: return 'o';
        case 0x16: return 'u';
        case 0x14: return 't';
        case 0x1f: return 's';
        case 0x39: return ' ';
        default: return 0;
    }
}

static void clear_screen() {
    for (int i = 0; i < 80 * 25; ++i)
        VIDEO[i] = 0x0720;
    cursor = 0;
}

static int str_equal(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        a++; b++;
    }
    return *a == *b;
}

void kernel_main() {
    print("Bem-vindo ao CToS!\nDigite 'help' para ajuda.\n> ");
    char buf[16];
    int pos = 0;
    while (1) {
        char c = getkey();
        if (!c) continue;
        if (c == '\n') {
            buf[pos] = '\0';
            if (pos > 0) {
                if (str_equal(buf, "help")) {
                    print("\nComandos disponiveis: help about cls\n> ");
                } else if (str_equal(buf, "about")) {
                    print("\nCToS inspirado no OS de Watch Dogs\n> ");
                } else if (str_equal(buf, "cls")) {
                    clear_screen();
                    print("> ");
                } else {
                    print("\nComando desconhecido\n> ");
                }
            } else {
                print("> ");
            }
            pos = 0;
        } else {
            if (pos < 15) buf[pos++] = c;
            putchar(c);
        }
    }
}
