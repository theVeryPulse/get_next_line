/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:57:59 by Philip Li         #+#    #+#             */
/*   Updated: 2023/11/22 22:38:13 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE (25)

static int	append_excess_to_fd_buffer_list(
				t_fd_buffer_list **head, int fd, char *buffer);

static int	get_next_line_from_fd_buffer_list(
				t_fd_buffer_list *fd_buffer_list, int fd, char *buffer);

static int	append_current_line_to_list(t_char_list **head, char *buffer);

static char	*list_to_string(t_char_list *list);

char	*get_nex_line(int fd)
{
	char					buffer[BUFFER_SIZE + 1];
	char					*string;
	ssize_t					read_return_val;
	t_char_list				*list;
	static t_fd_buffer_list	*fd_buffer_list = NULL;

	list = NULL;

	// Fill buffer with '\0's for initialization
	ft_memset(buffer, '\0', BUFFER_SIZE + 1);
	
	// If there is content for same file from last GNL, save it into buffer;
	if (get_next_line_from_fd_buffer_list(fd_buffer_list, fd, buffer)) // Cut next line from static linked list and paste it into buffer, return the length of pasted string. Return 0 if there is no content or no corresponding node fot the file descriptor
		append_current_line_to_list(&list, buffer);

	// Keep adding the content from read() to linked list until the end of file or sees end of line
	while (!ft_strchr(buffer, '\n'))
	{
		// Reset buffer to prepare for next read(), then read the bytes from file
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
		read_return_val = read(fd, buffer, BUFFER_SIZE);

		// Break loop when read reaches end of file and returns nothing
		if (read_return_val == 0)
			break;

		// Append the buffer content to the linked list, ignore anything after a '\n'
		append_current_line_to_list(&list, buffer);

		// Save the extra content after '\n' into static list if there is any
		if(ft_strchr(buffer, '\n'))
			append_excess_to_fd_buffer_list(&fd_buffer_list, fd, buffer);

	}

	// Convert linked list into a string
	string = list_to_string(list);

	// Free all space taken by the list
	free_list(list);

	return (string);
}

// Finished

/* Copy the string after the first \n into the linked list and to
   the node of the corresponding file descriptor. Create and append
   the node if it does not exist.
   
   Returns 0 upon success and -1 upon error */
static int	append_excess_to_fd_buffer_list
	(t_fd_buffer_list **head, int fd, char *buffer)
{
	char	*string;
	size_t	start;
	t_fd_buffer_list	*this_node;
	t_fd_buffer_list	*new_node;

	this_node = *head;

	// Copy the content after first '\n',
	// or end function if there is nothing found after first '\n'
	start = 0;
	string = NULL;
	while (buffer[start] && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\0')
		return (-1);
	string = ft_strdup(&buffer[start + 1]);
	if (string == NULL)
		return (-1);

	// Search for node with correct fd to save the information
	if (this_node)
	{
		while (this_node->fd != fd && this_node->next)
		{
			this_node = this_node->next;
		}
		if (this_node->fd == fd)
		{
			free(this_node->content);
			this_node->content = string;
			return (0);
		}
	}
	// Allocate memory for a new node
	new_node = (t_fd_buffer_list *)malloc(sizeof(t_fd_buffer_list));
	// Handle malloc error
	if (new_node == NULL)
	{
		free(string);
		return (-1);
	}

	// Add the string to a new node, attach the new node to linked list
	new_node->fd = fd;
	new_node->content = string;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	else
	{
		while (this_node->next)
			this_node = this_node->next;
		this_node->next = new_node;
		return (0);
	}
}

/* Try and cut the next line from list of corresponding file
   descriptor and paste it into buffer.

   Returns the length of pasted string. Return 0 if there is no
   content or no corresponding node fot the file descriptor */
static int	get_next_line_from_fd_buffer_list
	(t_fd_buffer_list *fd_buffer_list, int fd, char *buffer)
{
	t_fd_buffer_list	*this_node;
	size_t				i;
	size_t				j;
	char				*string;
	int					write_to_buffer_length;

	// End function upon incorrect input
	if (fd_buffer_list == NULL || fd < 0 || buffer == NULL)
		return (0);

	// Find the node with correct file descriptor, end function cannot find
	this_node = fd_buffer_list;
	while (this_node)
	{
		if (this_node->fd == fd)
			break;
		this_node = this_node->next;
	}
	if (this_node == NULL || this_node->fd != fd)
		return (0);

	// Copy the string until next '\n' into buffer
	i = 0;
	string = this_node->content;
	while (string[i] && string[i] != '\n')
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
	while (i < BUFFER_SIZE + 1)
		string[i++] = '\0';
	return (write_to_buffer_length);
}

/* Append the content from string until \n into a new node in the
   list. Set the head to point to new list head points to NULL.
   
   Returns 0 upon success and -1 upon failure */
static int	append_current_line_to_list(t_char_list **head, char *buffer)
{
	size_t	i;
	char	*string;
	t_char_list	*this_node;
	t_char_list	*new_node;

	this_node = *head;
	// Duplicate the buffer	
	string = ft_strdup(buffer);
	if (string == NULL)
		return (-1);
	// Trim everything after the NewLine
	i = 0;
	while(string[i] != '\n' && string[i])
		i++;
	if (string[i] == '\n' && i < BUFFER_SIZE)
		string[i + 1] = '\0';

	// Allocate memory for a new node
	new_node = (t_char_list *)malloc(sizeof(t_char_list));
	// Handle malloc error
	if (new_node == NULL)
	{
		free(string);
		return (-1);
	}

	// Add the string to a new node, attach the new node to linked list
	new_node->content = string;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (this_node->next)
			this_node = this_node->next;
		this_node->next = new_node;
	}
	return (0);
}

/* Concatenate all content from a list into a single string 

   Returns NULL if the conversion fails. */
static char	*list_to_string(t_char_list *list)
{
	char		*string;
	size_t		len;
	size_t		i;
	size_t		j;
	t_char_list	*this_node;

	if (list == NULL)
		return (NULL);
	// Calculate the total length of target string
	len = 0;
	this_node = list;
	while (this_node)
	{
		len += ft_strlen(this_node->content);
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
		while (this_node->content[j])
			string[i++] = this_node->content[j++];
		this_node= this_node->next;
	}
	string[i] = '\0';
	return (string);
}
