/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/09 22:33:38 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

int	ms_executor_read_from_pipe(struct s_ms_executor *executor)
{
	int	*stdin_pipe;
	int	exit_code;

	stdin_pipe = ms_executor_get_stdin_pipe(executor);
	exit_code = EXIT_SUCCESS;
	if (dup2(stdin_pipe[0], STDOUT_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	if (close(stdin_pipe[0]) == -1)
		exit_code = EXIT_FAILURE;
	if (close(stdin_pipe[1]) == -1)
		exit_code = EXIT_FAILURE;
	return (exit_code);
}

int	ms_executor_write_to_pipe(struct s_ms_executor *executor)
{
	int	*stdout_pipe;
	int	exit_code;

	stdout_pipe = ms_executor_get_stdout_pipe(executor);
	exit_code = EXIT_SUCCESS;
	if (dup2(stdout_pipe[1], STDOUT_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	if (close(stdout_pipe[0]) == -1)
		exit_code = EXIT_FAILURE;
	if (close(stdout_pipe[1]) == -1)
		exit_code = EXIT_FAILURE;
	return (exit_code);
}

int	ms_executor_read_from_fd(int fd)
{
	int	exit_code;

	if (dup2(fd, STDIN_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	if (close(fd) == -1)
		exit_code = EXIT_FAILURE;
	return (exit_code);
}

int	ms_executor_write_to_fd(int fd)
{
	int	exit_code;

	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	if (close(fd) == -1)
		exit_code = EXIT_FAILURE;
	return (exit_code);
}
