
#include <unitest.h>
#include <stdio.h>
#include <utils/utils.h>

int main(void){
    TEST(Add function,
        T_ASSERT_NUM(add(-1, 1), 0);
        T_ASSERT_NUM(add(8, 2), 10);
    );
    return 0;
}
