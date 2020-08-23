#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_assert__new__success() {
    int result = CEEU_SUCCESS;
    CEEU_assert* a = CEEU_assert__new(CEEU_SUCCESS, (char *) "a failure");
    result *= a->status == CEEU_SUCCESS;
    result *= a->message == NULL;
    result *= a->next_assert == NULL;
    return CEEU_test_result__new(result, __func__);
}

CEEU_test_result* test__CEEU_assert__new__failure() {
    int result = CEEU_SUCCESS;
    CEEU_assert* a = CEEU_assert__new(CEEU_FAILURE, (char *) "a failure");
    result *= a->status == CEEU_FAILURE;
    result *= a->message != NULL;
    result *= (strcmp("a failure", a->message) == 0);
    result *= a->next_assert == NULL;
    return CEEU_test_result__new(result, __func__);
}

CEEU_test_result* test__CEEU_assert__is_true__success() {
    int result = CEEU_SUCCESS;
    CEEU_assert* a = CEEU_assert__is_true(1, "true");
    result *= a->message == NULL;
    result *= a->next_assert == NULL;
    result *= a->status == CEEU_SUCCESS;
    return CEEU_test_result__new(result, __func__);
}

CEEU_test_result* test__CEEU_assert__is_true__failure() {
    int result = CEEU_SUCCESS;
    CEEU_assert* a = CEEU_assert__is_true(0, "true");
    result *= strcmp(a->message, "Failed to assert \"true\" is true") == 0;
    result *= a->next_assert == NULL;
    result *= a->status == CEEU_FAILURE;
    return CEEU_test_result__new(result, __func__);
}

CEEU_test_result* test__CEEU_assert__int_equals__success() {
    int result = CEEU_SUCCESS;
    CEEU_assert* a = CEEU_assert__int_equals(1, 1);
    result *= a->status == CEEU_SUCCESS;
    result *= a->message == NULL;
    result *= a->next_assert == NULL;
    return CEEU_test_result__new(result, __func__);
}

CEEU_test_result* test__CEEU_assert__int_equals__failure() {
    int result = CEEU_SUCCESS;
    CEEU_assert* a = CEEU_assert__int_equals(1, 2);
    result *= a->status == CEEU_FAILURE;
    result *= strlen(a->message) != 0;
    result *= strcmp(a->message, "Failed to assert 1 equals 2") == 0;
    result *= a->next_assert == NULL;
    return CEEU_test_result__new(result, __func__);
}
