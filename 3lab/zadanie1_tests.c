
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "encryption.h"

void encryption_test();

void assert_int_equals(const char *name, int expected, int actual) {
    if (expected != actual)
        printf("Test failed: %s, expected %d, got %d\n", name, expected, actual);
}

void assert_string_equals(const char *name, const char *expected, const char *actual) {
    if (strcmp(expected, actual) != 0)
        printf("Test failed: %s, expected %s, got %s\n", name, expected, actual);
    else{
        printf("Okk \n");
    }
}

void encrypt_test(){
    encryption_test("to be or not to be", "vq dg qt pqv vq dg");
    encryption_test("ala ma kota", "dod pd nrwd");
    encryption_test("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    encryption_test(" a b c d e f g h i j k l m n o p q r s t u v w x y z", " b c d e f g h i j k l m n o p q r s t u v w x y z a");

}

int main(){


    CU_pSuite pSuite = NULL;

    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry
    pSuite = CU_add_suite("encrypt_test_suite", 0, 0);

    // Always check if add was successful
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test to the suite
    if (NULL == CU_add_test(pSuite, "encrypt_test", encrypt_test))
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

void encryption_test(char *text, char *check) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char *ciphertext = (char*)malloc(strlen(text) * sizeof (char));
    caesar(text, alphabet, ciphertext);

    CU_ASSERT_NSTRING_EQUAL(ciphertext, check, strlen(text));
    free(ciphertext);
}

