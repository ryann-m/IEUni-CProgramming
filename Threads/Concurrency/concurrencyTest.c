#include "concurrencyHeader.h"
#include "utest.h"
#include <math.h>
#include <stdlib.h>

UTEST(Threads, AverageMatchesSingleThreaded) {
    int size = 1000000;
    float* list = generate_random_list(size);

    double single = average_single_thread(list, size);
    double multi = average_multi_thread(list, size, 4);

    ASSERT_NEAR(single, multi, 1e-6);

    free(list);
}

UTEST_MAIN();
