/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:06 by juli              #+#    #+#             */
/*   Updated: 2023/11/29 02:05:19 by Philip Li        ###   ########.fr       */
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

/* Free the space taken by the entire list.
*/
void	free_list(t_str_list *list)
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
}

/* Return the sum of lengths of all strings saved in the entire list.
*/
int		line_len_from_list(t_str_list *list)
{
	int			i;
	int			len;
	t_str_list	*this_node;

	len = 0;
	this_node = list;
	while (this_node)
	{
		i = 0;
		while (this_node->str[i] && this_node->str[i] != '\n')
		{
			i++;
			len++;
		}
		this_node = this_node->next;
	}
	return (len);
}

/* Return a pointer to a new node of t_str_list 
   
   Deep copy the string argument into the node
*/
t_str_list	*new_str_list_node(char *str, t_str_list *next)
{
	int	i;
	t_str_list	*new_node;
	
	new_node = (t_str_list *)malloc(sizeof(t_str_list) * 1);
	if (new_node == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_node->str[i] = str[i];
		i++;
	}
	new_node->str[i] = '\0';
	new_node->next = next;
	return (new_node);
}
