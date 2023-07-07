/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 10:52:29 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "MINISHELL/error_printer.h"
#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_redirection_in_file_open(\
struct s_ms_executor *executor, const char *filename, int flags)
{
	if (executor->redirection_in_fd != STDIN_FILENO)
	{
		if (close(executor->redirection_in_fd) == -1)
			return (PROGRAM_ERROR);
	}
	executor->redirection_in_fd = open(filename, flags, 0644);
	if (executor->redirection_in_fd == -1)
	{
		ms_error_printer_command(filename, strerror(errno));
		return (PROGRAM_FAILURE);
	}
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_executor_redirection_out_file_open(\
struct s_ms_executor *executor, const char *filename, int flags)
{
	if (executor->redirection_out_fd != STDOUT_FILENO)
	{
		if (close(executor->redirection_out_fd) == -1)
			return (PROGRAM_ERROR);
	}
	executor->redirection_out_fd = open(filename, flags, 0644);
	if (executor->redirection_out_fd == -1)
	{
		ms_error_printer_command(filename, strerror(errno));
		return (PROGRAM_FAILURE);
	}
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_executor_redirect_in_and_out(struct s_ms_executor *executor)
{
	if ((executor->redirection_in_fd != STDIN_FILENO) && \
		(executor->redirection_in_fd != -1))
	{
		if (dup2(executor->redirection_in_fd, STDIN_FILENO) == -1)
			return (PROGRAM_ERROR);
		if (close(executor->redirection_in_fd) == -1)
			return (PROGRAM_ERROR);
	}
	if ((executor->redirection_out_fd != STDOUT_FILENO) && \
		(executor->redirection_out_fd != -1))
	{
		if (dup2(executor->redirection_out_fd, STDOUT_FILENO) == -1)
			return (PROGRAM_ERROR);
		if (close(executor->redirection_out_fd) == -1)
			return (PROGRAM_ERROR);
	}
	return (PROGRAM_SUCCESS);
}

t_ms_exit_code	ms_executor_wait(struct s_ms_executor *executor)
{
	int				wstatus;
	t_ms_exit_code	exit_code;
	pid_t			pid;

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
