#include <cpm.h>
#include <cpm_apps.h>
#include <stdio.h>
#include <string.h>
#include <json.h>
#include <linux/limits.h>

CPM_APP_FUNCTION(json){
    char* value;
    void* project = NULL;

    strcat(context->current_dir, "/project.json");
    project = json_parse_file(context->current_dir);
    if(!*args){
        fprintf(stderr, "Argument <key> required\n");
        goto error;
    }
    if(!project){
        fprintf(stderr, "File project.json not found\n");
        goto error;
    }

    value = json_data(json_get(project, *args));
    printf("%s\n", (value ? value: ""));
    
    json_free(project);
    return 0;
    error:
    json_free(project);
    return 1;
}