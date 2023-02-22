#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>


int main(int argc, char **argv) {

    if (argc != 2){
        printf("Podaj odpowiednią ilość argumentów: [program]   [liczba_wątków]\n");
    }

    int n = atoi(argv[1]);
    printf("num: %d\n", n);

    for (int i = 0; i < n; ++i) {
        char *newName = (char*) malloc(20*sizeof (char));
        strcpy(newName, "thread");
        char num[5];
        sprintf(num, "%d", (i + 1));
        printf("num[5]: %s\n", num);
        for (int j = 0; j < strlen(num); ++j) {
            newName[6 + j] = num[j];
        }
        printf("%s\n", newName);
    }






}