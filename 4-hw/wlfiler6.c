#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"wl.h"

#define NUM_LETTERS	26
#define DEBUG		0


/*
 *	wordlist table module version 6
 *
 *	functions are:
 *			init_table()	- set up this module
 *			in_table(str)	- sees if word is in table
 *			insert(str,val) - insert value into table
 *			lookup(str)	- retrieve value
 *			update(str,val) - update value in table
 *			firstword()	- return first word in table
 *			nextword()	- return next word in table
 */

/*
 *	data structure for this unit:  a linked list of structs
 */

struct link {
		char	    *word;		/* the string	*/
		int	    value;		/* the count	*/
		struct link *next;		/* the next one	*/
	};

typedef struct link LINK;

//static int seek_to_word_link(struct link **, struct link **, char[]);

int show_table();


static LINK table[NUM_LETTERS] = {}; 		// initialize all to null 
static LINK *current_link;
static int current_array_index = 0;

static int get_char_index(char c) {

	if (DEBUG)
		printf("found index %d, for char %c \n", (int) c - 'a', c);

	return (int) c - 'a';	
}


/*
 *	init_table
 */

void
init_table()
{

	/* create an array of length 26 and initialize it 
	with head LINKs that point to NULL */
	int i = 0;
	while (i < NUM_LETTERS) {
		table[i++].next = NULL;
	}

	/* for iteration purposes */
	current_array_index = 0;

	if (DEBUG)
		printf("created a table of length %d\n", (int) ( sizeof(table) / sizeof(table[0]) ) ) ;

} 

/*
 *	int in_table(char str[])
 *  get the linked list for the first character in the word, search that 
 *  list for the string, assuming that they are in order.
 */

int in_table( char str[] )
{

	int char_index = get_char_index(str[0]);			 /* this should = 0 for 'a' */
	LINK *linkp = table[char_index].next; /* get the first link in the chain for that letter */

	if (DEBUG)
		printf("in_table: inside str[0] is %c str is %s linkp is %s \n", str[0], str, (linkp == NULL) ? "null" : "not null");

	if (DEBUG && linkp)
		printf("in_table: strcmp (linkp->word, str) = %d \n", strcmp( linkp->word, str ));


	while( linkp != NULL) {

		if ( strcmp( linkp->word, str ) == 0 ) {

			if (DEBUG) 
				printf("in_table: %s was found! \n", str);

			return YES ;

		} else if (strcmp( linkp->word, str ) < 0) {

			if (DEBUG) 
				printf("in_table: looking for %s \n", str);

			linkp = linkp->next;

		} else {

			// fall to return below
			break; 
		}
	}

	return NO;
}

/*
 *	int insert(str, val)
 *		purpose: add an entry to the table
 *		returns: NO if no more memory, YES if OK
 *		 method: add new node to head of list.  It's easy
 */

int
insert( char str[], int val )
{
	
	/* get the correct linked list for this letter */
	LINK *linkp = table[get_char_index(str[0])].next; 

	char *new_string; 
	LINK *new_link; 

	new_string = malloc(strlen(str) + 1); 		/* create new space in memory for string, 
													leave room for null char */
	if (new_string == NULL) { 			 		/* this happens if there's no memory free */
		return NO;
	}

	strcpy( new_string , str );		     		/* copy into new space */ 

	new_link = malloc(sizeof(LINK));	    /* create memory for new link	*/

	if ( new_link == NULL ) {					/* again check for memory overflow */

		free(new_string);						/* don't leak this memory */
		return NO;
	}

	// 
	new_link->word  = new_string;		
	new_link->value = val;
	new_link->next  = NULL;

	// first case: empty list 
	if (linkp == NULL) {

		table[get_char_index(str[0])].next = new_link;

		if (DEBUG)
			show_table();

		return YES;

	// if new_link->word preceeds the word at the front 
	//  of the list, make new_link the front of the list.	
	} else if ( strcmp(linkp->word, new_link->word) > 0 ) {

		new_link->next = table[get_char_index(str[0])].next;
		table[get_char_index(str[0])].next = new_link;
		
		if (DEBUG)
			show_table();

		return YES;	

	} else {

		/* seek to the link before where we want to insert */
		while ( linkp != NULL ) {

			/* if the next word in the list is null 
				then insert after current link */
			if (linkp->next == NULL) {

				if (DEBUG)
					printf("adding %s at the end of the list \n", linkp->word);
				break;
			
			/* if the next word in the link after this is 
				greater than the insert string, insert after current */
			} else if ( strcmp( linkp->next->word, str ) > 0 ) {

				if (DEBUG)
					printf("adding %s after %s and before %s \n", new_link->word, linkp->word, linkp->next->word);
				
				break;

			} else {

				linkp = linkp->next;
				continue;
			}
				
			printf("UNDEFINED BEHAVIOR: Infinite looping will occur\n");

		}

		new_link->next = linkp->next;
		linkp->next = new_link;

	}

	if (DEBUG)
		show_table();

	return YES;
}


#define TABLE_LEN       26
#define CHAR_BASE       'a'

/*
 * This function may help you debug your code.
 * It will print out the contents of the table
 * You can add it to the bottom of your wlfiler5.c file
 * and call it after each insert or update.
 */
int show_table()
{
        int          row;
        struct link *lp;

        for(row=0; row<TABLE_LEN; row++){
                printf("%3d [%c] [ | ]->", row, CHAR_BASE+row);
                for(lp=table[row].next;  lp ; lp = lp->next )
                        printf("[%s|%d]->", lp->word, lp->value);
                printf("NULL\n");
        }
    return 0;
}

/* 
 *	lookup (char *)
 *  input: a string that exists inside the word filed of a struct in the table
 *  output: the value associated with that word, or 0 if not found
 *  error: needs table defined in the class scope
 */
int lookup( char str[] )
{
	
	LINK *linkp;

	for( linkp = table[get_char_index(str[0])].next ; linkp ; linkp = linkp->next ) {

		if ( strcmp( linkp->word, str) == 0 ) {
			return linkp->value;
		}

	}
	return 0;					
}

/*
 * word_delete(char[])
 * input: a string that exists somewhere in the table 
 * output: none
 * error: fails silently if the string is not found in the table
 */
void word_delete(char word[]) {


	int char_index = get_char_index(word[0]);			 /* this should = 0 for 'a' */


	LINK *prev = &table[char_index];
	LINK *linkp = table[char_index].next; 				/* get the first link in the chain for that letter */

	while (linkp != NULL) {

		if ( strcmp( linkp->word, word ) == 0 ) {

			prev->next = linkp->next;
			free(linkp->word);
			free(linkp);

			//show_table();

			return;

		} else {

			if (linkp->next == NULL) {
				return;
			}

			prev = prev->next;
			linkp = linkp->next;
			continue;

		}

	}

	return;

}


/* 
 * update(char[], int) - update the value in the table for the given word to 
 *                       the specified integer value.
 * input: a char array (string) that exists in the table, and an int  
 * output: 1 if suceeded, 0 if not
 * errors: fails silently if not found
 */

int update( char str[], int val )
{
	LINK *linkp;

	for( linkp = table[get_char_index(str[0])].next ; linkp; linkp = linkp->next ) {

		if (DEBUG)
			printf("update: scanning for %s, linkp is %s\n", str, (linkp) ? "not null" : "null");

		if ( strcmp( linkp->word, str) == 0 ){  

			if (DEBUG)
				printf("update: found %s updating value to %d \n", str, val );

			linkp->value = val;	

			if (DEBUG)
				show_table();

			return YES;	

		} else {
			if (DEBUG)
				show_table();
		}
	}
	if (DEBUG)
		show_table();

	return 0;
}


/*
 * firstword() - get the first word alphbetically in the table, and set 
 *				 the global iterator to this value (for use with next word)
 * input: 
 *
 */
char * firstword()
{
	
	//int table_index;
	current_link = table[0].next;

	if (current_link != NULL) {
		return current_link->word;

	} else {

		// while array has more letters and head links for those letters point to NULL
		for (current_array_index = 0; current_array_index < NUM_LETTERS &&
			 table[current_array_index].next == NULL; current_array_index++) {

			if (DEBUG)
				printf("found nothing at %d\n", current_array_index);

		}

		// if we hit the end of the array and there's nothing there.
		if (current_link == NULL) {
			return NULL;
		}

		// set current link for iteration
		current_link = table[current_array_index].next;

		// return the word from this link
		return current_link->word;
	}

	// suppress warnings
	return NULL;
}

char * nextword()
{
	if (DEBUG)
		printf("entering the nextword function with %s\n", current_link->word );

	if ( current_link == NULL )
		return NULL;

	/* this will iterate through the links in a single letter's list */
	if (current_link->next) {
		
		current_link = current_link->next;
		return current_link->word;

	} else {

		/* search through the rest of the letters and see if there are any more */
		while ( ++current_array_index < NUM_LETTERS ) {

			/* is there anything in this letter's list, if so 
					make that the new current link */
			if (table[current_array_index].next) {

				current_link = table[current_array_index].next;

				if (DEBUG)
					printf("found %s at table[%d] \n", current_link->word, current_array_index );

				return current_link->word;
			
			} else {
				
				// iterate to next letter
				continue;
			} 
		}
	}

	return NULL;
}

/*
static int seek_to_word_link(struct link **prev, struct link **linkp, char word[]) {

	struct link *ptr_1 = *prev;
	struct link *ptr_2 = *linkp;

	// seek to the link before where we want to insert 
	while ( ptr_2 != NULL ) {

		// if the next word in the list is null then return null 
			
		if ( strcmp( ptr_2->word, word ) == 0 ) {

			//if (DEBUG)
				printf("found %s equaling %s after %s\n", word, ptr_2->word, ptr_1->word);
			
			return YES;

		} else {

			if (ptr_2->next == NULL) {
				return NO;
			}

			ptr_1 = ptr_1->next;
			ptr_2 = ptr_2->next;
			continue;
		}
			
		fprintf(stderr, "UNDEFINED BEHAVIOR: Infinite looping will occur\n");

	}

	return 0;

} */






