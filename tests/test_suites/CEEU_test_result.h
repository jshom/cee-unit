#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_test_result__new() {
    CEEU_test_result* tr = CEEU_test_result__new(CEEU_SUCCESS, __func__);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        (char*) tr->name,
        "test__CEEU_test_result__new"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_true(
        tr->result_status == CEEU_SUCCESS,
        "tr->result_status"
    ));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_test_result__new__with_failure() {
    CEEU_test_result* tr = CEEU_test_result__new(CEEU_FAILURE, __func__);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        (char*) tr->name,
        "test__CEEU_test_result__new__with_failure"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_false(
        tr->result_status,
        "tr->result_status"
    ));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_test_result__new__non_zero_or_one() {
    CEEU_test_result* tr = CEEU_test_result__new(534, __func__);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        (char*) tr->name,
        "test__CEEU_test_result__new__non_zero_or_one"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_false(
        tr->result_status,
        "tr->result_status"
    ));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_test_result__new_with_assertions() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_test_result* tr = CEEU_test_result__new_from_assertions(as);
    CEEU_assertions__add(as, CEEU_assert__int_equals(tr->result_status, CEEU_SUCCESS));
    CEEU_assertions__add(as, CEEU_assert__str_equals((char*) tr->name, __func__));
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(tr->assertions, "as->assertions"));
    return CEEU_assertions__resolve(as);
}
