#include <utils/render.h>
#include <unitest.h>
#include <malloc.h>

void
rendering_start(void) {
    char template[] = "$0<a href=\"\">Blah$1</a>";
    char* args[] = {"/kick"};
    long len = render_length(template, (const char**)args, sizeof(args)/sizeof(char*));
    char* res = render(template, (const char**)args, sizeof(args)/sizeof(char*));

    T_ASSERT_LONG(len, 30L);
    T_ASSERT_STRING(res, "/kick<a href=\"\">Blah(null)</a>");
    free(res);
}

void
rendering_mid(void) {
    char template[] = "<a href=\"$0\">$1Blah$$#0</a>";
    char* args[] = {"/kick"};
    long len = render_length(template, (const char**)args, sizeof(args)/sizeof(char*));
    char* res = render(template, (const char**)args, sizeof(args)/sizeof(char*));

    T_ASSERT_LONG(len, 32L);
    T_ASSERT_STRING(res, "<a href=\"/kick\">(null)Blah$0</a>");
    free(res);
}

void
rendering_end(void) {
    char template[] = "<a href=\"\">Blah$1</a>$0";
    char* args[] = {"/kick"};
    long len = render_length(template, (const char**)args, sizeof(args)/sizeof(char*));
    char* res = render(template, (const char**)args, sizeof(args)/sizeof(char*));

    T_ASSERT_LONG(len, 30L);
    T_ASSERT_STRING(res, "<a href=\"\">Blah(null)</a>/kick");
    free(res);
}

int
main(void) {
    (void) SUITE_SETUP_RESULT;

    TEST(Rendering start, rendering_start);

    TEST(Rendering mid, rendering_mid);

    TEST(Rendering end, rendering_end);
    return 0;
}
