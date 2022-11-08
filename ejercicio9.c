#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <pwd.h>

int main(){
     uid_t uid = getuid();

    printf("UID Real: %d\n", getuid());
    printf("UID efectivo: %d\n", geteuid());



    return 1;
}