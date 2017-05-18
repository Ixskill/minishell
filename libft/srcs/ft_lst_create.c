/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:07:04 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/11 13:31:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_simple_lst_create(void *data)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	new_node->next = NULL;
	new_node->data = data;
	return (new_node);
}

t_list_d	*ft_double_lst_create(void *data)
{
	t_list_d	*new_node;

	new_node = malloc(sizeof(t_list_d));
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->data = data;
	return (new_node);
}

t_lst_head	*ft_create_head(t_list_d *first)
{
	t_lst_head	*head;

	head = malloc(sizeof(t_lst_head));
	head->first = first;
	head->middle = first;
	head->last = first;
	head->shift_middle = 0;
	head->node_count = 1;
	return (head);
}