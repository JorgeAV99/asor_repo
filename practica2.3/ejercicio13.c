#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile int stop = 0;

void sig(int signal) {
    if (signal == SIGUSR1) {
        stop = 1;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    sigset_t mascara;
    sigemptyset(&mascara);
    sigaddset(&mascara, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &mascara, NULL);

    struct sigaction actual;
    sigaction(SIGUSR1, NULL, &actual); 
    actual.sa_handler = sig;
    sigaction(SIGUSR1, &actual, NULL);

    int seg = atoi(argv[1]);

    int i = 0;
    while ( i < seg && stop == 0) {
        i++;
        sleep(1);
    }

    if (stop == 0) {
        printf("Procedemos a borrar el proceso.");
        unlink(argv[0]);
    }
    else {
        printf("Se ha detenido el borrado del proceso.");
    }

    return 0;
}