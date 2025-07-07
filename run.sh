#!/bin/bash

flag_debug=0    # -d
flag_run=0      # -r

# Zpracování argumentů
while getopts "dr" opt; do
  case "$opt" in
    d) flag_debug=1 ;;
    r) flag_run=1 ;;
    ?) echo "Unknown: -$OPTARG" >&2; exit 1 ;;
  esac
done

make

PARAMS=()
if [ $flag_run -eq 1 ]; then
    qemu-system-i386 -drive format=raw,file=build/main_floppy.img
elif [ $flag_debug -eq 1 ]; then
    bochs -f bochs_config
fi
