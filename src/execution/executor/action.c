/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 16:40:18 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_executor_exit_code	ms_executor_read_from_fd(int fd)
{
	t_executor_exit_code	exit_code;

	exit_code = EXECUTION_SUCCESS;
	if (fd == -1)
		return (EXECUTION_ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_code = EXECUTION_ERROR;
	if (close(fd) == -1)
		exit_code = EXECUTION_ERROR;
	return (exit_code);
}

t_executor_exit_code	ms_executor_write_to_fd(int fd)
{
	t_executor_exit_code	exit_code;

	exit_code = EXECUTION_SUCCESS;
	if (fd == -1)
		return (EXECUTION_ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_code = EXECUTION_ERROR;
	if (close(fd) == -1)
		exit_code = EXECUTION_ERROR;
	return (exit_code);
}

t_executor_return_value	ms_executor_wait(struct s_ms_executor *executor)
{
	int						wstatus;
	t_executor_return_value	exit_code;
	pid_t					pid;

	pid = 1;
	while (pid != -1)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (pid == executor->last_child_pid)
		{
			exit_code = WEXITSTATUS(wstatus);
		}
	}
	return (exit_code);
}

pid_t	ms_executor_fork(struct s_ms_executor *executor)
{
	executor->last_child_pid = fork();
	return (executor->last_child_pid);
}
