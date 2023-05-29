/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:04:50 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/29 00:30:28 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	minishell_vars_export(struct s_minishell_vars *vars, const char *key, \
char *value)
{
	if (minishell_vars_database_set(&vars->shell, key, value) || \
		minishell_vars_database_set(&vars->environment, key, value))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	minishell_vars_export_without_value(struct s_minishell_vars *vars, \
const char *key)
{
	return (minishell_vars_database_set(&vars->environment, key, \
		minishell_vars_database_get(&vars->shell, key)));
}

void	minishell_vars_unset(struct s_minishell_vars *vars, const char *key)
{
	ht_del(&vars->shell, key);
	ht_del(&vars->environment, key);
}

const char	*minishell_vars_echo(struct s_minishell_vars *vars, \
const char *key)
{
	const char	*result;

	result = minishell_vars_database_get(&vars->environment, key);
	if (!result)
		result = minishell_vars_database_get(&vars->shell, key);
	return (result);
}
