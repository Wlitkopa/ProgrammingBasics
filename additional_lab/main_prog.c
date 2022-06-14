#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "header_file.h"



int main(int argc, char **argv){

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("nww: %d\n", nww(a, b));
    printf("nwd: %d\n", nwd(a, b));



    return 0;
}