/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip Li <LJHR.UK@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:00 by juli              #+#    #+#             */
/*   Updated: 2023/11/18 11:40:27 by Philip Li        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

typedef struct s_linked_list
{
	size_t			i;
	char			c;
	t_linked_list	*next;
} t_linked_list;


char	*get_next_line(int fd)
{
	ssize_t
}
