/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "hash_table.h"
#include "builtin.h"
#include "t_env.h"
#include "read.h"
#include "local.h"
#include "line_editing.h"
#include "history.h"
#include "exec.h"

static char			**split_values(char *line, t_read options)
{
	char			**values;
	char			*word;

	values = (char **)ft_parrnew();
	word = ft_strnew(0);
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line)
	{
		if (*line == '\\' && *(line + 1) && !(options.flags & R))
			backslash(&line, &word, 1);
		else
			ft_strpush(&word, *line++);
		if (*line == ' ' || *line == '\t')
		{
			ft_parrpush((void***)&values, word);
			word = ft_strnew(0);
		}
		while (*line == ' ' || *line == '\t')
			line++;
	}
	!*word ? free(word) : ft_parrpush((void***)&values, word);
	return (values);
}

static void			assign_values(char **vars, char **values, t_env *env)
{
	char			ptr;
	size_t			index;
	size_t			len;
	unsigned char	path;

	while (*vars)
	{
		ptr = (env_getenv((const char**)env->environ, *vars, &index)) ? 1 : 0;
		len = ft_strlen(*vars);
		path = (!ft_strcmp("PATH", *vars)) ? 1 : 0;
		ft_strpush(vars, '=');
		if (*values)
			ft_strspush(vars, *values++);
		while (!*(vars + 1) && *values)
		{
			ft_strpush(vars, ' ');
			ft_strspush(vars, *values++);
		}
		ptr ? env_add_var_from_string(env, *vars, len) :
			local_add_change_from_string(env, *vars);
		if (path)
			env_reload_tree_hash(env);
		vars++;
	}
}

static char			parse_option(t_read *options, const char ***args)
{
	char			*option;

	while (*++*args && ***args == '-')
	{
		option = (char*)**args + 1;
		if (!(parse_read(option, options, (char***)args)))
			return (0);
	}
	return (1);
}

static void			set_value(char *value, char **argv, t_env *env,
		t_read options)
{
	char			**split;

	split = split_values(value, options);
	assign_values((char**)argv, split, env);
	ft_arraydel(&split);
	free(value);
}

int					builtin_read(t_env *env, const char **argv)
{
	int				error;
	t_read			options;
	t_line			*line;
	char			*values;

	(void)env;
	line = singleton_line();
	ft_bzero(&options, sizeof(t_read));
	options.delim = '\n';
	if (!(error = parse_option(&options, &argv)) || error == 2)
		return (!(error) ? 2 : 1);
	if (singleton_jc()->shell_is_interactive && isatty(options.fd))
	{
		conf_term_non_canonical();
		load_prompt(env, line, NULL, \
				options.prompt ? options.prompt : "read> ");
		put_prompt(line);
		values = read_get_input(options);
		ft_putstr("\n");
		conf_term_canonical();
	}
	else
		values = read_get_rcinput(options);
	set_value(values, (char **)argv, env, options);
	return (0);
}
