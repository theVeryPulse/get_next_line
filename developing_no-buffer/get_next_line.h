/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:17:16 by juli              #+#    #+#             */
/*   Updated: 2023/11/29 01:17:31 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (25)
# endif

/* Linked list, each node contains the character content, its offset,
   and pointer to the next node */
typedef struct s_str_list
{
	char				str[BUFFER_SIZE + 1];
	struct s_str_list	*next;
}	t_str_list;

/* Save the previous offset for files when calling get_next_line
   function.

   .fd:       int
   .content:  char[BUFFER_SIZE + 1] 
   .next:     struct s_fd_offset_list *;

*/
typedef struct s_fd_str_list
{
	int						fd;
	char					str[BUFFER_SIZE + 1];
	struct s_fd_str_list	*next;
}	t_fd_str_list;

char		*get_next_line(int fd);

char		*ft_strchr(const char *s, int c);

void		free_list(t_str_list *list);

int			line_len_from_list(t_str_list *list);

t_str_list	*new_str_list_node(char *str, t_str_list *next);

#endif
