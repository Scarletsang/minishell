/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:19:54 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 11:48:08 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

static t_ms_status	ms_execute_ast_node_cmd(struct s_ms *ms, \
struct s_ast_node *node)
{
	t_ms_exit_code				exit_code;
	enum e_ms_execution_mode	mode;

	ms_piper_create_receiver(&ms->executor.piper);
	if ((ms_piper_create_sender(&ms->executor.piper)) || \
		(ms_executor_fork(&ms->executor) < 0))
		return (PROGRAM_ERROR);
	if (ms->executor.last_child_pid != 0)
		return (PROGRAM_SUCCESS);
	if (ms_piper_use_receiver(&ms->executor.piper) || \
		ms_piper_use_sender(&ms->executor.piper))
	{
		ms_free(ms);
		exit(EC_FAILURE);
	}
	mode = ms_execution_mode(&node->content->command);
	if (mode == MODE_EXECUTABLE)
		exit_code = ms_execute_command(ms, node->content);
	else if (mode == MODE_NO_COMMAND)
		exit_code = ms_status_to_exit_code(\
			ms_execute_declares_and_redirections(ms, node->content));
	else
		exit_code = ms_execute_builtin(ms, mode, node->content);
	ms_free(ms);
	exit(exit_code);
}

static t_ms_status	ms_execute_ast_node(struct s_ms *ms, \
struct s_ast_node *node)
{
	if (node->type == AST_NODE_PIPE)
		return (ms_execute_pipe(ms, node));
	else if (node->type == AST_NODE_CMD)
	{
		if (ms_ast_node_content_expand(node->content, ms) == PROGRAM_ERROR)
			return (PROGRAM_ERROR);
		return (ms_execute_ast_node_cmd(ms, node));
	}
	return (PROGRAM_FAILURE);
}

t_ms_status	ms_execute_pipe(struct s_ms *ms, \
struct s_ast_node *pipe)
{
	if (ms_execute_ast_node(ms, pipe->left) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	if (ms_execute_ast_node(ms, pipe->right) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}
