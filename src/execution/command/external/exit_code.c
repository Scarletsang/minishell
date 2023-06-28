/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:05:48 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 21:55:05 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "MINISHELL/error_printer.h"
#include "MINISHELL/execution/command/external.h"

t_ms_exit_code	ms_execve_builder_command_name_exit_code_get(\
struct s_ms_execve_builder *builder)
{
	struct stat	path_stat;

	if (access(builder->command_name->buffer, F_OK) == -1)
	{
		ms_execve_builder_command_name_error(builder, ENOENT);
		builder->exit_code = EC_COMMAND_NOT_FOUND;
	}
	else if (stat(builder->command_name->buffer, &path_stat) == -1)
	{
		ms_error_printer_internal_error();
		builder->exit_code = EC_FAILURE;
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ms_execve_builder_command_name_error(builder, EISDIR);
		builder->exit_code = EC_COMMAND_NO_PERMISSION;
	}
	else if (access(builder->command_name->buffer, X_OK) == -1)
	{
		ms_execve_builder_command_name_error(builder, EACCES);
		builder->exit_code = EC_COMMAND_NO_PERMISSION;
	}
	return (builder->exit_code);
}

t_ms_exit_code	ms_execve_builder_command_path_exit_code_get(\
struct s_ms_execve_builder *builder)
{
	if (access(builder->command_path.buffer, F_OK) == -1)
	{
		builder->exit_code = EC_COMMAND_NOT_FOUND;
	}
	else if (access(builder->command_path.buffer, X_OK) == -1)
	{
		builder->exit_code = EC_COMMAND_NO_PERMISSION;
	}
	else
	{
		builder->exit_code = EC_SUCCESS;
	}
	return (builder->exit_code);
}

void	ms_execve_builder_command_path_error(\
struct s_ms_execve_builder *builder)
{
	if (builder->exit_code == EC_COMMAND_NOT_FOUND)
		ms_error_printer_command(builder->command_name->buffer, \
			"command not found");
	else if (builder->exit_code == EC_COMMAND_NO_PERMISSION)
		ms_error_printer_command(builder->command_name->buffer, \
			strerror(EACCES));
}

void	ms_execve_builder_command_name_error(\
struct s_ms_execve_builder *builder, int error_num)
{
	ms_error_printer_command(builder->command_name->buffer, \
		strerror(error_num));
}
