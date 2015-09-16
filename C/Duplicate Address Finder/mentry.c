/*
Phillip Kriegel
kriegel
CIS 415 Project 0
mentry.c
This is my own work
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mentry.h"

/*Gets the input using a buffer to read in input, then allocate appropriate memory to place into strings*/
MEntry* me_get(FILE *fd){
	MEntry *entry;
	if((entry = malloc(sizeof *entry)) == NULL){
		return NULL;
	}

	char* firstLine = NULL;
	char* secondLine = NULL;
	char* thirdLine = NULL;
	char* buffer;

	if ((buffer = malloc(sizeof (char*) * 1024)) == NULL){
		return NULL;
	}
	
	size_t n = 0;

	int firstLineSuccess, secondLineSuccess, thirdLineSuccess;
	
	firstLineSuccess = getline(&firstLine, &n, fd);
	secondLineSuccess = getline(&secondLine, &n, fd);
	thirdLineSuccess = getline(&thirdLine, &n, fd);

	if ((firstLineSuccess == -1) | (secondLineSuccess == -1) | (thirdLineSuccess == -1)){
		free(entry);
		free(firstLine);
		free(secondLine);
		free(thirdLine);
		free(buffer);
		return NULL;
	}

	int size = 0;
	int i;
	for(i = 0; firstLine[i] != '\0'; i++){
		size++;
	}
	for(i = 0; secondLine[i] != '\0'; i++){
		size++;
	}
	for(i = 0; thirdLine[i] != '\0'; i++){
		size++;
	}

	if((entry -> full_address = malloc(sizeof (char) * size + 1 )) == NULL){
		return NULL;
	}
	//full = (char *) realloc(full, sizeof(firstLine) + sizeof(secondLine) + sizeof(thirdLine));
	strcpy(entry -> full_address, firstLine);
	strcat(entry -> full_address, secondLine);
	strcat(entry -> full_address, thirdLine);

	int house_number = 0;
	int x = sscanf(secondLine, "%d %*[^0-9]", &house_number);
	if(x == 0){
		house_number = 0;
		entry -> house_number = 0;
	} else {
		entry -> house_number = house_number;
	}

	sscanf(firstLine, "%[^,],", buffer);
	if((entry -> surname = malloc(sizeof (char *) * strlen(buffer))) == NULL){
		return NULL;
	}
	strcpy(entry -> surname, buffer);
	buffer[0] = '\0';


	if((entry -> zipcode = malloc(sizeof (char *) * 5)) == NULL){
		return NULL;
	}
	sscanf(thirdLine,  "%[^\t\n]", buffer);
	strcpy(entry -> zipcode, &buffer[strlen(buffer) - 5]);

	free(firstLine);
	free(secondLine);
	free(thirdLine);
	free(buffer);

	return entry;
}

/*Uses house number and every single character in zipcode and surname to determine hashvalue, making hash well distributed*/
unsigned long me_hash(MEntry *me, unsigned long size){
	char* hashString;
	if((hashString = malloc(sizeof (char) * 100)) == NULL){
		return 0;
	}
	strcpy(hashString, me -> surname);
	strcat(hashString, me -> zipcode);

	unsigned long hashval = 0;

	int i;
	for(i = 0; hashString[i] != '\0'; i++){
		hashval = *(hashString + i) + 100 * hashval;
	}

	hashval += me -> house_number;
	free(hashString);
	return hashval%size;
}

/*Prints out the offending address*/
void me_print(MEntry *me, FILE *fd){
	fprintf(fd, "%s", me -> full_address);
}

/*Compares to see if we find a duplicate*/
int me_compare(MEntry *me1, MEntry *me2){ 
	int surnameCmp = strcmp(me1 -> surname, me2 -> surname);
	if( surnameCmp != 0){
		return surnameCmp;
	}
	int zipCmp = strcmp(me1 -> zipcode, me2 -> zipcode);
	if( zipCmp != 0){
		return zipCmp;
	}
	if( me1 -> house_number < me2 -> house_number){
		return -1;
	} else if ( me1 -> house_number > me2 -> house_number){
		return 1;
	} else {
		return 0;
	}
}

/*Obliterates the list from memory, scattering its bits to the wind*/
void me_destroy(MEntry *me){
	free(me -> surname);
	free(me -> zipcode);
	free(me -> full_address);
	free(me);
}