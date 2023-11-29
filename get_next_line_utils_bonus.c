/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:06 by juli              #+#    #+#             */
/*   Updated: 2023/11/29 18:33:53 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Return a pointer to the first character (c) that is found in (s)

   Return NULL if no character (c) can be found */
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

/* Free the entire list and the content of each node*/
void	free_all(t_str_list *list, char *buffer)
{
	t_str_list	*this_node;
	t_str_list	*next_node;

	free(buffer);
	this_node = list;
	while (this_node)
	{
		next_node = this_node->next;
		free(this_node);
		this_node = next_node;
	}
}

/* Return the sum of lengths of all strings saved in the entire list.
*/
int	total_strlen_from_list(t_str_list *list)
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

void	read_until_eol_or_eof_and_save_excess(int fd, char *tmp_buffer,
				t_str_list **head, char **fd_buffer)
{
	int			chars_read;

	while (!ft_strchr(tmp_buffer, '\n'))
	{
		chars_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (chars_read <= 0)
			break ;
		tmp_buffer[chars_read] = '\0';
		add_until_eol_to_list(head, tmp_buffer);
		if (ft_strchr(tmp_buffer, '\n'))
			save_to_fd_buffer(fd_buffer,
				ft_strchr(tmp_buffer, '\n') + 1);
	}
}
