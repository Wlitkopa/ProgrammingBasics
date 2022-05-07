#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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

enum Day String__toDay(char *string){

    if(!strcmp(string,"Mon"))
        return MON;
    if(!strcmp(string,"Tue"))
        return TUE;
    if(!strcmp(string,"Wed"))
        return WED;
    if(!strcmp(string,"Thu"))
        return THU;
    if(!strcmp(string,"Fri"))
        return FRI;
    if(!strcmp(string,"Sat"))
        return SAT;
    if(!strcmp(string,"Sun"))
        return SUN;
}


int main(int argc, char **argv) {

    printf("%s\n", Day__toString(Day__nextDay(SUN)));
    printf("%s\n", Day__toString(Day__prevDay(SUN)));

    enum Action *actions = parse(argc, argv);
    printf("%d\n", actions[0]);
    enum Day userday = String__toDay(argv[1]);

    for (int i = 0; i < (argc-2); ++i) {
        if (actions[i] == 1){
            printf("Dzień w tył\n");
            userday = Day__prevDay(userday);
        }
        else if (actions[i] == 2){
            printf("Dzień w przód\n");
            userday = Day__nextDay(userday);
        }
        else if (actions[i] == 3){
            printf("Termin  w tył\n");
        }
        else if (actions[i] == 4){
            printf("Termin w przód\n");
        }
    }
    printf("%s\n", Day__toString(userday));

    return 0;
}