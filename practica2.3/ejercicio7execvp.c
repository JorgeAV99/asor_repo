#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    if (execvp(argv[1], argv + 1) == -1) {
        printf("ERROR: El comando no se ha ejecutado correctamente.\n");
    }

    printf("El comando ha terminado de ejecutarse.\n");

    return 0;
}