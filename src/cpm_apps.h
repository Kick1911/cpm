#ifndef _CPM_APPS_H
#define _CPM_APPS_H
#define CPM_APP_FUNCTION(name) \
    int cpm_app_run_##name (const cpm_context_t* context, const char** args, int args_len)
#define CPM_REGISTER_APP(name) \
    {#name, cpm_app_run_##name}

#endif
