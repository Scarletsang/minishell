/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:04:50 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/26 13:51:36 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	minishell_vars_export(struct s_minishell_vars *vars, \
const t_sb *key_and_value)
{
	char	*value;
	char	*key;

	value = minishell_vars_database_get(&vars->shell, key_and_value);
	if (!value)
	{
		if (minishell_vars_database_set(&vars->shell, key_and_value) || \
			minishell_vars_database_set(&vars->environment, key_and_value))
			return (EXIT_FAILURE);
	}
	else
	{
		key = minishell_vars_extract_key(key_and_value);
		if (ht_set(&vars->environment, key, value, free))
		{
			free(key);
			return (EXIT_FAILURE);
		}
		free(key);
	}
	return (EXIT_SUCCESS);
}

void	minishell_vars_unset(struct s_minishell_vars *vars, \
const t_sb *key_and_value)
{
	char	*key;

	key = minishell_vars_extract_key(key_and_value);
	if (!key)
		key = (char *) key_and_value->buffer;
	ht_del(&vars->shell, key);
	ht_del(&vars->environment, key);
	free(key);
}

char	*minishell_vars_echo(struct s_minishell_vars *vars, \
const t_sb *key_and_value)
{
	char	*result;

	result = minishell_vars_database_get(&vars->environment, key_and_value);
	if (!result)
		result = minishell_vars_database_get(&vars->shell, key_and_value);
	return (result);
}
