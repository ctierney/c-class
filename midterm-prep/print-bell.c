#include <stdio.h>


int main() {

int counter = 0;
int stop_at = 100;

	while (1) {

		printf("%d\n", '\a');

		if (counter++ < stop_at)
			break;

	}

	return 0;
}