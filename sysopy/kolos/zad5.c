#include <ulimit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){

    int i = 0;
    int pid = fork();

    if (pid == 0) {
        pid = fork();
    }
    else {
        fork();
    }

//    fork();
    getchar();


//    if (pid > 0){
//        pid = fork();
//        getchar();
//    }

    i += 1;
    printf("Fork %d\n", i);

//    system("ulimit -a");
    return 0;
}

// Ten proces może mieć 63204 procesy potomne
