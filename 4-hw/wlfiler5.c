#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"wl.h"

/*
 *	wordlist table module version 4
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

struct link head;		/* dummy node at head of list	*/
struct link *current_link;	/* for list traversal		*/

/*
 *	init_table
 */

void
init_table()
{
	head.next = NULL ;
}

/*
 *	int in_table(char str[])
 */

in_table( char str[] )
{
	struct link *linkp = head.next ;

	while( linkp != NULL )
		if ( strcmp( linkp->word, str ) == 0 )
			return YES ;
		else
			linkp = linkp->next ;
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
	newlink->next  = head.next;		/* attach list to link	*/
	head.next      = newlink;		/* make head pt to link */
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
