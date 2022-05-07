#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "task2.h"


void Term__init(struct Term* term, int hour, int minute, int duration) {
    term->hour = hour;
    term->minute = minute;
    term->duration = duration;
}

struct Term* Term__create(int hour, int minute, int duration){
    struct Term *term1 = malloc(sizeof (struct Term));
    Term__init(term1, hour, minute, duration);
    return term1;
}

void Term__destroy(struct Term* term){
    free(term);
}

char* Term__toString(struct Term* term) {
    char *termin = malloc(50*sizeof (char));
    int ind = 0;

    if (term->hour < 10){
        termin[ind++] = '0' + term->hour;
        termin[ind++] = ':';
    }
    else{
        termin[ind++] = '0' + (((term->hour)-(term->hour%10))/10);
        termin[ind++] = '0' + (term->hour%10);
        termin[ind++] = ':';
    }
    if (term->minute < 10){
        if (term->minute == 0){
            termin[ind++] = '0' + term->minute;
        }
        termin[ind++] = '0' + term->minute;
    }
    else{
        termin[ind++] = '0' + (((term->minute)-(term->minute%10))/10);
        termin[ind++] = '0' + (term->minute%10);
    }

    termin[ind++] = ' ';
    termin[ind++] = '[';

    int temp = term->duration;
//    printf("temp: %d\n", temp);
    int numbers = (int)floor(log10((float)temp)) + 1;

    for (int i = 0; i < numbers; ++i) {
        int power = 0;
        if (temp != 0){
            power = (int)floor(log10((float)temp));
        }
//        printf("power: %d\n", power);
        int rest = temp % (int)(pow((float)10, (float)power));
//        printf("rest: %d\n", rest);
//        printf("temp - rest: %d\n", temp-rest);
        int firstnum = (temp - rest)/(int)pow((float)10, (float)power);
        termin[ind++] = '0' + firstnum;
        temp = temp - firstnum*(int)pow((float)10, (float)power);
    }
    termin[ind++] = ']';

    return termin;
}

bool Term__earlierThan(struct Term* term1, struct Term *term2){

    if ((60*term1->hour + term1->minute)<(60*term2->hour + term2->minute)){
        return true;
    }
    else {
        return false;
    }
}

bool Term__laterThan(struct Term* term1, struct Term *term2){

    if ((60*term1->hour + term1->minute)>(60*term2->hour + term2->minute)){
        return true;
    }
    else {
        return false;
    }
}

bool Term__equals(struct Term* term1, struct Term *term2){

    if (((60*term1->hour + term1->minute) == (60*term2->hour + term2->minute)) && (term1->duration == term2->duration)){
        return true;
    }
    else {
        return false;
    }
}

struct Term* Term__endTerm(struct Term* term1, struct Term *term2){

    int difference;
    int hours;
    int minutes;

    if (Term__earlierThan(term1, term2)){
        difference = (60*term2->hour + term2->minute) - (60*term1->hour + term1->minute);
        printf("difference: %d\n", difference);
        hours = (difference - (difference%60))/60;
        minutes = difference%60;
    }
    else{
        printf("term1 nie jest wcześniejszy niż term2\n");
        return NULL;
    }

    struct Term *term3 = Term__create(term1->hour, term1->minute, difference);

    return term3;
}
