
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void printarray(int *arr, int len) {

    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void reverse(int len, int *arr) {
    int temp;
    for (int i = 0; i < floor(len / 2); ++i) {
        temp = arr[len - i - 1];
        arr[len - i - 1] = arr[i];
        arr[i] = temp;
    }
}

int partition(int p, int r, int *arr) {
    int x = arr[r];
    int i = p - 1;
    int temp;
    for (int k = p; k < r; ++k) {
        if (arr[k] <= x) {
            i++;
            temp = arr[i];
            arr[i] = arr[k];
            arr[k] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    i++;

    return i;
}


void quicksort(int p, int r, int *arr) {
    int q;
    if (p < r) {
        q = partition(p, r, arr);
        quicksort(p, q - 1, arr);
        quicksort(q + 1, r, arr);
    }
}


int one_two(int *arr1, const int len1, int *arr2, const int len2, int *arr3){

    int counter = 0;
    int ind1 = 0;
    int ind2 = 0;
    int ind3 = 0;

    for (int i = 0; i < (len1 + len2); ++i) {
        printf("ind1: %d \n", ind1);
        printf("ind2: %d \n", ind2);
        printf("arr1[ind1]: %d \n", arr1[ind1]);
        printf("arr2[ind2]: %d \n\n", arr2[ind2]);
        if (arr1[ind1] < arr2[ind2]){
            if (counter == 0) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
                if (ind1 != (len1-1)) {
                    ind1 += 1;
                }
                else if (ind2 != (len2-1)){
                    ind2 += 1;
                }
            }
            else if (arr3[ind3-1] < arr1[ind1]){
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
                if (ind1 != (len1-1)) {
                    ind1 += 1;
                }
                else if (ind2 != (len2-1)){
                    ind2 += 1;
                }
            }
            else{
                if (ind1 != (len1-1)) {
                    ind1 += 1;
                }
                else if (ind2 != (len2-1)){
                    ind2 += 1;
                }
            }

        }
        if (arr1[ind1] > arr2[ind2]){
            if (counter == 0) {
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
                if (ind2 != (len2-1)) {
                    ind2 += 1;
                }
                else if (ind1 != (len1-1)){
                    ind1 += 1;
                }
            }
            else if (arr3[ind3-1] < arr2[ind2]){
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
                if (ind2 != (len2-1)) {
                    ind2 += 1;
                }
                else if (ind1 != (len1-1)){
                    ind1 += 1;
                }
            }
            else{
                if (ind2 != (len2-1)) {
                    ind2 += 1;
                }
                else if (ind1 != (len1-1)){
                    ind1 += 1;
                }
            }

        }
        if (arr1[ind1] == arr2[ind2]){
            if (counter == 0) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
                if (ind1 != (len1-1)) {
                    ind1 += 1;
                }
                else if (ind2 != (len2-1)) {
                    ind2 += 1;
                }
            }
            else if (arr3[ind3-1] < arr1[ind1]){
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
                if (ind1 != (len1-1)) {
                    ind1 += 1;
                }
                else if (ind2 != (len2-1)) {
                    ind2 += 1;
                }
            }
            else {
                if (ind1 != (len1-1)) {
                    ind1 += 1;
                }
                else if (ind2 != (len2-1)) {
                    ind2 += 1;
                }
            }
        }
        if ((ind1 == (len1-1)) && (ind2 == (len2-1))){
            if ((arr1[ind1] > arr2[ind2]) && (arr1[ind1] > arr3[ind3-1])){
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
            }
            if ((arr1[ind1] < arr2[ind2]) && (arr2[ind2] > arr3[ind3-1])){
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
            }
        }
    }
    return counter;
}

void statistics(int *arr4, int len4){

    int it = 0;
    float stat;
    quicksort(0, len4 - 1, arr4);

    for (int i = 0; i < len4; ++i) {
        int counter = 1;
        for (int j = (it+1); j < len4; ++j) {
            if (arr4[j] == arr4[it]){
                counter += 1;
            }
        }
        stat = ((float)counter/(float)len4)*(100);
        if (it <= (len4-1)){
            printf("Element %d pojawia się w %f procent całej tablicy. \n", arr4[it], stat);
            it += counter;
        }

    }
}

int main() {

    int N1 = 15;
    int N2 = 15;
    int N4 = 15;
    int t1[N1];
    int t2[N2];
    int t4[N4];
    int t3[N1 + N2];

    srand48(time(NULL));

    for (int i = 0; i < N1; ++i) {
        t1[i] = (int) lrand48() % 10 + 1;
        t2[i] = (int) lrand48() % 10 + 1;
        t4[i] = ((int) lrand48() % 20 + 1) - 11;
    }

    printf("t1: ");
    for (int i = 0; i < N1; ++i) {
        printf("%d ", t1[i]);
    }
    printf("\n");

    reverse(N1, t1);
    printf("reversed t1: ");
    for (int i = 0; i < N1; ++i) {
        printf("%d ", t1[i]);
    }
    printf("\n");

    quicksort(0, N1 - 1, t1);
    printf("sorted t1: ");
    for (int i = 0; i < N1; ++i) {
        printf("%d ", t1[i]);
    }
    printf("\n");

    printf("t2: ");
    for (int i = 0; i < N2; ++i) {
        printf("%d ", t2[i]);
    }
    printf("\n");


    quicksort(0, N1 - 1, t1);
    quicksort(0, N2 - 1, t2);
    int result = one_two(t1, N1, t2, N2, t3);
    printf("Długość trzeciej tablicy to %d \n", result);
    printf("Trzecia tablica to: ");
    printarray(t3, result);
    printf("\n");


    statistics(t4, N4);
    printarray(t4, N4);

    return 0;
}

