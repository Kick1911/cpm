#include <cpm.h>
#include <cpm_apps.h>
#include <apps/init.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

struct stat st = {0};

void handle_tree_node(tree_node_t* n){
    switch(n->type){
        case TREE_NODE_DIR:
            char buffer[255];
            strcat(buffer, "./");
            strcat(buffer, n->name);
            if (stat(buffer, &st) == -1)
                mkdir(buffer, 0700);
        break;
        case TREE_NODE_FILE:
        break;
        default:
        break;
    }
}

void bfs(tree_node_t* root, void (*cb)(tree_node_t*)){
    tree_node_t* stack[256];
    tree_node_t** s_ptr = stack;
    *s_ptr++ = root;
    while( s_ptr - stack > 0 ){
        tree_node_t** child_p;
        tree_node_t* temp = *--s_ptr;
        cb(temp);
        child_p = temp->children;
        while(*child_p)
            *s_ptr++ = *child_p++;
    }
}

CPM_APP_FUNCTION(init){
    /* Define Directory tree */
    tree_node_t root = {"No Name", TREE_NODE_DIR, NULL, NULL};
    tree_node_t* root_children[4];
    tree_node_t* src_children[4];

    tree_node_t src = {"src", TREE_NODE_DIR, NULL, NULL};
    tree_node_t utils = {"utils", TREE_NODE_DIR, NULL, NULL};
    tree_node_t components = {"components", TREE_NODE_DIR, NULL, NULL};
    tree_node_t dependents = {"dependents", TREE_NODE_DIR, NULL, NULL};
    tree_node_t tests = {"tests", TREE_NODE_DIR, NULL, NULL};
    tree_node_t project_makefile = {"project.mk", TREE_NODE_FILE, NULL, NULL};

    root_children[0] = &src;
    root_children[1] = &tests;
    root_children[2] = &project_makefile;
    root_children[3] = NULL;
    src_children[0] = &utils;
    src_children[1] = &components;
    src_children[2] = &dependents;
    src_children[3] = NULL;
    root.name = *args;
    root.children = root_children;
    src.children = src_children;
    bfs(&root, handle_tree_node);
    return 0;
}