
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(){
  
  struct timeval tv;
  int ms = gettimeofday(&tv, NULL);
  int start = tv.tv_usec;

  int i;
  for (i = 0; i < 1000000; i++);

  int ms2 = gettimeofday(&tv, NULL);
  int end = tv.tv_usec;

  printf("El bucle ha tardado (ms): %i\n", end - start);

  return 1;
}