#include <util/render.h>
#include <unitest.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void){
    TEST(Rendering,
        char template[] = "<a href=\"$0\">Blah</a>";
        char* args[] = {"/kick"};
        char* res = render(template, strlen(template), args);
        T_ASSERT_STRING(res, "<a href=\"/kick\">Blah</a>");
        free(res);
    );
    return 0;
}