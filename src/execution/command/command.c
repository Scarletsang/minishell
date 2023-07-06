/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:28:52 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 00:51:59 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/command.h"
#include "MINISHELL/execution/command/builtins.h"
#include "MINISHELL/execution/command/external.h"

t_ms_exit_code	ms_execute_external(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_assignments_and_redirections(ms, content) \
		!= PROGRAM_SUCCESS))
		return (EC_FAILURE);
	return (ms_execute_external_executable(ms, &content->command));
}

t_ms_exit_code	ms_execute_builtin(struct s_ms *ms, \
enum e_ms_execution_mode mode, struct s_ast_node_content *content)
{
	if ((ms_execute_assignments_and_redirections(ms, content) \
		!= PROGRAM_SUCCESS))
		return (EC_FAILURE);
	if (mode == MODE_BUILTIN_ECHO)
		return (ms_execute_builtin_echo(ms, &content->command));
	if (mode == MODE_BUILTIN_CD)
		return (ms_execute_builtin_cd(ms, &content->command));
	if (mode == MODE_BUILTIN_PWD)
		return (ms_execute_builtin_pwd(ms, &content->command));
	if (mode == MODE_BUILTIN_UNSET)
		return (ms_execute_builtin_unset(ms, &content->command));
	if (mode == MODE_BUILTIN_EXPORT)
		return (ms_execute_builtin_export(ms, &content->command));
	if (mode == MODE_BUILTIN_ENV)
		return (ms_execute_builtin_env(ms, &content->command));
	if (mode == MODE_BUILTIN_EXIT)
		return (ms_execute_builtin_exit(ms, &content->command));
	return (EC_FAILURE);
}

t_ms_status	ms_execute_declares_and_redirections(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if ((ms_execute_declares(ms, &content->assignment) \
		== PROGRAM_ERROR))
		return (PROGRAM_ERROR);
	return (ms_executor_redirect_in_and_out(&ms->executor));
}

t_ms_status	ms_execute_assignments_and_redirections(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	if (ms_execute_assignments(ms, &content->assignment) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	return (ms_executor_redirect_in_and_out(&ms->executor));
}
