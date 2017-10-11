/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_control_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:58 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

/*
**	When CTRL-D is read, if the line is empty :
**	- if we're on the main LE, exit.
**	- if we're on heredoc LE, terminate le, return line->buff.
**
**	If line isnt empty, delete, delete char under the cursor if it exists.
*/

int		control_d(t_line *line)
{
	if (line->len == 0)
	{
		ft_putchar('\n');
		exit(0);
	}
	return (edit_del(line));
}

char	*control_d_heredoc(t_line *line)
{
	edit_add(4, line);
	return (edit_exit(line));
}
