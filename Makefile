# Alvo principal que gera a imagem pronta para uso
all: ctos.img

# Concatena o bootloader e o kernel em uma unica imagem
ctos.img: kernel/kernel.bin bootloader/bios/boot.bin
	cat bootloader/bios/boot.bin kernel/kernel.bin > ctos.img

kernel/kernel.bin:
	$(MAKE) -C kernel kernel.bin

bootloader/bios/boot.bin:
	$(MAKE) -C bootloader/bios boot.bin

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C bootloader/bios clean
	$(MAKE) -C bootloader/uefi clean
	rm -f ctos.img

run: all
	qemu-system-x86_64 -drive format=raw,file=ctos.img -m 64M -nographic
