#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_assertions__new() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);
    int result = 1;
    result *= as->head == NULL;
    result *= as->tail == NULL;
    result *= strcmp(as->name, __func__) == 0;
    return CEEU_test_result__new(result, __func__);
}

CEEU_test_result* test__CEEU_assertions__add() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__int_equals(1, 1));
    int result = 1;
    result *= as->head != NULL;
    result *= as->tail != NULL;
    result *= as->head == as->tail;
    CEEU_assert* assert_is_true_example = CEEU_assert__is_true(0, "zero");
    CEEU_assertions__add(as, assert_is_true_example);
    result *= as->head != as->tail;
    result *= as->tail == assert_is_true_example;
    return CEEU_test_result__new(result, __func__);
}

CEEU_test_result* test__CEEU_assertions__resolve() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__int_equals(1, 1));
    CEEU_assertions__add(as, CEEU_assert__is_true(1, "always true"));
    CEEU_test_result* tr = CEEU_assertions__resolve(as);
    int result = CEEU_SUCCESS;
    result *= tr->result_status == CEEU_SUCCESS;
    result *= (0 == strcmp(tr->name, __func__));
    return CEEU_test_result__new(result, __func__);
}
