#include <utils/render.h>
#include <unitest.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

char* CPM_SHARE_DIR;

int main(void){
    TEST(Rendering start,
        char template[] = "$0<a href=\"\">Blah$1</a>";
        char* args[] = {"/kick"};
        char* res = render(template, (const char**)args, sizeof(args)/sizeof(char*));
        T_ASSERT_STRING(res, "/kick<a href=\"\">Blah(null)</a>");
        free(res);
    );
    TEST(Rendering mid,
        char template[] = "<a href=\"$0\">$1Blah$$#0</a>";
        char* args[] = {"/kick"};
        char* res = render(template, (const char**)args, sizeof(args)/sizeof(char*));
        T_ASSERT_STRING(res, "<a href=\"/kick\">(null)Blah$0</a>");
        free(res);
    );
    TEST(Rendering end,
        char template[] = "<a href=\"\">Blah$1</a>$0";
        char* args[] = {"/kick"};
        char* res = render(template, (const char**)args, sizeof(args)/sizeof(char*));
        T_ASSERT_STRING(res, "<a href=\"\">Blah(null)</a>/kick");
        free(res);
    );
    return 0;
}