#include <stdio.h>
#include <string.h>

/*
 * problem 11
 * 
 * This is a small program to demonstrate iteration with 
 * pointers vs array indexes. 
 * 
 * @inputs: just call it with no arguments 
 * @outputs: it should print out this: 
 * using array indexes:
 * abcdefghijklmnopqrstuvwxyz
 * zyxwvutsrqponmlkjihgfedcba
 * using pointers:
 * abcdefghijklmnopqrstuvwxyz
 * zyxwvutsrqponmlkjihgfedcba
 * 
 */

char *strrev(char *s);
char *strrev_ptr(char *s);

int main() {

	char rev_string[] = "abcdefghijklmnopqrstuvwxyz";

	printf("using array indexes: \n");

	printf("%s\n", rev_string);
	char * ret_val = strrev(rev_string);
	printf("%s\n", ret_val);


	char rev_string_ptr[] = "abcdefghijklmnopqrstuvwxyz";

	printf("using pointers: \n");

	printf("%s\n", rev_string_ptr);
	char * ret_val_ptr = strrev_ptr(rev_string_ptr);
	printf("%s\n", ret_val_ptr);

	return 0;
}

/*
 * char *strrev(char *s) - reverse a string in place using array indexing
 *
 */ 
char *strrev(char *s) {

	int left = 0, right = strlen(s);
	right--; /* chomp off the ending null and leave it where it is */

	while (left < right) {

		char tmp = s[left];
		s[left] = s[right];
		s[right] = tmp;
		left++;
		right--;
	}

	return s;
}

/*
 * char *strrev_ptr(char *s) - reverse a string in place using pointers
 *
 */ 
char *strrev_ptr(char *s) {

	char *left = s, *right = s + strlen(s);

	right--; /* chomp off the ending null and leave it where it is */
	
	while (left < right) {

		char tmp = *left;
		*left= *right;
		*right = tmp;
		left++;
		right--;
	}

	return s;
}