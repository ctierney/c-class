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
#define		PERCENT				'%'
#define 	EQUAL_SIGN			'='


static char	*myname ;		/* used by fatal() */
static int read_field(FILE *,char *, int, char, char); 
static int read_value(FILE *,char *, int, char, char); 

static void reset_mode_and_strings(int *, char *, char *);
static void print_system_command(symtab_t *, char *);
static void store_record(symtab_t *, char *, char *);

int main(int ac, char *av[])
{
	FILE *fpfmt;
	myname = *av;
	char field_sep = ';';			/* default value */
	char record_sep = '\n';			/* default value */
	int process_std_in = 1;

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

	 int i;
	 for (i = 2; i < ac; i++) {

	 	if (av[i][0] == '-') {

	 		switch (av[i][1]) {

	 			case 'd':

	 				field_sep = av[i][2];
	 				break;

	 			case 'r':

	 				record_sep = av[i][2];
	 				break;
	 		}

	 	} else {

	 		// if it's a data file, process it
	 		FILE * datafile;
	 		if ( (datafile = fopen(av[i], "r")) != NULL ) {

	 			process(fpfmt,datafile, field_sep, record_sep);
	 			fclose(datafile);

	 			process_std_in = 0;

	 		} 
	 	}

	 }

	 if (process_std_in) {
	 	/* ... process data from stdin ... */
		process(fpfmt, stdin, field_sep, record_sep);
	 }

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

/*
 * mailmerge - given a table and format file, replace tokens
 *			in the file of the following formats:
 *			%fieldname% - replace with corresponding value in table 
 *			%!command%	- replace command with the result of that 
 *						  command on the system it's running on 
 * 			%%			- escaped percent sign.
 * 
 * inputs: table: a table with the name value pairs
 *			fmt:  a format file.
 */
void mailmerge(symtab_t *table, FILE *fmt) {

	/* start in read and print out mode */
	int mode = LOOKING_FOR_TOKEN; 
	int c;
	char field[MAXFLD] = "";
	int field_ctr = 0;

	while ( (c = fgetc(fmt)) != EOF ) {

		if (mode == LOOKING_FOR_TOKEN) {

			if (c == PERCENT) {

				mode = TOKEN_FOUND;
				continue;

			} else {
				putchar(c);
			}

		} else if (mode == TOKEN_FOUND) {

			// read field value 
			if ( c != PERCENT && (field_ctr < MAXFLD - 1)) {
				field[field_ctr++] = c;

			} else  {

				if (c == PERCENT) {

					// print the corresponding field, reset counter and field
					if (field_ctr > 0) {

						//terminate the field and lookup in table
						field[field_ctr++] = '\0';

						if (field[0] == '!') {
							print_system_command(table, &field[1]); /* skip over the ! */

						} else {

							char *result_val = lookup(table,field);

							if (result_val != NULL) {
								printf("%s", lookup(table,field));
							}
						}

					} else  {
						// was just an escaped %
						putchar(c);
					}
				} 

				field[0]='\0';
				field_ctr = 0;

				mode = LOOKING_FOR_TOKEN;
			}

		}
	}

	// rewind the fmt file to the beginning
	fseek(fmt, 0L, SEEK_SET);

	return; 
}

/*
 * print_system_command (table, command) - flush the buffer and print a system command
 * inputs:  table - table of name / value pairs 
 *			command - a pointer to a (string) command that should run with no problems 
 *    					in the unix shell
 * errors: if table or command are null
 */
static void print_system_command(symtab_t *table, char *command) {

	table_export(table); 	/* export table vals to env */
	fflush(stdout);			/* flush buffer to stdout 	*/
	system(command);		/* run command 				*/

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
int get_record(symtab_t *table, FILE *data, char field_sep, char record_sep) {

	int mode = READ_FIELD;								/* starting in read label mode */
	int rv = YES; 

	char field[MAXFLD] = "";
	char value[MAXVAL] = "";

	// while line has not been terminated
	while ( rv != NO ) {

		if (mode == READ_FIELD) {

			rv = read_field(data, field, MAXFLD, field_sep, record_sep);

			if ( rv == FILE_COMPLETE) {

				reset_mode_and_strings(&mode, field, value); 	/* end of the file, reset and break out */
				break;
			}
			mode = READ_VALUE;

		} else if (mode == READ_VALUE) {

			rv = read_value(data, value, MAXVAL, field_sep, record_sep); /* read a word into value field */
			store_record(table, field, value);							/* store field and value into table */
			reset_mode_and_strings(&mode, field, value);				/* reset field and value, set mode to READ_FIELD */
		}
	}

	if (rv == FILE_COMPLETE)
		return NO;

	return YES;
}

/* 
 * store_record (table, field, value) - stores a field=value pair in a table
 * inputs:	table: 	a symtab_t table to store values in.
 *			field:	a field name 
 *			value: 	corresponding value
 * errors:	will terminate the whole program if out of memory occurs.
 */
static void store_record(symtab_t *table, char *field, char *value) {

	int ret_val;
	// if there's no field name to look up by, there's no point storing anything
	if ( (ret_val = insert(table, field, value)) == NO) {
		fatal("out of memory error while storing", field);
		exit (ret_val);
	}	
}

/* reset_mode_and_strings - convenience function to reset field and value
 * 							and also set the mode to read field.
 * input: 	mode: pointer to int to receive READ_FIELD mode 
 * 		  	field: string to be reset to empty
 * 			value: string to be reset to empty
 */
static void reset_mode_and_strings(int *mode, char *field, char *value) {

	// reset for next key value pair
	field[ZERO] = '\0';
	value[ZERO] = '\0';

	*mode = READ_FIELD;

}

/* read_field - reads a word from a file stream 
 * 				strips off preceeding whitespace 
 *				terminates string on field_sep, record_sep, 
 *				or = 
 * inputs:	data: a file stream 
 *			target: pointer to a string where the word will be stored
 *			max_len: max_length of the WHOLE char * including the null terminator
 *			field_sep: separates name=value pairs in a record
 *			record_sep: separates records, (usually newline)
 *
 * return: 0 if ok, 1 if end of line, -1 if EOF  
 */
static int read_field(FILE *data, char *target, int max_len, 
						char field_sep, char record_sep) {
	int count = 0;
	int c = 0;


	while ( (c = fgetc(data)) != EOF) {


		if ( c == field_sep || 						/* these all terminate a word */
					c == EQUAL_SIGN || 
					c == record_sep ) {

			target[count++] = '\0'; 						/* add a trailing null */

			if (c == record_sep) {							/* ending on a record_separator */ 
				return NO;									/* means the record is complete */
			}
			return YES;										/* there is more on this line */

		} else if ( (count > max_len - 2)  ||						/* truncate extra chars */
			 (count == 0 && isspace(c)) ) {					/* strip off preceeding spaces */
			
			continue;

		} else {
			target[count++] = c;							/* this is where we actually read a word */
		}
	}

	return FILE_COMPLETE;
}

/* read_value - reads a word from a file stream 
 * 				strips off preceeding whitespace 
 *				terminates string on field_sep, record_sep
 * inputs:	data: a file stream 
 *			target: pointer to a string where the word will be stored
 *			max_len: max_length of the WHOLE char * including the null terminator
 *			field_sep: separates name=value pairs in a record
 *			record_sep: separates records, (usually newline)
 *
 * return: 0 if ok, 1 if end of line, -1 if EOF  
 */
static int read_value(FILE *data, char *target, int max_len, 
						char field_sep, char record_sep) {
	int count = 0;
	int c = 0;


	while ( (c = fgetc(data)) != EOF) {

		if ( c == field_sep || 						/* these all terminate a word */
				c == record_sep ) {

			target[count++] = '\0'; 						/* add a trailing null */

			if (c == record_sep) {							/* ending on a record_separator */ 
				return NO;									/* means the record is complete */
			}
			return YES;										/* there is more on this line */

		} else if ( (count > max_len - 2)  ||						/* truncate extra chars */
			 (count == 0 && isspace(c)) ) {					/* strip off preceeding spaces */
			continue;

		} else {
			target[count++] = c;							/* this is where we actually read a word */
		}
	}
	
	return FILE_COMPLETE;
}


