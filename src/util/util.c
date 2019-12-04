#include <util/util.h>
#include <malloc.h>
#include <string.h>

int number_of_digits(int n){
    int count = 1;
    while((n /= 10))
        count++;
    return count;
}

char* xstrcpy(char* dest, const char* src){
    const char* s = src;
    while((*dest++ = *s++));
    return dest - 1;
}

char* x_str(const char* s, size_t l){
    char* b = malloc(sizeof(char) * strlen(s) + l + 1);
    xstrcpy(b, s);
    return b;
}
