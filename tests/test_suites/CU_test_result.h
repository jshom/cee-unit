/* test suite for test_result */
#include "../../CU.h"
#include <string.h>

CU_test_result* test__CU_test_result__new() {
    CU_test_result* tr = CU_test_result__new(CU_SUCCESS, (char*) __func__);
    int result = 1;
    result *= 0 == strcmp(__func__, "test__CU_test_result__new");
    result *= tr->result_status == CU_SUCCESS;
    return CU_test_result__new(result, (char *) __func__);
}

CU_test_result* test__CU_test_result__new__with_failure() {
    CU_test_result* tr = CU_test_result__new(CU_FAILURE, (char*) __func__);
    int result = 1;
    result *= 0 == strcmp(__func__, "test__CU_test_result__new__with_failure");
    result *= tr->result_status == CU_FAILURE;
    return CU_test_result__new(result, (char *) __func__);
}


CU_test_result* test__CU_test_result__new__non_zero_or_one() {
    CU_test_result* tr = CU_test_result__new(534, (char*) __func__);
    int result = 1;
    result *= 0 == strcmp(__func__, "test__CU_test_result__new__non_zero_or_one");
    result *= tr->result_status == CU_FAILURE;
    return CU_test_result__new(result, (char *) __func__);
}
