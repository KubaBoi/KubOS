# Install

- sudo apt install g++ binutils libc6-dev-i386
- sudo apt install xorriso
- sudo apt install make
- sudo apt install grub-common

VSCode extension - ASM Code Lens

http://www.baldwin.cx/386htm/c17.htm

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

# Notes

## Video memory

- starts at `0xb800` and this address need to be saved in `ES`
- `DI` contains offset of mem address (better increase by 2)
- `AX` contains 2 byte "object"
- `stows` copy from `AX` to memory pointed by `ES:DI`  
- it is splited in 2 byte "object"
    - char
    - attribute
        - 0xF0 - white bc, black text
        - 0x0F - black bc, white text