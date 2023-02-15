#!bin/python

import os

lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "libraries"))

print("Moving files...")
headers = []
for root, dirs, files in os.walk("."):
    for file in files:
        if ((file.endswith(".h") or file.endswith(".cpp")) and root != "."):
            headers.append([root, file])
            
build_data = ""
for header in headers:    
    print(header[1])
    header_data = ""
    with open(os.path.join(*header), "r", encoding="utf-8") as f:
        header_data = f.read()
        
    with open(os.path.join(".", header[1]), "w", encoding="utf-8") as f:
        f.write(header_data)
    build_data += header[1] + "\n"
    
with open("build_data.txt", "w", encoding="utf-8") as f:
    f.write(build_data)