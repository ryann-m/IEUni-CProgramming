#include "utest.h"
#include "myRectangle.h"
#include <stdlib.h>

UTEST(rectangle, area) {
    Rectangle r;
    r.length = 5;
    r.width = 4;
    int a = area(r);
    ASSERT_EQ(20, a);
}

UTEST(rectangle, grow) {
    Rectangle r;
    r.length = 5;
    r.width = 10;

    grow(&r, 2, 3);
    ASSERT_EQ(7, r.length);
    ASSERT_EQ(12, r.width);
}

UTEST_MAIN();