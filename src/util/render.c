#include <render.h>
#include <util.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

char* render(const char* template, size_t length, char** args){
    int i, post_length = 0;
    const char* ptr = template;
    char* post_render,
          *buffer = malloc(sizeof(char) * length);
    while(sscanf(ptr, "%s$%d", buffer, &i) > 1){
        post_length += strlen(buffer) + strlen(args[i]);
        ptr += strlen(buffer) + number_of_digits(i) + 1;
    }
    post_render = malloc(sizeof(char) * post_length + 1);
    ptr = template;
    while(sscanf(ptr, "%s$%d", buffer, &i) > 1){
        memcpy(post_render, buffer, strlen(buffer));
        ptr += strlen(buffer) + number_of_digits(i) + 1;
    }
    free(buffer);
    return post_render;
}