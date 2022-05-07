#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "task1.h"

enum Day {MON, TUE, WED, THU, FRI, SAT, SUN};

enum Action {DAY_EARLIER = 1, DAY_LATER = 2, TIME_EARLIER = 3, TIME_LATER = 4};

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

enum Day Day__nextDay(enum Day day){
    return (day + 1)%7;
}

enum Day Day__prevDay(enum Day day){
    return (day + 6)%7;
}

enum Action* parse(int rozmiarTablicy, char *tablica[]){

    enum Action *action = malloc(rozmiarTablicy*sizeof (*action));
    int j = 0;

    for (int i = 0; i < rozmiarTablicy; ++i) {
        if (!strcmp(tablica[i], "d-")){
            action[j++] = DAY_EARLIER;
//            printf("Przypisuję tutaj kota\n");
        }
        else if (!strcmp(tablica[i], "d+")){
            action[j++] = DAY_LATER;
        }
        else if (!strcmp(tablica[i], "t-")){
            action[j++] = TIME_EARLIER;
        }
        else if (!strcmp(tablica[i], "t+")){
            action[j++] = TIME_LATER;
        }

    }

    return action;
}