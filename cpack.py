#!/bin/env python3

import os
import json


C90_STRING_LIMIT = 509


def get_output_path(p):
    parts = os.path.basename(p).split("#")
    return "/".join(parts)


def clean_text(text):
    text = text.replace('\\', '\\\\')
    text = text.replace('"', '\\"')
    text = text.replace("\n", "\\n\"\n\"")
    return text.rstrip('"')


def output_map_entry(f, path, metadata):
    slices = []

    text = f.read(C90_STRING_LIMIT)
    while text:
        slices.append(text)
        text = f.read(C90_STRING_LIMIT)

    first = slices.pop(0)
    is_directory = int(path[-1] == "#")
    output_path = get_output_path(path)
    data = metadata.get(output_path, dict(type="user"))

    print("    {%s, %s, %s, \"%s\", \"%s\"}," % (
        int(data["type"] == "system"),
        0,
        is_directory,
        output_path,
        clean_text(first).rstrip('\n"')
    ))

    for t in slices:
        print("    {%s, %s, %s, \"%s\", \"%s\"}," % (
            int(data["type"] == "system"),
            1,
            is_directory,
            output_path,
            clean_text(t).rstrip('\n"')
        ))


directory_path = "share/templates"

with open("share/metadata.json", "r") as f:
    metadata = json.loads(f.read())

print("#ifndef _TEMPLATE_TEXT_H")
print("#define _TEMPLATE_TEXT_H")

print("\n")

print("typedef struct map {")
print("    int is_system;")
print("    int append;")
print("    int is_directory;")
print("    char path[1024];")
print("    char template[1 << 13];")
print("} map_t;")

print("\n")

print("map_t STRUCTURE[] = {")

for filename in os.listdir(directory_path):
    path = os.path.join(directory_path, filename)
    if not os.path.isfile(path):
        continue

    with open(path, "r") as f:
        output_map_entry(f, path, metadata)

print('    {0, 0, 0, "", ""}')
print("};")
print("#endif")
