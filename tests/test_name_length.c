#include "utest.h"
#include "name_length.h"

UTEST(name_length, basic_tests) {
    ASSERT_EQ(name_length(""), 0);
}

UTEST(name_length, advanced_tests) {
ASSERT_EQ(name_length("Raul"), 4);
// Note that the space does NOT count!
ASSERT_EQ(name_length("Ana Maria"), 8);
}

UTEST_MAIN()