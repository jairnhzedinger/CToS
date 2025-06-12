[BITS 16]
ORG 0x7c00

start:
    mov [BOOT_DRIVE], dl       ; Save boot drive

    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    ; Print loading message
    mov si, msg
.print:
    lodsb
    or al, al
    jz .load
    mov ah, 0x0e
    mov bx, 0x0007
    int 0x10
    jmp .print

.load:
    ; Load kernel (16 sectors) to 0x100000
    mov ax, 0x1000        ; segment 0x1000 -> 1MB
    mov es, ax
    xor bx, bx            ; offset 0
    mov ah, 0x02          ; BIOS read sectors
    mov al, 16            ; number of sectors
    mov ch, 0
    mov cl, 2            ; start at LBA 1 (sector 2 in CHS)
    mov dh, 0
    mov dl, [BOOT_DRIVE]
    int 0x13
    jc disk_error

    ; Enable A20 (quick method)
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Set up GDT
    lgdt [gdt_descriptor]

    ; Enter protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEL:protected_start

disk_error:
    hlt
    jmp disk_error

msg db 'Loading CToS...',0
BOOT_DRIVE db 0

; GDT
ALIGN 4
gdt_start:
    dq 0x0000000000000000
    dq 0x00cf9a000000ffff      ; code segment
    dq 0x00cf92000000ffff      ; data segment
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEL equ 0x08
DATA_SEL equ 0x10

[BITS 32]
protected_start:
    mov ax, DATA_SEL
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    jmp 0x100000

TIMES 510 - ($-$$) db 0
DW 0xaa55
