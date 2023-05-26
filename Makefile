# C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
# HEADERS = $(wildcard kernel/*.h drivers/*.h)
# OBJ = ${C_SOURCES:.c=.o}

target:
	gcc -ffreestanding -c -fno-pie -m32 kernel/kernel.c -o build/kernel.o
	
	nasm boot/kernel_entry.asm -f elf -o build/kernel_entry.o

	ld build/kernel_entry.o build/kernel.o -o build/kernel.bin -m elf_i386 -Ttext 0x1000 --oformat binary

	nasm boot/bootsect.asm -f bin -o build/bootsect.bin

	cat build/bootsect.bin build/kernel.bin > build/os-image.bin

	cp build/os-image.bin build/os.img
	truncate -s 1440k build/os.img

	qemu-system-i386 build/os-image.bin
