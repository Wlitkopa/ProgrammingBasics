
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define dynamicnum 100000000
#define staticnum 1000000

void statyczna(){

    printf("statyczna\n");
    double static_ints[staticnum];
    for (int i = 0; i < staticnum; ++i) {
        static_ints[i] = i;
    }
    char c = getchar();
}


void dynamiczna(){

    printf("dynamiczna\n");

    double *tablica = (double*)malloc(dynamicnum * sizeof (double));
    for (int i = 0; i < dynamicnum; ++i) {
        tablica[i] = i;
    }
    char c = getchar();
    free(tablica);

}


int main(int argc, char **argv){

    int pid_t = getpid();
    printf("pid is: %d\n", pid_t);

    statyczna();
    char c =  getchar();
    dynamiczna();
    char ch = getchar();


}