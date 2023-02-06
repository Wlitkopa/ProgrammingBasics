

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void upcase(char *s)
{
    while (*s)
    {
        *s = toupper(*s);
        s++;
    }
}
void handle_sigint(int sig)
{
    char *str = strdup(sys_siglist[sig]);
    upcase(str);
    printf("Caught signal SIG%s\n", str);
    free(str);
}

int main()
{

    pid_t pid = getpid();
    printf("pid: %d\n", pid);
    signal(SIGINT, handle_sigint);
    signal(SIGHUP, handle_sigint);
    signal(SIGQUIT, handle_sigint);
    signal(SIGILL, handle_sigint);
    signal(SIGTRAP, handle_sigint);
    signal(SIGABRT, handle_sigint);
    signal(SIGBUS, handle_sigint);
    signal(SIGFPE, handle_sigint);
    signal(SIGKILL, handle_sigint);
    signal(SIGUSR1, handle_sigint);
    signal(SIGSEGV, handle_sigint);
    signal(SIGUSR2, handle_sigint);
    signal(SIGPIPE, handle_sigint);
    signal(SIGALRM, handle_sigint);
    signal(SIGTERM, handle_sigint);
    signal(SIGSTKFLT, handle_sigint);
    signal(SIGCHLD, handle_sigint);
    signal(SIGCONT, handle_sigint);
    signal(SIGSTOP, handle_sigint);
    signal(SIGTSTP, handle_sigint);
    signal(SIGTTIN, handle_sigint);
    signal(SIGTTOU, handle_sigint);
    signal(SIGURG, handle_sigint);
    signal(SIGXCPU, handle_sigint);
    signal(SIGXFSZ, handle_sigint);
    signal(SIGVTALRM, handle_sigint);
    signal(SIGPROF, handle_sigint);
    signal(SIGWINCH, handle_sigint);
    signal(SIGIO, handle_sigint);
    signal(SIGPWR, handle_sigint);
    signal(SIGSYS, handle_sigint);


    while (1){
        printf("Sleeping\n");
        sleep(1);
    }
    return 0;
}

// Nie łapie:
// 9 (SIGKILL), 19 (SIGSTOP)
