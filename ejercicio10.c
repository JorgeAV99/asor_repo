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

    struct passwd *pass= getpwuid(uid);

    char *name = pass->pw_name;
    char *dir = pass->pw_dir;
    char *desc = pass->pw_gecos;

    printf("Nombre de usuario: %s\n", name);
    printf("Home: %s\n", dir);
    printf("Descripción: %s\n",desc);


    return 1;
}