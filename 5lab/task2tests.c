#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "task2.h"


void creation_tests(){
    struct Term *term1 = Term__create(12, 00, 68);
    CU_ASSERT_EQUAL(term1->hour, 12);
    CU_ASSERT_EQUAL(term1->minute, 00);
    CU_ASSERT_EQUAL(term1->duration, 68);

    Term__init(term1, 1, 2, 0);
    CU_ASSERT_EQUAL(term1->hour, 1);
    CU_ASSERT_EQUAL(term1->minute, 2);
    CU_ASSERT_EQUAL(term1->duration, 0);

    Term__destroy(term1);

}

void toString_tests(){

    struct Term *term1 = Term__create(12, 00, 72000);
    CU_ASSERT_STRING_EQUAL(Term__toString(term1), "12:00 [72000]");

    Term__destroy(term1);
}

void bool_tests(){
    struct Term *term1 = Term__create(16, 43, 90);
    struct Term *term2 = Term__create(16, 43, 90);

    CU_ASSERT_EQUAL(Term__equals(term1, term2), 1);
    CU_ASSERT_EQUAL(Term__laterThan(term1, term2), 0);
    CU_ASSERT_EQUAL(Term__earlierThan(term1, term2), 0);

    Term__destroy(term1);
    Term__destroy(term2);


    term1 = Term__create(16, 43, 90);
    term2 = Term__create(18, 33, 90);

    CU_ASSERT_EQUAL(Term__equals(term1, term2), 0);
    CU_ASSERT_EQUAL(Term__laterThan(term1, term2), 0);
    CU_ASSERT_EQUAL(Term__earlierThan(term1, term2), 1);

    Term__destroy(term1);
    Term__destroy(term2);

    term1 = Term__create(16, 44, 90);
    term2 = Term__create(16, 43, 90);

    CU_ASSERT_EQUAL(Term__equals(term1, term2), 0);
    CU_ASSERT_EQUAL(Term__laterThan(term1, term2), 1);
    CU_ASSERT_EQUAL(Term__earlierThan(term1, term2), 0);

    Term__destroy(term1);
    Term__destroy(term2);




}

void Term_andTerm_test(){
    struct Term *term1 = Term__create(16, 30, 90);
    struct Term *term2 = Term__create(23, 45, 90);
    struct Term *term3 = Term__endTerm(term1, term2);


    CU_ASSERT_EQUAL(term3->hour, 16);
    CU_ASSERT_EQUAL(term3->minute, 30);
    CU_ASSERT_EQUAL(term3->duration, 435);


    Term__destroy(term1);
    Term__destroy(term2);


}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("test_suite", 0, 0);

    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "creation_tests", creation_tests)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "toString_tests", toString_tests))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "bool_tests", bool_tests))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "Term_andTerm_test", Term_andTerm_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    return CU_get_error();

    return 0;
}