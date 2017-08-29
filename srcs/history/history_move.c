/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/29 05:43:32 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "stdio.h"

int		strnequ_writen_buff(void *data)
{
	int len;

	len = ft_strlen(singleton_hist()->writen_buff);
	if (len == 0)
		return (1);
	if (ft_strnequ(data, singleton_hist()->writen_buff, len))
		return (1);
	return (0);
}

void	history_line_refresh(t_line *line, char *new_line)
{
	edit_refresh_clear(line);
	ft_strclr(line->buff);
	edit_insert_str(line, line->buff, new_line);
	line->len = ft_strlen((const char *)new_line);
	line->pos = line->len;
	put_prompt(line);
	edit_refresh_line(line);
}

int		history_next(t_line *line, t_hist *h)
{
	t_list_d	*tmp;

	tmp = NULL;
	tmp = ft_double_lst_return_if((h->cur) ? h->cur->next : h->list->first, \
			strnequ_writen_buff, 1);
	if (tmp)
	{
		h->cur = tmp;
		history_line_refresh(line, h->cur->data);
	}
	else
		put_termcap("bl");
	return (1);
}

int		history_prev(t_line *line, t_hist *h)
{
	t_list_d	*tmp;

	tmp = NULL;
	tmp = ft_double_lst_return_if((h->cur) ? h->cur->prev : NULL, \
			strnequ_writen_buff, 2);
	if (tmp)
	{
		h->cur = tmp;
		history_line_refresh(line, h->cur->data);
	}
	else
	{
		put_termcap("bl");
		line->pos = ft_strlen(h->writen_buff);
	}
	return (1);
}

int		history_move_init(t_line *line, t_hist *h)
{
	if (h->writen_buff)
		ft_strcpy(h->writen_buff, line->buff);
	return (1);
}

int		history_move_exit(t_line *line, t_hist *h)
{
	ft_strclr(h->writen_buff);
	(void)line;
	return (1);
}
