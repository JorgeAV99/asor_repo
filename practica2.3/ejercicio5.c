#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>

int main() {

    printf("PID: %i\n", getpid());
    printf("PPID: %i\n", getppid());
    printf("PPID: %i\n", getsid(getpid()));
    struct rlimit limite;
    if (getrlimit(RLIMIT_NOFILE, &limite) == -1) {
        perror("No se puede obtener el num max de ficheros");
        return -1;
    }
    printf("Num max de ficheros: %li\n", limite.rlim_max);

    char* ruta = malloc(sizeof(char) * (4096 + 1));
    char* rpath = getcwd(ruta, 4096 + 1);
    printf("Directorio de trabajo actual: %s\n", ruta);
    free(path);

    return 0;
}