/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enactment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:41:25 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 17:02:17 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include "MINISHELL/execution/executor.h"
#include "MINISHELL/execution/executor/enactment.h"
#include "MINISHELL/execution/executor/builtins.h"

t_executor_exit_code	ms_executor_enact(struct s_ms_executor *executor, \
struct s_ast_node *node, struct s_ms *ms)
{
	t_executor_exit_code	exit_code;

	if (node->type == AST_NODE_PIPE)
		return (ms_executor_enact_pipe(executor, node, ms));
	else if (node->type == AST_NODE_COMMAND)
	{
		if (ms_executor_expand_content(node->content, ms) == EXECUTION_ERROR)
			return (EXECUTION_ERROR);
		exit_code = ms_executor_enact_builtin(executor, node->content, ms);
		if (exit_code != EXECUTION_FAILURE)
			return (exit_code);
		if (ms_executor_fork(executor) < 0)
			return (EXECUTION_ERROR);
		if (executor->last_child_pid != 0)
			return (EXECUTION_SUCCESS);
		// use sender and receiver
		exit(ms_executor_enact_command(executor, node->content, ms));
	}
	return (EXECUTION_FAILURE);
}

t_executor_exit_code	ms_executor_enact_in_pipe(\
struct s_ms_executor *executor, struct s_ast_node *node, struct s_ms *ms)
{
	if (node->type == AST_NODE_PIPE)
		return (ms_executor_enact_pipe(executor, node, ms));
	else if (node->type == AST_NODE_COMMAND)
	{
		if (ms_executor_expand_content(node->content, ms) == EXECUTION_ERROR)
			return (EXECUTION_ERROR);
		ms_piper_create_receiver(&executor->piper);
		if (ms_piper_create_sender(&executor->piper))
			return (EXECUTION_ERROR);
		if (ms_executor_fork(executor) < 0)
			return (EXECUTION_ERROR);
		if (executor->last_child_pid != 0)
			return (EXECUTION_SUCCESS);
		// use sender and receiver
		if (ms_executor_enact_builtin(executor, node->content, ms) \
			!= EXECUTION_FAILURE)
			exit(EXIT_FAILURE); // TODO: executor cleanup
		exit(ms_executor_enact_command(executor, node->content, ms));
	}
	return (EXECUTION_FAILURE);
}

t_executor_exit_code	ms_executor_enact_pipe(\
struct s_ms_executor *executor, struct s_ast_node *node, struct s_ms *ms)
{
	if (ms_executor_enact_in_pipe(executor, node->left, ms) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	if (ms_executor_enact_in_pipe(executor, node->right, ms) == EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_builtin(\
struct s_ms_executor *executor, struct s_ast_node_content *content, \
struct s_ms *ms)
{
	t_ft_sb	*name_sb;
	char	*name;

	name_sb = ft_vector_get(&content->command, 0);
	if (!name_sb)
		return (EXECUTION_FAILURE);
	name = name_sb->buffer;
	if (ft_strcmp(name, "echo") == 0)
		return (ms_builtin_echo(executor, &content->command, ms));
	if (ft_strcmp(name, "cd") == 0)
		return (ms_builtin_cd(executor, &content->command, ms));
	if (ft_strcmp(name, "pwd") == 0)
		return (ms_builtin_pwd(executor, &content->command, ms));
	if (ft_strcmp(name, "unset") == 0)
		return (ms_builtin_unset(executor, &content->command, ms));
	if (ft_strcmp(name, "export") == 0)
		return (ms_builtin_export(executor, &content->command, ms));
	if (ft_strcmp(name, "env") == 0)
		return (ms_builtin_env(executor, &content->command, ms));
	if (ft_strcmp(name, "exit") == 0)
		return (ms_builtin_exit(executor, &content->command, ms));
	return (EXECUTION_FAILURE);
}

t_executor_return_value	ms_executor_enact_command(\
struct s_ms_executor *executor, struct s_ast_node_content *content, \
struct s_ms *ms)
{
	if ((ms_executor_enact_assignment(executor, \
		&content->assignment, ms) == EXECUTION_ERROR) || \
	(ms_executor_enact_redirection_in(executor, \
		&content->redirection_in, ms) == EXECUTION_ERROR) || \
	(ms_executor_enact_redirection_out(executor, \
		&content->redirection_out, ms) == EXECUTION_ERROR) || \
	(ms_executor_enact_command_execution(executor, \
		&content->command, ms) == EXECUTION_ERROR))
		;
	// TODO: executor cleanup
	return (EXIT_FAILURE);
}
