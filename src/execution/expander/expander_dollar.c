/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:26:37 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/07/07 04:36:52 by htsang           ###   ########.fr       */
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
	char		*value;
	size_t		variable_name_end;
	t_ft_str_nt	key_value;

	key_value = ms_vars_echo(vars, ft_str_slice(it->vector->buffer, from + 1, \
		it->index + 1));
	variable_name_end = it->index + 1;
	it->index = from;
	if (!key_value.content)
		return (ft_sb_iterator_mut_delete(it, variable_name_end - from));
	value = ft_strchr(key_value.content, '=');
	if (value)
		value++;
	return (ft_sb_iterator_mut_replace(it, ft_str_from_cstring(value), \
		variable_name_end - from));
}

static int	ms_expander_substite_special(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars)
{
	char		current;
	char		key[2];
	t_ft_str_nt	value;

	current = ft_sb_iterator_current(it);
	if (current == '?' || ft_isdigit(current))
	{
		ft_sb_iterator_prev(it);
		key[0] = current;
		key[1] = '\0';
		value = ms_vars_database_get(&vars->special, \
			ft_str_from_cstring(key));
		if (value.size > 0)
			value.size--;
		ft_sb_iterator_mut_replace(it, value, 2);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ms_expander_dollar_no_quote(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars)
{
	size_t	dollar;

	dollar = it->index;
	if (ft_sb_iterator_next(it))
		return (EXIT_FAILURE);
	if ((it->is_end == SB_RIGHT_END) || !ms_expander_substite_special(it, vars))
		return (EXIT_SUCCESS);
	if (!ms_expander_is_variable_char(it))
	{
		ft_sb_iterator_prev(it);
		return (ft_sb_iterator_mut_delete(it, 1), EXIT_SUCCESS);
	}
	while (it->is_end != SB_RIGHT_END)
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
	while (it->is_end != SB_RIGHT_END)
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
