#include <stdio.h>

struct stop {
       char *station;
       int hh, mm;
};

int main()
{
   char a[] = "north station";
   char b[] = "chelsea";
   char c[] = "lynn";
   struct stop s1, s2;
   struct stop *p1, *p2;
   int    *ip1, *ip2;
   p1 = &s1;
   p2 = &s2;
   ip1 = &(s1.hh);
   ip2 = &(p2->mm);
   s1.station = a;
   s2.station = b;
   p1->station = c;
   p1->hh = 8;
   s1.mm  = 40;
   s2.hh = *ip1;
   p2->mm = s1.mm;

printf("address of a is %lu\n", &a);
printf("value of a is %s\n", a);
printf("address of b is %lu\n", &b);
printf("value of b is %s\n", b);
printf("address of c is %lu\n", &c);
printf("value of c is %s\n", c);


printf("address of s1 is %lu\n", &s1);
printf("value of s1.station is %s\n", s1.station);
printf("address of s1.station is %lu\n", &s1.station);
printf("value address of s2.station is %lu\n", s1.station);

printf("value of s1.hh is %i\n", s1.hh);
printf("address of s1.hh is %lu\n", &s1.hh);
printf("value of s1.mm is %i\n", s1.mm);
printf("address of s1.mm is %lu\n", &s1.mm);

printf("address of s2 is %lu\n", &s2);
printf("value of s2.station is %s\n", s2.station);
printf("address of s2.station is %lu\n", &s2.station);
printf("value address of s2.station is %lu\n", s2.station);

printf("value of s2.hh is %i\n", s2.hh);
printf("address of s2.hh is %lu\n", &s2.hh);
printf("value of s2.mm is %i\n", s2.mm);
printf("address of s2.mm is %lu\n", &s2.mm);


printf("address of p1 is %lu\n", &p1);
printf("value of p1 is %lu\n", p1);
printf("value of p1.station is %s\n", p1->station);
printf("address of p1.station is %lu\n", &p1->station);

printf("value of p1.hh is %i\n", p1->hh);
printf("address of p1.hh is %lu\n", &p1->hh);

printf("value of p1.mm is %i\n", p1->mm);
printf("address of p1.mm is %lu\n", &p1->mm);

printf("*p1 is %lu\n", *p1);

printf("address of p2 is %lu\n", &p2);
printf("value of p2 is %lu\n", p2);
printf("value of p2.station is %s\n", p2->station);
printf("address of p2.station is %lu\n", &p2->station);

printf("value of p2.hh is %i\n", p2->hh);
printf("address of p2.hh is %lu\n", &p2->hh);

printf("value of p2.mm is %i\n", p2->mm);
printf("address of p2.mm is %lu\n", &p2->mm);

printf("*p2 is %lu\n", *p2);

printf("address of ip1 is %lu\n", &ip1);
printf("value of ip1 is %lu\n", ip1);
printf("*ip1 is %lu\n", *ip1);


printf("address of ip2 is %lu\n", &ip2);
printf("value of ip2 is %lu\n", ip2);
printf("*ip2 is %lu\n", *ip2);

return 0;

}

