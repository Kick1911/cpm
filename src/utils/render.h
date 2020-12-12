#ifndef _CPM_RENDER_H
#define _CPM_RENDER_H

#include <stddef.h>

char* render(const char* template, const char** args, unsigned long);
size_t render_length(const char* template, const char** args, unsigned long);

#endif
