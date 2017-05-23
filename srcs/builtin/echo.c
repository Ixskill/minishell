#include "libft.h"
#include "env.h"
#include <stdio.h>

static const char **parse_options(const char **argv, short int *n_flag)
{
	char	*option_array[2];

	option_array[0] = "-n";
	option_array[1] = NULL;
	while (ft_arraychr((const char**)option_array, (const char*)*argv))
	{
		if (ft_strequ(*argv, "-n"))
			*n_flag = true;
		argv++;
	}
	return (argv);
}


int	builtin_echo(t_env *env, const char **argv)
{
	short int n_flag;
	const char	**tmp;

	(void)env;
	n_flag = false;
	argv = parse_options(argv + 1, &n_flag);
	tmp = argv;
	while (*argv)
	{
		ft_putstr(*argv);
		if (*(argv + 1))
			ft_putchar(32);
		argv++;
	}
	if (!n_flag)
		ft_putchar('\n');
	else if (n_flag && *tmp)
		ft_putendl("\033[30m\033[47m%\x1b[0m");
	return (EXIT_SUCCESS);
}
