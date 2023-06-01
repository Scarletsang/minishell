/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:26:37 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/01 02:44:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/expander.h"
#include <stdio.h>

static int	minishell_expander_substitute(t_sb_iterator *it, size_t from, \
const struct s_minishell_vars *vars)
{
	struct s_sb_clipper	clipper;
	char				*key;
	const char			*key_value;

	sb_clipper_init(&clipper, it->vector);
	clipper.lbound = from + 1;
	clipper.rbound = it->index - 1;
	key = sb_clipper_run(&clipper);
	if (!key)
		return (EXIT_FAILURE);
	it->index = from;
	key_value = minishell_vars_echo(vars, key);
	free(key);
	if (!key_value)
		return (sb_iterator_mut_delete(it, clipper.rbound - \
			clipper.lbound + 2));
	while (*key_value && *key_value++ != '=')
		;
	return (sb_iterator_mut_replace(it, key_value, \
		clipper.rbound - clipper.lbound + 2));
}

static int	minishell_expander_substite_special(t_sb_iterator *it, \
const struct s_minishell_vars *vars)
{
	size_t	i;
	char	special[sizeof(SUPPORTED_SPECIAL_VARS)];

	ft_memcpy(special, SUPPORTED_SPECIAL_VARS, sizeof(SUPPORTED_SPECIAL_VARS));
	i = 0;
	while (i < sizeof(SUPPORTED_SPECIAL_VARS))
	{
		if (sb_iterator_current(it) == special[i])
		{
			sb_iterator_prev(it);
			return (sb_iterator_mut_replace(it, \
				minishell_vars_database_get(&vars->special, special + i), 2));
		}
		i += 2;
	}
	return (EXIT_FAILURE);
}

int	minishell_expander_dquote_dollar(t_sb_iterator *it, \
const struct s_minishell_vars *vars)
{
	size_t	dollar;

	dollar = it->index;
	if (sb_iterator_next(it))
		return (EXIT_FAILURE);
	if (!minishell_expander_match_any(it, " \""))
		return (EXIT_SUCCESS);
	if (!minishell_expander_substite_special(it, vars))
		return (EXIT_SUCCESS);
	while (!sb_iterator_is_end(it) && \
		minishell_expander_match_any(it, " \"$"))
		sb_iterator_next(it);
	if (dollar == it->index)
		return (EXIT_FAILURE);
	return (minishell_expander_substitute(it, dollar, vars));
}
