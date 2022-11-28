
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

const int MAX_ERR=255;

int main(){

    for (int i = 0; i < MAX_ERR; i++){
        printf("ERROR(%d): %s\n", i, strerror(i));
    }
    return 1;
}