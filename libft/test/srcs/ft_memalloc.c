/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:03:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/24 19:39:11 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alloc.h"
#include "str.h"
#include "mem.h"
#include "color.h"

/*
**	Allocates a memory and puts it to zero.
**	This function is meant to allocate memory for strings
*/

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (size)
		mem = malloc(size);
	else
		mem = NULL;
	if (!mem)
	{
		ft_putendl(RED"Memalloc exit\n"RESET);
		exit(1);
	}
	ft_bzero(mem, size);
	return (mem);
}
