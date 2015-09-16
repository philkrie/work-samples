/*
Phillip Kriegel
kriegel
CIS 415 Project 1
Rudimentary USPS, through part 4
usps.c
This is my own work
*/
 
#include <fcntl.h>
#include "p1fxns.h"
#include "usps.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>

#define BUF_SIZE 100 /*Maximum buffer sizes*/
#define WORD_BUF_SIZE 20
#define NUM_ARGS 100
#define MAX_NUM_PROGRAMS 100 /*This USPS can handle at most 100 programs*/
#define QUANTUM 100	/* number of milliseconds */

char** program;
char*** args;
int deadprograms = 0;
int numprograms = 0;
int pid_index = 0;

PID** pidarray;

static char *digits = "0123456789";
void itoa(char output[], int number){
    char buf[25];
    int i, n;
    if (number == 0) {
        buf[0] = '0';
        i = 1;
    } else {
        for (n = number, i = 0; n != 0; i++) {
            buf[i] = digits[n % 10];
            n /= 10;
        }
    }
    int j = 0;
    while (--i >= 0){
        output[j] = buf[i];
        j++;
    }
    output[j+1] = '\0';
}

char* strcat(char* dest, char *src)
{
    size_t i,j;
    for (i = 0; dest[i] != '\0'; i++)
        ;
        for (j = 0; src[j] != '\0'; j++)
            dest[i+j] = src[j];
    dest[i+j] = '\0';
    return dest;
}

void sigchld_handler () {
   	pid_t pidnum;
	int status;
	while ((pidnum = waitpid(-1, &status, WNOHANG)) > 0) {
		if (WIFEXITED(status)) {
			int a = pid_index;
			while (1){
				if(pidarray[a] -> pidnumber == pidnum){
					pidarray[a] -> status = 0;
					break;
				} else { a = (a + 1)%numprograms;}
			}
		    p1putint(1, pidnum);
			p1putstr(1, ": exited\n");
			deadprograms++;
		}
	}
}

void bigbrother(){
    char BUFFER[1024];
    int i;
    int j;
    int fd;
    int pid;
    char output[25] = "";
        for(i = 0; i < numprograms; i++){
        if(pidarray[i] -> status == 0){ //Find all live processes
           continue;
        }
        char* path;
        if ((path = (char*) calloc(25, sizeof(char*))) == NULL){
        	p1perror(1, "Failed to allocate path array");
		    exit(1);
        }
        pid = pidarray[i] -> pidnumber; //Retrieve PID
        itoa(output, pid);
        path = strcat(path, "/proc/");
        path = strcat(path, output);
        path = strcat(path, "/status");
        fd = open(path, O_RDONLY); //Open path to /proc/PID/status
        if(fd == -1){
            p1perror(1, "READ ERROR");
            exit(1);
        }
        p1getline(fd, BUFFER, 1024); //Read first line to get name
        int index = p1strchr(BUFFER, '\n');
 	    BUFFER[index] = '\0';
        p1putstr(1, "Process ");
        p1putint(1, pid);
        p1putstr(1, ": "); 
        p1putstr(1, BUFFER); //Gives us the process name
        p1getline(fd, BUFFER, 1024); //Read second line to get state
        index = p1strchr(BUFFER, '\n');
        BUFFER[index] = '\0';
        p1putstr(1, ", ");
        p1putstr(1, BUFFER); //Gives us the process state 
        for(j = 0; j < 11; j++){
            p1getline(fd, BUFFER, 1024); //Move forward 11 lines
        }                                //to get to VMSize       
        close(fd);
        index = p1strchr(BUFFER, '\n');
        BUFFER[index] = '\0';
        p1putstr(1, ", ");
        p1putstr(1, BUFFER); //Gives us the process size
        path[0] = '\0';
        path = strcat(path, "/proc/");
        path = strcat(path, output);
        path = strcat(path, "/io");
        fd = open(path, O_RDONLY); //Open path to /proc/PID/io
        if(fd == -1){
            p1perror(1, "READ ERROR");
            exit(1);
        }
        p1getline(fd, BUFFER, 1024); //Read first line to get read data
        index = p1strchr(BUFFER, '\n');
        BUFFER[index] = '\0';
        p1putstr(1, " ");
        p1putstr(1, BUFFER); //Gives us process read data
        p1getline(fd, BUFFER, 1024); //Read second line to get write data
        close(fd);
        index = p1strchr(BUFFER, '\n');
        BUFFER[index] = '\0';
        p1putstr(1, " ");
        p1putstr(1, BUFFER); //Gives us process write data
        p1putstr(1, "\n");
        path[0] = '\0'; 
        path = strcat(path, "/proc/");
        path = strcat(path, output);
        path = strcat(path, "/sched");
        fd = open(path, O_RDONLY); //Open path to /proc/PID/io
        if(fd == -1){
            p1perror(1, "READ ERROR");
            exit(1);
        }
        for(j = 0; j < 4; j++){
            p1getline(fd, BUFFER, 1024); //Read fourth line to get exec time data
        }
        close(fd);
        index = p1strchr(BUFFER, '\n');
        BUFFER[index] = '\0';
        p1putstr(1, BUFFER); //Gives us process exec time data
        p1putstr(1, "\n");   
        free(path);
        }  
   }

int counter = 0;
void timer_handler() {
    kill(pidarray[pid_index] -> pidnumber, SIGSTOP);
    counter++;
    int attempts = 0;
    while(1){
        attempts++;
    	pid_index = (pid_index + 1)%numprograms;
    	if(pidarray[pid_index] -> status == 1){
    		break;
    	} else if (attempts > numprograms){
            return;
    	}
    }
    /*If it is the first time signalling a process, we must send SIGUSR1 to
      let it know to begin execution. Otherwise, once we have started all
      processes we can go ahead and send SIGCONT*/
    if(counter < numprograms){
        if((kill(pidarray[pid_index] -> pidnumber, SIGUSR1)) == -1){
            p1perror(1, "Failed to send SIGUSR1");
        }
    }
    else if((kill(pidarray[pid_index] -> pidnumber, SIGCONT)) == -1){
            p1perror(1, "Failed to send SIGCONT");
        }
    p1putstr(1, "Switching process to process: ");
    p1putint(1, pidarray[pid_index] -> pidnumber);
    p1putstr(1, "\n");
    if(counter%4 == 0)
        bigbrother();
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
		p1perror(1, "Failed to allocate program array");
		exit(1);
	}

	if((args = (char***) calloc(MAX_NUM_PROGRAMS, sizeof(char**))) == NULL){
		p1perror(1, "Failed to allocate arg array");
		exit(1);
	}

	int i;
	for(i = 0; i < MAX_NUM_PROGRAMS; i++){
		if((args[i] = (char**) calloc(NUM_ARGS, sizeof(char*))) == NULL){
			p1perror(1, "Failed to allocate arg array");
			exit(1);
		}
	}

	if((pidarray = (PID**) calloc(MAX_NUM_PROGRAMS, sizeof(PID*))) == NULL){
		p1perror(1, "Failed to allocate pid array");
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

        if (numprograms == MAX_NUM_PROGRAMS){
            p1putstr(1, "Reach program limit, executing first 100");
            numprograms--;
            break;
        }
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
			p1perror(1, "Failed to allocate PID struct");
			exit(1);
		}

 		pid -> status = 1;
 		pidarray[line] = pid;
 		pidarray[line] -> pidnumber = fork();
 		
 		if(pidarray[line] -> pidnumber == -1){
 			p1perror(1, "Failed to create child");
 			exit(1);
 		}
 		
 		if (pidarray[line] -> pidnumber == 0){
			/* child branch */
			while (! USR1_received)
			sleep(1);
			if((execvp(program[line], args[line])) == -1){
                p1perror(1, "Failed to execute child program");
                _exit(1);
            }
		}
 		line++;
 	}
    
    /*Timer construct*/
 	struct itimerval it_val;

 	it_val.it_value.tv_sec = QUANTUM / 1000;
    it_val.it_value.tv_usec = (1000 * QUANTUM) % 1000000;
    it_val.it_interval = it_val.it_value;
    
    /*We send a signal the first process to start our USPS*/
 	if(kill(pidarray[0] -> pidnumber, SIGUSR1) == -1){
        p1perror(1, "Failed to send SIGUSR1");
    }
    
    /*We start our timer. Every 100 Milliseconds, it sends a signal
     that will tell the current process to stop, and either start or continue
     the next process in line */
 	if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
        p1perror(1, "Error calling setitimer()");
        exit(1);
    }
 	
    /*This while loop prevents the parent from finishing until
      all of the children have perished*/
    while(deadprograms < numprograms){
    }
    
    /*If we have made it, we clean up after ourselves*/
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
 	for(i = 0; i < MAX_NUM_PROGRAMS; i++){
 		free(program[i]);
 	}
 	free(program);
 	return 0;
 }
