/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:04:28 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 15:03:00 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include "MINISHELL/execution/command/external.h"
#include "MINISHELL/error_printer.h"

static t_ms_exit_code	ms_execve_builder_path_build_and_validate(\
struct s_ms_execve_builder *builder)
{
	t_ms_exit_code	exit_code;
	if ((builder->path_env == NULL) || \
		ft_strchr(builder->command_name->buffer, '/'))
	{
		exit_code = ms_executable_exit_code_evaluate(\
			builder->command_name->buffer, true, true);
	}
	else
	{
		exit_code = ms_execve_builder_path_build(builder);
		ms_executable_exit_code_print(exit_code, \
			builder->command_name->buffer);
		exit_code = ms_executable_exit_code_output(exit_code);
	}
	return (exit_code);
}

t_ms_exit_code	ms_execute_external_executable(struct s_ms *ms, \
t_sb_vector *command)
{
	struct s_ms_execve_builder	builder;
	t_ms_exit_code				exit_code;

	if (ms_execve_builder_init(&builder, ms, command))
		return (EC_FAILURE);
	exit_code = ms_execve_builder_path_build_and_validate(&builder);
	if (exit_code != EC_SUCCESS)
	{
		ms_execve_builder_free(&builder);
		return (exit_code);
	}
	if (ms_execve_builder_argv_build(&builder, command) != PROGRAM_SUCCESS)
	{
		ms_error_printer_internal_error();
		ms_execve_builder_free(&builder);
		return (EC_FAILURE);
	}
	execve(builder.command_path.buffer, builder.argv, \
		ms_executor_envp(&ms->executor));
	ms_execve_builder_free(&builder);
	return (EC_COMMAND_NOT_FOUND);
}
