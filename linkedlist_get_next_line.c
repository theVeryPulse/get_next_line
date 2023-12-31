/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_get_next_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:57:59 by Philip Li         #+#    #+#             */
/*   Updated: 2023/11/29 14:02:01 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LOG
   Remove comments
   free_all()
   Removed ft_strlen(). Add total_strlen_from_list() Test OK
   Removed ft_memset(). Test OK
*/

#include "linkedlist_get_next_line.h"

static void	add_to_fd_str_list(t_fd_str_list **head,
				int fd, char *buffer);

static int	get_next_line_from_fd_str_list(t_fd_str_list *fd_str_list,
				int fd, char *buffer);

static void	append_current_line_to_list(t_str_list **head, char *buffer);

static char	*_list_to_line(t_str_list *list);

// [ ] 28 lines
char	*get_next_line(int fd)
{
	char					*buffer;
	char					*string;
	int						read_return;
	t_str_list				*list;
	static t_fd_str_list	*fd_str_list = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	list = NULL;
	buffer[0] = '\0';
	if (get_next_line_from_fd_str_list(fd_str_list, fd, buffer))
		append_current_line_to_list(&list, buffer);
	while (!ft_strchr(buffer, '\n'))
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return <= 0)
		 	break ;
		buffer[read_return] = '\0';
		append_current_line_to_list(&list, buffer);
		if(ft_strchr(buffer, '\n'))
			add_to_fd_str_list(&fd_str_list, fd, ft_strchr(buffer, '\n') + 1);
	}
	string = _list_to_line(list);
	_free_all(list, buffer);
	return (string);
}

/* Copy the string after the first \n to the node of corresponding
   file descriptor. Create the node if it does not exist.
   
   Returns 0 upon success and -1 upon error */
// [ ] 37 Lines
static void	add_to_fd_str_list(t_fd_str_list **head,
	int fd, char *buffer)
{
	size_t			i;
	t_fd_str_list	*this_node;
	t_fd_str_list	*new_node;

	if (*head == NULL)
	{
		new_node = (t_fd_str_list *)malloc(sizeof(t_fd_str_list));
		if (new_node == NULL)
			return ;
		new_node->fd = fd;
		new_node->next = NULL;
		*head = new_node;
		this_node = new_node;
	}
	else
	{
		this_node = *head;
		while (this_node->fd != fd && this_node->next)
			this_node = this_node->next;
		if (this_node->fd != fd)
		{
			new_node = (t_fd_str_list *)malloc(sizeof(t_fd_str_list));
			if (new_node == NULL)
				return ;
			new_node->fd = fd;
			new_node->next = NULL;
			this_node->next = new_node;
			this_node = new_node;
		}
	}
	i = 0;
	while(buffer[i])
	{
		this_node->str[i] = buffer[i];
		i++;
	}
	this_node->str[i] = '\0';
}

/* Try and cut the next line from list of corresponding file
   descriptor and paste it into buffer.

   Returns the length of pasted string. Return 0 if there is no
   content or no corresponding node fot the file descriptor */
// [ ] 33 lines
static int	get_next_line_from_fd_str_list(t_fd_str_list *fd_str_list,
	int fd, char *buffer)
{
	t_fd_str_list	*this_node;
	size_t			i;
	size_t			j;
	int				write_to_buffer_length;

	if (fd_str_list == NULL || fd < 0 || buffer == NULL)
		return (0);
	this_node = fd_str_list;
	while (this_node->next && this_node->fd != fd)
		this_node = this_node->next;
	if (this_node->next == NULL && this_node->fd != fd)
		return (0);
	i = 0;
	while (this_node->str[i] && this_node->str[i] != '\n')
	{
		buffer[i] = this_node->str[i];
		i++;
	}
	if (this_node->str[i] == '\n')
		buffer[i++] = '\n';
	buffer[i] = '\0';
	write_to_buffer_length = i;
	j = i;
	i = 0;
	while (this_node->str[j])
	{
		this_node->str[i] = this_node->str[j];
		i++;
		j++;
	}
	while (i < BUFFER_SIZE && this_node->str[i])
		this_node->str[i++] = '\0';
	return (write_to_buffer_length);
}

/* Copy the content from buffer until \n into a new node in the
   list. If head points to NULL, set it to point to this new node.
   
   Returns 0 upon success and -1 upon failure */
static void	append_current_line_to_list(t_str_list **head, char *buffer)
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

/* Join all strings from a list into a single string 

   Returns NULL if the conversion fails. */
static char	*_list_to_line(t_str_list *list)
{
	char		*string;
	int			i;
	int			j;
	t_str_list	*this_node;

	if (list == NULL)
		return (NULL);
	string = (char *)malloc(sizeof(char) *
		(_total_strlen_from_list(list) + 1));
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
