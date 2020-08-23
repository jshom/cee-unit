/**
 * A super simple C Unit Testing library
 * Cee how light weight it is, and thats why we call it Cee Unit :)
 */
#ifndef __CEEU__
#define __CEEU__

#include <stdio.h>
#include <stdlib.h>

const short int CEEU_SUCCESS = 1;
const short int CEEU_FAILURE = 0;
const char* CEEU_SUCCESS_MSG = "SUCCESS";
const char* CEEU_FAILURE_MSG = "FAILURE";

/* [CEE_UNIT] Type for the result of a test case */
typedef struct CEEU_test_result {
    int result_status;
    char* name;
} CEEU_test_result;

/* [CEE_UNIT] Type for a function pointer that returns a test result */
typedef CEEU_test_result* (*CEEU_test)(void);

/* [CEE_UNIT] Type for the test runner to create a linked list of tests to run */
typedef struct CEEU_test_node {
    CEEU_test tf;
    CEEU_test_result* tr;
    struct CEEU_test_node* next_test;
} CEEU_test_node;

/* [CEE_UNIT] Type for a linked list of tests that has a final status */
typedef struct CEEU_test_runner {
    int status;
    struct CEEU_test_node* head;
    struct CEEU_test_node* tail;
    int size;
    int num_successful;
} CEEU_test_runner;

/* [CEE_UNIT] CEEU_test_result > new - Construct new test result */
CEEU_test_result* CEEU_test_result__new(int status, char* name) {
    CEEU_test_result* tr = (CEEU_test_result*) malloc(sizeof(CEEU_test_result));
    tr->result_status = (status == CEEU_SUCCESS);
    tr->name = name;
    return tr;
}

/* [CEE_UNIT] CEEU_test_result > print - Print result of the completed test */
void CEEU_test_result__print(CEEU_test_result* tr) {
    const char* msg_status;
    if (tr->result_status == CEEU_SUCCESS) {
        msg_status = CEEU_SUCCESS_MSG;
    } else {
        msg_status = CEEU_FAILURE_MSG;
    }
    printf("[%s] for %s\n", msg_status, tr->name);
}

/* [CEE_UNIT] CEEU_test_node > new - Construct new test node for execution list */
CEEU_test_node* CEEU_test_node__new(CEEU_test tf) {
    CEEU_test_node* t = (CEEU_test_node*) malloc(sizeof(CEEU_test_node));
    t->tf = tf;
    t->next_test = NULL;
    t->tr = NULL;
    return t;
}

/* [CEE_UNIT] CEEU_test_node > run - Execute a test and save the result */
CEEU_test_result* CEEU_test_node__run(CEEU_test_node* tn) {
    tn->tr = tn->tf();
    return tn->tr;
}

/* [CEE_UNIT] CEEU_test_runner > new - Construct test runner */
CEEU_test_runner* CEEU_test_runner__new() {
    CEEU_test_runner* trnr = (CEEU_test_runner*) malloc(sizeof(CEEU_test_runner));
    trnr->head = NULL;
    trnr->tail = NULL;
    trnr->size = 0;
    trnr->num_successful = 0;
    trnr->status = CEEU_SUCCESS;
    return trnr;
}

/* [CEE_UNIT] CEEU_test_runner > add_test - Add a test to the test runner */
void CEEU_test_runner__add_test(CEEU_test_runner* trnr, CEEU_test tf) {
    CEEU_test_node* t = CEEU_test_node__new(tf);
    if (!trnr->head) {
        trnr->head = t;
        trnr->tail = t;
    } else {
        trnr->tail->next_test = t;
        trnr->tail = t;
    }
    trnr->size += 1;
}

void CEEU_test_runner__print(
    CEEU_test_runner* trnr,
    int enable_output
) {
    if (!enable_output) return;
    CEEU_test_node* tn = trnr->head;
    while (tn) {
        CEEU_test_result__print(tn->tr);
        tn = tn->next_test;
    }
    printf("** SUMMARY **\n");
    printf("%d out of %d tests successfull (%d\%% passed)\n",
        trnr->num_successful,
        trnr->size,
        (int) (100 * (double) trnr->num_successful/trnr->size)
    );
}

/**
 * [CEE_UNIT]
 * CEEU_test_runner > exec - Executes all added tests
 * Returns process error code:
 *  - 0 if success
 *  - 1 if failure
 * (Opposite of CEEU_SUCCESS, CEEU_FAILURE)
 */
int CEEU_test_runner__exec(
    CEEU_test_runner* trnr, /* test runner */
    int enable_output /* enable logging */
) {
    CEEU_test_node* tn = trnr->head;
    while (tn) {
        CEEU_test_node__run(tn);
        trnr->status *= tn->tr->result_status;
        trnr->num_successful += tn->tr->result_status;
        tn = tn->next_test;
    }
    CEEU_test_runner__print(trnr, enable_output);
    return !trnr->status;
}

#endif
