#include <cpm.h>
#include <cpm_apps.h>
#include <stdio.h>

CPM_APP_FUNCTION(component){
    printf("Current Dir: %s\n", context->current_dir);
    return 0;
}