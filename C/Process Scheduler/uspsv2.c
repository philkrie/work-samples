/*
 *	Rudimentary USPS
 *  Project 1, Part 2
 */

#include "p1fxns.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

#define BUF_SIZE 100
#define WORD_BUF_SIZE 20
#define NUM_ARGS 10
#define MAX_NUM_PROGRAMS 100

int numprograms;
char** program;
char*** args;
int* pid;
int size;

/*static void sigchld_handler () {
	pid_t pid;
	int status;
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		if (WIFEXITED(status)) {
			p1putint(1, pid);
			p1putstr(1, ": exited\n");
		}
	}
} */

int USR1_received = 0;

void USR1_handler() {
	USR1_received++;
}


int main(){

	if (signal(SIGUSR1, USR1_handler) == SIG_ERR) {
	}

	//if (signal(SIGCHLD, sigchld_handler) == SIG_ERR){
	//}

    char buffer[BUF_SIZE];
    char word[WORD_BUF_SIZE];


	if((program = (char**) calloc(MAX_NUM_PROGRAMS, sizeof(char*))) == NULL){
		p1putstr(1, "Failed to allocate program array");
		exit(1);
	}

	if((args = (char***) calloc(MAX_NUM_PROGRAMS, sizeof(char**))) == NULL){
		p1putstr(1, "Failed to allocate arg array");
		exit(1);
	}

	int i;
	for(i = 0; i < MAX_NUM_PROGRAMS; i++){
		if((args[i] = (char**) calloc(NUM_ARGS, sizeof(char*))) == NULL){
			p1putstr(1, "Failed to allocate arg array");
			exit(1);
		}
	}

	if((pid = (int*) malloc(sizeof(int) * MAX_NUM_PROGRAMS)) == NULL){
		p1putstr(1, "Failed to allocate pid array");
		exit(1);
	}

	numprograms = 0;
	int word_count;
	int line = 0;
 	while(p1getline(0, buffer, BUF_SIZE) != 0){
 		int index = p1strchr(buffer, '\n');
 		buffer[index] = '\0';
 		numprograms++;
 		word_count = 0;
 		index = 0;
 		while(1){
 			index = p1getword(buffer, index, word);
 			if (index == -1){
 				args[line][word_count] = NULL;
 				break;
 			}
 			else if(word_count == 0){
 				program[line] = p1strdup(word);
 				args[line][word_count] = p1strdup(word);
 			} else {
 				args[line][word_count] = p1strdup(word);
 			}
 			word_count++;
 		}

 		pid[line] = fork();
 		if(pid[line] == -1){
 			p1putstr(1, "Failed to create child");
 			exit(1);
 		}
 		if (pid[line] == 0){
 			/*sigset_t theSet;
   		        int theInfo;
   		        pid_t thePid;
			*/
				 /* child branch */
				while (! USR1_received)
				sleep(1);
				p1putstr(1, "Got it!");
				execvp(program[line], args[line]);
				} 
			/*
    			thePid = getpid();
    			p1putint(1, thePid);
    			p1putstr(1, ": my pid\n");
    			if (signal(SIGUSR1, sig_handler)== SIG_ERR)
        			p1putstr(1, "can't catch SIGUSR1\n");
   		 		sigemptyset(&theSet);
    			sigaddset(&theSet, SIGUSR1);
   		        p1putstr(1, "Waiting for SIGUSR1\n");
   		        sigwait(&theSet, &theInfo);
   		        p1putstr(1, "Received SIGUSR1\n");
 			int error = execvp(program[line], args[line]);
 			if(error == -1){
 				p1putstr(1, "Failed to execute");
 				exit(1);
 			}*/
 		line++;
 	}

	for(i = 0; i < numprograms; i++){
		sleep(1);//Makes the output more aesthetically pleasing and orderly, can be removed
 		int killerror = kill(pid[i], SIGUSR1);
 		if(killerror == -1){
 			p1perror(1, "Failed to send SIGUSR1");
 		}
 	}

 	sleep(2);

 	for(i = 0; i < numprograms; i++){
		//Makes the output more aesthetically pleasing and orderly, can be removed
 		int killerror = kill(pid[i], SIGSTOP);
 		if(killerror == -1){
 			p1perror(1, "Failed to send SIGSTOP\n");
 		} else {
 			p1putstr(1, "Sent SIGSTOP\n");
 		}
 	}

 	for(i = 0; i < numprograms; i++){
		//Makes the output more aesthetically pleasing and orderly, can be removed
 		int killerror = kill(pid[i], SIGCONT);
 		if(killerror == -1){
 			p1perror(1, "Failed to SIGCONT\n");
 		} else {
 			p1putstr(1, "Sent SIGCONT\n");
 		}
 	}

 	int status;
 	for(i = 0; i < numprograms; i++){
 		 	waitpid(pid[i], &status, 0);
 		 	if(WIFEXITED(status)){
 		 		p1putint(1, pid[i]);
				p1putstr(1, ": exited\n");
 		 	} else {
 		 		i--;
 		 	}
 	}

 	int j;
 	for(i = 0; i < MAX_NUM_PROGRAMS; i++){
 		for(j = 0; j < NUM_ARGS; j++){
 			free(args[i][j]);
 		}
 		free(args[i]);
 	}
 	free(args);
 	free(pid);
 	for(i = 0; i < 20; i++){
 		free(program[i]);
 	}
 	free(program);
 	return 0;
 }
