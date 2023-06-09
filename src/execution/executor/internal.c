/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:55:35 by htsang            #+#    #+#             */
/*   Updated: 2023/06/09 20:57:33 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

int	*ms_executor_get_stdout_pipe(struct s_ms_executor *executor)
{
	if (executor->stdout_pipe == PIPE1)
		return (executor->pipe1);
	else
		return (executor->pipe2);
}

int	*ms_executor_get_stdin_pipe(struct s_ms_executor *executor)
{
	if (executor->stdout_pipe == PIPE1)
		return (executor->pipe2);
	else
		return (executor->pipe1);
}
