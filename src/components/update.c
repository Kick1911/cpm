#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>

#include <cpm.h>
#include <cpm_apps.h>
#include <components/init.h>

CPM_APP_FUNCTION(update){
    if( access("project.mk", F_OK) ){
        fprintf(stderr, "Not a cpm project. Change directory to a cpm project.\n");
        return 1;
    }

    if (create_project(".", args, args_len, 1)) {
        fprintf(stderr, "Failed to update project.");
        return 1;
    }

    return 0;
}
