/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:06 by juli              #+#    #+#             */
/*   Updated: 2023/11/30 14:42:57 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Returns a pointer to the first occurence of character (c) in the string (s).

   Return NULL if character (c) is not found */
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/* Attempts to free each node of the entire list and the provided buffer.
   Then resets the pointer to NULL after.

   Does nothing to pointers already pointing to NULL. */
void	_free_all(t_str_list **list, char **buffer)
{
	t_str_list	*this_node;
	t_str_list	*next_node;

	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (*list)
	{
		this_node = *list;
		while (this_node)
		{
			next_node = this_node->next;
			free(this_node);
			this_node = next_node;
		}
		*list = NULL;
	}
}

/* Calculates and returns the total length of all strings stored in the linked
   list.

   Iterates through each node in the list and adds up the lengths of the
   strings.*/
int	_total_strlen_from_list(t_str_list *list)
{
	int			i;
	int			len;
	t_str_list	*this_node;

	len = 0;
	this_node = list;
	while (this_node)
	{
		i = 0;
		while (this_node->str[i])
		{
			i++;
			len++;
		}
		this_node = this_node->next;
	}
	return (len);
}

/* Reads from a file descriptor until encounters a newline character or reaches
   the end of the file.

   Saves any excess data read into buffers for the file descriptor. Buffers are
   tracked with static pointers and are reserved bewteen different calls of the
   function.

   If list or fd_buffer does not exist (*head and *fd_buffer point to NULL),
   resets the original pointer to point to newly allocated node/buffer. 

   Frees the corresponding file descriptor buffer when the end of file is
   reached and resets to point to NULL. Free both the buffer and list and
   resets both to point to NULL upon read error (when return value is -1). */
void	_read_until_eol_or_eof_and_save_excess(int fd, char *tmp_buffer,
				t_str_list **head, char **fd_buffer)
{
	int			chars_read;

	chars_read = 1;
	while (!ft_strchr(tmp_buffer, '\n'))
	{
		chars_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (chars_read <= 0)
			break ;
		tmp_buffer[chars_read] = '\0';
		_add_until_eol_to_list(head, tmp_buffer);
		if (ft_strchr(tmp_buffer, '\n'))
			_save_to_fd_buffer(fd_buffer,
				ft_strchr(tmp_buffer, '\n') + 1);
	}
	if (chars_read == 0)
	{
		free(*fd_buffer);
		*fd_buffer = NULL;
	}
	else if (chars_read == -1)
	{
		_free_all(head, fd_buffer);
	}
}
