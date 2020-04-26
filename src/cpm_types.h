#ifndef _CPM_TYPES_H
#include <cpm.h>
#define _CPM_TYPES_H

typedef struct {
    char* name;
    int (*func)(const cpm_context_t*, const char**);
} cpm_app_t;

#endif
