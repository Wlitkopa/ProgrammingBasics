
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
const int r = 8;
const int c = 8;



void fillrandom(int arr1[r][c]){

    srand48(time(NULL));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < r; ++j) {
            arr1[i][j] = (int) lrand48() % 10 + 1;
        }
    }
}

void fill_with_zero(int arr1[r][c]){

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < r; ++j) {
            arr1[i][j] = 0;
        }
    }
}

void printarray(int arr1[r][c]){
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < r; ++j) {
            printf("%d \t", arr1[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void sum(int arr1[r][c]){

    int sum_diag = 0;
    int sum_col = 0;
    int sum_all = 0;

    for (int i = 0; i < r; ++i) {
        sum_diag += arr1[i][i];
    }
    printf("Suma elementów na przekątnej tablicy wynosi: %d \n", sum_diag);
    for (int i = 0; i < r; ++i) {
        sum_col = 0;
        for (int j = 0; j < r; ++j) {
            sum_col += arr1[j][i];
        }
        printf("Suma elementów w kolumnie %d wynosi: %d \n", (i+1), sum_col);
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < r; ++j) {
            sum_all += arr1[i][j];
        }
    }
    printf("Suma wszystkich elementów wynosi: %d \n", sum_all);
}

void multiply(int arr1[r][c], int arr2[r][c], int result[r][c]){

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < r; ++j) {
            for (int k = 0; k < r; ++k) {
                result[i][j] += (arr1[i][k]) * (arr2[k][j]);
                printf("result[%d][%d] to: %d \n", i, j, result[i][j]);
            }
        }
    }
    printarray(result);
}

int main(){

    int arr[8][8];
    int brr[8][8];
    int mult[8][8];

    fillrandom( arr);
    fillrandom( brr);
    fill_with_zero(mult);
    printarray(arr);
    printarray(brr);
    sum(arr);
    multiply(arr, brr, mult);

    return 0;
}
