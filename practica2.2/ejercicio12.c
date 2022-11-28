#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if (argc < 2) {
		 printf("ERROR: Se debe especificar la ruta del archivo de argumento.\n");
		 return -1;
	}

  int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
  
  if (fd == -1) {
    printf("ERROR: No se ha podido abrir el fichero.\n");
    return -1;
  }

  int fd2 = dup2(fd, 1);

  printf("Se ha reedirigido a d\n", argv[1]);

  dup2(fd2, fd);

  return 0;
}
