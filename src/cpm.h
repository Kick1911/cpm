#ifndef _CPM_H
#define _CPM_H

#include <cpm_types.h>

extern char* CPM_SHARE_DIR;

int run_app(const char*, cpm_context_t*, const char**);

#endif
