/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:17:16 by juli              #+#    #+#             */
/*   Updated: 2023/11/24 17:46:20 by Philip Li        ###   ########.fr       */
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
} t_str_list;


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
} t_fd_str_list;

char	*get_next_line(int fd);

char	*ft_strdup(const char *s);

void	*ft_memset(void *s, int c, size_t n);

char	*ft_strchr(const char *s, int c);

int		free_list(t_str_list *list);

int		ft_strlen(const char *s);

#endif
