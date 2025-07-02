#!/bin/bash

# sudo apt install qemu-utils qemu-system-x86 qemu-system-gui

flag_build=0    # -b
flag_run=0      # -r

# Zpracování argumentů
while getopts "br" opt; do
  case "$opt" in
    b) flag_build=1 ;;
    r) flag_run=1 ;;
    ?) echo "Unknown: -$OPTARG" >&2; exit 1 ;;
  esac
done

if [ $flag_build -eq 1 ]; then
    sudo docker rmi kubos-builder
    sudo docker build -t kubos-builder .
fi

sudo docker run --rm -v "$PWD":/src kubos-builder

if [ $flag_run -eq 1 ]; then
    qemu-system-i386 -fda build/main_floppy.img
fi