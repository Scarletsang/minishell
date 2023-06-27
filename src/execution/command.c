/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:28:52 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 11:47:12 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

t_ms_status	ms_execute_declares_and_redirections(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_declares(ms, &content->assignment) \
		== PROGRAM_ERROR) || \
	(ms_execute_redirection_in(&ms->executor, &content->redirection_in) \
		== PROGRAM_ERROR) || \
	(ms_execute_redirection_out(&ms->executor, &content->redirection_out) \
		== PROGRAM_ERROR))
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_execute_assignments_and_redirections(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_assignments(ms, &content->assignment) \
		== PROGRAM_ERROR) || \
	(ms_execute_redirection_in(&ms->executor, &content->redirection_in) \
		== PROGRAM_ERROR) || \
	(ms_execute_redirection_out(&ms->executor, &content->redirection_out) \
		== PROGRAM_ERROR))
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}

t_ms_exit_code	ms_execute_command(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_assignments_and_redirections(ms, content) == PROGRAM_ERROR))
		return (EC_FAILURE);
	return (ms_execute_executable(ms, &content->command));
}
