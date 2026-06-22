#include <utils/render.h>
#include <utils/util.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define ARG_FIND_PATTERN ("$%d")
#define NULL_STR ("(null)")

long
render_length(const char* template, const char** args, int args_l){
    int i, res;
    const char* start = template;
    long post_length = (long)strlen(template);

    while((start = strchr(start, '$'))){
        res = sscanf(start, ARG_FIND_PATTERN, &i);
        if(res > 0){
            if(i < args_l && args[i])
                post_length += (long)strlen(args[i]);
            else
                post_length += (long)strlen(NULL_STR);
            post_length -= (1 + number_of_digits(i));
        } else if(!strncmp(start, "$#", 2))
            post_length -= 2;
        start++;
    }

    return post_length;
}

char*
render(const char* template, const char** args, int args_l){
    int i, res;
    long post_length;
    const char* start = template, *end;
    char* post_render, *post_ptr;

    post_length = render_length(template, args, args_l);
    if (post_length < 0) return NULL;

    post_render = malloc(sizeof(char) * (size_t)(post_length + 1));
    start = template;
    post_ptr = post_render;

    while((end = strchr(start, '$'))){
        res = sscanf(end, ARG_FIND_PATTERN, &i);
        post_ptr = xstrncpy(post_ptr, start, end - start + 1);
        if(res > 0){
            post_ptr = xstrcpy(post_ptr - 1,
                               (i < args_l)?
                                    args[i]: NULL_STR);
            end += number_of_digits(i);
        } else if(!strncmp(end, "$#", 2)){
            post_ptr--; end++;
        }
        start = end + 1;
    }
    xstrcpy(post_ptr, start);
    return post_render;
}
