all: boot.bin

boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

clean:
	rm -f boot.bin ctos.img

run: all ../../kernel/kernel.bin
	cat boot.bin ../../kernel/kernel.bin > ctos.img
	qemu-system-x86_64 -drive format=raw,file=ctos.img -m 64M
