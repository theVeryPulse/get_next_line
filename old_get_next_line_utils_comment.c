/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_comment.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:06 by juli              #+#    #+#             */
/*   Updated: 2023/11/24 19:01:23 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Set (n) bytes of memory to character (c) at given address (s) */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)	
		((char *)s)[i++] = c;
	return (s);
}

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
int	_free_list(t_str_list *list) // [x] free_list: new struct refactor
{
	t_str_list	*this_node;
	t_str_list	*next_node;

	this_node = list;
	while (this_node)
	{
		next_node = this_node->next;
		free(this_node);
		this_node = next_node;
	}
	return (0);
}

/* Returns the length of a string */
int	ft_strlen(const char *s)
{
	int	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
