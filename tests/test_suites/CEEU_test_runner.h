/* test suite for test_result */
#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_test_runner__new() {
    CEEU_test_runner* trnr = CEEU_test_runner__new();

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__int_equals(trnr->size, 0));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(trnr->head, "trnr->head"));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(trnr->tail, "trnr->tail"));
    CEEU_assertions__add(as, CEEU_assert__int_equals(trnr->num_successful, 0));
    return CEEU_assertions__resolve(as);
}

/* test function used to test test node */
CEEU_test_result* test__fail_1() {
    return CEEU_test_result__new(CEEU_FAILURE, __func__);
}

CEEU_test_result* test__CEEU_test_runner__add_test() {
    CEEU_test_runner* trnr = CEEU_test_runner__new();
    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__int_equals(trnr->size, 0));

    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    CEEU_assertions__add(as, CEEU_assert__int_equals(trnr->size, 1));
    CEEU_assertions__add(as, CEEU_assert__is_true(trnr->head == trnr->tail, "trnr->head == trnr->tail"));
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(trnr->head, "trnr->head"));

    CEEU_test_runner__add_test(trnr, &test__fail_1);
    CEEU_assertions__add(as, CEEU_assert__int_equals(trnr->size, 2));
    CEEU_assertions__add(as, CEEU_assert__is_false(trnr->head == trnr->tail, "trnr->head == trnr->tail"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_test_runner__execute__successful() {
    CEEU_test_runner* trnr = CEEU_test_runner__new();
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__add_test);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__int_equals(CEEU_test_runner__exec(trnr, 0), 0));
    CEEU_assertions__add(as, CEEU_assert__int_equals(trnr->num_successful, 2));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_test_runner__execute__failing() {
    int result = 1;
    CEEU_test_runner* trnr = CEEU_test_runner__new();
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    CEEU_test_runner__add_test(trnr, &test__fail_1);

    CEEU_assertions *as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__int_equals(CEEU_test_runner__exec(trnr, 0), 1));
    CEEU_assertions__add(as, CEEU_assert__int_equals(trnr->num_successful, 1));
    return CEEU_assertions__resolve(as);
}
