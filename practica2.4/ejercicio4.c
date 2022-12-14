#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char** argv) {

    if (argc < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    char* nombre = getenv("HOME");
    char* pipe = strcat(nombre, "/pipe");
    printf("HOME: %s\n", pipe);
    mkfifo(pipe, 0777);

    int fd = open(pipe, O_WRONLY);
    write(fd, argv[1], strlen(argv[1])); //escribir primer argumento del programa
    close(fd);

    return 0;
}