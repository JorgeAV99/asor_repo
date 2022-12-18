
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

volatile int stop = 0;

void hler(int senial) {
    pid_t pid;

    pid = wait(NULL);

    printf("Pid terminado.\n");
}

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

    signal(SIGCHLD, hler);

    int st;
    while (1) {

        client_sd = accept(socketTCP, (struct sockaddr*)&client, &clientTam);

        pid_t pid;
        pid = fork();
        if (pid == 0) {
            while (1) {
                getnameinfo((struct sockaddr*)&client, clientTam, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST);
                printf("[PID: %i] Conexión desde %s:%s\n", getpid(), host, server);

                c = recv(client_sd, buffer, 80, 0);
                buffer[c] = '\0';

                if ((buffer[0] == 'q') && (c == 2)) {
                    printf("Terminada la conexión TCP.\n");
                    exit(0);
                }
                else {
                    send(client_sd, buffer, c, 0);
                }
            }
        }
        else {
            pid = wait(&st);
            close(client_sd);
            exit(0);
        }
    }
    
    close(client_sd);

    return 0;
}