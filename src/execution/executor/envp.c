/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:10:15 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 15:46:06 by htsang           ###   ########.fr       */
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
	size_t					i;
	struct s_ft_ht_entry	*ht_entry;

	if (vars->environnement_changed)
	{
		ms_executor_envp_reset(executor);
		i = 0;
		while ((i < vars->environment.capacity))
		{
			ht_entry = ft_vector_get(&vars->environment, i);
			if (ht_entry->key)
			{
				if (!ft_vector_append(&executor->envp, ht_entry->value))
					return (EXECUTION_ERROR);
			}
			i++;
		}
		if (!ft_vector_append(&executor->envp, NULL))
			return (EXECUTION_ERROR);
	}
	return (EXECUTION_SUCCESS);
}

void	ms_executor_envp_reset(struct s_ms_executor *executor)
{
	executor->envp.size = 0;
	ft_vector_append(&executor->envp, NULL);
}

static bool	ms_strcmp_till(const char *s1, const char *s2, char c)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		if (*s1 == c)
			return (true);
		s1++;
		s2++;
	}
	return (false);
}

t_executor_exit_code	ms_executor_envp_set(struct s_ms_executor *executor, \
char *pair)
{
	t_ft_vector_iterator	iterator;

	if (!pair)
		return (EXECUTION_FAILURE);
	ft_vector_iterator_init(&iterator, &executor->envp);
	while (ft_vector_iterator_is_end(&iterator))
	{
		if (ms_strcmp_till(pair, ft_vector_iterator_current(&iterator), '='))
		{
			ft_vector_set(&executor->envp, iterator.index, pair);
			return (EXECUTION_SUCCESS);
		}
		ft_vector_iterator_next(&iterator);
	}
	if (!ft_vector_append(&executor->envp, pair))
		return (EXECUTION_ERROR);
	return (EXECUTION_SUCCESS);
}
