#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <malloc.h>
#include <assert.h>

#include <cpm.h>
#include <project_map.h>
#include <cpm_apps.h>
#include <components/init.h>
#include <utils/util.h>
#include <utils/render.h>

#define FILE_PERMISSIONS 0644
#define DIR_PERMISSIONS 0700

static int
create_project(const char* root, const char** args, size_t arg_len){
    char path[PATH_MAX];
    map_t* key_value = structure;

    sprintf(path, "%s", root);

    while ( *(key_value->path) ) {
        char* dirc, *ptr;
        char output_path[PATH_MAX*2];
        char* output_text = key_value->template;

        ptr = xstrcpy(output_path, path);
        ptr = xstrcpy(ptr, "/");
        xstrncpy(ptr, key_value->path, PATH_MAX);

        dirc = strdup(output_path);
        dirname(dirc);

        printf("Creating output_path: %s, %s\n", output_path, dirc);

        WITH(render((key_value->is_directory) ? output_path : dirc, args, arg_len), filepath,
            make_dir(filepath, DIR_PERMISSIONS);
        );

        if (!key_value->is_directory) {
            WITH(render(output_path, args, arg_len), filepath,
                WITH(render(output_text, args, arg_len), rendered_text,
                    make_file(filepath, "a", FILE_PERMISSIONS, rendered_text);
                );
            );
        }

        free(dirc);
        key_value += 1;
    }

    return 0;
}

CPM_APP_FUNCTION(init){
    if(args_len < 1){
        fprintf(stderr, "`init` requires 1 parameter, `cpm init <name>`\n");
        return 1;
    }

    create_project(*args, args, args_len);
    return 0;
}
