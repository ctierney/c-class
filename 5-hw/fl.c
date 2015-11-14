#include	<stdio.h>
#include	<stdlib.h>
#include	"fl.h"
#include	"ws13.h"
#include	<ctype.h>

/*
 *	formletter program version 1.0
 *
 *	usage: fl format < datafile
 *
 *	data comes from stdin, output goes to stdout
 */

#define 	READ_FIELD 	1 
#define 	READ_VALUE	2
#define		DEBUG		0
#define		ZERO		0
#define		FILE_COMPLETE	-1


static char	*myname ;		/* used by fatal() */
static int read_word(char *, int, char); 
static void reset_mode_and_counters(int *, char *, char *);

int main(int ac, char *av[])
{
	FILE *fpfmt;
	
	myname = *av;

	/*
	 * 	check that there is at least one arg: the format file
	 */

	if ( ac == 1 )
		fatal("usage: fl format [datafile..]","");

	/*
	 *	then try to open it
	 */

	if (  (fpfmt = fopen( av[1] , "r")) == NULL )
		fatal("Cannot open format file:", av[1]);

	/*
	 *	in full version, code to handle names of data files
	 *	on the command line will appear here
	 */

	/* ... process data from stdin ... */

	process(fpfmt, stdin);
	return 0;
}

void fatal(char *s1, char *s2)
/*
 *	fatal error handler
 *	purpose: print error message to stderr then exit
 *	input:   two strings that are printed 
 *	never returns
 */
{
	fprintf(stderr, "%s: %s%s\n",  myname, s1, s2 );
	exit(1);
}


int get_record(symtab_t *table, FILE *data) {

	// start with an empty table
	clear_table(table);
	show_table(table);

	//starting in read label mode
	int mode = READ_FIELD;
	int c = 0;
	int rv = YES; 

	char field[MAXFLD] = "";
	char value[MAXVAL] = "";
	char *field_p = field;
	char *value_p = value;

	while ( rv != NO ) {

		//show_table(table);

		if (mode == READ_FIELD) {

			if ( (rv = read_word(field_p, MAXFLD, ';')) == FILE_COMPLETE) {

				// if we're at the end of the file, reset and break out 
				reset_mode_and_counters(&mode, field_p, value_p);
				break;
			}

			if (DEBUG)
				printf("read field %s rv was %d\n", field_p, rv);

			mode = READ_VALUE;

		} else if (mode == READ_VALUE) {


			rv = read_word(value_p, MAXVAL, ';');
			//if ( (rv = read_word(value_p, MAXVAL, ';') == FILE_COMPLETE ) {
			// 	reset_mode_and_counters(&mode, field_p, value_p);
			// 	break;
			// }

			int ret_val;
			if ( (ret_val = insert(table, field, value)) == NO) {
				fatal("out of memory error while storing", field);
				return ret_val;
			}

			reset_mode_and_counters(&mode, field_p, value_p);

		}
	}

	printf("returning record\n");
	//show_table(table);

	if (rv == FILE_COMPLETE) {

		return NO;
	}

	return YES;
}

static void reset_mode_and_counters(int *mode, char *field, char *value) {

	// reset for next key value pair
	field[ZERO] = '\0';
	value[ZERO] = '\0';

	*mode = READ_FIELD;

}

/* 
 * 
 *
 * return: 0 if ok, 1 if end of line, -1 if EOF  
 */
static int read_word(char *target, int max_len, char delim) {
	
	if (DEBUG)
		printf("read_word: getting called \n");

	int count = 0;
	int c = 0	;

	while ( (c = getchar()) != EOF) {

		if ( count > max_len - 1) {

			if (DEBUG) 
				printf("truncating off %c\n", c);

			continue;

		} else if ( count == 0 && isspace(c) ) {

			if (DEBUG) 
				printf("removed a space");
			continue;

		} else if ( c == delim || c == '=' || c == '\n') {

			// add a trailing null
			target[count++] = '\0';
			if (DEBUG)
				printf("read_word: adding a trailing null and returning %s\n", target);

			if (c == '\n') {
				return NO;
			}

			return YES;

		} else {

			target[count++] = c;
		}
	}

	if (DEBUG)
		printf("caught EOF \n");

	return FILE_COMPLETE;
}

void mailmerge(symtab_t *table, FILE *fmt) {

	/* do stuff */

	return; 

}