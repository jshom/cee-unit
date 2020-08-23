/* test suite for test_result */
#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_test_result__new() {
    CEEU_test_result* tr = CEEU_test_result__new(CEEU_SUCCESS, (char*) __func__);
    int result = 1;
    result *= 0 == strcmp(__func__, "test__CEEU_test_result__new");
    result *= tr->result_status == CEEU_SUCCESS;
    return CEEU_test_result__new(result, (char *) __func__);
}

CEEU_test_result* test__CEEU_test_result__new__with_failure() {
    CEEU_test_result* tr = CEEU_test_result__new(CEEU_FAILURE, (char*) __func__);
    int result = 1;
    result *= 0 == strcmp(__func__, "test__CEEU_test_result__new__with_failure");
    result *= tr->result_status == CEEU_FAILURE;
    return CEEU_test_result__new(result, (char *) __func__);
}


CEEU_test_result* test__CEEU_test_result__new__non_zero_or_one() {
    CEEU_test_result* tr = CEEU_test_result__new(534, (char*) __func__);
    int result = 1;
    result *= 0 == strcmp(__func__, "test__CEEU_test_result__new__non_zero_or_one");
    result *= tr->result_status == CEEU_FAILURE;
    return CEEU_test_result__new(result, (char *) __func__);
}
