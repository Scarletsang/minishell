/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:50:34 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 18:05:36 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_open_heredoc(struct s_ms_executor *executor, int *fd)
{
	if (dup2(executor->stdin_fd, STDIN_FILENO) == -1)
		return (PROGRAM_ERROR);
	*fd = open(HEREDOC_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_executor_redirect_from_heredoc(int opened_heredoc_fd)
{
	t_ms_status	exit_code;

	if (close(opened_heredoc_fd) == -1)
		return (PROGRAM_ERROR);
	exit_code = PROGRAM_SUCCESS;
	opened_heredoc_fd = open(HEREDOC_FILENAME, O_RDONLY, 0644);
	if (unlink(HEREDOC_FILENAME) == -1)
		return (PROGRAM_ERROR);
	if (dup2(opened_heredoc_fd, STDIN_FILENO) == -1)
		exit_code = PROGRAM_ERROR;
	if (close(opened_heredoc_fd) == -1)
		exit_code = PROGRAM_ERROR;
	return (exit_code);
}
