/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:32:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/13 22:27:10 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	ms_vars_init(struct s_ms_vars *vars)
{
	if (ht_init(&vars->environment, 20) || \
		ht_init(&vars->shell, 10) || \
		vector_init(&vars->envp, sizeof(char *), 20, vector_set_string))
	{
		ms_vars_free(vars);
		return (EXIT_FAILURE);
	}
	vars->environnement_changed = true;
	return (EXIT_SUCCESS);
}

void	ms_vars_free(struct s_ms_vars *vars)
{
	ht_free(&vars->environment);
	ht_free(&vars->shell);
	vector_free(&vars->envp);
}

/**
 * @details Iterates through the given environment variables and adds them to
 * the environment hash table. The key is the part of the string before the
 * first '=' character, and the value is simply the whole string. Then it will
 * use the key to add the env to the enviornment database. The value is not
 * owned by the database.
*/
int	ms_vars_import(struct s_ms_vars *vars, char **envp)
{
	char	*key;

	key = NULL;
	while (*envp)
	{
		key = ft_strchr(*envp, '=');
		if (!key)
			return (EXIT_FAILURE);
		key = ft_substr(*envp, 0, key - *envp);
		if (!key)
			return (EXIT_FAILURE);
		if (!ht_update(&vars->environment, key, *envp, NULL))
		{
			free(key);
			return (EXIT_FAILURE);
		}
		vars->environnement_changed = true;
		free(key);
		envp++;
	}
	return (EXIT_SUCCESS);
}

char	**ms_vars_get_envp(struct s_ms_vars *vars)
{
	size_t				i;
	size_t				valid_entry;
	struct s_ht_entry	*ht_entry;

	if (vars->environnement_changed)
	{
		i = 0;
		valid_entry = 0;
		while ((i < vars->environment.capacity) && \
			(valid_entry < vars->envp.size))
		{
			ht_entry = vector_get(&vars->environment, i);
			if (ht_entry->key)
			{
				vector_set(&vars->envp, i, ht_entry->value);
				valid_entry++;
			}
			i++;
		}
		vars->environnement_changed = false;
	}
	if (vars->envp.size == 0)
		return (NULL);
	return (vars->envp.buffer);
}

int	ms_vars_set_envp(struct s_ms_vars *vars, char *pair)
{
	if (!vector_append(&vars->envp, pair))
		return (EXIT_FAILURE);
	vars->environnement_changed = true;
	return (EXIT_SUCCESS);
}
