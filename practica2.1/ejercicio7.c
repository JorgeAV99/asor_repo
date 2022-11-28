#include <unistd.h>
#include <stdio.h>

int main() {

    int fd;
//n max de enlaces, tam max de ruta y tam max nombre fichero
	printf("Número máximo de enlaces: %li\n", fpathconf(fd, _PC_LINK_MAX));
	printf("Tamaño máximo de ruta: %li\n", fpathconf(fd, _PC_PATH_MAX));
	printf("Tamaño máximo de nombre de fichero: %li\n", fpathconf(fd, _PC_NAME_MAX));


    return 0;
}