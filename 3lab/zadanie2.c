
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* getHexAscii(const char ch[]){
    char *val = (char*) malloc(1*sizeof (char*));
    *val = (char)((int)*ch);
    return val;
}

char** getData(void){

    char **first = (char**) malloc(3*sizeof (char*));
    char *buffer;
    int rtrn;
    size_t bufsize = 32;
    size_t chars;
    buffer = (char*)malloc(bufsize*sizeof(char));

    for (int i = 0; i < 3; ++i) {
        chars = getline(&buffer, &bufsize, stdin);
        first[i] = (char*) malloc(chars*sizeof (char));
        printf("Chars: %zu \nBuffer: %s\n", chars, buffer);
        if(chars == -1){
            first[i] = NULL;
        }
        else{
            first[i] = buffer;
            printf("buffer: %s \n", buffer);
        }
        printf("You've typed %s \n", first[i]);

    }
    for (int i = 0; i < 3; ++i) {
        printf("You've typed %s \n", first[i]);
    }
    for (int i = 0; i < 3; ++i) {
        free(first[i]);
    }
    free(first);

//    return first;

}


int main(){

    char choice[] = "%";
    int linecnt = 3;
    printf("Value of %s in ASCII is %d\n", choice, *getHexAscii(choice));
    getData();

}