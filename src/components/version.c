#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include <cpm.h>
#include <cpm_apps.h>
#include <components/init.h>
#include <components/version.h>

CPM_APP_FUNCTION(version){
    (void) context;
    (void) args;
    (void) args_len;

    printf("%s\n", version_text);

    return 0;
}
