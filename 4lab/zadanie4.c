#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


int main(){

    FILE *file = fopen("task41.txt", "r");

    fseek(file, 0, SEEK_SET);
//    int ind2 = 0;
//
//
//    while ((char)getc(file) != '\n'){
//        ind2 += 1;
//        if (){
//
//
//        }
//
//
//    }







    int jus = 13;
    size_t bufsize = 1000;
    size_t chars;
    char *fileline;
    fileline = (char*)malloc(bufsize*sizeof(char));
    int *charnum = (int*)malloc(100*sizeof (int));

    chars = getline(&fileline, &bufsize, file);
    printf("fileline: %s\n", fileline);
    printf("strlen: %lu\n", strlen(fileline));

    int wordnum = 0;
    int ind = 0;
    int charsum = 0;
    int charsum2 = 0;
    int boundary = 0;
    char *word = (char*)malloc(100*sizeof(char));
    int space = 0;

    for (int i = 0; i < strlen(fileline); ++i) {
        ind += 1;
        if (*(fileline + i) == ' ' && *(fileline + i - 1) != ' '){
            space = i;
            printf("Działa1\n");
            wordnum += 1;
            printf("ind: %d\n", ind);
            charsum2 += ind - 1;
            charsum2 = 0;
        }
        if (charsum2 > jus){
            for (int j = 0; j < (jus-space); ++j) {
                printf(" ");
            }
            for (int j = 0; j < space; ++j) {
                printf("%c", fileline[j]);
            }
            printf("\n");
        }
    }
    printf("charnum: %d\n", *charnum);
    wordnum += 1;
    fseek(file, 0, SEEK_SET);


//    for (int i = 0; i < wordnum; ++i) {
//
//        if (charsum < jus){
//            printf("if działa\n");
//            charsum += charnum[i];
//            if (charsum >= 13){
//                boundary = i - 1;
//                for (int j = 0; j < boundary; ++j) {
//                    fscanf(file, "%s", word);
//                    for (int k = 0; k < (charsum - jus); ++k) {
//                        printf(" ");
//                    }
//                    printf("%s", word);
//                }
//                printf("\n");
//            }
//        }
//
//
//    }
    fclose(file);
    free(charnum);
    free(word);
    free(fileline);


    return 0;

}