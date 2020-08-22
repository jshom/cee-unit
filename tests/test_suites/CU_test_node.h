/* test suite for test_result */
#include "../../CU.h"
#include <string.h>

CU_test_result* test__CU_test_node__new() {
    CU_test_node* tn = CU_test_node__new(test__CU_test_node__new);
    int result = 1;
    result *= tn->next_test == NULL;
    result *= tn->tr == NULL;
    result *= tn->tf == test__CU_test_node__new;
    return CU_test_result__new(result, (char *) __func__);
}

CU_test_result* test__CU_test_node__run() {
    CU_test_node* tn = CU_test_node__new(test__CU_test_node__new);
    CU_test_node__run(tn);
    int result = 1;
    result *= tn->tr != NULL;
    result *= 0 == strcmp(tn->tr->name, "test__CU_test_node__new");
    result *= tn->tf != NULL; // assert does not erase tf
    result *= tn->tr->result_status == CU_SUCCESS;
    return CU_test_result__new(result, (char *) __func__);
}

/* test function used to test test node */
CU_test_result* test__fail() {
    return CU_test_result__new(CU_FAILURE, (char*) __func__);
}

CU_test_result* test__CU_test_node__run__with_failed_test() {
    CU_test_node* tn = CU_test_node__new(test__fail);
    CU_test_node__run(tn);
    int result = 1;
    result *= tn->tr->result_status == CU_FAILURE;
    result *= tn->tr != NULL;
    result *= 0 == strcmp(tn->tr->name, "test__fail");
    result *= tn->tf != NULL; // assert does not erase tf
    return CU_test_result__new(result, (char *) __func__);
}
