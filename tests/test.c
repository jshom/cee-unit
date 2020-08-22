#include "../CU.h" // you would download CU.h at reference that way
/* test suites */
#include "./test_suites/CU_test_result.h"

CU_test_result* test__always_succeeds() {
    return CU_test_result__new(CU_SUCCESS, (char* ) __FUNCTION__);
}

int main() {
    // create test runner
    CU_test_runner* trnr = CU_test_runner__new();
    // add tests
    CU_test_runner__add_test(trnr, &test__always_succeeds);
    CU_test_runner__add_test(trnr, &test__CU_test_result__new);
    // run all tests
    return CU_test_runner__exec(trnr);
}
