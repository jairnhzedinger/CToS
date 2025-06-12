#include <stddef.h>
#include <stdint.h>

static uint16_t* const VIDEO = (uint16_t*)0xb8000;
static uint16_t cursor = 0;
static uint8_t text_color = 0x07;

static void putchar(char c) {
    if (c == '\n') {
        cursor = (cursor / 80 + 1) * 80;
        if (cursor >= 80 * 25) cursor = 0;
        return;
    }
    VIDEO[cursor++] = (uint16_t)c | ((uint16_t)text_color << 8);
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

static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" :: "a"(val), "dN"(port));
}

static void delay(void) {
    for (volatile int i = 0; i < 100000; ++i);
}

static void beep(void) {
    unsigned char tmp = inb(0x61);
    outb(0x61, tmp | 3);
    delay();
    outb(0x61, tmp & ~3);
}

static void reboot(void) {
    unsigned char status;
    do {
        status = inb(0x64);
    } while (status & 0x02);
    outb(0x64, 0xfe);
}

static uint8_t read_cmos(uint8_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}

static void get_time(uint8_t* h, uint8_t* m, uint8_t* s) {
    *h = read_cmos(0x04);
    *m = read_cmos(0x02);
    *s = read_cmos(0x00);
}

static unsigned int rand_state = 123456789;

static unsigned int rand(void) {
    rand_state = rand_state * 1103515245 + 12345;
    return rand_state;
}

static void set_color(uint8_t color) {
    text_color = color & 0x0f;
}

static void print_dec(unsigned int v) {
    char buf[11];
    int i = 10;
    buf[i--] = '\0';
    if (v == 0) {
        buf[i] = '0';
        print(&buf[i]);
        return;
    }
    while (v && i >= 0) {
        buf[i--] = '0' + (v % 10);
        v /= 10;
    }
    print(&buf[i + 1]);
}

static unsigned char read_scancode() {
    while ((inb(0x64) & 1) == 0);
    return inb(0x60);
}

static char getkey() {
    unsigned char sc;
    do {
        sc = read_scancode();
    } while (sc & 0x80);

    switch (sc) {
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

static void clear_screen(void) {
    for (int i = 0; i < 80 * 25; ++i)
        VIDEO[i] = (uint16_t)' ' | ((uint16_t)text_color << 8);
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
    char buf[32];
    int pos = 0;
    while (1) {
        char c = getkey();
        if (!c) continue;
        if (c == '\n') {
            buf[pos] = '\0';
            if (pos > 0) {
                if (str_equal(buf, "help")) {
                    print("\nComandos disponiveis: help about cls ver beep reboot time rand color\n> ");
                } else if (str_equal(buf, "about")) {
                    print("\nCToS inspirado no OS de Watch Dogs\n> ");
                } else if (str_equal(buf, "cls")) {
                    clear_screen();
                    print("> ");
                } else if (str_equal(buf, "ver")) {
                    print("\nCToS versao 0.1\n> ");
                } else if (str_equal(buf, "beep")) {
                    beep();
                    print("\n> ");
                } else if (str_equal(buf, "reboot")) {
                    print("\nReiniciando...\n");
                    reboot();
                } else if (str_equal(buf, "time")) {
                    uint8_t h, m, s; get_time(&h, &m, &s);
                    print("\n");
                    print_dec(h); putchar(':');
                    if (m < 10) putchar('0');
                    print_dec(m); putchar(':');
                    if (s < 10) putchar('0');
                    print_dec(s); print("\n> ");
                } else if (str_equal(buf, "rand")) {
                    unsigned int v = rand();
                    print("\n");
                    print_dec(v); print("\n> ");
                } else if (pos > 6 && buf[0]=='c' && buf[1]=='o' && buf[2]=='l' && buf[3]=='o' && buf[4]=='r' && buf[5]==' ') {
                    set_color(buf[6]-'0');
                    print("\n> ");
                } else {
                    print("\nComando desconhecido\n> ");
                }
            } else {
                print("> ");
            }
            pos = 0;
        } else {
            if (pos < 31) buf[pos++] = c;
            putchar(c);
        }
    }
}
