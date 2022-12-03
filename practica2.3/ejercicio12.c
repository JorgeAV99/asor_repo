#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int intCont = 0;
volatile int tstpCont = 0;

void sen(int sign){
	if (sign == SIGINT){
		intCont++;
	}
	if (sign == SIGTSTP) {
		tstpCont++;
	}
}

int main(){
	
	struct sigaction actual;

	sigaction(SIGINT, NULL, &actual);
	actual.sa_handler = sen;
	sigaction(SIGINT, &actual, NULL);

	sigaction(SIGTSTP, NULL, &actual);
	actual.sa_handler = sen;
	sigaction(SIGTSTP, &actual, NULL);

	sigset_t set;
	sigemptyset(&set);

	while (intCont + tstpCont < 10) {
		sigsuspend(&set);
	}
	printf("SIGINT capturados: %i\n", intCont);
	printf("SIGTSTP capturados: %i\n", tstpCont);

	return 0;
}