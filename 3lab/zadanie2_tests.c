
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <CUnit/Basic.h>
#include "task2.h"

void gethexAsciif_test();

void reverse(int len, char *arr) {
    char temp;
    for (int i = 0; i < floor(len / 2); ++i) {
        temp = arr[len - i - 1];
        arr[len - i - 1] = arr[i];
        arr[i] = temp;
    }
}

void gethexAscii_test(){

    gethexAsciif_test("#", "23");
    gethexAsciif_test("(", "28");
    gethexAsciif_test("+", "2B");

}


void getData_test(){





}

void decompression_test(){





}


int main(){


    CU_pSuite pSuite = NULL;

    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry
    pSuite = CU_add_suite("gethexAscii_test_suite", 0, 0);


    // Always check if add was successful
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("gethexAscii_test_suite", 0, 0);
    // Add the test to the suite
    if (NULL == CU_add_test(pSuite, "gethexAscii_test", gethexAscii_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    pSuite = CU_add_suite("gethexAscii_test_suite", 0, 0);
    if (NULL == CU_add_test(pSuite, "gethexAscii_test", gethexAscii_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    pSuite = CU_add_suite("gethexAscii_test_suite", 0, 0);
    if (NULL == CU_add_test(pSuite, "gethexAscii_test", gethexAscii_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
    // Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL
    CU_basic_set_mode(CU_BRM_VERBOSE);

    // Run the tests and show the run summary
    CU_basic_run_tests();
    return CU_get_error();

    return 0;
}

void gethexAsciif_test(char ch[], char *check) {
    char *hexval = (char*)malloc(2 * sizeof (char));
    hexval = getHexAscii(ch);
    reverse(2, hexval);
    CU_ASSERT_NSTRING_EQUAL(hexval, check, strlen(hexval));
    free(hexval);
}



void compressed_test(char ch[], char *check) {
    char *hexval = (char*)malloc(2 * sizeof (char));
    hexval = getHexAscii(ch);
    reverse(2, hexval);
    CU_ASSERT_NSTRING_EQUAL(hexval, check, strlen(hexval));
    free(hexval);
}

//  gcc zadanie1_tests.c encryption.c -o zadanie1_tests -lcunit && ./zadanie1_tests