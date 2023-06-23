/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:28:42 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 17:55:17 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include "MINISHELL/execution.h"
#include "MINISHELL/execution/builtins.h"

t_executor_exit_code	ms_execute_builtin(struct s_ms *ms, \
struct s_ast_node_content *content)
{
	t_ft_sb	*name_sb;
	char	*name;

	name_sb = ft_vector_get(&content->command, 0);
	if (!name_sb)
		return (EXECUTION_FAILURE);
	name = name_sb->buffer;
	if (ft_strcmp(name, "echo") == 0)
		return (ms_execute_builtin_echo(ms, &content->command));
	if (ft_strcmp(name, "cd") == 0)
		return (ms_execute_builtin_cd(ms, &content->command));
	if (ft_strcmp(name, "pwd") == 0)
		return (ms_execute_builtin_pwd(ms, &content->command));
	if (ft_strcmp(name, "unset") == 0)
		return (ms_execute_builtin_unset(ms, &content->command));
	if (ft_strcmp(name, "export") == 0)
		return (ms_execute_builtin_export(ms, &content->command));
	if (ft_strcmp(name, "env") == 0)
		return (ms_execute_builtin_env(ms, &content->command));
	if (ft_strcmp(name, "exit") == 0)
		return (ms_execute_builtin_exit(ms, &content->command));
	return (EXECUTION_FAILURE);
}
