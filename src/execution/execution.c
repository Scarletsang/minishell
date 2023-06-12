/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:20:23 by htsang            #+#    #+#             */
/*   Updated: 2023/06/11 17:22:42 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

t_executor_return_value	ms_execute(struct s_AST_node *node, struct s_ms *ms)
{
	struct s_ms_executor	executor;
	t_executor_return_value	return_value;

	return_value = EXIT_FAILURE;
	ms_executor_init(&executor);
	if (ms_executor_enact(&executor, node, ms) == EXECUTION_ERROR)
		ms_executor_wait(&executor);
	else
		return_value = ms_executor_wait(&executor);
	if (ms_executor_destroy(&executor) == EXECUTION_ERROR)
		return (EXIT_FAILURE);
	return (return_value);
}
