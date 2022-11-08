
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){


    if (setuid(0) == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno));
    }
    
    return 1;
}