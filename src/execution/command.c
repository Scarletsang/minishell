/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:28:52 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 21:17:38 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

t_ms_status	ms_execute_assignment_and_redirection(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_assignments(ms, &content->assignment) \
		== PROGRAM_ERROR) || \
	(ms_execute_redirection_in(&ms->executor, &content->redirection_in) \
		== PROGRAM_ERROR) || \
	(ms_execute_redirection_out(&content->redirection_out) \
		== PROGRAM_ERROR))
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}

t_ms_exit_code	ms_execute_command(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_assignment_and_redirection(ms, \
			&content->command) == PROGRAM_ERROR))
		return (EC_FAILURE);
	return (ms_execute_executable(ms, &content->command));
}
