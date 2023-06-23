/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:20:23 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 17:46:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

static t_executor_exit_code	ms_execute_ast_root(struct s_ms *ms, \
struct s_ast_node *root)
{
	t_executor_exit_code	exit_code;

	if (root->type == AST_NODE_PIPE)
		return (ms_execute_pipe(ms, root));
	else if (root->type == AST_NODE_CMD)
	{
		if (ms_ast_node_content_expand(root->content, ms) == EXECUTION_ERROR)
			return (EXECUTION_ERROR);
		exit_code = ms_execute_builtin(ms, root->content);
		if (exit_code != EXECUTION_FAILURE)
			return (exit_code);
		if (ms_executor_fork(&ms->executor) < 0)
			return (EXECUTION_ERROR);
		if (ms->executor.last_child_pid != 0)
			return (EXECUTION_SUCCESS);
		// use sender and receiver
		exit(ms_execute_command(ms, root->content));
	}
	return (EXECUTION_FAILURE);
}

t_executor_return_value	ms_execute_ast(struct s_ms *ms, struct s_ast_node *root)
{
	struct s_ms_executor	executor;
	t_executor_return_value	return_value;

	return_value = EXIT_FAILURE;
	ms_executor_init(&executor);
	if (ms_execute_ast_root(ms, root) == EXECUTION_ERROR)
		ms_executor_wait(&executor);
	else
		return_value = ms_executor_wait(&executor);
	if (ms_executor_destroy(&executor) == EXECUTION_ERROR)
		return (EXIT_FAILURE);
	return (return_value);
}
