#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


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
//        printf("|\n");
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


int test(){

    FILE *matrixA = fopen("macierzA.txt", "r");
    FILE *matrixB = fopen("macierzB.txt", "r");
    FILE *matrixC = fopen("macierzC.txt", "r");

    int rawA = rawamount(matrixA);
    int colA = colamount(matrixA);
    int rawB = rawamount(matrixB);
    int colB = colamount(matrixB);
    int rawC = rawamount(matrixC);
    int colC = colamount(matrixC);
    if (colA != rawB){
        printf("colA: %d  rawB: %d\n", colA, rawB);
        printf("Test nie powiódł się. Liczba kolumn macierzy A jest różna od liczby wierszy macierzy B\n");
        return 1;
    }


    int *a = (int*) malloc(rawA*colA*sizeof (int));
    int *b = (int*) malloc(rawB*colB*sizeof (int));
    int *c = (int*) malloc(rawC*colC*sizeof (int));


    FILE *matrix = fopen("macierzA.txt", "r");
    for (int i = 0; i < rawA*colA; ++i) {
        fscanf(matrix, "%d", &a[i]);
    }
    fclose(matrix);

    matrix = fopen("macierzB.txt", "r");
    for (int i = 0; i < rawB*colB; ++i) {
        fscanf(matrix, "%d", &b[i]);
    }
    fclose(matrix);

    matrix = fopen("macierzC.txt", "r");
    for (int i = 0; i < rawC*colC; ++i) {
        fscanf(matrix, "%d", &c[i]);
    }
    fclose(matrix);

    int com = colA;
    int sum = 0;

    for (int i = 0; i < rawA; ++i) {
        for (int j = 0; j < colB; ++j) {
            sum = 0;
            for (int k = 0; k < com; ++k) {
                sum += (a[i*colA+k])*(b[j+k*colB]);
            }
            if (sum != c[i*colB + j]){
                printf("Test się nie powiódł2. \n");
                printf("sum: %d   sumexp: %d \n", sum, c[i*colB + j]);
                free(a);
                free(b);
                free(c);
                return 1;
            }
        }
    }
    printf("Test się powiódł!\n");
    free(a);
    free(b);
    free(c);
    return 0;
}



int main(int argc, char **argv){



    if (argc != 4){
        printf("Składnia: mode min max \n");
        return 1;
    }

    int mode = atoi(argv[1]);


    int min = atoi(argv[2]);
    int max = atoi(argv[3]);
    if (max <= min){
        printf("Składnia: min max \n");
        return 1;
    }

    switch (mode){
        case 1:
            fill("macierzA.txt", "macierzB.txt", min, max);
            break;
        case 2:
            test();
            break;
        default:
            printf("mode: 1-fill  2-test\n");
    }


}