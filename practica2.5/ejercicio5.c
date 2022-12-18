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

    if (bind(socketUDP, result->ai_addr, result->ai_addrlen) != 0) {
        printf("ERROR: No se ha podido ejecutar el comando bind.");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    signal(SIGCHLD, hler);

    char buffer[2];
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];

    struct sockaddr_storage client_addr;
    socklen_t client_addrtam = sizeof(client_addr);
    int i = 0;
    int st;
    for (i = 0; i < 2; i++) {
        pid_t pid;
        pid = fork();

        if (pid == 0) {
            while (1) {
                ssize_t bytes = recvfrom(socketUDP, buffer, 2, 0, (struct sockaddr*)&client_addr, &client_addrtam);
                buffer[1] = '\0';

                getnameinfo((struct sockaddr*)&client_addr, client_addrtam, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

                printf("%i byte(s) de %s:%s cuyo PID: %d\n", bytes, host, server, getpid());

                time_t tiempo = time(NULL);
                struct tm* tm = localtime(&tiempo);
                size_t max;
                char s[50];

                if (buffer[0] == 't') {
                    size_t bytesT = strftime(s, max, "%I:%M:%S %p", tm);
                    s[bytesT] = '\0';
                    sendto(socketUDP, s, bytesT, 0, (struct sockaddr*)&client_addr, client_addrtam);

                }
                else if (buffer[0] == 'd') {
                    size_t bytesT = strftime(s, max, "%Y-%m-%d", tm);
                    s[bytesT] = '\0';
                    sendto(socketUDP, s, bytesT, 0, (struct sockaddr*)&client_addr, client_addrtam);
                }
                else if (buffer[0] == 'q') {
                    printf("Terminando el proceso servidor.\n");
                    exit(0);
                }
                else {
                    printf("Comando no soportado: %d...\n", buffer[0]);
                }
            }
        }
        else {
            pid = wait(&st);
        }
    }
    return 0;
}