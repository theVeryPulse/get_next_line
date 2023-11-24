/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:57:59 by Philip Li         #+#    #+#             */
/*   Updated: 2023/11/24 01:32:51 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	append_excess_to_fd_str_list(t_fd_str_list **head,
				int fd, char *buffer);

static int	get_next_line_from_fd_str_list(t_fd_str_list *fd_str_list,
				int fd, char *buffer);

static int	append_current_line_to_list(t_str_list **head, char *buffer);

static char	*list_to_string(t_str_list *list);

char	*get_next_line(int fd)
{
	char					buffer[BUFFER_SIZE + 1];
	char					*string;
	int						read_return;
	t_str_list				*list;
	static t_fd_str_list	*fd_str_list = NULL;

	if (fd < 0)
		return (NULL);
	list = NULL;
	// Fill buffer with '\0's for initialization
	ft_memset(buffer, '\0', BUFFER_SIZE + 1);
	// If there is content for same file from last GNL, save it into buffer;
	if (get_next_line_from_fd_str_list(fd_str_list, fd, buffer))
		append_current_line_to_list(&list, buffer);
	// Keep adding the content from read() to linked list until the end of file or sees end of line
	while (!ft_strchr(buffer, '\n'))
	{
		// Reset buffer to prepare for next read()
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
		// Read the bytes from file Break loop when read reaches EoF
		// or in case of error
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return <= 0)
		 	break ;
		// Append the buffer content to the linked list, ignore anything after a \n
		append_current_line_to_list(&list, buffer);
		// Save the extra content after '\n' into static list if there is any
		if(ft_strchr(buffer, '\n'))
			append_excess_to_fd_str_list(&fd_str_list, fd, buffer);
	}
	// Convert linked list into a string
	string = list_to_string(list);
	// Free all space taken by the list
	free_list(list);
	return (string);
}

/* Copy the string after the first \n to the node of corresponding
   file descriptor. Create the node if it does not exist.
   
   Returns 0 upon success and -1 upon error */
static int	append_excess_to_fd_str_list(t_fd_str_list **head,
	int fd, char *buffer) // [x] append_excess_to_fd_str_list: new struct refactor
{
	size_t			i;
	t_fd_str_list	*this_node;
	t_fd_str_list	*new_node;

	this_node = *head;
	// Search for node with correct fd to save the information
	while (this_node->fd != fd && this_node->next)
		this_node = this_node->next;
	// When the node cannot be found
	// Allocate memory for a new node | handle malloc error
	if (this_node->fd != fd)
	{
		new_node = (t_fd_str_list *)malloc(sizeof(t_fd_str_list));
		if (new_node == NULL)
			return (-1);
		new_node->fd = fd;
		this_node->next = new_node;
		this_node = new_node;
	}
	// Copy the content after first \n into the node (strcpy)
	i = 0;
	while (buffer[i])
	{
		this_node->str[i] = buffer[i];
		if (buffer[i] == '\n')
			break;
		i++;
	}
	return (0);
}

/* Try and cut the next line from list of corresponding file
   descriptor and paste it into buffer.

   Returns the length of pasted string. Return 0 if there is no
   content or no corresponding node fot the file descriptor */
static int	get_next_line_from_fd_str_list(t_fd_str_list *fd_str_list,
	int fd, char *buffer) // [x] get_next_line_from_fd_str_list: new struct refactor
{
	t_fd_str_list	*this_node;
	size_t			i;
	size_t			j;
	char			*string;
	int				write_to_buffer_length;

	// End function upon incorrect input
	if (fd_str_list == NULL || fd < 0 || buffer == NULL)
		return (0);
	// Find the node with correct file descripotr, end function cannot find
	this_node = fd_str_list;
	while (this_node && this_node->fd != fd)
		this_node = this_node->next;
	if (this_node == NULL)
		return (0);
	// Copy the string until next '\n' into buffer
	i = 0;
	while (this_node->str[i] && this_node->str[i] != '\n')
	{
		buffer[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
		buffer[i++] = '\n';
	buffer[i] = '\0';
	write_to_buffer_length = i;
	// Replace current node content with what is after first '\'n
	j = i;
	i = 0;
	while (string[j])
	{
		string[i] = string[j];
		i++;
		j++;
	}
	while (i < BUFFER_SIZE && string[i])
		string[i++] = '\0';
	return (write_to_buffer_length);
}

/* Copy the content from buffer until \n into a new node in the
   list. If head points to NULL, set it to point to this new node.
   
   Returns 0 upon success and -1 upon failure */
static int	append_current_line_to_list(t_str_list **head, char *buffer) // [x] append_current_line_to_list: new struct refactor
{
	size_t		i;
	t_str_list	*this_node;
	t_str_list	*new_node;

	// Allocate memory for a new node | handle malloc error
	new_node = (t_str_list *)malloc(sizeof(t_str_list));
	if (new_node == NULL)
		return (-1);
	// Copy the current line into the new node, attach the new node to linked list
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new_node->str[i] = buffer[i];
		i++;
	}
	buffer[i] = '\0';
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
static char	*list_to_string(t_str_list *list) //[x] list_to_string: new struct refactor
{
	char		*string;
	size_t		len;
	size_t		i;
	size_t		j;
	t_str_list	*this_node;

	if (list == NULL)
		return (NULL);
	// Calculate the total length of target string (func total_len?)
	len = 0;
	this_node = list;
	while (this_node)
	{
		len += ft_strlen(this_node->str);
		this_node = this_node->next;
	}
	// Copy all content into the string
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	this_node = list;
	i = 0;
	while (this_node)
	{
		j = 0;
		while (this_node->str[j])
			string[i++] = this_node->str[j++];
		this_node= this_node->next;
	}
	string[i] = '\0';
	return (string);
}
