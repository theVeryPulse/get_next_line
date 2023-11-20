#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include "get_next_line.h"
#define BUFFER_SIZE (16)

/* Appends a new node to the linked list, save the input character as
   its content.

   Returns 0 upon success and -1 upon error. */
int	append_to_list(t_char_list *list, char *c)
{
	t_char_list	*new_node;

	new_node = (t_char_list *)malloc(sizeof(t_char_list));
	if (!new_node == NULL)
		return (NULL);
	new_node->buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (list->buffer == NULL)
		return (NULL);
	
	while (list->next)
		list = list->next;
	list->next = (t_char_list *)malloc(sizeof(t_char_list));
	if (list->next == NULL)
		return (-1);
	list = list->next;
	list->c = c;
	list->next = NULL;
	return (0);
}

/* Concatenate all characters from the linked list into one string. 
   Returns NULL upon error. 

   The string must be free()ed after usage to free the allocated
   space. */
char	*list_to_string(t_char_list *list)
{
	int		len;
	int		i;
	char	*s;

	len = 0;
	t_char_list *this_node = list;
	while (this_node)
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

int	free_list(t_char_list *list)
{
	t_char_list	*this_node;
	t_char_list	*next_node;
	this_node = list;
	while (this_node)
	{
		next_node = this_node->next;
		free(this_node);
		if (next_node == NULL)
			break;
		this_node = next_node;
	}
	return (0);
}

t_char_list	*new_list(void)
{
	int			i;
	t_char_list	*list;

	list = (t_char_list *)malloc(sizeof(t_char_list));
	if (!list == NULL)
		return (NULL);
	list->buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (list->buffer == NULL)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
		(list->buffer)[i++] = '\0';
	list->next = NULL;
	return (list);
}

char	*get_next_line(int fd)
{
	int						read_return;
	char					*string;
	char					buffer[BUFFER_SIZE + 1];
	t_char_list				*list;
	static t_fd_buffer_list *fd_buffer_list;

	list = new_list();
	read_return = 1;
	while (read_return)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		append_to_list(list, buffer);
		if (c == '\n')
			break;
	}
	if (read_return == 0)
		return (NULL);
	string = list_to_string(list);
	free_list(list);
	if (!string)
		return (NULL);
	return (string);
}

int main(void)
{
	char *s;
	int fd0 = open("test0.txt", O_RDONLY);
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	for (int i = 0; i < 120; i++)
	{
		s = get_next_line(fd0);
		printf("fd0: (%s)\n", s);
		free(s);
		s = get_next_line(fd1);
		printf("fd1: (%s)\n", s);
		free(s);
		s = get_next_line(fd2);
		printf("fd2: (%s)\n", s);
		free(s);
	}
}