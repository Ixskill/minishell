#include "exec.h"
/*
**	list             : list separator_op and_or
**	                 |                   and_or
*/

int exec_list(t_ast *ast)
{
	if (ast->child[0] && !ast->child[2])
		return (exec(ast->child[0]));
	if (ast->child[0] && ast->child[2])
	{
		exec(ast->child[0]);
		return (exec(ast->child[2]));
	}
}
