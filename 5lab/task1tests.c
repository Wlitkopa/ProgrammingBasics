
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <CUnit/Basic.h>
#include "task1.h"



enum Day {MON, TUE, WED, THU, FRI, SAT, SUN};

enum Action {DAY_EARLIER = 1, DAY_LATER = 2, TIME_EARLIER = 3, TIME_LATER = 4};

void Day__toStringf_test(enum Day day, char *check);

void Day__nextDayf_test(enum Day day, int check);

void Day__prevDayf_test(enum Day day, int check);

//void Action__parsef_test(int argc, char **argv);

int Action__parsef_test(int argc, char **argv){

    enum Action *actionset = parse(argc, argv);

    for (int i = 0; i < argc - 2; ++i) {
        printf("argv[%d]: %s and actionset[%d]: %d\n", i+2, argv[i+2], i, actionset[i]);
        if (!strcmp(argv[i+2], "d-") && (actionset[i] != 1)){
            printf("argv[%d]: %s and actionset[%d]: %d\n", i+2, argv[i+2], i, actionset[i]);
            printf("Pars Test Failed\n");
            return 1;
        }
        else if (!strcmp(argv[i+2], "d+") && (actionset[i] != 2)) {
            printf("argv[%d]: %s and actionset[%d]: %d\n", i+2, argv[i+2], i, actionset[i]);
            printf("Pars Test Failed\n");
            return 1;
        }
        else if (!strcmp(argv[i+2], "t-") && (actionset[i] != 3)) {
            printf("argv[%d]: %s and actionset[%d]: %d\n", i+2, argv[i+2], i, actionset[i]);
            printf("Pars Test Failed\n");
            return 1;
        }
        else if (!strcmp(argv[i+2], "t+") && (actionset[i] != 4)) {
            printf("argv[%d]: %s and actionset[%d]: %d\n", i+2, argv[i+2], i, actionset[i]);
            printf("Pars Test Failed\n");
            return 1;
        }
    }

    printf("Test passed!\n");
    return 0;
}

void Day__toString_test(){

    Day__toStringf_test(MON, "Poniedziałek");
    Day__toStringf_test(SUN, "Niedziela");
    Day__toStringf_test(WED, "Środa");

}

void Day__nextDay_test(){

    Day__nextDayf_test(MON, 1);
    Day__nextDayf_test(THU, 4);
    Day__nextDayf_test(SUN, 0);

}

void Day__prevDay_test(){

    Day__prevDayf_test(FRI, 3);
    Day__prevDayf_test(MON, 6);
    Day__prevDayf_test(SUN, 5);

}

void Action__parse_test(){
//    Action__parsef_test();

}

int main(int argc, char **argv){

    Action__parsef_test(argc, argv);

    CU_pSuite pSuite = NULL;

    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry
    pSuite = CU_add_suite("Day__toString_test_suite", 0, 0);


    // Always check if add was successful
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Day__toString_test_suite", 0, 0);
    // Add the test to the suite
    if (NULL == CU_add_test(pSuite, "Day__toString_test", Day__toString_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add a suite to the registry
    pSuite = CU_add_suite("Day__nextDay_test_suite", 0, 0);


    // Always check if add was successful
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Day__nextDay_test_suite", 0, 0);
    if (NULL == CU_add_test(pSuite, "Day__nextDay_test", Day__nextDay_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add a suite to the registry
    pSuite = CU_add_suite("Day__prevDay_test_suite", 0, 0);


    // Always check if add was successful
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Day__prevDay_test_suite", 0, 0);
    if (NULL == CU_add_test(pSuite, "Day__prevDay_test", Day__prevDay_test))
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


void Day__toStringf_test(enum Day day, char *check) {
    char *daystring;
    daystring = Day__toString(day);
    printf("Dzień: %s\n", daystring);
    printf("Check: %s\n", check);
    CU_ASSERT_NSTRING_EQUAL(daystring, check, strlen(check));
//    free(daystring);
}

void Day__nextDayf_test(enum Day day, int check){
    enum Day daynum;
    daynum = Day__nextDay(day);
    CU_ASSERT_EQUAL(daynum, check);

}

void Day__prevDayf_test(enum Day day, int check){
    enum Day daynum;
    daynum = Day__prevDay(day);
    CU_ASSERT_EQUAL(daynum, check);

}

//int Action__parsef_test(int argc, char **argv){
//
//    enum Action *actionset = parse(argc - 2, argv);
//
//    for (int i = 0; i < argc - 2; ++i) {
//        if (!strcmp(argv[i+2], "d-") && !(actionset[i] != 1)){
//            printf("Pars Test Failed\n");
//            return 1;
//        }
//        else if (!strcmp(argv[i+2], "d+") && !(actionset[i] != 2)) {
//            printf("Pars Test Failed\n");
//            return 1;
//        }
//        else if (!strcmp(argv[i+2], "t-") && !(actionset[i] != 3)) {
//            printf("Pars Test Failed\n");
//            return 1;
//        }
//        else if (!strcmp(argv[i+2], "t+") && !(actionset[i] != 4)) {
//            printf("Pars Test Failed\n");
//            return 1;
//        }
//    }
//
//
//
//}


//  gcc zadanie1_tests.c encryption.c -o zadanie1_tests -lcunit && ./zadanie1_tests
