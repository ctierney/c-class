#include <stdio.h>
#include <string.h>

#define LINE_LEN			512

int readline (char[], int);

/* 
 * tt2ht1.c - convert space separated tables to html
 * 
 * input: a space delimited text input stream such as the output to many unix commands
 * output: neatly formatted html table wrapping the table 
 * errors: if the line is longer than 512 characters, the output will be truncated.
 */

int main()
{

	char line[LINE_LEN]; 
	int i;
	char space[2] = " ";
	char *token;

	/* open the table */
	printf("<table>\n");
	
	/* read in a line */ 
	while ( (i = readline(line, LINE_LEN)) != 0) {

		/* begin the table row */
		printf("\t<tr>\n");

		/* get a token */
		token = strtok(line, space);

		while (token != NULL) {

			printf("\t\t<td>%s</td> \n", token);

			/* get the next token */
			token = strtok(NULL, space);
		}

		/* end the table row */
		printf("\t</tr>\n");

	}

	/* close table */
	printf("</table>\n");

	return 0;
}

/*
 * readline ( char[] , int ) - reads a line from standard in and stores it in an array.
 * 
 * arguments: 	str[] - string to store the line in 
 * 				n     - max length of the string to read in 
 * 
 */
int readline (char str[], int n) {

	int ch, i, rv;
	i = rv = 0;

	while ((i < n - 1 ) && (ch = getchar()) != EOF)  {
		rv++;

		if (ch == '\n') 
			break;
		str[i++] = ch;
	}

	str[i] = '\0';
	//printf("readline returning %s with length %d \n",str, i);
	return rv;
}

