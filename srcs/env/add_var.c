#include "env.h"
#include "libft.h"
#include <stdio.h>

void		env_add_var(t_env *env, const char *key, const char *value)
{
	char		**environ;
	char		**new_environ;
	char		*new_key_value;
	size_t	new_environ_size;

	environ = env->environ;
	new_environ_size = env->environ_size + 1;
	new_environ = palloc(sizeof(char*) * (new_environ_size + 1), __func__);
	new_key_value = ft_strsurround(key, "=", value);
	ft_addrcpy((void**)new_environ, (const void**)environ, env->environ_size);
	new_environ[new_environ_size - 1] = new_key_value;
	new_environ[new_environ_size] = NULL;
	free(env->environ);
	env->environ = new_environ;
	env->environ_size++;
}

void		env_change_value(t_env *env, const char *key, size_t key_index, const char *new_value)
{
	char	**environ;

	environ = env->environ;
	free(environ[key_index]);
	environ[key_index] = ft_strsurround(key, "=", new_value);
}

void		env_add_change(t_env *env, const char *key, const char *value)
{
	size_t	index;

	if (!(env_getenv((const char**)env->environ, key, &index)))
		env_add_var(env, key, value);
	else
		env_change_value(env, key, index, value);
}

void		env_add_var_from_string(t_env *env, char *key_value, ssize_t eq_index)
{
	key_value[eq_index] = '\0';
	env_add_change(env, (const char*)key_value, \
		(const char*)key_value + eq_index + 1);
}
