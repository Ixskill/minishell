/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:37 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "syntax_coloring.h"
#include "libft.h"

int		lex_action_default_le(t_lexer *lex, struct s_info **state_info, \
		t_line *line)
{
	if (lex->line[lex->pos] == 0)
		return (TRUE);
	if (lex->line[lex->pos] == ' ' || lex->line[lex->pos] == '\t')
		push_state_le(lex, WHITESPACE);
	else if (lex->line[lex->pos] == '\n')
		push_state_le(lex, NEWLINE);
	else if (CHAR_IS_OPERATOR(lex->line[lex->pos]))
		push_state_le(lex, OPERATOR);
	else if (lex->line[lex->pos] == '#')
		push_state_le(lex, COMMENT);
	else
		push_state_le(lex, WORD);
	(void)state_info;
	(void)line;
	return (TRUE);
}
