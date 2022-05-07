#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "task3.h"


void Lesson__toString_tests(){
    struct Lesson *lesson1 = Lesson__create(12, 40, 90, THU, "Matematyka dyskretna");
    CU_ASSERT_STRING_EQUAL(Lesson__toString(lesson1), "Matematyka dyskretna, Czwartek 12:40 [90]");
    Lesson__destroy(lesson1);
}

void Lesson__dayChanges_tests(){
    struct Lesson *lesson1 = Lesson__create(12, 40, 90, THU, "Algebra");
    struct Lesson *lesson2 = Lesson__create(12, 40, 90, THU, "Analiza");

    Lesson__earlierDay(lesson1);
    CU_ASSERT_EQUAL(lesson1->term->day, 2); // Przed czwartkiem jest środa :)
    Lesson__earlierDay(lesson1);
    Lesson__earlierDay(lesson1);
    Lesson__earlierDay(lesson1);
    CU_ASSERT_EQUAL(lesson1->term->day, 0); // Jeżeli funkcja działa poprawnie, to nie przesunie dnia zajęć na niedzielę tylko zostanie przy poniedziałku


    Lesson__laterDay(lesson2);
    CU_ASSERT_EQUAL(lesson2->term->day, 4);
    Lesson__laterDay(lesson2);
    CU_ASSERT_EQUAL(lesson2->term->day, 4); // Jeżeli funkcja działa poprawnie, to nie przesunie dnia zajęć na sobotę tylko zostanie przy piątku


    Lesson__destroy(lesson1);
    Lesson__destroy(lesson2);
}

void Lesson__termChanges_test(){
    struct Lesson *lesson1 = Lesson__create(9, 50, 90, WED, "Algebra");
    struct Lesson *lesson2 = Lesson__create(16, 15, 90, THU, "Analiza");
    struct Lesson *lesson3 = Lesson__create(13, 10, 90, FRI, "Podstawy programowania");
    struct TimeLimits *timelimits1 = Set__TimeLimits(8, 20, 0, 0);
    struct TimeLimits *timelimits2 = Set__TimeLimits(8, 17, 0, 0);


    Lesson__earlierTime(lesson1, timelimits1, timelimits2);
    CU_ASSERT_EQUAL(lesson1->term->hour, 8);
    CU_ASSERT_EQUAL(lesson1->term->minute, 20);
    Lesson__earlierTime(lesson1, timelimits1, timelimits2);
    CU_ASSERT_EQUAL(lesson1->term->hour, 8);
    CU_ASSERT_EQUAL(lesson1->term->minute, 20); // Funkcja nie może zmienić godzin zajęć na wcześniejsze niż 8:00 zatem powinna zostac przy godzinie 8:20


    Lesson__laterTime(lesson2, timelimits1, timelimits2);
    CU_ASSERT_EQUAL(lesson2->term->hour, 17);
    CU_ASSERT_EQUAL(lesson2->term->minute, 45);
    Lesson__laterTime(lesson2, timelimits1, timelimits2);
    CU_ASSERT_EQUAL(lesson2->term->hour, 17);
    CU_ASSERT_EQUAL(lesson2->term->minute, 45); // Zajęcia nie mogą zaczynać się o 19:15 bo skończyłyby się po 20:00 zatem funkcja powinna zostac przy 17:45


    Lesson__laterTime(lesson3, timelimits1, timelimits2);
    CU_ASSERT_EQUAL(lesson3->term->hour, 14);
    CU_ASSERT_EQUAL(lesson3->term->minute, 40);
    Lesson__laterTime(lesson3, timelimits1, timelimits2);
    CU_ASSERT_EQUAL(lesson3->term->hour, 14);
    CU_ASSERT_EQUAL(lesson3->term->minute, 40); // Zajęcia nie mogą zaczynać się o 16:10 bo skończyłyby się po 17:00 zatem funkcja powinna zostac przy 14:40


    Lesson__destroy(lesson1);
    Lesson__destroy(lesson2);
    Lesson__destroy(lesson3);
    Time__destroy(timelimits1);
    Time__destroy(timelimits2);

}


int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Lesson__toString_tests", 0, 0);

    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "Lesson__toString_tests", Lesson__toString_tests)) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    pSuite = CU_add_suite("Lesson__dayChanges_tests", 0, 0);

    if (NULL == CU_add_test(pSuite, "Lesson__dayChanges_tests", Lesson__dayChanges_tests))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    pSuite = CU_add_suite("Lesson__termChanges_test", 0, 0);

    if (NULL == CU_add_test(pSuite, "Lesson__termChanges_test", Lesson__termChanges_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    return CU_get_error();

    return 0;
}