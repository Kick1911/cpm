#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

#include <cpm.h>
#include <cpm_apps.h>
#include <components/components.h>

int run_app(const char* app_name,
            cpm_context_t* context,
            const char** args){
    const cpm_app_t* ptr = cpm_apps;

    while(ptr->name){
        if(!strcmp(app_name, ptr->name)){
            ptr->func(context, args + 2);
            return 0;
        }
        ptr++;
    }
    fprintf(stderr, "Command '%s' not found\n", app_name);
    return 1;
}

int main(int argc, const char** argv){
    char current_dir[PATH_MAX];
    cpm_context_t context;

    if(!getcwd(current_dir, sizeof(current_dir))){
        fprintf(stderr, "getcwd() failed.\n");
        return 2;
    }

    context.current_dir = current_dir;
    return run_app(argv[1], &context, argv);
}
