/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 22:45:37 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_init(struct s_ms_executor *executor)
{
	if (ft_vector_init(&executor->envp, sizeof(char *), 20, \
		ft_vector_copy_string) || \
		ft_iostream_init(&executor->iostream))
		return (PROGRAM_ERROR);
	executor->stdin_fd = dup(STDIN_FILENO);
	if (executor->stdin_fd == -1)
	{
		ft_vector_free(&executor->envp);
		return (PROGRAM_ERROR);
	}
	ft_vector_append(&executor->envp, NULL);
	ms_piper_init(&executor->piper);
	executor->last_child_pid = -1;
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_executor_reset(struct s_ms_executor *executor)
{
	ms_piper_init(&executor->piper);
	ft_iostream_reset(&executor->iostream);
	executor->last_child_pid = -1;
}

t_ms_status	ms_executor_destroy(struct s_ms_executor *executor)
{
	t_ms_status	exit_code;

	executor->last_child_pid = -1;
	ft_vector_free(&executor->envp);
	ft_iostream_free(&executor->iostream);
	exit_code = PROGRAM_SUCCESS;
	if (close(executor->stdin_fd) == -1)
		exit_code = PROGRAM_ERROR;
	if (ms_piper_destroy(&executor->piper))
		exit_code = PROGRAM_ERROR;
	return (exit_code);
}
