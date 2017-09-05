#ifndef NO_TERMCAPS
#include "history.h"
#include <stdio.h>
#include <errno.h>

void	history_refresh_command(t_hist *h, char *command)
{
	write(h->fd, command, ft_strlen(command));
}

void	history_refresh(char *command)
{
	t_hist		*h;
	t_list_d	*list;

	h = singleton_hist();
	if (command[0] == '\0')
		return ;
	list = ft_double_lst_create(ft_strdup(command));
	if (h->list == NULL)
		h->list = ft_create_head(list);
	else
		ft_double_lst_add(&h->list, list);
	history_refresh_command(h, command);
}
#endif
