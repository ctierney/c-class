
#include <stdio.h>

char t[3] = "hi";


int main() {

	int x , y[4] = { 71, 181, 30, 131 } ; char a[30] = "pointers store addresses."; int *q;
	char *p,*s;
	int **r;
              
	p = a + 4;
	q = &y[0];
	s = &x;  // warning because x is an int and s is a char
	*s = '0'; // set the front bit of the value of x
	x = 44;  // *s gets overwritten, but may not change anything 
	r = &q;
	*q = q[2] + --x;

	/* write code here to print out values and locations of all vars */	

	printf("value of t[0] is %lu\n", t[0]);
	printf("address of t[0] is %lu\n", &t[0]);

	printf("value of t[1] is %lu\n", t[1]);
	printf("address of t[1] is %lu\n", &t[1]);

	printf("value of t[2] is %lu\n", t[2]);
	printf("address of t[2] is %lu\n", &t[2]);

	printf("value of t[3] is %lu\n", t[3]);
	printf("address of t[3] is %lu\n", &t[3]);



	printf("address of t is %lu\n", &t);
	printf("value of t is %lu\n", t);
	
	printf("address of x is %lu\n", &x);
	printf("value of x is %d\n", x);
	//printf("*x is %d\n", *x);

	printf("address of y is %lu\n", &y);
	printf("value of y is %lu\n", y);
	printf("*y is %d\n", *y);


	// 30 + 43 

	int i;
	for (i = 0; i < 4; i++) {

			printf("value of y[%d] is %d\n", i, y[i]);
			printf("address of y[%d] is %lu\n", i, &y[i]);

	}

	printf("address of a is %lu\n", &a);
	printf("value of a is %d\n", a);
	printf("value of *a is %c\n", *a);



	int j;
	for (j = 0; j < 30; j++) {

			printf("value of a[%d] is %c\n", j, a[j]);
			printf("value of a[%d] is %lu\n", j, a[j]);
			printf("address of a[%d] is %lu\n", j, &a[j]);
	}	

 	printf("address of q is %lu\n", &q);
	printf("value of q is %lu\n", q);
	printf("value of *q is %d\n", *q);


	printf("address of p is %lu\n", &p);
	printf("value of p is %lu\n", p);
	printf("p points to %c\n", *p);
	printf("address of where p points to %lu\n", &*p);

	printf("address of s is %lu\n", &s);
	printf("value of s is %lu\n", s);
	printf("*s should be 43: %d\n", *s);

	printf("address of r is %lu\n", &r);
	printf("value of r is %lu\n", r);
	printf("value of *r is %lu\n", *r);
	printf("value of **r is %d\n", **r);



}