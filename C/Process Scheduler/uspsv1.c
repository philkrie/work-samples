/*
 *	Rudimentary USPS
 *  Project 1, Part 1
 */

#include "p1fxns.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 100
#define WORD_BUF_SIZE 50
#define NUM_ARGS 10
#define MAX_NUM_PROGRAMS 100

int numprograms;
char** programs;
char*** args;
int* pid;
int size;
int i;

 int main(){

 	char buffer[BUF_SIZE];
    char word[WORD_BUF_SIZE];		

	if((programs = (char**) calloc(MAX_NUM_PROGRAMS, sizeof(char*))) == NULL){
		p1putstr(1, "Failed to allocate program array");
		exit(1);
	}

	if((args = (char***) calloc(MAX_NUM_PROGRAMS, sizeof(char**))) == NULL){
		p1putstr(1, "Failed to allocate arg array");
		exit(1);
	}

	for(i = 0; i < MAX_NUM_PROGRAMS; i++){
		if((args[i] = (char**) calloc(NUM_ARGS, sizeof(char*))) == NULL){
			p1putstr(1, "Failed to allocate arg array");
			exit(1);
		}
	}

	int numprograms = 0;
	int word_count;
	int line = 0;

 	while(p1getline(0, buffer, BUF_SIZE) != 0){
 		int index = p1strchr(buffer, '\n');
 		buffer[index] = '\0';
 		numprograms++;
 		if (numprograms > MAX_NUM_PROGRAMS){
 			p1putstr(1, "Max number of programs is 100, please input fewer. Executing first 100");
 			break;
 		}
 		word_count = 0;
 		index = 0;
 		while(1){
 			index = p1getword(buffer, index, word);
 			if (index == -1){
 				args[line][word_count] = NULL;
 				break;
 			}
 			else if(word_count == 0){
 				programs[line] = p1strdup(word);
 				args[line][word_count] = p1strdup(word);
 			} else {
 				args[line][word_count] = p1strdup(word);
 			}
 			word_count++;
 		}
 		line++;
 	}

 	if((pid = (int*) malloc(sizeof(int)*numprograms)) == NULL){
		p1putstr(1, "Failed to allocate pid array");
		exit(1);
	}

 	for(i = 0; i < numprograms; i++){
 		pid[i] = fork();
 		if(pid[i] == -1){
 			p1putstr(1, "Failed to create child");
 			exit(1);
 		}
 		if (pid[i] == 0){
 			execvp(programs[i], args[i]);
 		}
 	}
 

 	for(i = 0; i < numprograms; i++){
 		waitpid(pid[i], NULL, 0);
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
 		free(programs[i]);
 	}
 	free(programs);
 	return 0;
 }