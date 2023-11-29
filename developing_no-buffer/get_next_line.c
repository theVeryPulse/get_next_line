/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:57:59 by Philip Li         #+#    #+#             */
/*   Updated: 2023/11/29 02:07:18 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LOG
   Remove comments
   free_all()
   Removed ft_strlen(). Add total_strlen_from_list() Test OK
   Removed ft_memset(). Test OK
*/

#include "get_next_line.h"

static void	add_to_fd_str_list(t_fd_str_list **head,
				int fd, char *buffer);

static void	get_next_line_from_fd_str_list(t_fd_str_list *fd_str_list,
				int fd, char *buffer);

static char	*list_to_line(t_str_list *list);


/* Add a new node to the tail of a linked list, reset tail to the new node.

   Deep copy the argument string into the node.
*/
static void	add_str_list_node_tail(t_str_list **tail, char *str, t_str_list *next)
{
	int			i;
	t_str_list	*prev_node;
	t_str_list	*new_node;

	prev_node = *tail;
	new_node = (t_str_list *)malloc(sizeof(t_str_list) * 1);
	if (new_node == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		new_node->str[i] = str[i];
		i++;
	}
	new_node->str[i] = '\0';
	new_node->next = next;
	prev_node->next = new_node;
	*tail = new_node;
}

// [ ] 25 lines
char	*get_next_line(int fd)
{
	int						read_return;
	char					*string;
	t_str_list				*head;
	t_str_list				*tail;
	static t_fd_str_list	*fd_str_list = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = new_str_list_node("", NULL);
	if (!head)
		return (NULL);
	tail = head;
	get_next_line_from_fd_str_list(fd_str_list, fd, tail->str);
	while (!ft_strchr(tail->str, '\n'))
	{
		add_str_list_node_tail(&tail, "", NULL);
		read_return = read(fd, tail->str, BUFFER_SIZE);
		if (read_return <= 0)
		 	break ;
		tail->str[read_return] = '\0';
		add_to_fd_str_list(&fd_str_list, fd, ft_strchr(tail->str, '\n'));
	}
	string = list_to_line(head);
	free_list(head);
	return (string);
}

/* Copy the string after the first \n to the node of corresponding
   file descriptor. Create the node if it does not exist.
   
   Returns 0 upon success and -1 upon error */
// [ ] 37 Lines
static void	add_to_fd_str_list(t_fd_str_list **head,
	int fd, char *buffer)
{
	int				i;
	int				j;
	t_fd_str_list	*this_node;
	t_fd_str_list	*new_node;

	if (fd == 0 || buffer == NULL)
		return ;
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
	j = 1;
	while(buffer[j])
	{
		this_node->str[i++] = buffer[j++];
	}
	this_node->str[i] = '\0';
}

/* Try and cut the next line from list of corresponding
   file descriptor and paste it into buffer. */
static void	get_next_line_from_fd_str_list(t_fd_str_list *fd_str_list,
	int fd, char *buffer)
// [ ] 33 lines
{
	t_fd_str_list	*this_node;
	size_t			i;
	size_t			j;

	if (fd_str_list == NULL || fd < 0 || buffer == NULL)
		return ;
	this_node = fd_str_list;
	while (this_node->next && this_node->fd != fd)
		this_node = this_node->next;
	if (this_node->next == NULL && this_node->fd != fd)
		return ;
	// Copy the string until NewLine from fd_str_list into buffer
	i = 0;
	while (this_node->str[i] && this_node->str[i] != '\n')
	{
		buffer[i] = this_node->str[i];
		i++;
	}
	if (this_node->str[i] == '\n')
		buffer[i++] = '\n';
	buffer[i] = '\0';
	// Overwrite the begining with what comes after the NewLine
	j = 0;
	while (this_node->str[i])
		this_node->str[j++] = this_node->str[i++];
	this_node->str[j] = '\0';
}

/* Join all strings from a list into a single string 

   Returns NULL if the conversion fails. */
static char	*list_to_line(t_str_list *list)
{
	char		*string;
	int			i;
	int			j;
	t_str_list	*this_node;

	string = (char *)malloc(sizeof(char) *
		(line_len_from_list(list) + 1));
	if (string == NULL)
		return (NULL);
	this_node = list;
	i = 0;
	while (this_node)
	{
		j = 0;
		while (this_node->str[j] && this_node->str[j] != '\n')
		{
			string[i++] = this_node->str[j++];
			if (this_node->str[j] == '\n')
			{
				string[i++] = '\n';
				break ;
			}
		}
		this_node= this_node->next;
	}
	string[i] = '\0';
	return (string);
}
