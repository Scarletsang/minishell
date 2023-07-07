/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:32:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/07/07 03:45:24 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"
#include "LIBFT/string.h"

int	ms_vars_init(struct s_ms_vars *vars)
{
	if (ft_ht_init(&vars->environment, 20) || \
		ft_ht_init(&vars->shell, 10) || \
		ft_ht_init(&vars->special, 3))
	{
		ms_vars_free(vars);
		return (EXIT_FAILURE);
	}
	vars->environnement_changed = true;
	return (EXIT_SUCCESS);
}

void	ms_vars_free(struct s_ms_vars *vars)
{
	ft_ht_free(&vars->environment);
	ft_ht_free(&vars->shell);
	ft_ht_free(&vars->special);
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
		if (!ft_ht_update(&vars->environment, \
			ft_str_slice(*envp, 0, key - *envp), \
			ft_str_nt_from_cstring(*envp), NULL))
		{
			return (EXIT_FAILURE);
		}
		vars->environnement_changed = true;
		envp++;
	}
	return (EXIT_SUCCESS);
}

int	ms_vars_import_default_special(struct s_ms_vars *vars)
{
	if (!ms_vars_database_set(&vars->special, ft_str_from_cstring("?"), \
			ft_str_nt_from_cstring("0")) || \
		!ms_vars_database_set(&vars->special, ft_str_from_cstring("0"), \
			ft_str_nt_from_cstring("minishell")))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
