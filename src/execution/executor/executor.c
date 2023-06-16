/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 16:40:13 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

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
