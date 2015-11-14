#include <stdio.h>

int main() 
{

   int x;
   int a[] = { 6, 5, 4, 3, 1 , 0};
   int *p = a ;

   // a: x = *p;
   // b: x=p[3];
   // c: x=++p[3];
   // d: x=*++p;
   // e: x=++*p;
   // f: x=*p++;
   // g: x=(*p)++;
   x=p[*(p+2)];

   printf("x = %d\n", x);
   printf("p points to: %d\n", *p);

   printf("a: { ");
   for (int i = 0; i < 6; i++ ) {

   		printf("%d", a[i]);

   		if (i < 5) {
   			printf(", ");
   		}

   }

   printf("} \n");

}