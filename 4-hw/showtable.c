#define	TABLE_LEN	26
#define	CHAR_BASE	'a'

/*
 * This function may help you debug your code.
 * It will print out the contents of the table
 * You can add it to the bottom of your wlfiler5.c file
 * and call it after each insert or update.
 */
show_table()
{
	int	     row;
	struct link *lp;

	for(row=0; row<TABLE_LEN; row++){
		printf("%3d [%c] [ | ]->", row, CHAR_BASE+row);
		for(lp=table[row].next;  lp ; lp = lp->next )
			printf("[%s|%d]->", lp->word, lp->value);
		printf("NULL\n");
	}
}
