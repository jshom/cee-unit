#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_assertions__new() {
    CEEU_assertions* as_example = CEEU_assertions__new(__func__);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_NULL(
        as_example->head,
        "as_example->head"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(
        as_example->tail,
        "as_example->tail"
    ));
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        (char*) as_example->name,
        __func__
    ));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assertions__add() {
    CEEU_assertions* as_example = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as_example, CEEU_assert__int_equals(1, 1));

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(
        as_example->head,
        "as_example->head"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(
        as_example->tail,
        "as_example->tail"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_true(
        as_example->head == as_example->tail,
        "as_example->head == as_example->tail"
    ));

    CEEU_assert* assert_is_true_example = CEEU_assert__is_true(0, "zero");
    CEEU_assertions__add(as_example, assert_is_true_example);

    CEEU_assertions__add(as, CEEU_assert__is_true(
        as_example->head != as_example->tail,
        "as_example->head != as_example->tail"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_true(
        as_example->tail == assert_is_true_example,
        "as_example->head == assert_is_true_example"
    ));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assertions__resolve() {
    CEEU_assertions* as_example = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as_example, CEEU_assert__int_equals(1, 1));
    CEEU_assertions__add(as_example, CEEU_assert__is_true(1, "always true"));
    CEEU_test_result* tr = CEEU_assertions__resolve(as_example);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_true(
        tr->result_status,
        "tr->result_status"
    ));
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        (char*) tr->name,
        __func__
    ));
    return CEEU_assertions__resolve(as);
}
