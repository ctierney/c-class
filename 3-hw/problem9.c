#include <stdio.h>

main() {

  char *p;
  printf("The string \"Hello\" has the value %lu\n",
        (unsigned long)"Hello");

  p = "Hello";
  printf("The variable p has the value %lu\n", (unsigned long)p);
  
  printf("The value of \"Hello\"+1 is %lu\n",
             (unsigned long)("Hello"+1));

  p = "Hello" + 1;
  printf("The variable p now has the value %lu\n",
             (unsigned long)p);

  printf("p now has the address %lu\n",
             &p);

  printf("The length of p+1 is %d\n", strlen(p+1));

  /* problem 10 */ 

  putchar("abcde"[3]);

}
