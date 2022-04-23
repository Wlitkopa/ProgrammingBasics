
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "task2.h"

char* getHexAscii(const char ch[]) {
//    char *val = (char*) malloc(2*sizeof (char));
    char *hexval = (char *) malloc(5 * sizeof(char));
    int dec = (int) *ch;
    int quotient;
    int remainder;
    int hexinnum;
    char znak;
    int j = 0;
//    *val = (char)((int)*ch);
    quotient = dec;

    while (quotient != 0) {
        remainder = quotient % 16;

        if (remainder < 10) {
            znak = 48 + remainder;
            hexval[j++] = znak;

        }
        else {
            znak = 55 + remainder;
            hexval[j++] = znak;
        }
        quotient = quotient / 16;
    }


    return hexval;
}


char** getData(int* len, int* largest){


    char **first = (char**) malloc(3*sizeof (char*));
    char *buffer = NULL;
    *len = 0;
//    printf("len1: %d\n", *len);
    *largest = 0;

    size_t bufsize = 32;
    size_t chars;
    buffer = (char*)malloc(bufsize*sizeof(char));

    while (1) {
        chars = getline(&buffer, &bufsize, stdin);
//        printf("Chars: %zu\n", chars);
        if ((int)chars > *largest){
            *largest = (int)chars;
        }
//        printf("len: %d\n", *len);

        if (*len > 2){
            first = (char**) realloc(first, (*len + 1)*sizeof (char*));
        }
        if (buffer[chars - 1] != '\n')
            chars += 1;
        buffer[chars - 1] = 0;

//        printf("Chars: %zu \nBuffer: %s\n", chars, buffer);

        if ((chars == -1) || (strlen(buffer) == 0)){
            first[*len] = NULL;
            printf("NULL has beed added\n\n");
            if (*len >= 3){
                break;
            }
        }
        else{
            first[*len] = (char*) malloc(chars*sizeof (char));

            memcpy(first[*len], buffer, chars * sizeof(char));
        }
//        printf("You've typed %s\n\n", first[*len]);
        *(len) += 1;

    }
    for (int i = 0; i < *len; ++i) {
        if (first[i] != NULL){
            printf("You've typed: %s\n", first[i]);
            printf("strlen: %d\n\n", (int)strlen(first[i]));
        }
    }
    printf("exit\n");

    return first;

}


char* compress(char** first, const int* len, const int* largest){

    printf("start1\n");
//    printf("largest: %d\n", *largest);
    printf("len: %d\n", *len);
    char *comp = (char*) malloc((*len)*(*largest) * sizeof (char));
    int length;
    char ch;
    int p = 0;
    printf("start2\n\n");

    for (int i = 0; i < *len; ++i) {

        if (first[i] != NULL){
            length = (int)strlen(first[i]);
            int* cnt = (int*)malloc(3*sizeof (int));
            *cnt = 1;

            for (int j = 0; j < length; ++j) {
//                printf("First[%d]: \n %s \n\n", i, first[i]);
//                printf("Careful: %c\n", first[i][j]);
                ch = first[i][j];
                if (first[i][j] == first[i][j+1]){
                    *cnt += 1;
                }

                else{
                    if (ch == '(' || ch == ')' || ch == '%'){
                        printf("else if brackets or percentage\n");
                        comp[p++] = '%';
                        char* hex = getHexAscii(&ch);
                        sprintf(&comp[p++], "%c", *(hex + 1));
                        sprintf(&comp[p++], "%c", *(hex));
                        free(hex);

//                        printf("Ascii: %d for char: %c\n", *(getHexAscii(&ch)), ch);
//                        comp[p++] = *getHexAscii(&ch);
                        comp[p++] = '(';
                        sprintf(&comp[p++], "%d", *cnt);
//                        comp[p++] = (char)cnt;
                        comp[p++] = ')';
                    }
                    else{
                        if (*cnt < 5){
                            for (int k = 0; k < *cnt; ++k) {
                                comp[p++] = ch;
                            }
                        }
                        else{
                            sprintf(&comp[p++], "%c", ch);
//                            comp[p++] = ch;
                            comp[p++] = '(';
                            if (*cnt > 9){
                                printf("cnt: %d\n", *cnt);
                                sprintf(&comp[p++], "%d", (*cnt-(*cnt%10))/10);
                                sprintf(&comp[p++], "%d", *cnt%10);
                            }
                            else{
                                sprintf(&comp[p++], "%d", *cnt);

                            }
//                            comp[p++] = (char)cnt;
                            comp[p++] = ')';
                        }
                    }
                    *cnt = 1;
                }

            }
            comp[p++] = '\n';

        }

    }

    return comp;

}


char* decompress(char** first, const int* len, const int* largest){

    char* decomp = (char*)malloc((*largest)*(*len)*sizeof (char));
    int p = 0;
    int g = 0;
    int amount = 0;
    int cnt = 0;
    int k;
    int ind = 0;
    int ascii = 0;
//    int amt; // amount of characters

    for (int i = 0; i < *len; ++i) {
        if (first[i] != NULL){
            int j = 0;

            while (j < strlen(first[i])) {
                char* amt = (char*) malloc((*largest)*sizeof (char));
                printf("first[%d][%d]: %c\n", i, j, first[i][j]);

                if (first[i][j] != '%' && first[i][j+1] != '('){
                    decomp[p++] = first[i][j];
                    printf("dodaję 1 do j\n");
                    j += 1;
                }

                else if (first[i][j+1] == '('){
//                    printf("działa else\n");

                    k = j+2;
                    while (first[i][k] != ')'){
                        amt[g++] = first[i][k];
                        cnt += 1;
                        printf("cnt: %d\n", cnt);
                        k += 1;
                    }
                    for (int l = 0; l < cnt; ++l) {
                        printf("amt: %c\n", amt[l]);
                    }
                    int temp = cnt;
                    int exponent = cnt;
                    for (int l = 0; l < temp; l++) {
                        int temp2 = (int)amt[l] - 48;
                        int power = (int)pow(10, (exponent-1));
                        amount += temp2*power;
                        exponent -= 1;
                        printf("amount: %d\n", amount);
                        printf("power %d and temp2 %d\n", power, temp2);
                    }
                    for (int l = 0; l < amount; ++l) {
                        decomp[p++] = first[i][j];
                        printf("działa (\n");
                        printf("first[%d][%d]: %c\n", i, j, first[i][j]);
                    }
                    j += 3 + cnt;
                    if (first[i][k+1] == '\n'){
                        break;
                    }
                    cnt = 0;
                    amount = 0;
                    g = 0;
                }

                else if (first[i][j] == '%'){
                    printf("działa else2\n");
                    k = j+4;

//                    printf("first[%d][%d]: %c\n", i, j, first[i][j]);
//                    printf("first[%d][%d]: %c\n", i, j+1, first[i][j+1]);
//                    printf("first[%d][%d]: %c\n", i, j+2, first[i][j+2]);
//                    printf("first[%d][%d]: %c\n", i, j+3, first[i][j+3]);
//                    printf("first[%d][%d]: %c\n", i, j+4, first[i][j+4]);
//                    printf("first[%d][%d]: %c\n", i, j+5, first[i][j+5]);
//                    printf("first[%d][%d]: %c\n", i, j+6, first[i][j+6]);



                    while (first[i][k] != ')'){
                        amt[g++] = first[i][k];
                        cnt += 1;
                        k += 1;
                    }


                    for (int l = 0; l < cnt; ++l) {
                        printf("amt: %c\n", amt[l]);
                    }
                    printf("cnt2: %d\n", cnt);

                    int temp = cnt;
                    int exponent = cnt;
                    printf("temp: %d\n", temp);
                    for (int l = 0; l < temp; l++) {
                        int temp2 = (int)amt[l] - 48;
                        printf("temp2: %d\n", temp2);
                        printf("temp: %d\n", temp);
                        int power = (int)pow(10, (exponent-1));
                        amount += temp2*power;
                        printf("amount2: %d\n", amount);
                        exponent -= 1;
                    }


                    if (first[i][j+2] == '5'){
                        for (int l = 0; l < amount; ++l) {
                            decomp[p++] = '%';
                        }
                    }
                    if (first[i][j+2] == '8'){
                        for (int l = 0; l < amount; ++l) {
                            decomp[p++] = '(';
                        }
                    }
                    if (first[i][j+2] == '9'){
                        for (int l = 0; l < amount; ++l) {
                            decomp[p++] = ')';
                        }
                    }
                    j += 5 + cnt;
                    cnt = 0;
                    amount = 0;
                    g = 0;

                }

                free(amt);
                printf("j: %d\n", j);

            }
            decomp[p++] = '\n';


        }

    }

    return decomp;
}