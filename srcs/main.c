/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:54:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/26 13:54:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"

int	main(void)
{
	extern const char	**environ;

	env_load_base_env(singleton_env(), environ);
	conf_term_in();
	main_loop(singleton_env());
	env_free_env(singleton_env());
	return (0);
}
