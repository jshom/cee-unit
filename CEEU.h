/**
 * A super simple C Unit Testing library
 * Cee how light weight it is, and thats why we call it Cee Unit :)
 *
 * cee-unit v0.4.1 (https://github.com/jshom/cee-unit)
 * Licensed under the GPLv3 License (https://github.com/jshom/cee-unit/blob/master/LICENSE)
 */
#ifndef __CEEU__
#define __CEEU__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const short int CEEU_SUCCESS = 1;
const short int CEEU_FAILURE = 0;
const char* CEEU_SUCCESS_MSG = "SUCCESS";
const char* CEEU_FAILURE_MSG = "FAILURE";
const size_t CEEU_ASSERTION_MESSAGE_SIZE = 128;
const size_t CEEU_ASSERTION_MESSAGE_SIZE_LARGE = 1024;

/* [CEE_UNIT] Type for an assertion i.e. expect some int to equal 5 */
typedef struct CEEU_assert {
    char* message;
    int status;
    struct CEEU_assert* next_assert;
} CEEU_assert;

/* [CEE_UNIT] Type for list of assertions to be used in test functions */
typedef struct CEEU_assertions {
    const char* name;
    CEEU_assert* head;
    CEEU_assert* tail;
    int status;
} CEEU_assertions;

/* [CEE_UNIT] Type for the result of a test case */
typedef struct CEEU_test_result {
    int result_status;
    const char* name;
    CEEU_assertions* assertions;
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
CEEU_test_result* CEEU_test_result__new(int status, const char* name) {
    CEEU_test_result* tr = (CEEU_test_result*) malloc(sizeof(CEEU_test_result));
    tr->result_status = (status == CEEU_SUCCESS);
    tr->name = name;
    return tr;
}

/* [CEE_UNIT] CEEU_test_result > new - Construct new test result from assertions */
CEEU_test_result* CEEU_test_result__new_from_assertions(CEEU_assertions* as) {
    CEEU_test_result* tr = (CEEU_test_result*) malloc(sizeof(CEEU_test_result));
    tr->result_status = as->status;
    tr->name = as->name;
    tr->assertions = as;
    return tr;
}

/* [CEE_UNIT] CEEU_assertions > print - Print assertions with option for all, or only failed */
void CEEU_assertions__print(
    CEEU_assertions* as
) {
   CEEU_assert* a = as->head;
   while (a) {
       if (a->status == CEEU_FAILURE) {
           printf("\t[FAILED ASSERTION] %s\n", a->message);
       }
       a = a->next_assert;
   }
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
    if (tr->assertions) {
        CEEU_assertions__print(tr->assertions);
    }
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
    printf("%d out of %d tests successful (%d%% passed)\n",
        trnr->num_successful,
        trnr->size,
        (int) (100 * trnr->num_successful/trnr->size)
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
    CEEU_test_runner* trnr,
    int enable_output
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
/* [CEE_UNIT] CEEU_assert > new - Create new assertion */
CEEU_assert* CEEU_assert__new(int status, char* failure_message) {
    CEEU_assert* a = (CEEU_assert*) malloc(sizeof(CEEU_assert));
    a->status = status;
    a->message = NULL;
    a->next_assert = NULL;
    if (a->status == CEEU_FAILURE) {
        a->message = failure_message;
    }
    return a;
}

/* [CEE_UNIT] CEEU_assertions > new - Create new assertions list */
CEEU_assertions* CEEU_assertions__new(const char* name) {
    CEEU_assertions* a = (CEEU_assertions*) malloc(sizeof(CEEU_assertions));
    a->name = name;
    a->head = NULL;
    a->tail = NULL;
    a->status = CEEU_SUCCESS;
    return a;
}

/* [CEE_UNIT] CEEU_assertions > add - Add assertion to CEEU_assertions */
void CEEU_assertions__add(CEEU_assertions* as, CEEU_assert* a) {
    if (!as->head) {
        as->head = a;
        as->tail = a;
    } else {
        as->tail->next_assert = a;
        as->tail = a;
    }
}

/* [CEE_UNIT] CEEU_assertions > resolve - Return new test result based on the status of provided assertions */
CEEU_test_result* CEEU_assertions__resolve(CEEU_assertions* as) {
    CEEU_assert* a = as->head;
    while (a) {
        as->status *= a->status;
        a = a->next_assert;
    }
    return CEEU_test_result__new_from_assertions(as);
}

/**
 * [CEE_UNIT]
 * CEEU_assert > int_equals - Create assertion to check for same integers values
 * Reports failure in form of: [Failed to assert {value} equals {expectation}]
 */
CEEU_assert* CEEU_assert__int_equals(int value, int expectation) {
    char* failure_message = (char*) malloc(CEEU_ASSERTION_MESSAGE_SIZE);
    sprintf(failure_message, "Failed to assert %d equals %d", value, expectation);
    return CEEU_assert__new(value == expectation, failure_message);
}

/**
 * [CEE_UNIT]
 * CEEU_assert > str_equals - Create assertion to check for same string values
 * Reports failure in form of: [Failed to assert ("{value}") equals ("{expectation}")]
 */
CEEU_assert* CEEU_assert__str_equals(char* value, const char* expectation) {
    char* failure_message = (char*) malloc(CEEU_ASSERTION_MESSAGE_SIZE_LARGE);
    sprintf(failure_message, "Failed to assert (\"%s\") equals (\"%s\")", value, expectation);
    return CEEU_assert__new(strcmp(value, expectation) == 0, failure_message);
}

/**
 * [CEE_UNIT]
 * CEEU_assert > is_true - Create assertion to check that the param is non-zero
 * Reports failure in form of: [Failed to assert "{name}" is true]
 */
CEEU_assert* CEEU_assert__is_true(int value, const char* name) {
    char* failure_message = (char*) malloc(CEEU_ASSERTION_MESSAGE_SIZE);
    sprintf(failure_message, "Failed to assert \"%s\" is true", name);
    return CEEU_assert__new(value != 0, failure_message);
}

/**
 * [CEE_UNIT]
 * CEEU_assert > is_false - Create assertion to check that the param is false
 * Reports failure in form of: [Failed to assert "{name}" is false]
 */
CEEU_assert* CEEU_assert__is_false(int value, const char* name) {
    char* failure_message = (char*) malloc(CEEU_ASSERTION_MESSAGE_SIZE);
    sprintf(failure_message, "Failed to assert \"%s\" is false", name);
    return CEEU_assert__new(value == 0, failure_message);
}

/**
 * [CEE_UNIT]
 * CEEU_assert > is_NULL - Create assertion to check a pointer is NULL
 * Reports failure in form of: [Failed to assert {value} equals {expectation}]
 */
CEEU_assert* CEEU_assert__is_NULL(void* p, const char* name) {
    char* failure_message = (char*) malloc(CEEU_ASSERTION_MESSAGE_SIZE);
    sprintf(failure_message, "Failed to assert \"%s\" is NULL", name);
    return CEEU_assert__new(p == NULL, failure_message);
}

/**
 * [CEE_UNIT]
 * CEEU_assert > is_not_NULL - Create assertion to check a pointer is NOT NULL
 * Reports failure in form of: [Failed to assert {value} equals {expectation}]
 */
CEEU_assert* CEEU_assert__is_not_NULL(void* p, const char* name) {
    char* failure_message = (char*) malloc(CEEU_ASSERTION_MESSAGE_SIZE);
    sprintf(failure_message, "Failed to assert \"%s\" is not NULL", name);
    return CEEU_assert__new(p != 0, failure_message);
}

#endif
