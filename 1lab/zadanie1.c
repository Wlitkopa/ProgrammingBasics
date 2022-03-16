
#include <stdio.h>
#include <time.h>
#include <complex.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(){

    int n;
    int tempn;
    int i = 1;
    int length = 0;
    int power;
    int intsum = 0;
    int lastdigit;
    int templength;
    printf("Podaj liczbę: ");
    scanf("%d", &n);
    length = (int)floorf(log10f((float)n)) + 1;
    printf("Liczba cyfr w n: %d \n", length);
    tempn = n;
    templength = length;
    while(templength > 0){
        lastdigit = tempn%10;
        printf("Last digit: %d \n", lastdigit);
        intsum = intsum + powf(lastdigit, length);
        printf("intsum: %d \n", intsum);
        tempn = tempn - lastdigit;
        tempn = tempn/10;
        printf("tempn: %d \n", tempn);
        templength--;
        i++;
    }
    if(intsum == n){
        printf("%d jest liczbą Armstronga \n", n);
    }
    else{
        printf("%d nie jest liczbą Armstronga \n", n);

    }


    return 0;
}