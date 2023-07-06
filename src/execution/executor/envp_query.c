/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_query.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:10:15 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 01:03:21 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_envp_import_from_environment(\
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
			if (ht_entry->key && !ht_entry->deleted)
			{
				if (!ft_vector_append(&executor->envp, &ht_entry->value))
					return (PROGRAM_ERROR);
			}
			i++;
		}
		if (!ft_vector_append(&executor->envp, NULL))
			return (PROGRAM_ERROR);
	}
	return (PROGRAM_SUCCESS);
}

static bool	ms_strcmp_till(const char *s1, const char *s2, char c)
{
	if (!s1 || !s2)
		return (false);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		if (*s1 == c)
			return (true);
		s1++;
		s2++;
	}
	return (false);
}

t_ms_status	ms_executor_envp_set(struct s_ms_executor *executor, \
char *pair)
{
	t_ft_vector_iterator	iterator;

	if (!pair)
		return (PROGRAM_FAILURE);
	ft_vector_iterator_init(&iterator, &executor->envp);
	while (!iterator.is_end)
	{
		if (ms_strcmp_till(pair, \
			*((char **) ft_vector_iterator_current(&iterator)), '='))
		{
			ft_vector_set(&executor->envp, iterator.index, &pair);
			return (PROGRAM_SUCCESS);
		}
		ft_vector_iterator_next(&iterator);
	}
	ft_vector_set(&executor->envp, executor->envp.size - 1, &pair);
	if (!ft_vector_append(&executor->envp, NULL))
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}

const char	*ms_executor_envp_get(struct s_ms_executor *executor, \
const char *key)
{
	t_ft_vector_iterator	iterator;
	char					*key_value;

	if (!key)
		return (NULL);
	ft_vector_iterator_init(&iterator, &executor->envp);
	while (!iterator.is_end)
	{
		key_value = *((char **) ft_vector_iterator_current(&iterator));
		if (key_value && ms_strcmp_till(key, key_value, '='))
		{
			return (key_value);
		}
		ft_vector_iterator_next(&iterator);
	}
	return (NULL);
}
