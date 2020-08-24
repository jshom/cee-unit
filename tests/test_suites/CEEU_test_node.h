/* test suite for test_result */
#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_test_node__new() {
    CEEU_test_node* tn = CEEU_test_node__new(test__CEEU_test_node__new);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_NULL(tn->next_test, "rn->next_test"));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(tn->tr, "tn->tr"));
    CEEU_assertions__add(as, CEEU_assert__is_true(
        tn->tf == test__CEEU_test_node__new,
        "tn->tf == test__CEEU_test_node__new"
    ));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_test_node__run() {
    CEEU_test_node* tn = CEEU_test_node__new(test__CEEU_test_node__new);
    CEEU_test_node__run(tn);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(tn->tr, "tn->tr"));
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        (char*) tn->tr->name,
        "test__CEEU_test_node__new"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(tn->tr, "tn->tr")); // assert does not erase tr
    CEEU_assertions__add(as, CEEU_assert__is_true(
        tn->tr->result_status,
        "tn->tr->result_status"
    ));
    return CEEU_assertions__resolve(as);
}

/* test function used to test test node */
CEEU_test_result* test__fail() {
    return CEEU_test_result__new(CEEU_FAILURE, (char*) __func__);
}

CEEU_test_result* test__CEEU_test_node__run__with_failed_test() {
    CEEU_test_node* tn = CEEU_test_node__new(test__fail);
    CEEU_test_node__run(tn);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(tn->tr, "tn->tr"));
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        (char*) tn->tr->name,
        "test__fail"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(tn->tr, "tn->tr")); // assert does not erase tr
    CEEU_assertions__add(as, CEEU_assert__is_false(
        tn->tr->result_status,
        "tn->tr->result_status"
    ));
    return CEEU_assertions__resolve(as);
}
