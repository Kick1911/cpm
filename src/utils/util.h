#ifndef _CPM_UTIL
#define _CPM_UTIL
#include <limits.h>
#include <sys/types.h>

#define _BR(line) line "\n"
#define _TR(line) "\t" _BR(line)

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
int make_file(const char*, const char*, mode_t, char*);
int make_dir(const char*, size_t, mode_t);
char* read_file(const char*);

#endif
