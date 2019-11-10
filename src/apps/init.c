#include <cpm.h>
#include <cpm_apps.h>
#include <stdio.h>

CPM_APP_FUNCTION(init){
    printf("Current Dir: %s\n", context->current_dir);
    return 0;
}