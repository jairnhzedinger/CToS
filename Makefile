all: kernel/kernel.bin bootloader/bios/boot.bin

kernel/kernel.bin:
	$(MAKE) -C kernel kernel.bin

bootloader/bios/boot.bin:
	$(MAKE) -C bootloader/bios boot.bin

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C bootloader/bios clean
	$(MAKE) -C bootloader/uefi clean

run: all
	cat bootloader/bios/boot.bin kernel/kernel.bin > ctos.img
	qemu-system-x86_64 -drive format=raw,file=ctos.img -m 64M -nographic
