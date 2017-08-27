/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:07:46 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"

t_comple	*singleton_comple(void)
{
	static t_comple c;

	return (&c);
}

int			comple_init_winch(t_comple *c)
{
	unsigned int	n;

	n = c->nb_matches;
	c->ws_col = get_ws_col();
	c->ws_row = get_ws_row();
	c->nb_colones = get_ws_col() / (c->max_len + 2);
	if (c->nb_colones == 0)
		return (0);
	c->nb_lines = (n % c->nb_colones == 0) ? n / c->nb_colones :
		(n / c->nb_colones) + 1;
	return (1);
}

int			comple_init(t_line *line, t_comple *c)
{
	ft_bzero(c, sizeof(t_comple));
	c->matches = comple_matching(line, c);
	free(c->current_word);
	c->max_len = ft_arraymax_f((char**)c->matches, ft_strlen_color);
	c->nb_matches = ft_arraylen((const char**)c->matches);
	if (comple_init_winch(c) == 0)
		return (0);
	c->pos = -1;
	if (c->nb_matches == 1)
	{
		c->pos = 0;
		comple_exit_matched(line, *c, 0);
		return (0);
	}
	else if (c->nb_matches == 0)
	{
		comple_exit_matched(line, *c, 0);
		return (0);
	}
	return (1);
}