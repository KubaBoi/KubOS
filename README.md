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

# Part 2

https://stackoverflow.com/questions/22054578/how-to-run-a-program-without-an-operating-system/32483545#32483545

```bash
printf '\364%509s\125\252' > main.img
sudo apt-get install qemu-system-x86
qemu-system-x86_64 -hda main.img
```

```bash
echo hlt > a.S
as -o a.o a.S
objdump -S a.o
```

## Assemble and link asm helloworld

```bash
as -g -o main.o main.S
ld --oformat binary -o main.img -T link.ld main.o
qemu-system-x86_64 -hda main.img
```

`--oformat binary` - output raw binary assembly code, don't wrap it inside an ELF file as is the case for regular userland executables.