#!/bin/python

import os

files = [
    "debug_custom.json",
    "debug.cfg",
    "esp32.svd"
]

print("Removing files...")
for file in files:
    file = file.strip()
    if (not os.path.exists(file)): continue
    os.remove(file)

for root, dirs, files in os.walk("."):
    for file in files:
        if (file.endswith(".h") or file.endswith(".cpp")):
            os.remove(file)
    break