/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/11 15:29:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

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
