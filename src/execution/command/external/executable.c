/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:04:28 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 11:43:43 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/command/external.h"

t_ms_exit_code	ms_execute_external_executable(struct s_ms *ms, \
t_sb_vector *command)
{
	struct s_ms_execve_builder	builder;

	if (ms_execve_builder_init(&builder))
		return (EC_FAILURE);
	if (ms_execve_builder_path_build(&builder, ms, \
		(t_ft_sb *) ft_vector_get(command, 0)) != PROGRAM_SUCCESS)
	{
		ms_execve_builder_free(&builder);
		return (EC_COMMAND_NOT_FOUND);
	}
	if (!ms_execve_builder_path_is_executable(&builder))
	{
		ms_execve_builder_free(&builder);
		return (EC_COMMAND_NO_PERMISSION);
	}
	if (ms_execve_builder_argv_build(&builder, command) != PROGRAM_SUCCESS)
	{
		ms_execve_builder_free(&builder);
		return (EC_FAILURE);
	}
	execve(builder.path.buffer, builder.argv, ms_executor_envp_get(ms));
	ms_execve_builder_free(&builder);
	return (EC_COMMAND_NOT_FOUND);
}
