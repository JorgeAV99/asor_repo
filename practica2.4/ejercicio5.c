
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {

    char* pipe1 = "pipe1";
    mkfifo(pipe1, 0644);

    char* pipe2 = "pipe2";
    mkfifo(pipe2, 0644);

    char buffer[257];

    int pipe1int = open(pipe1, O_RDONLY | O_NONBLOCK);
    int pipe2int = open(pipe2, O_RDONLY | O_NONBLOCK);
    int actualPipe;
    int changes;

    while (changes != -1) {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(pipe1int, &set);
        FD_SET(pipe2int, &set);
        int actualPipeCont;
        ssize_t tam = 256;

        changes = select((pipe1int < pipe2int) ? pipe2int + 1 : pipe1int + 1, &set, NULL, NULL, NULL);

        if (changes > 0) {
            if (FD_ISSET(pipe1int, &set)) {
                actualPipeCont = 1;
                actualPipe = pipe1int;
            }
            else if (FD_ISSET(pipe2int, &set)) {
                actualPipeCont = 2;
                actualPipe = pipe2int;
            }

            while (tam == 256) {
                tam = read(actualPipe, buffer, 256);
                buffer[tam] = '\0';
                printf("Tubería %i: %s", actualPipeCont, buffer);
            }

            if (tam != 256 && actualPipeCont == 1) {
                close(pipe1int);
                pipe1int = open(pipe1, O_RDONLY | O_NONBLOCK);

                if (pipe1int == -1) {
                    perror("ERROR: No es posible abrir la segunda tubería.");
                    close(pipe1int);
                    close(pipe2int);
                    return -1;
                }
            }
            else if (tam != 256 && actualPipeCont == 2) {
                close(pipe2int);
                pipe2int = open(pipe2, O_RDONLY | O_NONBLOCK);

                if (pipe1int == -1) {
                    perror("ERROR: No es posible abrir la segunda tubería.");
                    close(pipe1int);
                    close(pipe2int);
                    return -1;
                }
            }
        }

    }
    close(pipe1int);
    close(pipe2int);
    return 0;
}