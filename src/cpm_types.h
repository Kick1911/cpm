#ifndef _CPM_TYPES_H
#define _CPM_TYPES_H

typedef struct {
    char* current_dir;
} cpm_context_t;

typedef struct {
    char* name;
    int (*func)(const cpm_context_t*, const char**);
} cpm_app_t;

#endif
