/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:17:16 by juli              #+#    #+#             */
/*   Updated: 2023/11/22 19:42:13 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/* Linked list, each node contains the character content, its offset,
   and pointer to the next node */
typedef struct s_char_list
{
	char				*content;
	struct s_char_list	*next;
} t_char_list;


/* Save the previous offset for files when calling get_next_line
   function.

   .fd:       int
   .content:  char * 
   .next:     struct s_fd_offset_list *;

   t_fd_buffer_list
   | fd: int, buffer: string, ...
   | fd: int, buffer: string, ...
   | ...
*/
typedef struct s_fd_buffer_list
{
	int						fd;
	char					*content;
	struct s_fd_buffer_list	*next;
} t_fd_buffer_list;

char	*get_nex_line(int fd);

char	*ft_strdup(const char *s);

void	*ft_memset(void *s, int c, size_t n);

char	*ft_strchr(const char *s, int c);

int	free_list(t_char_list *list);

int	ft_strlen(const char *s);

#endif
