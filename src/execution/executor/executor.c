/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 13:31:17 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

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

t_executor_exit_code	ms_executor_init(struct s_ms_executor *executor)
{
	if (vector_init(&executor->envp, sizeof(char *), 20, vector_set_string))
		return (EXECUTION_ERROR);
	vector_append(&executor->envp, NULL);
	ms_piper_init(&executor->piper);
	executor->last_child_pid = -1;
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_destroy(struct s_ms_executor *executor)
{
	executor->last_child_pid = -1;
	vector_free(&executor->envp);
	if (ms_piper_destroy(&executor->piper))
		return (EXECUTION_ERROR);
	return (EXECUTION_SUCCESS);
}

pid_t	ms_executor_fork(struct s_ms_executor *executor)
{
	executor->last_child_pid = fork();
	return (executor->last_child_pid);
}
