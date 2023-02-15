#!/bin/python

import os

files = [
    "build_data.txt",
    "debug_custom.json",
    "debug.cfg",
    "esp32.svd"
]

with open("build_data.txt", "r", encoding="utf-8") as f:
    files += f.readlines()
    
print("Removing files...")
for file in files:
    file = file.strip()
    if (not os.path.exists(file)): continue
    os.remove(file)
