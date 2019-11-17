#include <util/render.h>
#include <unitest.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void){
    TEST(Rendering,
        char template[] = "<a href=\"$0\">Blah$1</a>";
        char* args[] = {"/kick"};
        char* res = render(template, args, sizeof(args)/sizeof(char*));
        T_ASSERT_STRING(res, "<a href=\"/kick\">Blah(null)</a>");
        free(res);
    );
    return 0;
}