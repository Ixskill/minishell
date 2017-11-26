/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_subst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:27 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

int		lex_action_cmd_subst_backquotes(t_lexer *lex, \
		struct s_info **state_info, struct s_info *info)
{
	if (lex->line[lex->pos] == '`')
	{
		if (info->count == 0)
		{
			consume_input(lex);
		}
		else
		{
			pop_state(lex, state_info);
			consume_input(lex);
		}
	}
	else if (lex->line[lex->pos] == '"')
		push_state(lex, DQUOTES);
	else if (lex->line[lex->pos] == '\'')
		push_state(lex, QUOTES);
	else if (lex->line[lex->pos] == '$')
		push_state(lex, PARAM_EXP);
	else
		consume_input(lex);
	return (TRUE);
}

int		lex_action_cmd_subst_paren_p2(t_lexer *lex, struct s_info **state_info,\
		struct s_info *info)
{
	if (lex->line[lex->pos] == ')')
	{
		if (info->nest == 0)
		{
			consume_input(lex);
			pop_state(lex, state_info);
		}
		else
		{
			info->nest--;
			consume_input(lex);
		}
	}
	else
		consume_input(lex);
	return (TRUE);
}

int		lex_action_cmd_subst_paren(t_lexer *lex, struct s_info **state_info,\
		struct s_info *info)
{
	if (lex->line[lex->pos] == '(')
	{
		if (info->count == 2)
		{
			consume_input(lex);
			change_state(lex, AR_EXP);
		}
		else
		{
			info->nest++;
			consume_input(lex);
		}
	}
	else if (lex->line[lex->pos] == '"')
		push_state(lex, DQUOTES);
	else if (lex->line[lex->pos] == '\'')
		push_state(lex, QUOTES);
	else if (lex->line[lex->pos] == '$')
		push_state(lex, PARAM_EXP);
	else
		lex_action_cmd_subst_paren_p2(lex, state_info, info);
	return (TRUE);
}

int		lex_action_cmd_subst(t_lexer *lex, struct s_info **state_info)
{
	struct s_info *info;

	info = lex->state->data;
	if (lex->line[lex->pos] == 0)
		return (FALSE);
	else if (lex->line[lex->pos] == '\\')
		push_state(lex, BS);
	else if ((!info->value.str && lex->line[lex->pos] == '`') \
			|| info->value.str[0] == '`')
		lex_action_cmd_subst_backquotes(lex, state_info, info);
	else
		lex_action_cmd_subst_paren(lex, state_info, info);
	return (TRUE);
}
