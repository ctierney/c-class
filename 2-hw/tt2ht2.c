#include <stdio.h>
#include <string.h>

#define PROCESS				1
#define NOPROCESS			2
#define ATTRIBUTES			3
#define MAX_LINE_LEN		512
#define MAX_ATTRIBUTES		16
#define MAX_ATTRIBUTES_LEN	32
#define NO_PROCESS_OPEN		"<noprocess>"
#define NO_PROCESS_CLOSE	"</noprocess>"
#define ATTRIBUTES_OPEN		"<attributes>"
#define ATTRIBUTES_CLOSE	"</attributes>"
#define DEBUG_ON			0


int readline (char[], int);

/* tt2ht2 - convert a space separated table into a html table
 * 
 * inputs: 	a space-separated table like a lot of unix utilities
 *			- accepts <noprocess> blocks which are just streamed directly to output (up to 512 chars)
 *			- accepts <attributes> blocks which are a list of newline-separated name value pairs which are 
 *				blindly copied into the td column attributes in order.
 * outputs: the middle of an html table without the table beginning an end tags
 * errors: 	should handle most cases gracefully, truncates lines of text over 511 chars and attributes 
 * 			over 31 chars. DOES NOT handle overlapping tags. Anything in a noprocess block will be ignored.
 */

int main() {

	int i = 0;
	int attr_counter = 0;

	char line[MAX_LINE_LEN];
	char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTES_LEN];
	int mode = PROCESS;
	char *token;
	int column_num = 0;
	char space[2] = " ";


	while ( (i = readline(line, MAX_LINE_LEN)) != 0) {

		if (DEBUG_ON)
			printf("debug: %s with length %d \n",line, (int)strlen(line));

		/* normal case */
		if (mode == PROCESS) {

			/* if encounter a noprocess tag, enter no process mode */
			if (strcmp(line, NO_PROCESS_OPEN) == 0) {

				if (DEBUG_ON)
					printf("debug: switching into noprocess mode.\n");

				mode = NOPROCESS;
				continue;

			/* if encounter an attributes tag, switch to attribute reading mode */	
			} else if (strcmp(line, ATTRIBUTES_OPEN) == 0) {

				if (DEBUG_ON)
					printf("debug: switching to attributes mode \n");

				attr_counter = 0;
				mode = ATTRIBUTES;
				continue; 
			
			/* convert tables to html */
			} else {

				column_num = 0;

				/* begin the table row */
				printf("\t<tr>\n");

				/* get a token */
				token = strtok(line, space);

				while (token != NULL) {

					char style_label[MAX_ATTRIBUTES_LEN];

					/* copy the attribute into the style label, 
						leaving room for the final \0 terminator
						adding a prepended space for readability */
					if ( column_num < attr_counter && strlen(attributes[column_num]) ) {

						strcpy(style_label, " ");
						strncat(style_label, attributes[column_num], 
							MAX_ATTRIBUTES_LEN - (strlen(style_label) + 1));
					}

					printf("\t\t<td%s>%s</td> \n",style_label,token);

					/* get the next token */
					token = strtok(NULL, space);
					column_num++;
					style_label[0] = '\0';
				}

				/* end the table row */
				printf("\t</tr>\n");
			}

		/* noprocess mode */ 
		} else if (mode == NOPROCESS) {

			if (strcmp(line, NO_PROCESS_CLOSE) == 0) {
		
				if (DEBUG_ON)
					printf("debug: switching back to process mode.\n");

				mode = PROCESS;
				continue;
			} else {
				printf("%s\n", line);
			}

		/* attribute reading mode */
		} else if (mode == ATTRIBUTES) {

			if (strcmp(line, ATTRIBUTES_CLOSE) == 0) {
				
				if (DEBUG_ON)
					printf("debug: switching to process mode\n");

				mode = PROCESS;
				continue;

			} else {

				if (DEBUG_ON)
					printf("debug: adding %s as attribute %d\n", line, attr_counter);

				strncpy(attributes[attr_counter++], line, MAX_ATTRIBUTES_LEN);

			}
		}
	}
	return 0;
}

/*
 * readline ( char[] , int ) - reads a line from standard in and stores it in an array.
 *							truncates strings after max_length - 1 and ignores the rest of the line.
 *
 * NB: This function strips whitespace from the beginning of a line. I decided to leave this in
 *      because I like it, but, it's a little weird because it's only beginning whitespace. I 
 * 		did this because the example in the HW had some whitespace before the <attributes> and
 * 		<noprocess> tags. 
 * 
 * arguments: 	str[] - string to store the line in 
 * 				n     - max length of the array to be read  (512 in this case), 
 *						string to read in max will be n - 1 (511 in this case)
 * 
 */
int readline (char str[], int n) {

	int ch, i, rv;
	i = rv = 0;

	/* initialize to the empty string */
	str[0] = '\0';

	while ( (ch = getchar()) != EOF)  {
		rv++;

		/* strip off beginning whitespace */
		if (i == 0 && ch == ' ') 
			continue;

		/* stop at new line */
		if (ch == '\n') 
			break;

		/* honor max length */
		if (i < n - 1 )
			str[i++] = ch;
	}

	/* if the last char in the array isn't \0, add one */
	if (i > 0 && str[i-1] != '\0')  						/* max length is handled above */
		str[i] = '\0';

	if (DEBUG_ON)
		printf("debug: readline returning %s with string length %d and array length %d \n",
			str, (int)strlen(str), i);

	return rv;
}



