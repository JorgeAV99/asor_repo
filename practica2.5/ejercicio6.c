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
    bind(socketTCP, result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);

    listen(socketTCP, 5);

    struct sockaddr_storage client;
    socklen_t clientTam = sizeof(client);

    char buffer[81];
    int client_sd;
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];
    ssize_t c;

    while (1) {

        cli_sd = accept(socketTCP, (struct sockaddr*)&client, &clientTam);

        while (1) {
            getnameinfo((struct sockaddr*)&client, clientTam, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST);
            printf("Conexión desde %s:%s\n", host, server);

            c = recv(client_sd, buffer, 80, 0);
            buffer[c] = '\0';

            if ((buffer[0] == 'Q') && (c == 2)) {
                printf("Terminada la conexión TCP.\n");
                break;
            }
            send(client_sd, buffer, c, 0);
        }
    }

    close(client_sd);

    return 0;
}