#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/file.h>
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
//
//    if (argc == 2){
//        FILE *file = fopen(argv[1], "r");
//
//        for (int i = 0; i < colamount(file); ++i) { //żeby czytało do końca pliku lista.txt wystarczy dać tutaj: while (!feof (file))
//
//            char *filename1 = (char*)malloc(30*sizeof (char));
//            char *filename2 = (char*)malloc(30*sizeof (char));
//            char *filename3 = (char*)malloc(30*sizeof (char));
//
//            fscanf(file, "%s", filename1);
//            fscanf(file, "%s", filename2);
//            fscanf(file, "%s", filename3);
//
//            printf("f1: %s\n", filename1);
//            printf("f2: %s\n", filename2);
//            printf("f3: %s\n", filename3);
//
//            fill(filename1, filename2, 3, 5);
//
//            FILE *matrixA = fopen(filename1, "r");
//            FILE *matrixB = fopen(filename2, "r");
//            FILE *matrixC = fopen(filename3, "w");
//
//
//            int numC = 0;
//            int rawA = rawamount(matrixA);
//            int colA = colamount(matrixA);
//            int rawB = rawamount(matrixB);
//            int colB = colamount(matrixB);
//            if (colA != rawB){
//                printf("colA: %d  rawB: %d\n", colA, rawB);
//                printf("Liczba kolumn macierzy A jest różna od liczby wierszy macierzy B\n");
//                return 1;
//            }
//            else{
//                printf("Działa! colA: %d  rawB: %d\n", colA, rawB);
//            }
//
//
//            int com = colA;
//
//            for (int i = 0; i < rawA; ++i) {
//                for (int j = 0; j < colB; ++j) {
//                    numC = 0;
//                    for (int k = 0; k < com; ++k) {
//                        numC += (getnum(matrixA, i*colA+k))*(getnum(matrixB, j+k*colB));
//                    }
//                    fprintf(matrixC, "%d\t", numC);
//
//                    printf("Printuję numC: %d\n", numC);
//                }
//                fprintf(matrixC, "\n");
//            }
//
//
//            fclose(matrixA);
//            fclose(matrixB);
//            fclose(matrixC);
//
//
//            free(filename1);
//            free(filename2);
//            free(filename3);
//
//        }
//
//        fclose(file);
//    }
    if (argc == 3){ //dodać flock'i

        FILE *file = fopen(argv[1], "r");

        for (int i = 0; i < 2; ++i) { //żeby czytało do końca pliku lista.txt wystarczy dać tutaj: while (!feof (file))
                                                    // https://www.ict.griffith.edu.au/teaching/2501ICT/archive/guide/ipc/flock.html

            char *filename1 = (char*)malloc(30*sizeof (char));
            char *filename2 = (char*)malloc(30*sizeof (char));
            char *filename3 = (char*)malloc(30*sizeof (char));

            fscanf(file, "%s", filename1);
            fscanf(file, "%s", filename2);
            fscanf(file, "%s", filename3);

            printf("f1: %s\n", filename1);
            printf("f2: %s\n", filename2);
            printf("f3: %s\n", filename3);

//            fill(filename1, filename2, 3, 5);

            FILE *matrixA = fopen(filename1, "r");
            flock(fileno(matrixA), LOCK_EX);
            FILE *matrixB = fopen(filename2, "r");
            flock(fileno(matrixB), LOCK_EX);
            FILE *matrixC = fopen(filename3, "a+");
            flock(fileno(matrixC), LOCK_EX);


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
//            int *processflag = (int*) malloc(1*sizeof (int));
            int com = colA;
            int oper;
            FILE *operation = fopen("operation.txt", "r+");
            fscanf(operation, "%d", &oper);

//    POMYSŁ Z FLAGĄ NIE JEST ZŁY, ALE TUTAJ JEST ŹLE ZAIMPLEMENTOWANY. FLAGA NIE POWINNA BYĆ ZMIENIONA DLA NASTĘPNEJ LINIJKI W PLIKU list.h
//    Może warto wykorzystać iterację pętli przechodzącej przez wszystkie linijki w pliku lista.txt?


            printf("midA: %d\n", midA);
            printf("midB: %d\n", midB);
            printf("argv[2][0]: %d\n", (int)argv[2][0]);



            if ((char)argv[2][0] == '2') {
                printf("Wszedłem2\n");
                for (int p = midA; p < rawA; ++p) {
                    fprintf(matrixC, "       ");
                    for (int j = midB; j < colB; ++j) {
                        numC = 0;
                        for (int k = 0; k < com; ++k) {
                            numC += (getnum(matrixA, p*colA+k))*(getnum(matrixB, j+k*colB));
                        }
                        fprintf(matrixC, "%d\t", numC);

                        printf("Printuję numC2: %d\n", numC);
                    }
                    fprintf(matrixC, "\n");
                }
            }

            if ((char)argv[2][0] == '1'){
                printf("Wszedłem1\n");

                for (int p = 0; p < midA; ++p) {
                    for (int j = 0; j < midB; ++j) {
                        numC = 0;
                        for (int k = 0; k < com; ++k) {
                            numC += (getnum(matrixA, p*colA+k))*(getnum(matrixB, j+k*colB));
                        }
                        fprintf(matrixC, "%d\t", numC);

                        printf("Printuję numC1: %d\n", numC);
                    }
                    fprintf(matrixC, "\n");
                }
//                *processflag = 2;
            }


            printf("Finished writing\n");
            flock(fileno(matrixA), LOCK_UN);
            fclose(matrixA);
            flock(fileno(matrixB), LOCK_UN);
            fclose(matrixB);
            flock(fileno(matrixC), LOCK_UN);
            fclose(matrixC);


            free(filename1);
            free(filename2);
            free(filename3);

//            if (*processflag == 2){
//                free(processflag);
//            }

        }

        fclose(file);

    }


    return 0;
}