#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


void *Stack__create (int size){
    printf("Tworzę stos o rozmiarze %d\n", size);
    int *stack = (int*) malloc(size*sizeof (int));

    if (stack == NULL){
        fprintf(stderr, "Nie mogę utworzyć stosu o podanym rozmiarze");
        exit(EXIT_FAILURE); // https://en.cppreference.com/w/c/program/EXIT_status
    }
    for (int i = 0; i < size; ++i){
        stack[i] = (int)INFINITY;
    }


    return stack;
}


void *Stack__destroy (int *stack){

    if (stack == NULL){
        printf("Stos nie istnieje (destroy)\n");
    }
    else{
        free(stack);
    }
}


void Stack__push (int *stack, char number, int stacksize){

    if (stack == NULL){
        fprintf(stderr, "Stos nie istnieje (push)\n");
        exit(EXIT_FAILURE); // https://en.cppreference.com/w/c/program/EXIT_status
    }

    else{

//        int stacksize = sizeof (*stack)/sizeof (int);
//        printf("Stacksize: %d\n", stacksize);
        if (stack[stacksize - 1] != (int)INFINITY){
            printf("Rozmiar stosu jest przekroczony. Nie można wpisać nowej wartości \"%d\" na stos\n", number);
        }
        else{
            for (int i = 0; i < stacksize; ++i){
                if (stack[i] == (int)INFINITY){
                    stack[i] = number;
                    break;
                }
            }
        }
    }
}


int Stack__pop (int *stack, int stacksize){

    if (stack == NULL){
        fprintf(stderr, "Stos nie istnieje (pop)\n");
        exit(EXIT_FAILURE); // https://en.cppreference.com/w/c/program/EXIT_status
    }
    else{
//        int stacksize = sizeof (*stack)/sizeof (int);
        int popnumber;
        if (stack[0] == (int)INFINITY){
            fprintf(stderr, "Stos jest pusty (pop)\n");
            exit(EXIT_FAILURE); // https://en.cppreference.com/w/c/program/EXIT_status
        }
        else if (stack[stacksize - 1] != (int)INFINITY){
            popnumber = stack[stacksize-1];
            stack[stacksize-1] = (int)INFINITY;
            return popnumber;
        }
        else{
            for (int i = 0; i < stacksize; ++i){
                if (stack[i] == (int)INFINITY){
                    popnumber = stack[i-1];
                    stack[i-1] = (int)INFINITY;
                    break;
                }
            }
        }

        return popnumber;
    }
}


void Stack__print(int *stack, int stacksize) {

    if (stack == NULL){
        fprintf(stderr, "Stos nie istnieje (print)\n");
        exit(EXIT_FAILURE); // https://en.cppreference.com/w/c/program/EXIT_status
    }
    else {
        printf("\nWypisuję stos: \n");
//        int stacksize = sizeof (stack)/sizeof (int);
        for (int i = stacksize - 1; i >= 0; --i) {
            if (stack[i] != (int)INFINITY){
                printf("%d\n", stack[i]);
            }
        }
        printf("Skończyłem wypisywać stos\n\n");
    }
}




int main() {

    int *stack = NULL;

//    Stack__destroy(stack); // Wypisuje: "Stos nie istnieje"
//    Stack__push(stack, 3, stacksize); // Dodanie liczby 3 na stos
//    Stack__push(stack, 5, stacksize);
//    Stack__push(stack, 2, stacksize);
//    Stack__push(stack, 4, stacksize); // Przekraczamy rozmiar stosu — funkcja nie powinna na to pozwolić
//    Stack__print(stack, stacksize); // Funkcja powinna wypisać:
//    // 2
//    // 5
//    // 3
//    printf("%d\n", Stack__pop(stack, stacksize)); // Wypisuje 2
//    Stack__print(stack, stacksize); // Funkcja powinna wypisać:
//    // 5
//    // 3
//    printf("%d\n", Stack__pop(stack, stacksize)); // Wypisuje 5
//    printf("%d\n", Stack__pop(stack, stacksize)); // Wypisuje 3


    char *ciag_znakow = "\\\\xyz/2\\\\z///";
//    char *ciag_znakow = "\\xyz/";
//    char *ciag_znakow = "\\\\xyz//";

    int stacksize = strlen(ciag_znakow);
    char curchar;
    char nextchar;
    stack = Stack__create(stacksize); // Utworzenie stosu o rozmiarze strlen(ciag_znakow)
    int flag = 0;


    for (int i = 0; i < strlen(ciag_znakow); ++i) {

        Stack__push(stack, (int)ciag_znakow[i], stacksize);

    }

    printf("Stos: \n\n");
    Stack__print(stack, stacksize);
    printf("\n\n");
    int previous;
    int current;



    for (int i = 0; i < strlen(ciag_znakow); ++i) {
//        current = Stack__pop(stack, stacksize);
        if (stack[i] == '\\'){
//            Stack__push(stack, 1, stacksize);
            if (stack[i+1] == '\\' && i != (strlen(ciag_znakow)-1)){
                flag = 1;
            }

        }
        if (stack[i] == '/'){
//            Stack__pop(stack, stacksize);
            if (i != (strlen(ciag_znakow)-1) && stack[i+1] != '/'){
                flag = 0;
            }
        }
        else {
            Stack__pop(stack, stacksize);
        }

    }
    Stack__print(stack, stacksize);
    if (flag == 1){
        printf("Znaleziono zduplikowane \\/\n");
    }
    else{
        printf("Nie znaleziono zduplikowanych \\/\n");
    }






    int liczba = Stack__pop(stack, stacksize); // Próbujemy zdjąć wartość z pustego stosu  — funkcja nie powinna na to pozwolić — powinna zwrócić wartość specjalną, na przykład INT_MIN
    Stack__destroy(stack); // Likwidacja stosu
//    Stack__destroy(stack); // Wypisuje: "Stos nie istnieje"

    return 0;
}