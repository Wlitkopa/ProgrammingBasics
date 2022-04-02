
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


int main(){

    int size;
    int arr[size][size];
    int arr2[size*size];
    int counter;
    int onecounter = 0;
    int first[1][2];
    int second[1][2];
    int largest = 1;
    printf("Podaj rozmiar obszaru: \n");
    scanf("%d", &size);


    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d \t", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = i; k < size; ++k) {
                for (int l = j; l < size; ++l) {
                    if(arr[k][l] != 0){
                        printf("condition \n");
                        if((k - i + 1)*(l - j + 1) > largest){
                            largest = (k - i)*(l - j);
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("Najwięsze pole to: %d \n", largest);


    return 0;
}