//AUTHOR: Marco Preciado
//Description:This program will call the 'worker' program to conduct some operation
//The user will have 3 options:-n arg,-s arg,-t arg
//-n arg, takes an integer that creates total children('worker') programs to launch
//-s arg, takes an integer that indicates how many children will be allowed to run simultaneously
//-t arg, is the integer passed to the child('worker') for processing
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <ctype.h>


//interfaces////////////////////////////
void border();
void exitMessage();
void printHelp();
int isNotDigit(char * optarg);
void printArgNotNumMessage(char opt);
/////////////////////////////////////////




int main(int argc, char ** argv){
	const char optstr[] = "hn:s:t:";
	char opt;
	int proc = 1;//number of total children to launch
	int simul = 1;//how many children to allow to run simultaneously
	int iter = 1;//number to pass to the worker process
	int continueProcess = 1;//false if user does not provide valid arguments to options
	if(argc <= 1){
		printHelp();
		exitMessage();
		return EXIT_FAILURE;
	}else{
		while((opt = getopt(argc, argv, optstr)) != -1){
			switch(opt){
			 	case 'h'://-h => help
			 		printHelp();
					continueProcess = 0;
					break;
				 case 'n'://-n arg => number of total children to launch
				 	if(isNotDigit(optarg) == 0){
						printArgNotNumMessage(opt);
						continueProcess = 0;
					}else{
						proc = atoi(optarg);
					}
					break;
				 case 's'://-s arg => how many children to allow to run simultaneously
				 	if(isNotDigit(optarg) == 0){
						printArgNotNumMessage(opt);
						continueProcess = 0;
						return EXIT_FAILURE;
					}else{
						simul = atoi(optarg);
					}
					break;
				 case 't'://-t arg => number to pass to the worker process
				 	if(isNotDigit(optarg) == 0){
						printArgNotNumMessage(opt);
						continueProcess = 0;
						return EXIT_FAILURE;
					}else{
						iter = atoi(optarg);
					}
					break;
			}
		}
		if(continueProcess == 1){
			printf("proc: %d\n", proc);
			printf("simul %d\n", simul);
			printf("iter: %d\n", iter);
			exitMessage();
			return EXIT_SUCCESS;
		}
		else{
			exitMessage();
			return EXIT_FAILURE;
		}
	}
}
//Console format///////////////////////
void border(){
	printf("-----------------------------------------------------\n");
}
////////////////////////////////////////
//Common Console Messages///////////////
void exitMessage(){
	printf("Exiting Program!");
}

void printArgNotNumMessage(char opt){
	printf("-%s was not given an integer!\n", opt);
}

void printHelp(){
	border();
	printf("Welcome to the worker process simulator!\n\n");
	printf("AUTHOR: Marco Preciado\n");
	printf("DESCRIPTION: the purpose of this program is to simulate how child programs process either simultaneosly and/or sequentially\n\n");
	printf("INSTRUCTIONS:Please provide an integer to each option provided\n");
	printf("OPTIONS: -n arg, -s arg, -t arg\n");
	printf("-n arg, where arg is the number of total children to launch\n");
	printf("-s arg, where arg is the number of children allowed to run simultaneously\n");
	printf("-t arg, where arg is the number passed to the worker for the number of iterations a worker performs\n");
	border();
}
//////////////////////////////////////////




int isNotDigit(char * optarg){
	if(isdigit(optarg[0]))
		return 1;
	else
		printf("Please enter a digit for all arguments!\n");
		return 0;
}




//END OF FILE
