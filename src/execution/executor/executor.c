/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/09 20:58:16 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

void	ms_executor_init(struct s_ms_executor *executor)
{
	executor->stdout_pipe = PIPE1;
}

int	ms_executor_pipe(struct s_ms_executor *executor)
{
	if (pipe(ms_executor_get_stdout_pipe(executor)) == -1)
		return (EXIT_FAILURE);
	executor->stdout_pipe ^= 1;
	return (EXIT_SUCCESS);
}

pid_t	ms_executor_fork(struct s_ms_executor *executor)
{
	executor->last_child_pid = fork();
	return (executor->last_child_pid);
}

t_executor_exit_code	ms_executor_wait(struct s_ms_executor *executor)
{
	int						wstatus;
	t_executor_exit_code	exit_code;
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
