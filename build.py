#!bin/python

import os
import shutil

lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "libraries"))

def get_lib_name(file):
    return file.replace(".h", "")

def get_source(file):
    return file.replace(".h", ".cpp")

headers = []
for root, dirs, files in os.walk("."):
    for file in files:
        if (file.endswith(".h") and root != "."):
            headers.append([root, file])

for header in headers:    
    print(header[1])
    header_data = ""
    with open(os.path.join(*header), "r", encoding="utf-8") as f:
        header_data = f.read()
        
    with open(os.path.join(".", header[1]), "w", encoding="utf-8") as f:
        f.write(header_data)
        
    source_path = os.path.join(header[0], "src", get_source(header[1]))
    if (os.path.exists(source_path)):
        print(source_path)
        source_data = ""
        with open(source_path, "r", encoding="utf-8") as f:
            source_data = f.read()
            
        with open(os.path.join(".", get_source(header[1])), "w", encoding="utf-8") as f:
            f.write(source_data)