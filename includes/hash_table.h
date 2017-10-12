/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:42:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/12 16:32:18 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H
# include "env.h"

# define HASH_TABLE_SIZE 998

void	free_hash_table(t_list ***has_table);
char	*hash_get(t_list **hash_table, char *value);
int		create_hash_table(t_list ***hash_table, char **environ);
#endif
