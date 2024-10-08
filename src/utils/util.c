#define _GNU_SOURCE

#include <utils/util.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

int number_of_digits(int n){
    int count = 1;
    while((n /= 10) && count++);
    return count;
}

char* xstrcpy(char* dest, const char* src){
    return xstrncpy(dest, src, 0) - 1;
}

char* xstrncpy(char* dest, const char* src, long int n){
    const char* s = src;
    while((*dest++ = *s++) && --n);
    return dest;
}

char* x_str(const char* s, size_t l){
    char* b = malloc(sizeof(char) * strlen(s) + l + 1);
    xstrcpy(b, s);
    return b;
}

int
make_dir(const char* d, size_t size, mode_t mode){
    int ret = 0;
    char* end, *ptr;
    char directory[PATH_MAX*2] = {0};
    char buffer[PATH_MAX*2] = {0};

    sprintf(directory, "%s%s", d, (d[size - 1] != '/') ? "/" : "");

    end = strchr(directory, '/');
    while (end) {
        ptr = xstrcpy(buffer, "./");
        xstrncpy(ptr, directory, end - directory);
        if (mkdir(buffer, mode) == -1) ret = 1;

        end = strchr(end + 1, '/');
    }

    return ret;
}

int
make_file(const char* name, const char* flags, mode_t mode, char* data){
    FILE* fp;

    fp = fopen(name, flags);
    if (!fp) goto close_file_and_error;

    if (data) fwrite(data, sizeof(char), strlen(data), fp);

    fclose(fp);
    chmod(name, mode);
    return 0;
close_file_and_error:
    return 1;
}

char* read_file(const char* path){
    long size = 0, bytes_read = 0;
    char* text;
    FILE* f = fopen(path, "r");

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    text = (char*)malloc(sizeof(char) * (size+1));

    bytes_read = fread(text, sizeof(char), size, f);
    if (!bytes_read) goto failed;
    text[bytes_read] = 0;

    fclose(f);

    return text;
failed:
    fclose(f);
    return NULL;
}
