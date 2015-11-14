#include <stdio.h>
#include <string.h>


int main() {

	char str1[10] = "abcdefghi";
	char str2[10] = "jklmnopqr";
	char *str3 = malloc (sizeof(str1) + sizeof(str2) + 1);

	char *d = strchr(str1, 'd');

	printf("strchr found %c\n", *d);

	str3 = strcat(str3, str1);
	str3 = strcat(str3, str2);

	printf("str3 = %s\n", str3);

	printf("strchr(str1, str2) = %d \n", strcmp(str1,str2));

	// strcpy 
	printf("strcpy(str1,str2) = %s\n", strcpy(str1,str2));

	char str4[10] = "abcdhighi";
	char str5[10] = "jklmnopqr";	

	char *needle = "hi";

	char *result = strstr(str4, needle);
	printf("result was %s\n", result);



	exit(0);
}