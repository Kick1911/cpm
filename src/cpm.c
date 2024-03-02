#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include <cpm.h>
#include <cpm_apps.h>
#include <components/components.h>
#include <utils/logger.h>


int
run_app(const char* app_name,
        cpm_context_t* context,
        const char** args,
        int args_len) {
    const cpm_app_t* ptr = cpm_apps;

    while(ptr->name){
        if(!strcmp(app_name, ptr->name))
            return ptr->func(context, args + 2, args_len - 2);
        ptr++;
    }
    fprintf(stderr, "Option '%s' not found\n", app_name);
    return 1;
}

int
main(int argc, const char** argv) {
    char current_dir[PATH_MAX];
    cpm_context_t context;

    if(argc < 2){
        fprintf(stderr, "No options\nTry `cpm init <app_name>`\n");
        return 1;
    }
    if(!getcwd(current_dir, sizeof(current_dir))){
        LOG_ERROR("getcwd() failed.\n");
        return 2;
    }

    context.current_dir = current_dir;
    return run_app(argv[1], &context, argv, argc);
}
