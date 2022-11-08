
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(){

  time_t t = time(NULL);
  struct tm *info = localtime(&t);

  int year = info->tm_year;

 

  char buf[100];
  strftime(buf, 100, "%A, %d de %B, %H:%M", info);
  printf("Hoy es día: %s\n", buf);
  return 1;
}