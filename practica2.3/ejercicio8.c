#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv) {

    if (argc < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    pid_t pid = fork();

    switch (pid) {
    case -1:
        perror("fork");
        exit(-1);
        break;
    case 0:;
        pid_t sid = setsid();
        printf("[Hijo] Proceso %i (Padre: %i)\n", getpid(), getppid());
        int fd = open("/tmp/daemon.out", O_CREAT | O_RDWR, 00777);
        int fdERROR = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
        int fdNULL = open("/dev/null", O_CREAT | O_RDWR, 00777);
        int fd2 = dup2(fd, 2);
        int fd3 = dup2(fdERROR, 1);
        int fd4 = dup2(fdNULL, 0);

        if (execvp(argv[1], argv + 1) == -1) {
            printf("ERROR: El comando no se ha ejecutado correctamente.\n");
            exit(-1);
        }
        break;
    default:
        printf("[Padre] Proceso %i (Padre: %i)\n", getpid(), getppid());
        break;
    }

    return 0;
}