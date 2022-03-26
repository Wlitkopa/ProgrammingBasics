
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>



int main(){

    srand48(time(NULL));

    int size;
    int *matrix;

    printf("Podaj rozmiar tablicy n na n: \n");
    scanf("%d", &size);
    printf("\n");

    matrix = (int*) malloc(size*size * sizeof(int));

    /*
    for (int i = 0; i < (size*size); ++i) {
        *(matrix + (i)*sizeof(int)) = (int) lrand48() % 10 + 1;
    }
    */

    for (int i = 0; i < size*size; ++i) {
        scanf("%d", matrix + i*sizeof (int));
    }

    printf("\n");

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d \t", *(matrix + (i*size + j)*sizeof (int)));
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < (size-1); ++i) {
        for (int j = (i+1); j < size; ++j) {
            if (*(matrix + (i*size + j)*sizeof(int)) != 0){
                printf("Ta macierz nie jest macierzą trójkątną dolną. \n");
                break;
            }
            else if ((i == (size - 2)) && (j == (size-1))){
                printf("To jest macierz trójkątna dolna. \n");
            }
        }
    }

    free(matrix);
    return 0;
}