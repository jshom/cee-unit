#include "../../CEEU.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CEEU_test_result* test__CEEU_assert__new__success() {
    CEEU_assert* a = CEEU_assert__new(CEEU_SUCCESS, (char *) "a failure");

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_true(a->status, "a->status"));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a->message, "a->message"));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a->next_assert, "a->next_assert"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__new__failure() {
    CEEU_assert* a = CEEU_assert__new(CEEU_FAILURE, (char *) "a failure");

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_false(a->status, "a->status"));
    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(a->message, "a->message"));
    CEEU_assertions__add(as, CEEU_assert__str_equals(a->message, "a failure"));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a->next_assert, "a->next_assert"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__is_true__success() {
    CEEU_assert* a = CEEU_assert__is_true(1, "true");

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a->message, "a->next_assert"));
    CEEU_assertions__add(as, CEEU_assert__is_true(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__is_true__failure() {
    CEEU_assert* a = CEEU_assert__is_true(0, "always false");

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        a->message,
        "Failed to assert \"always false\" is true"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_false(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__int_equals__success() {
    CEEU_assert* a = CEEU_assert__int_equals(1, 1);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a->message, "a->next_assert"));
    CEEU_assertions__add(as, CEEU_assert__is_true(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__int_equals__failure() {
    CEEU_assert* a = CEEU_assert__int_equals(1, 2);

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        a->message,
        "Failed to assert 1 equals 2"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_false(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__is_NULL__success() {
    CEEU_test_result* tr_for_test = NULL;
    int* p_int = NULL;
    CEEU_assert* a_tr = CEEU_assert__is_NULL(tr_for_test, "tr_for_test");
    CEEU_assert* a_int = CEEU_assert__is_NULL(p_int, "p_int");

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_true(a_tr->status, "a_tr->status"));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a_tr->message, "a_tr->message"));
    CEEU_assertions__add(as, CEEU_assert__is_true(a_int->status, "a_int->status"));
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a_int->message, "a_int->message"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__is_NULL__failure() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);

    int* p_int = (int*) malloc(sizeof(int));
    CEEU_test_result* tr_for_test = CEEU_test_result__new(CEEU_SUCCESS, __func__);
    CEEU_assert* a_tr = CEEU_assert__is_NULL(tr_for_test, "tr_for_test");
    CEEU_assert* a_int = CEEU_assert__is_NULL(p_int, "p_int");

    CEEU_assertions__add(as, CEEU_assert__str_equals(
        a_tr->message,
        "Failed to assert \"tr_for_test\" is NULL"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_false(a_tr->status, "a_tr->status"));
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        a_int->message,
        "Failed to assert \"p_int\" is NULL"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_false(a_int->status, "a_tr->status"));

    return CEEU_assertions__resolve(as);
}


CEEU_test_result* test__CEEU_assert__is_not_NULL__success() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assert* a_as = CEEU_assert__is_not_NULL(as, "as");
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a_as->message, "tr_for_test"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__is_not_NULL__failure() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);

    CEEU_test_result* tr = NULL;
    CEEU_assert* a_as = CEEU_assert__is_not_NULL(tr, "tr");

    CEEU_assertions__add(as, CEEU_assert__is_not_NULL(a_as->message, "a_as->message"));
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        a_as->message,
        "Failed to assert \"tr\" is not NULL"
    ));

    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__is_false__success() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);

    CEEU_assert* a = CEEU_assert__is_false(0, "always false");

    CEEU_assertions__add(as, a);
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a->message,"a->message"));
    CEEU_assertions__add(as, CEEU_assert__is_true(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__is_false__failure() {
    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assert* a = CEEU_assert__is_false(1, "always true");
    CEEU_assertions__add(as, CEEU_assert__str_equals(a->message, "Failed to assert \"always true\" is false"));
    CEEU_assertions__add(as, CEEU_assert__is_false(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__str_equals__success() {
    CEEU_assert* a = CEEU_assert__str_equals((char*) "string one", "string one");

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__is_NULL(a->message, "a->message"));
    CEEU_assertions__add(as, CEEU_assert__is_true(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}

CEEU_test_result* test__CEEU_assert__str_equals__failure() {
    CEEU_assert* a = CEEU_assert__str_equals((char*) "string one", "string two");

    CEEU_assertions* as = CEEU_assertions__new(__func__);
    CEEU_assertions__add(as, CEEU_assert__str_equals(
        a->message,
        "Failed to assert (\"string one\") equals (\"string two\")"
    ));
    CEEU_assertions__add(as, CEEU_assert__is_false(a->status, "a->status"));
    return CEEU_assertions__resolve(as);
}
