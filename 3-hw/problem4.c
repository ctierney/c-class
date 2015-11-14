#include <stdio.h>

int main() {

    char n[4][10] = { "ann", "bob", "carol", "dave" };
    char *p1, *p2;
    p1 = n[2];
    p2 = n + 2;
    printf("n is %lu, n[0] is %lu, n[0][0] is %lu\n",
          (unsigned long)n, (unsigned long)n[0], (unsigned long)n[0][0]);
    printf("(n+1) is %lu, (n+1)[0] is %lu, (n+1)[0][0] is %lu\n",
               (unsigned long)(n+1), (unsigned long)(n+1)[0],
               (unsigned long)(n+1)[0][0]);
    printf("p1 is %lu, p1[0] is %lu\n",
               (unsigned long)p1, (unsigned long)p1[0]);
    //printf("p1[0][0] is %lu\n", (unsigned long)p1[0][0]);
    printf("p2 is %lu, p2[0] is %lu\n", (unsigned long)p2, (unsigned long)p2[0]);
    //printf("p2[0][0] is %lu\n", (unsigned long)p2[0][0]);

    printf("address of p1 and p2 are %lu, %lu \n", &p1, &p2);

    int i, f;
    int num_rows = 4;
    int num_cols = 10;

    for (i = 0; i < num_rows; i++) {
        for (f = 0; f < num_cols; f++) {

          printf("n[%i][%i] = %c \n", i, f, n[i][f]);
          printf("\t\t\t\t\taddress of n[%i][%i] = %lu \n", i, f, &n[i][f]);

        }
    }

    printf("p2 + 1 = %s\n", p2 + 1);
    printf("p2 + 1 = %lu\n", p2 + 1);


}
