#ifndef _CPM_UTIL
#define _CPM_UTIL
#include <limits.h>
#define TREE_NODE_DIR 1
#define TREE_NODE_FILE 2

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

typedef struct dir_path dir_path_t;

struct dir_path {
    char path[PATH_MAX*2];
    char* end;
};

int number_of_digits(int);
char* xstrcpy(char* dest, const char* src);
char* xstrncpy(char* dest, const char* src, long int);
char* x_str(const char*, unsigned long);
int make_file(dir_path_t*, char*, int, char*);

#endif
