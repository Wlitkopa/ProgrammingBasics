
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(){

    srand48(time(NULL));

    int** arrn;
    int* arrm;
    int n;
    int m;

    printf("Podaj liczbę wierszy i kolumn: \n");
    scanf("%d", &n);
    scanf("%d", &m);
    printf("\n\n");

    arrn = (int**) malloc(n * sizeof(int*));

    for (int i = 0; i < n; ++i) {
        arrn[i] = (int*) malloc(m * sizeof(int));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            *(arrn[i] + j*sizeof (int)) = (int) lrand48() % 10 + 1;
            printf("%d \t", *(arrn[i] + j*sizeof (int)));
        }
        printf("\n");
    }
    printf("\n");


    for (int i = 0; i < n; ++i) {
        free(arrn[i]);
    }
    free(arrn);
    arrn = NULL;

    return 0;
}