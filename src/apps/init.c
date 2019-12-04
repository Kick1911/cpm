#include <cpm.h>
#include <cpm_apps.h>
#include <apps/init.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>
#include <util/util.h>

struct stat st = {0};

int make_file(char* name, int type, char* data){
    FILE* fp;
    char buffer[PATH_MAX*2] = {0};
    strcat(buffer, "./");
    strcat(buffer, name);
    printf("Creating %s\n", buffer);
    switch(type){
        case TREE_NODE_DIR:
            if (stat(buffer, &st) == -1)
                if(mkdir(buffer, 0700)){
                    fprintf(stderr, "Error creating directory: %s\n", name);
                    goto error;
                }
        break;
        case TREE_NODE_FILE:
            fp = fopen(buffer, "w");
            if(!fp) {
                fprintf(stderr, "Error creating file: %s\n", name);
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

#define WITH(expression, as, code) \
    { \
        void* as = expression; \
        code; \
        free(as); \
    }

#define _BR(line) line "\n"
#define PROJECT_MK \
    _BR("")

#define APP_MAKEFILE \
    _BR("include project.mk") \
    _BR("")

CPM_APP_FUNCTION(init){
    /* Define Directory tree */
    char path[PATH_MAX*2], *app;
    app = xstrcpy(path, *args);

    make_file(*args, TREE_NODE_DIR, NULL);

    xstrcpy(app, "/project.mk");
    make_file(path, TREE_NODE_FILE, PROJECT_MK);

    xstrcpy(app, "/Makefile");
    make_file(path, TREE_NODE_FILE, NULL);

    xstrcpy(app, "/src");
    WITH(x_str(path, PATH_MAX), src_head,
        char* src_end = strchr(src_head, 0);
        make_file(src_head, TREE_NODE_DIR, NULL);

        xstrcpy(src_end, "/utils");
        make_file(src_head, TREE_NODE_DIR, NULL);

        xstrcpy(src_end, "/dependents");
        make_file(src_head, TREE_NODE_DIR, NULL);

        xstrcpy(src_end, "/components");
        WITH(x_str(src_head, PATH_MAX), comp_head,
            char* comp_end = strchr(comp_head, 0);
            make_file(comp_head, TREE_NODE_DIR, NULL);

            xstrcpy(comp_end, "/Makefile");
            make_file(comp_head, TREE_NODE_FILE, NULL);
        );

        xstrcpy(src_end, "/tests");
        WITH(x_str(src_head, PATH_MAX), tests_head,
            char* tests_end = strchr(tests_head, 0);
            make_file(tests_head, TREE_NODE_DIR, NULL);

            xstrcpy(tests_end, "/Makefile");
            make_file(tests_head, TREE_NODE_FILE, NULL);
        );
    );

    return 0;
}