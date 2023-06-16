/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:10:15 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 13:45:08 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

char	**ms_executor_envp_get(struct s_ms_executor *executor)
{
	if (executor->envp.size == 0)
		return (NULL);
	return (executor->envp.buffer);
}

t_executor_exit_code	ms_executor_envp_import_from_environment(\
struct s_ms_executor *executor, struct s_ms_vars *vars)
{
	size_t				i;
	struct s_ht_entry	*ht_entry;

	if (vars->environnement_changed)
	{
		ms_executor_envp_reset(executor);
		i = 0;
		while ((i < vars->environment.capacity))
		{
			ht_entry = vector_get(&vars->environment, i);
			if (ht_entry->key)
			{
				if (vector_append(&executor->envp, ht_entry->value))
					return (EXECUTION_ERROR);
			}
			i++;
		}
		vars->environnement_changed = false;
	}
	return (EXECUTION_SUCCESS);
}

void	ms_executor_envp_reset(struct s_ms_executor *executor)
{
	executor->envp.size = 0;
	vector_append(&executor->envp, NULL);
}

t_executor_exit_code	ms_executor_envp_set(struct s_ms_executor *executor, \
struct s_ms_vars *vars, char *pair)
{
	// if (!vector_append(&vars->envp, pair))
	// 	return (EXIT_FAILURE);
	// vars->environnement_changed = true;
	// return (EXIT_SUCCESS);
}
