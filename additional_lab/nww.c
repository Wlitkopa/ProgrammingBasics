#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "header_file.h"


int nww(int a, int b){

    int new_a = a;
    int new_b = b;
    int nwd = 0;
    int nww = 0;
    int r = 1;

    while (r != 0){
        nwd = r;
        r = new_a-new_b*(new_a/new_b);
        new_a = new_b;
        new_b = r;
    }
    nww = (a*b)/nwd;

    return nww;
}