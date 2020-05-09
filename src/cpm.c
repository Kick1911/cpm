#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

#include <cpm.h>
#include <cpm_apps.h>
#include <components/components.h>

/* Force expansion because -D flag does not expand */
#define XSTR(x) #x
#define STR(x) XSTR(x)

int run_app(const char* app_name,
            cpm_context_t* context,
            const char** args){
    const cpm_app_t* ptr = cpm_apps;

    while(ptr->name){
        if(!strcmp(app_name, ptr->name))
            return ptr->func(context, args + 2);
        ptr++;
    }
    fprintf(stderr, "Command '%s' not found\n", app_name);
    return 1;
}

int main(int argc, const char** argv){
    #ifdef INSTALL_PATH
    char default_share_dir[] = STR(INSTALL_PATH) "/share/cpm";
    #else
    char default_share_dir[] = "/usr/share/cpm";
    #endif

    char current_dir[PATH_MAX], cpm_share_dir[PATH_MAX];
    char* share_dir = default_share_dir;
    cpm_context_t context;

    if(argc < 2){
        fprintf(stderr, "No app given\n");
        return 1;
    }
    if(!getcwd(current_dir, sizeof(current_dir))){
        fprintf(stderr, "getcwd() failed.\n");
        return 2;
    }

    if(getenv("CPM_SHARE_DIR"))
        share_dir = getenv("CPM_SHARE_DIR");
    strcpy(cpm_share_dir, share_dir);
    CPM_SHARE_DIR = cpm_share_dir;

    context.current_dir = current_dir;
    return run_app(argv[1], &context, argv);
}
