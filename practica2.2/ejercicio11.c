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
  
  mode_t mode = buffer.st_mode;
  
  if (S_ISREG(mode)) { //si es un fichero regular
  
	  const char PATH[] = argv[1];
    const char RIGIDO[] = "/D:/a.CARRERA/SEXTO/ASOR/ej11.hard";
    const char SIMBOLICO[] = "/D:/a.CARRERA/SEXTO/ASOR/ej11.sym";
    
    link(PATH, RIGIDO);
    
    symlink(PATH, SIMBOLICO);
  }
  
  return 0;
}
