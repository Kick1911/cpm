#include <util/util.h>
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
    return xstrncpy(dest, src, 0);
}

char* xstrncpy(char* dest, const char* src, long int n){
    const char* s = src;
    while((*dest++ = *s++) && --n);
    return dest - 1;
}

char* x_str(const char* s, size_t l){
    char* b = malloc(sizeof(char) * strlen(s) + l + 1);
    xstrcpy(b, s);
    return b;
}

int make_dir(dir_path_t* d, __mode_t mode){
    char buffer[PATH_MAX*2] = {0};
    struct stat st = {0};

    strcat(buffer, "./");
    strcat(buffer, d->path);

    if (stat(buffer, &st) == -1){
        if(mkdir(buffer, mode))
            goto error;
    }else
        goto error;

    return 0;
    error:
        fprintf(stderr, "Error creating directory: %s\n", d->path);
        return 1;
}

int make_file(dir_path_t* d, char* name, __mode_t mode, char* data){
    FILE* fp;
    char buffer[PATH_MAX*2] = {0};

    xstrcpy(d->end, name);
    strcat(buffer, "./");
    strcat(buffer, d->path);

    fp = fopen(buffer, "a");
    if(!fp) {
        fprintf(stderr, "Error creating file: %s\n", d->path);
        goto close_file_and_error;
    }
    if(data)
        fwrite(data, sizeof(char), strlen(data), fp);

    fclose(fp);
    chmod(buffer, mode);
    return 0;
    close_file_and_error:
        fclose(fp);
        return 1;
}
