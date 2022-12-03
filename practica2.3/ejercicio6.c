#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>


void ejercicio5(char* type) {

    printf("[%s]PID: %i\n", type, getpid());
    printf("[%s]PPID: %i\n", type, getppid());
    printf("[%s]PPID: %i\n", type, getsid(getpid()));
    struct rlimit limite;
    if (getrlimit(RLIMIT_NOFILE, &limite) == -1) {
        perror("No se puede obtener el num max de ficheros");
    }
    printf("[%s]Num max de ficheros: %li\n", type, limite.rlim_max);

    char* ruta = malloc(sizeof(char) * (4096 + 1));
    char* rpath = getcwd(ruta, 4096 + 1);
    printf("[%s]Directorio de trabajo actual: %s\n", type, ruta);
    free(path);
}

int main() {

    pid_t pid = fork();

    switch (pid) {
    case -1:
        perror("fork");
        exit(-1);
        break;
    case 0:;
        pid_t sid = setsid();
        char* directorio = chdir("/tmp");

        printf("[Hijo] Proceso %i (Padre: %i)\n", getpid(), getppid());
        ejercicio5("Hijo");

        break;
    default:
        printf("[Padre] Proceso %i (Padre: %i)\n", getpid(), getppid());
        ejercicio5("Padre");
        break;
    }

    return 0;
}