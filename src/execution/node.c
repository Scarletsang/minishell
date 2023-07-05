/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:19:54 by htsang            #+#    #+#             */
/*   Updated: 2023/07/05 23:25:27 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"
#include "MINISHELL/execution/command.h"

static t_ms_exit_code	ms_execute_ast_node_cmd_child(struct s_ms *ms, \
struct s_ast_node *node)
{
	t_ms_exit_code				exit_code;
	enum e_ms_execution_mode	mode;

	mode = ms_execution_mode(&node->content->command);
	if (mode == MODE_EXECUTABLE)
		exit_code = ms_execute_external(ms, node->content);
	else if (mode == MODE_NO_COMMAND)
		exit_code = ms_status_to_exit_code(\
			ms_execute_declares_and_redirections(ms, node->content));
	else
		exit_code = ms_execute_builtin(ms, mode, node->content);
	ms_free(ms);
	return (exit_code);
}

static t_ms_status	ms_execute_ast_node_cmd(struct s_ms *ms, \
struct s_ast_node *node)
{
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
	exit(ms_execute_ast_node_cmd_child(ms, node));
}

static t_ms_status	ms_execute_ast_node_cmd_last(struct s_ms *ms, \
struct s_ast_node *node)
{
	ms_piper_create_receiver(&ms->executor.piper);
	if ((ms_piper_close_sender(&ms->executor.piper)) || \
		(ms_executor_fork(&ms->executor) < 0))
		return (PROGRAM_ERROR);
	if (ms->executor.last_child_pid != 0)
	{
		if (ms_piper_close_receiver(&ms->executor.piper))
			return (PROGRAM_ERROR);
		return (PROGRAM_SUCCESS);
	}
	if (ms_piper_use_receiver(&ms->executor.piper))
	{
		ms_free(ms);
		exit(EC_FAILURE);
	}
	exit(ms_execute_ast_node_cmd_child(ms, node));
}

t_ms_status	ms_execute_ast_node(struct s_ms *ms, struct s_ast_node *node)
{
	t_ms_status	status;

	if (node->type == AST_NODE_PIPE)
		return (ms_execute_pipe(ms, node));
	else if (node->type == AST_NODE_CMD)
	{
		ms->executor.redirection_in_fd = STDIN_FILENO;
		ms->executor.redirection_out_fd = STDOUT_FILENO;
		if (ms_ast_node_content_expand(node->content, ms) == PROGRAM_ERROR)
			return (PROGRAM_ERROR);
		status = ms_all_redirection_in_out_open(&ms->executor, node->content);
		if (status != PROGRAM_SUCCESS)
			return (status);
		return (ms_execute_ast_node_cmd(ms, node));
	}
	return (PROGRAM_FAILURE);
}

t_ms_status	ms_execute_ast_node_last(struct s_ms *ms, struct s_ast_node *node)
{
	t_ms_status	status;

	if (node->type == AST_NODE_CMD)
	{
		ms->executor.redirection_in_fd = STDIN_FILENO;
		ms->executor.redirection_out_fd = STDOUT_FILENO;
		if (ms_ast_node_content_expand(node->content, ms) == PROGRAM_ERROR)
			return (PROGRAM_ERROR);
		status = ms_all_redirection_in_out_open(&ms->executor, node->content);
		if (status != PROGRAM_SUCCESS)
			return (status);
		return (ms_execute_ast_node_cmd_last(ms, node));
	}
	return (PROGRAM_FAILURE);
}
