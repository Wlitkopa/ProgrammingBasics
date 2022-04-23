#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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
        printf("prevcur: %c  cur: %c", prevcur, cur);
        printf("|\n");
        if (isspace((int)cur) && !isspace((int)prevcur)){
            printf("cnt += 1\n");
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
        printf("%c\n", cur);
        if (cur == '\n'){
            cnt += 1;
        }
    }
    cnt += 1;

    return cnt;
}


int main(int argc, char **argv){

    if (argc != 4){
        printf("Składnia: macierzA.txt macierzB.txt macierzC.txt \n");
        return 1;
    }
    
    FILE *matrixA = fopen(argv[1], "r");
    FILE *matrixB = fopen(argv[2], "r");
    FILE *matrixC = fopen(argv[3], "w");


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
    return 1;
}