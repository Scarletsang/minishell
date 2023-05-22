/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:32:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 19:17:35 by htsang           ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

void	minishell_vars_free(struct s_minishell_vars *vars)
{
	ht_free(&vars->environment);
	ht_free(&vars->shell);
	vector_free(&vars->envp);
}

int	minishell_vars_import(struct s_minishell_vars *vars, char **envp)
{
	t_sb	key_sb;
	t_sb	*value_sb;

	while (*envp)
	{
		if (sb_init(&key_sb, 10))
			return (EXIT_FAILURE);
		value_sb = malloc(sizeof(t_sb));
		if (!value_sb || \
			sb_init(value_sb, 20) || \
			sb_perform(&key_sb, sb_action_append_len(*envp, \
				ft_strchr(*envp, '=') - *envp)) || \
			sb_perform(value_sb, sb_action_append(*envp)) || \
			ht_set(&vars->environment, key_sb.buffer, value_sb, sb_free))
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
