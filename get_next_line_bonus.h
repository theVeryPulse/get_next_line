/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:17:16 by juli              #+#    #+#             */
/*   Updated: 2023/11/29 18:34:19 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (25)
# endif
# ifndef FD_MAX
#  define FD_MAX (4096)
# endif

/* Linked list: Each node contains buffer for read() function
   and a pointer to the next node */
typedef struct s_str_list
{
	char				str[BUFFER_SIZE + 1];
	struct s_str_list	*next;
}	t_str_list;

char	*get_next_line(int fd);

char	*ft_strchr(const char *s, int c);

int		free_list(t_str_list *list);

int		ft_strlen(const char *s);

int		total_strlen_from_list(t_str_list *list);

void	free_all(t_str_list *list, char *buffer);

void	read_until_eol_or_eof_and_save_excess(int fd, char *tmp_buffer,
			t_str_list **head, char **fd_buffer);

void	cut_line_into_buffer(char *fd_buffer, char *tmp_buffer);

void	save_to_fd_buffer(char **fd_buffer, char *source);

void	add_until_eol_to_list(t_str_list **head, char *buffer);

char	*list_to_line(t_str_list *list);
#endif
