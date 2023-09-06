ASM=nasm
CC=clang

.PHONY: all boot clean kernel run

all: clean kernel

boot:
	nasm -f elf32 src/boot.asm -o build/boot.o

kernel: boot
	clang -target i386-elf -ffreestanding -nostdlib -c -o build/main.o src/main.c
	ld.lld -melf_i386 -T src/linker.ld build/* -o build/kernel

clean:
	rm -rf build/*

run: all
	qemu-system-i386 -kernel build/kernel
