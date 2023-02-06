
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <unistd.h>

int main(){

    printf("Hello! I'm exec program\n");

    char *args[]={"./another",NULL};
    execvp(args[0],args);

    int ch = getchar();

    return 0;
}

// uruchamiając exec, zostaje otwarty inny program (uruchomiony inny proces, programu another), natomiast
// proces programu exec zostaje zamknięty. Nie widać go używając komendy pstree