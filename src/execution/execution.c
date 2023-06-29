/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:20:23 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 17:08:03 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include "MINISHELL/execution.h"
#include "MINISHELL/execution/command.h"
#include "MINISHELL/error_printer.h"

enum e_ms_execution_mode	ms_execution_mode(t_sb_vector *command)
{
	char	*name;

	if (command->size == 0)
		return (MODE_NO_COMMAND);
	name = ((t_ft_sb *) command->buffer)->buffer;
	if (ft_strcmp(name, "echo") == 0)
		return (MODE_BUILTIN_ECHO);
	if (ft_strcmp(name, "cd") == 0)
		return (MODE_BUILTIN_CD);
	if (ft_strcmp(name, "pwd") == 0)
		return (MODE_BUILTIN_PWD);
	if (ft_strcmp(name, "unset") == 0)
		return (MODE_BUILTIN_UNSET);
	if (ft_strcmp(name, "export") == 0)
		return (MODE_BUILTIN_EXPORT);
	if (ft_strcmp(name, "env") == 0)
		return (MODE_BUILTIN_ENV);
	if (ft_strcmp(name, "exit") == 0)
		return (MODE_BUILTIN_EXIT);
	return (MODE_EXECUTABLE);
}

static t_ms_exit_code	ms_execute_ast_node_cmd_single(struct s_ms *ms, \
struct s_ast_node *root)
{
	t_ms_exit_code				exit_code;
	enum e_ms_execution_mode	mode;

	mode = ms_execution_mode(&root->content->command);
	if (mode == MODE_EXECUTABLE)
	{
		if (ms_executor_fork(&ms->executor) < 0)
			return (ms_error_printer_internal_error(), EC_FAILURE);
		if (ms->executor.last_child_pid == 0)
		{
			exit_code = ms_execute_external(ms, root->content);
			ms_free(ms);
			exit(exit_code);
		}
		return (EC_SUCCESS);
	}
	if (mode == MODE_NO_COMMAND)
		exit_code = ms_status_to_exit_code(\
			ms_execute_declares_and_redirections(ms, root->content));
	else
		exit_code = ms_execute_builtin(ms, mode, root->content);
	if (ms_executor_reset_stdin_stdout(&ms->executor) == PROGRAM_ERROR)
		return (ms_error_printer_internal_error(), EC_FAILURE);
	return (exit_code);
}

t_ms_exit_code	ms_execute_ast(struct s_ms *ms, struct s_ast_node *root)
{
	t_ms_exit_code	exit_code;

	exit_code = EC_FAILURE;
	if (root->type == AST_NODE_PIPE)
	{
		if (ms_execute_pipe(ms, root) == PROGRAM_ERROR)
		{
			ms_executor_wait(&ms->executor);
			return (ms_error_printer_internal_error(), EC_FAILURE);
		}
	}
	else if (root->type == AST_NODE_CMD)
	{
		if (ms_ast_node_content_expand(root->content, ms) == PROGRAM_ERROR)
			return (ms_error_printer_internal_error(), EC_FAILURE);
		exit_code = ms_execute_ast_node_cmd_single(ms, root);
	}
	else
		return (EC_FAILURE);
	if (ms->executor.last_child_pid == -1)
		return (exit_code);
	return (ms_executor_wait(&ms->executor));
}
