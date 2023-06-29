/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 21:48:41 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_init(struct s_ms_executor *executor)
{
	if (ft_vector_init(&executor->envp, sizeof(char *), 20, \
		ft_vector_copy_string) || \
		ft_iostream_init(&executor->heredoc))
		return (PROGRAM_ERROR);
	executor->stdin_fd = dup(STDIN_FILENO);
	executor->stdout_fd = dup(STDOUT_FILENO);
	if (executor->stdin_fd == -1 || executor->stdout_fd == -1)
	{
		ft_vector_free(&executor->envp);
		return (PROGRAM_ERROR);
	}
	ft_vector_append(&executor->envp, NULL);
	ms_piper_init(&executor->piper);
	executor->last_child_pid = -1;
	return (PROGRAM_SUCCESS);
}

void	ms_executor_reset(struct s_ms_executor *executor)
{
	ms_piper_init(&executor->piper);
	ft_iostream_reset(&executor->heredoc);
	executor->last_child_pid = -1;
}

t_ms_status	ms_executor_free(struct s_ms_executor *executor)
{
	t_ms_status	exit_code;

	executor->last_child_pid = -1;
	ft_vector_free(&executor->envp);
	ft_iostream_free(&executor->heredoc);
	exit_code = PROGRAM_SUCCESS;
	if (close(executor->stdin_fd) == -1)
		exit_code = PROGRAM_ERROR;
	if (close(executor->stdout_fd) == -1)
		exit_code = PROGRAM_ERROR;
	if (ms_piper_reset(&executor->piper))
		exit_code = PROGRAM_ERROR;
	return (exit_code);
}
