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
	history_load(singleton_hist());
	main_loop(singleton_env());
	env_free_env(singleton_env());
	return (0);
}


