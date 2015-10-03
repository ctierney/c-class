#include <stdio.h>

/* don't include table start and end tags only process the tr and tds */

/* keep track of the length of the attributes array if they give you too many attributes, 
ignore them, when storing the attributes keep track of the array lengths use a multi dimensional char array
use strncpy to keep the array from over flowing snprintf will always terminate the string */

char *tmp = line; 
char *d; 
do {
	d = strchr(d,delim);
	if (d != null) {
		//
		tmp = d + 1;
	} else {
		// if it's a newline output a td characther 
	}
d,delim
}

