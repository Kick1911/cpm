#include <cpm.h>
#include <cpm_apps.h>
#include <apps/init.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <util/util.h>

struct stat st = {0};

int make_file(dir_path_t* d, char* name, int type, char* data){
    FILE* fp;
    char buffer[PATH_MAX*2] = {0};

    xstrcpy(d->end, name);
    strcat(buffer, "./");
    strcat(buffer, d->path);
    printf("Creating %s\n", buffer);

    switch(type){
        case TREE_NODE_DIR:
            if (stat(buffer, &st) == -1)
                if(mkdir(buffer, 0700)){
                    fprintf(stderr, "Error creating directory: %s\n", d->path);
                    goto error;
                }
        break;
        case TREE_NODE_FILE:
            fp = fopen(buffer, "w");
            if(!fp) {
                fprintf(stderr, "Error creating file: %s\n", d->path);
                goto close_file_and_error;
            }
            if(data)
                fwrite(data, sizeof(char), strlen(data), fp);
            fclose(fp);
        break;
        default:
            fprintf(stderr, "Error not Directory or File\n");
    }
    return 0;
    close_file_and_error:
        fclose(fp);
    error:
        return 1;
}

#define _BR(line) line "\n"
#define PROJECT_MK \
    _BR("")

#define APP_MAKEFILE \
    _BR("include project.mk") \
    _BR("")

CPM_APP_FUNCTION(init){
    /* Define Directory tree */
    dir_path_t root;
    root.end = xstrcpy(root.path, *args);

    make_file(&root, "", TREE_NODE_DIR, NULL);
    make_file(&root, "/project.mk", TREE_NODE_FILE, PROJECT_MK);
    make_file(&root, "/Makefile", TREE_NODE_FILE, APP_MAKEFILE);

    xstrcpy(root.end, "/src");
    {
        dir_path_t src;
        src.end = xstrcpy(src.path, root.path);

        make_file(&src, "", TREE_NODE_DIR, NULL);
        make_file(&src, "/utils", TREE_NODE_DIR, NULL);
        make_file(&src, "/dependents", TREE_NODE_DIR, NULL);

        xstrcpy(src.end, "/components");
        {
            dir_path_t comp;
            comp.end = xstrcpy(comp.path, src.path);

            make_file(&comp, "", TREE_NODE_DIR, NULL);
            make_file(&comp, "/Makefile", TREE_NODE_FILE, NULL);
        }

        xstrcpy(src.end, "/tests");
        {
            dir_path_t tests;
            tests.end = xstrcpy(tests.path, src.path);

            make_file(&tests, "", TREE_NODE_DIR, NULL);
            make_file(&tests, "/Makefile", TREE_NODE_FILE, NULL);
        }
    }

    return 0;
}