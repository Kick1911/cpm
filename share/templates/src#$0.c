#include <stdio.h>
#include <utils/utils.h>

int
main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    printf("Hello World\n");
    printf("5 + 6 = %d\n", add(5, 6));
    return 0;
}
