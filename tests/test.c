#include "CEEU.h" // you would download CEEU.h and have in your project

/* test suites */
#include "./test_suites/CEEU_test_result.h"
#include "./test_suites/CEEU_test_node.h"
#include "./test_suites/CEEU_test_runner.h"
#include "./test_suites/CEEU_assert.h"
#include "./test_suites/CEEU_assertions.h"

int main() {
    // create test runner
    CEEU_test_runner* trnr = CEEU_test_runner__new();

    // add tests
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_result__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_result__new__with_failure);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_result__new__non_zero_or_one);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_result__new_with_assertions);

    CEEU_test_runner__add_test(trnr, &test__CEEU_test_node__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_node__run);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_node__run__with_failed_test);

    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__add_test);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__execute__successful);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__execute__failing);

    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__new__success);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__new__failure);

    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_true__success);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_true__failure);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_false__success);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_false__failure);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__int_equals__success);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__int_equals__failure);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_NULL__success);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_NULL__failure);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_not_NULL__success);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__is_not_NULL__failure);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__str_equals__success);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assert__str_equals__failure);

    CEEU_test_runner__add_test(trnr, &test__CEEU_assertions__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assertions__add);
    CEEU_test_runner__add_test(trnr, &test__CEEU_assertions__resolve);

    /* run all tests */
    return CEEU_test_runner__exec(trnr, 1);
}
