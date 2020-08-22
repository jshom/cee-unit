/**
 * A super simple C Unit Testing library
 * Cee how light weight it is, and thats why we call it Cee Unit :)
 */

#ifndef __CU__
#define __CU__

#include <stdio.h>
#include <stdlib.h>

const short int CU_SUCCESS = 1;
const short int CU_FAILURE = 0;
const char* CU_SUCCESS_MSG = "SUCCESS";
const char* CU_FAILURE_MSG = "FAILURE";

/* [CEE_UNIT] Type for the result of a test case */
typedef struct CU_test_result {
    int result_status;
    char* name;
} CU_test_result;

/* [CEE_UNIT] Type for a function pointer that returns a test result */
typedef CU_test_result* (*CU_test)(void);

/* [CEE_UNIT] Type for the test runner to create a linked list of tests to run */
typedef struct CU_test_node {
    CU_test tf;
    CU_test_result* tr;
    struct CU_test_node* next_test;
} CU_test_node;

/* [CEE_UNIT] Type for a linked list of tests that has a final status */
typedef struct CU_test_runner {
    int status;
    struct CU_test_node* head;
    struct CU_test_node* tail;
} CU_test_runner;

/* [CEE_UNIT] CU_test_result > new - Construct new test result */
CU_test_result* CU_test_result__new(int status, char* name) {
    CU_test_result* tr = (CU_test_result*) malloc(sizeof(CU_test_result));
    tr->result_status = (status == CU_SUCCESS);
    tr->name = name;
    return tr;
}

/* [CEE_UNIT] CU_test_result > print - Print result of the completed test */
void CU_test_result__print(CU_test_result* tr) {
    const char* msg_status;
    if (tr->result_status == CU_SUCCESS) {
        msg_status = CU_SUCCESS_MSG;
    } else {
        msg_status = CU_FAILURE_MSG;
    }
    printf("[%s] for %s\n", msg_status, tr->name);
}

/* [CEE_UNIT] CU_test_runner > new - Construct test runner */
CU_test_runner* CU_test_runner__new() {
    CU_test_runner* trnr = (CU_test_runner*) malloc(sizeof(CU_test_runner));
    trnr->head = NULL;
    trnr->tail = NULL;
    return trnr;
}

/* [CEE_UNIT] CU_test_node > new - Construct new test node for execution list */
CU_test_node* CU_test_node__new(CU_test tf) {
    CU_test_node* t = (CU_test_node*) malloc(sizeof(CU_test_node));
    t->tf = tf;
    t->next_test = NULL;
    t->tr = NULL;
    return t;
}

/* [CEE_UNIT] CU_test_node > run - Execute a test and save the result */
CU_test_result* CU_test_node__run(CU_test_node* tn) {
    tn->tr = tn->tf();
    return tn->tr;
}

/* [CEE_UNIT] CU_test_runner > add_test - Add a test to the test runner */
void CU_test_runner__add_test(CU_test_runner* trnr, CU_test tf) {
    CU_test_node* t = CU_test_node__new(tf);
    if (!trnr->head) {
        trnr->head = t;
        trnr->tail = t;
    } else {
        trnr->tail->next_test = t;
        trnr->tail = t;
    }
}

/**
 * [CEE_UNIT]
 * CU_test_runner > exec - Executes all added tests
 * Returns process error code:
 *  - 0 if success
 *  - 1 if failure
 * (Opposite of CU_SUCCESS, CU_FAILURE)
 */
int CU_test_runner__exec(CU_test_runner* trnr) {
    int final_status = CU_SUCCESS;
    CU_test_node* t = trnr->head;
    while (t) {
        CU_test_node__run(t);
        CU_test_result__print(t->tr);
        final_status *= t->tr->result_status;
        t = t->next_test;
    }
    return !final_status;
}

#endif
