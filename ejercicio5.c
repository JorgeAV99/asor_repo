#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

	const char PATH[] = "/D:/a.CARRERA/SEXTO/ASOR/ej5.txt";

	int df = open(PATH, O_CREAT, 0645);

	return 1;
}