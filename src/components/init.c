#include <cpm.h>
#include <cpm_apps.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <utils/util.h>
#include <utils/render.h>
#include <components/init.h>

#define FILE_PERMISSIONS 0644
#define DIR_PERMISSIONS 0700

int fill_project(json_t* json, char* p, const char** args, size_t arg_len, const char** ex){
    char* key = NULL, path[PATH_MAX];
    void* value = NULL, *jloop = NULL;
    size_t path_len = strlen(p);

    xstrcpy(path, p);
    jloop = json_iter(json);
    while( !json_next(jloop, &key, &value) ){
        sprintf(path + path_len, "/%s", key);
        switch(json_type(value)){
            case JSON_OBJECT:
                WITH(render(path, args, arg_len), filepath,
                    make_dir(filepath, DIR_PERMISSIONS);
                );
                fill_project(json_data(value), path, args, arg_len, ex);
            break;
            case JSON_STRING:{
                const char** exclude_ex_i = ex;
                char* extension = strrchr(key, '.');
                if(extension && extension[1])
                    while(exclude_ex_i && *exclude_ex_i)
                        if(!strcmp(extension + 1, *exclude_ex_i++))
                            goto end_json_string;
                WITH(render(path, args, arg_len), filepath,
                    char* file;
                    char* text;
                    char template_path[PATH_MAX];

                    file = json_data(value);

                    sprintf(template_path, "%s/templates/%s", CPM_SHARE_DIR, file);
                    text = read_file(template_path);
                    WITH(render(text, args, arg_len), rendered_text,
                        make_file(filepath, FILE_PERMISSIONS, rendered_text);
                    );
                    free(text);
                );
                end_json_string:
                do{}while(0);
            }break;
            default:
            break;
        }
    }
    return 0;
}

static int create_project(json_t* json, const char* root, const char** args, size_t arg_len){
    char path[PATH_MAX];

    xstrcpy(path, root);
    /* Create project root */
    WITH(render(path, args, arg_len), filepath,
        make_dir(filepath, DIR_PERMISSIONS);
    );
    fill_project(json, path, args, arg_len, NULL);
    return 0;
}

CPM_APP_FUNCTION(init){
    void* json;
    char path_structure[PATH_MAX];

    sprintf(path_structure, "%s/structure.json", CPM_SHARE_DIR);
    json = json_parse_file(path_structure);
    create_project(json, *args, args, 1);
    json_free(json);
    return 0;
}
