#include <cpm.h>
#include <cpm_apps.h>
#include <cpm_types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include <apps/apps_func.h.partial>

const cpm_app_t cpm_apps[] = {
    #include <apps/apps_struct.h.partial>
    {NULL, NULL}
};

int main(int argc, char** argv){
    char current_dir[PATH_MAX];
    const cpm_app_t* ptr = cpm_apps;
    cpm_context_t context;

    if(!getcwd(current_dir, sizeof(current_dir))){
        fprintf(stderr, "getcwd() failed.\n");
        return 2;
    }

    context.current_dir = current_dir;

    while(ptr->name){
        if(!strcmp(argv[1], ptr->name)){
            ptr->func(&context, argv + 2);
            return 0;
        }
        ptr++;
    }
    fprintf(stderr, "Command '%s' not found\n", argv[1]);
    return 1;
}
