#include	<stdio.h>
#include	<stdlib.h>
#include	"fl.h"
#include	"ws13.h"
#include	<ctype.h>
#include	<string.h>

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
#define		LOOKING_FOR_TOKEN	3
#define		TOKEN_FOUND			4
#define		LOOP	1


static char	*myname ;		/* used by fatal() */
static int read_word(FILE *,char *, int, char); 
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


void mailmerge(symtab_t *table, FILE *fmt) {

	/* start in read and print out mode */
	int mode = LOOKING_FOR_TOKEN; 
	int c;
	char field[MAXFLD] = "";
	int field_ctr = 0;

	while ( (c = fgetc(fmt)) != EOF ) {

		if (mode == LOOKING_FOR_TOKEN) {

			if (c == '%') {
				
				mode = TOKEN_FOUND;
				continue;

			} else {
				putchar(c);
			}

		} else if (mode == TOKEN_FOUND) {

			if ( c != '%' && (field_ctr < MAXFLD - 1)) {

				field[field_ctr++] = c;

			} else  {

				if (c == '%') {

					// print the corresponding field, reset counter and field
					if (field_ctr > 0) {

						//terminate the field and lookup in table
						field[field_ctr++] = '\0';

						if (field[0] == '!') {

							table_export(table);
							fflush(stdout);
							char *cmd_ptr = &field[1];
							system(cmd_ptr);
						} else {
							printf("%s", lookup(table,field));
						}

					} else  {
						// was just an escaped %
						putchar(c);
					}
				} else 

				field[0]='\0';
				field_ctr = 0;

				mode = LOOKING_FOR_TOKEN;
			}

		}
	}
	return; 
}

/*
 * get_record - reads a name / value pair and stores it in 
 * 				the table passed to it.
 * inputs: 	table - pointer to a symtab_t type table 
 *			data  - pointer to a file with name / value pairs separated by an 
 *					equals sign and terminated by a delimiter, one record per line. 
 * returns: YES if there is more data in the file, NO if the file has reached it's end.
 * errors: if field / value separators are not '=' this will not work.
 */
int get_record(symtab_t *table, FILE *data) {

	//starting in read label mode
	int mode = READ_FIELD;
	int rv = YES; 

	char field[MAXFLD] = "";
	char value[MAXVAL] = "";
	char *field_p = field;
	char *value_p = value;

	// while line has not been terminated
	while ( rv != NO ) {

		if (mode == READ_FIELD) {

			if ( (rv = read_word(data, field_p, MAXFLD, ';')) == FILE_COMPLETE) {

				// if we're at the end of the file, reset and break out 
				reset_mode_and_counters(&mode, field_p, value_p);
				break;
			}
			mode = READ_VALUE;

		} else if (mode == READ_VALUE) {

			rv = read_word(data, value_p, MAXVAL, ';');

			int ret_val;
			// if there's no field name to look up by, there's no point storing anything
			if ( strlen(field) > 0 && (ret_val = insert(table, field, value)) == NO) {
				fatal("out of memory error while storing", field);
				return ret_val;
			}
			reset_mode_and_counters(&mode, field_p, value_p);
		}
	}

	if (rv == FILE_COMPLETE)
		return NO;

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
static int read_word(FILE *data, char *target, int max_len, char delim) {
	
	if (DEBUG)
		printf("read_word: getting called \n");

	int count = 0;
	int c = 0	;

	while ( (c = fgetc(data)) != EOF) {

		if ( count > max_len - 1) {

			if (DEBUG) 
				printf("truncating off %c\n", c);

			continue;

		} else if ( count == 0 && isspace(c) ) {

			if (DEBUG) 
				printf("removed a space\n");
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


