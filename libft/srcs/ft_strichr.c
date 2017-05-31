/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strichr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 01:12:18 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/31 16:05:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "mem.h"
#include "libft.h"
#include <stdio.h>

static void	align_memory(const char **s, char c)
{
	while (**s && **s != c && (((t_ulong)*s & (ULONG_SIZE - 1)) != 0))
		(*s)++;
}

static char *get_diff_end(const char *cp, char c)
{
	if (*cp == '\0')
		return NULL;
	else if (*++cp == c)
		return (char *) cp;
	if (*cp == '\0')
		return NULL;
	else if (*++cp == c)
		return (char *) cp;
	if (*++cp == c)
		return NULL;
	else if (*++cp == c)
		return (char *) cp;
	 if (*cp == '\0')
		return NULL;
	else if (*cp == '\0')
		return (char *) cp;
	return (NULL);
}

static char *get_diff_start(const char *cp, char c)
{
	if (*cp == '\0')
		return NULL;
	else if (*cp == c)
		return (char *) cp;
	if (*cp == '\0')
		return NULL;
	else if (*++cp == c)
		return (char *) cp;
	if (*cp == '\0')
		return NULL;
	else if (*++cp == c)
		return (char *) cp;
	if (*cp == '\0')
		return NULL;
	else if (*++cp == c)
		return (char *) cp;
	return (get_diff_end(cp, c));
}

ssize_t	ft_strichr(const char *s, int c_in)
{
	const unsigned long int *longword_ptr;
	unsigned long int longword;
	char	*ret;
	const char	*origin;

	origin = s;
	align_memory(&s, (char)c_in);
	if (*s == (char)c_in)
		return	(s - origin);
	else if (*s == '\0')
		return (-1);
	longword_ptr = (unsigned long int*) s;
	while (42)
	{
		longword = *longword_ptr++;
		if ((HAS_ZERO(longword)) || (HAS_VALUE(longword, CHAR_TO_LONG(c_in))))
		{
			(ret = get_diff_start((const char*)(longword_ptr - 1), (char)c_in));
			if (!ret)
				return (-1);
			else
				return (ret - origin);
		}
	}
	return (-1);
}
