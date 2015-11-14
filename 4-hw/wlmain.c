#include	<stdio.h>
#include 	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	"wl.h"


#define		DEBUG	0
/*
 *	wordlist	main module
 *
 *	program reads words from standard input until EOF
 *	then prints all words it saw with the number of times
 *	each word appeared.  Order is order of appearance.
 *
 *	calls functions in a filer module to store and retrieve
 *	the words.
 *
 *	history: modified 11.11.00 to answer all -Wall warnings
 */

/*
 *	definitions and declarations are in wl.h
 */

void convert_to_lower_case(char *);

char * read_word(char *, int *);
static char * expand_array(char **, int *);

int
main()
{

	int 	buf_len = BUFLEN;
	//char	buf[buf_len], *wordptr;
	char	*wordptr;

	//buf[0] = '\0';

	char * buffer = calloc(BUFLEN, sizeof(char));

	/* ... set up word filing module ... */
	init_table();	

	/* ... read words and store them ... */
	/* was: scanf("%s", buf) */
	while ( (buffer = read_word(buffer, &buf_len)) != NULL ){

		if (DEBUG)
			printf("buf = %s, buf_len: %d\n", buffer, buf_len);

		convert_to_lower_case( buffer );

		if ( in_table( buffer ) == YES ) {

			if (DEBUG)
				printf("main: found %s in table with a value of %d ", buffer, lookup( buffer ));

			update( buffer, 1 + lookup( buffer ) );

		} else if ( insert( buffer, 1 ) == NO ){
			fprintf(stderr,"wordfreq: out of memory\n");
			exit(1);
		}
	}

	/* ... move cursor down the table printing out results */
	if (DEBUG)
		printf("printing the results starting with %s \n", firstword());
	
	for( wordptr = firstword() ; wordptr != NULL; wordptr = nextword() )
		printf("%5d\t%s\n", lookup( wordptr ), wordptr );

	//char hello[] = "hello";
	//word_delete(hello);

	return 0;
}


char *
read_word(char *str, int *buffer_len) {

	int c; 
	int word_length = 0;
	static int eof_reached = 0;

	str[0] = '\0';

	if (eof_reached == 1) {

		if (DEBUG)
			printf("read_word: eof_reached was %d\n", eof_reached);

		return NULL;
	}

	while ((c = getchar()) != EOF ) {

		if (DEBUG)
			printf("c was %c, buffer_len is %d, word_length is %d, isspace(c) = %d\n", c, *buffer_len, word_length, isspace(c));

		// filter out spaces, tabs, etc.
		if (isspace(c) == 0 && c != '\n') {

			// if the buffer isn't long enough to 
			// hold another character, double it 
			if ( (word_length + 1) > *buffer_len ) {

				str = expand_array(&str, buffer_len);

				if (str == NULL) {
					fprintf(stderr,"read_word: out of memory\n");
					exit(1);
				}
			}

			str [word_length++] = c;
		
		// if it is a space, tab, or newline
		} else {

			// if we have a word in the buffer, return it
			if (word_length > 0) {
				break;

			// if the buffer is empty, keep looking for a word.	
			} else {
				continue;
			}
			
		}
	}

	if (c == EOF) {

		// if we have a word in the buffer, return it
		if (word_length > 0) {

			str[word_length++] = '\0'; 				// end it with a null char
			eof_reached = 1;
			return str;
		}

		if (DEBUG)
			printf("caught EOF getting ready to return\n");

		return NULL;
	}

	str[word_length++] = '\0';

	if (DEBUG)
		printf("word_length: %d, strlen(str): %d,  \n", word_length, (int) strlen(str) );

	return str; 

}

static char * expand_array(char **word, int *max_length) {

	if (DEBUG)
		printf("expanding array from %d to %d\n", *max_length, (*max_length * 2));

	*max_length = *max_length * 2;

	*word = (char *) realloc(*word, *max_length);

	if (*word == NULL) {
		fprintf(stderr, "ERROR: out of memory\n");
		return NULL;
	} 

	return *word;
}

/*
 * this function converts any string to all lower-case
 * letters.  Right now it is not being used since
 * the script that calls this program converts the text
 * anyway.
 */

void
convert_to_lower_case( char *str )
{
	while( *str )
	{
		*str = tolower( (int) *str );
		str++;
	}
}
