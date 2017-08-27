/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_refresh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:20 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

void	btsearch_refresh(t_line *line, t_hist *h)
{
	char	*search_line;

	edit_refresh_clear(line);
	move_cursor_lastline(line);
	ft_putchar('\n');
	search_line = (h->btsearch_cur == NULL) ? "failing bck-i-search: " : \
				"bck-i-search: ";
	search_line = ft_strjoin_free(search_line, h->btsearch_buff, 0);
	edit_refresh_nchar(line, 0, search_line, ft_strlen(search_line));
	ft_putchar('_');
	put_ntermcap("up", ft_strlen(search_line) / line->ws_col + 1);
	move_cursor_firstline_from_lastline(line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
	free(search_line);
	(void)h;
}