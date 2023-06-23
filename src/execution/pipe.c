/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:19:54 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 17:46:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

static t_executor_exit_code	ms_execute_ast_node(struct s_ms *ms, \
struct s_ast_node *node)
{
	if (node->type == AST_NODE_PIPE)
		return (ms_execute_pipe(ms, node));
	else if (node->type == AST_NODE_CMD)
	{
		if (ms_ast_node_content_expand(node->content, ms) == EXECUTION_ERROR)
			return (EXECUTION_ERROR);
		ms_piper_create_receiver(&ms->executor.piper);
		if (ms_piper_create_sender(&ms->executor.piper))
			return (EXECUTION_ERROR);
		if (ms_executor_fork(&ms->executor) < 0)
			return (EXECUTION_ERROR);
		if (ms->executor.last_child_pid != 0)
			return (EXECUTION_SUCCESS);
		// use sender and receiver
		if (ms_execute_builtin(ms, node->content) \
			!= EXECUTION_FAILURE)
			exit(EXIT_FAILURE); // TODO: executor cleanup
		exit(ms_execute_command(ms, node->content));
	}
	return (EXECUTION_FAILURE);
}

t_executor_exit_code	ms_execute_pipe(struct s_ms *ms, \
struct s_ast_node *pipe)
{
	if (ms_execute_ast_node(ms, pipe->left) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	if (ms_execute_ast_node(ms, pipe->right) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	return (EXECUTION_SUCCESS);
}
