#include "../CEEU.h" // you would download CEEU.h and have in your project

/* test suites */
#include "./test_suites/CEEU_test_result.h"
#include "./test_suites/CEEU_test_node.h"
#include "./test_suites/CEEU_test_runner.h"

CEEU_test_result* test__always_succeeds() {
    return CEEU_test_result__new(CEEU_SUCCESS, (char* ) __FUNCTION__);
}

int main() {
    // create test runner
    CEEU_test_runner* trnr = CEEU_test_runner__new();

    // add tests
    CEEU_test_runner__add_test(trnr, &test__always_succeeds);

    CEEU_test_runner__add_test(trnr, &test__CEEU_test_result__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_result__new__with_failure);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_result__new__non_zero_or_one);

    CEEU_test_runner__add_test(trnr, &test__CEEU_test_node__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_node__run);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_node__run__with_failed_test);

    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__add_test);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__execute__successful);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__execute__failing);

    /* run all tests */
    return CEEU_test_runner__exec(trnr, 1);
}
