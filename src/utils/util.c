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

int make_dir(const char* d, __mode_t mode){
    char buffer[PATH_MAX*2] = {0};
    struct stat st = {0};

    strcat(buffer, "./");
    strcat(buffer, d);

    if (stat(buffer, &st) == -1){
        if(mkdir(buffer, mode))
            goto error;
    }else
        goto error;

    return 0;
    error:
        fprintf(stderr, "Error creating directory: %s\n", d);
        return 1;
}

int make_file(const char* name, __mode_t mode, char* data){
    FILE* fp;

    fp = fopen(name, "w");
    if(!fp) {
        fprintf(stderr, "Error creating file: %s\n", name);
        goto close_file_and_error;
    }
    if(data)
        fwrite(data, sizeof(char), strlen(data), fp);

    fclose(fp);
    chmod(name, mode);
    return 0;
    close_file_and_error:
        fclose(fp);
        return 1;
}

char* read_file(const char* path){
    long size = 0;
    char* text;
    FILE* f = fopen(path, "r");

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    text = (char*)malloc(sizeof(char) * (size+1));
    fread(text, sizeof(char), size, f);
    text[size] = 0;
    fclose(f);

    return text;
}
