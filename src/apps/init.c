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
#include <util/render.h>
#include <templates/c_project.h>

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

CPM_APP_FUNCTION(init){
    /* Define Directory tree */

    dir_path_t root, src, comp, utils, tests;
    root.end = xstrcpy(root.path, *args);

    make_file(&root, "", TREE_NODE_DIR, NULL);
    WITH(render(PROJECT_MK, (const char**)args, 1), project_mk,
        make_file(&root, "/project.mk", TREE_NODE_FILE, project_mk);
    );
    make_file(&root, "/config.mk", TREE_NODE_FILE, CONFIG_MK);
    make_file(&root, "/Makefile", TREE_NODE_FILE, APP_MAKEFILE);

    xstrcpy(root.end, _SRC);
    src.end = xstrcpy(src.path, root.path);

    make_file(&src, "", TREE_NODE_DIR, NULL);
    WITH(render("/$0.c", (const char**)args, 1), app_c,
        make_file(&src, app_c, TREE_NODE_FILE, APP_C);
    );
    make_file(&src, _DEP, TREE_NODE_DIR, NULL);

    xstrcpy(src.end, _UTILS);
    utils.end = xstrcpy(utils.path, src.path);
    make_file(&utils, "", TREE_NODE_DIR, NULL);
    make_file(&utils, "/utils.c", TREE_NODE_FILE, UTILS_UTILS_C);
    make_file(&utils, "/utils.h", TREE_NODE_FILE, UTILS_UTILS_H);

    xstrcpy(src.end, _COMP);
    comp.end = xstrcpy(comp.path, src.path);

    make_file(&comp, "", TREE_NODE_DIR, NULL);

    xstrcpy(root.end, _TESTS);
    tests.end = xstrcpy(tests.path, root.path);

    make_file(&tests, "", TREE_NODE_DIR, NULL);
    make_file(&tests, "/Makefile", TREE_NODE_FILE, TESTS_MAKEFILE);
    make_file(&tests, "/test_utils.c", TREE_NODE_FILE, TEST_UTILS_C);

    return 0;
}
