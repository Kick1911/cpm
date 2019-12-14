#include <util/render.h>
#include <util/util.h>
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
        if(res < 1) continue;
        if(i < args_l && args[i])
            post_length += strlen(args[i]);
        else
            post_length += strlen(NULL_STR);
        post_length -= (1 + number_of_digits(i));
        start++;
    }

    post_render = malloc(sizeof(char) * post_length + 1);
    start = template;
    post_ptr = post_render;

    while((end = strchr(start, '$'))){
        res = sscanf(end, ARG_FIND_PATTERN, &i);
        if(res < 1) continue;
        if(start < end)
            post_ptr = xstrncpy(post_ptr, start, end - start + 1);
        post_ptr = xstrcpy(post_ptr,
                        (i < args_l)?
                                args[i]: NULL_STR);
        start = end + 1 + number_of_digits(i);
    }
    xstrcpy(post_ptr, start);
    return post_render;
}
