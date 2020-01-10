#include <cpm.h>
#include <cpm_apps.h>
#include <stdio.h>
#include <malloc.h>
#include <components/c_project.h>
#include <utils/util.h>
#include <utils/render.h>
#include <ctype.h>

CPM_APP_FUNCTION(component){
    dir_path_t src, comp;

    src.end = xstrcpy(src.path, _SRC);

    xstrcpy(src.end, "/" _COMP);
    comp.end = xstrcpy(comp.path, src.path);

    WITH(render("/$0.c", (const char**)args, 1), comp_c_filename,
        WITH(render(COMP_C, (const char**)args, 1), comp_c,
            make_file(&comp, comp_c_filename, FILE_PERMISSIONS, comp_c);
        );
    );

    WITH(render("/$0.h", (const char**)args, 1), comp_h_filename,
        char comp_name_upper[NAME_MAX];
        const char* header_args[1];
        char* ptr = comp_name_upper;

        xstrcpy(comp_name_upper, *args);
        *ptr = toupper(*ptr);
        while(*ptr++ && (*ptr = toupper(*ptr)));

        *header_args = comp_name_upper;
        WITH(render(COMP_H, header_args, 1), comp_h,
            make_file(&comp, comp_h_filename, FILE_PERMISSIONS, comp_h);
        );
    );
    return 0;
}
