#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "helper.h"


int getnum(FILE *file, int ind){
    int a;
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i <= ind; ++i) {
        fscanf(file, "%d", &a);
    }

    return a;
}


int colamount(FILE *file){

    int cnt = 0;
    char cur;
    char prevcur;
    fseek(file, 0, SEEK_SET);
    cur = (char)fgetc(file);
    while(cur != '\n') {
        prevcur = cur;
        cur = (char)fgetc(file);
//        printf("prevcur: %c  cur: %c", prevcur, cur);
        if (isspace((int)cur) && !isspace((int)prevcur)){
//            printf("cnt += 1\n");
            cnt += 1;
        }
    }
    return cnt;
}


int rawamount(FILE *file){
    int cnt = 0;
    char cur;
    fseek(file, 0, SEEK_SET);
    while (!feof (file)){
        cur = (char)fgetc(file);
//        printf("%c\n", cur);
        if (cur == '\n'){
            cnt += 1;
        }
    }
    cnt += 1;

    return cnt;
}


int main(int argc, char **argv){

    if (argc == 2){
        FILE *file = fopen(argv[1], "r");

        for (int i = 0; i < colamount(file); ++i) { //żeby czytało do końca pliku lista.txt wystarczy dać tutaj: while (!feof (file))

            char *filename1 = (char*)malloc(30*sizeof (char));
            char *filename2 = (char*)malloc(30*sizeof (char));
            char *filename3 = (char*)malloc(30*sizeof (char));

            fscanf(file, "%s", filename1);
            fscanf(file, "%s", filename2);
            fscanf(file, "%s", filename3);

            printf("f1: %s\n", filename1);
            printf("f2: %s\n", filename2);
            printf("f3: %s\n", filename3);

            fill(filename1, filename2, 3, 5);

            FILE *matrixA = fopen(filename1, "r");
            FILE *matrixB = fopen(filename2, "r");
            FILE *matrixC = fopen(filename3, "w");


            int numC = 0;
            int rawA = rawamount(matrixA);
            int colA = colamount(matrixA);
            int rawB = rawamount(matrixB);
            int colB = colamount(matrixB);
            if (colA != rawB){
                printf("colA: %d  rawB: %d\n", colA, rawB);
                printf("Liczba kolumn macierzy A jest różna od liczby wierszy macierzy B\n");
                return 1;
            }
            else{
                printf("Działa! colA: %d  rawB: %d\n", colA, rawB);
            }


            int com = colA;

            for (int i = 0; i < rawA; ++i) {
                for (int j = 0; j < colB; ++j) {
                    numC = 0;
                    for (int k = 0; k < com; ++k) {
                        numC += (getnum(matrixA, i*colA+k))*(getnum(matrixB, j+k*colB));
                    }
                    fprintf(matrixC, "%d\t", numC);

                    printf("Printuję numC: %d\n", numC);
                }
                fprintf(matrixC, "\n");
            }


            fclose(matrixA);
            fclose(matrixB);
            fclose(matrixC);


            free(filename1);
            free(filename2);
            free(filename3);

        }

        fclose(file);
    }
    if (argc == 6){ //dodać flock'i

        FILE *file = fopen(argv[1], "r");

        for (int i = 0; i < colamount(file); ++i) { //żeby czytało do końca pliku lista.txt wystarczy dać tutaj: while (!feof (file))

            char *filename1 = (char*)malloc(30*sizeof (char));
            char *filename2 = (char*)malloc(30*sizeof (char));
            char *filename3 = (char*)malloc(30*sizeof (char));

            fscanf(file, "%s", filename1);
            fscanf(file, "%s", filename2);
            fscanf(file, "%s", filename3);

            printf("f1: %s\n", filename1);
            printf("f2: %s\n", filename2);
            printf("f3: %s\n", filename3);

            fill(filename1, filename2, 3, 5);

            FILE *matrixA = fopen(filename1, "r");
            FILE *matrixB = fopen(filename2, "r");
            FILE *matrixC = fopen(filename3, "w");


            int numC = 0;
            int rawA = rawamount(matrixA);
            int colA = colamount(matrixA);
            int rawB = rawamount(matrixB);
            int colB = colamount(matrixB);
            if (colA != rawB){
                printf("colA: %d  rawB: %d\n", colA, rawB);
                printf("Liczba kolumn macierzy A jest różna od liczby wierszy macierzy B\n");
                return 1;
            }
            else{
                printf("Działa! colA: %d  rawB: %d\n", colA, rawB);
            }
            if (rawA != colB){
                printf("rawA: %d  colB: %d\n", rawA, colB);
                printf("Liczba wierszy macierzy A jest różna od liczby kolumn macierzy B\n");
                return 1;
            }
            else{
                printf("Działa! rawA: %d  colB: %d\n", rawA, colB);
            }


            int midA = floor(rawA/2);
            int midB = floor(colB/2);
            int *processflag = (int*) malloc(1*sizeof (int));
            int com = colA;

//    POMYSŁ Z FLAGĄ NIE JEST ZŁY, ALE TUTAJ JEST ŹLE ZAIMPLEMENTOWANY. FLAGA NIE POWINNA BYĆ ZMIENIONA DLA NASTĘPNEJ LINIJKI W PLIKU list.h
            if (*processflag == 1){
                for (int p = 0; p < midA; ++p) {
                    for (int j = 0; j < midB; ++j) {
                        numC = 0;
                        for (int k = 0; k < com; ++k) {
                            numC += (getnum(matrixA, p*colA+k))*(getnum(matrixB, j+k*colB));
                        }
                        fprintf(matrixC, "%d\t", numC);

                        printf("Printuję numC: %d\n", numC);
                    }
                    fprintf(matrixC, "\n");
                }
//                *processflag = 2;
            }
            else {
                for (int p = midA; p < rawA; ++p) {
                    for (int j = midB; j < colB; ++j) {
                        numC = 0;
                        for (int k = 0; k < com; ++k) {
                            numC += (getnum(matrixA, p*colA+k))*(getnum(matrixB, j+k*colB));
                        }
                        fprintf(matrixC, "%d\t", numC);

                        printf("Printuję numC: %d\n", numC);
                    }
                    fprintf(matrixC, "\n");
                }
                *processflag = 2;
            }



            fclose(matrixA);
            fclose(matrixB);
            fclose(matrixC);


            free(filename1);
            free(filename2);
            free(filename3);
            if (*processflag == 2){
                free(processflag);
            }

        }

        fclose(file);

    }


    return 0;
}