#include <unistd.h>

/* Linked list, each node contains the character content, its offset,
   and pointer to the next node */
typedef struct s_list
{
	char	c;
	int		offset;
	t_list	*next;
} t_list;

int main(void)
{
	char c;
	char *p = &c;
	t_list list = {'\0', 0, NULL};
	while(1)
	{
		read(STDIN_FILENO, p, 1);
		write(STDOUT_FILENO, p, 1);
	}
}
