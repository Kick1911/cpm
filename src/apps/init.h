#ifndef _CPM_INIT
#define _CPM_INIT
#include <limits.h>

#define TREE_NODE_DIR 1
#define TREE_NODE_FILE 2
#define _BR(line) line "\n"
#define _TR(line) "\t" _BR(line)

typedef struct dir_path dir_path_t;

struct dir_path {
    char path[PATH_MAX*2];
    char* end;
};

#endif
