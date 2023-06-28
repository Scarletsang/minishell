/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:04:28 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 22:03:02 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include <stdio.h>
#include "MINISHELL/execution/command/external.h"
#include "MINISHELL/error_printer.h"

static t_ms_exit_code	ms_execve_builder_internal_error_return(\
struct s_ms_execve_builder *builder)
{
	ms_error_printer_internal_error();
	ms_execve_builder_free(builder);
	return (EC_FAILURE);
}

t_ms_status	ms_execve_builder_path_build_wrapper(\
struct s_ms_execve_builder *builder)
{
	t_ms_status	status;

	status = ms_execve_builder_path_build(builder);
	if (status == PROGRAM_FAILURE)
	{
		ms_execve_builder_command_path_error(builder);
		ms_execve_builder_free(builder);
	}
	else if (status == PROGRAM_ERROR)
	{
		ms_error_printer_internal_error();
		ms_execve_builder_free(builder);
	}
	return (status);
}

t_ms_exit_code	ms_execute_external_executable(struct s_ms *ms, \
t_sb_vector *command)
{
	struct s_ms_execve_builder	builder;
	t_ms_status					status;

	if (ms_execve_builder_init(&builder, ms, command))
		return (EC_FAILURE);
	if ((builder.path_env == NULL) || \
		ft_strchr(builder.command_name->buffer, '/'))
		ms_execve_builder_command_name_exit_code_get(&builder);
	else
	{
		status = ms_execve_builder_path_build_wrapper(&builder);
		if (status == PROGRAM_FAILURE)
			return (builder.exit_code);
		if (status == PROGRAM_ERROR)
			return (EC_FAILURE);
	}
	if (builder.exit_code != EC_SUCCESS)
		return (ms_execve_builder_free(&builder), builder.exit_code);
	if (ms_execve_builder_argv_build(&builder, command) != PROGRAM_SUCCESS)
		return (ms_execve_builder_internal_error_return(&builder));
	execve(builder.command_path.buffer, builder.argv, \
		ms_executor_envp_get(&ms->executor));
	ms_execve_builder_free(&builder);
	return (EC_COMMAND_NOT_FOUND);
}
