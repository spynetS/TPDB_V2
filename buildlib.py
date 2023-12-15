#!/usr/bin/env python3
import os

src = "./src"
output = "./build/lib/"

# compile all c files to o files
o_files = "";
for (root,dirs,files) in os.walk(src,topdown=True):
    for file in files:
        split = file.split(".")
        if len(split) > 1 and split[1] == "c":
            o_path = f"{output}{file.replace('.c','.o')}"
            os.system(f"gcc -c {os.path.join(root,file)} -o {o_path}")
            o_files += o_path+" "

# ar -rcs librenderay.a renderay_core.o renderay_shapes.o
os.system(f"ar -rcs libtpdb.a {o_files}")
