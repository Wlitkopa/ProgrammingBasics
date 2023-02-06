#include <ulimit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){

    int i = 0;
    int pid = fork();

//    while (1) {
//        if (pid == 0) {
//            pid = fork();
//        }
//    }

    if (pid > 0){
        pid = fork();
    }
    i += 1;
    printf("Fork %d\n", i);


    system("ulimit -a");
    return 0;
}

// Ten proces może mieć 63204 procesy potomne
