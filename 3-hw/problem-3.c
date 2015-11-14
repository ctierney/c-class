#include <stdio.h>

int main() {
            
    int m[5] = { 4, 3, 2, 1, 0 };
    int *p;
	p = m + 2;
    
    printf("m is %lu, &m is %lu, &m[0] is %lu, m[0] is %lu\n",
          m, (unsigned long)&m, (unsigned long)&m[0], m[0]);
    printf("p is %lu, &p is %lu, &p[0] is %lu, p[0] is %lu\n",
    	p, (unsigned long)&p, (unsigned long)&p[0], p[0]);


    for (int i = 0; i < 5; i++) {

    	printf("address of m[%i] is %lu\n", i, &m[i]);
    }

    printf("value of p[-1] is %lu\n", &p[-1]);
    printf("value of p[-2] is %lu\n", &p[-2]);


}