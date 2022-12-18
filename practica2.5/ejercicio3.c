#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>


int main(int argc, char** argv) {

    if (argc < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    struct addrinfo posible;
    struct addrinfo* result;

    memset(&posible, 0, sizeof(struct addrinfo));
    posible.ai_family = AF_UNSPEC;
    posible.ai_socktype = SOCK_DGRAM;
    posible.ai_flags = AI_PASSIVE;

    if (getaddrinfo(argv[1], argv[2], &posible, &result) != 0) {
        printf("ERROR: No se ha podido ejecutar el comando getaddrinfo.");
        exit(EXIT_FAILURE);
    }

    int socketUDP = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    freeaddrinfo(result);

    struct sockaddr_storage client_addr;
    socklen_t client_addrtam = sizeof(client_addr);

    sendto(socketUDP, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);

    printf("%s\n", argv[3]);

    if (*argv[3] == 'd' || *argv[3] == 't') {
        char s[50];
        ssize_t bytes = recvfrom(socketUDP, s, 50, 0, (struct sockaddr*)&client_addr, &client_addrtam);
        s[bytes] = '\0';

        printf("%s\n", s);
    }

    return 0;
}