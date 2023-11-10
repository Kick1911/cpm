#!/bin/env python3

import os


C90_STRING_LIMIT = 509


def get_output_path(p):
    parts = os.path.basename(p).split("#")
    return "/".join(parts)


def clean_text(text):
    text = text.replace('\\', '\\\\')
    text = text.replace('"', '\\"')
    text = text.replace("\n", "\"\n\"")
    return text.rstrip('"')


def output_map_entry(f, path):
    slices = []

    text = f.read(C90_STRING_LIMIT)
    while text:
        slices.append(text)
        text = f.read(C90_STRING_LIMIT)

    last = slices.pop()

    for t in slices:
        print("    {\"%s\", \"%s\"}," % (get_output_path(path), clean_text(t)))

    print("    {\"%s\", \"%s}," % (get_output_path(path), clean_text(last)))


directory_path = "share/templates"

print("#ifndef _TEMPLATE_TEXT_H")
print("#define _TEMPLATE_TEXT_H")

print("\n")

print("typedef struct map {")
print("    char path[1024];")
print("    char template[1 << 13];")
print("} map_t;")

print("\n")

print("map_t structure[] = {")

for filename in os.listdir(directory_path):
    path = os.path.join(directory_path, filename)
    if not os.path.isfile(path):
        continue

    with open(path, "r") as f:
        output_map_entry(f, path)

print('    {"", ""}')
print("};")
print("#endif")
