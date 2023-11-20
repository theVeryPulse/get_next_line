/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:17:16 by juli              #+#    #+#             */
/*   Updated: 2023/11/20 20:11:56 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define ERROR (-1)

/* Linked list, each node contains the character content, its offset,
   and pointer to the next node */
typedef struct s_char_list
{
	char				c;
	struct s_char_list	*next;
} t_char_list;


/* Save the previous offset for files when calling get_next_line
   function.

   int fd; int offset; struct s_fd_offset_list *next;

   t_fd_buffer_list
   | fd:int, offset:int;
   | fd:int, offset:int;
   | ...
*/
typedef struct s_fd_buffer_list
{
	int						fd;
	char					*buffer;
	struct s_fd_buffer_list	*next;
} t_fd_buffer_list;

#endif
