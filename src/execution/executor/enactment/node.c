/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:36:33 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 23:33:39 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MINISHELL/execution/executor/enactment.h"

t_executor_exit_code	ms_executor_enact_assignment(\
struct s_ms_executor *executor, t_sb_vector *assignment, struct s_ms *ms)
{
	t_vector_iterator	iterator;

	if (ms_executor_envp_import_from_environment(executor, &ms->vars) \
		== EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	vector_iterator_init(&iterator, assignment);
	while (!vector_iterator_is_end(&iterator))
	{
		if (ms_executor_envp_set(executor, &ms->vars, \
			((t_sb *) vector_iterator_current(&iterator))->buffer))
			return (EXECUTION_ERROR);
		vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_redirection_in(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_in, \
struct s_ms *ms)
{

}

t_executor_exit_code	ms_executor_enact_redirection_out(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_out, \
struct s_ms *ms)
{
	t_vector_iterator			iterator;
	struct s_ast_redirection	*redirection;

	vector_iterator_init(&iterator, redirection_out);
	while (!vector_iterator_is_end(&iterator))
	{
		redirection = vector_iterator_current(&iterator);
		if (redirection->type == REDIRECT_STDOUT)
		{
			if (ms_executor_write_to_fd(\
					open(redirection->content.buffer, \
					O_WRONLY | O_CREAT | O_TRUNC)) == EXECUTION_ERROR)
				return (EXECUTION_ERROR);
		}
		else if (redirection->type == REDIRECT_STDOUT_APPEND)
		{
			if (ms_executor_write_to_fd(\
					open(redirection->content.buffer, \
					O_WRONLY | O_CREAT | O_APPEND)) == EXECUTION_ERROR)
				return (EXECUTION_ERROR);
		}
		vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_command_execution(\
struct s_ms_executor *executor, t_sb_vector *command, struct s_ms *ms)
{

}
