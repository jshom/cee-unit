/* test suite for test_result */
#include "../../CU.h"
#include <string.h>

CU_test_result* test__CU_test_result__new() {
    CU_test_result* tr = CU_test_result__new(1, (char *) __func__);
    int result = 1;
    result *= 0 == strcmp(__func__, "test__CU_test_result__new");
    return CU_test_result__new(result, (char *) __func__);
}
