/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:06 by juli              #+#    #+#             */
/*   Updated: 2023/11/28 22:33:43 by Philip Li        ###   ########.fr       */
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
void	_free_all(t_str_list *list, char *buffer)
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
int		_total_strlen_from_list(t_str_list *list)
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
