/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/17 18:05:18 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_executor_exit_code	ms_executor_init(struct s_ms_executor *executor)
{
	if (vector_init(&executor->envp, sizeof(char *), 20, vector_set_string))
		return (EXECUTION_ERROR);
	executor->stdin_fd = dup(STDIN_FILENO);
	if (executor->stdin_fd == -1)
	{
		vector_free(&executor->envp);
		return (EXECUTION_ERROR);
	}
	vector_append(&executor->envp, NULL);
	ms_piper_init(&executor->piper);
	executor->heredoc_fd_opened = false;
	executor->last_child_pid = -1;
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_close_heredoc_fd(\
struct s_ms_executor *executor)
{
	t_executor_exit_code	exit_code;

	exit_code = EXECUTION_SUCCESS;
	if (executor->heredoc_fd_opened)
	{
		if (unlink(HEREDOC_FILENAME) == -1)
			exit_code = EXECUTION_ERROR;
		if (close(executor->heredoc_fd) == -1)
			exit_code = EXECUTION_ERROR;
		executor->heredoc_fd_opened = false;
	}
	return (exit_code);
}

t_executor_exit_code	ms_executor_destroy(struct s_ms_executor *executor)
{
	t_executor_exit_code	exit_code;

	executor->last_child_pid = -1;
	vector_free(&executor->envp);
	exit_code = EXECUTION_SUCCESS;
	if (close(executor->stdin_fd) == -1)
		exit_code = EXECUTION_ERROR;
	if (ms_piper_destroy(&executor->piper))
		exit_code = EXECUTION_ERROR;
	return (exit_code);
}
