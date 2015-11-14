#include <stdio.h>

int main() 
{

    int a[] = {  4,  10, 4, 3, 6, 15 };


    printf("PROBLEM 5\n");
    
    printf("a: a[2] = %d\n", a[2]);
    printf("b: *(a + 2) %d\n", *(a + 2));
    printf("c: a[4]-a[2] %d\n", a[4] - a[2]);
    printf("d: a[a[4] - 2] %d\n", a[a[4] - 2]);
    printf("e: (a+10)[-8] %d\n", (a+10)[-8]);

    // problem 6 
    printf("PROBLEM 6\n");

    printf("a: %d\n", *a);
    printf("b: *(a+3) %d\n", *(a + 3));
    printf("c: (a + *a)[*a + a[2]] %d\n", (a + *a)[*a + a[2]]);
    printf("d: (a+4)[-2] %d\n", (a+4)[-2]);
    printf("e: *(a-10) %d\n", *(a-10));
 



}