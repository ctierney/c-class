#include <stdio.h>

/*
 * fold.c - reimplementation of the fold program in Unix.
 * 
 * input: text in the form of standard input 
 * output: text wrapped at the length of digits that are given.
 * errors: 
 */

#define	DEFAULT_WRAP		30 

int readstring (char[], int);

int main() 
{

	int wrap_length = DEFAULT_WRAP;
	int word_size = 0;
	int current_line = 0;
	char input_buffer[30]; 
	int i;


	/* read words off the standard input */
	while ( ( word_size = readstring(input_buffer, wrap_length ) ) != 0) {

		/* if the word doesn't fit in this line, put a newline */
		if (current_line + word_size > wrap_length) {
			putchar('\n');
			current_line = 0;
		}

		/* output the word */
		for (i = 0; i < word_size; i++) {

			/* handle newline */
			if (input_buffer[i] == '\n') {
				putchar(input_buffer[i]);
				current_line = 0;
			} else {
				putchar(input_buffer[i]);
				current_line++;
			}
			
		}

	}

	return 0;
}

/*  readsting (char[], int) -- reads a word from standard input (source: similar to readline.c in our packet.)
	If the word being read is longer than "length", we will just return the array filled with chars.
*/
int readstring (char string_buffer[], int length) 
{

	int i = 0;
	int ret_val = 0; 
	int c;

	/* read until you see a space, then return */
	while (i < length && ( ( c = getchar() ) != EOF) ){

			ret_val++;
			string_buffer[i++] = c;

			if (c == ' ') {
				return ret_val;
			}
	}

	/* should only happen if word is over 30 chars or EOF is reached */
	return ret_val;

}


