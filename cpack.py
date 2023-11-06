#!/bin/env python3

import os

directory_path = "share/templates"

print("#ifndef _TEMPLATE_TEXT_H")
print("#define _TEMPLATE_TEXT_H")

print("\n")

print("typedef struct map {")
print("    char path[1024];")
print("    char template[1 << 12];")
print("} map_t;")

print("\n")

print("map_t structure[] = {")

for filename in os.listdir(directory_path):
    path = os.path.join(directory_path, filename)
    if not os.path.isfile(path):
        continue

    with open(path, "r") as f:
        text = f.read()
        text = text.replace("\n", "\"\n\"")
        text = text.rstrip('"')
        print("    {\"%s\", \"%s}," % (path, text))

print("    NULL")
print("};")
