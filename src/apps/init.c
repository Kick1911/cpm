#include <cpm.h>
#include <cpm_apps.h>
#include <apps/init.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <util/util.h>
#include <util/render.h>
#include <templates/c_project.h>

CPM_APP_FUNCTION(init){
    /* Define Directory tree */
    const char* version[] = {VERSION};
    dir_path_t root, src, comp, utils, tests;
    root.end = xstrcpy(root.path, *args);

    make_dir(&root, DIR_PERMISSIONS);
    WITH(render(PROJECT_MK, (const char**)args, 1), project_mk,
        make_file(&root, "/project.mk", FILE_PERMISSIONS, project_mk);
    );
    make_file(&root, "/config.mk", FILE_PERMISSIONS, CONFIG_MK);
    make_file(&root, "/Makefile", FILE_PERMISSIONS, APP_MAKEFILE_1);
    make_file(&root, "/configure", 0755, APP_CONFIGURE);
    WITH(render(APP_MAKEFILE_2, (const char**)version, 1), app_makefile_2,
        make_file(&root, "/Makefile", FILE_PERMISSIONS, app_makefile_2);
    );

    xstrcpy(root.end, "/" _SRC);
    src.end = xstrcpy(src.path, root.path);

    make_dir(&src, DIR_PERMISSIONS);
    WITH(render("/$0.c", (const char**)args, 1), app_c,
        make_file(&src, app_c, FILE_PERMISSIONS, APP_C);
    );

    xstrcpy(src.end, "/" _UTILS);
    utils.end = xstrcpy(utils.path, src.path);
    make_dir(&utils, DIR_PERMISSIONS);
    make_file(&utils, "/utils.c", FILE_PERMISSIONS, UTILS_UTILS_C);
    make_file(&utils, "/utils.h", FILE_PERMISSIONS, UTILS_UTILS_H);

    xstrcpy(src.end, "/" _COMP);
    comp.end = xstrcpy(comp.path, src.path);

    make_dir(&comp, DIR_PERMISSIONS);

    xstrcpy(root.end, "/" _TESTS);
    tests.end = xstrcpy(tests.path, root.path);

    make_dir(&tests, DIR_PERMISSIONS);
    make_file(&tests, "/Makefile", FILE_PERMISSIONS, TESTS_MAKEFILE);
    make_file(&tests, "/test_utils.c", FILE_PERMISSIONS, TEST_UTILS_C);

    return 0;
}
