
#define _XOPEN_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ulimit.h>

//long ulimit(int UL_SETSIZE, long );

#define dynamicnum 1000
#define staticnum 1000000

int main(int argc, char **argv){

//    long ulimit(int UL_SETSIZE, long );


    int rozmiar = atoi(argv[1]);

    double ***array1 = (double***)malloc(rozmiar * sizeof (double**));

    for (int i = 0; i < rozmiar; ++i) {
        array1[i] = (double**) malloc(rozmiar * sizeof(double*));
        for (int j = 0; j < rozmiar; ++j) {
            array1[i][j] = (double*) malloc(rozmiar * sizeof(double));
            for (int k = 0; k < rozmiar; ++k) {
                array1[i][j][k] = 0;
            }
        }
    }

    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            free(array1[i][j]);
        }
        free(array1[i]);
    }


    printf("Podany rozmiar: %s\n", argv[1]);
    char c = getchar();

}


