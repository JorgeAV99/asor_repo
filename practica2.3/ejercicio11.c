#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    sigprocmask(SIG_BLOCK, &set, NULL);//bloqueamos

    char* sleep = getenv("SLEEP_SECS");
    int seg = atoi(sleep);
    printf("El proceso se va a dormir durante %d segundo(s)\n", seg);
    sleep(secs);//Dormimos

    sigset_t pend;
    sigpending(&pend);

    if (sigismember(&pend, SIGINT) == 1) {
        printf("Se ha recibido la señal SIGINT\n");
        sigdelset(&set, SIGINT);//Eliminamos
    }
    else {
        printf("No se ha recibido la señal SIGINT\n");
    }
    if (sigismember(&pend, SIGTSTP) == 1) {
        printf("Se ha recibido la señal SIGTSTP\n");
        sigdelset(&set, SIGTSTP);//Eliminamos
    }
    else {
        printf("No se ha recibido la señal SIGTSTP\n");
    }
    sigprocmask(SIG_UNBLOCK, &set, NULL);//desbloqueamos

    return 0;
}