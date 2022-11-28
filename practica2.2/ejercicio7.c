#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

  const char PATH[] = "/D:/a.CARRERA/SEXTO/ASOR/ej6.txt";
  
	mode_t prev = umask(027);
	int file = open(PATH, O_CREAT | O_RDONLY, 0777);

	return 0;
}
