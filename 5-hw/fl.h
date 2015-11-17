#include	"ws13.h"
#include	<stdio.h>
/*
 *	some constants
 */

#define	MAXFLD	40
#define	MAXVAL	120

/*
 *	function declarlations
 */

int	get_record(symtab_t *, FILE *, char, char);
void	mailmerge( symtab_t *, FILE *);
void	process(FILE*, FILE*, char, char);
void	fatal(char *, char *);
