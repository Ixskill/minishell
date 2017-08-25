#include "completion.h"
#include "line_editing.h"
	#include <stdio.h>
#include <string.h>

void	create_ternary_tree_dir(char *dir_path, t_env *env)
{
	struct dirent	*dirent;
	DIR		*dir;

	dir = NULL;
	if (!(dir = opendir(dir_path)))
		return ;
	while ((dirent = readdir(dir)) != NULL)
	{
		//	printf("\nd_name: %s \n", dirent->d_name);
		if (dirent->d_name[0] != '.' && ft_is_executable(dir_path, dirent->d_name))
		{
			if (!env->tree)
			{
				if ((dirent = readdir(dir)) != NULL )
					env->tree = ternary_tree_new_down(dirent->d_name, dirent->d_name);
//				ternary_tree_print(env->tree);
			}
			else
			{
				ternary_tree_add(env->tree, dirent->d_name, dirent->d_name);
			}
		}

	}
//	printf("\n TEST \n");
	//ternary_tree_print(env->tree);
	closedir(dir);
}

void	free_ternary_tree(t_ternary_tree *node)
{
	t_ternary_tree	*left;
	t_ternary_tree	*down;
	t_ternary_tree	*right;

	if (!node)
		return ;
	/*
**		printf("c is %c\n", node->c);
**		if (node->match)
**			printf("match is %s\n", node->match);
**		if (node->left)
**			printf("\n left \n");
*/
	left = node->left;
	right = node->right;
	down = node->down;
	if (node->match)
	{
		free(node->match);
	//	printf("match is %s\n", matches[*i]);
	}
	free_ternary_tree(left);
	/*
**		if (node->down)
**			printf("\n down \n");
*/
	free_ternary_tree(down);
	//put_termcap("do");
	/*
**		if (node->right)
**			printf("\n right\n");
*/
	free_ternary_tree(right);
	free(node);
}

int	create_ternary_tree(t_env *env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!(path = env_getenv((const char**)env->environ, "PATH", NULL)))
		return (0);
	paths = ft_strsplit(path, ":");
	while (paths[i])
	{
		create_ternary_tree_dir(paths[i], env);
		i++;
	}
	//ternary_tree_print(env->tree);
	ft_arraydel(&paths);
	return (1);
}
