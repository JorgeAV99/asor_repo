#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define PIPE_W 1
#define PIPE_R 0

int main() {

    int p_h[2];
    int h_p[2];
    pipe(p_h); 
    pipe(h_p);

    if (fork() == -1) {
        error("ERROR: Se produjo un error al realizar el fork.\n");
        return 1;
    }
    else if (fork() == 0) {
        close(p_h[1]); 
        close(h_p[0]);

        for (size_t i = 0; i < 10; i++) {
            ssize_t tam = read(p_h[0], mensajeProcesoPadre, 255);
            mensajeProcesoPadre[tam] = '\0';
            printf("Recibido el mensaje del proceso padre: %s\n", mensajeProcesoPadre);
            sleep(1);

            if (i == 9) {
                flag = 'q';
            }
            write(h_p[1], &flag, 1);
        }
    }
    else {
        close(p_h[0]); 
        close(h_p[1]);

        while (stop != 'q') {
            printf("%s\n", "Mensaje para el proceso hijo: ");
            ssize_t tam = read(0, mensaje, 255);
            mensaje[tam] = '\0';
            write(p_h[1], mensaje, 255);
            read(h_p[0], &flag, 1);
        }
        wait(NULL);
        close(fd[PIPE_W]);
        close(fd[PIPE_R]);

        printf("10 mensajes enviados. Finalizamos.\n");
    }
}