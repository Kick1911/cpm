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
    printf("%s\n", (value ? value: ""));
    
    close:
        json_free(project);
        return 0;
}