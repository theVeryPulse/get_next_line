/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:57:59 by Philip Li         #+#    #+#             */
/*   Updated: 2023/11/29 17:18:43 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	cut_line_into_buffer(char *fd_buffer, char *tmp_buffer);

static void	save_to_fd_buffer(char **fd_buffer, char *source);

static int	append_current_line_to_list(t_str_list **head, char *buffer);

static char	*list_to_line(t_str_list *list);

char	*get_next_line(int fd)
{
	char					*tmp_buffer;
	char					*string;
	static char				*fd_buffer_set[FD_MAX];
	int						chars_read;
	t_str_list				*list;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	list = NULL;
	tmp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buffer)
		return (NULL);
	tmp_buffer[0] ='\0';
	if (fd_buffer_set[fd] && fd_buffer_set[fd][0])
	{
		cut_line_into_buffer(fd_buffer_set[fd], tmp_buffer);
		append_current_line_to_list(&list, tmp_buffer);
	}
	// Keep adding the content from read() to linked list until the end of file or sees end of line
	while (!ft_strchr(tmp_buffer, '\n'))
	{
		// Read the bytes from file Break loop when read reaches EoF
		// or in case of error
		chars_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		 	break ;
		tmp_buffer[chars_read] = '\0';
		// Append the buffer content to the linked list, ignore anything after a \n
		append_current_line_to_list(&list, tmp_buffer);
		// Save the extra content after '\n' into static list if there is any
		if(ft_strchr(tmp_buffer, '\n'))
			save_to_fd_buffer(&fd_buffer_set[fd], ft_strchr(tmp_buffer, '\n') + 1);
	}
	string = list_to_line(list);
	free_all(list, tmp_buffer);
	return (string);
}

/* Cut and paste a line from (fd_buffer) into (tmp_buffer) */
static void	cut_line_into_buffer(char *fd_buffer, char *tmp_buffer)
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
	while(fd_buffer[i])
	{
		fd_buffer[move++] = fd_buffer[i++];
	}
	fd_buffer[move] = '\0';
}

/* Copy the source string into fd_buffer. If buffer of target file
   descriptor does not exist, allocate the memory. */
static void	save_to_fd_buffer(char **fd_buffer, char *source)
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
static int	append_current_line_to_list(t_str_list **head, char *buffer)
{
	size_t		i;
	t_str_list	*this_node;
	t_str_list	*new_node;

	new_node = (t_str_list *)malloc(sizeof(t_str_list));
	if (new_node == NULL)
		return (-1);
	new_node->next = NULL;
	i = 0;
 	while (buffer[i])
	{
		new_node->str[i] = buffer[i];
		if (buffer[i++] == '\n')
			break;
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
	return (0);
}

/* Concatenate all content from a list into a single string 

   Returns NULL if the conversion fails. */
static char	*list_to_line(t_str_list *list)
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
		this_node= this_node->next;
	}
	dest[i] = '\0';
	return (dest);
}
