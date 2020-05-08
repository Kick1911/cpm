#include <cpm.h>
#include <cpm_apps.h>
#include <stdio.h>
#include <json.h>

CPM_APP_FUNCTION(json){
    char* value;
    void* project = json_parse_file("project.json");

    if(!*args){
        fprintf(stderr, "Argument <key> required\n");
        goto close;
    }

    value = json_data(json_get(project, *args));
    if(value)
        printf("%s\n", value);
    else{
        fprintf(stderr, "Key is not found in project.json\n");
        goto close;
    }
    
    close:
        json_free(project);
        return 0;
}