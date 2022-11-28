#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char **argv) {
  
	if (argc < 2) {
		printf("ERROR: Se debe especificar la ruta del archivo.\n");
		return -1;
	}
  
  struct stat buffer;
	
  int statint = stat(argv[1], &buffer);

  if (statint == -1) {
  	printf("ERROR: No existe el directorio.\n");
	return -1;
  }
  
  //Major y Minor
  printf("MAJOR: %li\n", (long) minor(buffer.st_dev));
	printf("MINOR: %li\n", (long) major(buffer.st_dev));
  
  //I-Nodo
	printf("I-Nodo: %li\n",buffer.st_ino);
  
  //Tipo de archivo
	printf("MODO: %i\n",buffer.st_mode);
	mode_t mode = buffer.st_mode;

	if (S_ISLNK(mode)){
		printf("%s es un enlace simbólico.\n", argv[1]);
	} else if (S_ISREG(mode)) {
		printf("%s es un archivo ordinario.\n", argv[1]);
	} else if (S_ISDIR(mode)) {
		printf("%s es un directorio.\n", argv[1]);
	}
  
  //Hora ficheros M
	time_t t = buffer.st_mtime;

	struct tm *tm= localtime(&t);

	printf("Último acceso (M): %d:%d\n", tm->tm_hour, tm->tm_min);

	//Hora ficheros C
	time_t t2 = buffer.st_ctime;

	struct tm *tm2= localtime(&t2);

	printf("Último acceso (C): %d:%d\n", tm2->tm_hour, tm2->tm_min);

	return 0;
}
  
  
