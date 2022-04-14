
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* getHexAscii(const char ch[]){
    char *val = (char*) malloc(2*sizeof (char));
    *val = (char)((int)*ch);
    return val;
}


char** getData(int* len, int* largest){


    char **first = (char**) malloc(3*sizeof (char*));
    char *buffer = NULL;
    *len = 0;
    printf("len1: %d\n", *len);
    *largest = 0;

    size_t bufsize = 32;
    size_t chars;
    buffer = (char*)malloc(bufsize*sizeof(char));

    while (1) {
        chars = getline(&buffer, &bufsize, stdin);
        if ((int)chars > *largest){
            *largest = (int)chars;
        }
        printf("len: %d\n", *len);

        if (*len > 2){
            first = (char**) realloc(first, (*len + 1)*sizeof (char*));
        }
        if (buffer[chars - 1] != '\n')
            chars += 1;
        buffer[chars - 1] = 0;

        printf("Chars: %zu \nBuffer: %s\n", chars, buffer);

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
        printf("You've typed %s\n\n", first[*len]);
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
    printf("largest: %d\n", *largest);
    printf("len: %d\n", *len);
    char *comp = (char*) malloc((*len)*(*largest) * sizeof (char));
    int length;
    char ch;
    int p = 0;
    printf("start2\n\n");

    for (int i = 0; i < *len; ++i) {

        if (first[i] != NULL){
        length = (int)strlen(first[i]);
        int cnt = 1;


            for (int j = 0; j < length; ++j) {
//                printf("First[%d]: \n %s \n\n", i, first[i]);
//                printf("Careful: %c\n", first[i][j]);
                ch = first[i][j];
                if (first[i][j] == first[i][j+1]){
                    cnt += 1;
                }

                else{
                    if (ch == '(' || ch == ')' || ch == '%'){
                        printf("else if brackets or percentage\n");
                        comp[p++] = '%';
                        sprintf(&comp[p++], "%d", *(getHexAscii(&ch)));
                        sprintf(&comp[p++], "%d", (*(getHexAscii(&ch)))%10);

                        printf("Ascii: %d for char: %c\n", *(getHexAscii(&ch)), ch);
//                        comp[p++] = *getHexAscii(&ch);
                        comp[p++] = '(';
                        sprintf(&comp[p++], "%d", cnt);
//                        comp[p++] = (char)cnt;
                        comp[p++] = ')';
                    }
                    else{
                        if (cnt < 5){
                            for (int k = 0; k < cnt; ++k) {
                                comp[p++] = ch;
                            }
                        }
                        else{
                            sprintf(&comp[p++], "%c", ch);
//                            comp[p++] = ch;
                            comp[p++] = '(';
                            sprintf(&comp[p++], "%d", cnt);
//                            comp[p++] = (char)cnt;
                            comp[p++] = ')';
                        }
                    }
                    cnt = 1;
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
    char* amt = (char*) malloc((*largest)*sizeof (char));
    int k;
//    int amt; // amount of characters



    for (int i = 0; i < *len; ++i) {
        if (first[i] != NULL){

            for (int j = 0; j < strlen(first[i]); ++j) {

                if (first[i][j+1] != '%'){
                    decomp[p++] = first[i][j];
                }
                else if (first[i][j+1] == '('){
                    k = j+2;
                    while (first[i][k] != ')'){
                        amt[g++] = first[i][k];
                        cnt += 1;
                        k += 1;
                    }
                    for (int l = (k-1); l > 0; l--) {
                        amount += (int)(amt[l])*(10^cnt);
                    }
                    for (int l = 0; l < amount; ++l) {
                        decomp[p++] = first[i][j];
                    }
                }




            }


        }

    }


}


int main(){

    char choice[] = "%";
    printf("Value of %s in ASCII is %d\n", choice, *getHexAscii(choice));
    int *len = (int*) malloc(sizeof (int));
    int *largest = (int*) malloc(sizeof (int));
    char **tekst;
    char *compressed;
    tekst = getData(len, largest);
    compressed = compress(tekst, len, largest);
    printf("Finaly:\n%s", compressed);

    //    for (int i = 0; i < 3; ++i) {
    //        free(first[i]);
    //    }
    //    free(first);

}
