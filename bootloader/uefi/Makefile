CFLAGS=-fpic -fshort-wchar -mno-red-zone -Wall -I/usr/include/efi -I/usr/include/efi/x86_64 -DEFI_FUNCTION_WRAPPER
LDFLAGS=-nostdlib -znocombreloc -T /usr/lib/x86_64-linux-gnu/gnuefi/elf_x86_64_efi.lds -shared -Bsymbolic -L/usr/lib -lefi -lgnuefi

target: loader.efi

loader.o: loader.c
	gcc $(CFLAGS) -c loader.c -o loader.o

loader.efi: loader.o
	ld $(LDFLAGS) loader.o -o loader.efi
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .reloc -j .eh_frame -j .bss -j .rodata -O binary loader.efi loader.bin

clean:
	rm -f loader.o loader.efi loader.bin
