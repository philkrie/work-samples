/*
 *	Rudimentary USPS
 *  Project 1, Part 3
 */

#include "p1fxns.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>

#define BUF_SIZE 100
#define WORD_BUF_SIZE 20
#define NUM_ARGS 10
#define MAX_NUM_PROGRAMS 100
#define QUANTUM 100	/* number of milliseconds */

char** program;
char*** args;
int deadprograms = 0;
int numprograms = 0;
int pid_index = 0;
int error;

typedef struct pid {
	int pidnumber;
	int status;
} PID;

PID** pidarray;

static void sigchld_handler () {
	pid_t pidnum;
	int status;
	while ((pidnum = waitpid(-1, &status, WNOHANG)) > 0) {
		if (WIFEXITED(status)) {
			int a = pid_index;
			while (1){
				if(pidarray[a] -> pidnumber == pidnum){
					pidarray[a] -> status = 0;
					break;
				} else {
					a = (a + 1)%numprograms;
				}
			}
			p1putint(1, pidnum);
			p1putstr(1, ": exited\n");
			deadprograms++;
		}
	}
}

int counter = 0;
void timer_handler() {
    kill(pidarray[pid_index] -> pidnumber, SIGSTOP);
    counter++;
    while(1){
    	pid_index = (pid_index + 1)%numprograms;
    	if(pidarray[pid_index] -> status == 1){
    		break;
    	} else {
    	}
    } 
    if(counter < numprograms)
    	kill(pidarray[pid_index] -> pidnumber, SIGUSR1);
    else
    	kill(pidarray[pid_index] -> pidnumber, SIGCONT);
    p1putstr(1, "Switching process to process: ");
    p1putint(1, pidarray[pid_index] -> pidnumber);
    p1putstr(1, "\n");
}

int USR1_received = 0;

void USR1_handler() {
	USR1_received++;
}

int main(){

	if (signal(SIGUSR1, USR1_handler) == SIG_ERR) {
		p1perror(1, "Unable to catch SIGUSR1");
        exit(1);
	}

	if (signal(SIGCHLD, sigchld_handler) == SIG_ERR){
		p1perror(1, "Unable to catch SIGCHLD");
        exit(1);
	}

	if (signal(SIGALRM, timer_handler) == SIG_ERR) {
        p1perror(1, "Unable to catch SIGALARM");
        exit(1);
    }

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

	if((pidarray = (PID**) malloc(sizeof(PID*) * MAX_NUM_PROGRAMS)) == NULL){
		p1putstr(1, "Failed to allocate pid array");
		exit(1);
	}

	int word_count;
	int line = 0;
	int index = 0;

 	while(p1getline(0, buffer, BUF_SIZE) != 0){
 		
 		index = p1strchr(buffer, '\n');
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

 		PID* pid;
 		
 		if((pid = malloc(sizeof *pid)) == NULL){
			p1putstr(1, "Failed to allocate PID struct");
			exit(1);
		}

 		pid -> status = 1;
 		pidarray[line] = pid;
 		pidarray[line] -> pidnumber = fork();
 		
 		if(pidarray[line] -> pidnumber == -1){
 			p1putstr(1, "Failed to create child");
 			exit(1);
 		}
 		
 		if (pidarray[line] -> pidnumber == 0){
			/* child branch */
			while (! USR1_received)
			sleep(1);
			execvp(program[line], args[line]);
		}
 		line++;
 	}

 	struct itimerval it_val;

 	it_val.it_value.tv_sec = QUANTUM / 1000;
    it_val.it_value.tv_usec = (1000 * QUANTUM) % 1000000;
    it_val.it_interval = it_val.it_value;
    
	error = kill(pidarray[0] -> pidnumber, SIGUSR1);
 	if(error == -1)
 	  p1perror(1, "Failed to send SIGUSR1");

 	if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
        p1perror(1, "Error calling setitimer()");
        _exit(1);
    }
 	
    while(deadprograms < numprograms){
    }

 	int j;
 	for(i = 0; i < MAX_NUM_PROGRAMS; i++){
 		for(j = 0; j < NUM_ARGS; j++){
 			free(args[i][j]);
 		}
 		free(args[i]);
 	}
 	free(args);
 	for(i = 0; i < MAX_NUM_PROGRAMS; i++){
 		free(pidarray[i]);
 	}
 	free(pidarray);
 	for(i = 0; i < 20; i++){
 		free(program[i]);
 	}
 	free(program);
 	return 0;
 }
