#ifndef _CPM_COMPONENTS_H
#define _CPM_COMPONENTS_H

#include <stddef.h>
#include <cpm_types.h>
#include <cpm_apps.h>

CPM_APP_FUNCTION(init);
CPM_APP_FUNCTION(update);

const cpm_app_t cpm_apps[] = {
    CPM_REGISTER_APP(init),
    CPM_REGISTER_APP(update),
    {NULL, NULL}
};

#endif

