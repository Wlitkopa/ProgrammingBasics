#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "helper.h"


void fill(char file1[100], char file2[100], int min, int max){

    FILE *matrixA = fopen(file1, "w");
    FILE *matrixB = fopen(file2, "w");


    srand48(time(NULL));
    int rawA = (rand()%(max-min)) + min;
    srand48(time(NULL));
    int colA = (rand()%(max-min)) + min;
    int rawB = colA;
    srand48(time(NULL));
    int colB = (rand()%(max-min)) + min;
    int randnum;


    for (int i = 0; i < rawA; ++i) {
        for (int j = 0; j < colA; ++j) {
            randnum = (int)lrand48() % 10;
            fprintf(matrixA, "%d\t", randnum);
        }
        if (i != rawA - 1){
            fprintf(matrixA, "\n");
        }
    }


    for (int i = 0; i < rawB; ++i) {
        for (int j = 0; j < colB; ++j) {
            randnum = (int)lrand48() % 10;
            fprintf(matrixB, "%d\t", randnum);
        }
        if (i != rawB - 1){
            fprintf(matrixB, "\n");
        }
    }


    fclose(matrixA);
    fclose(matrixB);

}