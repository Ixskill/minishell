/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 12:51:27 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/26 15:56:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Exhaustive list of all shell operators
*/

static const char	*g_operator_list[] = {
	"<",
	">",
	";",
	"|",
	"&",
	"&&",
	"||",
	";;",
	"<<",
	">>",
	"<&",
	">&",
	"<>",
	"<<-",
	">|",
	NULL
};

/*
**	This function has 2 purposes :
**
**				DELIMITING TOKENS
**	When delimiting tokens, if we are currently reading an operator, if the
**	char we are reading is an operator, it will either be appended to our
**	operator token or will delimit it depending on wether or not it can create
**	a valid operator if joined with the last one. This function will return 1
**	if the 'new operator' is valid, 0 otherwise.
*/

int					match_operator(const char *value, size_t token_start, \
		size_t token_end)
{
	const char	*tmp_token;
	size_t		diff;
	int			i;

	i = 0;
	diff = token_end - token_start + 1;
	tmp_token = value + token_start;
	while (g_operator_list[i] != NULL && \
			!ft_strnequ(g_operator_list[i], tmp_token, diff))
		i++;
	if (g_operator_list[i] != NULL)
		return (1);
	return (0);
}

/*
**				ASSIGNING TOKEN ID
**	If used on a valid string, it will load the token_id variable (if pointer
**	exists) with the defined value for this exact token. See INCLUDES/LEXER.H
*/

t_token_id			id_operator(const char *value)
{
	int		i;

	i = 0;
	while (g_operator_list[i] != NULL && !ft_strequ(g_operator_list[i], value))
		i++;
	if (g_operator_list[i])
		return (i + 5);
	return (-1);
}
