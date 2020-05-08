#ifndef _CPM_COMPONENTS_INIT_H
#define _CPM_COMPONENTS_INIT_H
#include <json.h>

int fill_project(json_t*, char* path, const char** args, size_t arg_len);

#endif