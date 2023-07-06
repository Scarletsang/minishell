/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:26:37 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/07/07 00:55:29 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/ctype.h"
#include "LIBFT/string.h"
#include "LIBFT/stringbuilder/clipper.h"
#include "MINISHELL/execution/expander.h"

static bool	ms_expander_is_variable_char(t_ft_sb_iterator *it)
{
	char	current;

	current = ft_sb_iterator_current(it);
	return (ft_isalnum(current) || current == '_');
}

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
	if (key_value[0] == '\0')
		return (ft_sb_iterator_mut_replace(it, "", clipper.rbound - from));
	key_value = ft_strchr(key_value, '=');
	if (key_value)
		key_value++;
	return (ft_sb_iterator_mut_replace(it, key_value, \
		clipper.rbound - from));
}

static int	ms_expander_substite_special(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars)
{
	char	current;
	char	key[2];

	current = ft_sb_iterator_current(it);
	if (current == '?' || ft_isdigit(current))
	{
		ft_sb_iterator_prev(it);
		key[0] = current;
		key[1] = '\0';
		return (ft_sb_iterator_mut_replace(it, \
			ms_vars_database_get(&vars->special, key), 2));
	}
	return (EXIT_FAILURE);
}

int	ms_expander_dollar(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars)
{
	size_t	dollar;

	dollar = it->index;
	if (ft_sb_iterator_next(it))
		return (EXIT_FAILURE);
	if (!ms_expander_substite_special(it, vars))
		return (EXIT_SUCCESS);
	if (!ms_expander_is_variable_char(it))
		return (EXIT_SUCCESS);
	while (!ft_sb_iterator_is_end(it))
	{
		if (!ms_expander_is_variable_char(it))
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
