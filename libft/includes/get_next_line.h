/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 15:54:17 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/22 18:38:45 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 100
# include <stdlib.h>

typedef struct	s_l
{
	int			fd;
	struct s_l	*next;
	char		*stock;
	size_t		stock_size;
}				t_l;

int				get_next_line(const int fd, char **line);
#endif
