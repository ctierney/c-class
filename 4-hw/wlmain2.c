#include	<stdio.h>
#include 	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	"wl.h"


#define		DEBUG	1
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

	//*buffer = '\0';

	//printf("strlen(buffer) = %d\n", (int) strlen(buffer) );

	//buffer = realloc(buffer, BUFLEN * 2);

	//printf("strlen(buffer) = %d\n", (int) strlen(buffer) );

	/* end test */
	//return 0;


	/* ... set up word filing module ... */

	//init_table();	

	/* ... read words and store them ... */
	/* was: scanf("%s", buf) */
	while ( (buffer = read_word(buffer, &buf_len)) != NULL ){

		printf("main: buf = %s, buf_len: %d\n", buffer, buf_len);

	}

	return 0;
}

char *
read_word(char *str, int *buffer_len) {

	int c; 
	int word_length = 0;
	static int eof_reached = 0;
	int rv = 0;

	str[0] = '\0';

	if (eof_reached == 1) {
		printf("read_word: eof_reached was %d\n", eof_reached);
		return NULL;
	}

	while ((c = getchar()) != EOF ) {

		printf("c was %c, buffer_len is %d, word_length is %d, isspace(c) = %d\n", c, *buffer_len, word_length, isspace(c));

		// fast forward comments 
		if (c == '#') {

			while ( (c = getchar()) != '\n') {
				// skip to the end of the line
				printf("skipping.. %c\n", c );
			}
			continue;
		}

		// filter out spaces, tabs, etc.
		if (isspace(c) == 0 && c != '\n') {

			// if the buffer isn't long enough to 
			// hold another character, double it 
			if ( (word_length + 1) > *buffer_len ) {

				printf("time to expand the array! before array address is %lu \n", str);

				str = expand_array(&str, buffer_len);

				printf("after expanding the array, word_length: %d, str: %s, strlen(str): %d, array address is %lu \n", word_length, str, (int) strlen(str), str );
				
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

	if (c == EOF ) {

		// if we have a word in the buffer, return it
		if (word_length > 0) {

			str[word_length++] = '\0'; 				// end it with a null char
			eof_reached = 1;
			return str;
		}

		printf("caught EOF getting ready to return\n");
		return NULL;
	}

	str[word_length++] = '\0';

	printf("word_length: %d, strlen(str): %d,  \n", word_length, (int) strlen(str) );

	return str; 

}

static char * expand_array(char **word, int *max_length) {

	printf("expanding array from %d to %d\n", *max_length, (*max_length * 2));

	*max_length = *max_length * 2;

	printf("got here %d \n", *max_length);
	*word = (char *) realloc(*word, *max_length);
	printf("after reallocating *word, word is %s\n", *word);


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
