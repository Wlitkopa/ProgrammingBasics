
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

    printf("Hello! I'm system program\n");

    system("ls -al /var/log/");

    int ch = getchar();

    return 0;
}