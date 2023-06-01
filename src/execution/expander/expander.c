/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 02:46:53 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/01 15:06:33 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/expander.h"

int	minishell_expander_quote(t_sb_iterator *it)
{
	if (sb_iterator_mut_delete(it, 1))
		return (EXIT_FAILURE);
	while (!sb_iterator_is_end(it))
	{
		if (sb_iterator_current(it) == '\'')
		{
			return (sb_iterator_mut_delete(it, 1));
		}
		sb_iterator_next(it);
	}
	return (EXIT_FAILURE);
}

int	minishell_expander_dquote(t_sb_iterator *it, \
const struct s_minishell_vars *vars)
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
			if (minishell_expander_dquote_dollar(it, vars))
				return (EXIT_FAILURE);
			continue ;
		}
		sb_iterator_next(it);
	}
	return (EXIT_FAILURE);
}

int	minishell_expander(t_sb *sb, const struct s_minishell_vars *vars)
{
	t_sb_iterator	it;

	sb_iterator_init(&it, sb);
	while (!sb_iterator_is_end(&it))
	{
		if (sb_iterator_current(&it) == '\'')
		{
			if (minishell_expander_quote(&it))
				return (EXIT_FAILURE);
			continue ;
		}
		if (sb_iterator_current(&it) == '\"')
		{
			if (minishell_expander_dquote(&it, vars))
				return (EXIT_FAILURE);
			continue ;
		}
		sb_iterator_next(&it);
	}
	return (EXIT_SUCCESS);
}
