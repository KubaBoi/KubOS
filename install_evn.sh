#!/bin/bash

sudo apt update && apt upgrade -y
sudo apt install -y \
            build-essential wget \
            grub-pc-bin xorriso \
            git tree gdb htop vim \
            make nasm \
            qemu-utils qemu-system-x86 qemu-system-gui \
            dosfstools mtools \
            bochs bochs-sdl bochsbios vgabios


# https://github.com/open-watcom/open-watcom-v2/releases/tag/Current-build
WATCOM="open-watcom-2_0-c-linux-x64"
wget https://github.com/open-watcom/open-watcom-v2/releases/download/Current-build/"$WATCOM"
sudo chmod +x ./"$WATCOM"
sudo ./"$WATCOM"
rm "./$WATCOM"