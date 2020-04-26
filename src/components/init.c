#include <cpm.h>
#include <cpm_apps.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <utils/util.h>
#include <utils/render.h>
#include <json.h>

#define FILE_PERMISSIONS 0644
#define DIR_PERMISSIONS 0700

static char* read_file(const char* path){
    long size = 0;
    char* text;
    FILE* f = fopen(path, "r");

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    text = (char*)malloc(sizeof(char) * (size+1));
    fread(text, sizeof(char), size, f);
    text[size] = 0;
    fclose(f);

    return text;
}

static int read_structure(json_t* json, char* root, const char** args, size_t arg_len){
    char* key = NULL, path[PATH_MAX];
    void* value = NULL, *jloop = NULL;

    root = xstrcpy(path, root);
    jloop = json_iter(json);
    while( !json_next(jloop, &key, &value) ){
        sprintf(root, "/%s", key);
        switch(json_type(value)){
            case JSON_OBJECT:
                WITH(render(path, args, arg_len), filepath,
                    make_dir(filepath, DIR_PERMISSIONS);
                );
                read_structure(json_data(value), path, args, arg_len);
            break;
            case JSON_STRING:
                WITH(render(path, args, arg_len), filepath,
                    char* file;
                    char* text;
                    char template_path[PATH_MAX];

                    file = json_data(value);

                    sprintf(template_path, "%s/templates/%s", getenv("CPM_SHARE_DIR"), file);
                    text = read_file(template_path);
                    WITH(render(text, args, arg_len), rendered_text,
                        make_file(filepath, FILE_PERMISSIONS, rendered_text);
                    );
                    free(text);
                );
            break;
            default:
            break;
        }
    }
    return 0;
}

CPM_APP_FUNCTION(init){
    void* json;
    char dir_structure[PATH_MAX];
    const char* version[] = {"0.0.1"};

    sprintf(dir_structure, "%s/structure.json", getenv("CPM_SHARE_DIR"));
    json = json_parse_file(dir_structure);
    read_structure(json, ".", args, 1);
    json_free(json);
    return 0;
}
