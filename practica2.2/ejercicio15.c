#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char ** argv) {


  if (argc < 2) {
     printf("ERROR: Se debe especificar la ruta del archivo de argumento.\n");
     return -1;
  }

  int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
  if (fd == -1) {
    printf("ERROR: No se ha podido abrir el fichero.\n");
    return -1;
  }

  struct flock cerrojo;

  cerrojo.l_type = F_UNLCK;
  cerrojo.l_whence = SEEK_SET;
   cerrojo.l_len = 0;
  cerrojo.l_start = 0;
  cerrojo.l_pid = getpid();


  int status = fcntl(fd, F_GETLK, &cerrojo);

  if (cerrojo.l_type == F_UNLCK) {
    printf("STATUS: Cerrojo desbloqueado.\n");
    cerrojo.l_type = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_len = 0;
    cerrojo.l_start = 0;
    cerrojo.l_pid = getpid();

    if (fcntl(fd, F_GETLK, &cerrojo) == -1) {
      printf("ERROR:No se ha podido crear el cerrojo.\n");
      close(fd);
      return 1;
    } else {
      printf("STATUS: Cerrojo de escritura activado\n");

      //Escribir la hora actual
      time_t tim = time(NULL);

      struct tm *tm = localtime(&tim);

      char buffer[1024];

      sprintf (buffer, "Hora: %d:%d\n", tm->tm_hour, tm->tm_min);

      write(fd, &buffer, strlen(buffer));


      sleep(30);

      cerrojo.l_type = F_WRLCK;
      cerrojo.l_whence = SEEK_SET;
      cerrojo.l_len = 0;
      cerrojo.l_start = 0;
      cerrojo.l_pid = getpid();
      
      if (fcntl(fd, F_GETLK, &cerrojo) == -1) {
        printf("ERROR:No se ha podido crear el cerrojo.\n");
        close(fd);
        return 1;
      } else
      close(fd);
    }

  } else {
    printf("STATUS: Cerrojo bloqueado.\n");
    close(fd);
    return 1;
  }
  close(fd);
}
