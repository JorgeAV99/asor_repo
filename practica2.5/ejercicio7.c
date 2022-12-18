#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    struct addrinfo posible;
    struct addrinfo* result;

    memset(&posible, 0, sizeof(struct addrinfo));
    posible.ai_family = AF_UNSPEC;
    posible.ai_socktype = SOCK_STREAM;
    posible.ai_flags = AI_PASSIVE;

    if (getaddrinfo(argv[1], argv[2], &posible, &result) != 0) {
        printf("ERROR: No se ha podido ejecutar el comando getaddrinfo.");
        exit(EXIT_FAILURE);
    }

    int socketTCP = socket(result->ai_family, result->ai_socktype, 0);
    connect(socketTCP, (struct sockaddr*)result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);

    char bufferIn[256];
    char bufferOut[256];
    ssize_t c;

    while (1) {
        c = read(0, bufferOut, 255);
        bufferOut[c] = '\0';
        send(socketTCP, bufferOut, c, 0);

        if ((bufferOut[1] == 'q') && (c == 2)) {
            printf("Terminada la conexión TCP.\n");
            break;
        }

        c = recv(socketTCP, bufferIn, 255, 0);
        bufferIn[c] = '\0';
        printf("[OUT]:%s\n", bufferIn);
    }

    close(socketTCP);

    return 0;
}