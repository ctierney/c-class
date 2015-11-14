#include <stdio.h>

main() {
           char a[8];        /* an array  */
           char *p;          /* a pointer */
           printf("a is at %u\n", a);
           strcpy(a, "abcdefg");
           p = a;
           printf("a contains [%s] p=%u, p points to [%s]\n", a, p, p);
           /* use brackets */
           a[2] = 'X';
           p = a + 2;
           p[1] = 'Y';
           p++;
           printf("a contains [%s] p=%u, p points to [%s]\n", a, p, p);
           /* use stars */
           *a = 'Z';
           *(a+4) = 'T';
           *p = 'A';
           *(p+4) = 'Q';  /* this overwrites the \0 terminator */
           printf("a contains [%s] p=%u, p points to [%s]\n", a, p, p);
}
