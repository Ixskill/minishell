/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:52 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_simple_lst_pushback(t_list **first, t_list *new_node)
{
	t_list	*tmp;
	t_list	*old_tmp;

	if (new_node)
	{
		if (first == NULL || *first == NULL)
			*first = new_node;
		else
		{
			tmp = *first;
			old_tmp = tmp;
			while (tmp)
			{
				old_tmp = tmp;
				tmp = tmp->next;
			}
			old_tmp->next = new_node;
		}
	}
}

void	ft_double_lst_pushback(t_lst_head **head, t_list_d *new_node)
{
	t_list_d	*prev;

	if (new_node)
	{
		if ((*head)->last)
		{
			prev = (*head)->last;
			new_node->prev = prev;
			prev->next = new_node;
			(*head)->last = new_node;
			(*head)->shift_middle += 1;
			(*head)->node_count += 1;
		}
		else
		{
			(*head)->node_count += 1;
			(*head)->last = new_node;
			(*head)->middle = new_node;
		}
	}
	ft_lst_replace_middle(head);
}
