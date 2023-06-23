/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:28:42 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 20:53:13 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include "MINISHELL/execution.h"
#include "MINISHELL/execution/builtins.h"

t_ms_exit_code	ms_execute_builtin(struct s_ms *ms, \
enum e_ms_execution_mode mode, struct s_ast_node_content *content)
{
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
