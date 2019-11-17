#include <util/render.h>
#include <util/util.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define ARG_FIND_PATTERN ("%[^$]$%d")
#define NULL_STR ("(null)")

char* render(const char* template, char** args, size_t args_l){
    int i, post_length = 0;
    const char* ptr = template;
    char* post_render, *post_ptr,
          *buffer = malloc(sizeof(char) * strlen(template));
    while(sscanf(ptr, ARG_FIND_PATTERN, buffer, &i) > 1){
        post_length += strlen(buffer);
        if(i < args_l && args[i])
            post_length += strlen(args[i]);
        else
            post_length += strlen(NULL_STR);
        ptr += strlen(buffer) + number_of_digits(i) + 1;
    }
    post_length += strlen(buffer);

    post_render = malloc(sizeof(char) * post_length + 1);
    ptr = template;
    post_ptr = post_render;
    while(sscanf(ptr, ARG_FIND_PATTERN, buffer, &i) > 1){
        post_ptr = xstrcpy(post_ptr, buffer);
        post_ptr = xstrcpy(post_ptr,
                           (i < args_l)?
                                args[i]: NULL_STR);
        ptr += strlen(buffer) + number_of_digits(i) + 1;
    }
    xstrcpy(post_ptr, buffer);
    free(buffer);
    return post_render;
}