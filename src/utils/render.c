#include <utils/render.h>
#include <utils/util.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define ARG_FIND_PATTERN ("$%d")
#define NULL_STR ("(null)")

char* render(const char* template, const char** args, size_t args_l){
    int i, res, post_length = strlen(template);
    const char* start = template, *end;
    char* post_render, *post_ptr;

    while((start = strchr(start, '$'))){
        res = sscanf(start, ARG_FIND_PATTERN, &i);
        if(res > 0){
            if(i < args_l && args[i])
                post_length += strlen(args[i]);
            else
                post_length += strlen(NULL_STR);
            post_length -= (1 + number_of_digits(i));
        }
        start++;
    }

    post_render = malloc(sizeof(char) * post_length + 1);
    start = template;
    post_ptr = post_render;

    while((end = strchr(start, '$'))){
        res = sscanf(end, ARG_FIND_PATTERN, &i);
        post_ptr = xstrncpy(post_ptr, start, end - start + 2);
        if(res > 0){
            post_ptr = xstrcpy(post_ptr-1,
                            (i < args_l)?
                                    args[i]: NULL_STR);
            end += number_of_digits(i);
        }
        start = end + 1;
    }
    xstrcpy(post_ptr, start);
    return post_render;
}
