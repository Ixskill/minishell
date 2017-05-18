/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:42:12 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/08 16:23:22 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_str_realloc(size_t ptr_data_size, void *ptr, size_t size)
{
	void	*new_memory;

	if (!ptr) {
		return (palloc(size, __func__));
	} else if (size == 0) {
		free(ptr);
		return (NULL);
	} else {
		new_memory = palloc(size, __func__);
		ft_memcpy(new_memory, ptr, ptr_data_size);
		free(ptr);
	}
	return (new_memory);
}

void	**ft_array_realloc(size_t ptr_data_size, void **ptr, size_t size)
{
	void	**new_memory;

	if (!ptr) {
		return (palloc(size, __func__));
	} else if (size == 0) {
		free(ptr);
		return (NULL);
	} else {
		new_memory = palloc(size, __func__);
		ft_addcpy(new_memory, (const void **)ptr, ptr_data_size);
		free(ptr);
	}
	return (new_memory);
}

void	**ft_array_remove(int index, size_t ptr_data_size, void **ptr)
{
	void	**new_memory;
	int	size;

	size = ptr_data_size - 1;
	if (!ptr) {
		return (palloc(size, __func__));
	} else if (size == 0) {
		free(ptr);
		return (NULL);
	} else {
		new_memory = palloc(size, __func__);
		ft_addcpy(new_memory, (const void **)ptr, index);
		ft_addcpy(new_memory + index, (const void **)(ptr + index + 1), size - index);
		free(ptr);
	}
	return (new_memory);
}