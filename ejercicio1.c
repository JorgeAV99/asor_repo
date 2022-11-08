
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){

    if (setuid(0) == -1){
        perror("ERROR");
    }
    
    return 1;
}