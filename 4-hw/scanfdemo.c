#include	<stdio.h>

main()
{
	char	x[1000];
	int	rv;

	while(1)
	{
		rv = scanf("%s", x);
		printf("scanf just returned %d\n", rv);
		if ( rv == EOF )
			break;
		printf("and read in [%s]\n", x);
	}
}
