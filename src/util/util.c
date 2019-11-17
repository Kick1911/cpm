#include <util/util.h>

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
