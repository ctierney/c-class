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



/*
 * the list has a dummy link at the start.  The list runs
 * from that one
 */


struct link table[NUM_LETTERS]; 

struct link head;		/* dummy node at head of list	*/
struct link *current_link;	/* for list traversal		*/



static int get_char_index(char c) {

	if (DEBUG)
		printf("found index %d, for char %c", (int) c - 'a', c);
	return (int) c - 'a';	
}


/*
 *	init_table
 */

void
init_table()
{
	/* head.next = NULL ; */ 

	/* create an array of length 26 and initialize it with head LINKs */
	int i = 0;
	while (i < 26) {
		table[i++].next = NULL;
	}

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
	struct link *linkp = table[char_index].next; /* get the first link in the chain for that letter */

	while( linkp != NULL && strcmp( linkp->word, str ) < 0 ) {

		if ( strcmp( linkp->word, str ) == 0 )
			return YES ;
		else
			linkp = linkp->next ;
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
	head = table[get_char_index(str[0])]; 
	struct link *linkp = head.next; /* change this to current_link in the global namespace to implement caching */ 

	while ( linkp != NULL ) {

		/* if the next word in the list is greater than the insert string, 
			then insert after current string */
		if (linkp->next == NULL || strcmp( linkp->next->word, str ) > 0 ) {
			break;
		}

		linkp++;
	}

	char		*newstr ;
	struct link	*newlink;

	newstr = malloc( 1 + strlen( str ) );	/* get memory for str	*/
	if ( newstr == NULL )			/* or die		*/
		return NO;
	strcpy( newstr, str );			/* copy to mem		*/
	newlink = malloc(sizeof(struct link));	/* get mem for link	*/
	if ( newlink == NULL )			/* or die		*/
		return NO;
	newlink->word  = newstr;		/* put str in struct	*/
	newlink->value = val ;			/* put val in struct	*/
	newlink->next  = linkp->next;		/* attach list to link	*/
	linkp->next      = newlink;		/* make head pt to link */
	return YES;
}

/*
 *	int lookup( str )
 */
int
lookup( char str[] )
{
	struct link *linkp;

	for( linkp = head.next ; linkp ; linkp = linkp->next )
		if ( strcmp( linkp->word, str) == 0 )   /* if found	 */
			return linkp->value;		/* ret value     */
	return 0;					/* not found     */
}

/*
 * 	int update( str, val )
 */

int
update( char str[], int val )
{
	struct link *linkp;

	for( linkp = head.next ; linkp ; linkp = linkp->next )
		if ( strcmp( linkp->word, str) == 0 ){  /* if found	*/
			linkp->value = val;		/* update	*/
			return YES;			/* and go	*/
		}
	return 0;					/* not found     */
}

/*
 *	char *firstword()
 */

char *
firstword()
{
	current_link = head.next ;
	return nextword();
}

/*
 *	char *nextword()
 */

char *
nextword()
{
	char *ret_val;

	if ( current_link == NULL )
		return NULL;
	ret_val = current_link->word;
	current_link = current_link->next;
	return ret_val;
}
