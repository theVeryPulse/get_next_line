#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/* Linked list, each node contains the character content, its offset,
   and pointer to the next node */
typedef struct s_char_list
{
	char				c;
	int					offset; // offset is probably unnecessary since read() remebers the offset
	struct s_char_list	*next;
} t_char_list;


/* Save the previous offset for files when calling get_next_line
   function.

   int fd; int offset; struct s_fd_offset_list *next;

   t_fd_offset_list
   | fd:int, offset:int;
   | fd:int, offset:int;
   | ...
*/
typedef struct s_fd_offset_list
{
	int						fd;
	bool					same_fd;
	struct s_fd_offset_list	*next;
} t_fd_offset_list;


/* Returns a pointer to the character item of the tail of the list,
   adds a new node to the end of the list when necessary.

   Returns NULL pointer in case of error. */
char *append_to_list(t_char_list *list)
{
	if (list->c == '\0')
		return (&(list->c));
	while (list->next)
		list = list->next;
	list->next = (t_char_list *)malloc(sizeof(t_char_list));
	if (list->next == NULL)
		return (NULL);
	list->next->next = NULL;
	return (&(list->next->c));
}

/* Concatenate all characters from the linked list into one string. 
   Returns NULL upon error. */
char	*list_to_string(t_char_list *list)
{
	int		len;
	int		i;
	char	*s;

	len = 0;
	t_char_list *this_node = list;
	while (this_node->next)
	{
		this_node = this_node->next;
		len++;
	}
	s = (char *)malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (list)
	{
		s[i++] = list->c;
		list = list->next;
	}
	s[i] = '\0';
	return (s);
}

char	*get_next_line(int fd)
{
	int						offset;
	char					c;
	char					*buffer;
	char					*string;
	t_char_list				list;
	static t_fd_offset_list	fd_offset_list;

	list = (t_char_list) {'\0', 0, NULL};
	if (is_last_fd(&fd_offset_list, fd) == false)
		offset = get_offset(&fd_offset_list, fd);
	c = '0';
	buffer = &c;
	while (c && c != '\n')
	{
		read(STDIN_FILENO, buffer, 1);
		*(append_to_list(&list)) = *buffer;
		string = list_to_string(&list);
		if (!string)
			return (NULL);
		if (*buffer == '\n')
			break;
	}

}

int main(void)
{
	char c;
	char *p = &c;
	char *s;
	t_char_list list = (t_char_list) {'\0', 0, NULL};
	s = get_next_line(STDIN_FILENO);
	write(STDOUT_FILENO, ">>>>\n", strlen(">>>>\n"));
	write(STDOUT_FILENO, s, strlen(s));
	free(s);
	write(STDOUT_FILENO, "\n<<<<\n", strlen("\n<<<<\n"));

	int i = 0;
	for(t_char_list *this_node = &list; this_node; this_node = this_node->next, i++)
	{
		printf("node %d: char:(%c), offset(%d)\n",i, this_node->c, this_node->offset);
	}
}