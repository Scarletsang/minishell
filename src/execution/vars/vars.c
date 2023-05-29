/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:32:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/29 01:46:57 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	minishell_vars_init(struct s_minishell_vars *vars)
{
	if (ht_init(&vars->environment, 20) || \
		ht_init(&vars->shell, 10) || \
		vector_init(&vars->envp, sizeof(char *), 20, vector_set_string))
	{
		minishell_vars_free(vars);
		return (EXIT_FAILURE);
	}
	vars->environnement_changed = true;
	return (EXIT_SUCCESS);
}

void	minishell_vars_free(struct s_minishell_vars *vars)
{
	ht_free(&vars->environment);
	ht_free(&vars->shell);
	vector_free(&vars->envp);
}

static int	minishell_vars_import_cleaner(char **key, t_sb *key_and_value)
{
	if (*key)
		free(*key);
	sb_free(key_and_value);
	return (EXIT_FAILURE);
}

int	minishell_vars_import(struct s_minishell_vars *vars, char **envp)
{
	struct s_sb_clipper	clipper;
	t_sb				key_and_value;
	char				*key;

	key = NULL;
	while (*envp)
	{
		if (sb_init(&key_and_value, 10) || \
			sb_perform(&key_and_value, sb_action_append(*envp)))
			return (minishell_vars_import_cleaner(&key, &key_and_value));
		sb_clipper_init(&clipper, &key_and_value);
		if (sb_clipper_area(&clipper, NULL, "="))
			return (minishell_vars_import_cleaner(&key, &key_and_value));
		key = sb_clipper_run(&clipper);
		if (!key || minishell_vars_export(vars, key, *envp))
			return (minishell_vars_import_cleaner(&key, &key_and_value));
		vars->environnement_changed = true;
		minishell_vars_import_cleaner(&key, &key_and_value);
		envp++;
	}
	return (EXIT_SUCCESS);
}

char	**minishell_vars_get_envp(struct s_minishell_vars *vars)
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
