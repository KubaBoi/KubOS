#!/bin/bash

sudo apt update && apt upgrade -y
sudo apt install -y \
            build-essential \
            grub-pc-bin xorriso \
            git tree gdb htop vim \
            make nasm \
            qemu-utils qemu-system-x86 qemu-system-gui \
            dosfstools mtools \
            bochs bochs-sdl bochsbios vgabios