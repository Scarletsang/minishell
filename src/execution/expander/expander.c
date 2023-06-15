/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 02:46:53 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/15 19:57:48 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/expander.h"

int	ms_expander_remove_quote(t_sb_iterator *it, char quote)
{
	if (sb_iterator_mut_delete(it, 1))
		return (EXIT_FAILURE);
	while (!sb_iterator_is_end(it))
	{
		if (sb_iterator_current(it) == quote)
		{
			return (sb_iterator_mut_delete(it, 1));
		}
		sb_iterator_next(it);
	}
	return (EXIT_FAILURE);
}

int	ms_expander_dquote(t_sb_iterator *it, \
const struct s_ms_vars *vars)
{
	if (sb_iterator_mut_delete(it, 1))
		return (EXIT_FAILURE);
	while (!sb_iterator_is_end(it))
	{
		if (sb_iterator_current(it) == '\"')
		{
			return (sb_iterator_mut_delete(it, 1));
		}
		if (sb_iterator_current(it) == '$')
		{
			if (ms_expander_dquote_dollar(it, vars))
				return (EXIT_FAILURE);
			continue ;
		}
		sb_iterator_next(it);
	}
	return (EXIT_FAILURE);
}

int	ms_expander(t_sb *sb, const struct s_ms_vars *vars)
{
	t_sb_iterator	it;

	sb_iterator_init(&it, sb);
	while (!sb_iterator_is_end(&it))
	{
		if (sb_iterator_current(&it) == '\'')
		{
			if (ms_expander_remove_quote(&it, '\''))
				return (EXIT_FAILURE);
			continue ;
		}
		if (sb_iterator_current(&it) == '\"')
		{
			if (ms_expander_dquote(&it, vars))
				return (EXIT_FAILURE);
			continue ;
		}
		sb_iterator_next(&it);
	}
	return (EXIT_SUCCESS);
}

int	ms_expander_remove_quotes(t_sb *sb)
{
	t_sb_iterator	it;
	char			current;

	sb_iterator_init(&it, sb);
	while (!sb_iterator_is_end(&it))
	{
		current = sb_iterator_current(&it);
		if ( current == '\'' || current == '\"')
		{
			if (ms_expander_remove_quote(&it, current))
				return (EXIT_FAILURE);
			continue ;
		}
		sb_iterator_next(&it);
	}
	return (EXIT_SUCCESS);
}
