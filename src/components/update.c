#include <cpm.h>
#include <cpm_apps.h>
#include <components/init.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>

CPM_APP_FUNCTION(update){
    void* structure, *project;
    char path_structure[PATH_MAX];
    const char* argv[1];

    sprintf(path_structure, "%s/structure.json", getenv("CPM_SHARE_DIR"));
    structure = json_parse_file(path_structure);
    project = json_parse_file("project.json");

    *argv = json_data(json_get(project, "name"));
    if(!*argv){
        fprintf(stderr, "`name` not found in project.json\n");
        goto close;
    }
    fill_project(structure, ".", argv, 1);

    close:
        json_free(structure);
        json_free(project);
        return 0;
}
