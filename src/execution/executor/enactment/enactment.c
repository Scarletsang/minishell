/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enactment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:41:25 by htsang            #+#    #+#             */
/*   Updated: 2023/06/11 22:54:40 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_executor_exit_code	ms_executor_enact(struct s_ms_executor *executor, \
struct s_AST_node *node, struct s_ms *ms)
{
	if (node->type == AST_NODE_PIPE)
		return (ms_executor_enact_pipe(executor, node, ms));
	else if (node->type == AST_NODE_COMMAND)
		return (ms_executor_enact_ast(executor, node, ms));
	return (EXECUTION_FAILURE);
}

t_executor_exit_code	ms_executor_enact_pipe(struct s_ms_executor *executor, \
struct s_AST_node *node, struct s_ms *ms)
{
	if (ms_executor_enact(executor, node->left, ms) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	if (ms_executor_enact(executor, node->right, ms) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_ast(struct s_ms_executor *executor, \
struct s_AST_node *node, struct s_ms *ms)
{
	pid_t	pid;

	ms_piper_create_receiver(&executor->piper);
	if (ms_piper_create_sender(&executor->piper))
		return (EXECUTION_ERROR);
	pid = ms_executor_fork(executor);
	if (pid < 0)
		return (EXECUTION_ERROR);
	else if (pid == 0)
	{
		if ((ms_executor_enact_assignment(executor, node, ms) == \
				EXECUTION_ERROR) || \
			(ms_executor_enact_redirection_in(executor, node, ms) == \
				EXECUTION_ERROR) || \
			(ms_executor_enact_redirection_out(executor, node, ms) == \
				EXECUTION_ERROR) || \
			(ms_executor_enact_command(executor, node, ms) == \
				EXECUTION_ERROR))
			exit(EXIT_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}
