#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    int tam = 1;
    for (int i = 1; i < argc; i++)
        tam += strlen(argv[i]) + 1;
    char* res = malloc(sizeof(char) * tam);
    strcpy(res, "");

    for (int i = 1; i < argc; i++) {
        strcat(res, argv[i]);
        strcat(res, " ");
    }

    if (system(res) == -1) {
        printf("ERROR: El comando no se ha ejecutado correctamente.\n");
    }

    printf("El comando ha terminado de ejecutarse.\n");

    return 0;
}