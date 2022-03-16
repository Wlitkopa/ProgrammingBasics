
#include <stdio.h>
#include <time.h>
#include <complex.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(){

    float a;
    float b;
    float c;
    float delta;
    float sol1;
    float sol2;
    printf("Podaj współczynnik a: \n");
    scanf("%f", &a);
    printf("Podaj współczynnik b: \n");
    scanf("%f", &b);
    printf("Podaj współczynnik c: \n");
    scanf("%f", &c);

    delta = b*b - 4*a*c;
    if ((delta > 0) && (a != 0)) {
        sol1 = (-b + sqrtf((float)delta)/2*a);
        sol2 = (-b - sqrtf((float)delta)/2*a);
        printf("Pierwiastki równania to: %f oraz %f \n", sol1, sol2);
    }
    else if(delta == 0){
        sol1 = (-b/2*a);
        printf("Istnieje tylko jedno rozwiązanie: %f \n", sol1);
    }

    return 0;
}