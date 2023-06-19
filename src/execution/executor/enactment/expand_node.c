/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:28:06 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 17:03:21 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor/enactment.h"
#include "MINISHELL/execution/expander.h"

static t_executor_exit_code	ms_executor_expand_ast_redirection_vector(\
t_ast_redirection_vector *redirection_vector, struct s_ms *ms)
{
	t_ft_vector_iterator			iterator;
	struct s_ast_redirection		*redirection;

	ft_vector_iterator_init(&iterator, redirection_vector);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		redirection = ft_vector_iterator_current(&iterator);
		if (redirection->type == REDIRECT_HEREDOC)
		{
			if (ms_expander_remove_quotes(&redirection->content))
				return (EXECUTION_ERROR);
		}
		else
		{
			if (ms_expander(&redirection->content, \
				(const struct s_ms_vars *) &ms->vars))
				return (EXECUTION_ERROR);
		}
		ft_vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}

static t_executor_exit_code	ms_executor_expand_sb_vector(\
t_sb_vector *sb_vector, struct s_ms *ms)
{
	t_ft_vector_iterator	iterator;
	t_ft_sb					*sb;

	ft_vector_iterator_init(&iterator, sb_vector);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		sb = ft_vector_iterator_current(&iterator);
		if (ms_expander(sb, (const struct s_ms_vars *) &ms->vars))
			return (EXECUTION_ERROR);
		ft_vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_expand_content(\
struct s_ast_node_content *content, struct s_ms *ms)
{
	if ((ms_executor_expand_ast_redirection_vector(\
			&content->redirection_in, ms) == EXECUTION_ERROR) || \
		(ms_executor_expand_ast_redirection_vector(\
			&content->redirection_out, ms) == EXECUTION_ERROR) || \
		(ms_executor_expand_sb_vector(\
			&content->assignment, ms) == EXECUTION_ERROR) || \
		(ms_executor_expand_sb_vector(\
			&content->command, ms) == EXECUTION_ERROR))
		return (EXECUTION_ERROR);
	return (EXECUTION_SUCCESS);
}
