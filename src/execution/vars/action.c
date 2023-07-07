/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:04:50 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/07/07 01:49:40 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	ms_vars_declare(struct s_ms_vars *vars, t_ft_str key, \
t_ft_str_nt value)
{
	t_ft_str_nt					environment_str;
	const struct s_ft_ht_entry	*entry;

	entry = ms_vars_database_set(&vars->shell, key, value);
	if (!entry)
		return (EXIT_FAILURE);
	environment_str = ms_vars_database_get(&vars->environment, key);
	if (environment_str.content)
	{
		if (!ft_ht_update(&vars->environment, key, entry->value, NULL))
			return (EXIT_FAILURE);
		vars->environnement_changed = true;
	}
	return (EXIT_SUCCESS);
}

int	ms_vars_export(struct s_ms_vars *vars, t_ft_str key)
{
	t_ft_str_nt	value;

	value = ms_vars_database_get(&vars->shell, key);
	if (!value.content)
		value = key;
	if (!ft_ht_update(&vars->environment, key, value, free))
		return (EXIT_FAILURE);
	vars->environnement_changed = true;
	return (EXIT_SUCCESS);
}

void	ms_vars_unset(struct s_ms_vars *vars, t_ft_str key)
{
	bool	is_deleted;

	is_deleted = false;
	if (ft_ht_delete(&vars->shell, key))
		is_deleted = true;
	if (ft_ht_delete(&vars->environment, key))
		is_deleted = true;
	if (is_deleted)
		vars->environnement_changed = true;
}

t_ft_str_nt	ms_vars_echo(const struct s_ms_vars *vars, \
t_ft_str key)
{
	t_ft_str_nt	result;

	result = ms_vars_database_get(&vars->environment, key);
	if (!result.content)
		result = ms_vars_database_get(&vars->shell, key);
	return (result);
}
