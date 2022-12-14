#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define PIPE_W 1
#define PIPE_R 0

int main(int argv, char** argc) {

    if (argv < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
    }

    int fd[2];
    int pipe = pipe(fd);

    if (fork() == -1) {
        error("ERROR: Se produjo un error al realizar el fork.\n");
        return 1;
    }
    else if (fork() == 0) {
    
        dup(fd[PIPE_R], 0);
        //Antes de ejecutar el comando correspondiente, deben cerrarse todos los descriptores no necesarios.
        close(fd[PIPE_W]); 
        close(fd[PIPE_R]);
        //El proceso hijo redireccionará la entrada estándar al extremo de lectura de la tubería y ejecutará comando2 argumento2.
        execlp(argc[3], argc[3], argc[4]);
    }
    else {
        dup(fd[PIPE_W], 1);
        //Antes de ejecutar el comando correspondiente, deben cerrarse todos los descriptores no necesarios.
        close(fd[PIPE_W]);
        close(fd[PIPE_R]);
        //El proceso padre redireccionará la salida estándar al extremo de escritura de la tubería y ejecutará comando1 argumento1.
        execlp(argc[1], argc[1], argc[2]);
    }
}