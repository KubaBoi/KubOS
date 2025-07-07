# Install

## x86 CPU registers

https://commons.wikimedia.org/wiki/File:Table_of_x86_Registers_svg.svg

## Interupts

https://en.wikipedia.org/wiki/BIOS_interrupt_call#Interrupt_table

## FAT FS

https://wiki.osdev.org/FAT

Create test floppy for checking the headers:

```bash
dd if=/dev/zero of=test.img bs=512 count=2880
mkfs.fat -F 12 -n "NBOS" test.img
mcopy -i test.img build/kernel.bin "::kernel.bin"
hexedit test.img

# check the floppy
mdir -i build/main_floppy.img
```

## LBA to CHS conversion

(Logical Block Addressing)
(Cylinder-Head-Sector)

- sectors per track/cylinder (on single side)
- heads per cylinder (or just heads)

```
sector = (LBA % sectors per track) + 1
head = (LBA / sectors per track) % heads
cylinder = (LBA / sectors per track) / heads
```