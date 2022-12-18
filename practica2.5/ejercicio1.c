
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {


    if (argc < 2) {
        printf("ERROR: Se necesita que introduzca un argumento.\n");
        return -1;
    }

    printf("Familia de protocolos: [2] AF_INET [10] AF_INET6.\n");
    printf("Tipos de socket: [1] SOCK_STREAM [2] SOCK_DGRAM [3] SOCK_RAW.\n\n");

    struct addrinfo posible;
    struct addrinfo* result;
    struct addrinfo* *it;

    memset(&posible, 0, sizeof(struct addrinfo));

    posible.ai_family = AF_UNSPEC;
    posible.ai_socktype = 0;
    posible.ai_flags = AI_PASSIVE;
    posible.ai_protocol = 0;
    posible.ai_canonname = NULL;
    posible.ai_addr = NULL;
    posible.ai_next = NULL;

    if (getaddrinfo(argv[1], NULL, &posible, &result) != 0) {
        printf("ERROR: No se ha podido ejecutar el comando.");
        exit(EXIT_FAILURE);
    }

    for (it = result; it != NULL; it = it->ai_next) {
        if (it->ai_family == AF_INET) {
            struct sockaddr_in* info4 = it->ai_addr;
            char ipv4[INET_ADDRSTRLEN + 1] = "";
            inet_ntop(AF_INET, &(info4->sin_addr), ipv4, INET_ADDRSTRLEN + 1);
            printf("%s\t", ipv4);
        }
        else if (it->ai_family == AF_INET6) {
            struct sockaddr_in6* info6 = it->ai_addr;
            char ipv6[INET6_ADDRSTRLEN + 1] = "";
            inet_ntop(AF_INET6, &(info6->sin6_addr), ipv6, INET6_ADDRSTRLEN + 1);
            printf("%s\t", ipv6);
        }
        else {
            printf("ERROR: Familia de protocolos indefenida.\n");
        }

        printf("%i\t%i\t\n", it->ai_family, it->ai_socktype);
    }

    freeaddrinfo(result);

    return 0;
}