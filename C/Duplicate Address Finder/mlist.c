/*
Phillip Kriegel
kriegel
CIS 415 Project 0
mlist.c
This is my own work, though inspiration for the hash table's structure was drawn 
from a stackoverflow post http://stackoverflow.com/questions/13052402/c-having-trouble-resizing-a-hash-table
*/

#include "mlist.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct mlistnode {
	struct mlistnode *next;
	MEntry *entry;
	int length;
} MListNode;

struct mlist {
	unsigned long size;
	MListNode **table;
};

/* ml_create - created a new mailing list */
MList *ml_create(void) {
	MList *p;

	if ((p = (MList *)malloc(sizeof(MList))) == NULL) {
		return NULL;
	}

	p -> size = 100;
	p -> table = NULL;

	if ((p -> table = malloc(sizeof (MListNode *) * (p -> size))) == NULL){
		return NULL;
	}

	int i;
	for(i = 0; i < (p -> size); i++) p->table[i] = NULL;

	return p;
}

/*ml_create_helper - creates a new mailing list to replace the old. Takes a size, unlike ml_create*/
static MList *ml_create_helper(unsigned long size){
		MList *new;

		if ((new = (MList *)malloc(sizeof(MList))) == NULL) {
			return NULL;
		}

		new -> size = size;
		new -> table = NULL;

		if((new -> table = malloc(sizeof (MListNode *) * (new -> size))) == NULL){
			return NULL;
		}

		int i;
		for(i = 0; i < (new -> size); i++) new->table[i] = NULL;

		return new;
}

/*ml_add_helper - adds ementry to a the list. Used when moving from the old table to the new table */
static int ml_add_helper(MList **ml, MEntry *me){
	MList *p;
	MListNode *q;

	p = *ml;
	unsigned int hashval = me_hash(me, p -> size);

	if ((q = (MListNode *)malloc(sizeof(MListNode))) == NULL)
		return 0;

	q->entry = me;

	if(p -> table[hashval] == NULL){
		q -> length = 1;
	} else {
		q -> length = (p -> table[hashval]) -> length + 1;
	}

	q->next = p->table[hashval];
	p->table[hashval] = q;
	return 1;
}

/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ml_add(MList **ml, MEntry *me) {
	MList *p;
	MListNode *q;

	p = *ml;
	unsigned int hashval = me_hash(me, p -> size);

	if (ml_lookup(p, me) != NULL)
		return 1;

	if ((q = (MListNode *)malloc(sizeof(MListNode))) == NULL)
		return 0;

	q->entry = me;

	if(p -> table[hashval] == NULL){
		q -> length = 1;
	} else {
		q -> length = (p -> table[hashval]) -> length + 1;
	}

	if( q -> length > 20){

		fprintf(stderr, "Length of a hash bucket has surpassed 20; resize required\n");
		fprintf(stderr, "Current hash length: %d\n", p -> size);
		fprintf(stderr, "Doubling to: %d\n", (p -> size) * 2);

		//create static ML_create() that takes size
		MList *new = ml_create_helper((p -> size) * 2);

		*ml = new;
		MListNode *next_q;

		/*add the entry that triggered the resize, can't forget about this one*/
		ml_add_helper(&new, q -> entry);
		free(q);

		int i;
		for(i = 0; i < p -> size; i++){
			for(q = p -> table[i]; q != NULL;){
				next_q = q->next;
				ml_add_helper(&new, q -> entry);
    			free(q);
    			q = next_q;
			}
		}
		free(p -> table);
		free(p);
		return 1;
	}

	q->next = p->table[hashval];
	p->table[hashval] = q;
	return 1;
}


/* ml_lookup - looks for MEntry in the list, returns matching entry or NULL */
MEntry *ml_lookup(MList *ml, MEntry *me) {
	MList *p;
	MListNode *q;

	p = ml;
	unsigned int hashval = me_hash(me, p -> size);
	for (q = p->table[hashval]; q != NULL; q = q->next)
		if (me_compare(me, q->entry) == 0)
			return q->entry;
		
	return NULL;
}

/* ml_destroy - destroy the mailing list */
void ml_destroy(MList *ml) {

	MListNode *q;

	int i;
	for(i = 0; i < ml -> size; i++){
		q = ml -> table[i];
		while (q != NULL) {
			MListNode *r = q->next;
			me_destroy(q->entry);
			free(q);
			q = r;
		}
	}
	free(ml -> table);
	free(ml);
}
