
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(){

    srand48(time(NULL));

    int* arrn;
    int** arrm;
    int n;
    int m;

    printf("Podaj liczbę wierszy i kolumn: \n");
    scanf("%d", &n);
    scanf("%d", &m);

    arrn = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        arrn + i = (int*) malloc(m * sizeof(int));

    }




    return 0;
}