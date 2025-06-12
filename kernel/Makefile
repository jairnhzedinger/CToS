CFLAGS=-m32 -ffreestanding -O2 -Wall -Wextra

kernel.o: kernel.c
	gcc $(CFLAGS) -c kernel.c -o kernel.o

kernel.bin: kernel.o link.ld
	ld -m elf_i386 -T link.ld kernel.o -o kernel.elf
	objcopy -O binary kernel.elf kernel.bin

clean:
	rm -f kernel.o kernel.elf kernel.bin
