
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

//    int rpid;
    pid_t rpid;

    printf("Podaj pid receive: \n");
    scanf("%d", &rpid);
    printf("rpid: %d\n", rpid);

    pid_t pid = getpid();

    char command[100];

    for (int i = 20; i < 31; ++i) {
        sprintf(command, "kill -s %d %d", i + 1, rpid);
        printf("%s\n", command);
        system(command);
    }


    return 0;
}
