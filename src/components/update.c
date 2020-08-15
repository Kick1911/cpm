#include <cpm.h>
#include <cpm_apps.h>
#include <components/init.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>

CPM_APP_FUNCTION(update){
    void* structure = NULL;
    char path_structure[PATH_MAX];
    const char* argv[1];
    const char* exclude[] = {".c", ".h", ".json", "project.mk", NULL};

    sprintf(path_structure, "%s/structure.json", CPM_SHARE_DIR);
    structure = json_parse_file(path_structure);
    if(!structure){
        fprintf(stderr, "File '%s' not found\n", path_structure);
        goto error;
    }

    fill_project(structure, ".", argv, 1, exclude);

    json_free(structure);
    return 0;
    error:
    json_free(structure);
    return 1;
}
