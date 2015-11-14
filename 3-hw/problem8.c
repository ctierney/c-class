#include <stdio.h>

int set_squares(int[], int);

int main() 
{

	int square_array[10];
	int return_value; 

	return_value = set_squares(square_array, 10);

	for (int j = 0; j < 10; j++) {

		printf("%d\n", square_array[j]);
	}

	printf("size of the retuned array was %i \n", return_value);

	return 0;

}
int set_squares(int squares[], int n)   /* create a table of squares of ints */
{
	//int *squares[n];
	int i = 0;	

	for(i=0; i<n; i++)
    	squares[i] = i*i;

    return i;
 }