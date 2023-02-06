#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

    int pid_t = getpid();
    printf("pid is: %d\n", pid_t);
    char ch[1];
    int n = 0;
    int num = 0;

    while ((num = getchar()) != EOF && n < 1) {
        ch[n] = num;
        ++n;
        printf("char: %c\n", num);
    }

    FILE *fpoint;

    fpoint = fopen("file.txt", "w");
    char str[100];
    char *cha = (char*)malloc(5*sizeof(char));

    int x = 1;

    int pid = fork();

    if (pid < 0){
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0){
        x -= 1;
        printf("x: %d\n", x);
        int child_pid = getpid();
        int child_ppid = getppid();
        printf("Child process: %d\n", child_pid);
        printf("Parent process: %d\n", child_ppid);
        int chilstr = 0;
        char c = 'c';
        fwrite(&c, sizeof(char), 1, fpoint);
        chilstr = getchar();
        printf("chilstr: %c", chilstr);

//        int grandch = fork();
//        if (grandch < 0){
//            fprintf(stderr, "Grandchild Fork Failed\n");
//        }
//        else if (grandch == 0){
//            int grand_child_pid = getpid();
//            int grand_child_ppid = getppid();
//            printf("Grandchild process: %d\n", grand_child_pid);
//            printf("Parent of grandchild process: %d\n", grand_child_ppid);
//        }
        fclose(fpoint);
    }
    else{
        x += 1;
        printf("x: %d\n", x);
        printf("wait2: \n");
        int wait2 = getchar();
        printf("parent str: %c\n", wait2);
        printf("Child has finished it's program\n");
//        printf("Creating a brother\n");
//        int brother = fork();
//
//        if (brother < 0){
//            fprintf(stderr, "Child Fork Failed\n");
//        }
//        else if (brother == 0) {
//            int brother_pid = getpid();
//            int brother_parent_pid = getppid();
//            printf("Brother process: %d\n", brother_pid);
//            printf("Parent of brother process: %d\n", brother_parent_pid);
//            int wait = getchar();
//        }
    }


    return 0;


}