#ifndef _CPM_INIT
#define _CPM_INIT

#define TREE_NODE_DIR 1
#define TREE_NODE_FILE 2

typedef struct tree_node tree_node_t;

struct tree_node {
    char* name;
    int type;
    char* data;
    tree_node_t** children;
};

#endif