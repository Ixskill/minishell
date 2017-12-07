#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser_lr.h"

/*
**	renvoie les symboles apres le point dans de la gramar_rule
*/

struct s_morpheme_lst *get_point(struct s_parser_lr *lr, \
								 int gramar_rule, \
								 int point)
{
	return (ft_genlst_get_n(lr->grammar_rules[gramar_rule].childs, point));
}

struct s_item *lr_closure(struct s_parser_lr *lr, struct s_item *kernel)
{
	struct s_item	*cur = NULL;
	struct s_item	*res = NULL;	//res pointe sur le debut de cur;
	enum e_token	a;
	int				added = 0;

	cur = dup_item_lst(kernel);
	//printf("lr_closure-- kernel: "); debug_item_lst(lr, cur); //printf("\n"); 
	res = cur;
	while (cur)
	{
		a = cur->look_ahead;
		struct s_morpheme_lst *B = get_point(lr, cur->grammar_rule, cur->point);
		if (!B || !(IS_SYMBOL(B->m)))
		{
			cur = cur->next;
			continue ;
		}
		struct s_morpheme_lst *beta = dup_morpheme_lst(B->next);
		ft_genlst_pushback((void **)&beta, new_morpheme_lst(a));
		//printf("beta a: ");debug_morpheme_lst(beta);//printf("\n");
		struct s_morpheme_lst *firsts = lr_first(lr, beta);
		//printf("firsts: "); debug_morpheme_lst(firsts); //printf("\n");
		int		i = get_first_grammar_rule(lr->grammar_rules, B->m);
/*
**	each production B → γ in G ′ , and each terminal b ∈ FIRST ( βa) such that 
**	[ B → .γ,b ] 6∈ I do add [ B → .γ,b ] to I, here gama is represented by i
*/
		while (i < NB_RULES && lr->grammar_rules[i].node == B->m)
		{
			//printf("gama: ");debug_grammar_rule(lr, i);//printf("\n");
			struct s_morpheme_lst *tmp = firsts;
			while (tmp)
			{
				item_pushback_unique(&res, i, 0, tmp->m);
				//printf("cur first: ");debug_morpheme_node(tmp);//printf("\n");
				tmp = tmp->next;
			}
			i++;
		}
		//free(beta);
		cur = cur->next;
	}
	return (res);
}

/*
** let J be the set of items [A → αX.β, a] such that
** [A → α.Xβ, a] is in I;
*/

struct s_item *construct_J(struct s_parser_lr *lr, \
						   struct s_item *item_lst, \
						   struct s_item *cur, \
						   t_morpheme X)
{
	int				cur_found = 0;
	struct s_item *J = NULL;

	while (item_lst)
	{
		if (item_lst == cur)
			cur_found = 1;
		struct s_morpheme_lst *Y = get_point(lr, item_lst->grammar_rule, item_lst->point);
		if (!Y)
		{
			item_lst = item_lst->next;
			continue ;
		}
		if (Y->m == X)
		{
			if (!cur_found)
				return (NULL);
			ft_genlst_pushback((void *)&J, new_item(item_lst->grammar_rule, item_lst->point + 1, item_lst->look_ahead));
		}
		item_lst = item_lst->next;
	}
	return (J);
}
/*
**search a in lst
*/
int		search_item_lst(struct s_item *lst, struct s_item *a)
{
	while (lst)
	{
		if (lst->point == a->point && lst->grammar_rule == a->grammar_rule && lst->look_ahead == a->look_ahead)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int		equal_item_lst(struct s_item *a, struct s_item *b)
{
	if (!a)
		//printf("a is NULL in equal item_lst\n");
	if (!b)
		//printf("b is NULL in equal item_lst\n");
	if (ft_genlst_len(a) != ft_genlst_len(b))
		return (0);
	while (a && b)
	{
		if (!search_item_lst(a, b))
			return (0);
		b = b->next;
	}
	return (1);
}

struct s_line *kernel_is_in_C(struct s_line *C, struct s_item *new_kernel)
{
	while (C)
	{
		if (equal_item_lst(C->kernel, new_kernel))
			return (C);
		C = C->next;
	}
	return (NULL);
}

/*
** goto prend une line avec un set d item, et pushback des lines sur line
** If [A → α.aβ, b] is in Ii and goto(Ii, a) = Ij , 
** then set action[i, a] to ”shift j”.
** Here a must be a terminal.
** if goto(Ii, A) = Ij then goto[i,A] = j
*/

void	lr_goto(struct s_parser_lr *lr, \
			    struct s_line **res, \
				struct s_line *cur_line)
{
	struct s_item *new_kernel = NULL;
	struct s_item *cur = cur_line->closure;
	struct s_item *J = NULL;

	while (cur)
	{
		struct s_morpheme_lst *X = get_point(lr, cur->grammar_rule, cur->point);
		/*
		 ** If [A → α., a] is in Ii, then set action[i,a] to reduce A → α. Here A may
		 not be S′
		 */
		if (!X || X->m == DOLLAR)
		{
			if (cur->grammar_rule == 0 && cur->point == 1 && cur->look_ahead == DOLLAR)
			{
				if (cur_line->action_table[X->m - FIRST_TOKEN] != -1)
				{
					printf("conflict rule:%d symbol:\n", ft_genlst_index_of(*res, cur_line));
					debug_token(X->m);
				}
				cur_line->action_table[X->m - FIRST_TOKEN] = acc; //it is [S′ → S., $] i
			}
			else
			{
				if (cur_line->action_table[cur->look_ahead - FIRST_TOKEN] != -1)
				{
					printf("conflict rule:%d symbol:\n", ft_genlst_index_of(*res, cur_line));
					debug_token(X->m);
				}
				cur_line->action_table[cur->look_ahead - FIRST_TOKEN] = FIRST_REDUCE_RULE + cur->grammar_rule;
				if (cur->grammar_rule > 110)
					printf("error wrong nb of grammar rule\n");
			}
			cur = cur->next;
			continue ;
		}
		if ((new_kernel = construct_J(lr, cur_line->closure, cur, X->m)))
		{
			//printf("lr_goto-- kernel: "); debug_item_lst(lr, new_kernel); //printf("----\n"); 
			struct s_line *n_line = kernel_is_in_C(*res, new_kernel);
			if (!n_line)
			{
				n_line = new_line(0, new_kernel, lr_closure(lr, new_kernel));
				ft_genlst_pushback((void **)res, n_line);
			}
			int j = ft_genlst_index_of(*res, n_line);
			//printf("-----------------------\n");
			//            debug_token(X->m);
			//printf("\n-----------------------\n");
			if (IS_SYMBOL(X->m))
			{
				if (cur_line->goto_table[X->m - FIRST_SYMBOL] != -1)
				{
					printf("conflict rule:%d symbol:\n", ft_genlst_index_of(*res, cur_line));
					debug_symbol(X->m);
				}
				cur_line->goto_table[X->m - FIRST_SYMBOL] = j;	//set goto(i, X) = j 
			}
			else if (IS_TOKEN(X->m))
			{
				if (cur_line->action_table[X->m - FIRST_TOKEN] != -1)
				{
					printf("conflict rule:%d symbol:\n", ft_genlst_index_of(*res, cur_line));
					debug_token(X->m);
				}
				cur_line->action_table[X->m - FIRST_TOKEN] = j; //set swich(i, X) = j 
			}
			else
				printf("error is not a token neither a symbol\n");
		}
		cur = cur->next;
	}
}

/*
 **for each set of items I in C and each grammar symbol X
 **such that goto(I, X) is not empty and not in C do
 **add goto(I, X) to C
 */

struct s_line *lr_items(struct s_parser_lr *lr)
{
	struct s_line	*res = NULL;
	struct s_line	*cur = NULL;
	struct s_item	*initial_kernel;

	initial_kernel = new_item(0, 0, DOLLAR);
	cur = new_line(0, initial_kernel, lr_closure(lr, initial_kernel));
	res = cur;
	while (cur != NULL)
	{
		//	debug_line(lr, cur);
		//printf("\n");
		lr_goto(lr, &res, cur);
		cur = cur->next;
	}
	return (res);

}

int main(void)
{
	struct	s_parser_lr lr;
	struct s_line	*res = NULL;
	int		i;

	ft_bzero(&lr, sizeof(struct s_parser_lr));
	init_grammar_rules(&lr);
	debug_gramar(&lr);
	i = get_first_grammar_rule(lr.grammar_rules, start_symbol);
	debug_grammar_rule(&lr, i);
	init_firsts(&lr);
	debug_firsts(&lr);
	res = lr_items(&lr);
	printf("\n ----------------closure table---------------- \n");
	debug_closure_table(&lr, res);
	printf("\n\n");
	debug_action_table(&lr, res);
	printf("\n\n");
	debug_goto_table(&lr, res);
	generate_automaton(&lr, res);
	return 0;
}