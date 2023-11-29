/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:57:59 by Philip Li         #+#    #+#             */
/*   Updated: 2023/11/29 18:34:04 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*tmp_buffer;
	char		*out_str;
	static char	*fd_buffer_set[FD_MAX];
	t_str_list	*list;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	list = NULL;
	tmp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buffer)
		return (NULL);
	tmp_buffer[0] = '\0';
	if (fd_buffer_set[fd] && fd_buffer_set[fd][0])
	{
		cut_line_into_buffer(fd_buffer_set[fd], tmp_buffer);
		add_until_eol_to_list(&list, tmp_buffer);
	}
	read_until_eol_or_eof_and_save_excess(fd, tmp_buffer, &list,
		&fd_buffer_set[fd]);
	out_str = list_to_line(list);
	free_all(list, tmp_buffer);
	return (out_str);
}

/* Cut and paste a line from (fd_buffer) into (tmp_buffer) */
void	cut_line_into_buffer(char *fd_buffer, char *tmp_buffer)
{
	int	i;
	int	move;

	i = 0;
	while (fd_buffer[i] && fd_buffer[i] != '\n')
	{
		tmp_buffer[i] = fd_buffer[i];
		i++;
	}
	if (fd_buffer[i] == '\n')
		tmp_buffer[i++] = '\n';
	tmp_buffer[i] = '\0';
	move = 0;
	while (fd_buffer[i])
	{
		fd_buffer[move++] = fd_buffer[i++];
	}
	fd_buffer[move] = '\0';
}

/* Copy the source string into fd_buffer. If buffer of target file
   descriptor does not exist, allocate the memory. */
void	save_to_fd_buffer(char **fd_buffer, char *source)
{
	int		i;
	char	*dest;

	if (source == NULL)
		return ;
	if (*fd_buffer == NULL)
		*fd_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*fd_buffer == NULL)
		return ;
	dest = *fd_buffer;
	i = 0;
	while (source[i] && i < BUFFER_SIZE)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
}

/* Copy the content from buffer until \n into a new node in the
   list. If head points to NULL, set it to point to this new node.
   
   Returns 0 upon success and -1 upon failure */
void	add_until_eol_to_list(t_str_list **head, char *buffer)
{
	size_t		i;
	t_str_list	*this_node;
	t_str_list	*new_node;

	new_node = (t_str_list *)malloc(sizeof(t_str_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	i = 0;
	while (buffer[i])
	{
		new_node->str[i] = buffer[i];
		if (buffer[i++] == '\n')
			break ;
	}
	new_node->str[i] = '\0';
	if (*head == NULL)
		*head = new_node;
	else
	{
		this_node = *head;
		while (this_node->next)
			this_node = this_node->next;
		this_node->next = new_node;
	}
}

/* Concatenate all content from a list into a single string 

   Returns NULL if the conversion fails. */
char	*list_to_line(t_str_list *list)
{
	char		*dest;
	size_t		len;
	size_t		i;
	size_t		j;
	t_str_list	*this_node;

	if (list == NULL)
		return (NULL);
	len = total_strlen_from_list(list);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	this_node = list;
	i = 0;
	while (this_node)
	{
		j = 0;
		while (this_node->str[j])
			dest[i++] = this_node->str[j++];
		this_node = this_node->next;
	}
	dest[i] = '\0';
	return (dest);
}
