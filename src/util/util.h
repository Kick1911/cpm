#ifndef _CPM_UTIL
#define _CPM_UTIL

#define WITH(expression, as, code) \
    { \
        void* as = expression; \
        code; \
        free(as); \
    }

int number_of_digits(int);
char* xstrcpy(char* dest, const char* src);
char* x_str(const char*, unsigned long);

#endif