/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 20:26:10 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_redirect_from_file(const char *filename, \
int flags)
{
	t_ms_status	exit_code;
	int			fd;

	if (close(STDIN_FILENO) == -1)
		return (PROGRAM_ERROR);
	fd = open(filename, flags, 0644);
	if (fd == -1)
		return (PROGRAM_ERROR);
	exit_code = PROGRAM_SUCCESS;
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_code = PROGRAM_ERROR;
	if (close(fd) == -1)
		exit_code = PROGRAM_ERROR;
	return (exit_code);
}

t_ms_status	ms_executor_redirect_to_file(const char *filename, \
int flags)
{
	t_ms_status	exit_code;
	int			fd;

	if (close(STDOUT_FILENO) == -1)
		return (PROGRAM_ERROR);
	fd = open(filename, flags, 0644);
	if (fd == -1)
		return (PROGRAM_ERROR);
	exit_code = PROGRAM_SUCCESS;
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_code = PROGRAM_ERROR;
	if (close(fd) == -1)
		exit_code = PROGRAM_ERROR;
	return (exit_code);
}

t_ms_status	ms_executor_redirect_from_heredoc(void)
{
	t_ms_status	exit_code;
	int			fd;

	if (close(STDIN_FILENO) == -1)
		return (PROGRAM_ERROR);
	fd = open(HEREDOC_FILENAME, O_RDONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (PROGRAM_ERROR);
	exit_code = PROGRAM_SUCCESS;
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_code = PROGRAM_ERROR;
	if (close(fd) == -1)
		exit_code = PROGRAM_ERROR;
	return (exit_code);
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
