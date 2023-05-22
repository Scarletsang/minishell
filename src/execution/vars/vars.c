/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:32:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 14:35:59 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	minishell_vars_init(struct s_minishell_vars *vars)
{
	if (ht_init(vars->environment, 20))
		return (EXIT_FAILURE);
	if (ht_init(vars->shell, 10))
	{
		ht_free(vars->environment);
		return (EXIT_FAILURE);
	}
	vars->environ = NULL;
	return (EXIT_SUCCESS);
}

void	minishell_vars_destroy(struct s_minishell_vars *vars)
{
	ht_free(vars->environment);
	ht_free(vars->shell);
	if (vars->environ)
		free(vars->environ);
}

int	minishell_vars_import(struct s_minishell_vars *vars, char **envp)
{
	struct s_sb	key_sb;
	struct s_sb	*value_sb;

	while (*envp)
	{
		if (sb_init(&key_sb, 10))
			return (EXIT_FAILURE);
		value_sb = malloc(sizeof(struct s_sb));
		if (!value_sb || \
			sb_init(value_sb, 20) || \
			sb_perform(&key_sb, sb_action_append_len(*envp, \
				ft_strchr(*envp, '=') - *envp)) || \
			sb_perform(value_sb, sb_action_append(*envp)) || \
			ht_set(vars->environment, key_sb.buffer, value_sb, sb_free))
		{
			sb_free(&key_sb);
			if (value_sb)
				free(value_sb);
			return (EXIT_FAILURE);
		}
		envp++;
	}
	return (EXIT_SUCCESS);
}

int	minishell_vars_export_environ(struct s_minishell_vars *vars)
{
	
}
