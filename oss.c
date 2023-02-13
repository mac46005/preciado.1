//AUTHOR: Marco Preciado
//DESCRIPTION:
//This program will call the 'worker' program to conduct some operation
//The user will have 4 options:-h,-n,-t,-s
//-h is the option for help and will tell users how to use this program
//-n takes an argument that indicates how many children will be created
//-t takes an argument that indicates the number that is passed to worker for processing
//-s takes an argument that indicates the number of workers that process synchronously

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
void printHelp();
void exitMessage();
int isNotDigit(char* optarg);
			


int main(int argc, char* argv[]){
	const char optstr[] = "hn:s:t:";
	char opt;
	int proc = 1;//number of total children to launch
	int simul = 0;//how many children to allow simultaneous process
	char* iter;//number to pass to the worker process
	int continueProcess = 1;//false if user does not provide valid arguments to options

	if(argc <= 1){
		printHelp();
		exitMessage();
		return 1;
	}
	else{
		while((opt = getopt(argc, argv, optstr)) != -1){
			switch(opt){
				case 'h':
					printHelp();
					continueProcess = 0;
					break;
				case 'n':
					if(isNotDigit(optarg) == 0){
						continueProcess = 0;
						
					}else{
						proc = atoi(optarg);
					}
					break;
				case 's':
					if(isNotDigit(optarg) == 0){
						continueProcess = 0;
					}else{
						simul = atoi(optarg);
					}
					break;
				case 't':
					if(isNotDigit(optarg) == 0){
						continueProcess = 0;
					}else{
						iter = optarg;
					}
					break;
				default:
					break;

			}
		}









		if(continueProcess == 1){
			// This is where the forking happens
			char* progName = "./worker";
			char* arguments[] = {progName, iter, NULL};

			int pid = fork();
			if(pid == 0){
				execv(progName, arguments);
				exit(0);
			}
			else{
				wait(NULL);
				printf("parent waited\n");
			}
				
			
		}else{
			exitMessage();
			return 2;
		}











	}
	return 0;
}

void printHelp(){
	char helpMessage[] = 
		"Welcome to the worker process simulator!\nAUTHOR: Marco Preciado\n\nDESCRIPTION:\nThe purpose of this program is to simulate how child programs process either simultaneously and sequentially\n\nINSTRUCTIONS: Please provide and integer value to each of the following options\nOPTIONS: -n, -t, -s\n-n arg, where arg is the number of child processes created\n-t arg, where arg is the number passes to child processes for processing\n-s arg, where arg is the number of child processes that work simultaneously\n\nEXAMPLE: ./oss -n 3 -s 4 -t 40\n The example is an example use of this program that will create 3 workers of which 4 of them will work simultaneously and all workers will process the number 40.\n";
	printf(helpMessage);
}
void exitMessage(){
	char goodbye[] = "Thank you for using me. Good bye\n";
	printf(goodbye);
}

int isNotDigit(char* optarg){
	if(isdigit(optarg[0])){
		return 1;
	}
	else{
		printf("Please enter a digit for all arguments\n");
		return 0;
	}
}


