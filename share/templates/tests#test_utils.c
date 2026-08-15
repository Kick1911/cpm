#include <unitest.h>
#include <utils/utils.h>

static void
add_function(void) {
    T_ASSERT_NUM(add(-1, 1), 0);
    T_ASSERT_NUM(add(8, 2), 10);
}

int
main(void) {
    TEST(Add function, add_function);
    T_CONCLUDE();
    return 0;
}
