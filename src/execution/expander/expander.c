/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 02:46:53 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/24 13:37:53 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/expander.h"

int	ms_expander_remove_quote(t_ft_sb_iterator *it, char quote)
{
	if (ft_sb_iterator_mut_delete(it, 1))
		return (EXIT_FAILURE);
	while (!ft_sb_iterator_is_end(it))
	{
		if (ft_sb_iterator_current(it) == quote)
		{
			return (ft_sb_iterator_mut_delete(it, 1));
		}
		ft_sb_iterator_next(it);
	}
	return (EXIT_FAILURE);
}

int	ms_expander_dquote(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars)
{
	if (ft_sb_iterator_mut_delete(it, 1))
		return (EXIT_FAILURE);
	while (!ft_sb_iterator_is_end(it))
	{
		if (ft_sb_iterator_current(it) == '\"')
		{
			return (ft_sb_iterator_mut_delete(it, 1));
		}
		if (ft_sb_iterator_current(it) == '$')
		{
			if (ms_expander_dollar(it, vars, " \"$"))
				return (EXIT_FAILURE);
		}
		else
			ft_sb_iterator_next(it);
	}
	return (EXIT_FAILURE);
}

int	ms_expander(t_ft_sb *sb, const struct s_ms_vars *vars)
{
	t_ft_sb_iterator	it;

	ft_sb_iterator_init(&it, sb);
	while (!ft_sb_iterator_is_end(&it))
	{
		if (ft_sb_iterator_current(&it) == '\'')
		{
			if (ms_expander_remove_quote(&it, '\''))
				return (EXIT_FAILURE);
		}
		else if (ft_sb_iterator_current(&it) == '\"')
		{
			if (ms_expander_dquote(&it, vars))
				return (EXIT_FAILURE);
		}
		else if (ft_sb_iterator_current(&it) == '$')
		{
			if (ms_expander_dollar(&it, vars, " \"'$"))
				return (EXIT_FAILURE);
		}
		else
			ft_sb_iterator_next(&it);
	}
	return (EXIT_SUCCESS);
}

int	ms_expander_remove_quotes(t_ft_sb *sb)
{
	t_ft_sb_iterator	it;
	char				current;

	ft_sb_iterator_init(&it, sb);
	while (!ft_sb_iterator_is_end(&it))
	{
		current = ft_sb_iterator_current(&it);
		if (current == '\'' || current == '\"')
		{
			if (ms_expander_remove_quote(&it, current))
				return (EXIT_FAILURE);
		}
		else
			ft_sb_iterator_next(&it);
	}
	return (EXIT_SUCCESS);
}
