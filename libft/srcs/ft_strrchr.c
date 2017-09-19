/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*found;
	const char	*tmp;

	if (c == 0)
		return (ft_strchr(s, 0));
	found = NULL;
	while ((tmp = ft_strchr(s, c)))
	{
		found = tmp;
		s = tmp + 1;
	}
	return ((char*)found);
}

ssize_t	ft_strrichr(const char *s, int c)
{
	char	*ptr;

	ptr = ft_strrchr(s, c);
	return ((ptr) ? ptr - s : -1);
}
