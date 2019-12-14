#ifndef _CPM_UTIL
#define _CPM_UTIL

#define WITH(expression, as, code) \
    { \
        void* as = expression; \
        if(!as){ fprintf(stderr, "Expression: %s resulted in NULL, %d, %s\n", \
                         #expression, __LINE__, __FILE__); } \
        {code} \
        free(as); \
    }

int number_of_digits(int);
char* xstrcpy(char* dest, const char* src);
char* xstrncpy(char* dest, const char* src, long int);
char* x_str(const char*, unsigned long);

#endif
