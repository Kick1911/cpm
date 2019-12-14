#include <cpm.h>
#ifndef _CPM_TYPES_H
#define _CPM_TYPES_H

typedef struct {
    char* name;
    int (*func)(const cpm_context_t*, char**);
} cpm_app_t;

#endif
