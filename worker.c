//AUTHOR: Marco Preciado
//Description: This is the worker.c file
//This program simply uses the supplied integers and loops that amount of times
//printing the PID of the child and parent.
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char ** argv){
	int loopCount = atoi(argv[1]);
	int i;
	for(i = 0; i < loopCount; i++){
		printf("WORKER PID: %d, ", getpid());
		printf("PPID: %d ", getppid());
		printf("Iteration: %d\n", i + 1);
	}
	return 0;
}
