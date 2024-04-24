#as -g -o main.o main.S
#as -g -o print.o print.S
#gcc -c main.S -o main.o
nasm "main copy.S" -o main.o -f elf64
ld --oformat binary -o main.img -T link.ld main.o
qemu-system-x86_64 -hda main.img -D logfile #-s -S

#objdump -b binary -mi386 -D main.img

