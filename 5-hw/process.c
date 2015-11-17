#include	<stdio.h>
#include	"fl.h"
#include	"ws13.h"

#define DEBUG 0

/**
 *	process(fmt, data)
 *
 *	Purpose: read from datafile, format and output selected records
 *	Input:   fmt 		- input stream from format file
 *		 data		- stream from datafile
 *	Output:  copied fmt to stdout with insertions
 *	Errors:  not reported, functions call fatal() and die
 *	history: 2012-11-28 added free_table (10q BW)
 **/
void process(FILE *fmt, FILE *data, char field_sep, char record_sep)
{
	symtab_t *tab;

	if ( (tab = new_table()) == NULL )
		fatal("Cannot create storage object","");

	while ( get_record(tab,data, field_sep, record_sep) != NO ) 	/* while more data	*/
	{
		//printf("table is: \n");
		//show_table(tab);
		mailmerge( tab, fmt );		/* merge with format	*/
		clear_table(tab);		/* discard data		*/
	}

	free_table(tab);			/* no memory leaks!	*/
}
