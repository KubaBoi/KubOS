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

Regions:
    - Reserved = reserved_sectors (1)
    - File allocation tables = fat_count * sectors_per_fat (18)
    - Root directory = (dir_entry_count * 32 + bytes_per_sector - 1) / bytes_per_sector (14)
    - Data

Root directory:
    - File name (11b) - "KERNEL  BIN"
    - Attr
    - Creation time [1/10s]
    - Creation time 
    - Creation date
    - Access date
    - First cluster [high]
    - Modified time 
    - Modified date
    - First cluster [low] - fat12 only needs these first 16bits
    - Size

```
File name   F.cl.(h)    F.cl.(l)    Size
KERNEL  BIN 0           3           7743

lba = data_region_begin + (cluster - 2) * sectors_per_cluster
lba = 1+18+14 + (3 - 2) * 1
lba = 34 (sector number where data begins)
```

File allocation table:
    - lookup table with values of clusters
    - first entry is 3
    - all clusters of file are after then in chain
    - end if file is FF8
    - first cluster is not here (only in root dir)

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