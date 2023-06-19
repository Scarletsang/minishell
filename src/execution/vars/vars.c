/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:32:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/19 16:56:41 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"
#include "LIBFT/string.h"

int	ms_vars_init(struct s_ms_vars *vars)
{
	if (ft_ht_init(&vars->environment, 20) || \
		ft_ht_init(&vars->shell, 10))
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
		if (!ft_ht_update(&vars->environment, key, *envp, NULL))
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
