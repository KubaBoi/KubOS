# Install

- sudo apt install g++ binutils libc6-dev-i386
- sudo apt install xorriso
- sudo apt install make
- sudo apt install grub-common

## build

- ./build.sh 

## troubleshoot

connection refused

- apt-get install grub-pc-bin
- rebuild
- run

## build

https://wiki.osdev.org/Babystep1

`nasm boot.asm -f bin -o boot.bin`

## run

`qemu-system-i386 -hda boot.bin`
