#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>


void *line_by_line(void* line){

    FILE *balloons = fopen("balloons.ascii.pgm", "r");
    FILE *negative = fopen("output.ascii.pgm", "r+");

}


int list_to_number(char list[3], int cnt){
    int ind = cnt - 1;
    int result = 0;

    for (int i = 0; i < 3; ++i) {
//        printf("list[%d]: %c\n", i, list[i]);
        result += (list[i] - '0')* pow(10, ind);
//        printf("result: %d\n", result);
        ind -= 1;
    }
    return result;
}

void fill_with_zero(char list[3]){
    for (int i = 0; i < 3; ++i) {
        list[i] = 0;
    }
}

char* int_to_char(int numb){

    int integers = ceil(log10(numb));
    int ind = 0;
    char list3[integers];

    for (int i = 0; i < integers; ++i) {



    }

}


int main(int argc, char **argv){

    FILE *ballons = fopen("balloons.ascii.pgm", "r");
    FILE *negative = fopen("output.ascii.pgm", "wb+");
//    FILE *ballons = fopen("coins.ascii.pgm", "r");
//    FILE *negative = fopen("output2.ascii.pgm", "wb+");

    char cur;
    int n = 0;
    int m = 0;
    int cnt = 0;
    int ind = 0;
    char list[6];
    char list2[3];

    for (int i = 0; i < 6; ++i) {
        list[i] = 0;
    }

    fseek(ballons, 0, SEEK_SET);
    while (cnt < 2){
        cur = (char)fgetc(ballons);
        printf("%c", cur);
        fprintf(negative, "%c", cur);
        if (cur == '\n'){
            cnt += 1;
        }
    }
    cur = 'z';
    while (cur != '\n'){
        cur = (char)fgetc(ballons);
        printf("%c", cur);
        fprintf(negative, "%c", cur);

        if (!isspace((int)cur)){
            list[ind] = cur;
            ind += 1;
        }
    }

    ind = 2;
    for (int i = 0; i < 6; ++i) {
        if (i < 3){
            n += (list[i]-'0')*pow(10,ind);
            ind -= 1;
        }
        else{
            if (ind == -1){
                ind = 2;
            }
            m += (list[i]-'0')*pow(10, ind);
            ind -= 1;
        }
    }

    printf("m (high): %d\n", m);
    printf("n (wide): %d\n", n);

    cur = 'z';

    while (cur != '\n'){
        cur = (char)fgetc(ballons);
        printf("%c", cur);
        fprintf(negative, "%c", cur);
    }
//    cur = (char)fgetc(ballons);
//    printf("now: %c", cur);
//    fprintf(negative, "%c", cur);

    int c;
    int cnt2 = 0;
    int cur_numb;
    int new_numb;
    int integers;
    int cur_int;
    int ind2;
    char prev;

    cnt = 0;
    ind = 0;
    fill_with_zero(list2);
//    while (c = fgetc(ballons), c != EOF)
//    for (int i = 0; i < 150; ++i)
//    327462

    while (cnt < n*m){
//        printf("================\n");
        cur = (char)fgetc(ballons);
//        printf("cur: %c\n", cur);
//        printf("================\n");
//        printf("\n================\n");


        if (!isspace((int)cur)){
            list2[ind] = cur;
            cnt2 += 1;
//            printf("Po wpisaniu do listy: %c\n", cur);
            ind += 1;
        }
        else if (!isspace((int)prev)){

            ind = 0;
            cur_numb = list_to_number(list2, cnt2);
//            printf("\ncur_numb: %d\n", cur_numb);
            new_numb = 255 - cur_numb;
//            printf("new_numb: %d\n", new_numb);
            integers = floor(log10(new_numb)) + 1;
            ind2 = integers - 1;
            for (int j = 0; j < integers; ++j) {
                cur_int = (new_numb - (new_numb % (int)(pow(10, ind2))))/(int)(pow(10, ind2));
                printf("%c", cur_int + '0');
                fprintf(negative, "%c", cur_int + '0');
                new_numb -= cur_int*pow(10, ind2);
                ind2 -= 1;
            }
            cnt += 1;
            printf("%c", cur);
            fprintf(negative, "%c", cur);
            fill_with_zero(list2);
            cnt2 = 0;
//            printf("finish\n");
        }
        else {
            printf("%c", cur);
            fprintf(negative, "%c", cur);
        }
        prev = cur;

    }
    printf("\ncnt: %d\n", cnt);


    fclose(ballons);
    fclose(negative);

    return 0;
}