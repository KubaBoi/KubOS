NAME=boot
nasm $NAME.asm -f bin -o $NAME.bin &&
qemu-system-i386 -hda $NAME.bin
