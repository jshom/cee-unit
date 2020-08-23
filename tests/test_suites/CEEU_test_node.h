/* test suite for test_result */
#include "../../CEEU.h"
#include <string.h>

CEEU_test_result* test__CEEU_test_node__new() {
    CEEU_test_node* tn = CEEU_test_node__new(test__CEEU_test_node__new);
    int result = 1;
    result *= tn->next_test == NULL;
    result *= tn->tr == NULL;
    result *= tn->tf == test__CEEU_test_node__new;
    return CEEU_test_result__new(result, (char *) __func__);
}

CEEU_test_result* test__CEEU_test_node__run() {
    CEEU_test_node* tn = CEEU_test_node__new(test__CEEU_test_node__new);
    CEEU_test_node__run(tn);
    int result = 1;
    result *= tn->tr != NULL;
    result *= 0 == strcmp(tn->tr->name, "test__CEEU_test_node__new");
    result *= tn->tf != NULL; // assert does not erase tf
    result *= tn->tr->result_status == CEEU_SUCCESS;
    return CEEU_test_result__new(result, (char *) __func__);
}

/* test function used to test test node */
CEEU_test_result* test__fail() {
    return CEEU_test_result__new(CEEU_FAILURE, (char*) __func__);
}

CEEU_test_result* test__CEEU_test_node__run__with_failed_test() {
    CEEU_test_node* tn = CEEU_test_node__new(test__fail);
    CEEU_test_node__run(tn);
    int result = 1;
    result *= tn->tr->result_status == CEEU_FAILURE;
    result *= tn->tr != NULL;
    result *= 0 == strcmp(tn->tr->name, "test__fail");
    result *= tn->tf != NULL; // assert does not erase tf
    return CEEU_test_result__new(result, (char *) __func__);
}
