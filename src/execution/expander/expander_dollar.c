/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:26:37 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/24 13:32:11 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/expander.h"
#include "LIBFT/stringbuilder/clipper.h"
#include "LIBFT/string.h"

static int	ms_expander_substitute(t_ft_sb_iterator *it, const size_t from, \
const struct s_ms_vars *vars)
{
	struct s_ft_sb_clipper	clipper;
	char					*key;
	const char				*key_value;

	ft_sb_clipper_init(&clipper, it->vector);
	clipper.lbound = from + 1;
	clipper.rbound = it->index + 1;
	key = ft_sb_clipper_run(&clipper);
	if (!key)
		return (EXIT_FAILURE);
	key_value = ms_vars_echo(vars, key);
	free(key);
	it->index = from;
	if (!key_value)
		return (ft_sb_iterator_mut_delete(it, clipper.rbound - from));
	while (*key_value && *key_value++ != '=')
		;
	return (ft_sb_iterator_mut_replace(it, key_value, \
		clipper.rbound - from));
}

static int	ms_expander_substite_special(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars)
{
	size_t	i;
	char	special[sizeof(SUPPORTED_SPECIAL_VARS)];

	ft_memcpy(special, SUPPORTED_SPECIAL_VARS, sizeof(SUPPORTED_SPECIAL_VARS));
	i = 0;
	while (i < sizeof(SUPPORTED_SPECIAL_VARS))
	{
		if (ft_sb_iterator_current(it) == special[i])
		{
			ft_sb_iterator_prev(it);
			return (ft_sb_iterator_mut_replace(it, \
				ms_vars_database_get(&vars->special, special + i), 2));
		}
		i += 2;
	}
	return (EXIT_FAILURE);
}

int	ms_expander_dollar(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars, const char *match_end)
{
	size_t	dollar;

	dollar = it->index;
	if (ft_sb_iterator_next(it))
		return (EXIT_FAILURE);
	if (!ms_expander_substite_special(it, vars))
		return (EXIT_SUCCESS);
	if (!ms_expander_match_any(it, match_end))
		return (EXIT_SUCCESS);
	while (!ft_sb_iterator_is_end(it))
	{
		if (!ms_expander_match_any(it, match_end))
		{
			ft_sb_iterator_prev(it);
			break ;
		}
		ft_sb_iterator_next(it);
	}
	if (dollar == it->index)
		return (EXIT_FAILURE);
	return (ms_expander_substitute(it, dollar, vars));
}
