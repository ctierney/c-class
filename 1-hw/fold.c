#include <stdio.h>

/*
 * fold.c - reimplementation of the fold program in Unix.
 * 
 * input: text in the form of standard input 
 * output: text wrapped at the length of digits that are given.
 * errors: 
 */

#define	DEFAULT_WRAP		30 
#define LONG_WORD_MODE		1
#define SPACE_FOUND_MODE	2

int main() 
{

	int c;
	int count = 0;
	int array_size = 0;
	int wrap_length = DEFAULT_WRAP;
	char input_buffer[30]; 
	int mode = LONG_WORD_MODE;

	while ( (c = getchar() ) != EOF) {

		input_buffer[array_size] = c;
		array_size++;

		if (mode == LONG_WORD_MODE && count == wrap_length - 1) { 

			for (int i = 0; i < array_size; i++) {
                                putchar(input_buffer[i]);
                        }
			array_size = 0;
		}

		if (c == ' ') {

			mode = SPACE_FOUND_MODE;
			for (int i = 0; i < array_size; i++) {
                                putchar(input_buffer[i]);
                        }
                        array_size = 0;
		}
	

		/* add to an array, if a space is found or the array size reaches 30, 
		   flush the array and print a newline. reset count to the size of the array */ 

		/* */ 
		if (count == wrap_length - 1) {
			putchar('\n');
			count = 0;
		}

		count++;
	}

	return 0;
}
