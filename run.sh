#!/bin/bash

flag_bochs=0    # -b
flag_gdb=0      # -g
flag_run=0      # -r

# Zpracování argumentů
while getopts "bgr" opt; do
  case "$opt" in
    b) flag_bochs=1 ;;
    g) flag_gdb=1 ;;
    r) flag_run=1 ;;
    ?) echo "Unknown: -$OPTARG" >&2; exit 1 ;;
  esac
done

make

PARAMS=()
if [ $flag_run -eq 1 ]; then
    qemu-system-i386 -fda build/main_floppy.img
elif [ $flag_gdb -eq 1 ]; then
    qemu-system-i386 -fda build/main_floppy.img -S -gdb tcp::1234
elif [ $flag_bochs -eq 1 ]; then
    bochs -f bochs_config
fi
