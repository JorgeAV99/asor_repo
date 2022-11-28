#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {


	if (argc < 2) {
		 printf("ERROR: Se debe especificar la ruta del archivo de argumento.\n");
		 return -1;
	}

  DIR *directorio = opendir(argv[1]);

  if (directorio == NULL) {
    printf("ERROR: No existe el directorio.\n");
    return -1;
  }

  struct dirent *actual;
  struct stat info;
  size_t sizePath = strlen(argv[1]);
  actual = readdir(directorio);
  unsigned long int totalsize = 0;

  while (current != NULL) {
    char *path = malloc(sizeof(char)*(sizePath + strlen(actual->d_name) + 3));
    strcpy(path, argv[1]);
    strcat(path, "/");
    strcat(path, actual->d_name);


    if (stat(path, &info) == -1) {
      printf("ERROR : No se puede analizar el archivo\n");
      free(path);
      closedir(directorio);
      return -1;
    } else {
      if (S_ISREG(info.st_mode)) {
        printf("[*] %s \n", actual->d_name); //fichero regular y tiene permiso de ejecución para usuario, grupo u otros
        totalsize = totalsize + ((info.st_blksize/8)*info.st_blocks);

      } else if (S_ISDIR(info.st_mode)) {
        printf("[/] %s \n", current->d_name); //directorio

      } else if (S_ISLNK(info.st_mode)) {
        char *linkname = malloc(info.st_size + 1);
        int rc2 = readlink(path, linkname, info.st_size + 1);
        printf("[S]: %s->%s \n", actual->d_name, linkname); //enlace simbólico - nombre del fichero enlazado después del nombre
        totalsize = totalsize + ((info.st_blksize/8)*info.st_blocks);
        free(linkname);
      }
    }
    
    printf("Tamaño total de ficheros en KB = %i\n", totalsize); //TAMAÑO TOTAL
    
    free(path);
    actual = readdir(directorio);
  }

  closedir(directorio);
  return 0;
}
