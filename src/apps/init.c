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
    #define _SRC "/src"
    #define _COMP "/compoenents"
    #define _DEP "/dependents"
    #define _TESTS "/tests"
    #define _UTILS "/utils"
    #define CONFIG_MK \
        _BR("SRC_PATH = ${ROOT}" _SRC) \
        _BR("COMP_PATH = ${SRC_PATH}" _COMP) \
        _BR("DEP_PATH = ${SRC_PATH}" _DEP) \
        _BR("UTILS_PATH = ${SRC_PATH}" _UTILS) \
        _BR("TESTS_PATH = ${ROOT}" _TESTS) \
        _BR("COMP_C = ${shell ls ${COMP_PATH}/*.c}") \
        _BR("UTILS_C = ${shell ls ${UTILS_PATH}/*.c}") \
        _BR("COMP_O = ${COMP_C:%.c=%.o}") \
        _BR("UTILS_O = ${UTILS_C:%.c=%.o}") \
        _BR("") \
        _BR("CFLAGS += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${SRC_PATH}") \
        _BR("")

    #define PROJECT_MK \
        _BR("APP_NAME = $0") \
        _BR("")

    #define APP_MAKEFILE \
        _BR("ROOT = .") \
        _BR("include project.mk") \
        _BR(_BR("include config.mk")) \
        _BR(_BR("all: ${APP_NAME}")) \
        _BR("${APP_NAME}: ${SRC_PATH}/${APP_NAME}.c ${COMP_O} ${UTILS_O}") \
        _TR("${CC} $^ -o $@ ${CFLAGS}") \
        _BR("%.o: %.c") \
        _TR("${CC} -c $< -o $@ ${CFLAGS}") \
        _BR("")
    #define APP_C \
        _BR("#include <stdio.h>") \
        _BR("") \
        _BR("int main(int argc, char** argv){") \
        _TR("printf(\"Hello World\");") \
        _TR("return 0;") \
        _BR(_BR("}"))

    dir_path_t root, src, comp, tests;
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
    make_file(&src, _UTILS, TREE_NODE_DIR, NULL);
    make_file(&src, _DEP, TREE_NODE_DIR, NULL);

    xstrcpy(src.end, _COMP);
    comp.end = xstrcpy(comp.path, src.path);

    make_file(&comp, "", TREE_NODE_DIR, NULL);
    make_file(&comp, "/Makefile", TREE_NODE_FILE, NULL);

    xstrcpy(src.end, _TESTS);
    tests.end = xstrcpy(tests.path, src.path);

    make_file(&tests, "", TREE_NODE_DIR, NULL);
    make_file(&tests, "/Makefile", TREE_NODE_FILE, NULL);

    return 0;
}
