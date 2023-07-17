/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/07/17 11:47:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_init(struct s_ms_executor *executor)
{
	if (ft_vector_init(&executor->envp, sizeof(char *), 20, \
		ft_vector_copy_string) || \
		ft_iostream_init(&executor->stdin_stream))
		return (PROGRAM_ERROR);
	executor->redirection_in_fd = STDIN_FILENO;
	executor->redirection_out_fd = STDOUT_FILENO;
	ft_vector_append(&executor->envp, NULL);
	ms_piper_init(&executor->piper);
	executor->last_exit_code = EC_SUCCESS;
	executor->last_child_pid = -1;
	return (PROGRAM_SUCCESS);
}

void	ms_executor_reset(struct s_ms_executor *executor)
{
	ms_piper_init(&executor->piper);
	ft_iostream_reset(&executor->stdin_stream);
	executor->redirection_in_fd = STDIN_FILENO;
	executor->redirection_out_fd = STDOUT_FILENO;
	executor->last_child_pid = -1;
}

t_ms_status	ms_executor_free(struct s_ms_executor *executor)
{
	executor->last_child_pid = -1;
	ft_vector_free(&executor->envp);
	ft_iostream_free(&executor->stdin_stream);
	if (executor->redirection_in_fd != -1 && \
		executor->redirection_in_fd != STDIN_FILENO)
		close(executor->redirection_in_fd);
	if (executor->redirection_out_fd != -1 && \
		executor->redirection_out_fd != STDOUT_FILENO)
		close(executor->redirection_out_fd);
	executor->redirection_in_fd = STDIN_FILENO;
	executor->redirection_out_fd = STDOUT_FILENO;
	if (ms_piper_reset(&executor->piper))
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}
