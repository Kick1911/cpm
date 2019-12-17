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

int make_file(dir_path_t* d, char* name, int type, char* data){
    FILE* fp;
    char buffer[PATH_MAX*2] = {0};
    struct stat st = {0};

    xstrcpy(d->end, name);
    strcat(buffer, "./");
    strcat(buffer, d->path);
    printf("Creating %s\n", buffer);

    switch(type){
        case TREE_NODE_DIR:
            if (stat(buffer, &st) == -1)
                if(mkdir(buffer, 0700)){
                    fprintf(stderr, "Error creating directory: %s\n", d->path);
                    goto error;
                }
        break;
        case TREE_NODE_FILE:
            fp = fopen(buffer, "a");
            if(!fp) {
                fprintf(stderr, "Error creating file: %s\n", d->path);
                goto close_file_and_error;
            }
            if(data)
                fwrite(data, sizeof(char), strlen(data), fp);
            fclose(fp);
        break;
        default:
            fprintf(stderr, "Error not Directory or File\n");
    }
    return 0;
    close_file_and_error:
        fclose(fp);
    error:
        return 1;
}
