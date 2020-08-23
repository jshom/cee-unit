/* test suite for test_result */
#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_test_runner__new() {
    CEEU_test_runner* trnr = CEEU_test_runner__new();
    int result = 1;
    result *= trnr->size == 0;
    result *= trnr->head == NULL;
    result *= trnr->tail == NULL;
    return CEEU_test_result__new(result, (char *) __func__);
}

/* test function used to test test node */
CEEU_test_result* test__fail_1() {
    return CEEU_test_result__new(CEEU_FAILURE, (char*) __func__);
}

CEEU_test_result* test__CEEU_test_runner__add_test() {
    int result = 1;
    CEEU_test_runner* trnr = CEEU_test_runner__new();
    result *= trnr->size == 0;

    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    result *= trnr->size == 1;
    result *= trnr->tail == trnr->head;
    result *= trnr->head != NULL;

    CEEU_test_runner__add_test(trnr, &test__fail_1);
    result *= trnr->size == 2;
    result *= trnr->head != NULL;
    result *= trnr->head != trnr->tail;

    return CEEU_test_result__new(result, (char *) __func__);
}

CEEU_test_result* test__CEEU_test_runner__execute__successful() {
    int result = 1;
    CEEU_test_runner* trnr = CEEU_test_runner__new();
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__add_test);
    result *= CEEU_test_runner__exec(trnr, 0) == 0;
    return CEEU_test_result__new(result, (char*) __func__);
}

CEEU_test_result* test__CEEU_test_runner__execute__failing() {
    int result = 1;
    CEEU_test_runner* trnr = CEEU_test_runner__new();
    CEEU_test_runner__add_test(trnr, &test__CEEU_test_runner__new);
    CEEU_test_runner__add_test(trnr, &test__fail_1);
    result *= CEEU_test_runner__exec(trnr, 0) == 1;
    return CEEU_test_result__new(result, (char*) __func__);
}
