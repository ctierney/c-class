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


int readline (char[], int);

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

		printf("debug: %s\n", line);

		/* normal case */
		if (mode == PROCESS) {

			/* if encounter a noprocess tag, enter no process mode */
			if (strcmp(line, NO_PROCESS_OPEN) == 0) {

				printf("debug: switching into noprocess mode.\n");

				mode = NOPROCESS;
				continue;

			/* if encounter an attributes tag, switch to attribute reading mode */	
			} else if (strcmp(line, ATTRIBUTES_OPEN) == 0) {

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

					char style_label[MAX_ATTRIBUTES_LEN] =" ";

					if (column_num < attr_counter) {
						strncpy(style_label, attributes[column_num], MAX_ATTRIBUTES_LEN - strlen(style_label));
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

				printf("debug: switching back to process mode.\n");

				mode = PROCESS;
				continue;
			} else {
				printf("%s\n", line);
			}

		/* attribute reading mode */
		} else if (mode == ATTRIBUTES) {

			if (strcmp(line, ATTRIBUTES_CLOSE) == 0) {
				
				printf("debug: switching to process mode\n");
				mode = PROCESS;
				continue;

			} else {

				printf("debug: adding %s as attribute %d\n", line, attr_counter);
				strncpy(attributes[attr_counter++], line, MAX_ATTRIBUTES_LEN);

			}

		}


	}

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

		if (ch == ' ') {
			continue;
		}
		rv++;

		if (ch == '\n') 
			break;
		str[i++] = ch;
	}

	str[i] = '\0';
	//printf("readline returning %s with length %d \n",str, i);
	return rv;
}



