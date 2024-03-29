#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "task3.h"

void Term__init(struct Term* term, int hour, int minute, int duration, enum Day day) {
    term->hour = hour;
    term->minute = minute;
    term->duration = duration;
    term->day = day;
}

struct Term* Term__create(int hour, int minute, int duration, enum Day day){
    struct Term *term1 = malloc(sizeof (struct Term));
    Term__init(term1, hour, minute, duration, day);
    return term1;
}

void TimeLimits__init(struct TimeLimits *timelimits, int minh, int maxh, int minm, int maxm){
    timelimits->min_hour = minh;
    timelimits->max_hour = maxh;
    timelimits->min_minutes = minm;
    timelimits->max_minutes = maxm;
}

struct TimeLimits* Set__TimeLimits(int minh, int maxh, int minm, int maxm){
    struct TimeLimits *timelimits = malloc(sizeof (struct TimeLimits));
    TimeLimits__init(timelimits, minh, maxh, minm, maxm);
    return timelimits;
}

char* Day__toString(enum Day day){

    char* stringday = (char*) malloc(15*sizeof (char));

    switch ((int)day){
        case 0:
            stringday =  "Poniedziałek";
            break;
        case 1:
            stringday =  "Wtorek";
            break;
        case 2:
            stringday =  "Środa";
            break;
        case 3:
            stringday =  "Czwartek";
            break;
        case 4:
            stringday =  "Piątek";
            break;
        case 5:
            stringday =  "Sobota";
            break;
        case 6:
            stringday =  "Niedziela";
            break;
        default:
            printf("Wybierz odpowiednią wartość dnia tygodnia\n");
    }


    return stringday;
}

struct Lesson* Lesson__create(int hour, int minute, int duration, enum Day day, char *subject){
    struct Lesson *lesson = malloc(sizeof (struct Lesson));
    lesson->subject = malloc(strlen(subject)*sizeof(*subject));
    strcpy(lesson->subject, subject);
    lesson->term = Term__create(hour, minute, duration, day);
    return lesson;
}

void Term__destroy(struct Term* term){
    free(term);
}

void Lesson__destroy(struct Lesson* lesson){
    free(lesson);
}

void Time__destroy(struct TimeLimits* timelimits){
    free(timelimits);
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

struct Term* Term__endTerm(struct Term* term1, struct Term *term2, enum Day day){

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

    struct Term *term3 = Term__create(term1->hour, term1->minute, difference, day);

    return term3;
}

void Lesson__earlierDay(struct Lesson* lesson){
    int curday = lesson->term->day;
    if (((curday+6)%7)<5){
        lesson->term->day = ((curday+6)%7);
    }
    else{
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(((curday+6)%7)), lesson->term->hour, lesson->term->minute);
    }
}

void Lesson__laterDay(struct Lesson* lesson){
    int curday = lesson->term->day;
    printf("Curday: %d\n", curday);
    printf("Curday + 1: %d\n", ((curday+1)%7));

    if (((curday+1)%7)<5){
        lesson->term->day = ((curday+1)%7);
        printf("lesson->term->day: %d\n", lesson->term->day);
        printf("Po dodaniu 1 dnia: %s\n", Day__toString(lesson->term->day));
    }
    else{
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(((curday+1)%7)), lesson->term->hour, lesson->term->minute);
    }
}

void Lesson__laterTime(struct Lesson* lesson, struct TimeLimits *timelimits, struct TimeLimits *timelimits2){
    int durhours = (lesson->term->duration - (lesson->term->duration%60))/60;
    int durminutes = lesson->term->duration%60;
    int newminutes = lesson->term->minute + durminutes;
    int newhours = ((newminutes - newminutes%60)/60) + durhours;
    newminutes = newminutes%60;
    int hourslimit = 0;
    int minuteslimit = 0;

    if (lesson->term->day == 4){

        if (timelimits2->max_minutes < durminutes){
            minuteslimit = 60 - (durminutes - timelimits2->max_minutes);
            hourslimit = timelimits2->max_hour - durhours - 1;
        }
        else{
            minuteslimit = timelimits2->max_minutes - durminutes;
            hourslimit = timelimits2->max_hour - durhours;
        }

        if (lesson->term->hour + newhours > hourslimit){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), lesson->term->hour + newhours, newminutes);
        }
        else if (lesson->term->hour + newhours == hourslimit && lesson->term->minute + newminutes > minuteslimit){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), lesson->term->hour + newhours, newminutes);
        }
        else {
            lesson->term->hour += newhours;
            lesson->term->minute = newminutes;
        }
    }

    if (lesson->term->day < 4){

        if (timelimits->max_minutes < durminutes){
            minuteslimit = 60 - (durminutes - timelimits->max_minutes);
            hourslimit = timelimits->max_hour - durhours - 1;
        }
        else{
            minuteslimit = timelimits->max_minutes - durminutes;
            hourslimit = timelimits->max_hour - durhours;
        }

        if (lesson->term->hour + newhours > hourslimit){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), lesson->term->hour + newhours, newminutes);
        }
        else if (lesson->term->hour + newhours == hourslimit && lesson->term->minute + newminutes> minuteslimit){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), lesson->term->hour + newhours, newminutes);
        }
        else {
            lesson->term->hour += newhours;
            lesson->term->minute = newminutes;
        }
    }
}

void Lesson__earlierTime(struct Lesson* lesson, struct TimeLimits *timelimits, struct TimeLimits *timelimits2){
    int durhours = (lesson->term->duration - (lesson->term->duration%60))/60;
    int durminutes = lesson->term->duration%60;
    int newhour = 0;
    int newminute = 0;

    if (lesson->term->minute < durminutes){
        newhour = lesson->term->hour - durhours - 1;
        newminute = 60 - (durminutes - lesson->term->minute);
    }
    else{
        newhour = lesson->term->hour - durhours;
        newminute = lesson->term->minute - durminutes;
    }

    if (lesson->term->day == 4){
        if (newhour < timelimits2->min_hour){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), newhour, newminute);
        }
        else if (newhour == timelimits2->min_hour && newminute < timelimits2->min_minutes){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), newhour, newminute);
        }
        else {
            lesson->term->hour = newhour;
            lesson->term->minute = newminute;
        }
    }
    else if (lesson->term->day < 4){
        if (newhour < timelimits->min_hour){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), newhour, newminute);
        }
        else if (newhour == timelimits->min_hour && newminute < timelimits->min_minutes){
            printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s, %d:%d\"\n", lesson->subject, Day__toString(lesson->term->day), newhour, newminute);
        }
        else {
            lesson->term->hour = newhour;
            lesson->term->minute = newminute;
        }

    }
}

char *Lesson__toString(struct Lesson* lesson){
    char *lekcja = (char*) malloc(70*sizeof (char));
    int ind = 0;

    for (int i = 0; i < strlen(lesson->subject); ++i) {
        lekcja[ind++] = lesson->subject[i];
    }
    lekcja[ind++] = ',';
    lekcja[ind++] = ' ';

    char *dayt = Day__toString(lesson->term->day);
    for (int i = 0; i < strlen(dayt); ++i) {
        lekcja[ind++] = dayt[i];
    }
    lekcja[ind++] = ' ';


    if (lesson->term->hour < 10){
        lekcja[ind++] = '0' + lesson->term->hour;
        lekcja[ind++] = ':';
    }
    else{
        lekcja[ind++] = '0' + (((lesson->term->hour)-(lesson->term->hour%10))/10);
        lekcja[ind++] = '0' + (lesson->term->hour%10);
        lekcja[ind++] = ':';
    }
    if (lesson->term->minute < 10){
        if (lesson->term->minute == 0){
            lekcja[ind++] = '0' + lesson->term->minute;
        }
        lekcja[ind++] = '0' + lesson->term->minute;
    }
    else{
        lekcja[ind++] = '0' + (((lesson->term->minute)-(lesson->term->minute%10))/10);
        lekcja[ind++] = '0' + (lesson->term->minute%10);
    }

    lekcja[ind++] = ' ';
    lekcja[ind++] = '[';

    int temp = lesson->term->duration;
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
        lekcja[ind++] = '0' + firstnum;
        temp = temp - firstnum*(int)pow((float)10, (float)power);
    }
    lekcja[ind++] = ']';

    return lekcja;

}
