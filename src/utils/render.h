#ifndef _CPM_RENDER_H
#define _CPM_RENDER_H

#include <stddef.h>

char* render(const char* template, const char** args, int);
long render_length(const char* template, const char** args, int);

#endif
