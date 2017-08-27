/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 04:09:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 04:09:17 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

/*
**	Initialize the token_start index and returns the state according to the
**	first char of the token.
*/

int		start_token(t_lexer *lex, size_t *token_start)
{
	int		ret;

	ret = 0;
	while (lex->line[lex->index] && IS_WHITESPACE(lex->line[lex->index]))
		lex->index++;
	*token_start = lex->index;
	ret = update_state(lex);
	lex->index++;
	return (ret);
}
