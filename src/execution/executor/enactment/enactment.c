/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enactment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:41:25 by htsang            #+#    #+#             */
/*   Updated: 2023/06/13 23:51:23 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_executor_exit_code	ms_executor_enact(struct s_ms_executor *executor, \
struct s_AST_node *node, struct s_ms *ms)
{
	if (node->type == AST_NODE_PIPE)
		return (ms_executor_enact_pipe(executor, node, ms));
	else if (node->type == AST_NODE_COMMAND)
	{
		// expand
		// if entry is builtin, enact builtin
		// else, enact command
	}
	return (EXECUTION_FAILURE);
}

t_executor_exit_code	ms_executor_enact_in_pipe(\
struct s_ms_executor *executor, struct s_AST_node *node, struct s_ms *ms)
{
	if (node->type == AST_NODE_PIPE)
		return (ms_executor_enact_pipe(executor, node, ms));
	else if (node->type == AST_NODE_COMMAND)
	{
		//  expand
		ms_piper_create_receiver(&executor->piper);
		if (ms_piper_create_sender(&executor->piper))
			return (EXECUTION_ERROR);
		//  if is builtin
		//	fork, then enact builtin
		//  else
		//	enact command
	}
	return (EXECUTION_FAILURE);
}

t_executor_exit_code	ms_executor_enact_pipe(\
struct s_ms_executor *executor, struct s_AST_node *node, struct s_ms *ms)
{
	if (ms_executor_enact_in_pipe(executor, node->left, ms) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	if (ms_executor_enact_in_pipe(executor, node->right, ms) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_builtin(\
struct s_ms_executor *executor, struct s_AST_node_content *content, \
struct s_ms *ms)
{
	// enact assignment
	// save stdin and stdout
	// enact redirections
	// enact builtin
	// restore stdin and stdout
}

t_executor_exit_code	ms_executor_enact_command(\
struct s_ms_executor *executor, struct s_AST_node_content *content, \
struct s_ms *ms)
{
	pid_t	pid;

	pid = ms_executor_fork(executor);
	if (pid < 0)
		return (EXECUTION_ERROR);
	else if (pid == 0)
	{
		if ((ms_executor_enact_assignment(executor, \
				&content->assignment, ms) == EXECUTION_ERROR) || \
			(ms_executor_enact_redirection_in(executor, \
				&content->redirection_in, ms) == EXECUTION_ERROR) || \
			(ms_executor_enact_redirection_out(executor, \
				&content->redirection_out, ms) == EXECUTION_ERROR) || \
			(ms_executor_enact_command_execution(executor, \
				&content->command, ms) == EXECUTION_ERROR))
			exit(EXIT_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}
