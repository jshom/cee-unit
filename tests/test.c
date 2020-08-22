#include "../CU.h" // you would download CU.h and have in your project

/* test suites */
#include "./test_suites/CU_test_result.h"
#include "./test_suites/CU_test_node.h"

CU_test_result* test__always_succeeds() {
    return CU_test_result__new(CU_SUCCESS, (char* ) __FUNCTION__);
}

int main() {
    // create test runner
    CU_test_runner* trnr = CU_test_runner__new();

    // add tests
    CU_test_runner__add_test(trnr, &test__always_succeeds);

    CU_test_runner__add_test(trnr, &test__CU_test_result__new);
    CU_test_runner__add_test(trnr, &test__CU_test_result__new__with_failure);
    CU_test_runner__add_test(trnr, &test__CU_test_result__new__non_zero_or_one);

    CU_test_runner__add_test(trnr, &test__CU_test_node__new);
    CU_test_runner__add_test(trnr, &test__CU_test_node__run);
    CU_test_runner__add_test(trnr, &test__CU_test_node__run__with_failed_test);

    // run all tests
    return CU_test_runner__exec(trnr);
}
