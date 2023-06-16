/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:28:06 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 20:06:37 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor/enactment.h"

static t_executor_exit_code	ms_executor_expand_ast_redirection_vector(\
t_ast_redirection_vector *redirection_vector, struct s_ms *ms)
{
	t_vector_iterator			iterator;
	struct s_ast_redirection	*redirection;

	vector_iterator_init(&iterator, redirection_vector);
	while (!vector_iterator_is_end(&iterator))
	{
		redirection = vector_iterator_current(&iterator);
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
		vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}

static t_executor_exit_code	ms_executor_expand_sb_vector(\
t_sb_vector *sb_vector, struct s_ms *ms)
{
	t_vector_iterator	iterator;
	t_sb				*sb;

	vector_iterator_init(&iterator, sb_vector);
	while (!vector_iterator_is_end(&iterator))
	{
		sb = vector_iterator_current(&iterator);
		if (ms_expander(sb, (const struct s_ms_vars *) &ms->vars))
			return (EXECUTION_ERROR);
		vector_iterator_next(&iterator);
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
