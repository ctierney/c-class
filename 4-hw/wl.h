#define	BUFLEN	512
#define	YES	1
#define	NO	0

void	init_table();
int	in_table(char []);
int	insert(char [], int);
int	lookup(char []);
int	update(char [], int );
char	*firstword();
char	*nextword();
void	word_delete(char []);
