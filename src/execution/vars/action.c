/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:04:50 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/31 21:48:55 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	minishell_vars_declare(struct s_minishell_vars *vars, const char *key, \
const char *value)
{
	const char	*entry_in_environment;

	if (minishell_vars_database_set(&vars->shell, key, value))
		return (EXIT_FAILURE);
	entry_in_environment = minishell_vars_database_get(&vars->environment, key);
	if (entry_in_environment && ht_update(&vars->environment, key, \
		value, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	minishell_vars_export(struct s_minishell_vars *vars, const char *key)
{
	if (!ht_update(&vars->environment, key, \
		minishell_vars_database_get(&vars->shell, key), NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	minishell_vars_unset(struct s_minishell_vars *vars, const char *key)
{
	ht_del(&vars->shell, key);
	ht_del(&vars->environment, key);
}

const char	*minishell_vars_echo(const struct s_minishell_vars *vars, \
const char *key)
{
	const char	*result;

	result = minishell_vars_database_get(&vars->environment, key);
	if (!result)
		result = minishell_vars_database_get(&vars->shell, key);
	return (result);
}
