/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/21 15:22:07 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_executor_exit_code	ms_executor_init(struct s_ms_executor *executor)
{
	if (ft_vector_init(&executor->envp, sizeof(char *), 20, \
		ft_vector_copy_string) || \
		ft_iostream_init(&executor->iostream))
		return (EXECUTION_ERROR);
	executor->stdin_fd = dup(STDIN_FILENO);
	if (executor->stdin_fd == -1)
	{
		ft_vector_free(&executor->envp);
		return (EXECUTION_ERROR);
	}
	ft_vector_append(&executor->envp, NULL);
	ms_piper_init(&executor->piper);
	executor->last_child_pid = -1;
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_destroy(struct s_ms_executor *executor)
{
	t_executor_exit_code	exit_code;

	executor->last_child_pid = -1;
	ft_vector_free(&executor->envp);
	ft_iostream_free(&executor->iostream);
	exit_code = EXECUTION_SUCCESS;
	if (close(executor->stdin_fd) == -1)
		exit_code = EXECUTION_ERROR;
	if (ms_piper_destroy(&executor->piper))
		exit_code = EXECUTION_ERROR;
	return (exit_code);
}
