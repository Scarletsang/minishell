/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:28:52 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 17:47:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

t_executor_return_value	ms_execute_command(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_assignments(ms, &content->assignment) \
		== EXECUTION_ERROR) || \
	(ms_execute_redirection_in(&ms->executor, &content->redirection_in) \
		== EXECUTION_ERROR) || \
	(ms_execute_redirection_out(&content->redirection_out) \
		== EXECUTION_ERROR) || \
	(ms_execute_executable(ms, &content->command) == EXECUTION_ERROR))
		;
	// TODO: executor cleanup
	return (EXIT_FAILURE);
}
