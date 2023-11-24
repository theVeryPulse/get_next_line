/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_comment.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:06 by juli              #+#    #+#             */
/*   Updated: 2023/11/24 00:49:33 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Returns a copy of input string.

   The copy needs to be freed after usage */
char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

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
int	free_list(t_str_list *list) // [ ] free_list: new struct refactor
{
	t_str_list	*this_node;
	t_str_list	*next_node;

	this_node = list;
	while (this_node)
	{
		next_node = this_node->next;
		free(this_node->content);
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

/* Copy from (src) to (dst), make sure to null-terminate the string

   Parameter
   size: the size of (dst) array 
   
   Return Value
   The length of (src) string */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	total_len;

	i = 0;
	total_len = ft_strlen((char *)src);
	if (size == 0)
		return (total_len);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (total_len);
}